#include "Engine.h"
#include "TextureManager.h"

#include "Soilder.h"

using namespace std;

Engine* Engine::s_Instance = nullptr;
Soilder* player = nullptr;

bool Engine::Init() {
    if(SDL_Init(SDL_INIT_VIDEO)!= 0 and IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Fail to open image", SDL_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH, 0);
    if(m_Window == nullptr) {
        SDL_Log("Fail to create win", SDL_GetError());
        return false;
    }
    m_Renderer = (SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if(m_Renderer == nullptr) {
        SDL_Log("Fail to create render", SDL_GetError());
        return false;
    }
    TextureManager::GetInstance()->Load("player", "Assets/FlashIdle.png");

    player = new Soilder(new Properties("player", 200, 200, 305, 223));

    if (!TextureManager::GetInstance()->Load("player", "Assets/FlashIdle.png")) {
    SDL_Log("Failed to load player texture: %s", SDL_GetError());
    return false;
    }
    Transform tf;
    tf.Log();

    return m_IsRunning = true;
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            Quit();
            break;
    }
}

bool Engine::Clean() {
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    return true;
}

void Engine::Quit() {
    m_IsRunning = false;
}

void Engine::Update() {
    player->Update(0);
}


