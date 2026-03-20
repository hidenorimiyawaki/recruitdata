// ScripteEditor.h : SCRIPTEEDITOR アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SCRIPTEEDITOR_H__2F037F43_4F76_4359_B6F9_3D65ACD5C1CD__INCLUDED_)
#define AFX_SCRIPTEEDITOR_H__2F037F43_4F76_4359_B6F9_3D65ACD5C1CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CScripteEditorApp:
// このクラスの動作の定義に関しては ScripteEditor.cpp ファイルを参照してください。
//

class CScripteEditorApp : public CWinApp
{
public:
	CScripteEditorApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CScripteEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CScripteEditorApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SCRIPTEEDITOR_H__2F037F43_4F76_4359_B6F9_3D65ACD5C1CD__INCLUDED_)
