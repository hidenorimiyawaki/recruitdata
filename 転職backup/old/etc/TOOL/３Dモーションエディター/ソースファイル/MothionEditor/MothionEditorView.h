// MothionEditorView.h : CMothionEditorView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOTHIONEDITORVIEW_H__5EB29598_DC38_451F_9F1F_A75B9412AF66__INCLUDED_)
#define AFX_MOTHIONEDITORVIEW_H__5EB29598_DC38_451F_9F1F_A75B9412AF66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMothionEditorView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CMothionEditorView();
	DECLARE_DYNCREATE(CMothionEditorView)

// アトリビュート
public:
	CMothionEditorDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMothionEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	bool R_Button;
	bool L_Button;

	CPoint PointR;
	CPoint PointL;

	virtual ~CMothionEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMothionEditorView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MothionEditorView.cpp ファイルがデバッグ環境の時使用されます。
inline CMothionEditorDoc* CMothionEditorView::GetDocument()
   { return (CMothionEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MOTHIONEDITORVIEW_H__5EB29598_DC38_451F_9F1F_A75B9412AF66__INCLUDED_)
