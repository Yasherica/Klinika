#ifndef ENEMY
#define ENEMY
#include "entity.h"

//КЛАСС ВРАГА
class Enemy :public Entity{
public:
int direction;//направление движения врага

Enemy(Image &image, float X, float Y, int W, int H, string Name);

void checkCollisionWithMap(float Dx, float Dy);//ф-ция проверки столкновений с картой

void update(float time);
};//класс Enemy закрыт

#endif // ENEMY
