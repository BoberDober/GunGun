#ifndef WEAPON_H
#define WEAPON_H

#include "unit.h"
#include "SDL.h"
#include "cannon.h"
#include "cannonball.h"

class Weapon: public Unit
{
public:
    Weapon();

    bool create(SDL_Rect rect, SDL_Renderer *renderer);

    SDL_Rect *getCannonRect();
    SDL_Texture *getCannonTexture();

    SDL_Rect *getCannonBallRect();
    SDL_Texture *getCannonBallTexture();

    double getCannonAnlge() const;
    void setCannonAnlge(double anlge);

    bool getIsAim() const;
    void setIsAim(bool isAim);

    bool getIsShoot() const;

    void onShoot(SDL_Renderer *renderer);
    void deleteCannonBall();
    void moveCannonBall(int x, int y);
    void render(SDL_Renderer *renderer);

private:
    Cannon* m_cannon;
    CannonBall* m_cannonBall;
    bool m_isAim;
    bool m_isShoot;
};

#endif // WEAPON_H
