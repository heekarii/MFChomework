#pragma once
#include "CMyShape.h"
class CMyCircle :
    public CMyShape
{
public:
    int m_radius;
    CMyCircle(CPoint p, CPoint q);
    void UpdatePoint(CPoint pt) override;
    void Draw(CDC *dc) override;
    void Move(int dx, int dy) override;
    void SetRect() override
    {
        m_rect = CRect(m_p.x - m_radius, m_p.y - m_radius, m_p.x + m_radius, m_p.y + m_radius);
    }
    CRect GetRect() override
    {
        SetRect();
        return m_rect;
    }
    int GetType() override { return 1; }
};

