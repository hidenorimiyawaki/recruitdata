#include "All.h"


// 停止
#include	"../image/dragon_L/dragon_L_01.c"
#include	"../image/dragon_L/dragon_L_02.c"
#include	"../image/dragon_L/dragon_L_03.c"
#include	"../image/dragon_L/dragon_L_04.c"
#include	"../image/dragon_L/dragon_L_05.c"

// 歩き
#include	"../image/dragon_L/dragon_L_11.c"
#include	"../image/dragon_L/dragon_L_12.c"
#include	"../image/dragon_L/dragon_L_13.c"
#include	"../image/dragon_L/dragon_L_14.c"
#include	"../image/dragon_L/dragon_L_15.c"
#include	"../image/dragon_L/dragon_L_16.c"
#include	"../image/dragon_L/dragon_L_17.c"
#include	"../image/dragon_L/dragon_L_18.c"

// 爪
#include	"../image/dragon_L/dragon_L_41.c"
#include	"../image/dragon_L/dragon_L_42.c"
#include	"../image/dragon_L/dragon_L_43.c"
#include	"../image/dragon_L/dragon_L_44.c"
#include	"../image/dragon_L/dragon_L_45.c"
#include	"../image/dragon_L/dragon_L_46.c"
#include	"../image/dragon_L/dragon_L_47.c"
#include	"../image/dragon_L/dragon_L_48.c"

// 横ブレス
#include	"../image/dragon_L/dragon_L_21.c"
#include	"../image/dragon_L/dragon_L_22.c"
#include	"../image/dragon_L/dragon_L_23.c"
#include	"../image/dragon_L/dragon_L_24.c"
#include	"../image/dragon_L/dragon_L_25.c"
#include	"../image/dragon_L/dragon_L_26.c"
#include	"../image/dragon_L/dragon_L_27.c"
#include	"../image/dragon_L/dragon_L_28.c"
#include	"../image/dragon_L/dragon_L_29.c"
#include	"../image/dragon_L/dragon_L_30.c"
#include	"../image/dragon_L/dragon_L_31.c"
#include	"../image/dragon_L/dragon_L_32.c"
#include	"../image/dragon_L/dragon_L_33.c"
#include	"../image/dragon_L/dragon_L_34.c"
#include	"../image/dragon_L/dragon_L_35.c"

// 半円ブレス
#include	"../image/dragon_L/dragon_L_51.c"
#include	"../image/dragon_L/dragon_L_52.c"
#include	"../image/dragon_L/dragon_L_53.c"
#include	"../image/dragon_L/dragon_L_54.c"
#include	"../image/dragon_L/dragon_L_55.c"
#include	"../image/dragon_L/dragon_L_56.c"
#include	"../image/dragon_L/dragon_L_57.c"
#include	"../image/dragon_L/dragon_L_58.c"
#include	"../image/dragon_L/dragon_L_59.c"
#include	"../image/dragon_L/dragon_L_60.c"
#include	"../image/dragon_L/dragon_L_61.c"
#include	"../image/dragon_L/dragon_L_62.c"
#include	"../image/dragon_L/dragon_L_63.c"
#include	"../image/dragon_L/dragon_L_64.c"
#include	"../image/dragon_L/dragon_L_65.c"
#include	"../image/dragon_L/dragon_L_66.c"
#include	"../image/dragon_L/dragon_L_67.c"
#include	"../image/dragon_L/dragon_L_68.c"
#include	"../image/dragon_L/dragon_L_69.c"

// ダメージ
#include	"../image/dragon_L/dragon_L_70.c"
#include	"../image/dragon_L/dragon_L_71.c"
#include	"../image/dragon_L/dragon_L_72.c"





// BOSS構造体
typedef struct {
	s32		PosX;
	s32		PosY;
	s16		Hp;
	u8		Turn;
	u8		Type;
	u8		Anm;
	u8		Cnt;
} BOSS;

typedef struct {
	const u8*	pChar;
	u16			CharSize;
	const u16*	pMap;
	u16			MapSize;
	u8			Frame;
} BG_ANIME

const BG_ANIME	DRA_STAND[] = {
	{ dragon_L_01_Character, sizeof(dragon_L_01_Character), dragon_L_01_Map, sizeof(dragon_L_01_Map), 8 },
	{ dragon_L_02_Character, sizeof(dragon_L_02_Character), dragon_L_02_Map, sizeof(dragon_L_02_Map), 8 },
	{ dragon_L_03_Character, sizeof(dragon_L_03_Character), dragon_L_03_Map, sizeof(dragon_L_03_Map), 8 },
	{ dragon_L_04_Character, sizeof(dragon_L_04_Character), dragon_L_04_Map, sizeof(dragon_L_04_Map), 8 },
	{ dragon_L_05_Character, sizeof(dragon_L_05_Character), dragon_L_05_Map, sizeof(dragon_L_05_Map), 8 },
	{ dragon_L_04_Character, sizeof(dragon_L_04_Character), dragon_L_04_Map, sizeof(dragon_L_04_Map), 8 },
	{ dragon_L_03_Character, sizeof(dragon_L_03_Character), dragon_L_03_Map, sizeof(dragon_L_03_Map), 8 },
	{ dragon_L_02_Character, sizeof(dragon_L_02_Character), dragon_L_02_Map, sizeof(dragon_L_02_Map), 8 },
	{ NULL, 0, NULL, 0, 0 }
};

