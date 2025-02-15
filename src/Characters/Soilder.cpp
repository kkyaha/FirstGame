#include "Soilder.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Animation.h"
#include "Input.h"
#include <cmath>

Soilder::Soilder(Properties* props): Character(props)
{
    m_Animation = new Animation();
    //m_TextureID = "player";
    m_Animation->SetProps(m_TextureID, 0, 20, 80, SDL_FLIP_HORIZONTAL);
    m_Speed = 0.9;
    m_Angle = 0;
    m_WeaponID = 1;
}

void Soilder::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Angle);
    //SDL_Log("Drawing at: X = %f, Y = %f, Width = %d, Height = %d",
        //m_Transform->X, m_Transform->Y, m_Width, m_Height);
    //SDL_Log("🔍 TextureID của Soilder: %s", m_TextureID.c_str());

}

void Soilder::Update(float dt)
{
    //m_Animation->SetProps("player", 0, 20, 30);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    m_Angle = atan2(mouseY - m_Transform->Y, mouseX - m_Transform->X) * 180.0 / M_PI;

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_1)) {
        m_WeaponID = 1;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_2)) {
        m_WeaponID = 2;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_3)) {
        m_WeaponID = 3;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_4)) {
        m_WeaponID = 4;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_5)) {
        m_WeaponID = 5;
    }

    //std::string playerSprite;
    switch (m_WeaponID) {
        case 1: m_TextureID = "player"; break;
        case 2: m_TextureID = "player_knife"; break;
        case 3: m_TextureID = "player_hand_gun"; break;
        case 4: m_TextureID = "player_rife"; break;
        case 5: m_TextureID = "player_sg"; break;
        default: m_TextureID = "player"; break;
    }

    bool isMoving = false;

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
        m_Transform->TranslateY(-m_Speed);
        isMoving = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_Transform->TranslateX(-m_Speed);
        isMoving = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        m_Transform->TranslateY(m_Speed);
        isMoving = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_Transform->TranslateX(m_Speed);
        isMoving = true;
    }

    if (isMoving) {
        m_Animation->SetProps(m_TextureID + "_run", 0, 20, 20);
    }
    else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_Animation->SetProps(m_TextureID + "_attack", 0, 15, 30);
    }
    else {
        m_Animation->SetProps(m_TextureID + "_idle", 0, 20, 20);
    }

    m_Animation->Update();
}
void Soilder::Clean()
{
    TextureManager::GetInstance()->Clean();
}
