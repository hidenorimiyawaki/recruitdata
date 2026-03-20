// MapEditor.h : MAPEDITOR アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_MAPEDITOR_H__A9832CCE_7D64_422B_AB91_2DC98F939905__INCLUDED_)
#define AFX_MAPEDITOR_H__A9832CCE_7D64_422B_AB91_2DC98F939905__INCLUDED_

#include "AttrData.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル
#include "MapData.h"	// ClassView によって追加されました。
#include "BmpDialog.h"	// ClassView によって追加されました。
#include "DataDialog.h"	// ClassView によって追加されました。
#include "SizeDialog.h"	// ClassView によって追加されました。
#include "CursolSizeDialog.h"	// ClassView によって追加されました。
#include "GlidColorDialog.h"	// ClassView によって追加されました。

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp:
// このクラスの動作の定義に関しては MapEditor.cpp ファイルを参照してください。
//

class CMapEditorApp : public CWinApp
{
public:
	CGlidColorDialog GlidColorDialog;
	BOOL			MainGlid;
	BOOL			BmpDlgGlid;
	CPoint			*GlidPointX;
	CPoint			*GlidPointY;
	CCursolSizeDialog CSDialog;
	CAttrData		*AttrData;
	CSizeDialog		SizeDialog;
	CDataDialog		DataDialog;
	BOOL			MapMode;		//マップ配置モード選択判定用
	BOOL			AttrMode;		//属性設定モード選択判定用
	CBmpDialog		BmpDialog;		//BMPダイアログボックスのインスタンス用
	CBitmap			Bitmap;			//ビットマップ用変数(BMPダイアログ用…外部専用)
	CDC				DC;				//デバイスコンテキスト用
	BOOL			LoadBitmap;		//ビットマップ読み込み判定用
	HBITMAP			hBitmap;		//ビットマップ使用用
	UINT			NewChipNo;		//新しいマップのチップNo用
	CPoint			NewMapPoint;	//新しいマップのポイント用	
	CPoint			ScrollPoint;	//スクロールポイント用
	int				Scroll_Max_y;	//スクロールのY最大値用
	int				Scroll_Max_x;	//スクロールのX最大値用
	BOOL			DispAttr;		//属性表示実行判定用
	CMapData		*MapData;		//マップデータ用
	CMapEditorApp();
	virtual ~CMapEditorApp();
	

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMapEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CMapEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAttrDisp();
	afx_msg void OnDataOutput();
	afx_msg void OnModeEditmap();
	afx_msg void OnModesetattr();
	afx_msg void OnIdMakeData();
	afx_msg void OnLoadBmp();
	afx_msg void OnCursolSize();
	afx_msg void OnBmpGlid();
	afx_msg void OnMainGlid();
	afx_msg void OnSetGlidColor();
	afx_msg void OnDatDataOutput();
	afx_msg void OnDatDataLoad();
	afx_msg void OnSetAttr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAPEDITOR_H__A9832CCE_7D64_422B_AB91_2DC98F939905__INCLUDED_)
