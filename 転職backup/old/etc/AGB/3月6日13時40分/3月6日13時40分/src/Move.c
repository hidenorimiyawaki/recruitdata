#include "All.h"

//**************************************************************************** S
//	  関数名		:	キャラクターの移動処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	どのタイプも基本的には同じ処理、移動値に変化あり。
//	 最終更新日		:	2003/03/05 (水)
//**************************************************************************** E

void Move (u8 No)
{
	// ******************** 選択キャラによる処理の分岐 ********************S

	switch ( PlayerNowstatus[No].name ){
		// *********************** スピードタイプ **************************S
		
		case SPEED :
			switch ( SioKey[No] & PLUS_KEY_MASK ){				// 十字キー入力
				case R_U_KEY :	// 右上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_SPEED ];			// 歩きスピードを√2で割った値
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_SPEED ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)SP_WALK_S;
					break;
				case R_D_KEY :	// 右下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_SPEED ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_SPEED ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)SP_WALK_S;
					break;
				case L_U_KEY :	// 左上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_SPEED ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_SPEED ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)SP_WALK_S;
					break;
				case L_D_KEY :	// 左下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_SPEED ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_SPEED ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)SP_WALK_S;
					break;
				case R_KEY :	// 右移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_SPEED;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)SP_WALK_S;
					break;
				case L_KEY :	// 左移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_SPEED;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)SP_WALK_S;
					break;
				case U_KEY :	// 上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_SPEED;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_R );
					PlayerNowstatus[No].turn = TURN_U;
					NowAnime = (ANIME*)SP_WALK_R;
					break;
				case D_KEY :	// 下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_SPEED;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,SP_WALK_F );
					PlayerNowstatus[No].turn = TURN_D;
					NowAnime = (ANIME*)SP_WALK_F;
					break;
				default :		// 入力無し
					ObjBuf[OBJ_PLAYER_NO + No].Cnt = ObjBuf[OBJ_PLAYER_NO + No].Anime = 0;			// アニメーション状態を最初に戻す
					// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[No].turn ){		// 方向
							case TURN_R :	// 右
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,SP_STAND_S );
								NowAnime = (ANIME*)SP_STAND_S;
								break;
							case TURN_L :	// 左
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
								ObjAction( OBJ_PLAYER_NO + No,SP_STAND_S );
								NowAnime = (ANIME*)SP_STAND_S;
								break;
							case TURN_U :		// 上
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,SP_STAND_R );
								NowAnime = (ANIME*)SP_STAND_R;
								break;
							case TURN_D :	// 下
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,SP_STAND_F );
								NowAnime = (ANIME*)SP_STAND_F;
								break;
						}
					// ************ 移動方向の維持 *************E
			}
			break;
		// *********************** スピードタイプ **************************E


		// ***********************   プチタイプ   **************************S
		case PETIT :
			switch ( SioKey[No] & PLUS_KEY_MASK ){				// 十字キー入力
				case R_U_KEY :	// 右上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_PETIT ];			// 歩きスピードを√2で割った値
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_PETIT ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PT_WALK_S;
					break;
				case R_D_KEY :	// 右下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_PETIT ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_PETIT ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PT_WALK_S;
					break;
				case L_U_KEY :	// 左上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_PETIT ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_PETIT ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PT_WALK_S;
				case L_D_KEY :	// 左下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_PETIT ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_PETIT ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)PT_WALK_S;
					break;
				case R_KEY :	// 右移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_PETIT;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PT_WALK_S;
					break;
				case L_KEY :	// 左移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_PETIT;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)PT_WALK_S;
					break;
				case U_KEY :	// 上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_PETIT;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_R );
					PlayerNowstatus[No].turn = TURN_U;
					NowAnime = (ANIME*)PT_WALK_R;
					break;
				case D_KEY :	// 下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_PETIT;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PT_WALK_F );
					PlayerNowstatus[No].turn = TURN_D;
					NowAnime = (ANIME*)PT_WALK_F;
					break;
				default :		// 入力無し
					ObjBuf[OBJ_PLAYER_NO + No].Cnt = ObjBuf[OBJ_PLAYER_NO + No].Anime = 0;			// アニメーション状態を最初に戻す
					// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[No].turn ){		// 方向
							case TURN_R :	// 右
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,PT_STAND_S );
								NowAnime = (ANIME*)PT_STAND_S;
								break;
							case TURN_L :	// 左
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
								ObjAction( OBJ_PLAYER_NO + No,PT_STAND_S );
								NowAnime = (ANIME*)PT_STAND_S;
								break;
							case TURN_U :		// 上
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,PT_STAND_R );
								NowAnime = (ANIME*)PT_STAND_R;
								break;
							case TURN_D :	// 下
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,PT_STAND_F );
								NowAnime = (ANIME*)PT_STAND_F;
								break;
						}
					// ************ 移動方向の維持 *************E
			}
			break;
		// ***********************   プチタイプ   **************************E


		// *********************** 魔法使いタイプ **************************S
		case MAGIC :
			switch ( SioKey[No] & PLUS_KEY_MASK ){				// 十字キー入力
				case R_U_KEY :	// 右上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_MAGIC ];			// 歩きスピードを√2で割った値
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_MAGIC ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)MG_WALK_S;
					break;
				case R_D_KEY :	// 右下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_MAGIC ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_MAGIC ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)MG_WALK_S;
					break;
				case L_U_KEY :	// 左上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_MAGIC ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_MAGIC ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)MG_WALK_S;
				case L_D_KEY :	// 左下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_MAGIC ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_MAGIC ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)MG_WALK_S;
					break;
				case R_KEY :	// 右移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_MAGIC;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)MG_WALK_S;
					break;
				case L_KEY :	// 左移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_MAGIC;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)MG_WALK_S;
					break;
				case U_KEY :	// 上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_MAGIC;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_R );
					PlayerNowstatus[No].turn = TURN_U;
					NowAnime = (ANIME*)MG_WALK_R;
					break;
				case D_KEY :	// 下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_MAGIC;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,MG_WALK_F );
					PlayerNowstatus[No].turn = TURN_D;
					NowAnime = (ANIME*)MG_WALK_F;
					break;
				default :		// 入力無し
					ObjBuf[OBJ_PLAYER_NO + No].Cnt = ObjBuf[OBJ_PLAYER_NO + No].Anime = 0;			// アニメーション状態を最初に戻す
					// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[No].turn ){		// 方向
							case TURN_R :	// 右
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,MG_STAND_S );
								NowAnime = (ANIME*)MG_STAND_S;
								break;
							case TURN_L :	// 左
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
								ObjAction( OBJ_PLAYER_NO + No,MG_STAND_S );
								NowAnime = (ANIME*)MG_STAND_S;
								break;
							case TURN_U :		// 上
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,MG_STAND_R );
								NowAnime = (ANIME*)MG_STAND_R;
								break;
							case TURN_D :	// 下
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,MG_STAND_F );
								NowAnime = (ANIME*)MG_STAND_F;
								break;
						}
					// ************ 移動方向の維持 *************E
			}
			break;
		// *********************** 魔法使いタイプ **************************E


		// ***********************  パワータイプ  **************************S
		case POWER :
			switch ( SioKey[No] & PLUS_KEY_MASK ){				// 十字キー入力
				case R_U_KEY :	// 右上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_POWER ];			// 歩きスピードを√2で割った値
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_POWER ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PW_WALK_S;
					break;
				case R_D_KEY :	// 右下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_POWER ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_POWER ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PW_WALK_S;
					break;
				case L_U_KEY :	// 左上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_POWER ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_POWER ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PW_WALK_S;
				case L_D_KEY :	// 左下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_POWER ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_POWER ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)PW_WALK_S;
					break;
				case R_KEY :	// 右移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_POWER;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)PW_WALK_S;
					break;
				case L_KEY :	// 左移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_POWER;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)PW_WALK_S;
					break;
				case U_KEY :	// 上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_POWER;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_R );
					PlayerNowstatus[No].turn = TURN_U;
					NowAnime = (ANIME*)PW_WALK_R;
					break;
				case D_KEY :	// 下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_POWER;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,PW_WALK_F );
					PlayerNowstatus[No].turn = TURN_D;
					NowAnime = (ANIME*)PW_WALK_F;
					break;
				default :		// 入力無し
					ObjBuf[OBJ_PLAYER_NO + No].Cnt = ObjBuf[OBJ_PLAYER_NO + No].Anime = 0;			// アニメーション状態を最初に戻す
					// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[No].turn ){		// 方向
							case TURN_R :	// 右
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,PW_STAND_S );
								NowAnime = (ANIME*)PW_STAND_S;
								break;
							case TURN_L :	// 左
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
								ObjAction( OBJ_PLAYER_NO + No,PW_STAND_S );
								NowAnime = (ANIME*)PW_STAND_S;
								break;
							case TURN_U :		// 上
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,PW_STAND_R );
								NowAnime = (ANIME*)PW_STAND_R;
								break;
							case TURN_D :	// 下
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,PW_STAND_F );
								NowAnime = (ANIME*)PW_STAND_F;
								break;
						}
					// ************ 移動方向の維持 *************E
			}
			break;
		// ***********************  パワータイプ  **************************E


		// *********************** ビーストタイプ **************************S
		case BEAST :
			switch ( SioKey[No] & PLUS_KEY_MASK ){				// 十字キー入力
				case R_U_KEY :	// 右上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_BEAST ];			// 歩きスピードを√2で割った値
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_BEAST ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)BS_WALK_S;
					break;
				case R_D_KEY :	// 右下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_BEAST ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_BEAST ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)BS_WALK_S;
					break;
				case L_U_KEY :	// 左上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_BEAST ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_BEAST ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)BS_WALK_S;
				case L_D_KEY :	// 左下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_BEAST ];
						ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_BEAST ];
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)BS_WALK_S;
					break;
				case R_KEY :	// 右移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_BEAST;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_S );
					PlayerNowstatus[No].turn = TURN_R;
					NowAnime = (ANIME*)BS_WALK_S;
					break;
				case L_KEY :	// 左移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_BEAST;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_S );
					PlayerNowstatus[No].turn = TURN_L;
					NowAnime = (ANIME*)BS_WALK_S;
					break;
				case U_KEY :	// 上移動
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_BEAST;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_R );
					PlayerNowstatus[No].turn = TURN_U;
					NowAnime = (ANIME*)BS_WALK_R;
					break;
				case D_KEY :	// 下移動
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_BEAST;
						}
					}
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjAction( OBJ_PLAYER_NO + No,BS_WALK_F );
					PlayerNowstatus[No].turn = TURN_D;
					NowAnime = (ANIME*)BS_WALK_F;
					break;
				default :		// 入力無し
					ObjBuf[OBJ_PLAYER_NO + No].Cnt = ObjBuf[OBJ_PLAYER_NO + No].Anime = 0;			// アニメーション状態を最初に戻す
					// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[No].turn ){		// 方向
							case TURN_R :	// 右
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,BS_STAND_S );
								NowAnime = (ANIME*)BS_STAND_S;
								break;
							case TURN_L :	// 左
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
								ObjAction( OBJ_PLAYER_NO + No,BS_STAND_S );
								NowAnime = (ANIME*)BS_STAND_S;
								break;
							case TURN_U :		// 上
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,BS_STAND_R );
								NowAnime = (ANIME*)BS_STAND_R;
								break;
							case TURN_D :	// 下
								ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
								ObjAction( OBJ_PLAYER_NO + No,BS_STAND_F );
								NowAnime = (ANIME*)BS_STAND_F;
								break;
						}
					// ************ 移動方向の維持 *************E
			}
			break;
		// *********************** ビーストタイプ **************************E


		default :
			break;
	}
	// ******************** 選択キャラによる処理の分岐 ********************E

	return;
}


