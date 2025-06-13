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


};

