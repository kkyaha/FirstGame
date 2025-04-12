#ifndef SOILDER_H
#define SOILDER_H

#include "Character.h"
#include "Animation.h"

class Soilder: public Character
{
    public:
        Soilder(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
    public:
        float GetX() { return m_Transform->X; }
        float GetY() { return m_Transform->Y; }
        float GetAngle() { return m_Angle; }
        void TakeDamage(int damage);
        void Reset();
        void MeleeAttack();
        void RenderHealthBar(SDL_Renderer* renderer);

    private:
        //int m_Row, m_Frame, m_FrameCount;
        //int m_AnimationSpeed;
        int m_WeaponID;
        float m_Speed;
        double m_Angle;
        Animation* m_Animation;
        int m_Health;
};

#endif // SOILDER_H
