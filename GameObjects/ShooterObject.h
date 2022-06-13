#ifndef STARWARS_SHOOTEROBJECT_H
#define STARWARS_SHOOTEROBJECT_H


#include "../GameFramework/GameObject.h"
#include "../GameFramework/Vector2D.h"

class ShooterObject : public GameObject
{
public:

    virtual ~ShooterObject() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    virtual void draw();
    virtual void update();

    virtual void clean() {}
    virtual void collision() {}

    virtual std::string type() { return "SDLGameObject"; }

protected:

    ShooterObject();

    void doDyingAnimation();

    // свойста для пуль
    int m_bulletFiringSpeed;
    int m_bulletCounter;
    int m_moveSpeed;

    // как долго будет умирать объект
    int m_dyingTime;
    int m_dyingCounter;

    // чтобы проигрывать взрыв только один раз
    bool m_bPlayedDeathSound;
};

#endif
