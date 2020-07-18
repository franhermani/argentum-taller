

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
public:
    GameSoundManager();
    ~GameSoundManager();
    void playSound(soundType type);
};


#endif //ARGENTUM_GAME_SOUND_MANAGER_H
