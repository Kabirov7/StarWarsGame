#ifndef STARWARS_MENUSTATE_H
#define STARWARS_MENUSTATE_H


#include <vector>
#include "../GameFramework/GameState.h"
#include "../GameFramework/GameObject.h"
#include "../GameFramework/TextureManager.h"

// абстрактный класс который подразумевает что в состоянии есть кнопки
class MenuState : public GameState
{
public:

    virtual ~MenuState() {}

protected:

    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};



#endif
