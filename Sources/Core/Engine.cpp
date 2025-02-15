#include "Engine.h"
#include <iostream>
using namespace std;

Engine* Engine::s_Instance = nullptr;

bool Engine::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0 and IMG_Init(IMG_INIT_JPG or IMG_INIT_PNG) != 0) {
        SDL_Log("Fail", SDL_GetError());
        return false;
    }
    return m_IsRunning = true;
}

bool Engine::Clean() {

}

void Engine::Quit() {

}

void Engine::Update() {
    SDL_Log("ok");
}

void Engine::Render() {

}

void Engine::Events() {

}


