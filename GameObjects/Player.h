#ifndef STARWARS_PLAYER_H
#define STARWARS_PLAYER_H


#include "../GameFramework/GameObject.h"
#include "../GameFramework/ShooterObject.h"
#include "../GameFramework/GameObjectFactory.h"

class Player : public ShooterObject
{
public:

    Player();
    virtual ~Player() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void collision();

    virtual std::string type() { return "Player"; }

private:

    // возродить игрока если остались жизни
    void ressurect();

    // обработка нажатий с клавиатуры или мыши
    void handleInput();

    // обработка анимации в зависимости от состояния объекта
    void handleAnimation();

    // игрок при возраждении неуязвим
    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

// для фабрики объектов
class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif
