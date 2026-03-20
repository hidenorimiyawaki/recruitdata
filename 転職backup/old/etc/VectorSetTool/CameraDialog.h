#if !defined(AFX_CAMERADIALOG_H__EAD7BE1F_EC48_40DE_8D5E_D32860782ADA__INCLUDED_)
#define AFX_CAMERADIALOG_H__EAD7BE1F_EC48_40DE_8D5E_D32860782ADA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCameraDialog ダイアログ

class CCameraDialog : public CDialog
{
// コンストラクション
public:
	CCameraDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CCameraDialog)
	enum { IDD = IDD_CAMERA_DIALOG };
	CComboBox	m_Combo_Object;
	int		m_Move_X;
	int		m_Move_Y;
	int		m_Move_Z;
	int		m_Edit_Offset;
	//}}AFX_DATA
	int		object_flg;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCameraDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCameraDialog)
	afx_msg void OnButtonMove();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRight();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButtonDefault();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetPoint();
	afx_msg void OnButtonSetObject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CAMERADIALOG_H__EAD7BE1F_EC48_40DE_8D5E_D32860782ADA__INCLUDED_)
