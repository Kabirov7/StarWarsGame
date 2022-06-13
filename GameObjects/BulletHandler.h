#ifndef STARWARS_BULLETHANDLER_H
#define STARWARS_BULLETHANDLER_H

#include "iostream"
#include "Bullet.h"
#include "vector"

// класс является singleton'ом, так как мы разделяем логику столкновений и отрисовку
// пули нам нужны в разных частях программы
class BulletHandler
{
public:

    static BulletHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new BulletHandler();
            return s_pInstance;
        }
        return s_pInstance;
    }

    // добавление пуль игрока
    void addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
    // добавление пуль врага
    void addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

    // обновление пуль
    void updateBullets();
    void drawBullets();

    void clearBullets();

    // getter'ы хранилищь с пулями
    const std::vector<PlayerBullet*> getPlayerBullets() { return m_playerBullets; }
    const std::vector<EnemyBullet*> getEnemyBullets() { return m_enemyBullets; }

private:

    BulletHandler();
    ~BulletHandler();

    BulletHandler(const BulletHandler&);
    BulletHandler& operator=(const BulletHandler&);

    static BulletHandler* s_pInstance;

    // хранилище пуль игрока и пули врагов
    std::vector<PlayerBullet*> m_playerBullets;
    std::vector<EnemyBullet*> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;



#endif //MYCHESSSDL2_BULLETHANDLER_H
