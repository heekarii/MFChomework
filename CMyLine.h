#pragma once
#include "CMyShape.h"
#include <vector>
class CMyLine :
    public CMyShape
{
public:
    std::vector<CPoint> m_points;
    CMyLine(CPoint p, CPoint q);
    void UpdatePoint(CPoint pt) override;
    void Draw(CDC *dc) override;
    void Move(int dx, int dy) override;

};

