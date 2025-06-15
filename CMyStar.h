#pragma once
#include "CMyShape.h"
class CMyStar :
    public CMyShape
{
public:
    CPoint m_vertex[10];
    int m_r;

    CMyStar(CPoint p, CPoint q);
    void Draw(CDC *dc) override;
    void Move(int dx, int dy) override;
    void UpdatePoint(CPoint pt);
    void SetVertex();
    void SetRect() override
    {
        m_rect = CRect(m_vertex[2].x, m_vertex[0].y, m_vertex[8].x, m_vertex[4].y);
    }
    CRect GetRect() override
    {
        SetRect();
        return m_rect;
    }
    int GetType() override { return 3; }

};

