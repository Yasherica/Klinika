#include <SFML/Graphics.hpp>
    using namespace sf;
int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 3");
    Texture herotexture;
    herotexture.loadFromFile("images/hero.png");
    Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 192, 96, 96));//получили нужный прямоугольник
    herosprite.setPosition(50, 25);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(herosprite);
        window.display();
    }
    return 0;
}
