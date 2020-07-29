#include "mixer.h"
#include <iostream>

Mixer::Mixer()
{
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )
    {
        return;
    }
    m_music = Mix_LoadMUS("../GunGun/resource/sound/music.wav");
    m_hit = Mix_LoadWAV("../GunGun/resource/sound/hit.wav");
    m_shoot = Mix_LoadWAV("../GunGun/resource/sound/shoot.wav");
    if(m_music == nullptr || m_hit == nullptr || m_shoot == nullptr)
    {
        return;
    }

    Mix_VolumeMusic(30);
    Mix_VolumeChunk(m_hit, 6);
    Mix_VolumeChunk(m_shoot, 10);
}

Mixer::~Mixer()
{
    Mix_FreeMusic(m_music);
    Mix_CloseAudio();
}

void Mixer::playMusic()
{
    Mix_PlayMusic(m_music, -1);
}

void Mixer::stopMusic()
{
    Mix_HaltMusic();
}

void Mixer::playHit()
{
    Mix_PlayChannel(-1, m_hit, 0);
}

void Mixer::playShoot()
{
    Mix_PlayChannel(-1, m_shoot, 0);
}
