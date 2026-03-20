//**************************************************************************** S
//
//	 ソース名称		:	define.h
//
//==============================================================================
//	 コメント		:	defineデータの定義ヘッダー
//	 最終更新日		:	2003/ 2/23 (日)
//**************************************************************************** E

#ifndef		___DEFINE_H___
#define		___DEFINE_H___


// ここにでdefineで定義したデータを書き込む

// ======= 基本定数 ======= S
#define		ON						1
#define		OFF						0

#define		ENABLE					1
#define		DISABLE					0

#define		TRUE					1
#define		FALSE					0

#define		MAP_CHAR_MAX			32		// マップデータの最大キャラ数（縦横）
#define		MAP_DOT_MAX				256		// マップデータの最大ドット数（縦横）

#define		LCD_CHAR_H_MAX			30		// 表示画面上の横最大キャラ数
#define		LCD_CHAR_V_MAX			20		// 表示画面上の縦最大キャラ数
#define		ENEMY_MAX			4		// 敵の最大数

#define		OBJ_MAX					128		// スプライトの最大値

#define		DEX						10		// 10進数
#define		HEX						16		// 16進数

#define		WORLD_H_CHARA_MAX		90		// ワールドマップの横最大キャラ数
#define		WORLD_V_CHARA_MAX		60		// ワールドマップの縦最大キャラ数
#define		WORLD_V_DOT_MAX			(WORLD_V_CHARA_MAX * 8)
#define		WORLD_H_DOT_MAX			(WORLD_H_CHARA_MAX * 8)

#define		HERO_CENTER_X			104		// 自キャラ中心座標
#define		HERO_CENTER_Y			64		// 

#define		ENEMY_CNT_MAX			5		// 敵の同時出現数

#define		SIO_PLAYER_MAX			0		// 通信プレイヤー最大数

// ======= 基本定数 ======= E

// ======= OAM関連定数 ======= S
#define		LANK_SPLITE_NO			0+PlayerNo
#define		SPECIAL_SPLITE_NO		4+PlayerNo
#define		SHOT_P_SPLITE_NO		16+PlayerNo
#define		SHOT_E_SPLITE_NO		20+EnemyNo
#define		DAM_P_SPLITE_NO			30+PlayerNo
#define		DAM_E_SPLITE_NO			34+EnemyNo
//#define		PLAYER_SPLITE_NO		44+PlayerNo
#define		PLAYER_SPLITE_NO		PlayerNo
//#define		ENEMY_SPLITE_NO			(48+EnemyNo)
#define		ENEMY_SPLITE_NO			EnemyNo+1
#define		COIN_SPLITE_NO			58+EnemyNo

#define		LANK_CHAR_NO			OBJ_MODE0_VRAM+0+2*PlayerNo
#define		SPECIAL_CHAR_NO			OBJ_MODE0_VRAM+(LANK_CHAR_NO)+2048*PlayerNo
#define		SHOT_P_CHAR_NO			OBJ_MODE0_VRAM+(SPECIAL_CHAR_NO)+512*PlayerNo
#define		SHOT_E_CHAR_NO			OBJ_MODE0_VRAM+(SHOT_P_CHAR_NO)+512*EnemyNo
#define		DAM_P_CHAR_NO			OBJ_MODE0_VRAM+(SHOT_E_CHAR_NO)+512*PlayerNo
#define		DAM_E_CHAR_NO			OBJ_MODE0_VRAM+(DAM_P_CHAR_NO)+512*EnemyNo
#define		PLAYER_CHAR_NO			(OBJ_MODE0_VRAM+(DAM_E_CHAR_NO)+1024*PlayerNo)
//#define		ENEMY_CHAR_NO			OBJ_MODE0_VRAM+(PLAYER_CHAR_NO)+512*EnemyNo
#define		ENEMY_CHAR_NO			OBJ_MODE0_VRAM+4096 + 1024*(EnemyNo+1)
#define		COIN_CHAR_NO			OBJ_MODE0_VRAM+(ENEMY_CHAR_NO)+4*EnemyNo

// ======= OAM関連定数 ======= E







// ======= キー入力関連 ======= S
//#define	R_KEY			0x0010		//  右 キー
//#define	L_KEY			0x0020		//  左 キー
//#define	U_KEY			0x0040		//  上 キー
//#define	D_KEY			0x0080		//  下 キー
#define		R_U_KEY			0x0050		// 右上キー
#define		R_D_KEY			0x0090		// 右下キー
#define		L_U_KEY			0x0060		// 左上キー
#define		L_D_KEY			0x00A0		// 左下キー

#define		KEY_BUF_SIZE		128			// キーリングバッファサイズ
#define		KEY_CNT_MASK		(KEY_BUF_SIZE - 1)
											// KeyBufの要素数用のマスク定義
// ======= キー入力関連 ======= E


// ======= キャラクターの状態 ======= S
#define		STAND			0		// 通常
#define		ATK				1		// 攻撃 
#define		JUMP			2		// ジャンプ
#define		SKILL			3		// スキル
#define		INTERVAL		4		// 攻撃間隔
#define		DAMAGE			5		// ダメージ
#define		SPECIAL			6		// 特殊攻撃
#define		DEAD			7		// 死亡状態
// ======= キャラクターの状態 ======= E


// ======= キャラクターの向き ======= S
#define		TURN_U			0		// 上
#define		TURN_R			1		// 右
#define		TURN_D			2		// 下
#define		TURN_L			3		// 左
	// 上向きから時計回り
// ======= キャラクターの向き ======= E


// =======  プレイヤーの種類  ======= S
#define		SPEED			0
#define		MAGIC			1
#define		PETIT			2
#define		POWER			3
#define		BEAST			4
// =======  プレイヤーの種類  ======= E


// ===========  敵の種類  =========== S
#define		SLIME			0
#define		RAFRY			1
#define		USA				2
#define		SUSI			3
#define		PLAZUMA			4
#define		UNI				5
#define		TORI			6
#define		KAERU			7
#define		KINOKO			8
#define		BAT				9
#define		SASORI			10
#define		HAE				11
#define		GHOST			12
#define		DOM				13
// ===========  敵の種類  =========== E


// ======= OAM 関連 ====== S
//	上位4ビットが形、下位4ビットがサイズを示す
#define		SIZE8x8			0x00
#define		SIZE16x16		0x01
#define		SIZE32x32		0x02
#define		SIZE64x64		0x03
#define		SIZE16x8		0x10
#define		SIZE32x8		0x11
#define		SIZE32x16		0x12
#define		SIZE64x32		0x13
#define		SIZE8x16		0x20
#define		SIZE8x32		0x21
#define		SIZE16x32		0x22
#define		SIZE32x64		0x23
// ======= OAM 関連 ====== E

#endif