//**************************************************************************** S
//	  関数名		:	キャラクターのスキル使用時の移動処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	スピードのみの処理
//	 最終更新日		:	2003/03/05 (水)
//**************************************************************************** E
void SkillMove(u8 No){
	
	// 攻撃中にPlayerNowstatus[No].typeが変更されたときにフラグ等を初期化する
	if( PlayerNowstatus[No].atk && (!PlayerNowstatus[No].type == ATK || PlayerNowstatus[No].type == INTERVAL)){
		PlayerNowstatus[No].atk = 0;
		PlayerNowstatus[No].keep = 0;
	}
	if( !PlayerNowstatus[No].skillflg ){
		switch ( SioKey[No] & PLUS_KEY_MASK ){				// 十字キー入力
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
				switch ( PlayerNowstatus[No].turn ){		// 方向
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
		PlayerNowstatus[No].skillflg = 1;
	}
	switch ( PlayerNowstatus[No].turn ){		// 方向
		case TURN_R :	// 右
			if( ObjAction( OBJ_PLAYER_NO + No,SP_SKILL_S )){
				PlayerNowstatus[No].type = STAND;
				PlayerNowstatus[No].turn = TURN_L;
				ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
				PlayerNowstatus[No].skillflg = 0;
			}
			if( work_v > 0){
				if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) /8)+2][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
					ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
					ObjBuf[OBJ_PLAYER_NO + No].PosY += ((work_v * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				}
			}
			else if( work_v < 0){
				if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 32)/8)-2][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16) +32)/8)] == 0x0c) ){
					ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
					ObjBuf[OBJ_PLAYER_NO + No].PosY += ((work_v * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				}
			}
			else {
				if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
					ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				}
			}
			NowAnime = (ANIME*)SP_SKILL_S;
			break;
		case TURN_L :	// 左
			if( ObjAction( OBJ_PLAYER_NO + No,SP_SKILL_S )){
				PlayerNowstatus[No].type = STAND;
				PlayerNowstatus[No].turn = TURN_R;
				ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
				PlayerNowstatus[No].skillflg = 0;
			}
			if( work_v > 0){
				if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+2][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)-1] == 0x0c) ){
					ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
					ObjBuf[OBJ_PLAYER_NO + No].PosY += ((work_v * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				}
			}
			else if( work_v < 0){
				if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 32)/8)-2][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)-1] == 0x0c) ){
					ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
					ObjBuf[OBJ_PLAYER_NO + No].PosY += ((work_v * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				}
			}
			else {
				if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)-1] == 0x0c) ){
					ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				}
			}
			NowAnime = (ANIME*)SP_SKILL_S;
			break;
		case TURN_U :		// 上
			if( ObjAction( OBJ_PLAYER_NO + No,SP_SKILL_R )){
				PlayerNowstatus[No].type = STAND;
				PlayerNowstatus[No].turn = TURN_D;
				ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
				PlayerNowstatus[No].skillflg = 0;
			}
			if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)-1][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+1] == 0x0c) ){
				ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				ObjBuf[OBJ_PLAYER_NO + No].PosY += ((work_v * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
			}
			NowAnime = (ANIME*)SP_SKILL_R;
			break;
		case TURN_D :	// 下
			if( ObjAction( OBJ_PLAYER_NO + No,SP_SKILL_F )){
				PlayerNowstatus[No].type = STAND;
				PlayerNowstatus[No].turn = TURN_U;
				ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
				PlayerNowstatus[No].skillflg = 0;
			}
			if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+ 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+1] == 0x0c) ){
				ObjBuf[OBJ_PLAYER_NO + No].PosX += ((work_h * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
				ObjBuf[OBJ_PLAYER_NO + No].PosY += ((work_v * (SP_DASH - ObjBuf[OBJ_PLAYER_NO + No].Anime)) << 16);
			}
			NowAnime = (ANIME*)SP_SKILL_F;
			break;
	}
}


