
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCFinalHomework.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_curShape = 0;
	m_curSelected = 0;
	m_dragMode = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_DRAW_RECTANGLE, &CChildView::OnDrawRectangle)
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnDrawCurve)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnDrawStar)
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_ACTION_GROUP, &CChildView::OnActionGroup)
	ON_COMMAND(ID_ACTION_UNGROUP, &CChildView::OnActionUngroup)
	ON_COMMAND(ID_ALIGN_BRINGBACK, &CChildView::OnAlignBringback)
	ON_COMMAND(ID_ALIGN_BRINGFRONT, &CChildView::OnAlignBringfront)
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP, &CChildView::OnUpdateActionGroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_UNGROUP, &CChildView::OnUpdateActionUngroup)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGBACK, &CChildView::OnUpdateAlignBringback)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGFRONT, &CChildView::OnUpdateAlignBringfront)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CChildView::OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, &CChildView::OnUpdateDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CChildView::OnUpdateDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STAR, &CChildView::OnUpdateDrawStar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SELECT, &CChildView::OnUpdateActionSelect)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	
	CRect crect;
	GetClientRect(crect);
	int w = crect.Width();
	int h = crect.Height();
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap mbit;
	mbit.CreateCompatibleBitmap(&dc, w, h);
	memdc.SelectObject(mbit);

	CRect r(0, 0, w, h);
	memdc.Rectangle(r);
		
	CString shape;
	CString select;
	shape.Format(_T("Number of Shapes: %d"), m_shapes.size());
	select.Format(_T("Number of Selected: %d"), m_curSelected);

	
	for (auto e : m_shapes)
		e.DrawShape(&memdc);
		
	if (m_dragMode == true && m_curShape == 4)
	{
		CPen pen(PS_DOT, 1, RGB(255, 0, 0));
		memdc.SelectObject(pen);
		memdc.SelectStockObject(NULL_BRUSH);

		memdc.Rectangle(CRect(m_sp, m_ep));
	}

	memdc.TextOutW(0, 0, shape);
	memdc.TextOutW(0, 20, select);


	dc.BitBlt(0, 0, w, h, &memdc, 0, 0, SRCCOPY);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_curShape != 4)
		CancleSelection();

	switch (m_curShape)
	{
		case 0:
		{
			CMyRect *myRect = new CMyRect(point, point);
			CMyShapeTree root(myRect);
			m_shapes.push_back(root);
			break;
		}
		case 1:
		{
			CMyCircle *myCircle = new CMyCircle(point, point);
			CMyShapeTree root(myCircle);
			m_shapes.push_back(root);
			break;
		}
		case 2:
		{
			CMyLine *myLine = new CMyLine(point);
			CMyShapeTree root(myLine);
			m_shapes.push_back(root);
			break;
		}
		case 3:
		{
			CMyStar *myStar = new CMyStar(point, point);
			CMyShapeTree root(myStar);
			m_shapes.push_back(root);
			break;
		}
		case 4:
		{
			m_sp = point; // 드래그 시작점 설정
			m_ep = point; // 드래그 끝점 설정

			if (!(nFlags & MK_SHIFT)) // Shift 키를 누르지 않은 경우 (다중 선택 해제)
				CancleSelection();

			bool isSelected = false;
			// 리스트의 역순으로 노드 순회
			for (auto t = m_shapes.rbegin(); t != m_shapes.rend(); t++)
			{
				isSelected = false;
				PtInShape(*t, point, &isSelected); // 마우스 클릭 지점이 도형 내에 포함되는지 확인

				if (isSelected)
				{
					t->m_isSelected = true; // 도형 선택 플래그 설정
					m_curSelected++; // 선택된 도형 개수 증가
					break;
				}
			}

			if (!isSelected)
			{
				m_dragMode = true; // 선택된 도형이 없는 경우 드래그 모드 활성화
			}
			m_dragMode = true;
		}
	}
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(rect);
	if (nFlags & MK_LBUTTON && m_curShape < 4)
	{
		if (point.x <= rect.left) point.x = rect.left;
		if (point.x >= rect.right) point.x = rect.right;
		if (point.y <= rect.top) point.y = rect.top;
		if (point.y >= rect.bottom) point.y = rect.bottom;
		m_shapes.back().m_root->UpdatePoint(point);
		Invalidate();
	}

	if (nFlags & MK_LBUTTON && m_curShape == 4)
	{
		m_ep = point;
		if (m_curSelected)
		{
			if (point.x <= rect.left) point.x = rect.left;
			if (point.x >= rect.right) point.x = rect.right;
			if (point.y <= rect.top) point.y = rect.top;
			if (point.y >= rect.bottom) point.y = rect.bottom;

			for (auto &t : m_shapes)
			{
				if (t.m_isSelected)
					t.Move(m_ep.x - m_sp.x, m_ep.y - m_sp.y);
			}
			m_sp = point;
		}
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_curShape < 4)
	{
		m_shapes.back().SetPoint();
	}
	if (m_curShape == 4)
	{
		for (auto t = m_shapes.rbegin(); t != m_shapes.rend(); t++)
		{
			bool isSelected = false;
			PtInShape(*t, m_sp, m_ep, &isSelected);

			if (isSelected)
			{
				t->m_isSelected = true;
				//t->SetPoint();
				m_curSelected++;
			}
		}
	}
	m_dragMode = false;
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnDrawRectangle()
{
	m_curShape = 0;
}


