// MapEditorView.h : CMapEditorView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPEDITORVIEW_H__FE4BBA72_DA2C_4064_9126_E21550590220__INCLUDED_)
#define AFX_MAPEDITORVIEW_H__FE4BBA72_DA2C_4064_9126_E21550590220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMapEditorView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CMapEditorView();
	DECLARE_DYNCREATE(CMapEditorView)

// アトリビュート
public:
	CMapEditorDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMapEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CPen AttrPen[16];
	CPen GlidPen;
	CBrush CursolBrush;
	CPen CursolPen;
	CPoint MapPoint;
	BOOL MousePat;
	virtual ~CMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMapEditorView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MapEditorView.cpp ファイルがデバッグ環境の時使用されます。
inline CMapEditorDoc* CMapEditorView::GetDocument()
   { return (CMapEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAPEDITORVIEW_H__FE4BBA72_DA2C_4064_9126_E21550590220__INCLUDED_)
