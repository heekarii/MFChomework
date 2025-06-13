#include "pch.h"
#include "CMyLine.h"

CMyLine::CMyLine(CPoint p, CPoint q)
{
	m_p = p;
	m_q = q;
	m_points.push_back(p);
	m_points.push_back(q);
	m_isSelected = false;
	m_color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void CMyLine::UpdatePoint(CPoint pt)
{
	m_q = pt;
	m_points.push_back(m_q);
}

void CMyLine::Draw(CDC *dc)
{
	CPen pen(PS_SOLID, 3, m_color);
	dc->SelectObject(pen);
	for (int i = 0; i < m_points.size() - 1; i++)
	{
		dc->MoveTo(m_points[i]);
		dc->LineTo(m_points[i + 1]);
		 
	}
}

void CMyLine::Move(int dx, int dy)
{
	m_p.x += dx;
	m_q.x += dx;
	m_p.y += dy;
	m_q.y += dy;
}
