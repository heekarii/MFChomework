#pragma once
#include<list>
#include"CMyShape.h"
class CMyShapeTree
{
public:
	CMyShape *m_root;
	std::list <CMyShapeTree> m_child;
	int m_childCount;
	CRect m_selectBox;
	bool m_isSelected;
	int m_weight;

	CMyShapeTree();
	CMyShapeTree(CMyShape *root);
	void SetPoint();
	void DrawShape(CDC *dc);
	void Move(int dx, int dy);

};

