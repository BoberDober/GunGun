#include "cannon.h"

Cannon::Cannon()
{

}

bool Cannon::create(const SDL_Rect &rect, SDL_Renderer *renderer)
{
    m_rect = rect;
    m_texture = IMG_LoadTexture(renderer, "../GunGun/resource/cannon.png");
    if(!m_texture)
    {
      return false;
    }
    return true;
}

double Cannon::getAnlge() const
{
    return m_anlge;
}

void Cannon::setAnlge(double anlge)
{
    m_anlge = anlge;
}

void Cannon::render(SDL_Renderer *renderer)
{
    SDL_RenderCopyEx(renderer, getTexture(), nullptr, &m_rect, m_anlge, NULL, SDL_FLIP_NONE);
}
