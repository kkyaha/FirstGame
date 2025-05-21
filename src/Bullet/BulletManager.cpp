#include "BulletManager.h"
#include "ZombieManager.h"
#include "Bullet.h"
#include "Soilder.h"
#include "Engine.h"
#include "Camera.h"
#include <cmath>

void BulletManager::Update(float dt) {
    for (auto it = m_Bullets.begin(); it != m_Bullets.end();) {
        (*it)->Update(dt);

        bool collision = ZombieManager::GetInstance()->CheckBulletCollision(*it);
        if (collision || !(*it)->IsActive()) {
            if (collision) {
                std::cout << "[DEBUG] Bullet hit zombie! (Damage: " << (*it)->GetDamage() << ")\n";
            }
            delete *it;
            it = m_Bullets.erase(it);
        } else {
            ++it;
        }
    }
}


void BulletManager::Draw() {
    for (auto& bullet : m_Bullets) {
        bullet->Draw();
    }
}

void BulletManager::FireBullet(float x, float y, float angle, BulletType type, float m_FireDelay) {
    float currentTime = SDL_GetTicks() / 1000.0f;
    if (currentTime - m_LastFireTime < m_FireDelay) return;
    m_LastFireTime = currentTime;

    // Tính offset vị trí đầu nòng súng
    float barrelLength = 60.0f; // chiều dài từ tâm nhân vật đến đầu súng
    float offsetX = cos(angle * M_PI / 180.0f) * (barrelLength)-55;
    float offsetY = sin(angle * M_PI / 180.0f) * (barrelLength);

    // Tính vị trí đạn bắt đầu (toạ độ thế giới - KHÔNG trừ Camera)
    float bulletX = x + offsetX;
    float bulletY = y + offsetY;

    // Tạo đạn
    m_Bullets.push_back(new Bullet(bulletX, bulletY, angle, type));
}


bool ZombieManager::CheckBulletCollision(Bullet* bullet) {
    SDL_Rect bulletRect = bullet->GetCollisionRect(); // Tọa độ thế giới
    for (auto& zombie : m_Zombies) {
        SDL_Rect zombieRect = zombie->GetCollisionRect(); // Tọa độ thế giới
        if (SDL_HasIntersection(&bulletRect, &zombieRect)) {
            float bulletDx = bullet->GetDirectionX();
            float bulletDy = bullet->GetDirectionY();
            zombie->PushBack(bulletDx, bulletDy, 20.0f);
            zombie->TakeDamage(bullet->GetDamage());
            return true;
        }
    }
    return false;
}



