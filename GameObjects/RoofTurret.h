#ifndef STARWARS_ROOFTURRET_H
#define STARWARS_ROOFTURRET_H

// класс башенной туррели
class RoofTurret : public Turret
{
public:

    virtual ~RoofTurret() {}

    virtual void draw()
    {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
                                              m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_VERTICAL);
    }

    virtual void update()
    {
        if(!m_bDying)
        {
            // мы хотим чтобы этот объект прокручивался вместе с картой
            scroll(TheGame::Instance()->getScrollSpeed());

            if(m_bulletCounter == m_bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-3, 3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(0, 3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(3, 3));
                m_bulletCounter = 0;
            }

            m_bulletCounter++;
        }
        else
        {
            scroll(TheGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
    }
};

class RoofTurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new RoofTurret();
    }
};

#endif
