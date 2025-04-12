#include "Engine.h"
#include <iostream>
int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();
    std::cout << "Starting game..." << std::endl;

    while (Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
    }

    Engine::GetInstance()->Clean();
    return 0;
}
