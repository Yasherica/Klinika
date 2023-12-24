// enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "bullet.h"

class Enemy : public Entity {
public:
    Enemy(sf::Image &image, float X, float Y, int W, int H, std::string Name);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
    void shoot(float time);
    void updateBullets(float time);

    static sf::Image image;  // Сделали статической

private:
    std::vector<Bullet*> bullets;
    int direction;
};

#endif // ENEMY_H
