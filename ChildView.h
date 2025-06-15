
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창
#include <list>
#include "CMyShape.h"
#include "CMyRect.h"
#include "CMyCircle.h"
#include "CMyLine.h"
#include "CMyStar.h"
#include "CMyShapeTree.h"
class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

	std::list<CMyShapeTree> m_shapes;
	int m_curShape; //  0 : rect, 1 : circle, 2 : line, 3 : star, 4 : select
	int m_curSelected;
	bool m_dragMode; // int select mode
	CPoint m_sp, m_ep;


// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawCurve();
	afx_msg void OnDrawStar();
	afx_msg void OnActionSelect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd * /*pWnd*/, CPoint /*point*/);
	void CancleSelection();
	void PtInShape(CMyShapeTree root, CPoint point, bool *isSelected);
	void PtInShape(CMyShapeTree root, CPoint sp, CPoint ep, bool *isSelected);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActionGroup();
	afx_msg void OnActionUngroup();
	afx_msg void OnAlignBringback();
	afx_msg void OnAlignBringfront();
	afx_msg void OnUpdateActionGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateActionUngroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignBringback(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignBringfront(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawCurve(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawStar(CCmdUI *pCmdUI);
	afx_msg void OnUpdateActionSelect(CCmdUI *pCmdUI);
};

