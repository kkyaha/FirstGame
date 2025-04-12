#include "Menu.h"
#include "Input.h"
#include "Engine.h"

Menu::Menu() {
    selectedItem = 0;
}

bool Menu::Init(SDL_Renderer* renderer) {
    m_Renderer = renderer;
    TTF_Init();
    m_Font = TTF_OpenFont("Assets/kky.ttf", 130);
    TTF_SetFontStyle(m_Font, TTF_STYLE_BOLD);

    if (!m_Font) return false;

    SDL_Surface* bgSurface = IMG_Load("Assets/NEN.png");
    if (!bgSurface) {
        SDL_Log("Failed to load background: %s", SDL_GetError());
        return false;
    }
    m_BackgroundTexture = SDL_CreateTextureFromSurface(m_Renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    SDL_Color white = {255, 255, 255};
    int centerX = SCREEN_WIDTH / 2;
    int startY = SCREEN_HEIGHT / 3;

    for (size_t i = 0; i < menuItems.size(); i++) {
        SDL_Surface* surface = TTF_RenderText_Solid(m_Font, menuItems[i].c_str(), white);
        m_Textures.push_back(SDL_CreateTextureFromSurface(m_Renderer, surface));
        SDL_FreeSurface(surface);

        // Tạo rect để lưu vị trí từng mục menu
        int w, h;
        SDL_QueryTexture(m_Textures[i], NULL, NULL, &w, &h);
        itemRects[i] = {centerX - w / 2, startY + (int)i * 150, w, h};
    }
    return true;
}

void Menu::HandleInput() {
    SDL_GetMouseState(&mouseX, &mouseY);

    // Kiểm tra chuột di chuyển vào mục nào
    for (size_t i = 0; i < menuItems.size(); i++) {
        if (mouseX >= itemRects[i].x && mouseX <= itemRects[i].x + itemRects[i].w &&
            mouseY >= itemRects[i].y && mouseY <= itemRects[i].y + itemRects[i].h) {
            selectedItem = i;
        }
    }

    // Nếu nhấp chuột trái, chọn mục hiện tại
    if (Input::GetInstance()->GetMouseButtonDown(SDL_BUTTON_LEFT)) {
        if (selectedItem == 0) { // "Play"
            Engine::GetInstance()->SetGameState(GameState::PLAYING);
        } else if (selectedItem == 1) { // "Exit"
            Engine::GetInstance()->Quit();
        }
    }
}

void Menu::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);
    if (m_BackgroundTexture) {
        SDL_Rect bgRect = {0, 0, 1920, 1080};
        SDL_RenderCopyEx(m_Renderer, m_BackgroundTexture, NULL, &bgRect, 0, NULL, SDL_FLIP_NONE);

    } else {
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_Renderer);
    }

    for (size_t i = 0; i < menuItems.size(); i++) {
        if (i == selectedItem) {
            SDL_SetTextureColorMod(m_Textures[i], 255, 0, 0); // Đỏ khi chọn
        } else {
            SDL_SetTextureColorMod(m_Textures[i], 255, 255, 255);
        }
        SDL_RenderCopy(m_Renderer, m_Textures[i], NULL, &itemRects[i]);
    }

    SDL_RenderPresent(m_Renderer);
}

void Menu::Clean() {
    for (auto texture : m_Textures) {
        SDL_DestroyTexture(texture);
    }
    m_Textures.clear();

    if (m_BackgroundTexture) {
        SDL_DestroyTexture(m_BackgroundTexture);
        m_BackgroundTexture = nullptr;
    }

    TTF_CloseFont(m_Font);
    TTF_Quit();
}

