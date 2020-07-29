#ifndef SCORE_H
#define SCORE_H

#include "SDL2_TTF/SDL_ttf.h"
#include "SDL.h"
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL.h>

class Score
{
private:
    TTF_Font* m_font;
    SDL_Rect m_rect;
    int m_score;
    SDL_Color m_color;
public:
    Score(const SDL_Rect &rect);
    ~Score();
    void incScore();
    void render(SDL_Renderer *renderer);
};

#endif // SCORE_H
