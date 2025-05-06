#include "ZombieManager.h"
#include "Zombie.h"
#include "Camera.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

void ZombieManager::Update(float dt) {
    float currentTime = SDL_GetTicks() / 1000.0f;
    m_TimeElapsed = currentTime; // Cập nhật thời gian chơi
    // Tăng độ khó sau mỗi 30 giây
    if (static_cast<int>(m_TimeElapsed) % 30 == 0) {
        IncreaseDifficulty();
    }
    // Kiểm tra nếu số zombie chưa vượt quá giới hạn và đủ thời gian để spawn
    if ((m_Zombies.size() < m_MaxZombies) && (currentTime - m_LastSpawnTime >= m_SpawnInterval)) {
        SpawnZombie();
        m_LastSpawnTime = currentTime;
    }

    // Cập nhật từng zombie
    for (auto& zombie : m_Zombies) {
        zombie->Update(dt);
    }
    for (auto it = m_Zombies.begin(); it != m_Zombies.end();) {
        if ((*it)->IsDead()) {
            std::cout << "Deleting zombie at (" << (*it)->GetX() << ", " << (*it)->GetY() << ")" << std::endl;
            delete *it;
            it = m_Zombies.erase(it);
        } else {
            ++it;
        }
    }
}

void ZombieManager::Draw() {
    for (auto& zombie : m_Zombies) {
        zombie->Draw();
    }
}

void ZombieManager::SpawnZombie() {
    int x, y;
    int side = rand() % 4;

    switch (side) {
        case 0:
            x = rand() % 4044;
            y = -20;
            break;
        case 1:
            x = rand() % 4044;
            y = 3900;
            break;
        case 2:
            x = -20;
            y = rand() % 3890;
            break;
        case 3:
            x = 4054;
            y = rand() % 3890;
            break;
    }
    Zombie* zombie = new Zombie(new Properties("zombie_idle", x, y, 318, 294));

    m_Zombies.push_back(zombie);
    std::cout << "Spawned zombie at (" << x << ", " << y << ")" << std::endl;
}

void ZombieManager::Clean() {
    for (auto& zombie : m_Zombies) {
        delete zombie;
    }
    m_Zombies.clear();
}

void ZombieManager::IncreaseDifficulty() {
    if (m_MaxZombies < 100) { // Giới hạn tối đa 50 zombie trên màn hình
        m_MaxZombies += 2;   // Mỗi 30 giây, tăng 2 zombie tối đa
    }

    if (m_SpawnInterval > 1.0f) { // Không giảm dưới 1 giây
        m_SpawnInterval *= 0.9f;  // Giảm 10% thời gian spawn mỗi 30 giây
    }

    SDL_Log("Increased difficulty! Max Zombies: %d, Spawn Interval: %.2f", m_MaxZombies, m_SpawnInterval);
}

