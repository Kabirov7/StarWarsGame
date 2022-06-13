#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "../Levels/TileLayer.h"
#include "../Base64/base64.h"
#include "zlib.h"
#include "../Levels/ObjectLayer.h"

using namespace std;

Level* LevelParser::parseLevel(const char *levelFile)
{
    // открываем файл
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // создаем новый уровень и начинаем его заполнять
    Level* pLevel = new Level();

    // получаем галвный тэг
    TiXmlElement* pRoot = levelDocument.RootElement();

    std::cout << "Loading level:\n" << "\tVersion: " << pRoot->Attribute("version") << "\n";
    std::cout << "\tWidth:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height") << "\n";
    std::cout << "\tTile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight") << "\n";

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    // получаем изображения для данного уровня
    TiXmlElement* pProperties = pRoot->FirstChildElement();

    // парсим каждое изображение и загружаем его в игру
    for(TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("property"))
        {
            parseTextures(e);
        }
    }

    // парсим tileset чтобы нарисовать карту
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    // парсинг объктов которые будут использоваться на карте
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if(e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            }
            else if(e->FirstChildElement()->Value() == std::string("data") ||
                    (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers());
            }
        }
    }

    return pLevel;
}


void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
    std::cout << "adding texture " << pTextureRoot->Attribute("value") << " with ID " << pTextureRoot->Attribute("name") << std::endl;
//  загрузка картинок для дальнейшего использования
    TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    std::string assetsTag = "assets/";
    // сначала добавляем  tileset(картинку с блоками) в TextureManager
    std::cout << "adding texture " << pTilesetRoot->FirstChildElement()->Attribute("source") << " with ID " << pTilesetRoot->Attribute("name") << std::endl;
    TheTextureManager::Instance()->load(assetsTag.append(pTilesetRoot->FirstChildElement()->Attribute("source")), pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

    // Создаем характеристику для tileset'a
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel)
{
    // Создаем новый layer
    ObjectLayer* pObjectLayer = new ObjectLayer();

    for(TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackID = 0, animSpeed = 0;
            std::string textureID;
            std::string type;

            // получаем изначальные тип и значения узла на карте
            e->Attribute("x", &x);
            e->Attribute("y", &y);

            type = e->Attribute("type");
            GameObject* pGameObject = TheGameObjectFactory::Instance()->create(type);

            // получаем свойства объекта, на основе которых будет создан объект
            for(TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                property->Attribute("value", &numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->Attribute("value", &height);
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->Attribute("value", &width);
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                property->Attribute("value", &callbackID);
                            }
                            else if(e->Attribute("name") == std::string("animSpeed"))
                            {
                                property->Attribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }
            // инициализируем объект
            pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames,callbackID, animSpeed)));

            // создаем игрока
            if(type == "Player")
            {
                pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
            }

            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }

    pLayers->push_back(pObjectLayer);
}

// функция декодирует карту в массив значений
void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    bool collidable = false;

    // создаем пустой массив для карты, на основе id будет рисоваться карта
    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    TiXmlElement* pDataNode;

    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("properties"))
        {
            for(TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                if(property->Value() == std::string("property"))
                {
                    if(property->Attribute("name") == std::string("collidable"))
                    {
                        collidable = true;
                    }
                }
            }
        }

        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }

    // считываем кодированную карту
    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }

    // декодируем с помощью библиотеки zlib
    // выделяем память под карту, чтобы после декодировки записались все значения
    uLongf sizeofids = m_width * m_height * sizeof(int);
    std::vector<int> ids(m_width * m_height);
    uncompress((Bytef*)&ids[0], &sizeofids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);

//    заполняем массив id пустыми значениями
    for(int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

//    получаем id блока и записываем по нужному адрессу
    for(int rows = 0; rows < m_height; rows++)
    {
        for(int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = ids[rows * m_width + cols];
        }
    }

    // определяем нашу карту в TileLayer'e
    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(m_width);

    if(collidable)
    {
        pCollisionLayers->push_back(pTileLayer);
    }

    // добавляем наш tile в layer
    pLayers->push_back(pTileLayer);
}
