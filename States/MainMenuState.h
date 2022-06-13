#ifndef STARWARS_MAINMENUSTATE_H
#define STARWARS_MAINMENUSTATE_H

#include <vector>
#include "../GameFramework/GameState.h"
#include "../GameFramework/GameObject.h"
#include "../GameFramework/TextureManager.h"
#include "MenuState.h"

// класс для главного меню
class MainMenuState : public MenuState
{
public:

    virtual ~MainMenuState() {}

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_menuID; }

private:

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    // функции для кнопок
    static void s_menuToPlay();
    static void s_exitFromMenu();

    static const std::string s_menuID;

    std::vector<GameObject*> m_gameObjects;
};

#endif
