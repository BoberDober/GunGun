#ifndef ENEMY_H
#define ENEMY_H

#include "unit.h"

enum Direction {RIGHT = 0, LEFT};
enum Type {PUNK = 0, BUG, YELLOW};

class Enemy: public Unit
{
public:
    Enemy();
    bool create(const SDL_Rect &rect, SDL_Renderer *renderer);
    void move();
    bool alive() const;
    void setAlive(bool alive);
    int speed() const;
    void render(SDL_Renderer *renderer);

private:
    bool m_alive;
    int m_speed;
    Direction m_direction;
    Type m_type;
    int m_frame;
};

#endif // ENEMY_H
