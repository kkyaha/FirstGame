#pragma once
#include <SDL_mixer.h>
#include <string>
#include <map>

class SoundManager {
public:
    static SoundManager* GetInstance();

    bool LoadSound(const std::string& id, const std::string& path);
    bool LoadMusic(const std::string& id, const std::string& path);

    void PlaySound(const std::string& id, int loops = 0);
    void PlayMusic(const std::string& id, int loops = -1);
    void StopMusic();
    void StopAllSounds();

    void Clean();

private:
    SoundManager() = default;
    ~SoundManager() = default;

    std::map<std::string, Mix_Chunk*> m_SoundMap;
    std::map<std::string, Mix_Music*> m_MusicMap;

    static SoundManager* s_Instance;
};
