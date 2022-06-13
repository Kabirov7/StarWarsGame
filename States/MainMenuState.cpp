#include "MainMenuState.h"
#include <iostream>
#include "../GameFramework/Game.h"
#include "../GameObjects/MenuButton.h"
#include "PlayState.h"
#include "../GameFramework/StateParser.h"
#include "../GameFramework/InputHandler.h"

const std::string MainMenuState::s_menuID = "MENU";

// функции для кнопки
void MainMenuState::s_menuToPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}

void MainMenuState::update()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        s_menuToPlay();
    }
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            if(m_gameObjects[i] != 0)
            {
                m_gameObjects[i]->update();
            }
        }
    }
}

void MainMenuState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool MainMenuState::onEnter()
{
    // парсим состояние
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_menuID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    // устанавливаем функции
    setCallbacks(m_callbacks);

    m_loadingComplete = true;
    std::cout << "entering MenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    m_exiting = true;

    // удаляем объекты из памяти
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }

    m_gameObjects.clear();


    TheInputHandler::Instance()->reset();

    std::cout << "exiting MenuState\n";
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // пробигаемся по всем функциям и ставим функции нужным кнопкам
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
            {
                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}
