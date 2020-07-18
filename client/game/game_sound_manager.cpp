

#include "game_sound_manager.h"

GameSoundManager::GameSoundManager() {
    int flags = MIX_INIT_FLAC;
    int result = 0;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }
    std::string path_sword = "../client/resources/audio/sword.wav";
    std::string path_explosion = "../client/resources/audio/explosion.wav";
    addNewSound(path_sword, SWORD_STRIKE);
    addNewSound(path_explosion, EXPLOSION);
    static const char* path_music = "../client/resources/audio/got.mp3";
    music = Mix_LoadMUS(path_music);
    if (music == NULL) {
        std::cout << "Error: Could not load .mp3 file: " << path_music << std::endl;
    }
    Mix_PlayMusic(music, -1);
}

void GameSoundManager::addNewSound(std::string path, soundType type) {
    Mix_Chunk* sound = Mix_LoadWAV(path.data());
    if (sound == NULL) {
        std::cout << "Error: Could not load .wav file: " << path << std::endl;
    }
    chunkMap.insert({type, sound});
}

GameSoundManager::~GameSoundManager() {
    for (auto const& chunk : chunkMap) {
        Mix_FreeChunk(chunk.second);
    }
    Mix_Quit();
}


void GameSoundManager::playSound(soundType sound) {
    if (Mix_PlayChannel(0, chunkMap[sound], 0) == -1){
        std::cout << "Error: Could not play wav file  on channel "
                  << 0 << std::endl;
    }
}
