#include "all.h"

//**************************************************************************** S
//	  関数名		:	必殺技
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	
//	 最終更新日		:	2003/02/14 (金)
//**************************************************************************** E
s32 work_h,work_v;
s32	Skill_local_x;
s32	Skill_local_y;

#define	MAGIC_ZOOM		0x00018000		// 1.5

void Special( void )
{

		if( SpBgCnt <= 12 ){
				*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_BG2_ON | DISP_OBJ_CHAR_1D_MAP;
				*(vu16*)REG_BG2HOFS = 0;
				*(vu16*)REG_BG2VOFS = 0;

				SpBgCnt++;
				DmaArrayCopy( 3, SPECIAL_FLASH_CHARACTER[(SpBgCnt / 2)],  BG_VRAM + 0x8000, 16);	// 2番
//				DmaArrayCopy( 3, special_flash_01_Palette,    BG_PLTT + 32*2,   16);	// 

				*(vu16 *)REG_BG2CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0 | \
									  17 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;

				*(vu16 *)REG_BG1CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_2 | \
									  31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;

				*(vu16 *)REG_BG0CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1 | 
									  8  << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;


				ClearMapData( 2 );
				MakeMap( SPECIAL_FLASH_MAP[(SpBgCnt / 2)],  30, 20, 2 );
		}
		else{
				*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_OBJ_CHAR_1D_MAP;

				*(vu16 *)REG_BG2CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_2 | \
									  17 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;

				*(vu16 *)REG_BG1CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0 | \
									  31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;

				*(vu16 *)REG_BG0CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1 | 
									  8  << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;
				ClearMapData( 2 );

		}


	// ******************** 選択キャラによる処理の分岐 ********************S
		switch ( PlayerNowstatus[PlayerNo].name ){	
		// *********************** スピードタイプ **************************S
			case SPEED :
				// 攻撃中にHeroStatusが変更されたときにフラグ等を初期化する
				if( PlayerNowstatus[PlayerNo].atk && (!PlayerNowstatus[PlayerNo].type == ATK || !PlayerNowstatus[PlayerNo].type == INTERVAL)){
					PlayerNowstatus[PlayerNo].atk = 0;
					PlayerNowstatus[PlayerNo].keep = 0;
				}
				OamBuf[30].Bit32 = OAM_OBJ_ON;
				OamBuf[30].Oam.Pltt = 11;
				OamBuf[30].Oam.CharNo = 32*30;
				switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
					case TURN_R :	// 右
						OamBuf[0].Oam.HFlip = 0;
						OamBuf[30].Oam.HFlip = 0;
						if( Action(  30, OBJ_MODE0_VRAM+1024*30, SP_SPECIAL_EF_S  , HERO_CENTER_X - 16, HERO_CENTER_Y - 8, &PlayerEffect[0].cnt, &PlayerEffect[0].anime) ) OamBuf[30].Bit32 = OAM_OBJ_OFF;
						if( Action( 0, OBJ_MODE0_VRAM, SP_SKILL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							OamBuf[30].Bit32 = OAM_OBJ_OFF;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						Hoffset += (4 << 16);
						NowAnime = (ANIME*)SP_SKILL_S;		// 攻撃力を格納する
						break;
					case TURN_L :	// 左
						OamBuf[0].Oam.HFlip = 1;
						OamBuf[30].Oam.HFlip = 1;
						if( Action(  30, OBJ_MODE0_VRAM+1024*30, SP_SPECIAL_EF_S  , HERO_CENTER_X - 16, HERO_CENTER_Y - 8, &PlayerEffect[0].cnt, &PlayerEffect[0].anime) ) OamBuf[30].Bit32 = OAM_OBJ_OFF;
						if( Action( 0, OBJ_MODE0_VRAM, SP_SKILL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							OamBuf[30].Bit32 = OAM_OBJ_OFF;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						Hoffset -= (4 << 16);
						NowAnime = (ANIME*)SP_SKILL_S;
						break;
					case TURN_U :		// 上
						OamBuf[0].Oam.HFlip = 0;
						OamBuf[30].Oam.HFlip = 0;
						if( Action(  30, OBJ_MODE0_VRAM+1024*30, SP_SPECIAL_EF_R  , HERO_CENTER_X - 8, HERO_CENTER_Y - 16, &PlayerEffect[0].cnt, &PlayerEffect[0].anime) ) OamBuf[30].Bit32 = OAM_OBJ_OFF;
						if( Action( 0, OBJ_MODE0_VRAM, SP_SKILL_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							OamBuf[30].Bit32 = OAM_OBJ_OFF;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						Voffset -= (4 << 16);
						NowAnime = (ANIME*)SP_SKILL_R;
						break;
					case TURN_D :	// 下
						OamBuf[0].Oam.HFlip = 0;
						OamBuf[30].Oam.HFlip = 0;
	
						if( Action(  30, OBJ_MODE0_VRAM+1024*30, SP_SPECIAL_EF_F  , HERO_CENTER_X - 24, HERO_CENTER_Y - 16, &PlayerEffect[0].cnt, &PlayerEffect[0].anime) ) OamBuf[30].Bit32 = OAM_OBJ_OFF;
						if( Action( 0, OBJ_MODE0_VRAM, SP_SKILL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							OamBuf[30].Bit32 = OAM_OBJ_OFF;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						Voffset += (4 << 16);
						NowAnime = (ANIME*)SP_SKILL_F;
						break;
					}
	
	
				break;
			// *********************** スピードタイプ **************************E
	
	
			// ***********************   プチタイプ   **************************S
			case PETIT :
				if( Action( 0, OBJ_MODE0_VRAM, PT_SKILL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
	
				break;
			// ***********************   プチタイプ   **************************E
	
	
			// *********************** 魔法使いタイプ **************************S
			case MAGIC :
				if( Action( 0, OBJ_MODE0_VRAM, MG_SKILL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
				OamBuf[30].Oam.Pltt = 10;
				OamBuf[30].Oam.CharNo = 32*30;
				OamBuf[30].Oam.AffineMode = 3;
//				OamBuf[30].Bit32 = OAM_OBJ_ON;

				OamBuf[31].Oam.Pltt = 10;
				OamBuf[31].Oam.CharNo = 32*31;
				OamBuf[31].Oam.AffineMode = 3;
	//			OamBuf[31].Bit32 = OAM_OBJ_ON;


				if( Action( 30, OBJ_MODE0_VRAM+1024*30, MG_SPECIAL_EF_L  , HERO_CENTER_X, HERO_CENTER_Y, &PlayerEffect[0].cnt, &PlayerEffect[0].anime) )
					OamBuf[30].Bit32 = OAM_OBJ_OFF;
				if( Action( 31, OBJ_MODE0_VRAM+1024*31, MG_SPECIAL_EF_R  , HERO_CENTER_X, HERO_CENTER_Y, &PlayerEffect[1].cnt, &PlayerEffect[1].anime) )
					OamBuf[31].Bit32 = OAM_OBJ_OFF;

				break;
			// *********************** 魔法使いタイプ **************************E
	
			// ***********************  パワータイプ  **************************E
			case POWER :
				
				switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
					case TURN_R :	// 右
						OamBuf[0].Oam.HFlip = 0;
						OamBuf[30].Oam.HFlip = 0;
						if( Action( 0, OBJ_MODE0_VRAM, PW_SKILL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						NowAnime = (ANIME*)PW_SKILL_S;		// 攻撃力を格納する
						break;
					case TURN_L :	// 左
						OamBuf[0].Oam.HFlip = 1;
						OamBuf[30].Oam.HFlip = 1;
						if( Action( 0, OBJ_MODE0_VRAM, PW_SKILL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						NowAnime = (ANIME*)PW_SKILL_S;
						break;
					case TURN_U :		// 上
						OamBuf[0].Oam.HFlip = 0;
						OamBuf[30].Oam.HFlip = 0;
						if( Action( 0, OBJ_MODE0_VRAM, PW_SKILL_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						NowAnime = (ANIME*)PW_SKILL_R;
						break;
					case TURN_D :	// 下
						OamBuf[0].Oam.HFlip = 0;
						OamBuf[30].Oam.HFlip = 0;
	
						if( Action( 0, OBJ_MODE0_VRAM, PW_SKILL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
							PlayerNowstatus[PlayerNo].type = STAND;
							SpBgCnt = 0;
							PlayerNowstatus[PlayerNo].sp = 0;
						}
						NowAnime = (ANIME*)PW_SKILL_F;
						break;
					}
			
	
				break;
			// ***********************  パワータイプ  **************************E
	
			// *********************** ビーストタイプ **************************S
			case BEAST :
				if( PlayerNowstatus[PlayerNo].atk && (!PlayerNowstatus[PlayerNo].type == ATK || !PlayerNowstatus[PlayerNo].type == INTERVAL)){
					PlayerNowstatus[PlayerNo].atk = 0;
					PlayerNowstatus[PlayerNo].keep = 0;
				}
	
				if( Action( 0, OBJ_MODE0_VRAM, BS_SKILL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
	
				break;
			// *********************** ビーストタイプ **************************E
			
			default :
				break;
		}
		// ******************** 選択キャラによる処理の分岐 ********************E
	return;
}