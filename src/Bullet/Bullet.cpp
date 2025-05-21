#include "Bullet.h"
#include "Soilder.h"
#include "BulletManager.h"
#include "Engine.h"
#include "Camera.h"
#include <cmath>

Bullet::Bullet(float x, float y, float angle, BulletType type): m_X(x), m_Y(y), m_Angle(angle), m_Active(true)
{
    m_Animation = new Animation();
    m_Animation->SetProps("bullet", 0, 1, 1);
    m_DirectionX = cos(angle * M_PI / 180.0f);
    m_DirectionY = sin(angle * M_PI / 180.0f);
    switch (type) {
        case BulletType::PISTOL:
            m_Speed = 400.0f;
            m_Damage = 20.0f; // Pistol gây 10 damage
            //m_Animation->SetProps("bullet", 0, 1, 1);
            break;
        case BulletType::RIFE:
            m_Speed = 500.0f;
            m_Damage = 30.0f; // Rifle gây 20 damage
            //m_Animation->SetProps("bullet", 0, 1, 1);
            break;
        case BulletType::SHOTGUN:
            m_Speed = 400.0f;
            m_Damage = 40.0f;  // Shotgun gây 30 damage
            //m_Animation->SetProps("bullet", 0, 1, 1);
            break;
    }
}

void Bullet::Update(float dt) {

    float angleRad = m_Angle * M_PI / 180.0f;
    float velocityX = cos(angleRad) * m_Speed * dt;
    float velocityY = sin(angleRad) * m_Speed * dt;

    m_X += velocityX;
    m_Y += velocityY;

    // Xóa đạn khi ra khỏi màn hình
    if (m_X < 0 || m_X > 4090 || m_Y < 0 || m_Y > 3890)
        m_Active = false;

}

void Bullet::Draw()
{
    float camX = Camera::GetInstance()->GetX();
    float camY = Camera::GetInstance()->GetY();

    // Vẽ đạn ở vị trí đã trừ camera
    m_Animation->Draw(m_X - camX, m_Y - camY, 64, 64, m_Angle - 180);

    // Vẽ hitbox cũng trừ camera để trùng với sprite
    //SDL_Rect rect = GetCollisionRect();
    //rect.x -= (int)camX;
    //rect.y -= (int)camY;

    //SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 255);
    //SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &rect);
}

