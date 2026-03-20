#if !defined(AFX_DATADIALOG_H__D1DA0855_4BDB_4828_A2A1_694F6E2DD382__INCLUDED_)
#define AFX_DATADIALOG_H__D1DA0855_4BDB_4828_A2A1_694F6E2DD382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDataDialog ダイアログ

class CDataDialog : public CDialog
{
// コンストラクション
public:
	void Update();
	CDataDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDataDialog)
	enum { IDD = IDD_DATADIALOG };
	CSliderCtrl	m_Slider_Now_Frame;
	CSliderCtrl	m_Slider_Next_Frame;
	CSliderCtrl	m_Slider_Frame_Time;
	CButton	m_Check_Alpha;
	int		m_All_Time;
	int		m_Frame_Time;
	int		m_Next_Frame;
	int		m_Now_Frame;
	float	m_U_Size;
	float	m_V_Size;
	int		m_X_Size;
	int		m_Y_Size;
	float	m_U_Size2;
	float	m_V_Size2;
	int		m_Edit_Kukei;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDataDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDataDialog)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckAlpha();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonCheckKukei();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DATADIALOG_H__D1DA0855_4BDB_4828_A2A1_694F6E2DD382__INCLUDED_)
