#if !defined(AFX_DEFDIALOG_H__31273CE0_F175_4ED5_A046_538B99AD9617__INCLUDED_)
#define AFX_DEFDIALOG_H__31273CE0_F175_4ED5_A046_538B99AD9617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDefDialog ダイアログ

class CDefDialog : public CDialog
{
// コンストラクション
public:
	CDefDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDefDialog)
	enum { IDD = IDD_DEFDIALOG };
	int		m_EditDefTime;
	int		m_MaxHtmlNum;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDefDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDefDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEFDIALOG_H__31273CE0_F175_4ED5_A046_538B99AD9617__INCLUDED_)
