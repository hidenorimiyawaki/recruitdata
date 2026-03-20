#include	"Title.h"

#include	"../image/Title/title_cloud.c"
#include	"../image/Title/title_16_bg.c"
#include	"../image/Title/title_main_bg_01.c"
#include	"../image/Title/title_main_bg_02.c"
#include	"../image/Title/title_main_bg_03.c"

void Title( void )
{
	u8 ofs = 0, bg = 0, timer = 0;
	
	*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_BG1_ON| DISP_BG2_ON | DISP_OBJ_CHAR_1D_MAP;

	// ----- BG表示のための準備 ----- S
	*(vu16 *)REG_BG0CNT = BG_COLOR_256 | 24 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT; // スクリーンデータ格納位置、優先順位
	CpuFastArrayCopy( title_main_bg_01_Character, BG_VRAM );				// キャラクタデータ
	CpuFastArrayCopy( title_main_bg_01_Palette,   BG_PLTT );				// パレットデータ
	CpuFastArrayCopy( title_main_bg_01_Map,       BG_VRAM+0xC000 );			// スクリーンデータ
	*(vu16 *)REG_BG1CNT = 26 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT;;		// スクリーンデータ格納位置、優先順位
	CpuFastArrayCopy( title_cloud_Character, BG_VRAM+0x4000 );			// キャラクタデータ
	CpuFastArrayCopy( title_cloud_Palette,   BG_PLTT+(0x20*15) );			// パレットデータ
	CpuFastArrayCopy( title_cloud_Map,       BG_VRAM+0xD000 );			// スクリーンデータ1
	*(vu16 *)REG_BG2CNT = 28 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT;;		// スクリーンデータ格納位置、優先順位
	CpuFastArrayCopy( title_16_bg_Character, BG_VRAM+0x8000 );			// キャラクタデータ
	CpuFastArrayCopy( title_16_bg_Palette,   BG_PLTT+(0x20*14) );			// パレットデータ
	CpuFastArrayCopy( title_16_bg_Map,       BG_VRAM+0xE000 );		// スクリーンデータ1
	// ----- BG表示のための準備 ----- E

	while ( 1 ){
		if ( (++timer & 0xf) == 0xf )
			*(vu16 *)REG_BG1HOFS = ofs--;	// 雲スクロール
		if ( (timer & 0x7) == 0x7 ) {
			switch ( ++bg % 3 ) {
				case 0:
					CpuFastArrayCopy( title_main_bg_01_Character, BG_VRAM );
					CpuFastArrayCopy( title_main_bg_01_Map,       BG_VRAM+0xC000 );
					break;
				case 1:
					CpuFastArrayCopy( title_main_bg_02_Character, BG_VRAM );
					CpuFastArrayCopy( title_main_bg_02_Map,       BG_VRAM+0xC000 );
					break;
				case 2:
					CpuFastArrayCopy( title_main_bg_03_Character, BG_VRAM );
					CpuFastArrayCopy( title_main_bg_03_Map,       BG_VRAM+0xC000 );
			}
		}
		if ( (*(vu16 *)REG_KEYINPUT ^ ALL_KEY_MASK) & BUTTON_MASK ){
			*(vu16 *)REG_DISPCNT =DISP_MODE_0 | DISP_OBJ_ON | DISP_OBJ_CHAR_1D_MAP;
			ClearGraphicRam();
			break;
		}
		
		//m4aSoundMain();
		VBlankIntrWait();//V_Wait();;		// V-Blank割り込みが発生し、登録関数を処理するまで待つ
		//m4aSoundVSync();
	}
	return;
}