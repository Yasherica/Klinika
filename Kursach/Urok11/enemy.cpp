// enemy.cpp
#include "enemy.h"


using namespace sf;

std::list<Entity*>::iterator it;  // Определите итератор
std::list<Entity*> enemies;       // Определите коллекцию enemies
std::list<Entity*> Bullets;       // Определите коллекцию Bullets
sf::RenderWindow window;

sf::Image Enemy::image;  // Определение статической переменной

Enemy::Enemy(Image &image, float X, float Y, int W, int H, string Name) : Entity(image, X, Y, W, H, Name) {
    // Инициализация врага
    if (name == "EasyEnemy") {
        sprite.setTextureRect(IntRect(0, 0, w, h));
        direction = rand() % 4;
        speed = 0.1;
        dx = speed;
        bullets = vector<Bullet*>();
    }
    // Дополнительная инициализация в зависимости от типа врага (например, для других типов врагов)
    // ...
}
void Enemy::checkCollisionWithMap(float Dx, float Dy) {
    for (int i = y / 32; i < (y + h) / 32; i++) {
        for (int j = x / 32; j < (x + w) / 32; j++) {
            if (TileMap[i][j] == '0') {
                if (Dy > 0) {
                    y = i * 32 - h;
                    dy = -0.1;
                    direction = rand() % 3;
                } else if (Dy < 0) {
                    y = i * 32 + 32;
                    dy = 0.1;
                    direction = rand() % 3;
                } else if (Dx > 0) {
                    x = j * 32 - w;
                    dx = -0.1;
                    direction = rand() % 3;
                } else if (Dx < 0) {
                    x = j * 32 + 32;
                    dx = 0.1;
                    direction = rand() % 3;
                }
            }
        }
    }
}
void Enemy::update(float time) {
    // Логика обновления врага
    switch (direction) {
        case 0: // Состояние идти влево
            dx = -speed;
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
            break;

        case 1: // Состояние идти вправо
            dx = speed;
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
            break;

        case 2: // Состояние идти вверх
            dy = -speed;
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
            break;

        case 3: // Состояние идти вниз
            dy = speed;
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
            break;
    }
    x += dx * time;
       checkCollisionWithMap(dx, 0);

       y += dy * time;
       checkCollisionWithMap(0, dy);
       sprite.setPosition(x, y);

       // Инициализация стрельбы врага
       shoot(time);
       updateBullets(time);

       if (health <= 0) {
           life = false;
       }
   }
Image image;

void Enemy::shoot(float time) {
    if (life) {
        float bulletX = x + w / 2;
        float bulletY = y + h / 2;
        int bulletDirection = direction;

        // Создаем новый объект Bullet с использованием нового конструктора
        Bullet* bullet = new Bullet(image, bulletX, bulletY, 16, 16, "bullet", bulletDirection);

        bullets.push_back(bullet);
    }
}


