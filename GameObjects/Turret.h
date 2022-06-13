#ifndef STARWARS_TURRET_H
#define STARWARS_TURRET_H

#include <iostream>
#include "../GameFramework/GameObjectFactory.h"
#include "BulletHandler.h"
#include "../GameFramework/SoundManager.h"
#include <math.h>
#include "Enemy.h"

// класс Туррели
class Turret : public Enemy
{
public:
    
    Turret()
    {
        m_dyingTime = 100;
        m_health = 12;
        m_bulletFiringSpeed = 50;
    }
    
    virtual ~Turret() {}

    virtual void collision()
    {
        m_health -= 1;
        
        if(m_health == 0)
        {
            if(!m_bPlayedDeathSound)
            {

                m_position.setX(m_position.getX() + 10);
                m_position.setY(m_position.getY() - 10);
                TheSoundManager::Instance()->playSound("explode", 0);
                
                m_textureID = "largeexplosion";
                m_currentFrame = 0;
                m_numFrames = 12;
                m_width = 50;
                m_height = 60;
                m_bDying = true;
            }
            
        }
    }
    
    virtual void update()
    {
        if(!m_bDying)
        {
            // движение объекта вместе с остальными объектами
            scroll(TheGame::Instance()->getScrollSpeed());
            
            if(m_bulletCounter == m_bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet2", 1, Vector2D(-3, -3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(3, -3));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
        }
        else
        {
            // прокрутка вмесе с картой
            scroll(TheGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
        
    }

};

// класс для фабрики объектов
class TurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Turret();
    }
};


#endif
