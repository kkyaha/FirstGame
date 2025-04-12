#include "Camera.h"

Camera*Camera::s_Instance = nullptr;

Camera::Camera()
{
    m_ViewBox = {0, 0, 1920, 1080};
}

void Camera::Update(Soilder* target)
{
    if(target)
    {
        m_ViewBox.x = target->GetX() - (m_ViewBox.w / 2);
        m_ViewBox.y = target->GetY() - (m_ViewBox.h / 2);

        if(m_ViewBox.x < 0) m_ViewBox.x = 0;
        if(m_ViewBox.y < 0) m_ViewBox.y = 0;
        if (m_ViewBox.x > 1920 - m_ViewBox.w) m_ViewBox.x = 1920 - m_ViewBox.w;
        if (m_ViewBox.y > 1020 - m_ViewBox.h) m_ViewBox.y = 1080 - m_ViewBox.h;
    }
}
