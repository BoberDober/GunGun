#ifndef MIXER_H
#define MIXER_H

#include "SDL2_mixer/SDL_mixer.h"

class Mixer
{
private:
    Mix_Music *m_music;
    Mix_Chunk *m_hit;
    Mix_Chunk *m_shoot;
public:
    Mixer();
    ~Mixer();
    void playMusic();
    void stopMusic();
    void playHit();
    void playShoot();
};

#endif // MIXER_H
