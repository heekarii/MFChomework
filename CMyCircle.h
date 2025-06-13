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
};

