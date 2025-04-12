#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include <vector>
#include "Bullet.h"

class BulletManager
{
    public:
        static BulletManager* GetInstance() {
            if (!s_Instance) s_Instance = new BulletManager();
            return s_Instance;
        }
        void Update(float dt);
        void Draw();
        void FireBullet(float x, float y, float angle, BulletType type);
        void CheckCollisions();

    private:
        BulletManager() = default;
        static BulletManager* s_Instance;
        std::vector<Bullet*> m_Bullets;
        float m_LastFireTime = 0;  // Lưu thời gian viên đạn cuối cùng được bắn
        float m_FireDelay = 0.2f;   // 0.2 giây giữa các viên đạn
};

#endif // BULLETMANAGER_H
