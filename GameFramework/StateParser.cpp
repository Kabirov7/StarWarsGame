#include "StateParser.h"
#include "../GameFramework/Game.h"
#include "../GameFramework/GameObjectFactory.h"
#include "../GameFramework/TextureManager.h"

using namespace std;

bool StateParser::parseState(const char *stateFile, string stateID, vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs)
{
    // создаем документ для чтения
    TiXmlDocument xmlDoc;

    // начинаем читать файл
    while(!xmlDoc.LoadFile(stateFile)){}

    // получаем первый элемент
    TiXmlElement* pRoot = xmlDoc.RootElement();

    // инициализируем state
    TiXmlElement* pStateRoot = 0;
    // получаем главный узел текущего состояния и говорим что он нам нужен чтобы прочитать стэйт и правильно его отобразить
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == stateID)
        {
            pStateRoot = e;
            break;
        }
    }

    // инициализация тэга родителя всех текстур
    TiXmlElement* pTextureRoot = 0;

    // получение тэга текстур
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == string("TEXTURES"))
        {
            pTextureRoot = e;
            break;
        }
    }

    // парсим все текстуры
    parseTextures(pTextureRoot, pTextureIDs);

    // инициализация тэга родителя всех объектов
    TiXmlElement* pObjectRoot = 0;

    // получение тэга объектов
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == string("OBJECTS"))
        {
            pObjectRoot = e;
            break;
        }
    }

//    парсим все объекты
    parseObjects(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{
    // получаем текстуру и добавляем его в менеджер текстур
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        string filenameAttribute = e->Attribute("filename");
        string idAttribute = e->Attribute("ID");

        pTextureIDs->push_back(idAttribute); // добавляем id текстуры чтобы потом удалить

        TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer());
    }
}

void StateParser::parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjects)
{
//    поступам с объектами так же как мы поступали с текстурами
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        string textureID;
        textureID = e->Attribute("textureID");
        if (textureID != "background") {
            e->Attribute("x", &x);
            e->Attribute("y", &y);
            e->Attribute("width", &width);
            e->Attribute("height", &height);
            e->Attribute("numFrames", &numFrames);
            e->Attribute("callbackID", &callbackID);
            e->Attribute("animSpeed", &animSpeed);
        } else {
            x = 0;
            y = 0;
            width = TheGame::Instance()->getGameWidth();
            height = TheGame::Instance()->getGameHeight();
            numFrames = 1;
            callbackID = 0;
            animSpeed = 1;
        }

        GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
        pObjects->push_back(pGameObject);
    }
}