#pragma once
#include <vector>
class CMyShape
{
public:
	CPoint m_p;
	CPoint m_q;


	bool m_isSelected;

	COLORREF m_color;


	virtual CRect GetRect()
	{
		return CRect(m_p, m_q);
	}
	virtual void Draw(CDC *dc) = 0;
	virtual void UpdatePoint(CPoint pt) = 0;
	virtual void Move(int dx, int dy) = 0;
};

