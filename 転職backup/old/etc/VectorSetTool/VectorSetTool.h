// VectorSetTool.h : VECTORSETTOOL アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_VECTORSETTOOL_H__DF59DE66_E317_43E9_B6B1_F98638F416D8__INCLUDED_)
#define AFX_VECTORSETTOOL_H__DF59DE66_E317_43E9_B6B1_F98638F416D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolApp:
// このクラスの動作の定義に関しては VectorSetTool.cpp ファイルを参照してください。
//

class CVectorSetToolApp : public CWinApp
{
public:
	void DrawExec();
	//---------------汎用的に使用、代入される変数---------------
	CDirectX			Dx;							// 汎用DirectXクラス定義から設定、描画までするクラスのインスタンス
	CPoint				start,end,now,work;			// 始点、終点、現在点、作業用点のためのポイントくらす
	int					lbutton;					// マウスの左ボタンがクリックされたかの判定変数
	int					fileload;					// 画像ファイルが読み込まれたかの判定変数
	int					draw_flg;					// ダイアログ呼んだからアイドル時間に描画してくださいなフラグ
	UINT				bftime;						// アイドル時間判定の前のフレーム時間用データ
	UINT				time;						// アイドル時間判定の今のフレーム時間用データ
	CString				mainfile;
	CPoint				point[MAX_DATA];
	int					point_cnt;
	CPoint				drum_point[MAX_DATA];
	int					drum_point_cnt;
	CPoint				ballon_point[MAX_DATA];
	int					ballon_point_cnt;
	int					drum_Point_Cheker;
	int					ballon_Point_Cheker;
	int					object_flg;

	//---------------アニメーションに関する変数---------------
	int					animation_flg;				// アニメーション確認中かどうかフラグ
	int					anime_time;					// アニメーションしてる時間のカウンタ
	UINT				frame_count;				// アニメーションしてるフレームのカウンタ
	CPen				GlidPen;					// グリッド本線のためのペン(ダイアログで色を変化させられる)
	CPen				CheckPen;					// グリッド本線のためのペン(ダイアログで色を変化させられる)
	CPen				PointPen;					// のためのペン(ダイアログで色を変化させられる)
	CPen				SelectPen;					// のためのペン(ダイアログで色を変化させられる)
	CPen				DrumPen;					// のためのペン(ダイアログで色を変化させられる)
	CPen				BallonPen;					// のためのペン(ダイアログで色を変化させられる)

	CBrush				CursolBrush;				// 各所に使われるための中ぬき色のペン
	int					SnapFlg;
	int					Point_flg;
	int					point_offset_x;
	int					point_offset_y;
	int					camera_offset_x;
	int					camera_offset_y;
	int					Point_Cheker;
	CPoint				NowPoint;
	CCameraDialog		CameraDialog;
	int					shift_flg;
	int					cnt_flg;
	//---------------モデルに関する変数---------------
	CModel				mainmodel;
	CVectorSetToolApp();
	D3DXVECTOR3 work_dir;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CVectorSetToolApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL


// インプリメンテーション
	//{{AFX_MSG(CVectorSetToolApp)
	afx_msg void OnAppAbout();
	afx_msg void OnIdChangePoint();
	afx_msg void OnIdEditPoint();
	afx_msg void OnIdDeletePoint();
	afx_msg void OnIdSnapOn();
	afx_msg void OnIdSnapOff();
	afx_msg void OnIdChangeObjectPoint();
	afx_msg void OnIdDeleteObjectPoint();
	afx_msg void OnIdObject1();
	afx_msg void OnIdObject2();
	afx_msg void OnIdSetObjectPoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VECTORSETTOOL_H__DF59DE66_E317_43E9_B6B1_F98638F416D8__INCLUDED_)
