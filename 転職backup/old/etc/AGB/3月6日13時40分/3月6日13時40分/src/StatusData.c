#include "all.h"

/*
// ------- プレイヤーステータス -------
typedef struct {
	s32	x;				// X座標:符号有り固定小数点型(16-16)
	s32	y;				// Y座標:符号有り固定小数点型(16-16)
	s16	localX;			// ローカルX座標
	s16	localY;			// ローカルY座標
	s16	hp      :12;	// ヒットポイント（-2048～2047）
	s8	sp;				// スキルポイント（-128～127）
	s8	coin;			// 取得コイン枚数（-128～127）
	u8	turn    : 2;	// 向き（4方向:2bit)
	u8	type    : 4;	// 現在の行動状態（16種類:4bit)
	u8	anime;			// アニメーションのカウンタ（0～15)
	u8	cnt;			// フレームのカウンタ
	u16	keep    :10;	// ボタン押し時間の制御（0～1023)
	u8	skillflg: 1;	// スキル発動フラグ（ON,OFF)
	u8	spflg   : 1;	// 必殺技発動フラグ（ON,OFF)
	u8	atk     : 2;	// 連続攻撃の状態を格納（4パターン:2bit)
	u8	effect  : 1;	// エフェクトフラグ（ON,OFF)
	s8	invincible;		// 無敵時間のカウンタ
	s8	dead;			// 死亡時間のカウンタ
	u8	name    : 3;	// プレイヤーキャラクターネーム(最大8種類)
	u8	coloer  : 4;	// 使用パレット（16色:4bit)
} PLAYER;
*/
const PLAYER PLAYER_STATUS[] = {
	{ 104, 64, 104, 64, 300, 0, TURN_D, STAND, 0, 0, 0, OFF, OFF, 0, OFF, 0, 0, SPEED, 0 },
	{ 104, 64, 104, 64, 300, 0, TURN_D, STAND, 0, 0, 0, OFF, OFF, 0, OFF, 0, 0, MAGIC, 0 },
	{ 104, 64, 104, 64, 300, 0, TURN_D, STAND, 0, 0, 0, OFF, OFF, 0, OFF, 0, 0, PETIT, 0 },
	{ 104, 64, 104, 64, 300, 0, TURN_D, STAND, 0, 0, 0, OFF, OFF, 0, OFF, 0, 0, POWER, 0 },
	{ 104, 64, 104, 64, 300, 0, TURN_D, STAND, 0, 0, 0, OFF, OFF, 0, OFF, 0, 0, BEAST, 0 },
};

// ------- エネミーステータス -------
typedef struct {
	s16	hp;				// ヒットポイント
	u8	count;			// 敵の攻撃間隔用カウンタ（0～255)
	u8	turn  : 2;		// 向き（4方向:2bit)
	u8	type  : 4;		// 現在の行動状態（16種類:4bit)
	u8	hit   : 4;		// 被弾フラグ（各1bitが各プレイヤーに対応)
	u8	name  : 5;		// 敵キャラクターネーム
	u8	coloer: 4;		// 使用パレット（16色:4bit)
	u8	effect: 1; 		// エフェクトフラグ
	u8	dead  : 1; 		// 死亡判定フラグ
} ENEMY;
EX enum { SLIME, RAFRY, USA, SUSI, PLAZUMA, UNI, TORI, KAERU, KINOKO, BAT, GHOST, DOM, SASORI } EnemyName;
*/
// 敵の基本データ
const ENEMY ENEMY_STATUS[] = {
	{ 320,  0, 0, 0, 0, SLIME,  3, 0, 0 }, // スライム
	{ 420,  0, 0, 0, 0, USA,    3, 0, 0 }, // ウサ（トカゲ）
	{ 100,  0, 0, 0, 0, PLAZUMA,4, 0, 0 }, // プラズマ
	{ 580,  0, 0, 0, 0, RAFRY,  3, 0, 0 }, // ラフリ
//	{ 370,  0, 0, 0, 0, SUSI,   3, 0, 0 }, // スシ
	{ 400,  0, 0, 0, 0, UNI,    4, 0, 0 }, // ウニ
//	{ 250,  0, 0, 0, 0, TORI,   4, 0, 0 }, // トリ
	{ 280,  0, 0, 0, 0, KINOKO, 5, 0, 0 }, // キノコ
	{ 180,  0, 0, 0, 0, BAT,    5, 0, 0 }, // 蝙蝠
	{ 550,  0, 0, 0, 0, GHOST,  6, 0, 0 }, // ゴースト
	{ 1500, 0, 0, 0, 0, DOM,    6, 0, 0 }, // ドム
	{ 600,  0, 0, 0, 0, SASORI, 6, 0, 0 }, // サソリ
};
