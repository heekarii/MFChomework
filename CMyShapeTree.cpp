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
	m_selectBox = m_root->GetRect();
	// 선택된 것을 잘 보여주기 위해 도형 크기 늘리기
	m_selectBox.left -= 5;
	m_selectBox.top -= 5;
	m_selectBox.right += 5;
	m_selectBox.bottom += 5;

	// 선택된 도형이 자식 노드를 가진 경우(그룹화가 되어있는 경우) 도형 전체에 외곽 사각형 
	if (m_childCount > 0)
	{
		for (auto const &T : m_child)
		{
			m_selectBox.left = min(m_selectBox.left, T.m_selectBox.left);
			m_selectBox.right = max(m_selectBox.right, T.m_selectBox.right);
			m_selectBox.top = min(m_selectBox.top, T.m_selectBox.top);
			m_selectBox.bottom = max(m_selectBox.bottom, T.m_selectBox.bottom);
		}
	}

}

void CMyShapeTree::DrawShape(CDC *dc)
{
	// 자식들을 모두 순회하며 도형 그리기, 재귀적으로 구현
	for (auto &t : m_child)
		t.DrawShape(dc);

	m_root->Draw(dc);

	if (m_isSelected == true)
	{
		CPen pen(PS_DOT, 1, RGB(255, 0, 0));
		dc->SelectStockObject(NULL_BRUSH);
		dc->SelectObject(&pen);
		dc->Rectangle(&m_selectBox);
	}

}

void CMyShapeTree::Move(int dx, int dy)
{
	// 노드 순회하면서 도형 이동, 재귀적으로 구현
	m_root->Move(dx, dy);

	for (auto &t : m_child)
		t.Move(dx, dy);

	m_selectBox.left += dx;
	m_selectBox.right += dx;
	m_selectBox.top += dy;
	m_selectBox.bottom += dy;

}
