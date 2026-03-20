#if !defined(AFX_ATTRDIALOG_H__E48B2FF0_AB49_4335_913C_7D934190687F__INCLUDED_)
#define AFX_ATTRDIALOG_H__E48B2FF0_AB49_4335_913C_7D934190687F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttrDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAttrDialog ダイアログ

class CAttrDialog : public CDialog
{
// コンストラクション
public:
	CAttrDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAttrDialog)
	enum { IDD = IDD_ATTR_DIALOG };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAttrDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAttrDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ATTRDIALOG_H__E48B2FF0_AB49_4335_913C_7D934190687F__INCLUDED_)
