#include "TextureManager.h"
#include "Engine.h"
#include "SDL.h"
#include <iostream>

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    std::cout << "Loading texture from path: " << id << std::endl;
    if(!surface){
        std::cout << "[ERROR] IMG_Load failed: " <<id<<'-'<< filename << " - " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(!texture) {
        SDL_Log("Fail to create texture from surface", SDL_GetError());
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
     SDL_Rect srcRect = {0, 0, width, height};
     SDL_Rect dstRect = {x, y, width, height};
     SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Draw(std::string id, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dest);
}


void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip, double angle)
{
     SDL_Rect srcRect = {width*frame, height*row, width, height};
     float scaleFactor = 0.42f;  // Giảm 50%
     SDL_Rect dstRect = {x, y, static_cast<int>(width * scaleFactor), static_cast<int>(height * scaleFactor)};

     SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, angle, nullptr, flip);
}

void TextureManager::Drop(std::string id) {
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    m_TextureMap.clear();
    SDL_Log("texturemap cleaned");
}