//**************************************************************************** S
//	  関数名		:	キャラクターの必殺技使用時の移動処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	スピードのみの処理
//	 最終更新日		:	2003/03/05 (水)
//**************************************************************************** E
void SpecialMove(u8 No){
	switch ( PlayerNowstatus[No].name ){	
	// *********************** スピードタイプ **************************S
		case SPEED :
			// 攻撃中にHeroStatusが変更されたときにフラグ等を初期化する
			if( PlayerNowstatus[No].atk && (!PlayerNowstatus[No].type == ATK || !PlayerNowstatus[No].type == INTERVAL)){
				PlayerNowstatus[No].atk = 0;
				PlayerNowstatus[No].keep = 0;
			}
			switch ( PlayerNowstatus[No].turn ){		// 方向
				case TURN_R :	// 右
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_SPCIAL_NO + No, SP_SPECIAL_EF_S ) );
					if( ObjAction( OBJ_PLAYER_NO + No, SP_SPECIAL_S ) ){
						PlayerNowstatus[No].type = STAND;
						SpBgCnt = 0;
						PlayerNowstatus[No].sp = 0;
					}
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+1][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX += (SPECIAL_SPEED << 16);
					}
					NowAnime = (ANIME*)SP_SPECIAL_S;		// 攻撃力を格納する
					break;
				case TURN_L :	// 左
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
					ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 1;
					if( ObjAction( OBJ_SPCIAL_NO + No, SP_SPECIAL_EF_S ) );
					if( ObjAction( OBJ_PLAYER_NO + No, SP_SPECIAL_S ) ){
						PlayerNowstatus[No].type = STAND;
						SpBgCnt = 0;
						PlayerNowstatus[No].sp = 0;
					}
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+1][(ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosX -= (SPECIAL_SPEED << 16);
					}
					NowAnime = (ANIME*)SP_SPECIAL_S;
					break;
				case TURN_U :		// 上
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_SPCIAL_NO + No, SP_SPECIAL_EF_R ) );
					if( ObjAction( OBJ_PLAYER_NO + No, SP_SPECIAL_R ) ){
						PlayerNowstatus[No].type = STAND;
						SpBgCnt = 0;
						PlayerNowstatus[No].sp = 0;
					}
					if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+1] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosY -= (SPECIAL_SPEED << 16);
					}
					NowAnime = (ANIME*)SP_SPECIAL_R;
					break;
				case TURN_D :	// 下
					ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
					ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 0;
					if( ObjAction( OBJ_SPCIAL_NO + No, SP_SPECIAL_EF_F ) );
					if( ObjAction( OBJ_PLAYER_NO + No, SP_SPECIAL_F ) ){
						PlayerNowstatus[No].type = STAND;
						SpBgCnt = 0;
						PlayerNowstatus[No].sp = 0;
					}
					if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+1] == 0x0c) ){
						ObjBuf[OBJ_PLAYER_NO + No].PosY += (SPECIAL_SPEED << 16);
					}
					NowAnime = (ANIME*)SP_SPECIAL_F;
					break;
				}
			break;
		// ***********************   スピードタイプ   **************************E

