#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Soilder.h"
#include "SDL.h"

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

    TextureManager::GetInstance()->Load("player_idle", "Assets/FlashIdle.png");
    TextureManager::GetInstance()->Load("player_run", "Assets/FlashRun.png");
    TextureManager::GetInstance()->Load("player_attack", "Assets/FlashAttack.png");
    TextureManager::GetInstance()->Load("player_hand_gun_idle", "Assets/HandGunIdle.png");
    TextureManager::GetInstance()->Load("player_hand_gun_run", "Assets/HandGunRun.png");
    TextureManager::GetInstance()->Load("player_hand_gun_attack", "Assets/HandGunAttack.png");
    TextureManager::GetInstance()->Load("player_hand_gun_reload", "Assets/HandGunReload.png");
    TextureManager::GetInstance()->Load("player_knife_run", "Assets/KnifeRun.png");
    TextureManager::GetInstance()->Load("player_knife_attack", "Assets/KnifeAttack.png");
    TextureManager::GetInstance()->Load("player_knife_idle", "Assets/KnifeIdle.png");
    TextureManager::GetInstance()->Load("player_rife_run", "Assets/RifeRun.png");
    TextureManager::GetInstance()->Load("player_rife_attack", "Assets/RifeAttack.png");
    TextureManager::GetInstance()->Load("player_rife_idle", "Assets/RifeIdle.png");
    TextureManager::GetInstance()->Load("player_sg_run", "Assets/SgRun.png");
    TextureManager::GetInstance()->Load("player_sg_attack", "Assets/SgAttack.png");
    TextureManager::GetInstance()->Load("player_sg_idle", "Assets/SgIdle.png");

    player = new Soilder(new Properties("player", 300, 300, 305, 223));

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
    Input::GetInstance()->Listen();
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