void CChildView::OnDrawCircle()
{
	m_curShape = 1;
}


void CChildView::OnDrawCurve()
{
	m_curShape = 2;
}


void CChildView::OnDrawStar()
{
	m_curShape = 3;
}


void CChildView::OnActionSelect()
{
	m_curShape = 4;
}



BOOL CChildView::OnEraseBkgnd(CDC *pDC)
{
	return true;
}

void CChildView::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CMenu menu;

	menu.LoadMenu(IDR_MAINFRAME);

	CMenu *pMenu = menu.GetSubMenu(3);

	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd());

}


void CChildView::CancleSelection()
{
	m_curSelected = 0;
	for (auto &t = m_shapes.begin(); t != m_shapes.end(); t++)
	{
		if ((*t).m_isSelected)
			t->m_isSelected = false;
	}
}


void CChildView::PtInShape(CMyShapeTree root, CPoint point, bool *isSelected)
{
	if (root.m_root->GetType() == 2)
	{
		CMyLine *line = (CMyLine *)root.m_root;
		if (line->PtInLine(point))
		{
			*isSelected = true;
			return;
		}
	}

	if (PtInRect(root.m_root->GetRect(), point))
	{
		*isSelected = true;
		return;
	}

	for (CMyShapeTree child : root.m_child)
	{
		if (child.m_childCount > 0)
			PtInShape(child, point, isSelected);
		else if (PtInRect(child.m_selectBox, point))
		{
			*isSelected = true;
			return;
		}
	}
	return;
}

