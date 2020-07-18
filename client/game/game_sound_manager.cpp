

#include "game_sound_manager.h"

GameSoundManager::GameSoundManager() {
    int flags = MIX_INIT_FLAC;
    int result = 0;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        throw SoundException(Mix_GetError());
    }
    std::string path_sword = "../client/resources/audio/sword.wav";
    std::string path_explosion = "../client/resources/audio/explosion.wav";
    addNewSound(path_sword, SWORD_STRIKE);
    addNewSound(path_explosion, EXPLOSION);
    std::string path_music = "../client/resources/audio/got.mp3";
    music = Mix_LoadMUS(path_music.data());
    if (music == NULL) {
        std::string error_msg = "\nError: Could not load .mp3 file: ";
        throw SoundException(error_msg + path_music);
    }
    Mix_PlayMusic(music, -1);
}

void GameSoundManager::addNewSound(std::string path, soundType type) {
    Mix_Chunk* sound = Mix_LoadWAV(path.data());
    if (sound == NULL) {
        std::string error_msg ="\nError: Could not load .wav file: ";
        throw SoundException(error_msg + path);
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
    //en caso sonido aun no implementado no queremos que rompa
    if (chunkMap.find(sound) == chunkMap.end()) return;
    if (Mix_PlayChannel(0, chunkMap.at(sound), 0) == -1) {
        throw SoundException("\nError: Could not play wav file on channel");
    }
}