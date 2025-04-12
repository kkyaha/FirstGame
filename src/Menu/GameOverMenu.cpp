#include "GameOverMenu.h"
#include "Engine.h"
#include "Input.h"

GameOverMenu::GameOverMenu() {
    menuItems = {"Retry", "Exit"};
    selectedItem = 0;
}

bool GameOverMenu::Init(SDL_Renderer* renderer) {
    m_Renderer = renderer;
    if (!Menu::Init(renderer)) return false;
    TTF_Init();
    m_Font = TTF_OpenFont("Assets/kky.ttf", 130);
    TTF_SetFontStyle(m_Font, TTF_STYLE_BOLD);
    SDL_Color red = {255, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, "GAME OVER", red);
    if (!surface) {
        SDL_Log("[ERROR] Không thể tạo surface GAME OVER: %s", TTF_GetError());
        return false;
    }

    m_GameOverTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);
    if (!m_GameOverTexture) {
        SDL_Log("[ERROR] Không thể tạo texture GAME OVER: %s", SDL_GetError());
        return false;
    }

    int w, h;
    SDL_QueryTexture(m_GameOverTexture, NULL, NULL, &w, &h);
    m_GameOverRect = {SCREEN_WIDTH / 2 - w / 2, SCREEN_HEIGHT / 5, w, h};

    return true;
}

void GameOverMenu::HandleInput() {
    Menu::HandleInput();
    SDL_GetMouseState(&mouseX, &mouseY);

    for (size_t i = 0; i < menuItems.size(); i++) {
        if (mouseX >= itemRects[i].x && mouseX <= itemRects[i].x + itemRects[i].w &&
            mouseY >= itemRects[i].y && mouseY <= itemRects[i].y + itemRects[i].h) {
            selectedItem = i;
        }
    }

    if (Input::GetInstance()->GetMouseButtonDown(SDL_BUTTON_LEFT)) {
        if (selectedItem == 0) {
            Engine::GetInstance()->RestartGame();
        } else if (selectedItem == 1) {
            Engine::GetInstance()->Quit();
        }
    }
}

void GameOverMenu::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);

    SDL_RenderCopy(m_Renderer, m_BackgroundTexture, NULL, NULL);
    SDL_RenderCopy(m_Renderer, m_GameOverTexture, NULL, &m_GameOverRect);

    for (size_t i = 0; i < menuItems.size(); i++) {
        if (i < m_Textures.size()) {
            if (i == selectedItem) {
                SDL_SetTextureColorMod(m_Textures[i], 255, 0, 0);
            } else {
                SDL_SetTextureColorMod(m_Textures[i], 255, 255, 255);
            }
            SDL_RenderCopy(m_Renderer, m_Textures[i], NULL, &itemRects[i]);
        }
    }

    SDL_RenderPresent(m_Renderer);
}

void GameOverMenu::Clean() {
    if (m_GameOverTexture) {
        SDL_DestroyTexture(m_GameOverTexture);
        m_GameOverTexture = nullptr;
    }

    Menu::Clean();
}
