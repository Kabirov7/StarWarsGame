#include "ObjectLayer.h"
#include "../GameFramework/Game.h"
#include "Level.h"

// удаляем все объекты которые были использованы этим слоем
ObjectLayer::~ObjectLayer()
{
    for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)// < m_gameObjects.size(); i++)
    {
        delete (*it);
    }
    m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
    // у нас есть 4 основных случая когда может произойти столкновения
    // 1. пули врага попали в игрока
    m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
    // 2. пули игрока попали во врага
    m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
    // 3. игрок столкнулся с врагом
    m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);

    // 4. игрок врезался в карту
    if(pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
    {
        m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
    }

    // перебираем все объекты карты
    if(!m_gameObjects.empty())
    {
        for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)// < m_gameObjects.size(); i++)
        {
            // проверяем является ли объект нужным для нас, то есть он находиится на нужной для нас позиции, если да то обновляем
            if((*it)->getPosition().getX() <= TheGame::Instance()->getGameWidth())
            {
                (*it)->setUpdating(true);
                (*it)->update();
            }
            else
            {
                // обновляем игрока
                if((*it)->type() != std::string("Player"))
                {
                    (*it)->setUpdating(false);
                    (*it)->scroll(TheGame::Instance()->getScrollSpeed());
                }
                else
                {
                    // обновляем остальные объекты
                    (*it)->update();
                }
            }

            // проверяем не убили ли игрока
            if((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheGame::Instance()->getGameHeight()) || ((*it)->dead()))
            {
                delete * it;
                it = m_gameObjects.erase(it); // удаляем итератор и меняем его
            }
            else
            {
                ++it; // увеличиваем итератор если всё хорошо
            }

        }
    }
}

void ObjectLayer::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        if(m_gameObjects[i]->getPosition().getX() <= TheGame::Instance()->getGameWidth())
        {
            m_gameObjects[i]->draw();
        }
    }
}