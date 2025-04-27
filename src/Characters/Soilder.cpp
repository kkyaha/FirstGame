#include "Soilder.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Animation.h"
#include "Input.h"
#include <cmath>
#include "Camera.h"
#include "Position.h"
#include "Engine.h"
#include "BulletManager.h"
#include "Zombie.h"
#include "ZombieManager.h"
#include "SoundManager.h"

Soilder::Soilder(Properties* props): Character(props) {
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 20, 80, SDL_FLIP_HORIZONTAL);
    m_Speed = 5;
    m_Angle = 0;
    m_WeaponID = 1;
    m_Health = 100;
    m_Transform->X = 960;
    m_Transform->Y = 540;
}

void Soilder::RenderHealthBar(SDL_Renderer* renderer) {
    int barWidth = 200;
    int barHeight = 20;
    int x = 80;
    int y = 30;

    float healthPercent = static_cast<float>(m_Health) / 100;
    int currentWidth = static_cast<int>(barWidth * healthPercent);

    // Vẽ nền thanh máu (xám)
    SDL_Rect background = {x, y, barWidth, barHeight};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &background);

    // Vẽ phần máu (đỏ)
    SDL_Rect foreground = {x, y, currentWidth, barHeight};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &foreground);

    // Viền đen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &background);

    TTF_Font* font = TTF_OpenFont("Assets/kky.ttf", 24);
    if (font) {
        SDL_Color white = {255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, "HP:", white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        int textW, textH;
        SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
        SDL_Rect textRect = {x - textW - 10, y + (barHeight - textH) / 2, textW, textH};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }
}


void Soilder::Draw() {
    int renderX = m_Transform->X - Camera::GetInstance()->GetX() - 100;
    int renderY = m_Transform->Y - Camera::GetInstance()->GetY() - 50;

    m_Animation->Draw(renderX, renderY, m_Width, m_Height, m_Angle);
    RenderHealthBar(Engine::GetInstance()->GetRenderer());
}

void Soilder::MeleeAttack() {
    SDL_Rect soldierAttackBox = {
        (int)(m_Transform->X - 50), // Phạm vi tấn công bên trái
        (int)(m_Transform->Y - 50), // Phạm vi tấn công phía trên
        100, 100 // Kích thước vùng tấn công
    };
    static float lastAttackTime = 0;
    float currentTime = SDL_GetTicks() / 1000.0f; // Thời gian hiện tại
    if (currentTime - lastAttackTime < 0.5f) // Cooldown 0.5 giây
        return;
    lastAttackTime = currentTime; // Cập nhật thời gian cận chiến

    for (auto& zombie : ZombieManager::GetInstance()->GetZombies()) {
        SDL_Rect zombieBox = zombie->GetCollisionRect();

        if (SDL_HasIntersection(&soldierAttackBox, &zombieBox)) {
            zombie->TakeDamage(10);
            float dx = zombie->GetX() - m_Transform->X;
            float dy = zombie->GetY() - m_Transform->Y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance > 0.0f) {
                float pushX = (dx / distance);
                float pushY = (dy / distance);
                zombie->PushBack(pushX, pushY, 50.0f);
            }
        }
    }
}

void Soilder::Update(float dt) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int gameMouseX = mouseX + Camera::GetInstance()->GetX();
    int gameMouseY = mouseY + Camera::GetInstance()->GetY();

    int centerX = m_Transform->X + (m_Width / 2);
    int centerY = m_Transform->Y + (m_Height / 2);

    float angleRad = atan2(gameMouseY - centerY, gameMouseX - centerX);
    m_Angle = angleRad * 180 / M_PI;

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

    switch (m_WeaponID) {
        case 1: m_TextureID = "player_knife"; break;
        case 2: m_TextureID = "player_hand_gun"; break;
        case 3: m_TextureID = "player_rife"; break;
        case 4: m_TextureID = "player_sg"; break;
        default: m_TextureID = "player_knife"; break;
    }

    bool isMoving = false;

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
        if(m_Transform->Y > 50)
            m_Transform->TranslateY(-m_Speed);
        isMoving = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        if(m_Transform->X > 50)
            m_Transform->TranslateX(-m_Speed);
        isMoving = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        if(m_Transform->Y < 1030)
            m_Transform->TranslateY(m_Speed);
        isMoving = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        if(m_Transform->X < 1870)
            m_Transform->TranslateX(m_Speed);
        isMoving = true;
    }

    if (isMoving) {
        m_Animation->SetProps(m_TextureID + "_run", 0, 20, 20);
    }
    else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_Animation->SetProps(m_TextureID + "_attack", 0, 15, 40);
        MeleeAttack();
    }
    else {
        m_Animation->SetProps(m_TextureID + "_idle", 0, 20, 20);
    }

    if (Input::GetInstance()->GetMouseButtonDown(SDL_BUTTON_LEFT))
    {
        if(m_WeaponID == 2)
        {
            BulletManager::GetInstance()->FireBullet(m_Transform->X, m_Transform->Y, m_Angle, BulletType::PISTOL);
            SoundManager::GetInstance()->PlaySound("gun", -1);
        }
        if(m_WeaponID == 3)
            BulletManager::GetInstance()->FireBullet(m_Transform->X, m_Transform->Y, m_Angle, BulletType::RIFE);
        if(m_WeaponID == 4)
            BulletManager::GetInstance()->FireBullet(m_Transform->X, m_Transform->Y, m_Angle, BulletType::SHOTGUN);
    }
    Position::GetInstance().SetPlayerPosition(m_Transform->X, m_Transform->Y);
    m_Animation->Update();
}

void Soilder::Clean() {
    TextureManager::GetInstance()->Clean();
    SDL_Log("Soilder cleaned up");
}

void Soilder::TakeDamage(int damage) {
    m_Health -= damage;
    std::cout << "[DEBUG] Nhân vật bị tấn công! Máu còn lại: " << m_Health << std::endl;
    if (m_Health <= 0) {
        std::cout << "[DEBUG] Nhân vật đã chết!\n";
        Engine::GetInstance()->SetGameState(GameState::GAME_OVER);
    }
}

void Soilder::Reset() {
    m_Health = 100; // Reset máu
    m_Transform->X = 960;
    m_Transform->Y = 540;
}
