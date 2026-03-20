// AnimationToolView.h : CAnimationToolView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMATIONTOOLVIEW_H__5BCF0B08_0EEF_4F30_9942_4B6A9D9DC58A__INCLUDED_)
#define AFX_ANIMATIONTOOLVIEW_H__5BCF0B08_0EEF_4F30_9942_4B6A9D9DC58A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAnimationToolView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CAnimationToolView();
	DECLARE_DYNCREATE(CAnimationToolView)

// アトリビュート
public:
	CAnimationToolDoc* GetDocument();
	CBitmap Bitmap;
	CDC memDC;
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAnimationToolView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void RectDraw();
	virtual ~CAnimationToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAnimationToolView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // AnimationToolView.cpp ファイルがデバッグ環境の時使用されます。
inline CAnimationToolDoc* CAnimationToolView::GetDocument()
   { return (CAnimationToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ANIMATIONTOOLVIEW_H__5BCF0B08_0EEF_4F30_9942_4B6A9D9DC58A__INCLUDED_)
