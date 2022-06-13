
// Файл описывает оружие для игрока и пришельцев
#ifndef STARWARS_BULLET_H
#define STARWARS_BULLET_H

#include "ShooterObject.h"

class PlayerBullet : public ShooterObject
{
public:
    PlayerBullet() : ShooterObject(), m_heading(0,0)
    {
        m_dyingTime = 5;
    }

    virtual ~PlayerBullet() {}

    virtual std::string type() { return "PlayerBullet"; }

    virtual void load(std::unique_ptr<LoaderParams> pParams, Vector2D heading)
    {
        ShooterObject::load(std::move(pParams));
        // скорость движения пули
        m_heading = heading;
    }



    virtual void draw()
    {
        // так как класс не несет особой логики, можно использовать просто метод родительского класса
        ShooterObject::draw();
    }

    virtual void collision()
    {
        m_textureID = "smallexplosion";
        m_currentFrame = 0;
        m_numFrames = 2;
        m_width = 20;
        m_height = 20;
        m_bDying = true;
    }

    virtual void update()
    {
        // если объект не убили то обновляем его как обычно
        if(!m_bDying)
        {
            m_velocity.setX(m_heading.getX());
            m_velocity.setY(m_heading.getY());

            ShooterObject::update();
        }
        else // иначе показываем что объект умер
        {
            m_velocity.setX(0);
            m_velocity.setY(0);
            doDyingAnimation();
        }
    }

    virtual void clean()
    {
        ShooterObject::clean();
    }

private:

    Vector2D m_heading;
};

class EnemyBullet : public PlayerBullet
{
public:
    EnemyBullet() : PlayerBullet()
    {
    }

    virtual ~EnemyBullet() {}

    virtual std::string type() { return "EnemyBullet"; }
};

#endif
