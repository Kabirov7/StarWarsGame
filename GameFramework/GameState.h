#ifndef STARWARS_GAMESTATE_H
#define STARWARS_GAMESTATE_H

#include <string>
#include <vector>

// абстрактный класс любого состояния.
// с помощью него удобно рендерить и обновлять объекты на экране.
class GameState
{
public:

    virtual ~GameState() {}

    // обновляет состояния объектов
    virtual void update() = 0;
    // отрисовывает объекты на экране
    virtual void render() = 0;

    // определяет данные при создании нового состояния
    virtual bool onEnter() = 0;
    // очищает все использованные данные в состоянии с помощью m_textureIDList
    virtual bool onExit() = 0;
    // метод используется в состояниях в которых надо сохранить результаты, если состояние не сменилось а добавилось сверху
    virtual void resume() {}

    virtual std::string getStateID() const = 0;

protected:

    GameState() : m_loadingComplete(false), m_exiting(false)
    {

    }

    bool m_loadingComplete;
    bool m_exiting;

    std::vector<std::string> m_textureIDList;
};

#endif
