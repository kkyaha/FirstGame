#ifndef POSITION_H
#define POSITION_H


class Position
{
    public:
        static Position& GetInstance() {
            static Position instance;
            return instance;
        }
        void SetPlayerPosition(float x, float y) {
            m_PlayerX = x;
            m_PlayerY = y;
            //m_Angle = angle;
        }

        float GetPlayerX() { return m_PlayerX; }
        float GetPlayerY() { return m_PlayerY; }

    private:
        Position() {} // Private constructor (Singleton)
        float m_PlayerX = 0.0f;
        float m_PlayerY = 0.0f;
        double m_Angle = 0;
};

#endif // POSITION_H
