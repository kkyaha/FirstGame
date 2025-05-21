#ifndef ZOMBIEMANAGER_H
#define ZOMBIEMANAGER_H
#include "Bullet.h"
#include "Zombie.h"
#include <vector>

class ZombieManager {
public:
    static ZombieManager* GetInstance() {
        if (!s_Instance) s_Instance = new ZombieManager();
        return s_Instance;
    }
    inline bool CheckBulletCollision(Bullet* bullet);
    void Update(float dt);
    void Draw();
    void SpawnZombie();
    void Clean();
    void IncreaseDifficulty();
    std::vector<Zombie*>& GetZombies() { return m_Zombies; }

private:
    ZombieManager() {}
    static ZombieManager* s_Instance;
    std::vector<Zombie*> m_Zombies;
    float m_LastSpawnTime;
    float m_SpawnInterval = 0.5f;
    float m_TimeElapsed;
    int m_MaxZombies = 50;
};

#endif // ZOMBIEMANAGER_H
