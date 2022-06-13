#ifndef STARWARS_GAMEOBJECT_H
#define STARWARS_GAMEOBJECT_H


#include <iostream>
#include "SDL.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject
{
public:

    // виртуальный деструктор абстрактного класса
    virtual ~GameObject() {}

    // загрузка объекта из файла
    virtual void load(std::unique_ptr<LoaderParams> const &pParams)=0;

    // отрисовка объекта
    virtual void draw()=0;

    // обновление состояния объекта
    virtual void update()=0;

    // удаление объекта
    virtual void clean()=0;

    // функция при коллизии объекта
    virtual void collision() = 0;

    // получение типа объекта
    virtual std::string type() = 0;

    // Геттеры состояния объекта
    Vector2D& getPosition() { return m_position; }
    Vector2D& getVelocity() { return m_velocity; }

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }

    // прокрутка объекта вместе с картой
    void scroll(float scrollSpeed)
    {
        if(type() != std::string("Player")) // игрок никогда не прокручивается
        {
            m_position.setX(m_position.getX() - scrollSpeed);
        }
    }

    // обновляется ли объект в настоящее время
    bool updating() { return m_bUpdating; }

    // умер ли объект
    bool dead() { return m_bDead; }

    // объект умирает и работает анимация смерти
    bool dying() { return m_bDying; }

    // сеттер обновления объекта, с помощью него мы понимает стоит ли обновлять наш объект
    void setUpdating(bool updating) { m_bUpdating = updating; }

protected:

    // конструктор с дефолтными значениями
    GameObject() :  m_position(0,0),
                    m_velocity(0,0),
                    m_acceleration(0,0),
                    m_width(0),
                    m_height(0),
                    m_currentRow(0),
                    m_currentFrame(0),
                    m_bUpdating(false),
                    m_bDead(false),
                    m_bDying(false),
                    m_angle(0),
                    m_alpha(255)
    {
    }

    // переменные нужные для движения
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    // свойтсва объекта, ширина и высота, для вывода на экран
    int m_width;
    int m_height;

    // переменные нужные для отрисовки объекта, будь то sprite sheet, или же просто одна картинка
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;

    // переменные для граматной анимации, смерти или же обычного движения
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;

    double m_angle;

    // для затухания
    int m_alpha;
};


#endif
