#include "player.h"
#include "bullet.h"
#include "enemy.h"


int main()
{
sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
sf::RenderWindow window(sf::VideoMode(1280, 800, desktop.bitsPerPixel), "Lesson 12");

Font font;//шрифт
font.loadFromFile("BrassMono-Italic.ttf");//передаем нашему шрифту файл шрифта

Text text("", font, 20);//создаем объект текст
text.setColor(Color::Red);//покрасили текст в красный
text.setStyle(Text::Bold);//жирный текст.

Image map_image;//объект изображения для карты
map_image.loadFromFile("images/map_new.png");//загружаем файл для карты

Texture map;//текстура карты
map.loadFromImage(map_image);//заряжаем текстуру картинкой

Sprite s_map;//создаём спрайт для карты
s_map.setTexture(map);//заливаем текстуру спрайтом

Clock clock;
Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры
int gameTime = 0;//объявили игровое время, инициализировали.

Image heroImage;
heroImage.loadFromFile("images/hero.png"); // загружаем изображение игрока

Image easyEnemyImage;
easyEnemyImage.loadFromFile("images/enemy.png"); // загружаем изображение врага

Image BulletImage;//изображение для пули
BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения

Player p(heroImage, 100, 100, 96, 96, "Player1");//объект класса игрока

std::list<Entity*> enemies; //список врагов
std::list<Entity*> Bullets; //список пуль
std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка
std::list<Entity*>::iterator eit;

const int ENEMY_COUNT = 3; //максимальное количество врагов в игре
int enemiesCount = 0; //текущее количество врагов в игре

//Заполняем список объектами врагами
for (int i = 0; i < ENEMY_COUNT; i++)
{
    float xr = 150 + rand() % 500; // случайная координата врага на поле игры по оси “x”
    float yr = 150 + rand() % 350; // случайная координата врага на поле игры по оси “y”
    //создаем врагов и помещаем в список

    enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));
    enemiesCount +=1; //увеличили счётчик врагов
}

    int createObjectForMapTimer = 0;

    int count=1;//Переменная под время для генерирования камней
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в
        //секундах идёт вперед, пока жив игрок. Перезагружать как time его не надо.
        //оно не обновляет логику игры
        clock.restart();
        time = time / 800;
        createObjectForMapTimer += time;//наращиваем таймер
        if (createObjectForMapTimer>8000){
        {//Расставляем справки
                if (count==1){
                p.TileMap[3][10] = 's';
                count++;
                }// ожидание 15 секунд

               else if (count==2){
                 p.TileMap[21][28] = 's';
                 count++;   // ожидание 15 секунд
                }
                 else if (count==3){
                 p.TileMap[21][10] = 's';
                count++;   // ожидание 15 секунд
                }

                else if (count==4){
                 p.TileMap[3][28] = 's';
                 count=1;   // ожидание 15 секунд
                }
            };//генерация камней
        createObjectForMapTimer = 0;//обнуляем таймер
    }




    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        window.close();
        //стреляем по нажатию клавиши "P"
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::P)
            {
                Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state));
            }
        }
    }

    p.update(time); //оживляем объект “p” класса “Player”

    //оживляем врагов
    for (it = enemies.begin(); it != enemies.end(); it++)
    {
    (*it)->update(time); //запускаем метод update()
    }

    //оживляем пули
    for (it = Bullets.begin(); it != Bullets.end(); it++)
    {
    (*it)->update(time); //запускаем метод update()
    }

    //Проверяем список на наличие "мертвых" пуль и удаляем их
    for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца
    {// если этот объект мертв, то удаляем его
    if ((*it)-> life == false) { it = Bullets.erase(it); }
    else it++;//и идем курсором (итератором) к след объекту.
    }

    //Проверка пересечения игрока с врагами
    //Если пересечение произошло, то "health = 0", игрок обездвижевается и
    //выводится сообщение "you are lose"
    if (p.life == true)
    {//если игрок жив
        for (it = enemies.begin(); it != enemies.end(); it++)
        {//бежим по списку врагов
            if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
            {
            p.health = 0;
            std::cout << "you are lose";
            }
        }
    }
    if (p.playerScore == 1){
             p.health = 0;
            std::cout << "you are win";
            break;
          }
    //пересечение пули с врагом
        for (eit = enemies.begin(); eit != enemies.end(); eit++){//бежим по списку врагов
            for (it = Bullets.begin(); it != Bullets.end(); it++){//по списку пуль
                if (((*it)->getRect().intersects((*eit)->getRect())) &&
                    ((*eit)->name == "EasyEnemy") && ((*it)->name == "Bullet"))
                {
                    cout << "Exellent hit!\n";

                    //при попадании пули у врага отнимается здоровье
                    (*eit)-> health = 0;
                    if ((*eit)-> health <= 0) {
                        //(*eit)-> life = false;
                        //enemiesCount -= 1; //уменьшаем количество врагов в игре
                        (*eit)-> speed = 0;
                        cout << "Enemy destroyed!\n";
                    }
                    (*it)-> life = false;
                }
            }
        }

    window.clear();

    /////////////////////////////Рисуем карту/////////////////////
    for (int i = 0; i < HEIGHT_MAP; i++)
    for (int j = 0; j < WIDTH_MAP; j++)
    {
    if (p.TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));//пол
     if (p.TileMap[i][j] == 'k') s_map.setTextureRect(IntRect(0, 0, 32, 32));//пол
    if (p.TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));//справка
    if ((p.TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//стена
    s_map.setPosition(j * 32, i * 32);
    window.draw(s_map);
    }


    //объявили переменную здоровья и времени
    std::ostringstream playerHealthString, gameTimeString, playerScoreString;
    playerHealthString << p.health; gameTimeString << gameTime; playerScoreString << p.playerScore;//формируем строку
    text.setString("Health: " + playerHealthString.str() + "\nTime: " + gameTimeString.str()+"\nSpravki:" + playerScoreString.str());//задаем строку тексту
    text.setPosition(50, 50);//задаем позицию текста
    window.draw(text);//рисуем этот текст

    window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
    //рисуем врагов
    for (it = enemies.begin(); it != enemies.end(); it++)
    {
    if ((*it)->life) //если враги живы
    window.draw((*it)->sprite); //рисуем
    }
    //рисуем пули
    for (it = Bullets.begin(); it != Bullets.end(); it++)
    {
        if ((*it)->life) //если пули живы
        window.draw((*it)->sprite); //рисуем объекты
    }
    window.display();
}
return 0;
}

