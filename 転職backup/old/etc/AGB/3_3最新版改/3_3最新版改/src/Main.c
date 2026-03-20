/********************************************************************/
/*		  main.c													*/
/*			multi_sio（マルチプレイ通信サンプル）のメイン			*/
/*																	*/
/*		  Copyright (C) 1999-2001 NINTENDO Co.,Ltd.					*/
/********************************************************************/
//#define CODE32
#include "All.h"

/*------------------------------------------------------------------*/
/*					  割り込みテーブル							*/
/*------------------------------------------------------------------*/

const IntrFuncp IntrTable[13] = {
#ifdef MULTI_SIO_DI_FUNC_FAST
	(IntrFuncp )IntrFuncBuf,	// シリアル通信割り込み
#else							// or マルチプレイ通信用タイマー割り込み
	MultiSioIntr,
#endif
	VBlankIntr,				 // Ｖブランク割り込み

	IntrDummy,				  // Ｈブランク割り込み
	IntrDummy,				  // Ｖカウンタ一致割り込み
	IntrDummy,				  // ＤＭＡ０割り込み
	IntrDummy,				  // ＤＭＡ１割り込み
	IntrDummy,				  // ＤＭＡ２割り込み
	IntrDummy,				  // ＤＭＡ３割り込み
	IntrDummy,				  // キー割り込み
};

IntrFuncp IntrTableBuf[14];


/*==================================================================*/
/*					  メインルーチン							  */
/*==================================================================*/
extern void intr_main(void);

void AgbMain(void)
{
	enum { MAIN } Status;

	SioSetting();

	Title();

	// ----- BG Font セッティング -----
	*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_OBJ_ON; // LCDC ON
	*(vu16 *)REG_BG0CNT = 31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT; // BGセッティング
	CpuFastArrayCopy( system_Char,	  BG_VRAM+0xC000 );		// 3番 キャラクターデータベースブロック
	CpuFastArrayCopy( system_Palette, BG_PLTT+32*15  );		// パレットデータ

	ClearOamRam();		// OAMクリア

	MultiSioInit();		// マルチプレイ通信初期化

	while(1) {
		VBlankIntrWait();							// Vブランク割込終了待ち
		KeyManager();								// キー操作
		MultiSio();
		Briefing();
/*
		switch (  ) {
		case  :
			break;
		default :
			break;
		}
*/
	}
}