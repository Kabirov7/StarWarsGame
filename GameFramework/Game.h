#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "iostream"
#include "TextureManager.h"
#include "GameObject.h"
#include "../GameObjects/Player.h"
#include "GameStateMachine.h"

#ifndef STARWARS_GAME_H
#define STARWARS_GAME_H

// Класс является singleton'ом, он один на всю программу
class Game
{
public:

//    с помощью этого метода реализуется подход singleton
    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }

    // инициализация игры
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    // отрисовка всех объектов игры
    void render();
    // обновление характеристик всех объектов игры
    void update();
    // обработчик событий
    void handleEvents();
    // закрывает игру
    void clean();

    // геттеры и сеттеры
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }
    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

    void setPlayerLives(int lives) { m_playerLives = lives; }
    int getPlayerLives() { return m_playerLives; }

    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel() { return m_currentLevel; }

    void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
    const int getNextLevel() { return m_nextLevel; }

    void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
    const bool getLevelComplete() { return m_bLevelComplete; }

    bool running() { return m_bRunning; }

    void quit() { m_bRunning = false; }

    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }
    float getScrollSpeed() { return m_scrollSpeed; }

    bool changingState() { return m_bChangingState; }
    void changingState(bool cs) { m_bChangingState = cs; }

    std::vector<std::string> getLevelFiles() { return m_levelFiles; }

private:
    bool m_bChangingState;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    GameStateMachine* m_pGameStateMachine;

    bool m_bRunning;

    static Game* s_pInstance;

    int m_gameWidth;
    int m_gameHeight;
    float m_scrollSpeed;

    int m_playerLives;

    int m_currentLevel;
    int m_nextLevel;
    bool m_bLevelComplete;

    std::vector<std::string> m_levelFiles;

    Game();
    ~Game();

    Game(const Game&);
    Game& operator=(const Game&);
};

typedef Game TheGame;

#endif