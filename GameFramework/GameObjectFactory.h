#ifndef STARWARS_GAMEOBJECTFACTORY_H
#define STARWARS_GAMEOBJECTFACTORY_H


#include <map>
#include "GameObject.h"

// с помощью этого абстрактного класса мне удалось реализовать полиморфизм. С помощью него создается каждый объект на экране
class BaseCreator {
public:
    // обязательный метод наследников. создает объект нужного типа
    virtual GameObject *createGameObject() const = 0;

    virtual ~BaseCreator() {};
};

// класс singleton который помогает динамически создавать объекты на экране читая про них из xml файла.
// храни в себе ссылки на объекты по id
class GameObjectFactory {
public:
    bool registerType(std::string typeID, BaseCreator *pCreator) {
        std::map<std::string, BaseCreator *>::iterator it = m_creators.find(typeID);
        if (it != m_creators.end()) {
            delete pCreator;
            return false;
        }
        m_creators[typeID] = pCreator;
        return true;
    }

    GameObject *create(std::string typeID) {
        std::map<std::string, BaseCreator *>::iterator it = m_creators.find(typeID);
        if (it == m_creators.end()) {
            std::cout << "Couldn't find type " << typeID << std::endl;
            return NULL;
        }
        BaseCreator *pCreator = (*it).second;
        return pCreator->createGameObject();
    }

    static GameObjectFactory* Instance(){
        if(!s_pInstance)
        {
            s_pInstance = new GameObjectFactory();
            return s_pInstance;
        }
        return s_pInstance;
    }

private:
    std::map<std::string, BaseCreator *> m_creators;
    static GameObjectFactory *s_pInstance;

    GameObjectFactory(){};

    ~GameObjectFactory(){};

};

typedef GameObjectFactory TheGameObjectFactory;

#endif //MYCHESSSDL2_GAMEOBJECTFACTORY_H
