// entity.cpp
#include "entity.h"


Entity::Entity(const sf::Image &image, float X, float Y, int W, int H, std::string Name) {

    x = X; y = Y;
    w = W; h = H;
    name = std::string(Name);
    moveTimer = 0;
    dx = 0; dy = 0;
    speed = 0;
    CurrentFrame = 0;
    health = 100;
    life = true;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

sf::FloatRect Entity::getRect() {
    sf::FloatRect FR(x, y, w, h);
    return FR;
}

