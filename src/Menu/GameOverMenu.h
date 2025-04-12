#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

#include "Menu.h"

class GameOverMenu : public Menu {
public:
    GameOverMenu();
    bool Init(SDL_Renderer* renderer) ;
    void HandleInput() ;
    void Render() ;
    void Clean();

private:
    SDL_Texture* m_GameOverTexture;
    SDL_Rect m_GameOverRect;
};

#endif
