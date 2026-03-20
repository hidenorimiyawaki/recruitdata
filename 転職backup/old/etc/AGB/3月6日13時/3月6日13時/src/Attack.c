#include "All.h"

//**************************************************************************** S
//	  関数名		:	キャラクターの攻撃行動処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	
//	 最終更新日		:	2003/03/06 (水)
//**************************************************************************** E

void Attack (u8 No)
{
	// ******************** 選択キャラによる処理の分岐 ********************S

	switch ( PlayerNowstatus[No].name ){
		// *********************** スピードタイプ **************************S
		
		case SPEED :
			switch ( PlayerNowstatus[No].turn ){		// 方向
				case TURN_R :	// 右
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK_S ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)SP_ATK_S;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK2_S ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)SP_ATK2_S;
					}						
					break;
				case TURN_L :	// 左
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK_S ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)SP_ATK_S;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK2_S ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)SP_ATK2_S;
					}						
					break;
				case TURN_U :		// 上
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK_R ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)SP_ATK_R;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK2_R ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)SP_ATK2_R;
					}						
					break;
				case TURN_D :	// 下
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK_F ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)SP_ATK_F;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,SP_ATK2_F ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)SP_ATK2_F;
					}						
					break;
			}
			break;
		break;
		// *********************** スピードタイプ **************************E


		// ***********************   プチタイプ   **************************S
		case PETIT :
			switch ( PlayerNowstatus[No].turn ){		// 方向
				case TURN_R :	// 右
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_PLAYER_NO + No,PT_ATK_S ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PT_ATK_S;		// 攻撃力を格納する
					break;
				case TURN_L :	// 左
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					if( ObjAction( OBJ_PLAYER_NO + No,PT_ATK_S ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PT_ATK_S;		// 攻撃力を格納する
					break;
				case TURN_U :		// 上
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_PLAYER_NO + No,PT_ATK_R ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PT_ATK_R;		// 攻撃力を格納する
					break;
				case TURN_D :	// 下
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_PLAYER_NO + No,PT_ATK_F ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PT_ATK_F;		// 攻撃力を格納する
			}
			break;
		// ***********************   プチタイプ   **************************E


		// *********************** 魔法使いタイプ **************************S
		case MAGIC :
			switch ( PlayerNowstatus[No].turn ){		// 方向
				case TURN_R :	// 右
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if ( !PlayerMagic[No].flg && ObjBuf[OBJ_PLAYER_NO + No].Anime == MAGIC_TIMING ){		// 魔法が発動していない状態で且つ発動タイミングなら
						PlayerMagic[No].status = 1;		// 魔法発動
					}
					if( ObjAction( OBJ_PLAYER_NO + No,MG_ATK_S ) ){
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					}
					break;
				case TURN_L :	// 左
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					if ( !PlayerMagic[No].flg && ObjBuf[OBJ_PLAYER_NO + No].Anime == MAGIC_TIMING ){		// 魔法が発動していない状態で且つ発動タイミングなら
						PlayerMagic[No].status = 1;		// 魔法発動
					}
					if( ObjAction( OBJ_PLAYER_NO + No,MG_ATK_S ) ){
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					}
					break;
				case TURN_U :		// 上
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if ( !PlayerMagic[No].flg && ObjBuf[OBJ_PLAYER_NO + No].Anime == MAGIC_TIMING ){		// 魔法が発動していない状態で且つ発動タイミングなら
						PlayerMagic[No].status = 1;		// 魔法発動
					}
					if( ObjAction( OBJ_PLAYER_NO + No,MG_ATK_R ) ){
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					}
					break;
				case TURN_D :	// 下
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if ( !PlayerMagic[No].flg && ObjBuf[OBJ_PLAYER_NO + No].Anime == MAGIC_TIMING ){		// 魔法が発動していない状態で且つ発動タイミングなら
						PlayerMagic[No].status = 1;		// 魔法発動
					}
					if( ObjAction( OBJ_PLAYER_NO + No,MG_ATK_F ) ){
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					}
					break;
			}
			break;
		// *********************** 魔法使いタイプ **************************E


		// ***********************  パワータイプ  **************************S
		case POWER :
			switch ( PlayerNowstatus[No].turn ){		// 方向
				case TURN_R :	// 右
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_PLAYER_NO + No,PW_ATK_S ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PW_ATK_S;		// 攻撃力を格納する
					break;
				case TURN_L :	// 左
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					if( ObjAction( OBJ_PLAYER_NO + No,PW_ATK_S ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PW_ATK_S;		// 攻撃力を格納する
					break;
				case TURN_U :		// 上
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_PLAYER_NO + No,PW_ATK_R ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PW_ATK_R;		// 攻撃力を格納する
					break;
				case TURN_D :	// 下
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_PLAYER_NO + No,PW_ATK_F ) )
						PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
					NowAnime = (ANIME*)PW_ATK_F;		// 攻撃力を格納する
			}
			break;
		// ***********************  パワータイプ  **************************E


		// *********************** ビーストタイプ **************************S
		case BEAST :
			switch ( PlayerNowstatus[No].turn ){		// 方向
				case TURN_R :	// 右
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK_S ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)BS_ATK_S;
					}
					else if( PlayerNowstatus[No].atk == 1 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK2_S ) ){
							PlayerNowstatus[No].type = INTERVAL;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 2;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK2_S;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK3_S ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK3_S;
					}						
					break;
				case TURN_L :	// 左
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK_S ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)BS_ATK_S;
					}
					else if( PlayerNowstatus[No].atk == 1 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK2_S ) ){
							PlayerNowstatus[No].type = INTERVAL;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 2;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK2_S;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK3_S ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK3_S;
					}						
					break;
				case TURN_U :		// 上
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK_R ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)BS_ATK_R;
					}
					else if( PlayerNowstatus[No].atk == 1 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK2_R ) ){
							PlayerNowstatus[No].type = INTERVAL;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 2;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK2_R;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK3_R ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK3_R;
					}						
					break;
				case TURN_D :	// 下
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					if( PlayerNowstatus[No].atk == 0 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK_F ) ){
							PlayerNowstatus[No].atk = 1;
							PlayerNowstatus[No].type = INTERVAL;
						}
						NowAnime = (ANIME*)BS_ATK_F;
					}
					else if( PlayerNowstatus[No].atk == 1 ){
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK2_F ) ){
							PlayerNowstatus[No].type = INTERVAL;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 2;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK2_F;
					}
					else {
						if( ObjAction( OBJ_PLAYER_NO + No,BS_ATK3_F ) ){
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
							PlayerNowstatus[No].atk = 0;
							PlayerNowstatus[No].keep = 0;
						}
						NowAnime = (ANIME*)BS_ATK3_F;
					}						
			}
			break;
		// *********************** ビーストタイプ **************************E


		default :
			break;
	}
	// ******************** 選択キャラによる処理の分岐 ********************E

	return;
}

