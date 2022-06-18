#ifndef STARWARS_MENUBUTTON_H
#define STARWARS_MENUBUTTON_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"

// С помощью этого класса создаются все кнопки в игре. класс всегда имеет одну функцию которая сробатывает при нажатии
class MenuButton : public ShooterObject
{
public:

    MenuButton();

    virtual ~MenuButton() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    void setCallback(void(*callback)()) { m_callback = callback;}
    int getCallbackID() { return m_callbackID; }

private:

    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    bool m_bReleased;

    int m_callbackID;

    void (*m_callback)();
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};

#endif
