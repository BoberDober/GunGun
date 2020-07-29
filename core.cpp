#include "core.h"
#include <iostream>
#include <math.h>
#include <ctime>

Core::Core()
{
    m_width = 800;
    m_height = 365;
    m_running = true;
    m_mainWindow = nullptr;
    m_backgroundTexture = nullptr;
    m_renderer = nullptr;
    m_nEnemies = 3;
    m_enemies.resize(m_nEnemies);
    for(int i = 0; i < m_nEnemies; ++i)
    {
        m_enemies[i] = std::make_shared<Enemy>();
    }
    srand(time(0));
}

int Core::OnExecute()
{
    if(OnInit() == false)
    {
        std::cout << SDL_GetError();
        return -1;
    }

    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;

    SDL_Event event;
    while(m_running)
    {
        frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }

    OnCleanup();
    return 0;
}

bool Core::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    m_mainWindow = SDL_CreateWindow("Test task",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    m_width,
                                    m_height,
                                    SDL_WINDOW_SHOWN);
    if(m_mainWindow == nullptr)
    {
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_mainWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *backgroundSurface = SDL_LoadBMP("../GunGun/resource/background.bmp");
    if (backgroundSurface == nullptr)
    {
        return false;
    }

    m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


    m_weapon = std::make_shared<Weapon>();
    SDL_Rect weaponRect = {m_width / 2 - 50, 315, 100, 44};
    if(m_weapon->create(weaponRect, m_renderer) == false)
    {
        std::cout << SDL_GetError();
    }

    SDL_Rect scoreRect = {m_weapon->getRect()->x + (m_weapon->getRect()->w / 2) - (m_weapon->getRect()->w / 3) / 2, m_weapon->getRect()->y, m_weapon->getRect()->w / 3, m_weapon->getRect()->h};
    m_score = std::make_shared<Score>(scoreRect);
    m_mixer = std::make_shared<Mixer>();
    m_mixer->playMusic();
    return true;
}

void Core::OnEvent(SDL_Event* event)
{
    SDL_Point mousePoint = {event->motion.x, event->motion.y};

    switch (event->type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if(!m_weapon->getIsShoot())
            {
                m_weapon->setIsAim(true);
                actionCannon(mousePoint);
            }
            break;

        case SDL_MOUSEBUTTONUP:
            m_weapon->setIsAim(false);
            m_mixer->playShoot();
            if(!m_weapon->getIsShoot())
            {
                m_weapon->onShoot(m_renderer);
            }
            m_timeClick = SDL_GetTicks();
            break;

        case SDL_MOUSEMOTION:
            if(m_weapon->getIsAim() == true)
            {
                actionCannon(mousePoint);
            }
            break;
        case SDL_QUIT:
            m_running = false;
            break;
    }
}

void Core::OnLoop()
{

    //enemies loop
    for(auto enemies: m_enemies)
    {
        if(!enemies->alive())
        {
            SDL_Rect enemyRect = {m_width, 0, 50, 50};
            enemies->create(enemyRect, m_renderer);
        }
        else
        {
            enemies->move();
            if(enemies->getRect()->x > m_width || enemies->getRect()->x < 0 - enemies->getRect()->w)
            {
                enemies->setAlive(false);
            }
        }
    }


    //weapon loop
    if(m_weapon->getIsShoot())
    {
        SDL_Point cannonBallPoint =  {m_weapon->getCannonBallRect()->x, m_weapon->getCannonBallRect()->y};
        double x = 0.0;
        double y = 0.0;
        int x_0 = cannonBallPoint.x;
        int y_0 = cannonBallPoint.y;
        static double v = 0.1;
        double v_x = -1*(v*cos((M_PI * m_weapon->getCannonAnlge()) / 180));
        double v_y = -1* (v*sin((M_PI * m_weapon->getCannonAnlge()) / 180));
        Uint32 time = SDL_GetTicks() - m_timeClick;
        x = x_0 + v_x * time;
        y = y_0 + v_y * time;

        m_weapon->moveCannonBall(round(x), round(y));
        int indexIntersects = isIntersects();
        if(indexIntersects != -1)
        {
            m_enemies[indexIntersects]->setAlive(false);
            m_mixer->playHit();
            m_score->incScore();
            m_weapon->deleteCannonBall();
        }

        if(m_weapon->getCannonBallRect()->y + m_weapon->getCannonBallRect()->h < 0 ||
                m_weapon->getCannonBallRect()->x + m_weapon->getCannonBallRect()->w < 0 ||
                m_weapon->getCannonBallRect()->x > m_width)
        {
            m_weapon->deleteCannonBall();
        }
    }
}

double Core::getAngle(int x1, int y1, int x2, int y2)
{
    double t = (x1*x2+y1*y2)/(sqrt((double)x1*x1+y1*y1)*sqrt((double)x2*x2+y2*y2));
    if     (t<-1) t=-1;
    else if(t> 1) t= 1;
    return acos(t);
}

void Core::actionCannon(const SDL_Point &mousePoint)
{
    SDL_Rect *cannonRect = m_weapon->getCannonRect();
    SDL_Point point_1 = {-1, 0};
    SDL_Point point_2 = {mousePoint.x - (cannonRect->x + cannonRect->w/2), mousePoint.y - (cannonRect->y + cannonRect->h/2)};
    double angle = getAngle(point_1.x, point_1.y, point_2.x, point_2.y) *180/M_PI;
    if(mousePoint.y > cannonRect->y && mousePoint.x < cannonRect->x)
        angle = 0;
    if(mousePoint.y > cannonRect->y  && mousePoint.x > cannonRect->x)
        angle = 180;
    m_weapon->setCannonAnlge(angle);
}

int Core::isIntersects()
{
    int index = -1;
    for(int i=0; i<m_nEnemies; i++)
    {
        const SDL_Rect *a_rect =  m_enemies[i]->getRect();
        int a_x = a_rect->x, a_y = a_rect->y, a_x1 = a_rect->x + a_rect->w, a_y1 = a_rect->y + a_rect->h;
        const SDL_Rect *b_rect = m_weapon->getCannonBallRect();
        int b_x = b_rect->x, b_y = b_rect->y, b_x1 = b_rect->x + b_rect->w;
        if((b_y <= a_y1) && (b_x1 >= a_x) && (b_x <= a_x1) && (b_y <= a_y))
        {
            index = i;
        }
    }
    return index;
}

void Core::OnRender()
{
    SDL_RenderClear(m_renderer);

    SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);
    m_weapon->render(m_renderer);
    for(int i=0; i<m_nEnemies; i++)
    {
        m_enemies[i]->render(m_renderer);
    }

    m_score->render(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void Core::OnCleanup()
{
    m_mixer->stopMusic();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_backgroundTexture);
    SDL_DestroyWindow(m_mainWindow);
    SDL_Quit();
}
