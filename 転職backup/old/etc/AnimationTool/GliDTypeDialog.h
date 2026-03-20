#if !defined(AFX_GLIDTYPEDIALOG_H__7E377EDA_CB69_4C5E_ADAA_EBB17AAD1904__INCLUDED_)
#define AFX_GLIDTYPEDIALOG_H__7E377EDA_CB69_4C5E_ADAA_EBB17AAD1904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GliDTypeDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CGliDTypeDialog ダイアログ

class CGliDTypeDialog : public CDialog
{
// コンストラクション
public:
	CGliDTypeDialog(CWnd* pParent = NULL);				// 標準のコンストラクタ
	CBrush				CursolBrush;					// グリッドのサンプルカラー塗りますよブラシ

// ダイアログ データ
	//{{AFX_DATA(CGliDTypeDialog)
	enum { IDD = IDD_GLID_TYPE_DIALOG };
	CStatic				m_Static_Color;					// グリッド色の確認サンプルカラーのスタティック領域
	CSliderCtrl			m_Slider_R;						// グリッド色のR値いじるスライダー
	CSliderCtrl			m_Slider_G;						// グリッド色のG値いじるスライダー
	CSliderCtrl			m_Slider_B;						// グリッド色のB値いじるスライダー
	int					m_Edit_B;						// グリッド色のR値の確認のための値(エディットボックス)
	int					m_Edit_G;						// グリッド色のR値の確認のための値(エディットボックス)
	int					m_Edit_R;						// グリッド色のR値の確認のための値(エディットボックス)
	CComboBox			m_Combo_Width;					// グリッドの幅をいじるコンボボックス
	CComboBox			m_Combo_Height;					// グリッドの高さをいじるコンボボックス
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CGliDTypeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CGliDTypeDialog)
	virtual BOOL OnInitDialog();						// ダイアログ起動したから初期化しようぜ関数
	virtual void OnOK();								// OKおされましたから各種設定しましょう関数
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	
														// スライダーがスクロールされたからいろいろしましょう関数
	afx_msg void OnPaint();								// さぁサンプル色塗りましょうね関数
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_GLIDTYPEDIALOG_H__7E377EDA_CB69_4C5E_ADAA_EBB17AAD1904__INCLUDED_)
