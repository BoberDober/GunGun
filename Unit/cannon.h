#ifndef CANNON_H
#define CANNON_H

#include "unit.h"

class Cannon: public Unit
{
public:
    Cannon();

    bool create(const SDL_Rect &rect, SDL_Renderer *renderer);

    double getAnlge() const;
    void setAnlge(double anlge);
    void render(SDL_Renderer *renderer);
private:
    double m_anlge;
};

#endif // CANNON_H
