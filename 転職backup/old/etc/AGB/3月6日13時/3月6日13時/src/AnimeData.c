#include "all.h"

//*****************************************************************************S
//
//	プログラム名称	:	アニメ データ
//	 ソース名称		:	AnimeData.c
//
//==============================================================================
//
//	 コメント		:	アニメーションパターンを配列化（構造体）
//
//*****************************************************************************E

/*
// 上位4ビットが形、下位4ビットがサイズを示す
#define	SIZE8x8		0x00
#define	SIZE16x16	0x01
#define	SIZE32x32	0x02
#define	SIZE64x64	0x03
#define	SIZE16x8	0x10
#define	SIZE32x8	0x11
#define	SIZE32x16	0x12
#define	SIZE64x32	0x13
#define	SIZE8x16	0x20
#define SIZE8x32	0x21
#define SIZE16x32	0x22
#define SIZE32x64	0x23

// ----- 構造体宣言 -----
typedef struct {
	const u8	*chara;		// キャラクターデータ
	u8			size;		// スプライトのサイズ
	u8			frame;		// 表示されるフレーム数
	s8			hofs;		// H オフセット
	s8			vofs;		// V オフセット
	u8			hit;		// やられ範囲の指定（別テーブルデータの要素数）
	u8			atk;		// 攻撃範囲の指定（別テーブルデータの要素数）
	u8			dam;		// 攻撃力
	u8			type;		// その他特殊状態（ふっとばし等）
} ANIME;
*/

// ************** スピード ***************S

// ****通常状態
// 前
const ANIME		SP_STAND_F[] = {
	{ sp_01_f_Char, SIZE32x32, 0, 0, 0, 1, 0, 0, 0 },
};
// 横
const ANIME		SP_STAND_S[] = {
	{ sp_01_s_Char, SIZE32x32, 0, 0, 0, 1, 0, 0, 0 },
};
// 後
const ANIME		SP_STAND_R[] = {
	{ sp_01_r_Char, SIZE32x32, 0, 0, 0, 1, 0, 0, 0 },
};

