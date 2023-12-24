#include "player.h" //подключили код с картой



Player::Player(Image &image, float X, float Y, int W, int H, string Name) : Entity(image, X, Y, W, H, Name) {
    playerScore = 0;
    state = State::Stay;
    if (name == "Player1") {
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }
}

void Player :: control(){
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
    state = left;
    speed = 0.1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
    state = right;
    speed = 0.1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
    state = up;
    speed = 0.1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
    state = down;
    speed = 0.1;
    }
}

//Метод проверки столкновений с элементами карты
void Player::checkCollisionWithMap(float Dx, float Dy) const {
    TileType tile = getTileAtPosition(x, y);
    for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
    for (int j = x / 32; j<(x + w) / 32; j++)
    {
        if (TileMap[i][j] == '0')//если элемент тайлик земли
        {
        if (Dy > 0) { y = i * 32 - h; dy = 0; }//по Y
        if (Dy < 0) { y = i * 32 + 32; dy = 0; }//столкновение с верхними краями
        if (Dx > 0) { x = j * 32 - w; dx = 0; }//с правым краем карты
        if (Dx < 0) { x = j * 32 + 32; dx = 0; }// с левым краем карты
        }
        if (TileMap[i][j] == 's') {
        playerScore++; //если взяли камень
        TileMap[i][j] = ' ';
        }
    }
}

void Player :: update(float time) //метод "оживления/обновления" объекта класса.
{
    if (life) {//проверяем, жив ли герой
        control();//функция управления персонажем
        switch (state)//делаются различные действия в зависимости от состояния
        {
            case right:{//состояние идти вправо
            dx = speed;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
            break;
            }
            case left:{//состояние идти влево

            dx = -speed;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
            break;
            }
            case up:{//идти вверх
            dy = -speed;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
            break;
            }
            case down:{//идти вниз
            dy = speed;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
            break;
            }
            case stay:{//стоим
            dy = speed;
            dx = speed;
            break;
            }
        }
        x += dx*time; //движение по “X”
        checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
        y += dy*time; //движение по “Y”
        checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
        speed = 0; //обнуляем скорость, чтобы персонаж остановился.
        //state = stay;
        sprite.setPosition(x, y); //спрайт в позиции (x, y).
        if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем
    }
}
