#ifndef STARWARS_INPUTHANDLER_H
#define STARWARS_INPUTHANDLER_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "Vector2D.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

// Singleton обрабатывает ввод с клавиатуры и мышки
class InputHandler
{
public:

    static InputHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new InputHandler();
        }

        return s_pInstance;
    }

    void reset();

    // обновляет и очищает сохраненные нажатые клавиши
    void update();
    void clean();

    // проверяет была ли нажата определенная клавиша клавиатуры
    bool isKeyDown(SDL_Scancode key) const;

    // получает клики мышки
    bool getMouseButtonState(int buttonNumber) const;
    // возвращает позицию мыши
    Vector2D* getMousePosition() const;

private:

    InputHandler();
    ~InputHandler();

    InputHandler(const InputHandler&);
    InputHandler& operator=(const InputHandler&);

    // Приватные методы

    // обработка клавиатуры
    void onKeyDown();
    void onKeyUp();

    // обработка мыши
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    // клавиатура
    const Uint8* m_keystates;

    // мышка
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;

    // singleton
    static InputHandler* s_pInstance;
};
typedef InputHandler TheInputHandler;


#endif