#include <iostream>
#include "PlayState.h"
#include "../GameFramework/InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "../GameFramework/LevelParser.h"
#include "../GameObjects/BulletHandler.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    // проверяем жив ли наш игрок, нажата ли клавиша escape
    if(m_loadingComplete && !m_exiting)
    {
        // если нажата клавиша escape - поверх текущего состояния добавляем состояние паузы
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
        }

        // обновляем пули
        TheBulletHandler::Instance()->updateBullets();

        if(TheGame::Instance()->getPlayerLives() == 0)
        {
            // если игрок исчерпал все свои жизни то выводим состояние GameOver
            TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
        }

        if(pLevel != 0)
        {
            // иначе обновляем всё что есть на экране
            pLevel->update();
        }
    }
}

// отрисовываем все объекты на экране
void PlayState::render()
{
    if(m_loadingComplete)
    {
        if(pLevel != 0)
        {
            pLevel->render();
        }

        for(int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
        {
            TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
        }

        TheBulletHandler::Instance()->drawBullets();
    }
}

bool PlayState::onEnter()
{
    // инициализируем игрока с 3 жизнями
    TheGame::Instance()->setPlayerLives(3);

    // начинаем парсить уровень
    LevelParser levelParser;
    pLevel = levelParser.parseLevel(TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());

    // добавляем в TextureManager картинки для пуль
    TheTextureManager::Instance()->load("assets/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/lives.png", "lives", TheGame::Instance()->getRenderer());

    if(pLevel != 0)
    {
        m_loadingComplete = true;
    }

    std::cout << "entering PlayState\n";
    return true;
}

// при выходе из состояния удаляем все объекты
bool PlayState::onExit()
{
    m_exiting = true;

    TheInputHandler::Instance()->reset();
    TheBulletHandler::Instance()->clearBullets();

    std::cout << "exiting PlayState\n";
    return true;
}
