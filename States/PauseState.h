#ifndef STARWARS_PAUSESTATE_H
#define STARWARS_PAUSESTATE_H


#include "../GameFramework/Game.h"
#include "../GameFramework/GameState.h"
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:

    virtual ~PauseState() {}

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_pauseID; }

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:

    // функции для кнопок
    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;

    std::vector<GameObject*> m_gameObjects;
};

#endif