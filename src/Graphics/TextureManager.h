#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <SDL.h>
#include <map>

class TextureManager
{
    public:
        static TextureManager* GetInstance(){
            if (s_Instance == nullptr) {
                s_Instance = new TextureManager();
            }
            return s_Instance;
        }
        bool Load(std::string id, std::string filename);
        void Drop(std::string id);
        void Clean();

        void Draw(std::string id, SDL_Rect src, SDL_Rect dest);
        void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0);
        SDL_Texture* GetTexture(const std::string& id) {
        if (m_TextureMap.find(id) != m_TextureMap.end()) {
            return m_TextureMap[id];
        }
        return nullptr;
    }
    private:
        TextureManager(){}
        std::map<std::string, SDL_Texture*> m_TextureMap;
        static TextureManager* s_Instance;
};

#endif // TEXTUREMANAGER_H
