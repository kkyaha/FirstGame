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

void BulletManager::FireBullet(float x, float y, float angle, BulletType type) {
    float currentTime = SDL_GetTicks() / 1000.0f;
    if (currentTime - m_LastFireTime < m_FireDelay) return;
    m_LastFireTime = currentTime;

    // Lấy tọa độ từ nhân vật

    // Tính toán vị trí nòng súng
    float offsetX = cos(angle * M_PI / 180.0f) * 50;
    float offsetY = sin(angle * M_PI / 180.0f) * 50;

    // Khởi tạo đạn ở vị trí nhân vật
    m_Bullets.push_back(new Bullet(x + offsetX - Camera::GetInstance()->GetX(), y + offsetY -Camera::GetInstance()->GetY(), angle, type));
}

bool ZombieManager::CheckBulletCollision(Bullet* bullet) {
    SDL_Rect bulletRect = bullet->GetCollisionRect(); // Tọa độ thế giới
    for (auto& zombie : m_Zombies) {
        SDL_Rect zombieRect = zombie->GetCollisionRect(); // Tọa độ thế giới
        if (SDL_HasIntersection(&bulletRect, &zombieRect)) {
            std::cout << "[DEBUG] Collision detected: Bullet at ("
                      << bullet->GetX() << ", " << bullet->GetY()
                      << ") vs Zombie at (" << zombie->GetX() << ", " << zombie->GetY() << ")\n";
            float bulletDx = bullet->GetDirectionX();
            float bulletDy = bullet->GetDirectionY();
            zombie->PushBack(bulletDx, bulletDy, 20.0f);
            zombie->TakeDamage(bullet->GetDamage());
            return true;
        }
    }
    return false;
}



