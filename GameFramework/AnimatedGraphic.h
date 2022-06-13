#ifndef STARWARS_ANIMATEDGRAPHIC_H
#define STARWARS_ANIMATEDGRAPHIC_H


#include "LoaderParams.h"
#include "../GameObjects/ShooterObject.h"
#include "GameObjectFactory.h"

// класс нужен чтобы было удобно рисовать всякие надписи под типу game over при неудачном прохождении игры
class AnimatedGraphic : public ShooterObject
{
public:

    AnimatedGraphic();
    virtual ~AnimatedGraphic() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    int m_animSpeed;
    int m_frameCount;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif
