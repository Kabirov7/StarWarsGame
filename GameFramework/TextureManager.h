#ifndef STARWARS_TEXTUREMANAGER_H
#define STARWARS_TEXTUREMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"

// класс singleton помогает из любой точки программы воспользоваться текстурами которые мы загрузили из xml файлов
class TextureManager
{
public:

    static TextureManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }

        return s_pInstance;
    }

    // загрузка и добавление текстуры в игру для дальнейшего использования
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    // очистка выделенной памяти под текстуры
    void clearTextureMap();
    // удаляем текстуру по id из хранилища текстур
    void clearFromTextureMap(std::string id);

    // отрисовка объекта
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // отрисовка фрэйма
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // отрисовка карты
    void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);

    // получаем весь список текстур
    std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }

private:

    TextureManager() {}
    ~TextureManager() {}

    TextureManager(const TextureManager&);
    TextureManager& operator=(const TextureManager&);

    std::map<std::string, SDL_Texture*> m_textureMap;

    static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;

#endif
