#ifndef UNIT_H
#define UNIT_H

#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <memory>

class Unit
{
public:
    virtual bool create(const SDL_Rect &rect, SDL_Renderer *renderer) = 0;
    virtual SDL_Rect* getRect() { return &m_rect; }
    virtual SDL_Texture* getTexture() { return m_texture; }
    virtual void render(SDL_Renderer *renderer) = 0;
    Unit() {m_texture = nullptr;}
    virtual ~Unit() {
        if(m_texture)
        {
            SDL_DestroyTexture(m_texture);
        }
    };
protected:
    SDL_Rect m_rect;
    SDL_Texture *m_texture;
};

#endif // UNIT_H
