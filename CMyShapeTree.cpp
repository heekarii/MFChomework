#include "pch.h"
#include "CMyShapeTree.h"

CMyShapeTree::CMyShapeTree()
{
	m_root = nullptr;
	m_childCount = 0;
	m_isSelected = false;
	m_weight  = 0;
}

CMyShapeTree::CMyShapeTree(CMyShape *root)
{
	m_root = root;
	m_childCount = 0;
	m_isSelected = false;
	m_weight = 0;
}

void CMyShapeTree::SetPoint()
{
	// ������ �ѷ��� �簢�� ��������
	m_outerBox = m_root->GetRect();
	// ���õ� ���� �� �����ֱ� ���� ���� ũ�� �ø���
	m_outerBox.left -= 5;
	m_outerBox.top -= 5;
	m_outerBox.right += 5;
	m_outerBox.bottom += 5;

	// ���õ� ������ �ڽ� ��带 ���� ���(�׷�ȭ�� �Ǿ��ִ� ���) ���� ��ü�� �ܰ� �簢�� 
	if (m_childCount > 0)
	{
		for (auto T : m_child)
		{
			m_outerBox.left = min(m_outerBox.left, T.m_outerBox.left);
			m_outerBox.top = min(m_outerBox.top, T.m_outerBox.top);
			m_outerBox.right = max(m_outerBox.right, T.m_outerBox.right);
			m_outerBox.bottom = max(m_outerBox.bottom, T.m_outerBox.bottom);
		}
	}

}

void CMyShapeTree::DrawShape(CDC *dc)
{
	// �ڽĵ��� ��� ��ȸ�ϸ� ���� �׸���, ��������� ����
	for (auto t : m_child)
		t.DrawShape(dc);

	m_root->Draw(dc);

	if (m_isSelected)
	{
		CPen pen(PS_DOT, 1, RGB(255, 0, 0));
		dc->SelectStockObject(NULL_BRUSH);
		dc->SelectObject(pen);
		dc->Rectangle(m_outerBox);
	}

}

void CMyShapeTree::Move(int dx, int dy)
{
	// ��� ��ȸ�ϸ鼭 ���� �̵�, ��������� ����
	m_root->Move(dx, dy);

	for (auto t : m_child)
		t.Move(dx, dy);

	m_outerBox.left += dx;
	m_outerBox.right += dx;
	m_outerBox.top += dy;
	m_outerBox.bottom += dy;

}
