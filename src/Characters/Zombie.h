#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Character.h"
#include "Soilder.h"
#include "Position.h"
enum ZombieState { WALKING, ATTACKING };
class Zombie : public Character
{
    public:
        SDL_Rect GetCollisionRect() const {
            SDL_Rect rect;
            // Giả sử m_Width và m_Height được cập nhật theo kích thước của sprite zombie.
            rect.x = static_cast<int>(m_Transform->X);
            rect.y = static_cast<int>(m_Transform->Y);
            rect.w = m_Width-200;
            rect.h = m_Height-200;
            return rect;
        }
        Zombie(Properties* props);
        void Update(float dt) override;
        void Draw() override;
        void Clean() override;
        void TakeDamage(float damage);
        bool IsDead() const { return m_Health <= 0; }
        float GetX() const { return m_X; }
        float GetY() const { return m_Y; }
        float GetWidth() const { return m_Width; }
        float GetHeight() const { return m_Height; }
        void SetState(ZombieState newState);
        void PushBack(float dirX, float dirY, float force);
        const int MELEE_ATTACK_RANGE = 50; // Khoảng cách tối đa để zombie có thể tấn công cận chiến
        const float MELEE_ATTACK_INTERVAL = 1.5f; // Thời gian giữa các đợt tấn công

    private:
        float m_Speed;
        double m_Angle;
        Animation* m_Animation;
        float m_X, m_Y;
        float m_Width, m_Height;
        int m_Health;

        float lastAttackTime = 0.0f;
        ZombieState m_State;
        Soilder* player;
};

#endif // ZOMBIE_H
