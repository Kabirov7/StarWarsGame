#ifndef STARWARS_PLAYSTATE_H
#define STARWARS_PLAYSTATE_H


#include <vector>
#include "../GameFramework/GameState.h"
#include "../GameFramework/GameObject.h"
#include "../GameFramework/Game.h"
#include "../Levels/Level.h"

// наследуемся от абстрактного класса состояния и создаем состояние игры
class PlayState : public GameState {
public:
    // обновление состояния
    virtual void update();

    // отрисовка состояния
    virtual void render();

    // что будет происходить при включении этого состояния
    virtual bool onEnter();

    // что будет происходить при выходе из этого состояния
    virtual bool onExit();

    virtual std::string getStateID() const { return s_playID; }

private:
    // ID состояния игры
    static const std::string s_playID;

    // все объекты используемые в этом состоянии
    std::vector<GameObject *> m_gameObjects;
    // Текущий уровень
    Level *pLevel;
};

#endif
