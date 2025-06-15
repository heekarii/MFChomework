#include "pch.h"
#include "CMyCircle.h"

CMyCircle::CMyCircle(CPoint p, CPoint q)
{
	m_p = p;
	m_q = q;
	m_radius = 0; 
	m_isSelected = false;
	m_color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void CMyCircle::UpdatePoint(CPoint pt)
{
	m_q = pt;
	m_radius = sqrt((m_p.x - m_q.x) * (m_p.x - m_q.x) + (m_p.y - m_q.y) * (m_p.y - m_q.y));
	SetRect();
}

void CMyCircle::Draw(CDC *dc)
{
	CBrush brush(m_color);
	dc->SelectObject(brush);
	CPen pen(PS_SOLID, 1,m_color);
	dc->SelectObject(pen);

	dc->Ellipse(m_p.x - m_radius, m_p.y - m_radius, m_p.x + m_radius, m_p.y + m_radius);
}

void CMyCircle::Move(int dx, int dy)
{
	m_p.x += dx;
	m_q.x += dx;
	m_p.y += dy;
	m_q.y += dy;
}


