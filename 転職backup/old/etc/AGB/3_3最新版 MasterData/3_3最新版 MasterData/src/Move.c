#include "all.h"

//*****************************************************************************S
//	  関数名	:	
//	   機能		:	
//	 主要変数	:	アニメーションパターンを格納した二つの引数（配列）
//==============================================================================
//	 コメント	:	
// 最終更新日時 :	
//*****************************************************************************E

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

void Move(void){
		switch ( PlayerNowstatus[PlayerNo].name ){
		// *********************** スピードタイプ **************************S
			case SPEED :
				if ( !PlayerNowstatus[PlayerNo].type == STAND ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;	// キャラが停止するのを防止
				
				// ************ SP移動状態 *************S
				switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){				// 十字キー入力
					case R_U_KEY :	// 右上移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)][(((Hoffset >> 16)+104+32)/8)] == 0x0c) ){
							Hoffset += c_DivRoot2[ WALK_SPEED ];			// 歩きスピードを√2で割った値
							Voffset -= c_DivRoot2[ WALK_SPEED ];
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;	// 入力キーが前回と違ったらアニメーション状態を最初に戻す
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_S, PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64+32)/8)][(((Hoffset >> 16)+104+32)/8)] == 0x0c) ){
							Hoffset += c_DivRoot2[ WALK_SPEED ];
							Voffset += c_DivRoot2[ WALK_SPEED ];
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_S, PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)][(((Hoffset >> 16)+104)/8)] == 0x0c) ){
							Hoffset -= c_DivRoot2[ WALK_SPEED ];
							Voffset -= c_DivRoot2[ WALK_SPEED ];
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_S, PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
					case L_D_KEY :	// 左下移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64+32)/8)][(((Hoffset >> 16)+104)/8)] == 0x0c) ){
							Hoffset -= c_DivRoot2[ WALK_SPEED ];
							Voffset += c_DivRoot2[ WALK_SPEED ];
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)+3][(((Hoffset >> 16)+104+31)/8)] == 0x0c) ){
							if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)+1][(((Hoffset >> 16)+104+31)/8)] == 0x0c) ){
								Hoffset += WALK2_SPEED;
							}
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)+3][(((Hoffset >> 16)+104)/8)] == 0x0c) ){
							if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)+1][(((Hoffset >> 16)+104)/8)] == 0x0c) ){
								Hoffset -= WALK2_SPEED;
							}
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)][(((Hoffset >> 16)+104)/8)+3] == 0x0c) ){
							if ( !( bg_woods_Wall[(((Voffset >> 16)+64)/8)][(((Hoffset >> 16)+104)/8)+1] == 0x0c) ){
								Voffset -= WALK2_SPEED;
							}
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_R,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						if ( !( bg_woods_Wall[(((Voffset >> 16)+64 + 31)/8)][(((Hoffset >> 16)+104)/8)+3] == 0x0c) ){
							if ( !( bg_woods_Wall[(((Voffset >> 16)+64 + 31)/8)][(((Hoffset >> 16)+104)/8)+1] == 0x0c) ){
								Voffset += WALK2_SPEED;
							}
						}
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, SP_WALK_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_D;
						break;
					default :		// 入力無し
						PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;			// アニメーション状態を最初に戻す
						// ************ 移動方向の維持 *************S
							switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
								case TURN_R :	// 右
									OamBuf[0].Oam.HFlip = 0;
									Action( 0, OBJ_MODE0_VRAM, SP_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
									NowAnime = (ANIME*)SP_STAND_S;
									break;
								case TURN_L :	// 左
									OamBuf[0].Oam.HFlip = 1;
									Action( 0, OBJ_MODE0_VRAM, SP_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
									NowAnime = (ANIME*)SP_STAND_S;
									break;
								case TURN_U :		// 上
									OamBuf[0].Oam.HFlip = 0;
									Action( 0, OBJ_MODE0_VRAM, SP_STAND_R ,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
									NowAnime = (ANIME*)SP_STAND_R;
									break;
								case TURN_D :	// 下
									OamBuf[0].Oam.HFlip = 0;
									Action( 0, OBJ_MODE0_VRAM, SP_STAND_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
									NowAnime = (ANIME*)SP_STAND_F;
									break;
							}
						// ************ 移動方向の維持 *************E
				}
			break;
			
			case PETIT :
				if ( !PlayerNowstatus[PlayerNo].type == STAND ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;

				// ************ PT移動状態 *************S
				switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){				// 十字キー入力
					case R_U_KEY :	// 右上移動
						Hoffset += c_DivRoot2[ WALK_PETIT ];			// 歩きスピードを√2で割った値
						Voffset -= c_DivRoot2[ WALK_PETIT ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;	// 入力キーが前回と違ったらアニメーション状態を最初に戻す
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						Hoffset += c_DivRoot2[ WALK_PETIT ];
						Voffset += c_DivRoot2[ WALK_PETIT ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						Hoffset -= c_DivRoot2[ WALK_PETIT ];
						Voffset -= c_DivRoot2[ WALK_PETIT ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						Hoffset -= c_DivRoot2[ WALK_PETIT ];
						Voffset += c_DivRoot2[ WALK_PETIT ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						Hoffset += WALK2_PETIT;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						Hoffset -= WALK2_PETIT;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						Voffset -= WALK2_PETIT;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_R,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						Voffset += WALK2_PETIT;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PT_WALK_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_D;
						break;
					default :		// 入力無し
						PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;			// アニメーション状態を最初に戻す
						// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
							case TURN_R :	// 右
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, PT_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
							case TURN_L :	// 左
								OamBuf[0].Oam.HFlip = 1;
								Action( 0, OBJ_MODE0_VRAM, PT_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
							case TURN_U :		// 上
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, PT_STAND_R ,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
							case TURN_D :	// 下
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, PT_STAND_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
						}
						// ************ 移動方向の維持 *************E
				}
				break;
				
		case MAGIC :
			if ( !PlayerNowstatus[PlayerNo].type == STAND ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
				// ************ MG移動状態 *************S
				switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){				// 十字キー入力
					case R_U_KEY :	// 右上移動
						Hoffset += c_DivRoot2[ WALK_MAGIC ];			// 歩きスピードを√2で割った値
						Voffset -= c_DivRoot2[ WALK_MAGIC ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;	// 入力キーが前回と違ったらアニメーション状態を最初に戻す
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						Hoffset += c_DivRoot2[ WALK_MAGIC ];
						Voffset += c_DivRoot2[ WALK_MAGIC ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						Hoffset -= c_DivRoot2[ WALK_MAGIC ];
						Voffset -= c_DivRoot2[ WALK_MAGIC ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						Hoffset -= c_DivRoot2[ WALK_MAGIC ];
						Voffset += c_DivRoot2[ WALK_MAGIC ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						Hoffset += WALK2_MAGIC;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						Hoffset -= WALK2_MAGIC;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						Voffset -= WALK2_MAGIC;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_R,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						Voffset += WALK2_MAGIC;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, MG_WALK_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_D;
						break;
					default :		// 入力無し
						PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;			// アニメーション状態を最初に戻す
						// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
							case TURN_R :	// 右
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, MG_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
							case TURN_L :	// 左
								OamBuf[0].Oam.HFlip = 1;
								Action( 0, OBJ_MODE0_VRAM, MG_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
							case TURN_U :		// 上
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, MG_STAND_R ,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
							case TURN_D :	// 下
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, MG_STAND_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								break;
						}
						// ************ 移動方向の維持 *************E
				}
				break;

		case POWER :
				if ( !PlayerNowstatus[PlayerNo].type == STAND ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;

				// ************ SP移動状態 *************S
				switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){				// 十字キー入力
					case R_U_KEY :	// 右上移動
						Hoffset += c_DivRoot2[ WALK_POWER ];			// 歩きスピードを√2で割った値
						Voffset -= c_DivRoot2[ WALK_POWER ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;	// 入力キーが前回と違ったらアニメーション状態を最初に戻す
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case R_D_KEY :	// 右下移動
						Hoffset += c_DivRoot2[ WALK_POWER ];
						Voffset += c_DivRoot2[ WALK_POWER ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_U_KEY :	// 左上移動
						Hoffset -= c_DivRoot2[ WALK_POWER ];
						Voffset -= c_DivRoot2[ WALK_POWER ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case L_D_KEY :	// 左下移動
						Hoffset -= c_DivRoot2[ WALK_POWER ];
						Voffset += c_DivRoot2[ WALK_POWER ];
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case R_KEY :	// 右移動
						Hoffset += WALK2_POWER;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_R;
						break;
					case L_KEY :	// 左移動
						Hoffset -= WALK2_POWER;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 1;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_L;
						break;
					case U_KEY :	// 上移動
						Voffset -= WALK2_POWER;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_R,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_U;
						break;
					case D_KEY :	// 下移動
						Voffset += WALK2_POWER;
						if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
						OamBuf[0].Oam.HFlip = 0;
						Action( 0, OBJ_MODE0_VRAM, PW_WALK_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].turn = TURN_D;
						break;
					default :		// 入力無し
						PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;			// アニメーション状態を最初に戻す
						// ************ 移動方向の維持 *************S
						switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
							case TURN_R :	// 右
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, PW_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								NowAnime = (ANIME*)PW_STAND_S;
								break;
							case TURN_L :	// 左
								OamBuf[0].Oam.HFlip = 1;
								Action( 0, OBJ_MODE0_VRAM, PW_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								NowAnime = (ANIME*)PW_STAND_S;
								break;
							case TURN_U :		// 上
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, PW_STAND_R ,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								NowAnime = (ANIME*)PW_STAND_R;
								break;
							case TURN_D :	// 下
								OamBuf[0].Oam.HFlip = 0;
								Action( 0, OBJ_MODE0_VRAM, PW_STAND_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
								NowAnime = (ANIME*)PW_STAND_F;
								break;
						}
						// ************ 移動方向の維持 *************E
				}
				break;
		case BEAST :
			if ( !PlayerNowstatus[PlayerNo].type == STAND ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;

			// ************ BS移動状態 *************S
			switch ( SioKey[PlayerNo] & PLUS_KEY_MASK ){				// 十字キー入力
				case R_U_KEY :	// 右上移動
					Hoffset += c_DivRoot2[ WALK_BEAST ];			// 歩きスピードを√2で割った値
					Voffset -= c_DivRoot2[ WALK_BEAST ];
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;	// 入力キーが前回と違ったらアニメーション状態を最初に戻す
					OamBuf[0].Oam.HFlip = 0;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_R;
					break;
				case R_D_KEY :	// 右下移動
					Hoffset += c_DivRoot2[ WALK_BEAST ];
					Voffset += c_DivRoot2[ WALK_BEAST ];
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
					OamBuf[0].Oam.HFlip = 0;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_R;
					break;
				case L_U_KEY :	// 左上移動
					Hoffset -= c_DivRoot2[ WALK_BEAST ];
					Voffset -= c_DivRoot2[ WALK_BEAST ];
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
					OamBuf[0].Oam.HFlip = 1;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_L;
					break;
				case L_D_KEY :	// 左下移動
					Hoffset -= c_DivRoot2[ WALK_BEAST ];
					Voffset += c_DivRoot2[ WALK_BEAST ];
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
					OamBuf[0].Oam.HFlip = 1;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_L;
					break;
				case R_KEY :	// 右移動
					Hoffset += WALK2_BEAST;
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
					OamBuf[0].Oam.HFlip = 0;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_R;
					break;
				case L_KEY :	// 左移動
					Hoffset -= WALK2_BEAST;
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
					OamBuf[0].Oam.HFlip = 1;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_L;
					break;
				case U_KEY :	// 上移動
					Voffset -= WALK2_BEAST;
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
					OamBuf[0].Oam.HFlip = 0;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_R,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_U;
					break;
				case D_KEY :	// 下移動
					Voffset += WALK2_BEAST;
					if ( SioKey[PlayerNo] ^ SioOldKey[PlayerNo] ) PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;
					OamBuf[0].Oam.HFlip = 0;
					Action( 0, OBJ_MODE0_VRAM, BS_WALK_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
					PlayerNowstatus[PlayerNo].turn = TURN_D;
					break;
				default :		// 入力無し
					PlayerNowstatus[PlayerNo].cnt = PlayerNowstatus[PlayerNo].anime = 0;			// アニメーション状態を最初に戻す
					// ************ 移動方向の維持 *************S
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							OamBuf[0].Oam.HFlip = 0;
							Action( 0, OBJ_MODE0_VRAM, BS_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
							NowAnime = (ANIME*)BS_STAND_S;
							break;
						case TURN_L :	// 左
							OamBuf[0].Oam.HFlip = 1;
							Action( 0, OBJ_MODE0_VRAM, BS_STAND_S,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
							NowAnime = (ANIME*)BS_STAND_S;
							break;
						case TURN_U :		// 上
							OamBuf[0].Oam.HFlip = 0;
							Action( 0, OBJ_MODE0_VRAM, BS_STAND_R ,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
							NowAnime = (ANIME*)BS_STAND_R;
							break;
						case TURN_D :	// 下
							OamBuf[0].Oam.HFlip = 0;
							Action( 0, OBJ_MODE0_VRAM, BS_STAND_F,  PlayerNowstatus[PlayerNo].localX, PlayerNowstatus[PlayerNo].localY, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
							NowAnime = (ANIME*)BS_STAND_F;
							break;
					}
					// ************ 移動方向の維持 *************E
			}
			break;

		}
}




