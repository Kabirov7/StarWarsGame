#ifndef STARWARS_LEVELPARSER_H
#define STARWARS_LEVELPARSER_H


#include "../Levels/Level.h"
#include "../xmlparsing/tinyxml.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;

// Парсер xml для уровней игры
class LevelParser
{
public:

    // парсит сам файл, из него вызывают отдельные функции которые парсят определенные тэги xml файла
    Level* parseLevel(const char* stateFile);

private:

    // парсит текстуры(изображения)
    void parseTextures(TiXmlElement* pTextureRoot);
    // парсит tileset который нужен для отрисовки карты
    void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    // парсит объекты и их характеристики
    void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);
    //  парсит саму карту
    void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);

    int m_tileSize;
    int m_width;
    int m_height;
};

#endif
