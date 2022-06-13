#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
    // удаляет каждый слой
    for(int i = 0; i < m_layers.size(); i++)
    {
        delete m_layers[i];
    }

    m_layers.clear();
}

void Level::render()
{
    // отрисовывает каждый слой
    for(int i = 0; i < m_layers.size(); i++)
    {
        m_layers[i]->render();
    }
}

void Level::update()
{

    // обновляет каждый слой
    for(int i = 0; i < m_layers.size(); i++)
    {
        m_layers[i]->update(this);
    }
}