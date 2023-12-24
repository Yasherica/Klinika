// Bullet.h
#ifndef BULLET
#define BULLET

#include "entity.h"

class Bullet : public Entity {
public:
    int direction;  // Объявление переменной direction внутри класса Bullet

    Bullet(Image &image, float X, float Y, int W, int H, string Name, int dir);

    void update(float time);
};

#endif // BULLET
