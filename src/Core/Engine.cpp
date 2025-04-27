#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Soilder.h"
#include "SDL.h"
#include "Camera.h"
#include "Zombie.h"
#include "ZombieManager.h"
#include "BulletManager.h"
#include "SDL_image.h"
#include "Menu.h"
#include "Bullet.h"
#include "GameOverMenu.h"
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>
#include "SoundManager.h"

using namespace std;

Engine* Engine::s_Instance = nullptr;

ZombieManager* ZombieManager::s_Instance = nullptr;
BulletManager* BulletManager::s_Instance = nullptr;


float dt = 4;

bool Engine::Init() {
    if(SDL_Init(SDL_INIT_VIDEO)!= 0 and IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Fail to open image", SDL_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("Zombie Shooter", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH, 0);
    if(m_Window == nullptr) {
        SDL_Log("Fail to create win", SDL_GetError());
        return false;
    }
    m_Renderer = (SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if(m_Renderer == nullptr) {
        SDL_Log("Fail to create render", SDL_GetError());
        return false;
    }

        TextureManager::GetInstance()->Load("background", "Assets/MAP3.png");
        TextureManager::GetInstance()->Load("player_hand_gun_idle", "Assets/HandGunIdle.png");
        TextureManager::GetInstance()->Load("player_hand_gun_run", "Assets/HandGunRun.png");
        TextureManager::GetInstance()->Load("player_hand_gun_attack", "Assets/HandGunAttack.png");
        TextureManager::GetInstance()->Load("player_hand_gun_reload", "Assets/HandGunReload.png");
        TextureManager::GetInstance()->Load("player_hand_gun_shoot", "Assets/HandGunShoot.png");
        TextureManager::GetInstance()->Load("player_knife_run", "Assets/KnifeRun.png");
        TextureManager::GetInstance()->Load("player_knife_attack", "Assets/KnifeAttack.png");
        TextureManager::GetInstance()->Load("player_knife_idle", "Assets/KnifeIdle.png");
        TextureManager::GetInstance()->Load("player_rife_run", "Assets/RifeRun.png");
        TextureManager::GetInstance()->Load("player_rife_attack", "Assets/RifeAttack.png");
        TextureManager::GetInstance()->Load("player_rife_idle", "Assets/RifeIdle.png");
        TextureManager::GetInstance()->Load("player_sg_run", "Assets/SgRun.png");
        TextureManager::GetInstance()->Load("player_sg_attack", "Assets/SgAttack.png");
        TextureManager::GetInstance()->Load("player_sg_idle", "Assets/SgIdle.png");
        TextureManager::GetInstance()->Load("zombie_idle", "Assets/ZombieIdle.png");
        TextureManager::GetInstance()->Load("zombie_run", "Assets/ZombieRun.png");
        TextureManager::GetInstance()->Load("zombie_attack", "Assets/ZombieAttack.png");
        TextureManager::GetInstance()->Load("bullet", "Assets/Bullet.png");

        SoundManager::GetInstance()->LoadSound("pistol", "Assets/pistolsound.wav");
        SoundManager::GetInstance()->LoadMusic("music", "Assets/nhacnen.mp3");
        SoundManager::GetInstance()->PlayMusic("music",-1);

        player = new Soilder(new Properties("player_knife", 960, 540, 305, 223));

        if (!m_Menu.Init(m_Renderer)) {
            SDL_Log("Menu Init Failed!");
            return false;
        }
        if (!m_GameOverMenu.Init(m_Renderer)) {
            SDL_Log("GameOverMenu Init Failed!");
            return false;
        }


        srand(time(0)); // Khởi tạo random
        for (int i = 0; i <= 10; i++)
            ZombieManager::GetInstance()->SpawnZombie();
        return m_IsRunning = true;

}

void Engine::Render() {
    SDL_RenderClear(m_Renderer);
    if (m_GameState == GameState::MENU) {
        m_Menu.Render();
        //m_GameOverMenu.Render();
    }
    else if (m_GameState == GameState::GAME_OVER) {
        m_GameOverMenu.Render();
    } else {
        SDL_Rect camera = Camera::GetInstance()->GetViewBox();
        TextureManager::GetInstance()->Draw("background", -camera.x, -camera.y, 1920, 1080);
        player->Draw();
        ZombieManager::GetInstance()->Draw();
        player->RenderHealthBar(Engine::GetInstance()->GetRenderer());
        BulletManager::GetInstance()->Draw();
    }

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
    if (m_GameState == GameState::MENU) {
        m_Menu.HandleInput();
    }
    else if (m_GameState == GameState::GAME_OVER) {
        m_GameOverMenu.HandleInput();
    } else {
        player->Update(0);
        Camera::GetInstance()->Update(player);
        ZombieManager::GetInstance()->Update(0.016f);
        BulletManager::GetInstance()->Update(0.016f);
    }
}
void Engine::RestartGame() {
    std::cout << "[INFO] Restarting game...\n";
    player->Reset();
    ZombieManager::GetInstance()->Clean();
    m_GameState = GameState::PLAYING;
}

