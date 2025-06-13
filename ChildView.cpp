
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

	memdc.TextOutW(0, 0, shape);
	memdc.TextOutW(0, 20, select);

	
	for (auto e : m_shapes)
		e.DrawShape(&memdc);
		


	dc.BitBlt(0, 0, w, h, &memdc, 0, 0, SRCCOPY);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
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
			CMyLine *myLine = new CMyLine(point, point);
			CMyShapeTree root(myLine);
			m_shapes.push_back(root);
			break;
		}
	}
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		m_shapes.back().m_root->UpdatePoint(point);
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
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