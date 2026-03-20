// ScripteEditorDlg.h : ヘッダー ファイル
//

#if !defined(AFX_SCRIPTEEDITORDLG_H__5EF4DCDB_0A3B_4B1E_A995_A99BFF93415B__INCLUDED_)
#define AFX_SCRIPTEEDITORDLG_H__5EF4DCDB_0A3B_4B1E_A995_A99BFF93415B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScripteEditorDlg ダイアログ

class CScripteEditorDlg : public CDialog
{
// 構築
public:
	CScripteEditorDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	int	posB,posR,posG;
	CBrush SampleBrush;
// ダイアログ データ
	//{{AFX_DATA(CScripteEditorDlg)
	enum { IDD = IDD_SCRIPTEEDITOR_DIALOG };
	CSliderCtrl	m_SliderColorR;
	CSliderCtrl	m_SliderColorG;
	CSliderCtrl	m_SliderColorB;
	CStatic	m_SampleColor;
	CComboBox	m_ComboFontSize;
	CComboBox	m_ComboMoveType;
	CComboBox	m_ComboFontType;
	CButton	m_CheckUnderLine;
	CButton	m_CheckPower;
	CButton	m_CheckNaname;
	CString	m_EditBunshou;
	int		m_EditBrank;
	int		m_EditSpeed;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CScripteEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CScripteEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonsave();
	afx_msg void OnButtonload();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusEditBrank();
	afx_msg void OnKillfocusEditBunshou();
	afx_msg void OnKillfocusEditSpeed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SCRIPTEEDITORDLG_H__5EF4DCDB_0A3B_4B1E_A995_A99BFF93415B__INCLUDED_)
