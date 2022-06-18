#ifndef STARWARS_ENEMY_H
#define STARWARS_ENEMY_H


#include "../GameFramework/ShooterObject.h"
#include "../GameFramework/GameObjectFactory.h"

// Абстрактный класс, от него наследуются все подклассы врагов, такие как glider, турель, боссы
class Enemy : public ShooterObject
{
public:

    virtual std::string type() { return "Enemy"; }

protected:

    int m_health;

    Enemy() : ShooterObject() {}
    virtual ~Enemy() {}
};

#endif
