#include "PauseState.h"
#include "MenuState.h"
#include "../GameFramework/MenuButton.h"
#include "../GameFramework/LoaderParams.h"
#include "MainMenuState.h"
#include "../GameFramework/StateParser.h"
#include "../GameFramework/InputHandler.h"

const std::string PauseState::s_pauseID = "PAUSE";

// функция для кнопки вернуться в главное меню, она убирает состояние паузы и добовляет состояние главного меню
void PauseState::s_pauseToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

// для кнопки продолжить, просто убирается верхнее состояни из машины состояний
void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

// обновление всех объектов состояния
void PauseState::update()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
}

// отрисовка всех объектов состояния
void PauseState::render()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

// при входе в состояние парсим информацию из файла, добавляем функции для кнопок
bool PauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    m_loadingComplete = true;

    std::cout << "entering PauseState\n";
    return true;
}

// при выходе из состояния удаляем все объекты из памяти
bool PauseState::onExit()
{
    if(m_loadingComplete && !m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->clean();
            delete m_gameObjects[i];
        }
        m_gameObjects.clear();
    }
    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    TheInputHandler::Instance()->reset();

    std::cout << "exiting PauseState\n";
    return true;
}

// установка функция для кнопок
void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // пробегаемся через все функции и задаем для каждой кнопки нужную функцию
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            // если объект типа MenuButton тогда даем ей нужную функцию
            if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
            {
                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}

