#if !defined(AFX_BMPDIALOG_H__F3EE9203_1D6E_48CD_A517_662740D49D00__INCLUDED_)
#define AFX_BMPDIALOG_H__F3EE9203_1D6E_48CD_A517_662740D49D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CBmpDialog ダイアログ

class CBmpDialog : public CDialog
{
// コンストラクション
public:
	CPoint GlidPointY[64];
	CPoint GlidPointX[64];
	CPen GlidPen;
	CBrush CursolBrush;
	CPen CursolPen;
	CPoint MousePoint;
	CBmpDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CBmpDialog)
	enum { IDD = IDD_BMP_DIALOG };
	CStatic	m_bmp_field;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBmpDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CBmpDialog)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BMPDIALOG_H__F3EE9203_1D6E_48CD_A517_662740D49D00__INCLUDED_)
