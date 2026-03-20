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
	VBlankIntr,				// Ｖブランク割り込み

	IntrDummy,				// Ｈブランク割り込み
	IntrDummy,				// Ｖカウンタ一致割り込み
	IntrDummy,				// ＤＭＡ０割り込み
	IntrDummy,				// ＤＭＡ１割り込み
	IntrDummy,				// ＤＭＡ２割り込み
	IntrDummy,				// ＤＭＡ３割り込み
	IntrDummy,				// キー割り込み
};

IntrFuncp IntrTableBuf[14];


/*==================================================================*/
/*					  メインルーチン							  */
/*==================================================================*/
extern void intr_main(void);

void AgbMain(void)
{

	int i;
	GameStatus = START;

	while(1) {

		switch ( GameStatus ) {
		case START :
			ClearRamAll();		// RAMクリア
			SioSetting();		// マルチプレイ通信初期化１
			Title();			// タイトル画面
			MultiSioInit();		// マルチプレイ通信初期化２
			GameStatus = C_SELECT;
			break;

		case C_SELECT :
			ObjInit();
			ClearMapData(0);
			CpuFastArrayCopy( rank_Palette,   OBJ_PLTT		 + 32*12 );			// RANKING
			CpuFastArrayCopy( system_Palette, OBJ_PLTT		 + 32*15 );			// パレットを末尾に
			CpuFastArrayCopy( system_Char,    OBJ_MODE0_VRAM + 0x7000 );		// 文字フォントデータを末尾に
			
			// ----- BG Font セッティング -----
			*(vu16 *)REG_BG0CNT = 31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT; // BGセッティング
			CpuFastArrayCopy( system_Char,	  BG_VRAM + 0x4000*3 );		// 3番 キャラクターデータベースブロック
			CpuFastArrayCopy( system_Palette, BG_PLTT + 32*15    );		// パレットデータ
			*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_OBJ_CHAR_1D_MAP;
			for ( i = 0; i < 4; i++ ) {
				ObjBuf[i].PosX = (16+i*8) << 16;
				ObjBuf[i].PosY = (32+i*8) << 16;
			}
			ObjAction( 0, RANK1 );
			ObjAction( 1, RANK2 );
			ObjAction( 2, RANK3 );
			ObjAction( 3, RANK4 );
			ObjStringPrint( "TEST", 100, 100, 15);
			//BgStringPrint(  "TEST",  10,  10, 15, 0 );
			BgDataOut( GameTimer,     2, 0, 15, DEX, 0 );
			//BgDataOut( *(u32*)&ObjBuf[0].Oam, 4, 0, 15, HEX, 0 );
			//BgDataOut( *(u32*)OAM,    6, 0, 15, HEX, 0 );
			//GameStatus = S_SELECT;
			break;

		case S_SELECT :
			GameStatus = MAIN;
			break;

		case MAIN :
			GameStatus = END;
			break;

		case END :
			//Ending();
			GameStatus = START;
			break;

		default :
			GameStatus = START;
			break;
		}
		
		//OamManager();
		for ( i = 0; i < 128; i++ )
			*((OamData *)OAM+i) = ObjBuf[i].Oam;
		StringNo = 127;
		VBlankIntrWait();			// Vブランク割込終了待ち
		KeyManager();				// キー操作

#ifndef	DEBUGING
		MultiSio();				// 通信
#else
		SioKey[0] = Key;
		SioTrg[0] = Trg;
		SioOldKey[0] = OldKey;
#endif
		GameTimer++;
	}
}