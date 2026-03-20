#if !defined(AFX_DATADIALOG_H__623F2B05_AA76_4F0D_A333_A0EBAE3295DC__INCLUDED_)
#define AFX_DATADIALOG_H__623F2B05_AA76_4F0D_A333_A0EBAE3295DC__INCLUDED_

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
	UINT	data;
	UINT	step_data;
	UINT	damage_data;
	UINT	floor_data;
	CString step;
	CString damage;
	CString floor;
	~CDataDialog();
	CDataDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDataDialog)
	enum { IDD = IDD_DATA_DIALOG };
	CComboBox	m_combo_step;
	CComboBox	m_combo_floor;
	CComboBox	m_combo_damage;
	UINT	m_palet;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDataDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDataDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DATADIALOG_H__623F2B05_AA76_4F0D_A333_A0EBAE3295DC__INCLUDED_)
