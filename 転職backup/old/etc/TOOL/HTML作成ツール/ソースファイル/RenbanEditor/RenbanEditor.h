// RenbanEditor.h : RENBANEDITOR アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_RENBANEDITOR_H__B081E9E5_A6FB_4E3D_B93E_F574AF2EE36E__INCLUDED_)
#define AFX_RENBANEDITOR_H__B081E9E5_A6FB_4E3D_B93E_F574AF2EE36E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CRenbanEditorApp:
// このクラスの動作の定義に関しては RenbanEditor.cpp ファイルを参照してください。
//

class CRenbanEditorApp : public CWinApp
{
public:
	CRenbanEditorApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRenbanEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CRenbanEditorApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RENBANEDITOR_H__B081E9E5_A6FB_4E3D_B93E_F574AF2EE36E__INCLUDED_)
