#include "weapon.h"
#include <iostream>

Weapon::Weapon(): Unit()
{
    m_cannon = std::make_shared<Cannon>();
    m_isAim = false;
//    m_trackPoint = {0, 0};
    m_isShoot = false;
    m_cannonBall = std::make_shared<CannonBall>();
}

bool Weapon::create(const SDL_Rect &rect, SDL_Renderer *renderer)
{
    m_rect = rect;
    m_texture = IMG_LoadTexture(renderer, "../GunGun/resource/stand.png");
    if(!m_texture)
    {
      return false;
    }
    SDL_Rect cannonRect = {rect.x + rect.w/2 - 30 , 250, 66, 50};
    if(m_cannon->create(cannonRect, renderer) == false)
    {
        return false;
    }

    return true;
}

SDL_Rect *Weapon::getCannonRect()
{
    return m_cannon->getRect();
}

SDL_Texture *Weapon::getCannonTexture()
{
    return m_cannon->getTexture();
}

SDL_Rect *Weapon::getCannonBallRect()
{
    return m_cannonBall->getRect();
}

SDL_Texture *Weapon::getCannonBallTexture()
{
    return m_cannonBall->getTexture();
}

double Weapon::getCannonAnlge() const
{
    return m_cannon->getAnlge();
}

void Weapon::setCannonAnlge(double anlge)
{
    m_cannon->setAnlge(anlge);
}

bool Weapon::getIsAim() const
{
    return m_isAim;
}

void Weapon::setIsAim(bool isAim)
{
    m_isAim = isAim;
}

bool Weapon::getIsShoot() const
{
    return m_isShoot;
}

void Weapon::onShoot(SDL_Renderer *renderer)
{
    m_isShoot = true;
    int cannonBallSize = 40;
    SDL_Rect cannonBallRect = {getCannonRect()->x + getCannonRect()->w/2 - cannonBallSize/2 , getCannonRect()->y, cannonBallSize, cannonBallSize};
    if(m_cannonBall->create(cannonBallRect, renderer) == false)
    {
        return;
    }
}

void Weapon::deleteCannonBall()
{
    m_isShoot = false;
}

void Weapon::moveCannonBall(int x, int y)
{
    m_cannonBall->move(x, y);
}

void Weapon::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, getTexture(), nullptr, &m_rect);
    m_cannon->render(renderer);
    if(m_isShoot)
    {
        m_cannonBall->render(renderer);
    }
}
