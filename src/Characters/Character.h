#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include <string>

class Character: public GameObject
{
    public:
        Character(Properties* props): GameObject(props) {
             m_X = props->X;
             m_Y = props->Y;
        }
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
        float GetX() { return m_X; }
        float GetY() { return m_Y; }

    protected:
        std::string m_Name;
        float m_X, m_Y;
};

#endif // CHARACTER_H
