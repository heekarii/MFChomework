#pragma once
#include "CMyShape.h"
#include "pch.h"

class CMyRect :
    public CMyShape
{
public:
    int m_width, m_height;
    CMyRect(CPoint p, CPoint q);
    void UpdatePoint(CPoint pt) override;
    void Draw(CDC *dc) override;
    void Move(int dx, int dy) override;
    void SetRect() override
    {
        if (m_p.x > m_q.x) std::swap(m_p.x, m_q.x);
        if (m_p.y > m_q.y) std::swap(m_p.y, m_q.y);
        m_rect = CRect(m_p, m_q);
    }
    CRect GetRect() override
    {
        SetRect();
        return m_rect;
    }
    int GetType() override { return 0; }
};

