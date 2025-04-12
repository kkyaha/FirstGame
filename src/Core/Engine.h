#ifndef ENGINE_H
#define ENGINE_H

#include<SDL.h>
#include<SDL_image.h>
#include "Vector2D.h"
#include "Menu.h"
#include "GameOverMenu.h"
#include "Soilder.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1920
enum class GameState { MENU, PLAYING, EXIT, GAME_OVER };
class Engine {
public:
    static Engine* GetInstance(){
        if (s_Instance == nullptr) {
            s_Instance = new Engine();
        }
        return s_Instance;
    }
    void SetGameState(GameState state) { m_GameState = state; }
    GameState GetGameState() { return m_GameState; }
    bool Init();
    bool Clean();
    void Quit();
    void Update();
    void Render();
    void Events();
    void RestartGame();
    Soilder* GetPlayer() { return player; }
    inline bool IsRunning() { return m_IsRunning; }
    inline SDL_Renderer* GetRenderer() {return m_Renderer;}

private:
    Engine() : m_IsRunning(true) {}
    bool m_IsRunning;
    SDL_Window * m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
    Vector2D GetPlayerPosition();
    GameState m_GameState = GameState::MENU;  // Đảm bảo GameState đã khai báo
    Menu m_Menu;
    Soilder* player = nullptr;
    GameOverMenu m_GameOverMenu;
};

#endif // ENGINE_H
