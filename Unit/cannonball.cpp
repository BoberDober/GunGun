#include "cannonball.h"

CannonBall::CannonBall()
{

}

bool CannonBall::create(const SDL_Rect &rect, SDL_Renderer *renderer)
{
    m_rect = rect;
    m_texture = IMG_LoadTexture(renderer, "../GunGun/resource/cannonBall.png");
    if(!m_texture)
    {
      return false;
    }
    return true;
}

void CannonBall::move(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
}

void CannonBall::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, getTexture(), nullptr, &m_rect);
}
