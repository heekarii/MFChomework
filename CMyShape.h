#pragma once
#include <vector>
class CMyShape
{
public:
	CPoint m_p;
	CPoint m_q;


	bool m_isSelected;

	COLORREF m_color;

	CRect m_rect; // Å×µÎ¸®

	virtual void SetRect() = 0;
	virtual CRect GetRect() = 0;
	virtual void Draw(CDC *dc) = 0;
	virtual void UpdatePoint(CPoint pt) = 0;
	virtual void Move(int dx, int dy) = 0;
	virtual int GetType() = 0;
};

