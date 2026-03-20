// DougaEditor.h : DOUGAEDITOR アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DOUGAEDITOR_H__571CBF2C_2D1F_46EF_87ED_D1BE76DE53CE__INCLUDED_)
#define AFX_DOUGAEDITOR_H__571CBF2C_2D1F_46EF_87ED_D1BE76DE53CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDougaEditorApp:
// このクラスの動作の定義に関しては DougaEditor.cpp ファイルを参照してください。
//

class CDougaEditorApp : public CWinApp
{
public:
	CDougaEditorApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDougaEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CDougaEditorApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DOUGAEDITOR_H__571CBF2C_2D1F_46EF_87ED_D1BE76DE53CE__INCLUDED_)
