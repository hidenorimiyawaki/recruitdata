#if !defined(AFX_CURSOLSIZEDIALOG_H__4E0C7C0A_71D0_48C7_8656_0C46FA1E819B__INCLUDED_)
#define AFX_CURSOLSIZEDIALOG_H__4E0C7C0A_71D0_48C7_8656_0C46FA1E819B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CursolSizeDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCursolSizeDialog ダイアログ

class CCursolSizeDialog : public CDialog
{
// コンストラクション
public:
	UINT work_y;
	UINT work_x;
	CCursolSizeDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CCursolSizeDialog)
	enum { IDD = IDD_CURSOL_DIALOG };
	UINT	m_cursol_x;
	UINT	m_cursol_y;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCursolSizeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCursolSizeDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CURSOLSIZEDIALOG_H__4E0C7C0A_71D0_48C7_8656_0C46FA1E819B__INCLUDED_)
