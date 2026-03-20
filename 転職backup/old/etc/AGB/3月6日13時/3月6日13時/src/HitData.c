#include "all.h"

/*
// ------- 当たり判定型 -------
typedef struct {
	s8	x;		// 始点のX座標
	s8	y;		// 始点のY座標
	u8	wid;	// 横の長さ
	u8	hei;	// 縦の長さ
} HIT_TYPE;
*/
// ======= 攻撃当たり判定データ ======== S
const HIT_TYPE ATTACK[] = {
	{  0,  0,  0,  0 }, // 
	{  0,  0, 32, 32 }, // スライムの体
	{  0,-32, 32, 32 },	// 上:2
	{  0, 32, 32, 32 },	// 下:3
	{ 32,  0, 32, 32 },	// 右:4
	{-32,  0, 32, 32 },	// 左:5
	{  0,  0, 16, 16 },	// 移動状態の魔法
	{  0,  0, 16, 16 },	// 移動状態の魔法
	{  0,  0, 32, 32 },	// カウンター
	{  0,  0, 32, 32 },	// カウンター
};
// 命中判定用添え字のデファイン
#define	SP_BODY			1
#define	MG_BODY			1
#define	PT_BODY			1
#define	PW_BODY			1
#define	BS_BODY			1

#define	US_BODY			1
#define	PZ_BODY			1
#define	RF_BODY			1
#define	UI_BODY			1
#define	TR_BODY			1
#define	KN_BODY			1
#define	KO_BODY			1
#define	GO_BODY			1
#define	DO_BODY			1
#define	SA_BODY			1

#define	KNIGHT_BODY		1

// 攻撃範囲用添え字デファイン
#define	SP_R_ATK		1
#define	SP_L_ATK		1
#define	SP_U_ATK		1
#define	SP_D_ATK		1
#define	PT_BODY			1
#define	PW_BODY			1
#define	BS_BODY			1
