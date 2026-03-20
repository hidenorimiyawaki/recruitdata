/************************************************************
*						DEFINE.H							*
*															*
*		このファイルでは、定数定義のをします。				*
*															*
*				作成日：2003/09/19							*
*			最終更新日：2003/09/19							*
*															*
************************************************************/


//-------- 定数定義
#define CLASS_NAME		"Nocturn"									// ウィンドウクラス名
#define CAPTION_NAME	"GAME PROTO"								// キャプション名

const float FRAME_RATE		= 1000/60;								// フレームレート
const int	SCREEN_WIDTH	= 640;									// スクリーンの幅
const int	SCREEN_HEIGHT	= 480;									// スクリーンの高さ
const float	ASPECT_RATIO	= (float)SCREEN_WIDTH/SCREEN_HEIGHT;	// アスペクト比
const int	FONT_SIZE		= 20;									// デバッグ文字フォントサイズ
const char*	FONT_TYPE		= "ＭＳ ゴシック";						// デバッグ文字フォント種別
const float	NEAR_CLIP		= 100.0;								// ニアクリップを行う距離
const float	FAR_CLIP		= 30000.0;								// ファークリップを行う距離
const float	PI				= (float)3.141592653589;				// 円周率
const float	RAD				= PI/180;								// ラジアン

const float ROTATE_SPEED	= (float)0.04;							// 回転速度
const float MOVE_SPEED		= (float)10.0;							// 移動速度
const float HIT_SIZE		= (float)40.0;							// 当たり判定サイズ

#define		YUKA_MAX	4
#define		PLAYER_MOVE	15

#define		PLAYER_RANGE_X	400
#define		PLAYER_RANGE_Y	300

#define		ENEMY_RANGE_X	600
#define		ENEMY_RANGE_Y	500

#define		GAME_END_FOG	9000
#define		FOG_POS			100

#define		TITLE_MAX		4

#define		EF_OFFSET		10

#define		ENEMY_START1	30
#define		ENEMY_START2	3
#define		ENEMY_START3	4
#define		ENEMY_START4	5
#define		ENEMY_START5	7

#define		ENEMY_GROUP		8
#define		ENEMY_GROUP2	18