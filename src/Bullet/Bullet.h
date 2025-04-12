#pragma once
#include <iostream>
#include "Animation.h"

enum class BulletType { PISTOL, RIFE, SHOTGUN };

class Bullet {
public:
    SDL_Rect GetCollisionRect() const {
        SDL_Rect rect;
        // Giả sử m_X, m_Y là tọa độ đạn đã tính offset, và sprite có kích thước 64x64.
        // Nếu bạn muốn căn giữa hitbox, giảm kích thước hitbox nếu sprite có khoảng trống\n
        rect.x = static_cast<int>(m_X) - 15; // Căn giữa theo sprite 64x64
        rect.y = static_cast<int>(m_Y) - 15;
        rect.w = 30;
        rect.h = 30;
        return rect;
    }

    Bullet(float x, float y, float angle, BulletType type);
    void Update(float dt);
    void Draw();
    bool IsActive() const { return m_Active; }

    float GetX() const { return m_X; }
    float GetY() const { return m_Y; }
    float GetDamage() const { return m_Damage; }
    float m_DirectionX; // Hướng theo trục X
    float m_DirectionY; // Hướng theo trục Y
    float GetDirectionX() const { return m_DirectionX; }
    float GetDirectionY() const { return m_DirectionY; }

private:
    float m_X, m_Y;
    float m_Angle;
    float m_Speed;
    float m_Damage;
    bool m_Active;
    Animation* m_Animation;

};
