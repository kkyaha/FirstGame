#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Input
{
    public:
        static Input* GetInstance(){
        if (s_Instance == nullptr) {
            s_Instance = new Input();
        }
        return s_Instance;
    }
    void Listen();
    bool GetKeyDown(SDL_Scancode key);

    private:
        Input();
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyStates;
        static Input* s_Instance;
};

#endif // INPUT_H
