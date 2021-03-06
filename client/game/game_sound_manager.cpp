

#include "game_sound_manager.h"
#define CHUNKSIZE 2048
#define CHANNELS 4
#define FREQUENCY 44100
#define DEFAULT_CHANNEL 0

GameSoundManager::GameSoundManager() {
    int flags = MIX_INIT_FLAC;
    int result = 0;
    Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNKSIZE);
    if (flags != (result = Mix_Init(flags))) {
        Mix_CloseAudio();
        printf("Could not initialize mixer (result: %d).\n", result);
        throw SoundException(Mix_GetError());
    }
    initSounds();
    initMusic();
}

void GameSoundManager::initMusic() {
    std::string path_music = "../client/resources/audio/got.mp3";
    music = Mix_LoadMUS(path_music.data());
    if (music == NULL) {
        Mix_CloseAudio();
        for (auto const& chunk : chunkMap) {
            Mix_FreeChunk(chunk.second);
        }
        std::string error_msg = "\nError: Could not load .mp3 file: ";
        throw SoundException(error_msg + path_music);
    }
    Mix_PlayMusic(music, -1);
    musicOn = true;
}

void GameSoundManager::initSounds() {
    std::string path_sword = "../client/resources/audio/sword.wav";
    std::string path_explosion = "../client/resources/audio/explosion.wav";
    std::string path_melee = "../client/resources/audio/melee.wav";
    std::string path_magic_strike = "../client/resources/audio/shot.mp3";
    std::string path_arrow_strike = "../client/resources/audio/arrow.mp3";
    std::string path_heal = "../client/resources/audio/flute.wav";
    std::string path_axe = "../client/resources/audio/axe.mp3";
    std::string path_hammer = "../client/resources/audio/hammer.mp3";
    std::string path_list = "../client/resources/audio/list.mp3";

    addNewSound(path_melee, PLAYER_PUNCH);
    addNewSound(path_melee, CREATURE_PUNCH);
    addNewSound(path_hammer, HAMMER_STRIKE);
    addNewSound(path_axe, AXE_STRIKE);
    addNewSound(path_arrow_strike, ARROW_STRIKE);
    addNewSound(path_sword, SWORD_STRIKE);
    addNewSound(path_magic_strike, MAGIC_STRIKE);
    addNewSound(path_explosion, EXPLOSION);
    addNewSound(path_heal, HEAL_STRIKE);
    addNewSound(path_list, LIST);

    soundOn = true;
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
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_AudioQuit();
}


void GameSoundManager::playSound(soundType sound) {
    if (Mix_Playing(-1) != 0 || not soundOn) return;
    //en caso sonido aun no implementado no queremos que rompa
    if (chunkMap.find(sound) == chunkMap.end()) return;
    if (Mix_PlayChannel(-1, chunkMap.at(sound), 0) == -1) {
        throw SoundException("\nError: Could not play wav file on channel");
    }
}

void GameSoundManager::toggleSound() {
    if (soundOn) {
        for (int i = 0; i < CHANNELS; i++) {
            Mix_Pause(i);
        }
        soundOn = false;
    } else {
        soundOn = true;
    }
}

void GameSoundManager::toggleMusic() {
    if (musicOn) {
        Mix_PauseMusic();
        musicOn = false;
    } else {
        Mix_ResumeMusic();
        musicOn = true;
    }
}
