#ifndef _DEFINE_H
#define _DEFINE_H

//----- 定数
#define	SCREEN_WIDTH		800					// スクリーンの幅
#define	SCREEN_HEIGHT		600					// スクリーンの高さ
#define ASPECT_RATIO		SCREEN_WIDTH/SCREEN_HEIGHT		// アスペクト比
#define NEAR_CLIP			0.0f				// ニアクリップを行う距離
#define FAR_CLIP			3000.0f				// ファークリップを行う距離
#define	PI					(float)3.1415926535897932		// 円周率
#define FRAME_RATE			(float)1000/60		// フレームレート
#define FRAME_QTY			32					// バンクあたりフレーム数
#define BANK_QTY			32					// バンク数
#define TIME_MAX			1000				// フレームタイム上限値
#define SCROLL_MIN			-150000				// スクロールバーの移動最小値
#define SCROLL_MAX			150000				// スクロールバーの移動最大値
#define FONT_SIZE			15					// デバッグ文字フォントサイズ
#define FONT_TYPE			"ＭＳ ゴシック"		// デバッグ文字フォント種別
#define RAD					(float)PI/180		// ラジアン
#define TOP					0					// RECT型にあわせた保存用変数のための定数
#define LEFT				1					// RECT型にあわせた保存用変数のための定数
#define DOWN				2					// RECT型にあわせた保存用変数のための定数
#define RIGHT				3					// RECT型にあわせた保存用変数のための定数
#define ON					1					// フラグの設定をわかりやすくするための定数
#define OFF					0					// フラグの設定をわかりやすくするための定数

// パーティクル定義
#define	PARTICLE_MAX		500					// パーティクル最大数
#define	PARTICLE_MAX_SCALE	50					// パーティクル最大スケール
#define	PARTICLE_INIT		10					// パーティクル初期数
#define	BURSTLEVEL_INIT		70					// 噴火レベル初期値
#define	PARTICLE_AFTERIMAGE 15					// パーティクル残像数

#define DEFAULT_COLOR_R 0x00
#define DEFAULT_COLOR_G 0x40
#define DEFAULT_COLOR_B 0x80

//---- マクロ ----
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(o)	if(o) {o->Release() ;o=NULL;}
#endif


//----- 頂点フォーマット定義
struct VERTEX {
	float x, y, z;		// 座標
	DWORD color;
	float tu, tv;		// テクスチャ

};
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 座標軸表示用フォーマット
struct LVERTEX {
	float x, y, z;		// 座標
	DWORD diffuse;		// ディフューズ色
};
#define	FVF_LVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

//--- 座標用定義(座標・回転併用)
typedef struct{
	float x,y,z;		// 座標・回転用の各軸用X,Y,Z変数
}POSITION3;

//--- 座標用定義(座標・回転併用)
typedef struct{
	float x,y,z,w;		// 座標・回転用の各軸用X,Y,Z変数
}POSITION4;

//--- 座標用定義(座標・回転併用)
typedef struct{
	bool x,y,z,w;		// 座標・回転用の各軸用X,Y,Z変数
}FLG4;

#endif
