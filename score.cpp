#include "score.h"
#include <iostream>

Score::Score(const SDL_Rect &rect)
{
    m_score = 0;
    if(TTF_Init()==-1) {
        std::cout << "TTF_Init ERROR: " << TTF_GetError();
        return;
    }

    m_font = TTF_OpenFont("../GunGun/resource/mainFont.ttf", 18);
    m_rect = rect;
    m_color = {255, 255, 0, 0};
}

void Score::incScore()
{
    m_score++;
}

void Score::render(SDL_Renderer *renderer)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, std::to_string(m_score).data(), m_color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_RenderCopy(renderer, Message, NULL, &m_rect);
}
