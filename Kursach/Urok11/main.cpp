#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>
#include <sstream>
#include "Enums.h"

using namespace sf;

int main() {
    State state = State::stay;
    int count = 1;
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Your Game");
    window.setFramerateLimit(60);

    std::list<Entity*>::iterator it;
    std::list<Entity*> enemies;
    std::list<Entity*> Bullets;

    Font font;
    font.loadFromFile("BrassMono-Italic.ttf");
    Text text("", font, 20);
    text.setColor(Color::Red);
    text.setStyle(Text::Bold);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    Clock clock;
    Clock gameTimeClock;
    int gameTime = 0;
    int createObjectForMapTimer = 0;
    Sprite s_map;

    // Замените это на ваш объект класса Player
    Player p;

    // Остальной код без повторных объявлений
    // ...

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        createObjectForMapTimer += time;

        // Расставляем справки
        if (count == 1) {
            p.TileMap[3][10] = 's';
            count++;
        } else if (count == 2) {
            p.TileMap[21][28] = 's';
            count++;
        } else if (count == 3) {
            p.TileMap[21][10] = 's';
            count++;
        } else if (count == 4) {
            p.TileMap[3][28] = 's';
            count = 1;
        }

        // генерация камней
        createObjectForMapTimer = 0;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    // Объявите переменные p и BulletImage

                    Image BulletImage;
                    Bullets.push_back(new Bullet(BulletImage, p.getX(), p.getY(), 16, 16, "Bullet", static_cast<int>(p.getState())));

                }
            }
        }

        // Замените "p" на ваш объект класса Player
        p.update(time);

        for (it = enemies.begin(); it != enemies.end(); it++) {
            (*it)->update(time);
        }

        for (it = Bullets.begin(); it != Bullets.end(); it++) {
            (*it)->update(time);
        }

        for (it = Bullets.begin(); it != Bullets.end(); ) {
            if ((*it)->life == false) {
                it = Bullets.erase(it);
            } else
                it++;
        }

        if (p.life == true) {
            for (it = enemies.begin(); it != enemies.end(); it++) {
                if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy")) {
                    p.health = 0;
                    std::cout << "you are lose";
                }
            }
        }

        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++) {
                if (p.TileMap[i][j] == ' ')
                    s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (p.TileMap[i][j] == 'k')
                    s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (p.TileMap[i][j] == 's')
                    s_map.setTextureRect(IntRect(32, 0, 32, 32));
                if ((p.TileMap[i][j] == '0'))
                    s_map.setTextureRect(IntRect(64, 0, 32, 32));
                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }

        std::ostringstream playerHealthString, gameTimeString, playerScoreString;
        playerHealthString << p.health;
        gameTimeString << gameTime;
        playerScoreString << p.playerScore;
        text.setString("Health: " + playerHealthString.str() + "\nTime: " + gameTimeString.str() +
                       "\nSpravki:" + playerScoreString.str());
        text.setPosition(50, 50);
        window.draw(text);

        window.draw(p.sprite);

        for (it = enemies.begin(); it != enemies.end(); it++) {
            if ((*it)->life)
                window.draw((*it)->sprite);
        }

        for (it = Bullets.begin(); it != Bullets.end(); it++) {
            if ((*it)->life)
                window.draw((*it)->sprite);
        }

        if (p.life == true) {
            for (it = enemies.begin(); it != enemies.end(); it++) {
                if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy")) {
                    p.health = 0;
                    std::cout << "you are lose";
                }
            }
        }

        window.display();
    }

    return 0;
}

