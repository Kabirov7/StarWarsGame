#ifndef STARWARS_GAMESTATEMACHINE_H
#define STARWARS_GAMESTATEMACHINE_H


#include <vector>
#include "GameState.h"

// Класс с работает с состояниями(переключает, добавляет, удаляет)
class GameStateMachine
{
public:

    GameStateMachine() {}
    ~GameStateMachine() {}

//    update и render обновляет объекты текущего состояния
    void update();
    void render();

    // добавляет состояние
    void pushState(GameState* pState);
    // меняет состояние
    void changeState(GameState* pState);
    // удаляет последнее состояние
    void popState();

    void clean();

    std::vector<GameState*>& getGameStates() { return m_gameStates; }

private:
    // храни в себе состояния
    std::vector<GameState*> m_gameStates;
};
#endif
