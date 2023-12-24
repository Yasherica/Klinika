#ifndef ENTITY
#define ENTITY
#include "base.h"

#include <windows.h>

class Entity {
public:
enum { left, right, up, down, stay} state;// тип перечисления - состояние объекта

float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей

int w, h, health; //переменная “health”, хранящая жизни игрока

bool life; //переменная “life” жизнь, логическая

Texture texture;//сфмл текстура
Sprite sprite;//сфмл спрайт

float CurrentFrame;//хранит текущий кадр

Entity(Image &image, float X, float Y, int W, int H, string Name); //конструктор

FloatRect getRect();

string name;//враги могут быть разные, врагов можно различать по именам
//каждому можно дать свое действие в update() в зависимости от имени


virtual void update(float time) = 0;


std::string TileMap[HEIGHT_MAP] = {
    "0000000000000000000000000000000000000000",
    "0                                      0",
    "0      0000000           0000000       0",
    "0      0     0           0  s  0       0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0                                      0",
    "0      0     0           0     0       0",
    "0      0000000           0000000       0",
    "0                                      0",
    "0000000000000000000000000000000000000000",

};
};
#endif // ENTITY

