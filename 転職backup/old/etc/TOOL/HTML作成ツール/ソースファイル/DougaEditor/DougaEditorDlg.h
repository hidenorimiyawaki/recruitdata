// DougaEditorDlg.h : ヘッダー ファイル
//

#if !defined(AFX_DOUGAEDITORDLG_H__FE954A46_F4ED_403B_871C_CE38FA3A0E44__INCLUDED_)
#define AFX_DOUGAEDITORDLG_H__FE954A46_F4ED_403B_871C_CE38FA3A0E44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDougaEditorDlg ダイアログ

class CDougaEditorDlg : public CDialog
{
// 構築
public:
	CDougaEditorDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDougaEditorDlg)
	enum { IDD = IDD_DOUGAEDITOR_DIALOG };
	CButton	m_CheckAuto;
	CButton	m_CheckHidden;
	CButton	m_CheckRoop;
	CComboBox	m_ComboPos;
	CString	m_EditAddles;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDougaEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDougaEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonBrows();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DOUGAEDITORDLG_H__FE954A46_F4ED_403B_871C_CE38FA3A0E44__INCLUDED_)
