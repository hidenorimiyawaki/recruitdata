#include	"Briefing.h"

// BG
#include	"../image/briefing/char_select_frame.c"	// キャラセレクト背景
#include	"../image/briefing/stage_select_frame.c"// ステージセレクト背景
#include	"../image/briefing/winner_frame.c"		// 結果発表背景

#include	"../image/briefing/woods_icon.c"		// ステージイメージ
#include	"../image/briefing/ruins_icon.c"
#include	"../image/briefing/snow_icon.c"

// SPRITE
#include	"../image/briefing/select_speed.c"		// キャラセレイメージ
#include	"../image/briefing/select_magic.c"
#include	"../image/briefing/select_petit.c"
#include	"../image/briefing/select_beast.c"
#include	"../image/briefing/select_power.c"

#include	"../image/briefing/player1_logo.c"		// 順位イメージ
#include	"../image/briefing/player2_logo.c"
#include	"../image/briefing/player3_logo.c"
#include	"../image/briefing/player4_logo.c"

void Briefing(void)
{
	switch ( GameStatus ) {
		case C_SELECT :
			*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_BG1_ON| DISP_BG2_ON | DISP_OBJ_CHAR_1D_MAP;
		
			// ----- BG表示のための準備 ----- S
			CpuFastArrayCopy( char_select_frame_Palette,   BG_PLTT );				// パレットデータ
		
			*(vu16 *)REG_BG0CNT = BG_COLOR_16 | 24 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT;	// スクリーンデータ格納位置、優先順位
			CpuFastArrayCopy( char_select_frame_Character, BG_VRAM );				// キャラクタデータ
			CpuFastArrayCopy( char_select_frame_Map,       BG_VRAM+0xC000 );			// スクリーンデータ
			// ----- BG表示のための準備 ----- E
			break;
		case S_SELECT :
			*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_BG0_ON | DISP_BG1_ON| DISP_BG2_ON | DISP_OBJ_CHAR_1D_MAP;
		
			// ----- BG表示のための準備 ----- S		
			*(vu16 *)REG_BG0CNT = BG_COLOR_16 | 24 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT;	// スクリーンデータ格納位置、優先順位
			CpuFastArrayCopy( stage_select_frame_Character, BG_VRAM );				// キャラクタデータ
			CpuFastArrayCopy( stage_select_frame_Map,       BG_VRAM+0xC000 );			// スクリーンデータ
			// ----- BG表示のための準備 ----- E
			if ( Trg & L_KEY )	select++;
			if ( Trg & R_KEY )	select--;
			if ( select >= 5 )	select = 0;
			if ( select < 0 )	select = 4;
			OamBuf[0].Bit32  = OAM_OBJ_ON;
			OamBuf[0].Oam.CharNo =(VRAM_OTHER - OBJ_MODE0_VRAM) / 32;
			
			switch (select){
				case 0 : 
					OamBuf[0].Oam.Pltt = PLAYER_STATUS[SPEED].coloer;
					Action( 0, VRAM_OTHER, SP_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo] = PLAYER_STATUS[SPEED];
					break;
				case 1 :
					OamBuf[VRAM_OTHER].Oam.Pltt = PLAYER_STATUS[MAGIC].coloer;
					Action( 0, VRAM_OTHER, MG_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo] = PLAYER_STATUS[MAGIC];
					break;
				case 2 :
					OamBuf[VRAM_OTHER].Oam.Pltt = PLAYER_STATUS[PETIT].coloer;
					Action( 0, VRAM_OTHER, PT_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo] = PLAYER_STATUS[PETIT];
					break;
				case 3 :
					OamBuf[VRAM_OTHER].Oam.Pltt = PLAYER_STATUS[POWER].coloer;
					Action( 0, VRAM_OTHER, PW_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo] = PLAYER_STATUS[POWER];
					break;
				case 4 :
					OamBuf[VRAM_OTHER].Oam.Pltt = PLAYER_STATUS[BEAST].coloer;
					Action( 0, VRAM_OTHER, BS_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo] = PLAYER_STATUS[BEAST];
					break;
				default :
			}

			break;
	}
	return;
}