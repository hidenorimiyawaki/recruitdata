#if !defined(AFX_GLIDCOLORDIALOG_H__2151C4C0_176D_11D7_81BB_444553540000__INCLUDED_)
#define AFX_GLIDCOLORDIALOG_H__2151C4C0_176D_11D7_81BB_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlidColorDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CGlidColorDialog ダイアログ

class CGlidColorDialog : public CDialog
{
// コンストラクション
public:
	CBrush SampleBrush;
	CGlidColorDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CGlidColorDialog)
	enum { IDD = IDD_GLID_COLOR_DIALOG };
	CStatic	m_Sample_Color;
	UINT	m_Edit_B;
	UINT	m_Edit_G;
	UINT	m_Edit_R;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CGlidColorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CGlidColorDialog)
	afx_msg void OnPaint();
	afx_msg void OnSampleButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_GLIDCOLORDIALOG_H__2151C4C0_176D_11D7_81BB_444553540000__INCLUDED_)
