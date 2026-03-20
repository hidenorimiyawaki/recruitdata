// RenbanEditorDlg.h : ヘッダー ファイル
//

#if !defined(AFX_RENBANEDITORDLG_H__DB462B73_6E76_4A29_86F2_DB43DDBD05D7__INCLUDED_)
#define AFX_RENBANEDITORDLG_H__DB462B73_6E76_4A29_86F2_DB43DDBD05D7__INCLUDED_

#include "DefDialog.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct{
	CString ImageAddles;
	int		ImageTime;
}HTMLPAGEDATA;

/////////////////////////////////////////////////////////////////////////////
// CRenbanEditorDlg ダイアログ

class CRenbanEditorDlg : public CDialog
{
// 構築
public:
	HTMLPAGEDATA* SetData;
	CDefDialog DefSetDialog;
	CRenbanEditorDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRenbanEditorDlg)
	enum { IDD = IDD_RENBANEDITOR_DIALOG };
	CSliderCtrl	m_SliderEdit;
	CString	m_EditAddles;
	int		m_EditNowNo;
	int		m_EditNowTime;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRenbanEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRenbanEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonDatasave();
	afx_msg void OnButtonDataload();
	afx_msg void OnButtonBrows();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusEditnowno();
	afx_msg void OnKillfocusEditnowtime();
	afx_msg void OnKillfocusEditaddles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RENBANEDITORDLG_H__DB462B73_6E76_4A29_86F2_DB43DDBD05D7__INCLUDED_)
