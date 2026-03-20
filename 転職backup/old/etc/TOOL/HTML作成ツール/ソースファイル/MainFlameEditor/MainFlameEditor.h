// MainFlameEditor.h : MAINFLAMEEDITOR アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_MAINFLAMEEDITOR_H__AABB2B01_050B_4018_9AC8_7A02CEB1D9B6__INCLUDED_)
#define AFX_MAINFLAMEEDITOR_H__AABB2B01_050B_4018_9AC8_7A02CEB1D9B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMainFlameEditorApp:
// このクラスの動作の定義に関しては MainFlameEditor.cpp ファイルを参照してください。
//

class CMainFlameEditorApp : public CWinApp
{
public:
	CMainFlameEditorApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMainFlameEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMainFlameEditorApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAINFLAMEEDITOR_H__AABB2B01_050B_4018_9AC8_7A02CEB1D9B6__INCLUDED_)
