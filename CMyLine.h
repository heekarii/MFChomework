#pragma once
#include "CMyShape.h"
#include <vector>
class CMyLine :
    public CMyShape
{
public:
    std::vector<CPoint> m_points;
    CMyLine(CPoint p);
    void UpdatePoint(CPoint pt) override;
    void Draw(CDC *dc) override;
    void Move(int dx, int dy) override;
    void SetRect() override
    {
		int x1 = m_points.front().x,
			x2 = m_points.front().x,
			y1 = m_points.front().y,
			y2 = m_points.front().y; //ÀÛÀº, Å«...

		for (auto &pt : m_points)
		{
			if (pt.x < x1)
				x1 = pt.x;
			if (pt.x > x2)
				x2 = pt.x;
			if (pt.y < y1)
				y1 = pt.y;
			if (pt.y > y2)
				y2 = pt.y;
		}
		m_rect = CRect(x1, y1, x2, y2);
    }
	CRect GetRect() override
	{
		SetRect();
		return m_rect;
	}
	bool PtInLine(CPoint point)
	{
		for (CPoint pt : m_points)
		{
			if (pt.x - 8 <= point.x && point.x <= pt.x + 8 &&
				pt.y - 8 <= point.y && point.y <= pt.y + 8		)
				return true;
		}
		return false;
	}
	int GetType() override { return 2; }
};

