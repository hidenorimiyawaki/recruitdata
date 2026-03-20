// particleediterView.h : CparticleediterView クラスのインターフェイス
//


#pragma once


class CparticleediterView : public CView
{
protected: // シリアル化からのみ作成します。
	CparticleediterView();
	DECLARE_DYNCREATE(CparticleediterView)

// 属性
public:
	CparticleediterDoc* GetDocument() const;

// 操作
public:

// オーバーライド
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CparticleediterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	bool R_Button;
	bool L_Button;

	CPoint PointR;
	CPoint PointL;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT nIDEvent);
};

#ifndef _DEBUG  // particleediterView.cpp のデバッグ バージョン
inline CparticleediterDoc* CparticleediterView::GetDocument() const
   { return reinterpret_cast<CparticleediterDoc*>(m_pDocument); }
#endif

