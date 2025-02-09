#include "Soilder.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Animation.h"

Soilder::Soilder(Properties* props):  Character(props)
{
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 20, 80, SDL_FLIP_VERTICAL);
}

void Soilder::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    SDL_Log("Drawing at: X = %f, Y = %f, Width = %d, Height = %d",
        m_Transform->X, m_Transform->Y, m_Width, m_Height);
    SDL_Log("🔍 TextureID của Soilder: %s", m_TextureID.c_str());

}

void Soilder::Update(float dt)
{
    m_Animation->Update();
}

void Soilder::Clean()
{
    TextureManager::GetInstance()->Clean();
}
