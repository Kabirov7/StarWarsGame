#include "GameOverState.h"
#include "../GameFramework/InputHandler.h"
#include "../GameFramework/Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "../GameFramework/MenuButton.h"
#include "../GameFramework/StateParser.h"
#include "MainMenuState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

// функции для кнопок
void GameOverState::s_gameOverToMain() {
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

// начало новой игры
void GameOverState::s_restartPlay() {
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

// обновление всех объектов состояния
void GameOverState::update() {
    if (m_loadingComplete && !m_gameObjects.empty()) {
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->update();
        }
    }
}

// отрисовка объектов состояния
void GameOverState::render() {
    if (m_loadingComplete && !m_gameObjects.empty()) {
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
    }
}

bool GameOverState::onEnter() {
    // парсим нужное состояние
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

    // устанавливаем функции
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    m_loadingComplete = true;

    std::cout << "entering GameOverState\n";
    return true;
}

// удалаяем все объекты состояния
bool GameOverState::onExit() {
    if (m_loadingComplete && !m_gameObjects.empty()) {
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->clean();
            delete m_gameObjects[i];
        }

        m_gameObjects.clear();
    }

    std::cout << m_gameObjects.size();

    for (int i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    TheInputHandler::Instance()->reset();

    std::cout << "exiting GameOverState\n";
    return true;
}

// устанавливаем функции по id
void GameOverState::setCallbacks(const std::vector<Callback> &callbacks) {
    // ищем кнопки и задаем им функции
    for (int i = 0; i < m_gameObjects.size(); i++) {
        if (dynamic_cast<MenuButton *>(m_gameObjects[i])) {
            MenuButton *pButton = dynamic_cast<MenuButton *>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}
