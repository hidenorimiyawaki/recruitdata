// MothionEditor.h : MOTHIONEDITOR アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_MOTHIONEDITOR_H__31D7E21D_E4CC_4CB7_B28B_883A100F1AF6__INCLUDED_)
#define AFX_MOTHIONEDITOR_H__31D7E21D_E4CC_4CB7_B28B_883A100F1AF6__INCLUDED_

#include "EditDialog.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorApp:
// このクラスの動作の定義に関しては MothionEditor.cpp ファイルを参照してください。
//

class CMothionEditorApp : public CWinApp
{
public:
	CEditDialog EditDialog;
	CMothionEditorApp();
	UINT frame_count;
	UINT bftime;
	UINT time;
	CDirectX direct_x;
	CModelManager model_manager;
	CZintai zintai;
	FLG flgset[BANK_QTY][FRAME_QTY];
	MOTION_DATA *motion;
	int end_check;
	int play_flg;
	int frame_time[BANK_QTY][FRAME_QTY];
	int anime_time;
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMothionEditorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CMothionEditorApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MOTHIONEDITOR_H__31D7E21D_E4CC_4CB7_B28B_883A100F1AF6__INCLUDED_)
