#include "ShooterObject.h"
#include "TextureManager.h"
#include "Game.h"

ShooterObject::ShooterObject() :    GameObject(),
                                    m_bulletFiringSpeed(0),
                                    m_bulletCounter(0),
                                    m_moveSpeed(0),
                                    m_dyingTime(0),
                                    m_dyingCounter(0),
                                    m_bPlayedDeathSound(false)
{
}

void ShooterObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
    // задаем позиции объекта
    m_position = Vector2D(pParams->getX(),pParams->getY());

    // задаем свойства для отрисовки объекта
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
}

// рисуем объект на экране
void ShooterObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
                                          m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

// добавляем ускорение к нашей позиции
void ShooterObject::update()
{
    m_position += m_velocity;
    m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
}

void ShooterObject::doDyingAnimation()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));

    if(m_dyingCounter == m_dyingTime)
    {
        m_bDead = true;
    }
    m_dyingCounter++;
}