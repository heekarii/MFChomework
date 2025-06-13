#include "pch.h"
#include "CMyRect.h"

CMyRect::CMyRect(CPoint p, CPoint q)
{
    m_p = p;
    m_q = q;
    m_width = 0;
    m_height = 0;
    m_isSelected = false;
    m_color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void CMyRect::UpdatePoint(CPoint pt)
{
    m_q = pt;
    m_width = abs(m_p.x - m_q.x);
    m_height = abs(m_p.y - m_q.y);
}

void CMyRect::Draw(CDC *dc)
{
    CBrush brush(m_color);
    dc->SelectObject(brush);

    dc->Rectangle(m_p.x, m_p.y, m_q.x, m_q.y);
}

void CMyRect::Move(int dx, int dy)
{
    m_p.x += dx;
    m_q.x += dx;
    m_q.y += dy;
    m_q.y += dy;
}
