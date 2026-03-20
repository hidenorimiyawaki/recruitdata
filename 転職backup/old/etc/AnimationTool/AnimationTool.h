// AnimationTool.h : ANIMATIONTOOL アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_ANIMATIONTOOL_H__35B8F361_B6FF_40D0_97B9_6DA06420CAA6__INCLUDED_)
#define AFX_ANIMATIONTOOL_H__35B8F361_B6FF_40D0_97B9_6DA06420CAA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CAnimationToolApp:
// このクラスの動作の定義に関しては AnimationTool.cpp ファイルを参照してください。
//

class CAnimationToolApp : public CWinApp
{
public:
	void DrawAnimeTest();
	CAnimationToolApp();

	//---------------汎用的に使用、代入される変数---------------
	CDirectX			Dx;							// 汎用DirectXクラス定義から設定、描画までするクラスのインスタンス
	CPoint				start,end,now,work;			// 始点、終点、現在点、作業用点のためのポイントくらす
	int					lbutton;					// マウスの左ボタンがクリックされたかの判定変数
	int					fileload;					// 画像ファイルが読み込まれたかの判定変数
	float				data[MAX_DATA][4];			// ファイルアウトするための矩形のUVデータ用変数(データ最大数分取得)
	int					frame_data[MAX_DATA];		// アニメーションフレームの秒数データ(データ最大数分取得)
	int					next_frame[MAX_DATA];		// 次に参照するアニメーションのコマデータ(データ最大数分取得)
	int					attach_kukei[MAX_DATA];		// キャッシュの矩形と実際のデータとのかみ合わせデータ(データ最大数分取得)
	int					draw_flg;					// ダイアログ呼んだからアイドル時間に描画してくださいなフラグ
	UINT				bftime;						// アイドル時間判定の前のフレーム時間用データ
	UINT				time;						// アイドル時間判定の今のフレーム時間用データ
	CDataDialog			DataDialog;					// 最終データ(アニメーション関連)の設定をするダイアログのインスタンス


	//---------------キャッシュに関する変数---------------
	int					cash_cnt;					// キャッシュの最大数のためのカウンタ
	CString				cash_string[CASH_MAX];		// キャッシュの補足説明の文章を保存(キャッシュ最大数分取得)
	RECT				cash_data[CASH_MAX];		// キャッシュの4隅のデータを保存(キャッシュ最大数分取得)
	CGlidDialog			GlidDialog;					// 上記の変数に実体をぶち込むためのダイアログのインスタンス


	//---------------グリッドに関する変数---------------
	int					GLID_WIDTH,GLID_HEIGHT;		// グリッドの幅・高さを格納(16,32,64,128で大きさ固定)
	CGliDTypeDialog		GlidTypeDialog;				// グリッドの幅・高さ、色を設定するダイアログのインスタンス
	CPen				CursolPen;					// 選択された矩形の描画のためのペン
	CPen				HollowGlidPen;				// グリッド本線間の薄い灰色の線のためのペン
	CPen				GlidPen;					// グリッド本線のためのペン(ダイアログで色を変化させられる)
	CBrush				CursolBrush;				// 各所に使われるための中ぬき色のペン
	int					GlidFlg;					// グリッドの表示・非表示のフラグ
	int					SnapFlg;					// グリッドにカーソルがフィットするかしないかのフラグ

	//---------------アニメーションに関する変数---------------
	int					animation_flg;				// アニメーション確認中かどうかフラグ
	int					anime_time;					// アニメーションしてる時間のカウンタ
	UINT				frame_count;				// アニメーションしてるフレームのカウンタ
	CAnimeDialog		AnimeDialog;				// アニメーションをテストするダイアログのインスタンス


	//---------------自己描画関数---------------
	void DrawExecEx();								// キャッシュに関連された絵の取得・描画のための関数
	void DrawExec();								// 一画面の描画(完成形)(DirectX＋MFCの描画)


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAnimationToolApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CAnimationToolApp)
	afx_msg void OnAppAbout();
	afx_msg void OnIdGlidOn();
	afx_msg void OnIdGlidOff();
	afx_msg void OnIdSnapOn();
	afx_msg void OnIdSnapOff();
	afx_msg void OnAnimeTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ANIMATIONTOOL_H__35B8F361_B6FF_40D0_97B9_6DA06420CAA6__INCLUDED_)
