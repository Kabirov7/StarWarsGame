#ifndef STARWARS_GAMEOVERSTATE_H
#define STARWARS_GAMEOVERSTATE_H


#include <vector>
#include "../GameFramework/GameState.h"
#include "../GameFramework/GameObject.h"
#include "MenuState.h"

class GameObject;

// состояния конца игры
class GameOverState : public MenuState
{
public:

    virtual ~GameOverState() {}

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_gameOverID; }

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:

    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_gameOverID;

    std::vector<GameObject*> m_gameObjects;
};

#endif