/*			
		// *********************** ビーストタイプ **************************S
		case BEAST :
			if( !PlayerNowstatus[No].spflg ){
				PlayerNowstatus[No].spflg = ON;
				PlayerNowstatus[No].keep = 300;
			}
			if( PlayerNowstatus[No].keep <= 1000 ){

				PlayerNowstatus[No].keep--;

				switch ( SioKey[No] & PLUS_KEY_MASK ){			// 十字キー入力
					case R_U_KEY :	// 右上移動
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						PlayerNowstatus[No].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						PlayerNowstatus[No].turn = TURN_D;
				}

				switch ( PlayerNowstatus[No].turn ){		// 方向
					case TURN_R :	// 右
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_SPCIAL_NO + No, SPLASH_EF_S ) );
						if( ObjAction( OBJ_PLAYER_NO + No, BS_SPECIAL_S ) ){
						}
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+1][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += (BEAST_SPEED << 16);
						}
						NowAnime = (ANIME*)BS_SPECIAL_S;		// 攻撃力を格納する
						break;
					case TURN_L :	// 左
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
						ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 1;
						if( ObjAction( OBJ_SPCIAL_NO + No, SPLASH_EF_S ) );
						if( ObjAction( OBJ_PLAYER_NO + No, BS_SPECIAL_S ) ){
						}
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+1][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= (BEAST_SPEED << 16);
						}
						NowAnime = (ANIME*)BS_SPECIAL_S;
						break;
					case TURN_U :		// 上
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_SPCIAL_NO + No, SPLASH_EF_R ) );
						if( ObjAction( OBJ_PLAYER_NO + No, BS_SPECIAL_R ) ){
						}
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= (BEAST_SPEED << 16);
						}
						NowAnime = (ANIME*)BS_SPECIAL_R;
						break;
					case TURN_D :	// 下
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						ObjBuf[OBJ_SPCIAL_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_SPCIAL_NO + No, SPLASH_EF_F ) );
						if( ObjAction( OBJ_PLAYER_NO + No, BS_SPECIAL_F ) ){
						}
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+ 31)/8][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+1] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosY += (BEAST_SPEED << 16);
						}
						NowAnime = (ANIME*)BS_SPECIAL_F;
						break;
				}
			}
			else{
				PlayerNowstatus[No].spflg = OFF;
				PlayerNowstatus[No].type = STAND;
				SpBgCnt = 0;
				PlayerNowstatus[No].sp = 0;
			}
*/
			break;
		// *********************** ビーストタイプ **************************E
		
		default :
			break;
	}
}
