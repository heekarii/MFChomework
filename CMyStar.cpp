#include "pch.h"
#include "CMyStar.h"

CMyStar::CMyStar(CPoint p, CPoint q)
{
	m_r = 0;
	m_p = p;
	m_q = q;
	m_color = RGB(rand() % 256, rand() % 256, rand() % 256);
	m_isSelected = false;
	SetVertex();
}

void CMyStar::Draw(CDC *dc)
{
	CBrush brush(m_color);
	dc->SelectObject(brush);

	CPen pen(PS_SOLID, 1, m_color);
	dc->SelectObject(pen);

	CRgn rgn;
	rgn.CreatePolygonRgn(m_vertex, 10, ALTERNATE);
	dc->PaintRgn(&rgn);

	dc->MoveTo(m_vertex[0]);
	for (int i = 0; i < 10; i++)
		dc->LineTo(m_vertex[i]);
	dc->LineTo(m_vertex[0]);

}

void CMyStar::Move(int dx, int dy)
{
	m_p.x += dx;
	m_q.x += dx;
	m_p.y += dy;
	m_q.y += dy;
	SetVertex();
}

void CMyStar::UpdatePoint(CPoint pt)
{
	m_q = pt;
	m_r = sqrt((m_p.x - m_q.x) * (m_p.x - m_q.x) + (m_p.y - m_q.y) * (m_p.y - m_q.y));
	SetVertex();
}

void CMyStar::SetVertex()
{
	float outerRadius = m_r;            // �ܺ� ������
	float innerRadius = m_r / 2.5f;     // ���� ������ (�ʿ信 ���� ���� ����)
	float angleStep = 36 * (3.141592 / 180);     // 36���� �������� ��ȯ (360 / 5 = 72, �� ���� ����)

	// ù ��° �� ����
	CPoint outerPt = CPoint(0, outerRadius); // �߽ɿ��� �����Ͽ� ���� �̵�
	CPoint innerPt = CPoint(0, innerRadius); // �߽ɿ��� �����Ͽ� ���� �̵�
	float x = innerPt.x * cos(angleStep) - innerPt.y * sin(angleStep);
	float y = innerPt.x * sin(angleStep) + innerPt.y * cos(angleStep);
	innerPt = CPoint(x, y);

	for (int i = 0; i < 5; i++)
	{
		int step = i * 2; //2 4 6 8
		// 2���� ȸ�� ��ȯ ��� ����
		float outerX = outerPt.x * cos(angleStep * step) - outerPt.y * sin(angleStep * step);
		float outerY = outerPt.x * sin(angleStep * step) + outerPt.y * cos(angleStep * step);

		float innerX = innerPt.x * cos(angleStep * step) - innerPt.y * sin(angleStep * step);
		float innerY = innerPt.x * sin(angleStep * step) + innerPt.y * cos(angleStep * step);

		// ���� ������ ���
		m_vertex[i * 2] = CPoint(m_p.x + outerX, m_p.y - outerY); //0, 2, 4, 6, 8
		m_vertex[i * 2 + 1] = CPoint(m_p.x + innerX, m_p.y - innerY); //1, 3, 5, 7, 9
	}
}
