// entity.h
#ifndef ENTITY
#define ENTITY

#include "base.h"
#include <windows.h>
#include <SFML/Graphics.hpp>

class Entity {
public:
    enum { left, right, up, down, stay } state;
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life;
    sf::Texture texture;
    sf::Sprite sprite;
    float CurrentFrame;

    Entity(const sf::Image &image = sf::Image(), float X = 0, float Y = 0, int W = 0, int H = 0, std::string Name = "");

    sf::FloatRect getRect();

    std::string name;

    virtual void update(float time);

    std::string TileMap[HEIGHT_MAP];

};

#endif // ENTITY
