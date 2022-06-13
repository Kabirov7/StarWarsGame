#ifndef STARWARS_LEVEL_H
#define STARWARS_LEVEL_H

#include <vector>
#include "iostream"
#include "Layer.h"
#include "../GameObjects/Player.h"

class TileLayer;

// структура помогает хранить характеристики тайла чтобы правильно рисовать карту
struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

// класс Уровень, позволяет грамотно организовать работу всех объектов на карте, каждый уровень создается на основе этого класса
class Level
{
public:

    ~Level();

    void update();
    void render();

    std::vector<Tileset>* getTilesets() { return &m_tilesets; }
    std::vector<Layer*>* getLayers() { return &m_layers; }
    std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }

    const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }

    Player* getPlayer() { return m_pPlayer; }
    void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:

    friend class LevelParser;

    Level();

    Player* m_pPlayer;

    std::vector<Layer*> m_layers;
    std::vector<Tileset> m_tilesets;
    std::vector<TileLayer*> m_collisionLayers;
};

#endif
