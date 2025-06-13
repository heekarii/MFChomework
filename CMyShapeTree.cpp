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
	// 도형을 둘러싼 사각형 가져오기
	m_outerBox = m_root->GetRect();
	// 선택된 것을 잘 보여주기 위해 도형 크기 늘리기
	m_outerBox.left -= 5;
	m_outerBox.top -= 5;
	m_outerBox.right += 5;
	m_outerBox.bottom += 5;

	// 선택된 도형이 자식 노드를 가진 경우(그룹화가 되어있는 경우) 도형 전체에 외곽 사각형 
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
	// 자식들을 모두 순회하며 도형 그리기, 재귀적으로 구현
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
	// 노드 순회하면서 도형 이동, 재귀적으로 구현
	m_root->Move(dx, dy);

	for (auto t : m_child)
		t.Move(dx, dy);

	m_outerBox.left += dx;
	m_outerBox.right += dx;
	m_outerBox.top += dy;
	m_outerBox.bottom += dy;

}
