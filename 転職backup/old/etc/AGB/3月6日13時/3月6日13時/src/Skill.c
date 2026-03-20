#include "all.h"

//**************************************************************************** S
//	  関数名		:	特殊動作
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	
//	 最終更新日		:	2003/02/14 (金)
//**************************************************************************** E
s32 work_h,work_v;

void Skill( void )
{

	u8 sp_dash = 5;
	// ******************** 選択キャラによる処理の分岐 ********************S
	switch ( PlayerNowstatus[PlayerNo].name ){
		// *********************** スピードタイプ **************************S
		
		case SPEED :
			// 攻撃中にPlayerNowstatus[PlayerNo].typeが変更されたときにフラグ等を初期化する
			if( PlayerNowstatus[PlayerNo].atk && (!PlayerNowstatus[PlayerNo].type == ATK || !PlayerNowstatus[PlayerNo].type == INTERVAL)){
				PlayerNowstatus[PlayerNo].atk = 0;
				PlayerNowstatus[PlayerNo].keep = 0;
			}
			if( !PlayerNowstatus[PlayerNo].skillflg ){
				switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){				// 十字キー入力
					case R_U_KEY :	// 右上移動
						work_h = 1;
						work_v = -1;
						break;
					case R_D_KEY :	// 右下移動
						work_h = 1;
						work_v = 1;
						break;
					case L_U_KEY :	// 左上移動
						work_h = -1;
						work_v = -1;
						break;
					case L_D_KEY :	// 左下移動
						work_h = -1;
						work_v = 1;
						break;
					case R_KEY :	// 右移動
						work_h = 2;
						work_v = 0;
						break;
					case L_KEY :	// 左移動
						work_h = -2;
						work_v = 0;
						break;
					case U_KEY :	// 上移動
						work_h = 0;
						work_v = -2;
						break;
					case D_KEY :	// 下移動
						work_h = 0;
						work_v = 2;
						break;
					default :		// 入力無し
						switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
							case TURN_R :	// 右
								work_h = 2;
								work_v = 0;
								break;
							case TURN_L :	// 左
								work_h = -2;
								work_v = 0;
								break;
							case TURN_U :		// 上
								work_h = 0;
								work_v = -2;
								break;
							case TURN_D :	// 下
								work_h = 0;
								work_v = 2;
								break;
							}
					}
				PlayerNowstatus[PlayerNo].skillflg = 1;

			}
			switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
				case TURN_R :	// 右
					if( Action( 0, OBJ_MODE0_VRAM, SP_SPECIAL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
						PlayerNowstatus[PlayerNo].type = STAND;
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						OamBuf[0].Oam.HFlip = 1;
						PlayerNowstatus[PlayerNo].skillflg = 0;
					}
					Hoffset += ((work_h * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					Voffset += ((work_v * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					break;
				case TURN_L :	// 左
					if( Action( 0, OBJ_MODE0_VRAM, SP_SPECIAL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
						PlayerNowstatus[PlayerNo].type = STAND;
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						OamBuf[0].Oam.HFlip = 0;
						PlayerNowstatus[PlayerNo].skillflg = 0;
					}
					Hoffset += ((work_h * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					Voffset += ((work_v * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					break;
				case TURN_U :		// 上
					if( Action( 0, OBJ_MODE0_VRAM, SP_SPECIAL_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
						PlayerNowstatus[PlayerNo].type = STAND;
						PlayerNowstatus[PlayerNo].turn = TURN_D;
						OamBuf[0].Oam.HFlip = 0;
						PlayerNowstatus[PlayerNo].skillflg = 0;
					}
					Hoffset += ((work_h * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					Voffset += ((work_v * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					break;
				case TURN_D :	// 下
					if( Action( 0, OBJ_MODE0_VRAM, SP_SPECIAL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
						PlayerNowstatus[PlayerNo].type = STAND;
						PlayerNowstatus[PlayerNo].turn = TURN_U;
						OamBuf[0].Oam.HFlip = 0;
						PlayerNowstatus[PlayerNo].skillflg = 0;
					}
					Hoffset += ((work_h * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					Voffset += ((work_v * (sp_dash - PlayerNowstatus[PlayerNo].anime)) << 16);
					break;
				}

			break;
		// *********************** スピードタイプ **************************E


		// ***********************   プチタイプ   **************************S
		case PETIT :
			if( Action( 0, OBJ_MODE0_VRAM, PT_SPECIAL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
				if ( SioOldKey[PlayerNo] & L_BUTTON ){
					PlayerNowstatus[PlayerNo].anime = 1;
					PlayerNowstatus[PlayerNo].type = SKILL;
					PlayerNowstatus[PlayerNo].hp += 10;
				}
				else{
					PlayerNowstatus[PlayerNo].type = STAND;
				}
			}
			break;
		// ***********************   プチタイプ   **************************E


		// *********************** 魔法使いタイプ **************************S
		case MAGIC :
			if( Action( 0, OBJ_MODE0_VRAM, MG_SPECIAL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
				if ( SioOldKey[PlayerNo] & L_BUTTON ){
					PlayerNowstatus[PlayerNo].anime = 2;
					PlayerNowstatus[PlayerNo].type = SKILL;
				}
				else{
					PlayerNowstatus[PlayerNo].type = STAND;
					OamBuf[30].Bit32 = OAM_OBJ_OFF;
				}
			}
			NowAnime = (ANIME*)MG_SPECIAL_F;

			// **************** シールド出現処理 *************** S
			OamBuf[30].Bit32 = OAM_OBJ_ON;
			OamBuf[30].Oam.Pltt = 10;
			OamBuf[30].Oam.CharNo = 32*30;
			if( Action( 30, OBJ_MODE0_VRAM+1024*30, MG_SKILL_EF  , HERO_CENTER_X, HERO_CENTER_Y, &PlayerEffect[0].cnt, &PlayerEffect[0].anime) ){
			}
			// **************** シールド出現処理 *************** E
		break;
		// *********************** 魔法使いタイプ **************************E

		// ***********************  パワータイプ  **************************E
		case POWER :
			switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
				case TURN_R :	// 右
					OamBuf[0].Oam.HFlip = 0;
					if( Action( 0, OBJ_MODE0_VRAM, PW_SPECIAL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
					break;
				case TURN_L :	// 左
					OamBuf[0].Oam.HFlip = 1;
					if( Action( 0, OBJ_MODE0_VRAM, PW_SPECIAL_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
					break;
				case TURN_U :		// 上
					OamBuf[0].Oam.HFlip = 0;
					if( Action( 0, OBJ_MODE0_VRAM, PW_SPECIAL_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
					break;
				case TURN_D :	// 下
					OamBuf[0].Oam.HFlip = 0;
					if( Action( 0, OBJ_MODE0_VRAM, PW_SPECIAL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
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
			if( Action( 0, OBJ_MODE0_VRAM, BS_SPECIAL_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ) PlayerNowstatus[PlayerNo].type = STAND;
			break;
		// *********************** ビーストタイプ **************************E
		
		default :
			break;
	}
	// ******************** 選択キャラによる処理の分岐 ********************E

	return;
}