const BG_ANIME	DRA_WALK[] = {
	{ dragon_L_11_Character, sizeof(dragon_L_11_Character), dragon_L_11_Map, sizeof(dragon_L_11_Map), 8 },
	{ dragon_L_12_Character, sizeof(dragon_L_12_Character), dragon_L_12_Map, sizeof(dragon_L_12_Map), 8 },
	{ dragon_L_13_Character, sizeof(dragon_L_13_Character), dragon_L_13_Map, sizeof(dragon_L_13_Map), 8 },
	{ dragon_L_14_Character, sizeof(dragon_L_14_Character), dragon_L_14_Map, sizeof(dragon_L_14_Map), 8 },
	{ dragon_L_15_Character, sizeof(dragon_L_15_Character), dragon_L_15_Map, sizeof(dragon_L_15_Map), 8 },
	{ dragon_L_16_Character, sizeof(dragon_L_16_Character), dragon_L_16_Map, sizeof(dragon_L_16_Map), 8 },
	{ dragon_L_17_Character, sizeof(dragon_L_17_Character), dragon_L_17_Map, sizeof(dragon_L_17_Map), 8 },
	{ dragon_L_18_Character, sizeof(dragon_L_18_Character), dragon_L_18_Map, sizeof(dragon_L_18_Map), 8 },
	{ NULL, 0, NULL, 0, 0 }
};

const BG_ANIME	DRA_CLAW[] = {
	{ dragon_L_41_Character, sizeof(dragon_L_41_Character), dragon_L_41_Map, sizeof(dragon_L_41_Map), 8 },
	{ dragon_L_42_Character, sizeof(dragon_L_42_Character), dragon_L_42_Map, sizeof(dragon_L_42_Map), 8 },
	{ dragon_L_43_Character, sizeof(dragon_L_43_Character), dragon_L_43_Map, sizeof(dragon_L_43_Map), 8 },
	{ dragon_L_44_Character, sizeof(dragon_L_44_Character), dragon_L_44_Map, sizeof(dragon_L_44_Map), 8 },
	{ dragon_L_45_Character, sizeof(dragon_L_45_Character), dragon_L_45_Map, sizeof(dragon_L_45_Map), 8 },
	{ dragon_L_46_Character, sizeof(dragon_L_46_Character), dragon_L_46_Map, sizeof(dragon_L_46_Map), 8 },
	{ dragon_L_47_Character, sizeof(dragon_L_47_Character), dragon_L_47_Map, sizeof(dragon_L_47_Map), 8 },
	{ dragon_L_48_Character, sizeof(dragon_L_48_Character), dragon_L_48_Map, sizeof(dragon_L_48_Map), 8 },
	{ NULL, 0, NULL, 0, 0 }
};

const BG_ANIME	DRA_FIRE[] = {
	{ dragon_L_21_Character, sizeof(dragon_L_21_Character), dragon_L_21_Map, sizeof(dragon_L_21_Map), 8 },
	{ dragon_L_22_Character, sizeof(dragon_L_22_Character), dragon_L_22_Map, sizeof(dragon_L_22_Map), 8 },
	{ dragon_L_23_Character, sizeof(dragon_L_23_Character), dragon_L_23_Map, sizeof(dragon_L_23_Map), 8 },
	{ dragon_L_24_Character, sizeof(dragon_L_24_Character), dragon_L_24_Map, sizeof(dragon_L_24_Map), 8 },
	{ dragon_L_25_Character, sizeof(dragon_L_25_Character), dragon_L_25_Map, sizeof(dragon_L_25_Map), 8 },
	{ dragon_L_26_Character, sizeof(dragon_L_26_Character), dragon_L_26_Map, sizeof(dragon_L_26_Map), 8 },
	{ dragon_L_27_Character, sizeof(dragon_L_27_Character), dragon_L_27_Map, sizeof(dragon_L_27_Map), 8 },
	{ dragon_L_28_Character, sizeof(dragon_L_28_Character), dragon_L_28_Map, sizeof(dragon_L_28_Map), 8 },
	{ dragon_L_29_Character, sizeof(dragon_L_29_Character), dragon_L_29_Map, sizeof(dragon_L_29_Map), 8 },
	{ dragon_L_30_Character, sizeof(dragon_L_30_Character), dragon_L_30_Map, sizeof(dragon_L_30_Map), 8 },
	{ dragon_L_31_Character, sizeof(dragon_L_31_Character), dragon_L_31_Map, sizeof(dragon_L_31_Map), 8 },
	{ dragon_L_32_Character, sizeof(dragon_L_32_Character), dragon_L_32_Map, sizeof(dragon_L_32_Map), 8 },
	{ dragon_L_30_Character, sizeof(dragon_L_30_Character), dragon_L_30_Map, sizeof(dragon_L_30_Map), 8 },
	{ dragon_L_31_Character, sizeof(dragon_L_31_Character), dragon_L_31_Map, sizeof(dragon_L_31_Map), 8 },
	{ dragon_L_32_Character, sizeof(dragon_L_32_Character), dragon_L_32_Map, sizeof(dragon_L_32_Map), 8 },
	{ dragon_L_30_Character, sizeof(dragon_L_30_Character), dragon_L_30_Map, sizeof(dragon_L_30_Map), 8 },
	{ dragon_L_31_Character, sizeof(dragon_L_31_Character), dragon_L_31_Map, sizeof(dragon_L_31_Map), 8 },
	{ dragon_L_32_Character, sizeof(dragon_L_32_Character), dragon_L_32_Map, sizeof(dragon_L_32_Map), 8 },
	{ dragon_L_33_Character, sizeof(dragon_L_33_Character), dragon_L_33_Map, sizeof(dragon_L_33_Map), 8 },
	{ dragon_L_34_Character, sizeof(dragon_L_34_Character), dragon_L_34_Map, sizeof(dragon_L_34_Map), 8 },
	{ dragon_L_35_Character, sizeof(dragon_L_35_Character), dragon_L_35_Map, sizeof(dragon_L_35_Map), 8 },
	{ NULL, 0, NULL, 0, 0 }
};