// ****移動状態
// 前
const ANIME		SP_WALK_F[] = {
	{ sp_11_f_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_12_f_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_13_f_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_14_f_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ

};
// 横
const ANIME		SP_WALK_S[] = {
	{ sp_11_s_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_12_s_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_13_s_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_14_s_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		SP_WALK_R[] = {
	{ sp_11_r_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_12_r_Char, SIZE32x32, 8, 0, 2, 1, 0, 0, 0 },
	{ sp_13_r_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ sp_14_r_Char, SIZE32x32, 8, 0, 2, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****攻撃状態
// 前
const ANIME		SP_ATK_F[] = {
	{ sp_21_f_Char, SIZE32x32, 8,  1, 2, 0, 3, 0, 0 },
	{ sp_22_f_Char, SIZE32x64, 4,  4, 3, 0, 3,10, 0 },
	{ sp_23_f_Char, SIZE32x32, 4, -1, 2, 0, 0, 0, 0 },
	{ sp_24_f_Char, SIZE32x32, 8, -1, 2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		SP_ATK2_F[] = {
	{ sp_25_f_Char, SIZE32x32, 8, -1, 2, 0, 3, 0, 0 },
	{ sp_26_f_Char, SIZE32x64, 4,  0, 3, 0, 3,10, 0 },
	{ sp_27_f_Char, SIZE32x32, 16, -1, 2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		SP_ATK_S[] = {
	{ sp_21_s_Char, SIZE32x32, 8,  0, 0, 0, 4, 0, 0 },
	{ sp_22_s_Char, SIZE64x32, 4,  0, 0, 0, 4,10, 0 },
	{ sp_23_s_Char, SIZE32x32, 4,  6, 0, 0, 0, 0, 0 },
	{ sp_24_s_Char, SIZE32x32, 8,  6, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		SP_ATK2_S[] = {
	{ sp_25_s_Char, SIZE32x32, 8, -1, 0, 0, 4, 0, 0 },
	{ sp_26_s_Char, SIZE64x32, 4,  0, 0, 0, 4,10, 0 },
	{ sp_27_s_Char, SIZE32x32, 8,  4, 0, 0, 0, 0, 0 },
	{ sp_28_s_Char, SIZE32x32, 8,  4, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// 後
const ANIME		SP_ATK_R[] = {
	{ sp_21_r_Char, SIZE32x32, 8, 0,  0, 0, 2, 0, 0 },
	{ sp_22_r_Char, SIZE32x64, 4, 0,-34, 0, 2,10, 0 },
	{ sp_23_r_Char, SIZE32x32, 4, 0,  0, 0, 0, 0, 0 },
	{ sp_24_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		SP_ATK2_R[] = {
	{ sp_25_r_Char, SIZE32x32, 8, 0,  0, 0, 2, 0, 0 },
	{ sp_26_r_Char, SIZE32x64, 4, 0,-34, 0, 2,10, 0 },
	{ sp_27_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ sp_28_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ジャンプ状態
// 前
const ANIME		SP_JUMP_F[] = {
	{ sp_31_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ sp_31_f_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ sp_32_f_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ sp_33_f_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ sp_34_f_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ sp_35_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		SP_JUMP_S[] = {
	{ sp_31_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ sp_31_s_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ sp_32_s_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ sp_33_s_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ sp_34_s_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ sp_35_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		SP_JUMP_R[] = {
	{ sp_31_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ sp_31_r_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ sp_32_r_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ sp_33_r_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ sp_34_r_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ sp_35_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 上:2 下:3 右:4 左:5
// ****技状態
// 前
const ANIME		SP_SKILL_F[] = {
	{ sp_41_f_Char, SIZE32x32, 8, 0, 0, 0, 3,10, 0 },
	{ sp_42_f_Char, SIZE32x32, 4, 0, 0, 0, 3,10, 0 },
	{ sp_43_f_Char, SIZE32x32, 4, 0, 0, 0, 3,10, 0 },
	{ sp_42_f_Char, SIZE32x32, 4, 0, 0, 0, 3,10, 0 },
	{ sp_43_f_Char, SIZE32x32, 4, 0, 0, 0, 3,10, 0 },
	{ sp_42_f_Char, SIZE32x32, 4, 0, 0, 0, 3,10, 0 },
	{ sp_43_f_Char, SIZE32x32, 4, 0, 0, 0, 3,10, 0 },
	{ sp_44_f_Char, SIZE32x32, 8, 0, 0, 0, 3,10, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		SP_SKILL_S[] = {
	{ sp_41_s_Char, SIZE32x32, 8, 0, 0, 0, 4,10, 0 },
	{ sp_42_s_Char, SIZE64x32, 4, 0, 0, 0, 4,10, 0 },
	{ sp_43_s_Char, SIZE64x32, 4, 0, 0, 0, 4,10, 0 },
	{ sp_42_s_Char, SIZE64x32, 4, 0, 0, 0, 4,10, 0 },
	{ sp_43_s_Char, SIZE64x32, 4, 0, 0, 0, 4,10, 0 },
	{ sp_42_s_Char, SIZE64x32, 4, 0, 0, 0, 4,10, 0 },
	{ sp_43_s_Char, SIZE64x32, 4, 0, 0, 0, 4,10, 0 },
	{ sp_44_s_Char, SIZE32x32, 8, 0, 0, 0, 4,10, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		SP_SKILL_R[] = {
	{ sp_41_r_Char, SIZE32x32, 8, 0,  0, 0, 2,10, 0 },
	{ sp_42_r_Char, SIZE32x64, 4, 0,-32, 0, 2,10, 0 },
	{ sp_43_r_Char, SIZE32x64, 4, 0,-32, 0, 2,10, 0 },
	{ sp_42_r_Char, SIZE32x64, 4, 0,-32, 0, 2,10, 0 },
	{ sp_43_r_Char, SIZE32x64, 4, 0,-32, 0, 2,10, 0 },
	{ sp_42_r_Char, SIZE32x64, 4, 0,-32, 0, 2,10, 0 },
	{ sp_43_r_Char, SIZE32x64, 4, 0,-32, 0, 2,10, 0 },
	{ sp_44_r_Char, SIZE32x32, 8, 0,  0, 0, 2,10, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ダメージ状態
// 前
const ANIME		SP_DAM_F[] = {
	{ sp_51_f_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		SP_DAM_S[] = {
	{ sp_51_s_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		SP_DAM_R[] = {
	{ sp_51_r_Char, SIZE32x32, 20, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****必殺技状態
// 前
const ANIME		SP_SPECIAL_F[] = {
	{ sp_61_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sp_62_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sp_63_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		SP_SPECIAL_S[] = {
	{ sp_61_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sp_62_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sp_63_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		SP_SPECIAL_R[] = {
	{ sp_61_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ sp_62_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ sp_63_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****死亡状態
// 前
const ANIME		SP_DEATH_F[] = {
	{ sp_90_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};


// ************** マジシャン **************S

// ****通常状態
// 前
const ANIME		MG_STAND_F[] = {
	{ mg_01_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 横
const ANIME		MG_STAND_S[] = {
	{ mg_01_s_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 後
const ANIME		MG_STAND_R[] = {
	{ mg_01_r_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};

// ****移動状態
// 前
const ANIME		MG_WALK_F[] = {
	{ mg_11_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_12_f_Char, SIZE32x32, 8, 0, 2, 0, 0, 0, 0 },
	{ mg_13_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_14_f_Char, SIZE32x32, 8, 0, 2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		MG_WALK_S[] = {
	{ mg_11_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_12_s_Char, SIZE32x32, 8, 0, 1, 0, 0, 0, 0 },
	{ mg_13_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_14_s_Char, SIZE32x32, 8, 0, 1, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		MG_WALK_R[] = {
	{ mg_11_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_12_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_13_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_14_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****攻撃状態
// 前
const ANIME		MG_ATK_F[] = {
	{ mg_21_f_Char, SIZE32x32, 8, 0, 2, 0, 0, 0, 0 },
	{ mg_22_f_Char, SIZE32x32, 8, 0, 4, 0, 0, 0, 0 },
	{ mg_23_f_Char, SIZE32x32, 8, 0, 4, 0, 0, 0, 0 },
	{ mg_24_f_Char, SIZE32x32, 8, 0, 4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		MG_ATK_S[] = {
	{ mg_21_s_Char, SIZE32x32, 8, 2, 0, 0, 0, 0, 0 },
	{ mg_22_s_Char, SIZE32x32, 8, 4, 0, 0, 0, 0, 0 },
	{ mg_23_s_Char, SIZE32x32, 8, 4, 0, 0, 0, 0, 0 },
	{ mg_24_s_Char, SIZE32x32, 8, 4, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		MG_ATK_R[] = {
	{ mg_21_r_Char, SIZE32x32, 8, 0, -2, 0, 0, 0, 0 },
	{ mg_22_r_Char, SIZE32x32, 8, 0, -4, 0, 0, 0, 0 },
	{ mg_23_r_Char, SIZE32x32, 8, 0, -4, 0, 0, 0, 0 },
	{ mg_24_r_Char, SIZE32x32, 8, 0, -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ジャンプ状態
// 前
const ANIME		MG_JUMP_F[] = {
	{ mg_31_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ mg_31_f_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ mg_32_f_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ mg_32_f_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ mg_33_f_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ mg_33_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// 横
const ANIME		MG_JUMP_S[] = {
	{ mg_31_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ mg_31_s_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ mg_32_s_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ mg_32_s_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ mg_33_s_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ mg_33_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		MG_JUMP_R[] = {
	{ mg_31_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ mg_31_r_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ mg_32_r_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ mg_32_r_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ mg_33_r_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ mg_33_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****技状態
// 前
const ANIME		MG_SKILL_F[] = {
	{ mg_41_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_42_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_43_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_44_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_45_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_44_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_45_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_44_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_45_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// ****ダメージ状態
// 前
const ANIME		MG_DAM_F[] = {
	{ mg_51_f_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		MG_DAM_S[] = {
	{ mg_51_s_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		MG_DAM_R[] = {
	{ mg_51_r_Char, SIZE32x32, 20, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****必殺技状態
// 前
const ANIME		MG_SPECIAL_F[] = {
	{ mg_61_f_Char, SIZE32x32, 8, 0, 0, 0, 1, 1, 0 },
	{ mg_62_f_Char, SIZE32x32, 8, 0, 0, 0, 1, 1, 0 },
	{ mg_63_f_Char, SIZE32x32, 8, 0, 0, 0, 1, 1, 0 },
	{ mg_64_f_Char, SIZE32x32, 8, 0, 0, 0, 1, 1, 0 },
	{ mg_65_f_Char, SIZE32x32, 8, 0, 0, 0, 1, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ダメージ状態
// 前
const ANIME		MG_DEATH_F[] = {
	{ mg_90_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};

// ************** プチ **************S

// ****通常状態
// 前
const ANIME		PT_STAND_F[] = {
	{ pt_01_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 横
const ANIME		PT_STAND_S[] = {
	{ pt_01_s_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 後
const ANIME		PT_STAND_R[] = {
	{ pt_01_r_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};

// ****移動状態
// 前
const ANIME		PT_WALK_F[] = {
	{ pt_11_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_12_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_13_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_14_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PT_WALK_S[] = {
	{ pt_11_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_12_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_13_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_14_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PT_WALK_R[] = {
	{ pt_11_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_12_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_13_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_14_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****攻撃状態
// 前
const ANIME		PT_ATK_F[] = {
	{ pt_21_f_Char, SIZE32x32,  6, 0,  6, 0, 3, 3, 0 },
	{ pt_22_f_Char, SIZE32x32,  8, 0, 10, 0, 3, 3, 0 },
	{ pt_23_f_Char, SIZE32x32,  6, 0,  6, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PT_ATK_S[] = {
	{ pt_21_s_Char, SIZE32x32, 6,  8, 0, 0, 4, 0, 0 },
	{ pt_22_s_Char, SIZE32x32, 8, 16, 0, 0, 4, 3, 0 },
	{ pt_23_s_Char, SIZE32x32, 6,  8, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PT_ATK_R[] = {
	{ pt_21_r_Char, SIZE32x32, 6, 0, -6, 0, 2, 0, 0 },
	{ pt_22_r_Char, SIZE32x32, 8, 0,-10, 0, 2, 3, 0 },
	{ pt_23_r_Char, SIZE32x32, 6, 0, -6, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ジャンプ状態
// 前
const ANIME		PT_JUMP_F[] = {
	{ pt_31_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ pt_31_f_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ pt_32_f_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ pt_32_f_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ pt_33_f_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ pt_33_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PT_JUMP_S[] = {
	{ pt_31_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ pt_31_s_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ pt_32_s_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ pt_32_s_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ pt_33_s_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ pt_33_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PT_JUMP_R[] = {
	{ pt_31_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ pt_31_r_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ pt_32_r_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ pt_32_r_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ pt_33_r_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ pt_33_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****技状態
// 前
const ANIME		PT_SKILL_F[] = {
	{ pt_41_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_42_f_Char, SIZE32x32, 180, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PT_SKILL_S[] = {
	{ pt_41_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_42_s_Char, SIZE32x32, 180, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PT_SKILL_R[] = {
	{ pt_41_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ pt_42_r_Char, SIZE32x32, 180, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ダメージ状態
// 前
const ANIME		PT_DAM_F[] = {
	{ pt_51_f_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PT_DAM_S[] = {
	{ pt_51_s_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PT_DAM_R[] = {
	{ pt_51_r_Char, SIZE32x32, 20, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****必殺技状態
// 前
const ANIME		PT_SPECIAL_F[] = {
	{ pt_61_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_62_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pt_63_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****死亡状態
// 前
const ANIME		PT_DEATH_F[] = {
	{ pt_90_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};

// ************** ビースト **************S

// ****通常状態
// 前
const ANIME		BS_STAND_F[] = {
	{ bs_01_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 横
const ANIME		BS_STAND_S[] = {
	{ bs_01_s_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 後
const ANIME		BS_STAND_R[] = {
	{ bs_01_r_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};

// ****移動状態
// 前
const ANIME		BS_WALK_F[] = {
	{ bs_11_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_12_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_13_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_14_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ

};
// 横
const ANIME		BS_WALK_S[] = {
	{ bs_11_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_12_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_13_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_14_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		BS_WALK_R[] = {
	{ bs_11_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_12_r_Char, SIZE32x32, 8, 0, 2, 0, 0, 0, 0 },
	{ bs_13_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_14_r_Char, SIZE32x32, 8, 0, 2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****攻撃状態
// 前
const ANIME		BS_ATK_F[] = {
	{ bs_21_f_Char, SIZE32x32,  8, 0,  6, 0, 3, 0, 0 },
	{ bs_22_f_Char, SIZE32x64,  4, 0, 10, 0, 3, 2, 0 },
	{ bs_23_f_Char, SIZE32x32,  8, 0,  6, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		BS_ATK2_F[] = {
	{ bs_24_f_Char, SIZE32x32,  8, 0,  6, 0, 3, 0, 0 },
	{ bs_25_f_Char, SIZE32x64,  4, 0, 10, 0, 3, 2, 0 },
	{ bs_26_f_Char, SIZE32x32,  8, 0,  6, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		BS_ATK3_F[] = {
	{ bs_27_f_Char, SIZE32x32, 16, 0,  6, 0, 3, 0, 0 },
	{ bs_28_f_Char, SIZE32x64,  4, 0, 10, 0, 3, 2, 0 },
	{ bs_29_f_Char, SIZE32x32, 16, 0,  6, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// 横
const ANIME		BS_ATK_S[] = {
	{ bs_21_s_Char, SIZE32x32, 8,  8, 0, 0, 4, 0, 0 },
	{ bs_22_s_Char, SIZE64x32, 4, 16, 0, 0, 4, 2, 0 },
	{ bs_23_s_Char, SIZE32x32, 8,  8, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		BS_ATK2_S[] = {
	{ bs_24_s_Char, SIZE32x32, 8,  8, 0, 0, 4, 0, 0 },
	{ bs_25_s_Char, SIZE64x32, 4, 16, 0, 0, 4, 2, 0 },
	{ bs_26_s_Char, SIZE32x32, 8,  8, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		BS_ATK3_S[] = {
	{ bs_27_s_Char, SIZE32x32, 16,  8, 0, 0, 4, 0, 0 },
	{ bs_28_s_Char, SIZE64x32,  4, 16, 0, 0, 4, 2, 0 },
	{ bs_29_s_Char, SIZE32x32, 16,  8, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// 後
const ANIME		BS_ATK_R[] = {
	{ bs_21_r_Char, SIZE32x32, 8,  0,  0, 0, 2, 0, 0 },
	{ bs_22_r_Char, SIZE32x64, 4,  1,-34, 0, 2, 2, 0 },
	{ bs_23_r_Char, SIZE32x32, 8,  1, -2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		BS_ATK2_R[] = {
	{ bs_24_r_Char, SIZE32x32, 8,  0,  0, 0, 2, 0, 0 },
	{ bs_25_r_Char, SIZE32x64, 4, -1,-34, 0, 2, 2, 0 },
	{ bs_26_r_Char, SIZE32x32, 8, -1, -2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		BS_ATK3_R[] = {
	{ bs_27_r_Char, SIZE32x32, 16,  0,  0, 0, 2, 0, 0 },
	{ bs_28_r_Char, SIZE32x64,  4,  0,-36, 0, 2, 2, 0 },
	{ bs_29_r_Char, SIZE32x32, 16,  0, -2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ジャンプ状態
// 前
const ANIME		BS_JUMP_F[] = {
	{ bs_31_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ bs_31_f_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ bs_32_f_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ bs_32_f_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ bs_33_f_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ bs_33_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		BS_JUMP_S[] = {
	{ bs_31_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ bs_31_s_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ bs_32_s_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ bs_32_s_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ bs_33_s_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ bs_33_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		BS_JUMP_R[] = {
	{ bs_31_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ bs_31_r_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ bs_32_r_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ bs_32_r_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ bs_33_r_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ bs_33_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****技状態
// 前
const ANIME		BS_SKILL_F[] = {
	{ bs_41_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_42_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_43_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		BS_SKILL_S[] = {
	{ bs_41_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_42_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ bs_43_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		BS_SKILL_R[] = {
	{ bs_41_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ bs_42_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ bs_43_r_Char, SIZE32x32, 8, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ダメージ状態
// 前
const ANIME		BS_DAM_F[] = {
	{ bs_51_f_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		BS_DAM_S[] = {
	{ bs_51_s_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		BS_DAM_R[] = {
	{ bs_51_r_Char, SIZE32x32, 20, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****必殺技状態
// 前
const ANIME		BS_SPECIAL_F[] = {
	{ bs_61_f_Char, SIZE32x32, 8, 0, 0, 0, 8, 6, 0 },
	{ bs_62_f_Char, SIZE32x32, 8, 0, 0, 0, 8, 6, 0 },
	{ bs_63_f_Char, SIZE32x32, 8, 0, 0, 0, 8, 6, 0 },
	{ bs_64_f_Char, SIZE32x32, 8, 0, 0, 0, 8, 6, 0 },
	{ bs_65_f_Char, SIZE32x32, 8, 0, 0, 0, 8, 6, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****死亡状態
// 前
const ANIME		BS_DEATH_F[] = {
	{ bs_90_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
};

// ************** パワー **************S

// ****通常状態
// 前
const ANIME		PW_STAND_F[] = {
	{ pw_01_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 横
const ANIME		PW_STAND_S[] = {
	{ pw_01_s_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};
// 後
const ANIME		PW_STAND_R[] = {
	{ pw_01_r_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};

// ****移動状態
// 前
const ANIME		PW_WALK_F[] = {
	{ pw_11_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pw_12_f_Char, SIZE32x32, 8, 0, 2, 0, 0, 0, 0 },
	{ pw_13_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pw_14_f_Char, SIZE32x32, 8, 0, 2, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ

};
// 横
const ANIME		PW_WALK_S[] = {
	{ pw_11_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pw_12_s_Char, SIZE32x32, 8, 0, 1, 0, 0, 0, 0 },
	{ pw_13_s_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pw_14_s_Char, SIZE32x32, 8, 0, 1, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PW_WALK_R[] = {
	{ pw_11_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pw_12_r_Char, SIZE32x32, 8, 0,-1, 0, 0, 0, 0 },
	{ pw_13_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ pw_14_r_Char, SIZE32x32, 8, 0,-1, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****攻撃状態
// 前
const ANIME		PW_ATK_F[] = {
	{ pw_21_f_Char, SIZE32x32,  6, 4,  6, 0, 3,20, 0 },
	{ pw_22_f_Char, SIZE32x64,  8, 0, 10, 0, 3,20, 0 },
	{ pw_23_f_Char, SIZE32x64,  6, 0, 10, 0, 0, 0, 0 },
	{ pw_24_f_Char, SIZE32x64,  6, 0, 10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ

};
// 横
const ANIME		PW_ATK_S[] = {
	{ pw_21_s_Char, SIZE32x32, 6,  8, 0, 0, 4,20, 0 },
	{ pw_22_s_Char, SIZE64x32, 8, 16, 0, 0, 4,20, 0 },
	{ pw_23_s_Char, SIZE64x32, 6, 16, 0, 0, 0, 0, 0 },
	{ pw_24_s_Char, SIZE32x32, 6, 16, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PW_ATK_R[] = {
	{ pw_21_r_Char, SIZE32x32, 6, -4,  0, 0, 2,20, 0 },
	{ pw_22_r_Char, SIZE32x64, 8,  0,-38, 0, 2,20, 0 },
	{ pw_23_r_Char, SIZE32x64, 6,  0,-38, 0, 0, 0, 0 },
	{ pw_24_r_Char, SIZE32x32, 6,  0, -6, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ジャンプ状態
// 前
const ANIME		PW_JUMP_F[] = {
	{ pw_31_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ pw_31_f_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ pw_32_f_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ pw_32_f_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ pw_33_f_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ pw_33_f_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PW_JUMP_S[] = {
	{ pw_31_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ pw_31_s_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ pw_32_s_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ pw_32_s_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ pw_33_s_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ pw_33_s_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PW_JUMP_R[] = {
	{ pw_31_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ pw_31_r_Char, SIZE32x32, 4, 0, -14, 0, 0, 0, 0 },
	{ pw_32_r_Char, SIZE32x32, 4, 0, -22, 0, 0, 0, 0 },
	{ pw_32_r_Char, SIZE32x32, 4, 0, -20, 0, 0, 0, 0 },
	{ pw_33_r_Char, SIZE32x32, 4, 0, -16, 0, 0, 0, 0 },
	{ pw_33_r_Char, SIZE32x32, 4, 0,  -4, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****技状態
// 前
const ANIME		PW_SKILL_F[] = {
	{ pw_41_f_Char, SIZE32x32, 16, 0, 0, 0, 0, 0, 0 },
	{ pw_42_f_Char, SIZE32x32, 16, 0, 10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PW_SKILL_S[] = {
	{ pw_41_s_Char, SIZE32x32, 16, 0, 0, 0, 0, 0, 0 },
	{ pw_42_s_Char, SIZE32x32, 16, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PW_SKILL_R[] = {
	{ pw_41_r_Char, SIZE32x32, 16, 0, 0, 0, 0, 0, 0 },
	{ pw_42_r_Char, SIZE32x32, 16, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****ダメージ状態
// 前
const ANIME		PW_DAM_F[] = {
	{ pw_51_f_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PW_DAM_S[] = {
	{ pw_51_s_Char, SIZE32x32, 20, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PW_DAM_R[] = {
	{ pw_51_r_Char, SIZE32x32, 20, 0,  0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****必殺技状態
// 前
const ANIME		PW_SPECIAL_F[] = {
	{ pw_61_f_Char, SIZE32x32, 8, 0, 0, 0, 3, 1, 0 },
	{ pw_62_f_Char, SIZE32x32, 8, 0, 0, 0, 3, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		PW_SPECIAL_S[] = {
	{ pw_61_s_Char, SIZE32x32, 8, 0, 0, 0, 4, 1, 0 },
	{ pw_62_s_Char, SIZE32x32, 8, 0, 0, 0, 4, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後
const ANIME		PW_SPECIAL_R[] = {
	{ pw_61_r_Char, SIZE32x32, 8, 0,  0, 0, 2, 1, 0 },
	{ pw_62_r_Char, SIZE32x32, 8, 0,  0, 0, 2, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****死亡状態
// 前
const ANIME		PW_DEATH_F[] = {
	{ pw_90_f_Char, SIZE32x32, 0, 0, 0, 0, 0, 0, 0 },
};

// ************** 敵 *************** S
// **** スライム
const ANIME		ENEMY_SL_F[] = {
	{ sl_01_f_Char, SIZE32x32, 8, 0, 0, 1, 1, 1, 0 },
	{ sl_02_f_Char, SIZE32x32, 8, 0, 0, 1, 1, 1, 0 },
	{ sl_03_f_Char, SIZE32x32, 8, 0, 0, 1, 1, 1, 0 },
	{ sl_02_f_Char, SIZE32x32, 8, 0, 0, 1, 1, 1, 0 },
	{ sl_01_f_Char, SIZE32x32, 8, 0, 0, 1, 1, 1, 0 },
	{ sl_04_f_Char, SIZE32x32, 8, 0, 0, 1, 1, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** スライムダメージ
const ANIME		ENEMY_SL_DAM[] = {
	{ sl_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ sl_21_Char, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ヌー
const ANIME		ENEMY_NU_F[] = {
	{ nu_01_f_Char, SIZE32x32, 4, 0, 0, 1, 0, 0, 0 },
	{ nu_02_f_Char, SIZE32x32, 4, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ヌー後ろ
const ANIME		ENEMY_NU_R[] = {
	{ nu_01_r_Char, SIZE32x32, 4, 0, 0, 1, 0, 0, 0 },
	{ nu_02_r_Char, SIZE32x32, 4, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ヌーアタック
const ANIME		ENEMY_NU_ATK_F[] = {
	{ nu_01_f_Char, SIZE32x32,  4, 0, 0, 0, 1, 4, 0 },
	{ nu_11_f_Char, SIZE32x32, 12, 0, 0, 0, 0, 0, 0 },
	{ nu_01_f_Char, SIZE32x32,  4, 0, 0, 0, 1, 4, 0 },
	{ nu_12_f_Char, SIZE32x32, 12, 9, 5, 0, 1, 4, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ヌーアタック後ろ
const ANIME		ENEMY_NU_ATK_R[] = {
	{ nu_01_r_Char, SIZE32x32,  4,  0,  0, 0, 1, 4, 0 },
	{ nu_11_r_Char, SIZE32x32, 12,  0,  0, 0, 0, 0, 0 },
	{ nu_01_r_Char, SIZE32x32,  4,  0,  0, 0, 1, 4, 0 },
	{ nu_12_r_Char, SIZE32x32, 12,  9, -5, 0, 1, 4, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ヌーダメージ
const ANIME		ENEMY_NU_DAM[] = {
	{ nu_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** ラフリー
const ANIME		ENEMY_RF_F[] = {
	{ rf_01_f_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ rf_02_f_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ rf_01_f_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ rf_03_f_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ラフリー後ろ
const ANIME		ENEMY_RF_R[] = {
	{ rf_01_r_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ rf_02_r_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ rf_01_r_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ rf_03_r_Char, SIZE32x32, 13, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ラフリーアタック
const ANIME		ENEMY_RF_ATK[] = {
	{ rf_01_f_Char, SIZE32x32, 13, 0, 0, 1, 0, 1, 0 },
	{ rf_37_Char  , SIZE32x32, 13, 0, 0, 1, 0, 1, 0 },
	{ rf_36_Char  , SIZE32x32, 13, 0, 0, 1, 0, 1, 0 },
	{ rf_11_Char  , SIZE32x32, 13, 0, 0, 1, 0, 1, 0 },
	{ rf_12_Char  , SIZE32x32, 24, 0, 0, 1, 0, 1, 0 },
	{ rf_01_f_Char, SIZE32x32, 24, 0, 0, 1, 0, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ラフリーダメージ
const ANIME		ENEMY_RF_DAM[] = {
	{ rf_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ラフリー出現
const ANIME		ENEMY_RF_APP[] = {
	{ rf_31_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ rf_32_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ rf_33_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ rf_34_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ rf_35_Char, SIZE32x32, 16, 0, 0, 0, 1, 1, 0 },
	{ rf_36_Char, SIZE32x32, 16, 0, 0, 0, 1, 1, 0 },
	{ rf_37_Char, SIZE32x32, 16, 0, 0, 0, 1, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウサ
const ANIME		ENEMY_US_F[] = {
	{ us_01_f_Char, SIZE32x32, 8, 0,  0, 1, 0, 0, 0 },
	{ us_02_f_Char, SIZE32x32, 8, 0,  0, 1, 0, 0, 0 },
	{ us_03_f_Char, SIZE32x32, 6, 0, -9, 1, 0, 0, 0 },
	{ us_03_f_Char, SIZE32x32, 6, 0,-15, 1, 0, 0, 0 },
	{ us_03_f_Char, SIZE32x32, 6, 0, -9, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウサ後ろ
const ANIME		ENEMY_US_R[] = {
	{ us_01_r_Char, SIZE32x32, 8, 0,  0, 1, 0, 0, 0 },
	{ us_02_r_Char, SIZE32x32, 8, 0,  0, 1, 0, 0, 0 },
	{ us_03_r_Char, SIZE32x32, 6, 0, -9, 1, 0, 0, 0 },
	{ us_03_r_Char, SIZE32x32, 6, 0,-15, 1, 0, 0, 0 },
	{ us_03_r_Char, SIZE32x32, 6, 0, -9, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウサアタック前
const ANIME		ENEMY_US_ATK_F[] = {
	{ us_01_f_Char, SIZE32x32,  8,  0,  0, 1, 0, 0, 0 },
	{ us_02_f_Char, SIZE32x32, 16,  0,  0, 1, 0, 0, 0 },
	{ us_01_f_Char, SIZE32x32,  8,  0,  0, 0, 1, 6, 0 },
	{ us_11_f_Char, SIZE32x32, 24, 12,  5, 0, 1, 6, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウサアタック後ろ
const ANIME		ENEMY_US_ATK_R[] = {
	{ us_01_r_Char, SIZE32x32,  8,  0,  0, 1, 0, 0, 0 },
	{ us_02_r_Char, SIZE32x32, 16,  0,  0, 1, 0, 0, 0 },
	{ us_01_r_Char, SIZE32x32,  8,  0,  0, 0, 1, 6, 0 },
	{ us_11_r_Char, SIZE32x32, 24, 12, -5, 0, 1, 6, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウサダメージ
const ANIME		ENEMY_US_DAM[] = {
	{ us_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** プラズマー
const ANIME		ENEMY_PZ_F[] = {
	{ pz_01_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ pz_02_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ pz_03_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ pz_04_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** プラズマー後ろ
const ANIME		ENEMY_PZ_R[] = {
	{ pz_01_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ pz_02_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ pz_03_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ pz_04_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** プラズマーアタック
const ANIME		ENEMY_PZ_ATK_F[] = {
	{ pz_11_f_Char, SIZE32x32, 6, -5,  0, 0, 1, 0, 0 },
	{ pz_12_f_Char, SIZE32x32, 6,  0,  5, 0, 1, 2, 0 },
	{ pz_11_f_Char, SIZE32x32, 2,  0, -5, 0, 1, 2, 0 },
	{ pz_13_f_Char, SIZE32x32, 2,  5,  0, 0, 1, 2, 0 },
	{ pz_11_f_Char, SIZE32x32, 2, -5,  0, 0, 1, 2, 0 },
	{ pz_12_f_Char, SIZE32x32, 2,  0,  5, 0, 1, 2, 0 },
	{ pz_11_f_Char, SIZE32x32, 2,  0, -5, 0, 1, 2, 0 },
	{ pz_13_f_Char, SIZE32x32, 2,  5,  0, 0, 1, 2, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** プラズマーアタック後ろ
const ANIME		ENEMY_PZ_ATK_R[] = {
	{ pz_11_r_Char, SIZE32x32, 6, -5,  0, 0, 1, 2, 0 },
	{ pz_12_r_Char, SIZE32x32, 6,  0,  5, 0, 1, 2, 0 },
	{ pz_11_r_Char, SIZE32x32, 2,  0, -5, 0, 1, 2, 0 },
	{ pz_13_r_Char, SIZE32x32, 2,  5,  0, 0, 1, 2, 0 },
	{ pz_11_r_Char, SIZE32x32, 2, -5,  0, 0, 1, 2, 0 },
	{ pz_12_r_Char, SIZE32x32, 2,  0,  5, 0, 1, 2, 0 },
	{ pz_11_r_Char, SIZE32x32, 2,  0, -5, 0, 1, 2, 0 },
	{ pz_13_r_Char, SIZE32x32, 2,  5,  0, 0, 1, 2, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** プラズマーダメージ
const ANIME		ENEMY_PZ_DAM[] = {
	{ pz_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウニ
const ANIME		ENEMY_UI_F[] = {
	{ ui_01_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ ui_02_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ ui_03_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ ui_04_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウニ後ろ
const ANIME		ENEMY_UI_R[] = {
	{ ui_01_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ ui_02_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ ui_03_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ ui_04_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウニアタック
const ANIME		ENEMY_UI_ATK_F[] = {
	{ ui_11_f_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ ui_12_f_Char, SIZE32x32, 12, 0, 0, 0, 0, 0, 0 },
	{ ui_13_f_Char, SIZE32x32,  4, 0, 0, 0, 0, 0, 0 },
	{ ui_14_f_Char, SIZE32x32,  4, 0, 0, 0, 0, 0, 0 },
	{ ui_13_f_Char, SIZE32x32,  4, 0, 0, 0, 0, 0, 0 },
	{ ui_14_f_Char, SIZE32x32,  8, 0, 0, 0, 0, 0, 0 },
	{ ui_15_f_Char, SIZE32x32, 14, 0, 0, 0, 1, 5, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウニアタック後ろ
const ANIME		ENEMY_UI_ATK_R[] = {
	{ ui_11_r_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ ui_12_r_Char, SIZE32x32, 12, 0, 0, 0, 0, 0, 0 },
	{ ui_13_r_Char, SIZE32x32,  4, 0, 0, 0, 0, 0, 0 },
	{ ui_14_r_Char, SIZE32x32,  4, 0, 0, 0, 0, 0, 0 },
	{ ui_13_r_Char, SIZE32x32,  4, 0, 0, 0, 0, 0, 0 },
	{ ui_14_r_Char, SIZE32x32,  8, 0, 0, 0, 0, 0, 0 },
	{ ui_15_r_Char, SIZE32x32, 14, 0, 0, 0, 1, 5, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ウニダメージ
const ANIME		ENEMY_UI_DAM[] = {
	{ ui_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** トリ
const ANIME		ENEMY_TR_F[] = {
	{ tr_01_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ tr_02_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ tr_01_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ tr_03_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** トリ後ろ
const ANIME		ENEMY_TR_R[] = {
	{ tr_01_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ tr_02_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ tr_01_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ tr_03_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 上:2 下:3 右:4 左:5
// **** トリアタック
const ANIME		ENEMY_TR_ATK_F[] = {
	{ tr_11_f_Char, SIZE32x32, 10,  0, 0, 0, 4, 0, 0 },
	{ tr_12_f_Char, SIZE32x32, 18,  0, 0, 0, 4, 0, 0 },
	{ tr_13_f_Char, SIZE32x32,  8,  8, 0, 0, 4, 2, 0 },
	{ tr_14_f_Char, SIZE32x32,  6, 10, 0, 0, 4, 3, 0 },
	{ tr_15_f_Char, SIZE32x32,  6, 10, 0, 0, 4, 3, 0 },
	{ tr_14_f_Char, SIZE32x32,  6, 10, 0, 0, 4, 3, 0 },
	{ tr_15_f_Char, SIZE32x32,  6,  8, 0, 0, 4, 2, 0 },
	{ tr_16_f_Char, SIZE32x32,  8,  6, 0, 0, 4, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** トリアタック後ろ
const ANIME		ENEMY_TR_ATK_R[] = {
	{ tr_11_r_Char, SIZE32x32, 10,  0, 0, 0, 4, 0, 0 },
	{ tr_12_r_Char, SIZE32x32, 18,  0, 0, 0, 4, 0, 0 },
	{ tr_13_r_Char, SIZE32x32,  8,  8, 0, 0, 4, 2, 0 },
	{ tr_14_r_Char, SIZE32x32,  6, 10, 0, 0, 4, 3, 0 },
	{ tr_15_r_Char, SIZE32x32,  6, 10, 0, 0, 4, 3, 0 },
	{ tr_14_r_Char, SIZE32x32,  6, 10, 0, 0, 4, 3, 0 },
	{ tr_15_r_Char, SIZE32x32,  6,  8, 0, 0, 4, 2, 0 },
	{ tr_16_r_Char, SIZE32x32,  8,  6, 0, 0, 4, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** トリダメージ
const ANIME		ENEMY_TR_DAM[] = {
	{ tr_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};


// **** カエル
const ANIME		ENEMY_KE_F[] = {
	{ ke_01_f_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ ke_02_f_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ ke_03_f_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** キノコ
const ANIME		ENEMY_KN_F[] = {
	{ kn_01_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ kn_02_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ kn_01_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ kn_03_f_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キノコ後ろ
const ANIME		ENEMY_KN_R[] = {
	{ kn_01_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ kn_02_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ kn_01_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ kn_03_r_Char, SIZE32x32, 10, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キノコアタック
const ANIME		ENEMY_KN_ATK_F[] = {
	{ kn_11_f_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_12_f_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_13_f_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_14_f_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_15_f_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_16_f_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キノコアタック後ろ
const ANIME		ENEMY_KN_ATK_R[] = {
	{ kn_11_r_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_12_r_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_13_r_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_14_r_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_15_r_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ kn_16_r_Char, SIZE32x32,  8, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キノコダメージ
const ANIME		ENEMY_KN_DAM[] = {
	{ kn_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** ゴースト
const ANIME		ENEMY_GO_F[] = {
	{ go_01_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ go_02_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ go_03_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ go_04_f_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ゴースト後ろ
const ANIME		ENEMY_GO_R[] = {
	{ go_01_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ go_02_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ go_03_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ go_04_r_Char, SIZE32x32, 11, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ゴーストアタック
const ANIME		ENEMY_GO_ATK_F[] = {
	{ go_01_f_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ go_11_f_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ go_12_f_Char, SIZE32x32, 16, 0, 0, 0, 1, 1, 0 },
	{ go_13_f_Char, SIZE32x32, 16, 0, 0, 0, 1, 1, 0 },
	{ go_14_f_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ゴーストアタック後ろ
const ANIME		ENEMY_GO_ATK_R[] = {
	{ go_01_f_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ go_11_f_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ go_12_r_Char, SIZE32x32, 16, 0, 0, 0, 1, 1, 0 },
	{ go_13_r_Char, SIZE32x32, 16, 0, 0, 0, 1, 1, 0 },
	{ go_14_r_Char, SIZE32x32,  8, 0, 0, 0, 1, 1, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ゴーストダメージ
const ANIME		ENEMY_GO_DAM[] = {
	{ go_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ドム
const ANIME		ENEMY_DO_F[] = {
	{ do_01_f_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ do_02_f_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ do_01_f_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ do_03_f_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ドム後ろ
const ANIME		ENEMY_DO_R[] = {
	{ do_01_r_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ do_02_r_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ do_01_r_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ do_03_r_Char, SIZE32x32, 12, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ドムアタック
const ANIME		ENEMY_DO_ATK_F[] = {
	{ do_01_f_Char, SIZE32x32,  8, 0, 0, 0, 1,  0, 0 },
	{ do_11_f_Char, SIZE32x32, 13, 0, 0, 0, 0,  0, 0 },
	{ do_12_f_Char, SIZE32x32, 25, 0, 0, 0, 0,  0, 0 },
	{ do_13_f_Char, SIZE32x32,  8, 6, 6, 0, 1, 10, 0 },
	{ do_14_f_Char, SIZE32x32, 30, 6, 6, 0, 1, 10, 0 },
	{ do_13_f_Char, SIZE32x32,  8, 6, 6, 0, 1, 10, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ドムアタック後ろ
const ANIME		ENEMY_DO_ATK_R[] = {
	{ do_01_r_Char, SIZE32x32,  8, 0,  0, 0, 1,  0, 0 },
	{ do_11_r_Char, SIZE32x32, 13, 0,  0, 0, 0,  0, 0 },
	{ do_12_r_Char, SIZE32x32, 25, 0,  0, 0, 0,  0, 0 },
	{ do_13_r_Char, SIZE32x32,  8, 6, -6, 0, 1, 10, 0 },
	{ do_14_r_Char, SIZE32x32, 30, 6, -6, 0, 1, 10, 0 },
	{ do_13_r_Char, SIZE32x32,  8, 6, -6, 0, 1, 10, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ドムダメージ
const ANIME		ENEMY_DO_DAM[] = {
	{ do_21_Char, SIZE32x32, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** コウモリ
const ANIME		ENEMY_KO_F[] = {
	{ ko_01_f_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ ko_02_f_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ ko_01_f_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ ko_03_f_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** コウモリ後ろ
const ANIME		ENEMY_KO_R[] = {
	{ ko_01_r_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ ko_02_r_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ ko_01_r_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ ko_03_r_Char, SIZE16x16, 9, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** コウモリアタック
const ANIME		ENEMY_KO_ATK_F[] = {
	{ ko_11_f_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_12_f_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_13_f_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_14_f_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_15_f_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_16_f_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_17_f_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** コウモリアタック後ろ
const ANIME		ENEMY_KO_ATK_R[] = {
	{ ko_11_r_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_12_r_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_13_r_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_14_r_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_15_r_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_16_r_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ ko_17_r_Char, SIZE32x32, 10, 0, 0, 0, 1, 3, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** コウモリダメージ
const ANIME		ENEMY_KO_DAM[] = {
	{ ko_21_Char, SIZE16x16, 20, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** サソリ
const ANIME		ENEMY_SA_F[] = {
	{ sa_01_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sa_02_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sa_01_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sa_03_f_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** サソリ後ろ
const ANIME		ENEMY_SA_R[] = {
	{ sa_01_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sa_02_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sa_01_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ sa_03_r_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** サソリアタック
const ANIME		ENEMY_SA_ATK_F[] = {
	{ sa_01_f_Char, SIZE32x32,  8, 0, 0, 0, 0, 0, 0 },
	{ sa_11_f_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ sa_12_f_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ sa_13_f_Char, SIZE32x32, 16, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** サソリアタック後ろ
const ANIME		ENEMY_SA_ATK_R[] = {
	{ sa_01_r_Char, SIZE32x32,  8, 0, 0, 0, 0, 0, 0 },
	{ sa_11_r_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ sa_12_r_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ sa_13_r_Char, SIZE32x32, 16, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** サソリダメージ
const ANIME		ENEMY_SA_DAM[] = {
	{ sa_21_Char, SIZE32x32, 20,  0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// ************** 敵 *************** E

// ************** ボス *************** S

// **** ナイト通常状態
const ANIME		KNIGHT_STAND[] = {
	{ knight_01_Char, SIZE64x64,20, 0, 0, 0, 0, 0, 0 },
	{ knight_02_Char, SIZE64x64,20, 0, 0, 0, 0, 0, 0 },
	{ knight_03_Char, SIZE64x64,15, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ナイト攻撃状態
const ANIME		KNIGHT_ATK[] = {
	{ knight_10_Char, SIZE64x64,20, 0, 0, 0, 0, 0, 0 },
	{ knight_11_Char, SIZE64x64,12, 0, 0, 0, 0, 0, 0 },
	{ knight_12_Char, SIZE64x64,18, 0, 0, 0, 0, 0, 0 },
	{ knight_13_Char, SIZE64x64,18, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** ナイト攻撃状態（槍）
const ANIME		KNIGHT_ATK_EF[] = {
	{ knight_12_half_Char, SIZE64x64,18, 0, 0, 0, 0, 0, 0 },
	{ knight_13_half_Char, SIZE64x64,18, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// ************** ボス *************** E

// ******** アイテム
const ANIME		COIN_ANIME[] = {
	{ coin_small_01_Char, SIZE16x16, 8, 0, 0, 6, 0, 0, 0 },
	{ coin_small_02_Char, SIZE16x16, 8, 0, 0, 6, 0, 0, 0 },
	{ coin_small_03_Char, SIZE16x16, 8, 0, 0, 6, 0, 0, 0 },
	{ coin_small_04_Char, SIZE16x16, 8, 0, 0, 6, 0, 0, 0 },
	{ coin_small_04_Char, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** 敵エフェクト
// **** ゴースト魔法攻撃
// 移動
const ANIME		ENEMY_GO_SHOT_S[] = {
	{ go_shot_01_Char, SIZE16x16, 8, 0, 0, 0, 1, 10, 0 },
	{ go_shot_02_Char, SIZE16x16, 8, 0, 0, 0, 1, 10, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 爆発
const ANIME		ENEMY_GO_SHOT_B[] = {
	{ go_shot_02_Char, SIZE32x32, 8, 0, 0, 0, 1, 10, 0 },
	{ go_shot_11_Char, SIZE32x32, 8, 0, 0, 0, 1, 10, 0 },
	{ go_shot_12_Char, SIZE32x32, 8, 0, 0, 0, 1, 10, 0 },
	{ go_shot_13_Char, SIZE32x32, 8, 0, 0, 0, 1, 10, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** ラフリー種攻撃
const ANIME		ENEMY_RF_SHOT[] = {
	{ rf_shot_01_Char, SIZE8x8, 6, 0, 0, 0, 1, 3, 0 },
	{ rf_shot_02_Char, SIZE8x8, 6, 0, 0, 0, 1, 3, 0 },
	{ rf_shot_03_Char, SIZE8x8, 6, 0, 0, 0, 1, 3, 0 },
	{ rf_shot_04_Char, SIZE8x8, 6, 0, 0, 0, 1, 3, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ****************** エフェクト *********************

// **** ダメージエフェクト
const ANIME		EFFECT_DAMAGE[] = {
	{ dmg_ef_01_Char, SIZE32x32, 2, 0, 0, 1, 0, 0, 0 },
	{ dmg_ef_02_Char, SIZE32x32, 4, 0, 0, 1, 0, 0, 0 },
	{ dmg_ef_03_Char, SIZE32x32, 4, 0, 0, 1, 0, 0, 0 },
	{ dmg_ef_04_Char, SIZE32x32, 4, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** 煙エフェクト
const ANIME		EFFECT_SMOKE[] = {
	{ smk_ef_01_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ smk_ef_02_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ smk_ef_03_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ smk_ef_04_Char, SIZE32x32, 8, 0, 0, 1, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** マジ魔法攻撃
// 移動
const ANIME		MG_SHOT_S[] = {
	{ mg_shot_01_Char, SIZE16x16, 8, 0, 0, 0, 6, 140, 0 },
	{ mg_shot_02_Char, SIZE16x16, 8, 0, 0, 0, 6, 120, 0 },
	{ mg_shot_03_Char, SIZE16x16, 8, 0, 0, 0, 6, 100, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 爆発
const ANIME		MG_SHOT_B[] = {
	{ mg_shot_11_Char, SIZE32x32, 8,  -8,-10, 0, 0, 0, 0 },
	{ mg_shot_12_Char, SIZE32x32, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_shot_13_Char, SIZE32x32, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_shot_14_Char, SIZE32x32, 8,  -8,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 技攻撃
const ANIME		MG_SKILL_EF[] = {
	{ mg_skill_ef_01_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_skill_ef_02_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_skill_ef_03_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ mg_skill_ef_04_Char, SIZE32x32, 8, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// エフェクト
const ANIME		MG_SPECIAL_EF[] = {
	{ mg_special_ef_01_Char, SIZE64x64, 8,  -8,-10, 0, 0, 0, 0 },
	{ mg_special_ef_02_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_03_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_04_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_05_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_06_Char, SIZE64x64, 8,  -8,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** パワー技攻撃
const ANIME		PW_SPECIAL_EF[] = {
	{ pw_special_ef_01_Char, SIZE32x32, 8,  -8,-10, 0, 0, 0, 0 },
	{ pw_special_ef_02_Char, SIZE32x64, 8, -10,-10, 0, 0, 0, 0 },
	{ pw_special_ef_03_Char, SIZE32x64, 8, -10,-10, 0, 0, 0, 0 },
	{ pw_special_ef_04_Char, SIZE32x32, 8,  -8,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** スピード技攻撃
// 前
const ANIME		SP_SPECIAL_EF_F[] = {
	{ sp_special_ef_01_f_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ sp_special_ef_02_f_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ sp_special_ef_03_f_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 横
const ANIME		SP_SPECIAL_EF_S[] = {
	{ sp_special_ef_01_s_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ sp_special_ef_02_s_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ sp_special_ef_03_s_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// 後ろ
const ANIME		SP_SPECIAL_EF_R[] = {
	{ sp_special_ef_01_r_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ sp_special_ef_02_r_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ sp_special_ef_03_r_Char, SIZE64x64, 8, 0,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// **** ファイア技攻撃
const ANIME		PT_FIRE_F[] = {
	{ pt_fire_f_01_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ pt_fire_f_02_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ pt_fire_f_03_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		PT_FIRE_S[] = {
	{ pt_fire_s_01_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ pt_fire_s_02_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ pt_fire_s_03_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		PT_FIRE_R[] = {
	{ pt_fire_r_01_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ pt_fire_r_02_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ pt_fire_r_03_Char, SIZE32x32, 10, 0, 0, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};


// **** プチ専用スプラッシュ
const ANIME		SPLASH_EF_F[] = {
	{ splash_ef_f_01_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_f_02_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_f_03_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_f_04_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		SPLASH_EF_S[] = {
	{ splash_ef_s_01_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_s_02_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_s_03_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
const ANIME		SPLASH_EF_R[] = {
	{ splash_ef_r_01_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_r_02_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_r_03_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ splash_ef_r_04_Char, SIZE32x32, 8, 0,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// エフェクト
const ANIME		MG_SPECIAL_EF_L[] = {
	{ mg_special_ef_01_Char, SIZE64x64, 8,  -8,-10, 0, 0, 0, 0 },
	{ mg_special_ef_02_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_03_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_04_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_05_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_06_Char, SIZE64x64, 8,  -8,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// エフェクト
const ANIME		MG_SPECIAL_EF_R[] = {
	{ mg_special_ef_01_Char, SIZE64x64, 8,  -8,-10, 0, 0, 0, 0 },
	{ mg_special_ef_02_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_03_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_04_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_05_Char, SIZE64x64, 8, -10,-10, 0, 0, 0, 0 },
	{ mg_special_ef_06_Char, SIZE64x64, 8,  -8,-10, 0, 0, 0, 0 },
	{ NULL, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

// ******************** エフェクト *********************** E

const ANIME		RANK1[] = {
	{ rank1_Char, SIZE16x8, 0, 0, 0, 0, 0, 0, 0 },
};
const ANIME		RANK2[] = {
	{ rank2_Char, SIZE16x8, 0, 0, 0, 0, 0, 0, 0 },
};
const ANIME		RANK3[] = {
	{ rank3_Char, SIZE16x8, 0, 0, 0, 0, 0, 0, 0 },
};
const ANIME		RANK4[] = {
	{ rank4_Char, SIZE16x8, 0, 0, 0, 0, 0, 0, 0 },
};

// **** キャラクターセレクト用 ビースト
const ANIME		SELECT_BEAST[] = {
	{ select_beast_Char, SIZE64x64, 8, 0, 0, 0, 0, 0, 0 },
	{ select_beast_Char, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キャラクターセレクト用 マジック
const ANIME		SELECT_MAGIC[] = {
	{ select_magic_Char, SIZE64x64, 8, 0, 0, 0, 0, 0, 0 },
	{ select_magic_Char, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キャラクターセレクト用 プチ
const ANIME		SELECT_PETIT[] = {
	{ select_petit_Char, SIZE64x64, 8, 0, 0, 0, 0, 0, 0 },
	{ select_petit_Char, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キャラクターセレクト用 パワー
const ANIME		SELECT_POWER[] = {
	{ select_power_Char, SIZE64x64, 8, 0, 0, 0, 0, 0, 0 },
	{ select_power_Char, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};
// **** キャラクターセレクト用 スピード
const ANIME		SELECT_SPEED[] = {
	{ select_speed_Char, SIZE64x64, 8, 0, 0, 0, 0, 0, 0 },
	{ select_speed_Char, 0xED, 0xED, 0xED, 0xED, 0, 0, 0, 0 }	// 終端データ
};

/*
// BGアニメーション構造体
typedef struct {
	const u8*	pChar;
	u16			CharSize;
	const u16*	pMap;
	u16			MapSize;
	u8			Frame;
} BG_ANIME;
*/
const BG_ANIME	SPECIAL_FLASH_BG[] = {
	{ special_flash_01_Character, sizeof(special_flash_01_Character), special_flash_01_Map, sizeof(special_flash_01_Map), 10 },
	{ special_flash_02_Character, sizeof(special_flash_02_Character), special_flash_02_Map, sizeof(special_flash_02_Map), 10 },
	{ special_flash_03_Character, sizeof(special_flash_03_Character), special_flash_03_Map, sizeof(special_flash_03_Map), 10 },
	{ special_flash_04_Character, sizeof(special_flash_04_Character), special_flash_04_Map, sizeof(special_flash_04_Map), 10 },
	{ special_flash_05_Character, sizeof(special_flash_05_Character), special_flash_05_Map, sizeof(special_flash_05_Map), 10 },
	{ special_flash_06_Character, sizeof(special_flash_06_Character), special_flash_06_Map, sizeof(special_flash_06_Map), 10 },
};