void CChildView::PtInShape(CMyShapeTree root, CPoint sp, CPoint ep, bool *isSelected)
{
	if (sp.x > ep.x)
		std::swap(sp.x, ep.x);
	if (sp.y > ep.y)
		std::swap(sp.x, ep.x);

	if (sp.x <= root.m_selectBox.left && root.m_selectBox.right <= ep.x &&
		sp.y <= root.m_selectBox.top && root.m_selectBox.bottom <= ep.y)
	{
		// 만약 st_pt와 ed_pt가 root.m_selectBox 사각형 내부에 있다면
		*isSelected = true;
	}
	return;
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)
	{
		for (auto t = m_shapes.begin(); t != m_shapes.end();)
		{
			if (t->m_isSelected)
			{
				t = m_shapes.erase(t);
				m_curSelected--;
				Invalidate();
			}
			else
				t++;
		}
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

#include <vector>
void CChildView::OnActionGroup()
{
	int n = m_curSelected;
	auto t = m_shapes.begin();

	CMyShapeTree rootNode;
	std::vector<CMyShapeTree> childList;

	while (n && t != m_shapes.end())
	{
		if (t->m_isSelected)
		{
			if (n == 1)	//마지막으로 선택된 노드(n == 1)
			{
				rootNode = *t;
				rootNode.m_weight = 0;	// weight of root = 0

			}
			else
			{
				// 나머지 선택된 노드들은 리스트에 추가(하나로 합쳐질것이기 때문에 자식들의 isSelected = false)
				childList.push_back(*t);
				childList.back().m_isSelected = false;
			}
			t = m_shapes.erase(t);
			n--;
		}
		else
		{
			++t;
		}

	}
	int w = 1;
	if (!rootNode.m_child.empty())
	{
		w = rootNode.m_child.back().m_weight + 1;
	}

	for (auto &it : childList)
	{
		it.m_weight = w;
		rootNode.m_child.push_back(it);
	}

	rootNode.m_childCount = rootNode.m_child.size();
	rootNode.SetPoint();

	m_shapes.push_back(rootNode);
	m_curSelected = 1;
	Invalidate();
}


void CChildView::OnActionUngroup()
{
	int n = m_curSelected;
	auto t = m_shapes.begin();

	CMyShapeTree rootNode;
	while (n && t != m_shapes.end())
	{
		if (t->m_isSelected)
		{
			if (t->m_childCount > 0)
			{
				rootNode = *t;
				int w = -1;
				while (!rootNode.m_child.empty())
				{
					CMyShapeTree tmp = rootNode.m_child.back();

					if (w > tmp.m_weight) break;

					tmp.m_isSelected = true;
					m_curSelected++;

					w = tmp.m_weight;
					tmp.m_weight = 0;
					tmp.SetPoint();

					rootNode.m_child.pop_back();
					m_shapes.push_back(tmp);
				}

				t = m_shapes.erase(t);

				rootNode.m_childCount = rootNode.m_child.size();
				rootNode.SetPoint();
				m_shapes.push_back(rootNode);
			}
			else
				t++;
			n--;
			Invalidate();
		}
		else
			t++;
	}
}


void CChildView::OnAlignBringback()
{
	int n = m_curSelected;
	auto t = m_shapes.begin();
	while (n)
	{
		if (t == m_shapes.end()) break;

		if (t->m_isSelected)
		{
			m_shapes.push_front(*t);
			t = m_shapes.erase(t);
			n--;
			Invalidate();
		}
		else
			t++;
	}
}


void CChildView::OnAlignBringfront()
{
	int n = m_curSelected;
	auto t = m_shapes.begin();

	while (n)
	{
		if (t == m_shapes.end()) break;

		if (t->m_isSelected)
		{
			m_shapes.push_back(*t);
			t = m_shapes.erase(t);
			n--;
			Invalidate();
		}
		else
		{
			t++;
		}
	}
}


void CChildView::OnUpdateActionGroup(CCmdUI *pCmdUI)
{
	if (m_curSelected > 1)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);

}


void CChildView::OnUpdateActionUngroup(CCmdUI *pCmdUI)
{
	if (m_curSelected >= 1)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(false);
}

void CChildView::OnUpdateAlignBringback(CCmdUI *pCmdUI)
{
	if (m_curSelected >= 1)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(false);
}


void CChildView::OnUpdateAlignBringfront(CCmdUI *pCmdUI)
{
	if (m_curSelected >= 1)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(false);
}


void CChildView::OnUpdateDrawCircle(CCmdUI *pCmdUI)
{
	if (m_curShape == 1)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CChildView::OnUpdateDrawCurve(CCmdUI *pCmdUI)
{
	if (m_curShape == 2)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CChildView::OnUpdateDrawRectangle(CCmdUI *pCmdUI)
{
	if (m_curShape == 0)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CChildView::OnUpdateDrawStar(CCmdUI *pCmdUI)
{
	if (m_curShape == 3)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}


void CChildView::OnUpdateActionSelect(CCmdUI *pCmdUI)
{
	if (m_curShape == 4)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}
