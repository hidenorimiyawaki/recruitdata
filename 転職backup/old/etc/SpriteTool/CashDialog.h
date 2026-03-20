#if !defined(AFX_CASHDIALOG_H__26A5791C_E444_4800_98DF_F4C69389FF9C__INCLUDED_)
#define AFX_CASHDIALOG_H__26A5791C_E444_4800_98DF_F4C69389FF9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CashDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCashDialog ダイアログ

class CCashDialog : public CDialog
{
// コンストラクション
public:
	CCashDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	void DrawExecEx();
	void DrawExec();
	CGlidDialog(CWnd* pParent = NULL);						// 標準のコンストラクタ
	CBitmap			Bitmap;									// 仮想領域の絵を書くためのビットマップ
	CDC				memDC;									// 仮想領域をいじるためのデバイスコンテキストクラス
	int				delete_flg;								// キャッシュ消しましたよキートリガー
	int				enter_flg;								// キャッシュ消しましたよキートリガー

// ダイアログ データ
	//{{AFX_DATA(CCashDialog)
	enum { IDD = IDD_CASH_DIALOG };
	CListBox	m_List_Cash;
	CStatic	m_Bit_Test;
	CString	m_Edit_Caption;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCashDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCashDialog)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDblclkListCash();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeListCash();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CASHDIALOG_H__26A5791C_E444_4800_98DF_F4C69389FF9C__INCLUDED_)
