#ifndef STARWARS_TILELAYER_H
#define STARWARS_TILELAYER_H

#include <vector>
#include "Layer.h"
#include "../GameFramework/Vector2D.h"
#include "Level.h"

// TileLayer нужен для хранения информации про Tileset'ы
// с помощью него можно воспользоваться считанным тайло, взять его или отрисовать какой-нибудь блок
class TileLayer : public Layer
{
public:

    // конструктор TileLayer, получает tileSize и все считанные тайлсеты
    TileLayer(int tileSize, const std::vector<Tileset>& tilesets);

    virtual ~TileLayer() {}

    // обновление тайла по уровню
    virtual void update(Level* pLevel);
    // отрисовка тайла
    virtual void render();

    // задаем айди тайлсетов
    void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }
    // устанавливаем размер тайлов
    void setTileSize(int tileSize) { m_tileSize = tileSize; }
    // установка ширины карты
    void setMapWidth(int mapWidth) { m_mapWidth = mapWidth; }

    // геттеры
    int getTileSize() { return m_tileSize; }

    const std::vector<std::vector<int>>& getTileIDs() { return m_tileIDs; }

    Tileset getTilesetByID(int tileID);

    const Vector2D getPosition() { return m_position; }

private:

    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    int m_mapWidth;

    Vector2D m_position;
    Vector2D m_velocity;

    const std::vector<Tileset>& m_tilesets;

    std::vector<std::vector<int>> m_tileIDs;
};

#endif
