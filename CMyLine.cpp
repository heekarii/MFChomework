#include "pch.h"
#include "CMyLine.h"

CMyLine::CMyLine(CPoint p)
{
	m_p = p;
	m_points.push_back(p);
	m_isSelected = false;
	m_color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void CMyLine::UpdatePoint(CPoint pt)
{
	m_points.push_back(pt);
}

void CMyLine::Draw(CDC *dc)
{
	CPen pen(PS_SOLID, 3, m_color);
	dc->SelectObject(pen);
	dc->MoveTo(m_points[0]);
	for (int i = 0; i < m_points.size(); i++)
	{
		dc->LineTo(m_points[i]);
	}
}

void CMyLine::Move(int dx, int dy)
{
	for (auto &pt : m_points)
	{
		pt.x += dx;
		pt.y += dy;
	}
}
