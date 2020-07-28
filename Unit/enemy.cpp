#include "enemy.h"
#include "iostream"
#include "string"

Enemy::Enemy()
{
    m_alive = false;
    m_direction = RIGHT;
    m_type = PUNK;
    m_frame = 0;
}

bool Enemy::create(SDL_Rect rect, SDL_Renderer *renderer)
{
    m_direction = static_cast<Direction>(rand() % 2 == 0);
    m_type = static_cast<Type>(rand() % 3);
    m_rect = rect;
    m_rect.y = rand() % 100 +0;
    m_speed = rand() % 7 +2;
    std::string path = "../GunGun/resource/enemyTiles/";
    switch (m_type)
    {
    case PUNK:
        path += "punkBird/";
        break;
    case BUG:
        path += "redBug/";
        break;
    case YELLOW:
        path += "yellowBird/";
        break;
    default:
        path += "punkBird/";
        break;
    }

    switch (m_direction)
    {
    case LEFT:
        m_speed*= -1;
        path += "leftSprite.png";
        break;
    case RIGHT:
        m_rect.x = 0;
        path += "rightSprite.png";
        break;
    default:
        m_rect.x = 0;
        path += "rightSprite.png";
        break;
    }

    m_texture = IMG_LoadTexture(renderer, path.data());
    if(!m_texture)
    {
      return false;
    }

    m_alive = true;
    return true;
}

void Enemy::move()
{
    m_frame++;
    if(m_frame == 4)
    {
        m_frame = 0;
    }
    m_rect.x = m_rect.x + m_speed;
}

bool Enemy::alive() const
{
    return m_alive;
}

void Enemy::setAlive(bool alive)
{
    m_alive = alive;
}

int Enemy::speed() const
{
    return m_speed;
}

void Enemy::render(SDL_Renderer *renderer)
{
    SDL_Rect srcRect = { m_rect.w * m_frame, 0, m_rect.w, m_rect.h };
    SDL_Rect rect = { getRect()->x, getRect()->y, m_rect.w, m_rect.h };
    SDL_RenderCopy(renderer, m_texture, &srcRect, &rect);
}

