#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Soilder.h"

class Camera
{
    public:
        inline static Camera* GetInstance(){
            if (s_Instance == nullptr) {
                s_Instance = new Camera();
            }
            return s_Instance;
        }

    void Update(Soilder* target);
    SDL_Rect GetViewBox() { return m_ViewBox;}

    int GetX() {return m_ViewBox.x;}
    int GetY() {return m_ViewBox.y;}

    private:
        Camera();
        SDL_Rect m_ViewBox;
        static Camera* s_Instance;
};

#endif // CAMERA_H
