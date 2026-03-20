#if !defined(AFX_SIZEDIALOG_H__149B992E_9BFE_4B9B_B8F2_DAC88D9E6502__INCLUDED_)
#define AFX_SIZEDIALOG_H__149B992E_9BFE_4B9B_B8F2_DAC88D9E6502__INCLUDED_

#include "MapData.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SizeDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSizeDialog ダイアログ

class CSizeDialog : public CDialog
{
// コンストラクション
public:
	UINT MAP_Y;
	UINT MAP_X;
	CSizeDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSizeDialog)
	enum { IDD = IDD_SIZE_DIALOG };
	UINT	m_y_size;
	UINT	m_x_size;
	UINT	m_plaet_no;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSizeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSizeDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SIZEDIALOG_H__149B992E_9BFE_4B9B_B8F2_DAC88D9E6502__INCLUDED_)
