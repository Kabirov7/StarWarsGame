#ifndef STARWARS_ESKELETOR_H
#define STARWARS_ESKELETOR_H

#include "Enemy.h"

// штука которая падает сверху и стреляет в обе стороны
class Eskeletor : public Enemy
{
public:

    virtual ~Eskeletor() {}

    Eskeletor() : Enemy()
    {
        m_dyingTime = 24;
        m_health = 1;
        m_moveSpeed = 3;
        m_bulletFiringSpeed = 50;
    }

    virtual void collision()
    {
        m_health -= 1;

        if(m_health == 0)
        {
            if(!m_bPlayedDeathSound)
            {
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
            scroll(TheGame::Instance()->getScrollSpeed());
            m_velocity.setY(m_moveSpeed);

            if(m_bulletCounter == m_bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-3, 0));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(3, 0));
                m_bulletCounter = 0;
            }
            m_bulletCounter++;

        }
        else
        {
            m_velocity.setY(0);
            doDyingAnimation();
        }

        ShooterObject::update();
    }
};

class EskeletorCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Eskeletor();
    }
};


#endif
