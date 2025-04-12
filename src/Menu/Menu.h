#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>

class Menu {
public:
    Menu();
    bool Init(SDL_Renderer* renderer);
    void Render();
    void HandleInput();
    void Clean();
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_BackgroundTexture = nullptr;
    TTF_Font* m_Font;
    std::vector<std::string> menuItems = {"Play", "Exit"};
    std::vector<SDL_Texture*> m_Textures;
    int selectedItem = 0;

    int mouseX, mouseY;
    SDL_Rect itemRects[2];  // Lưu vị trí từng item để kiểm tra chuột
};

#endif
