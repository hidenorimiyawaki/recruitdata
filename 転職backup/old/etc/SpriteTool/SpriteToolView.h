// SpriteToolView.h : CSpriteToolView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITETOOLVIEW_H__053E30C6_1E71_49F6_9D03_61E2D92D6893__INCLUDED_)
#define AFX_SPRITETOOLVIEW_H__053E30C6_1E71_49F6_9D03_61E2D92D6893__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSpriteToolView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CSpriteToolView();
	DECLARE_DYNCREATE(CSpriteToolView)

// アトリビュート
public:
	CSpriteToolDoc* GetDocument();
	CBitmap Bitmap;
	CDC memDC;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSpriteToolView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void RectDraw();
	virtual ~CSpriteToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSpriteToolView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SpriteToolView.cpp ファイルがデバッグ環境の時使用されます。
inline CSpriteToolDoc* CSpriteToolView::GetDocument()
   { return (CSpriteToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SPRITETOOLVIEW_H__053E30C6_1E71_49F6_9D03_61E2D92D6893__INCLUDED_)
