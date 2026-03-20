#if !defined(AFX_GLIDTYPEDIALOG_H__6CB814C9_F83F_424E_9299_5228623BF2AC__INCLUDED_)
#define AFX_GLIDTYPEDIALOG_H__6CB814C9_F83F_424E_9299_5228623BF2AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlidTypeDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CGlidTypeDialog ダイアログ

class CGlidTypeDialog : public CDialog
{
// コンストラクション
public:
	CGlidTypeDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CBrush				CursolBrush;					// グリッドのサンプルカラー塗りますよブラシ

// ダイアログ データ
	//{{AFX_DATA(CGlidTypeDialog)
	enum { IDD = IDD_GLID_TYPE_DIALOG };
	CStatic	m_Static_Color;
	CSliderCtrl	m_Slider_R;
	CSliderCtrl	m_Slider_G;
	CSliderCtrl	m_Slider_B;
	CComboBox	m_Combo_Height;
	CComboBox	m_Combo_Width;
	int		m_Edit_B;
	int		m_Edit_G;
	int		m_Edit_R;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CGlidTypeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CGlidTypeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_GLIDTYPEDIALOG_H__6CB814C9_F83F_424E_9299_5228623BF2AC__INCLUDED_)
