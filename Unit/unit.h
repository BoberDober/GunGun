#ifndef UNIT_H
#define UNIT_H

#include "SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class Unit
{

public:
    virtual bool create(SDL_Rect rect, SDL_Renderer *renderer) = 0;
    virtual SDL_Rect* getRect() { return &m_rect; }
    virtual SDL_Texture* getTexture() { return m_texture; }
    Unit() {};
    virtual ~Unit() {       std::cout << "DELETE UNIT" << std::endl;};
protected:
    SDL_Rect m_rect;
    SDL_Texture *m_texture;
};

#endif // UNIT_H
