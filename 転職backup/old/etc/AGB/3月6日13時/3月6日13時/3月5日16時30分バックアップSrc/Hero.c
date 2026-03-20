#include "all.h"

//**************************************************************************** S
//	  関数名		:	キャラクターの行動処理
//	   引数 		:	無し
//	  戻り値		:	現在のアニメーション状態の攻撃力
//==============================================================================
//	 コメント		:	どのタイプも基本的に同じような処理なので見間違えに注意
//	 最終更新日		:	2003/02/07 (金)
//**************************************************************************** E

// 斜め
#define	WALK_SPEED		2				// 斜め移動でどの√をとるか
#define WALK_MAGIC		1
#define WALK_PETIT		1
#define WALK_POWER		19
#define WALK_BEAST		2

// 上下左右
#define	WALK2_SPEED		0x0001F000		// 1.9375
#define WALK2_MAGIC		0x0000F000		// 0.9375
#define WALK2_PETIT		0x00010000		// 1
#define WALK2_POWER		0x0000C000		// 0.75
#define WALK2_BEAST		0x0001C000		// 1.75
#define	ATK_INTERVAL	15				// 連続攻撃を行えるキー入力間隔
#define	MAGIC_TIMING	2				// 攻撃モーションから魔法が発動するまでのタイミング
/*
0x00002434, 0x00005A82, 0x00007EB6
17 0.2√2	18 0.5√2	19 0.7√2

0x00010000		// 1
0x00018000		// 1.5
0x0001C000		// 1.75
0x0001E000		// 1.875
0x0001F000		// 1.9375
0x00008000		// 0.5
0x0000C000		// 0.75
0x0000E000		// 0.875
0x0000F000		// 0.9375
*/
void Hero (void)
{
	vu16 ret = 0;
	NowAnime = (ANIME*)SP_STAND_F;

	// ******************** 選択キャラによる処理の分岐 ********************S

	switch ( PlayerNowstatus[PlayerNo].name ){
		// *********************** スピードタイプ **************************S
		
		case SPEED :
			// 攻撃中にPlayerNowstatus[PlayerNo].typeが変更されたときにフラグ等を初期化する
			if( PlayerNowstatus[PlayerNo].atk && (!PlayerNowstatus[PlayerNo].type == ATK || !PlayerNowstatus[PlayerNo].type == INTERVAL)){
				PlayerNowstatus[PlayerNo].atk = 0;
				PlayerNowstatus[PlayerNo].keep = 0;
			}
			switch ( PlayerNowstatus[PlayerNo].type ){	
				case INTERVAL:			// 連続攻撃インターバル
					if ( SioTrg[PlayerNo] & A_BUTTON ){
						PlayerNowstatus[PlayerNo].type = ATK;
						PlayerNowstatus[PlayerNo].keep = 0;
					}
					if( PlayerNowstatus[PlayerNo].atk == ON) PlayerNowstatus[PlayerNo].keep++;
					if( PlayerNowstatus[PlayerNo].keep >= ATK_INTERVAL) {
						PlayerNowstatus[PlayerNo].type = STAND;
						PlayerNowstatus[PlayerNo].atk = OFF;
						PlayerNowstatus[PlayerNo].keep = 0;
					}
					
				case STAND :			// 初期状態
					if ( SioTrg[PlayerNo] & A_BUTTON )		PlayerNowstatus[PlayerNo].type = ATK;
					if ( SioTrg[PlayerNo] & B_BUTTON )		PlayerNowstatus[PlayerNo].type = JUMP;
					if ( SioTrg[PlayerNo] & L_BUTTON )		PlayerNowstatus[PlayerNo].type = SKILL;
					if ( PlayerNowstatus[PlayerNo].sp >= 100 ){
						if ( SioTrg[PlayerNo] & R_BUTTON )		PlayerNowstatus[PlayerNo].type = SPECIAL;
					}
					Move();
					break;
				// ************** SP移動状態 ***************E

				// ************ SPアタック状態 *************S
				case ATK :
					
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							// Action.cからの戻り値で判定
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)SP_ATK_S;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK2_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = 0;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)SP_ATK2_S;
							}						
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)SP_ATK_S;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK2_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = OFF;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)SP_ATK2_S;
							}						
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)SP_ATK_R;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK2_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = OFF;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)SP_ATK_R;
							}						
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)SP_ATK_F;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, SP_ATK2_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = OFF;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)SP_ATK2_F;
							}						
							break;
					}
					break;
				// ************ SPアタック状態 *************E

				// ************ SPジャンプ状態 *************S
				case JUMP :	

					// ************ ジャンプ中の移動 ************S
					switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){			// 十字キー入力
						case R_U_KEY :	// 右上移動
							Hoffset += c_DivRoot2[ WALK_SPEED ];		// 歩きスピードを√2で割った値
							Voffset -= c_DivRoot2[ WALK_SPEED ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case R_D_KEY :	// 右下移動
							Hoffset += c_DivRoot2[ WALK_SPEED ];
							Voffset += c_DivRoot2[ WALK_SPEED ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_U_KEY :	// 左上移動
							Hoffset -= c_DivRoot2[ WALK_SPEED ];
							Voffset -= c_DivRoot2[ WALK_SPEED ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case L_D_KEY :	// 左下移動
							Hoffset -= c_DivRoot2[ WALK_SPEED ];
							Voffset += c_DivRoot2[ WALK_SPEED ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case R_KEY :	// 右移動
							Hoffset += WALK2_SPEED;
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_KEY :	// 左移動
							Hoffset -= WALK2_SPEED;
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case U_KEY :	// 上移動
							Voffset -= WALK2_SPEED;
							PlayerNowstatus[PlayerNo].turn = TURN_U;
							break;
						case D_KEY :	// 下移動
							Voffset += WALK2_SPEED;
							PlayerNowstatus[PlayerNo].turn = TURN_D;
					}
					// ************ ジャンプ中の移動 *************E

					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, SP_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							NowAnime = (ANIME*)SP_JUMP_S;
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, SP_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)SP_JUMP_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, SP_JUMP_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)SP_JUMP_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, SP_JUMP_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)SP_JUMP_F;
							break;
					}

					break;
				// ************* SPジャンプ状態 **************E

				// ************ SPスキル使用状態 *************S
				case SKILL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							Skill();
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
					}
					break;
				// ************ SPスキル使用状態 *************E
				
				// ************ SP必殺技使用状態 *************S
				case SPECIAL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							Special();
							break;
						case TURN_L :	// 左
							Special();
							break;
						case TURN_U :		// 上
							Special();
							break;
						case TURN_D :	// 下
							Special();
							break;
					}
					break;
				// ************ SP必殺技使用状態 *************E

				// ************  SPダメージ状態  *************S
				case DAMAGE :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, SP_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)SP_DAM_S;		// 攻撃力を格納する
							
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, SP_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)SP_DAM_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, SP_DAM_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)SP_DAM_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, SP_DAM_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)SP_DAM_F;
							break;
					}
					break;
				// ************ SPダメージ状態 *************E
				case DEAD:
					Action( 0, OBJ_MODE0_VRAM, SP_DEATH_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					break;


			}
			break;
		// *********************** スピードタイプ **************************E


		// ***********************   プチタイプ   **************************S
		case PETIT :
			switch ( PlayerNowstatus[PlayerNo].type ){
				case STAND :			// 初期状態
					if ( SioTrg[PlayerNo] & A_BUTTON )		PlayerNowstatus[PlayerNo].type = ATK;
					if ( SioTrg[PlayerNo] & B_BUTTON )		PlayerNowstatus[PlayerNo].type = JUMP;
					if ( SioTrg[PlayerNo] & L_BUTTON )		PlayerNowstatus[PlayerNo].type = SKILL;
					if ( PlayerNowstatus[PlayerNo].sp >= 100 ){
						if ( SioTrg[PlayerNo] & R_BUTTON )		PlayerNowstatus[PlayerNo].type = SPECIAL;
					}
					Move();
					break;
				// ************** PT移動状態 ***************E

				// ************ PTアタック状態 *************S
				case ATK :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PT_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							NowAnime = (ANIME*)PT_ATK_S;		// 攻撃力を格納する
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, PT_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PT_ATK_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if(  Action( 0, OBJ_MODE0_VRAM, PT_ATK_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								 PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PT_ATK_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if(  Action( 0, OBJ_MODE0_VRAM, PT_ATK_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PT_ATK_F;
							break;
					}
					break;
				// ************ PTアタック状態 *************E

				// ************ PTジャンプ状態 *************S
				case JUMP :	

					// ************ ジャンプ中の移動 ************S
					switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){			// 十字キー入力
						case R_U_KEY :	// 右上移動
							Hoffset += c_DivRoot2[ WALK_PETIT ];		// 歩きスピードを√2で割った値
							Voffset -= c_DivRoot2[ WALK_PETIT ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case R_D_KEY :	// 右下移動
							Hoffset += c_DivRoot2[ WALK_PETIT ];
							Voffset += c_DivRoot2[ WALK_PETIT ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_U_KEY :	// 左上移動
							Hoffset -= c_DivRoot2[ WALK_PETIT ];
							Voffset -= c_DivRoot2[ WALK_PETIT ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case L_D_KEY :	// 左下移動
							Hoffset -= c_DivRoot2[ WALK_PETIT ];
							Voffset += c_DivRoot2[ WALK_PETIT ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case R_KEY :	// 右移動
							Hoffset += WALK2_PETIT;
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_KEY :	// 左移動
							Hoffset -= WALK2_PETIT;
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case U_KEY :	// 上移動
							Voffset -= WALK2_PETIT;
							PlayerNowstatus[PlayerNo].turn = TURN_U;
							break;
						case D_KEY :	// 下移動
							Voffset += WALK2_PETIT;
							PlayerNowstatus[PlayerNo].turn = TURN_D;
					}
					// ************ ジャンプ中の移動 *************E

					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PT_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, PT_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PT_JUMP_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PT_JUMP_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							break;
					}
					break;
				// ************* PTジャンプ状態 **************E

				// ************ PTスキル使用状態 *************S

				case SKILL :	// スキル攻撃
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
						case TURN_L :	// 左
							Skill();
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
					}
					break;
				// ************ PTスキル使用状態 *************E

				// ************ PT必殺技使用状態 *************S
				case SPECIAL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							Special();
							break;
						case TURN_L :	// 左
							Special();
							break;
						case TURN_U :		// 上
							Special();
							break;
						case TURN_D :	// 下
							Special();
							break;
					}
					break;
				// ************ PT必殺技使用状態 *************E


				// ************  PTダメージ状態  *************S
				case DAMAGE :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PT_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PT_DAM_S;		// 攻撃力を格納する
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, PT_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PT_DAM_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PT_DAM_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PT_DAM_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PT_DAM_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PT_DAM_F;
							break;
					}
					break;
				// ************ PTダメージ状態 *************E
				case DEAD:
					Action( 0, OBJ_MODE0_VRAM, PT_DEATH_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					break;


			}
			break;
		// ***********************   プチタイプ   **************************E


		// *********************** 魔法使いタイプ **************************S
		case MAGIC :
			switch ( PlayerNowstatus[PlayerNo].type ){
				case STAND :	// 初期状態
					if ( !PlayerMagic[0].flg && SioTrg[PlayerNo] & A_BUTTON ) PlayerNowstatus[PlayerNo].type = ATK;
					if ( SioTrg[PlayerNo] & B_BUTTON )		PlayerNowstatus[PlayerNo].type = JUMP;
					if ( SioTrg[PlayerNo] & L_BUTTON )		PlayerNowstatus[PlayerNo].type = SKILL;
					if ( PlayerNowstatus[PlayerNo].sp >= 100 ){
						if ( SioTrg[PlayerNo] & R_BUTTON )		PlayerNowstatus[PlayerNo].type = SPECIAL;
					}
					Move();
					break;
				// ************** MG移動状態 ***************E

				// ************ MGアタック状態 *************S
				case ATK :	// 攻撃
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							if ( !PlayerMagic[0].flg && PlayerNowstatus[PlayerNo].anime == MAGIC_TIMING ){		// 魔法が発動していない状態で且つ発動タイミングなら
								PlayerMagic[0].status = 1;		// 魔法発動
							}
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, MG_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							}
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if ( !PlayerMagic[0].flg && PlayerNowstatus[PlayerNo].anime == MAGIC_TIMING ){
								PlayerMagic[0].status = 1;
							}
							if( Action( 0, OBJ_MODE0_VRAM, MG_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
								PlayerNowstatus[PlayerNo].type = STAND;
							}
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if ( !PlayerMagic[0].flg && PlayerNowstatus[PlayerNo].anime == MAGIC_TIMING ){
								PlayerMagic[0].status = 1;
							}
							if( Action( 0, OBJ_MODE0_VRAM, MG_ATK_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
								PlayerNowstatus[PlayerNo].type = STAND;
							}
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if ( !PlayerMagic[0].flg && PlayerNowstatus[PlayerNo].anime == MAGIC_TIMING ){
								PlayerMagic[0].status = 1;
							}
							if( Action( 0, OBJ_MODE0_VRAM, MG_ATK_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
								PlayerNowstatus[PlayerNo].type = STAND;
							}
							break;
					}
					break;
				// ************ MGアタック状態 *************E

				// ************ MGジャンプ状態 *************S
				case JUMP :

					// ************ ジャンプ中の移動 ************S
					switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){			// 十字キー入力
						case R_U_KEY :	// 右上移動
							Hoffset += c_DivRoot2[ WALK_MAGIC ];		// 歩きスピードを√2で割った値
							Voffset -= c_DivRoot2[ WALK_MAGIC ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case R_D_KEY :	// 右下移動
							Hoffset += c_DivRoot2[ WALK_MAGIC ];
							Voffset += c_DivRoot2[ WALK_MAGIC ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_U_KEY :	// 左上移動
							Hoffset -= c_DivRoot2[ WALK_MAGIC ];
							Voffset -= c_DivRoot2[ WALK_MAGIC ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case L_D_KEY :	// 左下移動
							Hoffset -= c_DivRoot2[ WALK_MAGIC ];
							Voffset += c_DivRoot2[ WALK_MAGIC ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case R_KEY :	// 右移動
							Hoffset += WALK2_MAGIC;
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_KEY :	// 左移動
							Hoffset -= WALK2_MAGIC;
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case U_KEY :	// 上移動
							Voffset -= WALK2_MAGIC;
							PlayerNowstatus[PlayerNo].turn = TURN_U;
							break;
						case D_KEY :	// 下移動
							Voffset += WALK2_MAGIC;
							PlayerNowstatus[PlayerNo].turn = TURN_D;
					}
					// ************ ジャンプ中の移動 *************E

					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, MG_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, MG_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, MG_JUMP_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, MG_JUMP_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							break;
					}
					break;
				// ************* MGジャンプ状態 **************E

				// ************ MGスキル使用状態 *************S

				case SKILL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							Skill();
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							Skill();
							break;
					}
					break;
				// ************ MGスキル使用状態 *************E

				// ************ MG必殺技使用状態 *************S
				case SPECIAL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							Special();
							break;
						case TURN_L :	// 左
							Special();
							break;
						case TURN_U :		// 上
							Special();
							break;
						case TURN_D :	// 下
							Special();
							break;
					}
					break;
				// ************ MG必殺技使用状態 *************E

				// ************  MGダメージ状態  *************S
				case DAMAGE :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, MG_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)MG_DAM_S;		// 攻撃力を格納する
							
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, MG_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)MG_DAM_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, MG_DAM_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)MG_DAM_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, MG_DAM_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)MG_DAM_F;
							break;
					}
					break;
				// ************ MGダメージ状態 *************E
				case DEAD:
					Action( 0, OBJ_MODE0_VRAM, MG_DEATH_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					break;

			}
			break;
		// *********************** 魔法使いタイプ **************************E

		// ***********************  パワータイプ  **************************E
		case POWER :
			switch ( PlayerNowstatus[PlayerNo].type ){
				case STAND :			// 初期状態
					if ( SioTrg[PlayerNo] & A_BUTTON )		PlayerNowstatus[PlayerNo].type = ATK;
					if ( SioTrg[PlayerNo] & B_BUTTON )		PlayerNowstatus[PlayerNo].type = JUMP;
					if ( SioTrg[PlayerNo] & L_BUTTON )		PlayerNowstatus[PlayerNo].type = SKILL;
					if ( PlayerNowstatus[PlayerNo].sp >= 100 ){
						if ( SioTrg[PlayerNo] & R_BUTTON )		PlayerNowstatus[PlayerNo].type = SPECIAL;
					}
					Move();
					break;
				// ************** PW移動状態 ***************E

				// ************ PWアタック状態 *************S
				case ATK :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							// Action.cからの戻り値で判定
							if( Action( 0, OBJ_MODE0_VRAM, PW_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							NowAnime = (ANIME*)PW_ATK_S;
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, PW_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								 PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PW_ATK_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_ATK_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PW_ATK_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_ATK_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PW_ATK_F;
							break;
					}
					break;
				// ************ PWアタック状態 *************E

				// ************ PWジャンプ状態 *************S
				case JUMP :	

					// ************ ジャンプ中の移動 ************S
					switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){			// 十字キー入力
						case R_U_KEY :	// 右上移動
							Hoffset += c_DivRoot2[ WALK_POWER ];		// 歩きスピードを√2で割った値
							Voffset -= c_DivRoot2[ WALK_POWER ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case R_D_KEY :	// 右下移動
							Hoffset += c_DivRoot2[ WALK_POWER ];
							Voffset += c_DivRoot2[ WALK_POWER ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_U_KEY :	// 左上移動
							Hoffset -= c_DivRoot2[ WALK_POWER ];
							Voffset -= c_DivRoot2[ WALK_POWER ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case L_D_KEY :	// 左下移動
							Hoffset -= c_DivRoot2[ WALK_POWER ];
							Voffset += c_DivRoot2[ WALK_POWER ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case R_KEY :	// 右移動
							Hoffset += WALK2_POWER;
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_KEY :	// 左移動
							Hoffset -= WALK2_POWER;
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case U_KEY :	// 上移動
							Voffset -= WALK2_POWER;
							PlayerNowstatus[PlayerNo].turn = TURN_U;
							break;
						case D_KEY :	// 下移動
							Voffset += WALK2_POWER;
							PlayerNowstatus[PlayerNo].turn = TURN_D;
					}
					// ************ ジャンプ中の移動 *************E

					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							NowAnime = (ANIME*)PW_JUMP_S;
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, PW_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PW_JUMP_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_JUMP_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PW_JUMP_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_JUMP_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)PW_JUMP_F;
							break;
					}
					break;
				// ************* PWジャンプ状態 **************E

				// ************ PWスキル使用状態 *************S
				case SKILL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							NowAnime = (ANIME*)PW_SPECIAL_S;		// 攻撃力を格納する
							Skill();
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							NowAnime = (ANIME*)PW_SPECIAL_S;
							Skill();
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							NowAnime = (ANIME*)PW_SPECIAL_R;
							Skill();
							break;
						case TURN_D :	// 下a
							OamBuf[0].Oam.HFlip = 0;
							NowAnime = (ANIME*)PW_SPECIAL_F;
							Skill();
							break;
					}
					break;
				// ************ PWスキル使用状態 *************E

				// ************ PW必殺技使用状態 *************S
				case SPECIAL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							Special();
							break;
						case TURN_L :	// 左
							Special();
							break;
						case TURN_U :		// 上
							Special();
							break;
						case TURN_D :	// 下
							Special();
							break;
					}
					break;
				// ************ PW必殺技使用状態 *************E

				// ************  PWダメージ状態  *************S
				case DAMAGE :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PW_DAM_S;		// 攻撃力を格納する
							
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, PW_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PW_DAM_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_DAM_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PW_DAM_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, PW_DAM_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)PW_DAM_F;
							break;
					}
					break;
				// ************ PWダメージ状態 *************E
				case DEAD:
					Action( 0, OBJ_MODE0_VRAM, PW_DEATH_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
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

			switch ( PlayerNowstatus[PlayerNo].type ){
				case INTERVAL:
					if ( SioTrg[PlayerNo] & A_BUTTON ){
						PlayerNowstatus[PlayerNo].type = ATK;
						PlayerNowstatus[PlayerNo].keep = 0;
					}
					if( PlayerNowstatus[PlayerNo].atk ) PlayerNowstatus[PlayerNo].keep++;
					if( PlayerNowstatus[PlayerNo].keep >= ATK_INTERVAL) {
						PlayerNowstatus[PlayerNo].atk = 0;
						PlayerNowstatus[PlayerNo].type = STAND;
						PlayerNowstatus[PlayerNo].keep = 0;
					}
				
				case STAND :			// 初期状態
					if ( SioTrg[PlayerNo] & A_BUTTON )		PlayerNowstatus[PlayerNo].type = ATK;
					if ( SioTrg[PlayerNo] & B_BUTTON )		PlayerNowstatus[PlayerNo].type = JUMP;
					if ( SioTrg[PlayerNo] & L_BUTTON )		PlayerNowstatus[PlayerNo].type = SKILL;
					if ( PlayerNowstatus[PlayerNo].sp >= 100 ){
						if ( SioTrg[PlayerNo] & R_BUTTON )		PlayerNowstatus[PlayerNo].type = SPECIAL;
					}
					Move();
					break;
				// ************** BS移動状態 ***************E

				// ************ BSアタック状態 *************S
				case ATK :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							// Action.cからの戻り値で判定
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK_S;
							}
							else if( PlayerNowstatus[PlayerNo].atk == 1 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK2_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 2;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK2_S;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK3_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = 0;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)BS_ATK3_S;
							}						
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK_S;
							}
							else if( PlayerNowstatus[PlayerNo].atk == 1 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK2_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 2;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK2_S;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK3_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = 0;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)BS_ATK3_S;
							}	
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK_R;
							}
							else if( PlayerNowstatus[PlayerNo].atk == 1 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK2_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 2;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK2_R;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK3_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = 0;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)BS_ATK3_R;
							}	
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( PlayerNowstatus[PlayerNo].atk == 0 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 1;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK_F;
							}
							else if( PlayerNowstatus[PlayerNo].atk == 1 ){
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK2_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].atk = 2;
									PlayerNowstatus[PlayerNo].type = INTERVAL;
								}
								NowAnime = (ANIME*)BS_ATK2_F;
							}
							else {
								if( Action( 0, OBJ_MODE0_VRAM, BS_ATK3_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) ){
									PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
									PlayerNowstatus[PlayerNo].atk = 0;
									PlayerNowstatus[PlayerNo].keep = 0;
								}
								NowAnime = (ANIME*)BS_ATK3_F;
							}	
							break;
					}
					break;
				// ************ BSアタック状態 *************E

				// ************ BSジャンプ状態 *************S
				case JUMP :	

					// ************ ジャンプ中の移動 ************S
					switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){			// 十字キー入力
						case R_U_KEY :	// 右上移動
							Hoffset += c_DivRoot2[ WALK_BEAST ];		// 歩きスピードを√2で割った値
							Voffset -= c_DivRoot2[ WALK_BEAST ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case R_D_KEY :	// 右下移動
							Hoffset += c_DivRoot2[ WALK_BEAST ];
							Voffset += c_DivRoot2[ WALK_BEAST ];
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_U_KEY :	// 左上移動
							Hoffset -= c_DivRoot2[ WALK_BEAST ];
							Voffset -= c_DivRoot2[ WALK_BEAST ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case L_D_KEY :	// 左下移動
							Hoffset -= c_DivRoot2[ WALK_BEAST ];
							Voffset += c_DivRoot2[ WALK_BEAST ];
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case R_KEY :	// 右移動
							Hoffset += WALK2_BEAST;
							PlayerNowstatus[PlayerNo].turn = TURN_R;
							break;
						case L_KEY :	// 左移動
							Hoffset -= WALK2_BEAST;
							PlayerNowstatus[PlayerNo].turn = TURN_L;
							break;
						case U_KEY :	// 上移動
							Voffset -= WALK2_BEAST;
							PlayerNowstatus[PlayerNo].turn = TURN_U;
							break;
						case D_KEY :	// 下移動
							Voffset += WALK2_BEAST;
							PlayerNowstatus[PlayerNo].turn = TURN_D;
					}
					// ************ ジャンプ中の移動 *************E

					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, BS_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
							NowAnime = (ANIME*)BS_JUMP_S;
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, BS_JUMP_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)BS_JUMP_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, BS_JUMP_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)BS_JUMP_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, BS_JUMP_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
							NowAnime = (ANIME*)BS_JUMP_F;
							break;
					}
					break;
				// ************* BSジャンプ状態 **************E

				// ************ BSスキル使用状態 *************S
				case SKILL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							NowAnime = (ANIME*)BS_SPECIAL_F;		// 攻撃力を格納する
							Skill();
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							NowAnime = (ANIME*)BS_SPECIAL_F;
							Skill();
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							NowAnime = (ANIME*)BS_SPECIAL_F;
							Skill();
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							NowAnime = (ANIME*)BS_SPECIAL_F;
							Skill();
							break;
					}
					break;
				// ************ BSスキル使用状態 *************E

				// ************ BS必殺技使用状態 *************S
				case SPECIAL :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							Special();
							break;
						case TURN_L :	// 左
							Special();
							break;
						case TURN_U :		// 上
							Special();
							break;
						case TURN_D :	// 下
							Special();
							break;
					}

					break;
				// ************ BS必殺技使用状態 *************E

				// ************  BSダメージ状態  *************S
				case DAMAGE :
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, BS_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;				// アニメーションが終了したら通常状態へ変更
								PlayerNowstatus[PlayerNo].invincible = 90;
								NowAnime = (ANIME*)BS_DAM_S;		// 攻撃力を格納する
							
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							if( Action( 0, OBJ_MODE0_VRAM, BS_DAM_S, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)BS_DAM_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, BS_DAM_R, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)BS_DAM_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							if( Action( 0, OBJ_MODE0_VRAM, BS_DAM_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime) )
								PlayerNowstatus[PlayerNo].type = STAND;
								PlayerNowstatus[PlayerNo].invincible = 90;
							NowAnime = (ANIME*)BS_DAM_F;
							break;
					}
					break;
				// ************ BSダメージ状態 *************E
				case DEAD:
					Action( 0, OBJ_MODE0_VRAM, BS_DEATH_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
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

