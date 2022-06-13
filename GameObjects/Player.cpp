#include "Player.h"
#include "../GameFramework/InputHandler.h"
#include "../GameFramework/SoundManager.h"
#include "../GameObjects/BulletHandler.h"
#include "../GameFramework/Game.h"

using namespace std;

Player::Player() : ShooterObject(),
                   m_invulnerable(false),
                   m_invulnerableTime(200),
                   m_invulnerableCounter(0) {
}

void Player::collision() {
    // если игрок уязвим ты мы меняем его значения для анимации смерти
    // if the player is not invulnerable then set to dying and change values for death animation tile sheet
    if (!m_invulnerable && !TheGame::Instance()->getLevelComplete()) {
        m_textureID = "largeexplosion";
        m_currentFrame = 2;
        m_numFrames = 12;
        m_width = 50;
        m_height = 60;
        m_bDying = true;
    }
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams) {
    // унаследованная функция загрузки объекта
    ShooterObject::load(std::move(pParams));

    // настройка пуль
    m_bulletFiringSpeed = 13;
    m_moveSpeed = 4;

    // позволяет стрелять мгновенно
    m_bulletCounter = m_bulletFiringSpeed;

    // время для смерти объекта
    m_dyingTime = 50;
}

void Player::draw() {
    ShooterObject::draw();
}

void Player::handleAnimation() {
    // если игрок уязвим мы можем менять его альфа канал тем самым нам будет казаться мигание объекта
    if (m_invulnerable) {
        // когда игрок загрузился мы меняем его значения на изначальные
        if (m_invulnerableCounter == m_invulnerableTime) {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        } else // иначе мы заставляем объект мигать
        {
            if (m_alpha == 255) {
                m_alpha = 0;
            } else {
                m_alpha = 255;
            }
        }

        // увеличиваем счетчик загрузки
        m_invulnerableCounter++;
    }

    // если игрок не мертв мы меняем его углы, в зависимости от клавиши
    if (!m_bDead) {
        if (m_velocity.getX() < 0) {
            m_angle = -5.0;
        } else if (m_velocity.getX() > 0) {
            m_angle = 5.0;
        } else {
            m_angle = 0.0;
        }
    }

    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::update() {
    if (TheGame::Instance()->getLevelComplete()) {
        if (m_position.getX() >= TheGame::Instance()->getGameWidth()) {
            TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
        } else {
            m_velocity.setY(0);
            m_velocity.setX(3);
            ShooterObject::update();
            handleAnimation();
        }
    } else {
        // если объект не умер то обновляем его как обычно
        if (!m_bDying) {
            // меняем значения, чтобы объект перестал двигаться после того как мы отпустили клавишу
            m_velocity.setX(0);
            m_velocity.setY(0);

            // обрабатываем входные данные
            handleInput();

            // меняем позицию
            ShooterObject::update();

            // делаем анимацию
            handleAnimation();
        } else // если игрок умер то...
        {
            m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));

            // если анимация смерти закончилась возвращаем его на изначальную позицию
            if (m_dyingCounter == m_dyingTime) {
                ressurect();
            }
            m_dyingCounter++;
        }
    }
}

void Player::ressurect() {
    TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);

    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;

    m_textureID = "player";

    m_currentFrame = 0;
    m_numFrames = 4;
    m_width = 60;
    m_height = 40;

    m_dyingCounter = 0;
    m_invulnerable = true;
}

void Player::clean() {
    ShooterObject::clean();
}

void Player::handleInput() {
    if (!m_bDead) {
        // обработка клавиш
        if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ||
             TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) && m_position.getY() > 0) {
            m_velocity.setY(-m_moveSpeed);
        } else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) ||
                    TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) &&
                   (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10) {
            m_velocity.setY(m_moveSpeed);
        }

        if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) ||
             TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) && m_position.getX() > 0) {
            m_velocity.setX(-m_moveSpeed);
        } else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) ||
                    TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) &&
                   (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth()) {
            m_velocity.setX(m_moveSpeed);
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) ||
            TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
            if (m_bulletCounter == m_bulletFiringSpeed) {
                TheSoundManager::Instance()->playSound("shoot", 0);
                TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11,
                                                              "bullet1", 1, Vector2D(10, 0));
                m_bulletCounter = 0;
            }

            m_bulletCounter++;
        } else {
            m_bulletCounter = m_bulletFiringSpeed;
        }

    }
}