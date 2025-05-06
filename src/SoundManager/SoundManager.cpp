#include "SoundManager.h"
#include <SDL.h>
#include <iostream>

SoundManager* SoundManager::s_Instance = nullptr;

SoundManager* SoundManager::GetInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new SoundManager();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    }
    return s_Instance;
}

bool SoundManager::LoadSound(const std::string& id, const std::string& path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (chunk == nullptr) {
        std::cerr << "Failed to load sound: " << path << " Error: " << Mix_GetError() << std::endl;
        return false;
    }
    m_SoundMap[id] = chunk;
    return true;
}

bool SoundManager::LoadMusic(const std::string& id, const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << path << " Error: " << Mix_GetError() << std::endl;
        return false;
    }
    m_MusicMap[id] = music;
    return true;
}

void SoundManager::PlaySound(const std::string& id, int loops) {
    if (m_SoundMap.count(id) > 0)
        Mix_PlayChannel(-1, m_SoundMap[id], loops);
}

void SoundManager::PlayMusic(const std::string& id, int loops) {
    if (m_MusicMap.count(id) > 0)
        Mix_PlayMusic(m_MusicMap[id], loops);
}

void SoundManager::StopMusic() {
    Mix_HaltMusic();
}

void SoundManager::StopAllSounds() {
    Mix_HaltChannel(-1);
}

void SoundManager::Clean() {
    for (auto& pair : m_SoundMap) {
        Mix_FreeChunk(pair.second);
    }
    m_SoundMap.clear();

    for (auto& pair : m_MusicMap) {
        Mix_FreeMusic(pair.second);
    }
    m_MusicMap.clear();

    Mix_CloseAudio();
}
