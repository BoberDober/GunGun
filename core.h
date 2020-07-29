#ifndef CORE_H
#define CORE_H

#include "SDL.h"
//#include <SDL2/SDL.h>
#include "Unit/weapon.h"
#include "Unit/enemy.h"
#include "score.h"
#include <memory>
#include <vector>

class Core
{
private:
    int m_width;
    int m_height;
    bool m_running;
    int m_nEnemies;
    SDL_Window *m_mainWindow;
    SDL_Texture *m_backgroundTexture;
    SDL_Renderer *m_renderer;
    std::shared_ptr<Weapon> m_weapon;
    std::vector<std::shared_ptr<Enemy> > m_enemies;
    std::shared_ptr<Score> m_score;
    void actionCannon(const SDL_Point &mousePoint);

    Uint32 m_timeClick;
    int isIntersects();

public:
    Core();
    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    double getAngle(int x1, int y1, int x2, int y2);
    void OnRender();
    void OnCleanup();
};

#endif // CORE_H
