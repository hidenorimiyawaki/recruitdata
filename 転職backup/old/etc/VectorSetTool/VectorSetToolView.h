// VectorSetToolView.h : CVectorSetToolView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORSETTOOLVIEW_H__E4DFC00C_6252_4CA9_88A7_CF7A9F893C77__INCLUDED_)
#define AFX_VECTORSETTOOLVIEW_H__E4DFC00C_6252_4CA9_88A7_CF7A9F893C77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVectorSetToolView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CVectorSetToolView();
	DECLARE_DYNCREATE(CVectorSetToolView)

// アトリビュート
public:
	CVectorSetToolDoc* GetDocument();
	bool R_Button;
	bool L_Button;

	CPoint PointR;
	CPoint PointL;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CVectorSetToolView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CVectorSetToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CVectorSetToolView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // VectorSetToolView.cpp ファイルがデバッグ環境の時使用されます。
inline CVectorSetToolDoc* CVectorSetToolView::GetDocument()
   { return (CVectorSetToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VECTORSETTOOLVIEW_H__E4DFC00C_6252_4CA9_88A7_CF7A9F893C77__INCLUDED_)
