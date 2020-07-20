

#ifndef ARGENTUM_GAME_SOUND_MANAGER_H
#define ARGENTUM_GAME_SOUND_MANAGER_H


#include <SDL2/SDL_mixer.h>
#include "../../common/defines/attacks.h"
#include <map>
#include <iostream>
#include <string>
#include "exception.h"


class GameSoundManager {
    Mix_Music* music;
    std::map<soundType, Mix_Chunk*> chunkMap;
    void addNewSound(std::string path, soundType type);
    void initSounds();
    void initMusic();
    int musicOn;
    int soundOn;

public:
    GameSoundManager();
    ~GameSoundManager();
    void playSound(soundType type);
    void toggleMusic();
    void toggleSound();
};


#endif //ARGENTUM_GAME_SOUND_MANAGER_H
