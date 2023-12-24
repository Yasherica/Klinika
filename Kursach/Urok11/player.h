// В файле player.h
#ifndef SOME_OTHER_FILE_H
#define SOME_OTHER_FILE_H
#include "Enums.h"
#include "entity.h"


enum class State {
    Right,
    Left,
    Up,
    Down,
    Stay
};

enum class TileType {
    Empty,
    Ground,
    Stone
};

class Player : public Entity {
public:
    int playerScore;
    State state = State::stay;

    Player(Image &image, float X, float Y, int W, int H, string Name);

    // Конструктор по умолчанию
    Player() : Entity(Image(), 0, 0, 0, 0, std::string("")) {
        playerScore = 0;
        State state = State::stay;
    }


    void control();
    void checkCollisionWithMap(float Dx, float Dy) const;
    void update(float time) override;
    float getX() const { return x; }
    float getY() const { return y; }
    State getState() const { return state; }

private:
    static const int HEIGHT_MAP = 1;
    static const int WIDTH_MAP = 1;

    TileType tile;
};

#endif // SOME_OTHER_FILE_H
