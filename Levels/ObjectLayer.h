#ifndef STARWARS_OBJECTLAYER_H
#define STARWARS_OBJECTLAYER_H


#include "Layer.h"
#include "iostream"
#include "vector"
#include "../GameFramework/GameObject.h"
#include "../GameFramework/CollisionManager.h"

class GameObject;

class ObjectLayer : public Layer
{
public:

    virtual ~ObjectLayer();

    // передаем уровень для анализа объектов на экране
    virtual void update(Level* pLevel);
    virtual void render();

    // возвращает указатель на объекты этого слоя, LevelParser затем будет добавлять объекты сюда
    std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:

    // Проверяет на коллизию объекты слоя
    CollisionManager m_collisionManager;

    // массив объектов игры
    std::vector<GameObject*> m_gameObjects;
};

#endif