const BG_ANIME	DRA_SPECIAL[] = {
	{ dragon_L_51_Character, sizeof(dragon_L_51_Character), dragon_L_51_Map, sizeof(dragon_L_51_Map), 8 },
	{ dragon_L_52_Character, sizeof(dragon_L_52_Character), dragon_L_52_Map, sizeof(dragon_L_52_Map), 8 },
	{ dragon_L_53_Character, sizeof(dragon_L_53_Character), dragon_L_53_Map, sizeof(dragon_L_53_Map), 8 },
	{ dragon_L_54_Character, sizeof(dragon_L_54_Character), dragon_L_54_Map, sizeof(dragon_L_54_Map), 8 },
	{ dragon_L_55_Character, sizeof(dragon_L_55_Character), dragon_L_55_Map, sizeof(dragon_L_55_Map), 8 },
	{ dragon_L_56_Character, sizeof(dragon_L_56_Character), dragon_L_56_Map, sizeof(dragon_L_56_Map), 8 },
	{ dragon_L_57_Character, sizeof(dragon_L_57_Character), dragon_L_57_Map, sizeof(dragon_L_57_Map), 8 },
	{ dragon_L_58_Character, sizeof(dragon_L_58_Character), dragon_L_58_Map, sizeof(dragon_L_58_Map), 8 },
	{ dragon_L_59_Character, sizeof(dragon_L_59_Character), dragon_L_59_Map, sizeof(dragon_L_59_Map), 8 },
	{ dragon_L_60_Character, sizeof(dragon_L_60_Character), dragon_L_60_Map, sizeof(dragon_L_60_Map), 8 },
	{ dragon_L_61_Character, sizeof(dragon_L_61_Character), dragon_L_61_Map, sizeof(dragon_L_61_Map), 8 },
	{ dragon_L_62_Character, sizeof(dragon_L_62_Character), dragon_L_62_Map, sizeof(dragon_L_62_Map), 8 },
	{ dragon_L_63_Character, sizeof(dragon_L_63_Character), dragon_L_63_Map, sizeof(dragon_L_63_Map), 8 },
	{ dragon_L_64_Character, sizeof(dragon_L_64_Character), dragon_L_64_Map, sizeof(dragon_L_64_Map), 8 },
	{ dragon_L_65_Character, sizeof(dragon_L_65_Character), dragon_L_65_Map, sizeof(dragon_L_65_Map), 8 },
	{ dragon_L_66_Character, sizeof(dragon_L_66_Character), dragon_L_66_Map, sizeof(dragon_L_66_Map), 8 },
	{ dragon_L_67_Character, sizeof(dragon_L_67_Character), dragon_L_67_Map, sizeof(dragon_L_67_Map), 8 },
	{ dragon_L_68_Character, sizeof(dragon_L_68_Character), dragon_L_68_Map, sizeof(dragon_L_68_Map), 8 },
	{ dragon_L_69_Character, sizeof(dragon_L_69_Character), dragon_L_69_Map, sizeof(dragon_L_69_Map), 8 },
	{ NULL, 0, NULL, 0, 0 }
};

const BG_ANIME	DRA_DAMAGE[] = {
	{ dragon_L_70_Character, sizeof(dragon_L_70_Character), dragon_L_70_Map, sizeof(dragon_L_70_Map), 20 },
	{ dragon_L_71_Character, sizeof(dragon_L_71_Character), dragon_L_71_Map, sizeof(dragon_L_71_Map), 20 },
	{ dragon_L_72_Character, sizeof(dragon_L_72_Character), dragon_L_72_Map, sizeof(dragon_L_72_Map), 20 },
	{ NULL, 0, NULL, 0, 0 }
};