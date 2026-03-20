#ifndef	_H_DEFINE_
#define _H_DEFINE_
 
//---- 定数 ----
#define FRAME_RATE			1000/60							// フレームレート
#define SCREEN_WIDTH		800								// スクリーンの幅
#define SCREEN_HEIGHT		600								// スクリーンの高さ
#define ASPECT_RATIO		SCREEN_WIDTH/SCREEN_HEIGHT		// アスペクト比
#define FONT_SIZE			15								// デバッグ文字フォントサイズ
#define FONT_TYPE			"ＭＳ ゴシック"					// デバッグ文字フォント種別
#define NEAR_CLIP			(float)1.0						// ニアクリップを行う距離
#define FAR_CLIP			(float)30000.0					// ファークリップを行う距離
#define PI					3.141592653589					// 円周率
#define RAD					(float)PI/180					// ラジアン
#define CASH_MAX			50								// キャッシュの最大数
#define MAX_DATA			200								// 最大データ数
#define TOP					0								// RECT型にあわせた保存用変数のための定数
#define LEFT				1								// RECT型にあわせた保存用変数のための定数
#define DOWN				2								// RECT型にあわせた保存用変数のための定数
#define RIGHT				3								// RECT型にあわせた保存用変数のための定数
#define ON					1								// フラグの設定をわかりやすくするための定数
#define OFF					0								// フラグの設定をわかりやすくするための定数
#define SET_OFFSET			459
//---- マクロ ----
#define SAFE_RELEASE(o)	if(o) {o->Release() ;o=NULL;}

#endif