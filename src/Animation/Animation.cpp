#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks()/m_AnimationSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, double angle)
{

    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip, angle);
    //SDL_Log("🎞️ Frame hiện tại: %d / Tổng Frame: %d", m_SpriteFrame, m_FrameCount);
}

void Animation::SetProps(std::string textureID, int SpriteRow, int FrameCount, int AnimationSpeed, SDL_RendererFlip flip, double angle)
{
    m_TextureID = textureID;
    m_SpriteRow = SpriteRow;
    m_FrameCount = FrameCount;
    m_AnimationSpeed = AnimationSpeed;
    m_Flip = flip;
    m_Angle = angle;
}
