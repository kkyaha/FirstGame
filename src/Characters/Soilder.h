#ifndef SOILDER_H
#define SOILDER_H

#include "Character.h"
#include "Animation.h"

class Soilder: public Character
{
    public:
        Soilder(Properties* props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

    protected:

    private:
        //int m_Row, m_Frame, m_FrameCount;
        //int m_AnimationSpeed;
        Animation* m_Animation;
};

#endif // SOILDER_H
