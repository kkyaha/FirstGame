#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>;
#include "SDL.h"

class Animation
{
    public:
        Animation(){}

        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight);
        void SetProps(std::string textureID, int SpriteRow, int FrameCount, int AnimationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        int m_SpriteRow, m_SpriteFrame;
        int m_AnimationSpeed, m_FrameCount;
        std::string m_TextureID;;
        SDL_RendererFlip m_Flip;
};

#endif // ANIMATION_H
