#include "Zombie.h"
#include "Soilder.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Animation.h"
#include "Camera.h"
#include "Engine.h"
#include "ZombieManager.h"
#include <cmath>


Zombie::Zombie(Properties* props): Character(props)
{
    m_X = props->X;
    m_Y = props->Y;
    m_Width = props->Width;
    m_Height = props->Height;
    m_Animation = new Animation();
    m_Animation->SetProps("zombie_run", 0, 16, 50);
    m_Angle = 0;
    m_Speed = 1.25;
    m_Health = 100;
    player = Engine::GetInstance()->GetPlayer();
    std::cout << "Zombie initialized at (" << m_X << ", " << m_Y << ")" << std::endl;
}

void Zombie::SetState(ZombieState newState) {
    if (m_State == newState) return;
    m_State = newState;

    if (m_State == WALKING) {
         m_Animation->SetProps("zombie_run", 0, 16, 60);
    } else if (m_State == ATTACKING) {
        m_Animation->SetProps("zombie_attack", 0, 8, 70);
    }
}

void Zombie::TakeDamage(float damage) {
    m_Health -= damage;
    std::cout << "Zombie took " << damage << " damage! Remaining health: " << m_Health << "\n";
}

void Zombie::Update(float dt) {
    float playerX = Position::GetInstance().GetPlayerX();
    float playerY = Position::GetInstance().GetPlayerY();
    float dx = playerX - m_Transform->X-100;
    float dy = playerY - m_Transform->Y-50;
    float distance = sqrt(dx * dx + dy * dy);
    if (distance < MELEE_ATTACK_RANGE) {
        // Nếu zombie có thể tấn công, kiểm tra cooldown
        float currentTime = SDL_GetTicks() / 1000.0f;
        if (currentTime - lastAttackTime >= MELEE_ATTACK_INTERVAL) {
            if (player) player->TakeDamage(20); // Gây sát thương lên nhân vật
            lastAttackTime = currentTime;
            SetState(ATTACKING);
            std::cout << "[DEBUG] Zombie hit soldier.\n";
        }
    } else {
        // Di chuyển về phía nhân vật nếu chưa đủ gần
        if(distance > 45.0f)
        {
            SetState(WALKING);
            m_Transform->TranslateX((dx / distance) * m_Speed);
            m_Transform->TranslateY((dy / distance) * m_Speed);
        }
    }

    float angleRad = atan2(dy, dx);
    m_Angle = angleRad * 180 / M_PI;

    m_Animation->Update();
}



void Zombie::Draw() {
    m_Animation->Draw(m_Transform->X - Camera::GetInstance()->GetX(),
                      m_Transform->Y - Camera::GetInstance()->GetY(),
                      m_Width, m_Height, m_Angle);
    //SDL_Rect hitbox = GetCollisionRect(); // Hàm này trả về hitbox của zombie theo tọa độ thế giới
    //hitbox.x -= Camera::GetInstance()->GetX();
    //hitbox.y -= Camera::GetInstance()->GetY();

    //SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 255);
    //SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &hitbox);
}

void Zombie::PushBack(float dirX, float dirY, float force) {
    float length = sqrt(dirX * dirX + dirY * dirY);
    if (length > 0) {
        dirX /= length;
        dirY /= length;
    }

    m_Transform->TranslateX(dirX * force);
    m_Transform->TranslateY(dirY * force);
}

void Zombie::Clean()
{

}
