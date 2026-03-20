#include "All.h"

//**************************************************************************** S
//	  関数名		:	キャラクターのジャンプ行動処理
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	どのタイプも基本的には同じ処理、移動値に変化あり。
//	 最終更新日		:	2003/03/05 (水)
//**************************************************************************** E

void Jump (u8 No)
{
	// ******************** 選択キャラによる処理の分岐 ********************S

	switch ( PlayerNowstatus[No].name ){
		// *********************** スピードタイプ **************************S
		
		case SPEED :
			// ************ SPジャンプ状態 *************S

				// ************ ジャンプ中の移動 ************S
				switch ( SioKey[No] & PLUS_KEY_MASK ){			// 十字キー入力
					case R_U_KEY :	// 右上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_SPEED ];		// 歩きスピードを√2で割った値
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_SPEED ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_SPEED ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_SPEED ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_SPEED ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_SPEED ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_SPEED ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_SPEED ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_SPEED;
							}
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_SPEED;
							}
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_SPEED;
							}
						}
						PlayerNowstatus[No].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_SPEED;
							}
						}
						PlayerNowstatus[No].turn = TURN_D;
				}
				// ************ ジャンプ中の移動 *************E

				switch ( PlayerNowstatus[No].turn ){		// 方向
					case TURN_R :	// 右
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,SP_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)SP_JUMP_S;
						break;
					case TURN_L :	// 左
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
						if( ObjAction( OBJ_PLAYER_NO + No,SP_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)SP_JUMP_S;
						break;
					case TURN_U :		// 上
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,SP_JUMP_R ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)SP_JUMP_R;
						break;
					case TURN_D :	// 下
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,SP_JUMP_F ) )
							PlayerNowstatus[No].type = STAND;
						NowAnime = (ANIME*)SP_JUMP_F;
						break;
				}
				break;
			// ************* SPジャンプ状態 **************E

			break;
		// *********************** スピードタイプ **************************E


		// ***********************   プチタイプ   **************************S
		case PETIT :
			// ************ PTジャンプ状態 *************S

				// ************ ジャンプ中の移動 ************S
				switch ( SioKey[No] & PLUS_KEY_MASK ){			// 十字キー入力
					case R_U_KEY :	// 右上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_PETIT ];		// 歩きスピードを√2で割った値
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_PETIT ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_PETIT ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_PETIT ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_PETIT ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_PETIT ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_PETIT ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_PETIT ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_PETIT;
							}
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_PETIT;
							}
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_PETIT;
							}
						}
						PlayerNowstatus[No].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_PETIT;
							}
						}
						PlayerNowstatus[No].turn = TURN_D;
				}
				// ************ ジャンプ中の移動 *************E

				switch ( PlayerNowstatus[No].turn ){		// 方向
					case TURN_R :	// 右
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,PT_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)PT_JUMP_S;
						break;
					case TURN_L :	// 左
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
						if( ObjAction( OBJ_PLAYER_NO + No,PT_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)PT_JUMP_S;
						break;
					case TURN_U :		// 上
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,PT_JUMP_R ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)PT_JUMP_R;
						break;
					case TURN_D :	// 下
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,PT_JUMP_F ) )
							PlayerNowstatus[No].type = STAND;
						NowAnime = (ANIME*)PT_JUMP_F;
						break;
				}
				break;
			// ************* PTジャンプ状態 **************E
			break;
		// ***********************   プチタイプ   **************************E


		// *********************** 魔法使いタイプ **************************S
		case MAGIC :
			// ************ MGジャンプ状態 *************S

				// ************ ジャンプ中の移動 ************S
				switch ( SioKey[No] & PLUS_KEY_MASK ){			// 十字キー入力
					case R_U_KEY :	// 右上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_MAGIC ];		// 歩きスピードを√2で割った値
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_MAGIC ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_MAGIC ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_MAGIC ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_MAGIC ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_MAGIC ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_MAGIC ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_MAGIC ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_MAGIC;
							}
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_MAGIC;
							}
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_MAGIC;
							}
						}
						PlayerNowstatus[No].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_MAGIC;
							}
						}
						PlayerNowstatus[No].turn = TURN_D;
				}
				// ************ ジャンプ中の移動 *************E

				switch ( PlayerNowstatus[No].turn ){		// 方向
					case TURN_R :	// 右
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,MG_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)MG_JUMP_S;
						break;
					case TURN_L :	// 左
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
						if( ObjAction( OBJ_PLAYER_NO + No,MG_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)MG_JUMP_S;
						break;
					case TURN_U :		// 上
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,MG_JUMP_R ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)MG_JUMP_R;
						break;
					case TURN_D :	// 下
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,MG_JUMP_F ) )
							PlayerNowstatus[No].type = STAND;
						NowAnime = (ANIME*)MG_JUMP_F;
						break;
				}
				break;
			// ************* MGジャンプ状態 **************E
			break;
		// *********************** 魔法使いタイプ **************************E


		// ***********************  パワータイプ  **************************S
		case POWER :
			// ************ PWジャンプ状態 *************S

				// ************ ジャンプ中の移動 ************S
				switch ( SioKey[No] & PLUS_KEY_MASK ){			// 十字キー入力
					case R_U_KEY :	// 右上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_POWER ];		// 歩きスピードを√2で割った値
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_POWER ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_POWER ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_POWER ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_POWER ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_POWER ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_POWER ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_POWER ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_POWER;
							}
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_POWER;
							}
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_POWER;
							}
						}
						PlayerNowstatus[No].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_POWER;
							}
						}
						PlayerNowstatus[No].turn = TURN_D;
				}
				// ************ ジャンプ中の移動 *************E

				switch ( PlayerNowstatus[No].turn ){		// 方向
					case TURN_R :	// 右
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,PW_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)PW_JUMP_S;
						break;
					case TURN_L :	// 左
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
						if( ObjAction( OBJ_PLAYER_NO + No,PW_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)PW_JUMP_S;
						break;
					case TURN_U :		// 上
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,PW_JUMP_R ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)MG_JUMP_R;
						break;
					case TURN_D :	// 下
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,PW_JUMP_F ) )
							PlayerNowstatus[No].type = STAND;
						NowAnime = (ANIME*)PW_JUMP_F;
						break;
				}
				break;
			// ************* PWジャンプ状態 **************E
			break;
		// ***********************  パワータイプ  **************************E


		// *********************** ビーストタイプ **************************S
		case BEAST :
			// ************ PWジャンプ状態 *************S

				// ************ ジャンプ中の移動 ************S
				switch ( SioKey[No] & PLUS_KEY_MASK ){			// 十字キー入力
					case R_U_KEY :	// 右上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_BEAST ];		// 歩きスピードを√2で割った値
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_BEAST ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+32)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX += c_DivRoot2[ WALK_BEAST ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_BEAST ];
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_BEAST ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY -= c_DivRoot2[ WALK_BEAST ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+32)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							ObjBuf[OBJ_PLAYER_NO + No].PosX -= c_DivRoot2[ WALK_BEAST ];
							ObjBuf[OBJ_PLAYER_NO + No].PosY += c_DivRoot2[ WALK_BEAST ];
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+31)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104+31)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX += WALK2_BEAST;
							}
						}
						PlayerNowstatus[No].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)+3][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)+1][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosX -= WALK2_BEAST;
							}
						}
						PlayerNowstatus[No].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						if ( !( bg_sanctuary_Wall[((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY -= WALK2_BEAST;
							}
						}
						PlayerNowstatus[No].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16) + 31)/8)][((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)/8)+3] == 0x0c) ){
							if ( !( bg_sanctuary_Wall[(((ObjBuf[OBJ_PLAYER_NO + No].PosY >> 16)+64 + 31)/8)][(((ObjBuf[OBJ_PLAYER_NO + No].PosX >> 16)+104)/8)+1] == 0x0c) ){
								ObjBuf[OBJ_PLAYER_NO + No].PosY += WALK2_BEAST;
							}
						}
						PlayerNowstatus[No].turn = TURN_D;
				}
				// ************ ジャンプ中の移動 *************E

				switch ( PlayerNowstatus[No].turn ){		// 方向
					case TURN_R :	// 右
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,BS_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)BS_JUMP_S;
						break;
					case TURN_L :	// 左
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 1;
						if( ObjAction( OBJ_PLAYER_NO + No,BS_JUMP_S ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)BS_JUMP_S;
						break;
					case TURN_U :		// 上
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,BS_JUMP_R ) )
							PlayerNowstatus[No].type = STAND;				// アニメーションが終了したら通常状態へ変更
						NowAnime = (ANIME*)BS_JUMP_R;
						break;
					case TURN_D :	// 下
						ObjBuf[OBJ_PLAYER_NO + No].Oam.HFlip = 0;
						if( ObjAction( OBJ_PLAYER_NO + No,BS_JUMP_F ) )
							PlayerNowstatus[No].type = STAND;
						NowAnime = (ANIME*)BS_JUMP_F;
						break;
				}
				break;
			// ************* MGジャンプ状態 **************E
			break;
		// *********************** ビーストタイプ **************************E


		default :
			break;
	}
	// ******************** 選択キャラによる処理の分岐 ********************E

	return;
}

