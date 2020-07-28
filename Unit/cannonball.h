#ifndef CANNONBALL_H
#define CANNONBALL_H

#include "unit.h"

class CannonBall: public Unit
{
public:
    CannonBall();

    bool create(SDL_Rect rect, SDL_Renderer *renderer);
    void move(int x, int y);
    void render(SDL_Renderer *renderer);

};

#endif // CANNONBALL_H
