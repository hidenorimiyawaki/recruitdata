#if !defined(AFX_ANIMEDIALOG_H__826BFFA7_8626_4536_9983_C30FFE32005A__INCLUDED_)
#define AFX_ANIMEDIALOG_H__826BFFA7_8626_4536_9983_C30FFE32005A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimeDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAnimeDialog ダイアログ

class CAnimeDialog : public CDialog
{
// コンストラクション
public:

	CAnimeDialog(CWnd* pParent = NULL);						// 標準のコンストラクタ
	void DrawExec();										// 描画呼び出し関数

	CBitmap			Bitmap;									// 仮想領域の絵を書くためのビットマップ
	CDC				memDC;									// 仮想領域をいじるためのデバイスコンテキストクラス
	int				playflg;								// アニメーション許可フラグ
	int				anime_frame;							// アニメーションの参照カウンタ
	int				anime_time;								// アニメーションのフレームカウンタ
	int				end;									// ダイアログの終了判定変数

// ダイアログ データ
	//{{AFX_DATA(CAnimeDialog)
	enum { IDD = IDD_ANIME_DIALOG };
	CSliderCtrl	m_Flame_Slider;
	CStatic			m_Play_Window;							// アニメーション領域変数
	int		m_Edit_Flame;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAnimeDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);		// DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAnimeDialog)
	afx_msg void OnButtonPlay();							// アニメーション再生許可関数		
	afx_msg void OnButtonStop();							// アニメーション再生許可解除関数
	afx_msg void OnButtonBack();							// アニメーション参照初期化関数
	virtual BOOL OnInitDialog();							// ダイアログボックス初期化関数
	afx_msg void OnPaint();									// システム描画関数
	virtual void OnOK();									// ダイアログ終了関数
	virtual void OnCancel();								// ダイアログ終了関数
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ANIMEDIALOG_H__826BFFA7_8626_4536_9983_C30FFE32005A__INCLUDED_)
