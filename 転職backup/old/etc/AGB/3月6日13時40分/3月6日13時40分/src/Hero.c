#include "All.h"

//**************************************************************************** S
//	  関数名		:	キャラクターの行動処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	どのタイプも基本的関数の呼び出ししかしない。
//	 最終更新日		:	2003/03/05 (水)
//**************************************************************************** E

void Hero (u8 No)
{

	// ******************** 選択キャラによる処理の分岐 ********************S

	switch ( PlayerNowstatus[No].name ){
		// *********************** スピードタイプ **************************S
		
		case SPEED :
			if( PlayerNowstatus[No].atk && (!PlayerNowstatus[No].type == ATK || !PlayerNowstatus[No].type == INTERVAL)){
				PlayerNowstatus[No].atk = 0;
				PlayerNowstatus[No].keep = 0;
			}
			switch ( PlayerNowstatus[No].type ){	
				// *********** SPインターバル状態 **********S
				case INTERVAL:			// 連続攻撃インターバル
					if ( SioTrg[No] & B_BUTTON ){
						PlayerNowstatus[No].type = ATK;
						PlayerNowstatus[No].keep = 0;
					}
					if( PlayerNowstatus[No].atk == ON) PlayerNowstatus[No].keep++;
					if( PlayerNowstatus[No].keep >= ATK_INTERVAL) {
						PlayerNowstatus[No].type = STAND;
						PlayerNowstatus[No].atk = OFF;
						PlayerNowstatus[No].keep = 0;
					}
				// *********** SPインターバル状態 **********E

				// ************** SP移動状態 ***************S
				case STAND :			// 初期状態
					if ( SioTrg[No] & A_BUTTON ){
						PlayerNowstatus[No].type = JUMP;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					if ( SioTrg[No] & B_BUTTON ){
						PlayerNowstatus[No].type = ATK;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					Move(No);
					break;
				// ************** SP移動状態 ***************E

				// ************ SPアタック状態 *************S
				case ATK :
					Attack(No);
					break;
				// ************ SPアタック状態 *************E

				// ************ SPジャンプ状態 *************S
				case JUMP :	
					Jump(No);
					break;
				// ************ SPスキル使用状態 *************E
				
				// ************ SP必殺技使用状態 *************S
				case SPECIAL :
					break;
				// ************ SP必殺技使用状態 *************E

				// ************  SPダメージ状態  *************S
				case DAMAGE :
					break;
				// ************ SPダメージ状態 *************E
				case DEAD:
					break;
			}
			break;
		// *********************** スピードタイプ **************************E


		// ***********************   プチタイプ   **************************S
		case PETIT :
			switch ( PlayerNowstatus[No].type ){	
				// *********** PTインターバル状態 **********S
				case INTERVAL:			// 連続攻撃インターバル
				// *********** PTインターバル状態 **********E

				// ************** PT移動状態 ***************S
				case STAND :			// 初期状態
					if ( SioTrg[No] & A_BUTTON ){
						PlayerNowstatus[No].type = JUMP;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					if ( SioTrg[No] & B_BUTTON ){
						PlayerNowstatus[No].type = ATK;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					Move(No);
					break;
				// ************** PT移動状態 ***************E

				// ************ PTアタック状態 *************S
				case ATK :
					Attack(No);
					break;
				// ************ PTアタック状態 *************E

				// ************ PTジャンプ状態 *************S
				case JUMP :	
					Jump(No);
					break;
				// ************ PTスキル使用状態 *************E
				
				// ************ PT必殺技使用状態 *************S
				case SPECIAL :
					break;
				// ************ PT必殺技使用状態 *************E

				// ************  PTダメージ状態  *************S
				case DAMAGE :
					break;
				// ************ PTダメージ状態 *************E
				case DEAD:
					break;
			}
			break;
		// ***********************   プチタイプ   **************************E


		// *********************** 魔法使いタイプ **************************S
		case MAGIC :
			switch ( PlayerNowstatus[No].type ){	
				// *********** MGインターバル状態 **********S
				case INTERVAL:			// 連続攻撃インターバル
				// *********** MGインターバル状態 **********E

				// ************** MG移動状態 ***************S
				case STAND :			// 初期状態
					if ( SioTrg[No] & A_BUTTON ){
						PlayerNowstatus[No].type = JUMP;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					if ( SioTrg[No] & B_BUTTON ){
						PlayerNowstatus[No].type = ATK;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					Move(No);
					break;
				// ************** MG移動状態 ***************E

				// ************ MGアタック状態 *************S
				case ATK :
					Attack(No);
					break;
				// ************ MGアタック状態 *************E

				// ************ MGジャンプ状態 *************S
				case JUMP :	
					Jump(No);
					break;
				// ************ MGスキル使用状態 *************E
				
				// ************ MG必殺技使用状態 *************S
				case SPECIAL :
					break;
				// ************ MG必殺技使用状態 *************E

				// ************  MGダメージ状態  *************S
				case DAMAGE :
					break;
				// ************ MGダメージ状態 *************E
				case DEAD:
					break;
			}
			break;
		// *********************** 魔法使いタイプ **************************E

		// ***********************  パワータイプ  **************************E
		case POWER :
			switch ( PlayerNowstatus[No].type ){	
				// *********** PWインターバル状態 **********S
				case INTERVAL:			// 連続攻撃インターバル
				// *********** PWインターバル状態 **********E

				// ************** PW移動状態 ***************S
				case STAND :			// 初期状態
					if ( SioTrg[No] & A_BUTTON ){
						PlayerNowstatus[No].type = JUMP;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					if ( SioTrg[No] & B_BUTTON ){
						PlayerNowstatus[No].type = ATK;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					Move(No);
					break;
				// ************** PW移動状態 ***************E

				// ************ PWアタック状態 *************S
				case ATK :
					Attack(No);
					break;
				// ************ PWアタック状態 *************E

				// ************ PWジャンプ状態 *************S
				case JUMP :	
					Jump(No);
					break;
				// ************ PWスキル使用状態 *************E
				
				// ************ PW必殺技使用状態 *************S
				case SPECIAL :
					break;
				// ************ PW必殺技使用状態 *************E

				// ************  PWダメージ状態  *************S
				case DAMAGE :
					break;
				// ************ PWダメージ状態 *************E
				case DEAD:
					break;
			}
			break;
		// ***********************  パワータイプ  **************************E

		// *********************** ビーストタイプ **************************S
		case BEAST :
			if( PlayerNowstatus[No].atk && (!PlayerNowstatus[No].type == ATK || !PlayerNowstatus[No].type == INTERVAL)){
				PlayerNowstatus[No].atk = 0;
				PlayerNowstatus[No].keep = 0;
			}
			switch ( PlayerNowstatus[No].type ){	
				// *********** BSインターバル状態 **********S
				case INTERVAL:			// 連続攻撃インターバル
					if ( SioTrg[No] & B_BUTTON ){
						PlayerNowstatus[No].type = ATK;
						PlayerNowstatus[No].keep = 0;
					}
					if( PlayerNowstatus[No].atk == ON) PlayerNowstatus[No].keep++;
					if( PlayerNowstatus[No].keep >= ATK_INTERVAL) {
						PlayerNowstatus[No].type = STAND;
						PlayerNowstatus[No].atk = OFF;
						PlayerNowstatus[No].keep = 0;
					}
				// *********** BSインターバル状態 **********E

				// ************** BS移動状態 ***************S
				case STAND :			// 初期状態
					if ( SioTrg[No] & A_BUTTON ){
						PlayerNowstatus[No].type = JUMP;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					if ( SioTrg[No] & B_BUTTON ){
						PlayerNowstatus[No].type = ATK;
						ObjBuf[OBJ_PLAYER_NO + No].Anime = ObjBuf[OBJ_PLAYER_NO + No].Cnt = 0;
					}
					Move(No);
					break;
				// ************** BS移動状態 ***************E

				// ************ BSアタック状態 *************S
				case ATK :
					Attack(No);
					break;
				// ************ BSアタック状態 *************E

				// ************ BSジャンプ状態 *************S
				case JUMP :	
					Jump(No);
					break;
				// ************ BSスキル使用状態 *************E
				
				// ************ BS必殺技使用状態 *************S
				case SPECIAL :
					break;
				// ************ BS必殺技使用状態 *************E

				// ************  BSダメージ状態  *************S
				case DAMAGE :
					break;
				// ************ BSダメージ状態 *************E
				case DEAD:
					break;
			}
			break;
		// *********************** ビーストタイプ **************************E
		
		default :
			break;
	}
	// ******************** 選択キャラによる処理の分岐 ********************E

	return;
}

