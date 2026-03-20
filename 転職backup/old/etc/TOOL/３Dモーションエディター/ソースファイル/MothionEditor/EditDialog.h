#if !defined(AFX_EDITDIALOG_H__DCD0A5DA_3ADB_49C8_86DE_A3C2E411FC01__INCLUDED_)
#define AFX_EDITDIALOG_H__DCD0A5DA_3ADB_49C8_86DE_A3C2E411FC01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CEditDialog ダイアログ

class CEditDialog : public CDialog
{
// コンストラクション
public:
	void SetData();
	void Animation();
	void SetControl();
	CEditDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CEditDialog)
	enum { IDD = IDD_EDIT_DIALOG };
	CSliderCtrl	m_Slider_Time;
	CButton	m_Check_Animation;
	CSliderCtrl	m_Slider_Frame;
	CButton	m_Check_Attack;
	CButton	m_Check_Gard;
	CSliderCtrl	m_Slider_RotZ;
	CSliderCtrl	m_Slider_RotY;
	CSliderCtrl	m_Slider_RotX;
	CSliderCtrl	m_Slider_PosZ;
	CSliderCtrl	m_Slider_PosY;
	CSliderCtrl	m_Slider_PosX;
	CSliderCtrl	m_Slider_Parts_No;
	int		m_Edit_Parts_No;
	float	m_Edit_PosX;
	float	m_Edit_PosY;
	float	m_Edit_PosZ;
	float	m_Edit_RotX;
	float	m_Edit_RotY;
	float	m_Edit_RotZ;
	int		m_Edit_Frame;
	int		m_Edit_Time;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CEditDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CEditDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckAttack();
	afx_msg void OnCheckGard();
	afx_msg void OnCheckAnimation();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EDITDIALOG_H__DCD0A5DA_3ADB_49C8_86DE_A3C2E411FC01__INCLUDED_)
