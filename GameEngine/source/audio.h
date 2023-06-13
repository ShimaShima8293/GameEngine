#pragma once

#include "macros.h"
#include PATH_SDL_MIXER

enum Channels
{
    CH_ALL = -1,
    CH_INTRO = 1,
    CH_LOOP,
    CH_FX,
};

struct MusicSet
{
    Mix_Chunk* intro;
    Mix_Chunk* loop;
    int fade = 5000;
};

void playMusicSet(MusicSet& set);
void playMusicSet(Mix_Chunk* intro, Mix_Chunk* loop, int fade = 5000);

void haltMusic();

void fadeOutMusic(int fade = 5000);

// Plays music with loop on. It will Print out an error message if it failed to play.
// [DEPRECATED]
//void playMusic(Mix_Music* music, int loops = -1);

bool getMuteState();
void setMuteState(bool _mute);