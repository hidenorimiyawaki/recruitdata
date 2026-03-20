#if !defined(AFX_GLIDDIALOG_H__B80FF854_8A81_4533_B096_02A5A4D3FD39__INCLUDED_)
#define AFX_GLIDDIALOG_H__B80FF854_8A81_4533_B096_02A5A4D3FD39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlidDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CGlidDialog ダイアログ

class CGlidDialog : public CDialog
{
// コンストラクション
public:
	void DrawExecEx();
	void DrawExec();
	CGlidDialog(CWnd* pParent = NULL);						// 標準のコンストラクタ
	CBitmap			Bitmap;									// 仮想領域の絵を書くためのビットマップ
	CDC				memDC;									// 仮想領域をいじるためのデバイスコンテキストクラス
	int				delete_flg;								// キャッシュ消しましたよキートリガー
	int				enter_flg;								// キャッシュ消しましたよキートリガー

// ダイアログ データ
	//{{AFX_DATA(CGlidDialog)
	enum { IDD = IDD_GLID_DIALOG };
	CStatic			m_Bit_Test;								// 確認の絵の描画用スタティック領域
	CListBox		m_List_Cash;							// 矩形キャッシュの状態表示用リストキャッシュ
	CString			m_Edit_Caption;							// 矩形キャッシュに説明つけましょう文章(エディットボックス)
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CGlidDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);			// メッセージ送られる前に殺っちまえ関数
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);		// DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CGlidDialog)
	virtual void OnOK();									// OK押されてますからどうにかしろや関数
	virtual void OnCancel();								// キャンセル押されてますからどうにかしろや関数
	afx_msg void OnDblclkListCash();						// リスト項目ダブルクリックされたから文章あげましょう関数
	afx_msg void OnPaint();									// さぁ今の矩形の絵描画しましょう関数
	virtual BOOL OnInitDialog();							// ダイアログ起動されたから初期化しようぜ関数
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);	// ウィンドウが見せられるからなんかしようや関数
	afx_msg void OnSelchangeListCash();						// リスト項目変更されたからその絵を見せましょ関数
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_GLIDDIALOG_H__B80FF854_8A81_4533_B096_02A5A4D3FD39__INCLUDED_)
