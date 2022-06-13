#include "Game.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "InputHandler.h"
#include "../States/MenuState.h"
#include "../GameObjects/MenuButton.h"
#include "../States/MainMenuState.h"
#include "../GameObjects/Enemy.h"
#include "AnimatedGraphic.h"
#include "ScrollingBackground.h"
#include "../GameObjects/Turret.h"
#include "../GameObjects/Glider.h"
#include "../GameObjects/ShotGlider.h"
#include "../GameObjects/RoofTurret.h"
#include "../GameObjects/Eskeletor.h"
#include "../GameObjects/Level1Boss.h"
#include "../States/GameOverState.h"

using namespace std;

Game* Game::s_pInstance = 0;


Game::Game():
        m_pWindow(0),
        m_pRenderer(0),
        m_bRunning(false),
        m_pGameStateMachine(0),
        m_playerLives(3),
        m_scrollSpeed(0.8),
        m_bLevelComplete(false),
        m_bChangingState(false)
{
    // Добавление уровней
    m_levelFiles.push_back("assets/map1.tmx");
    m_levelFiles.push_back("assets/map2.tmx");

    // Начальный уровень
    m_currentLevel = 1;
}

Game::~Game()
{
    // При закрытии приложения обнуляем рендер и закрываем окно
    m_pRenderer= 0;
    m_pWindow = 0;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    // сохраняем ширину и высоту, чтобы в дальнейшем было удобно рисовать tilemap
    m_gameWidth = width;
    m_gameHeight = height;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // пытаемся создать окно для игры
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "SDL init success\n";
        // инициализируем окно
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        // если получилось создать окно то создаем рендер и открываем главное меню
        if(m_pWindow != 0) // window init success
        {
            cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

            if(m_pRenderer != 0) // при удачном создании рендера заливаем всё окно черным цветом
            {
                cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,255);
            }
            else
            {
                cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        cout << "SDL init fail\n";
        return false; // SDL init fail
    }

    // Загружаем музыку для игры, чтобы было комфортно и интересно играть
    TheSoundManager::Instance()->load("assets/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
    TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
    TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);

//    включаем музыку для меню
    TheSoundManager::Instance()->playMusic("music1", -1);


    // Регистрация типов. Это нужно сделать чтобы можно было создавать объекты для игры просто читая xml
    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
    TheGameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    TheGameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
    TheGameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
    TheGameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
    TheGameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
    TheGameObjectFactory::Instance()->registerType("Level1Boss", new Level1BossCreator());

    // Первое состояние - меню, из него мы выбираем что мы будем делать
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

//    флаг который поможет в дальнейшем закрыть окно
    m_bRunning = true;
    return true;
}

void Game::setCurrentLevel(int currentLevel)
{
    // меняем машину состояние переключая уровни.
    m_currentLevel = currentLevel;
    m_pGameStateMachine->changeState(new GameOverState());
    m_bLevelComplete = false;
}

// рендер всех объектов на экране
void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    // обновляем все объекты на экране, тут происходит проверка логики.
    // далее метод update спускается до самих объектов у которых тоже есть методы update.
    m_pGameStateMachine->update();

}

void Game::handleEvents()
{
    // обработчик кликов, событий
    TheInputHandler::Instance()->update();

}

void Game::clean()
{
    // метод помогает закрыть программу, тут происходит сборка муссора, засчет чего не происходит утечка памяти
    cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();

    m_pGameStateMachine->clean();

    m_pGameStateMachine = 0;
    delete m_pGameStateMachine;

    TheTextureManager::Instance()->clearTextureMap();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}


