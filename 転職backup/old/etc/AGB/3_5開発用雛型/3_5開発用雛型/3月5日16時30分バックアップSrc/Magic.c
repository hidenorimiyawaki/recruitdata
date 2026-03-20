#include "all.h"

//**************************************************************************** S
//	  関数名		:	魔法の判定
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	
//	 最終更新日		:	2003/02/05 (水)
//**************************************************************************** E
/*
// ------- 魔法型 -------
typedef struct {
	s32			x;				// X座標
	s32			y;				// Y座標
	u8			anime;			// 魔法 アニメーションのカウンタ
	u8			cnt;			// フレームのカウンタ
	u8			status : 4;		// 魔法の発動状態
	u8			flg    : 1;		// 有無のフラグ （ONかOFF)
	u8			turn   : 3;		// 向き（8方向:3bit)
} MAGIC_EFFECT;
*/

#define	MAGIC_SPEED			2		// 魔法の移動スピード

// 
#define MG_RIGHT_OFFSET_X 	32
#define MG_RIGHT_OFFSET_Y 	16

#define MG_LEFT_OFFSET_X 	16
#define MG_LEFT_OFFSET_Y 	16

#define MG_UP_OFFSET_X 		8
#define MG_UP_OFFSET_Y 		16

#define MG_DOWN_OFFSET_X 	8
#define MG_DOWN_OFFSET_Y 	32


void Magic( void )
{
		s32	Mg_local_x;
		s32	Mg_local_y;

		// ************** 魔法が発動中の時のみ処理 ************** S
		if( PlayerMagic[0].status ){
			
			OamBuf[21].Bit32 = OAM_OBJ_ON;		// スプライト表示の準備
			OamBuf[21].Oam.Pltt = 10;
			OamBuf[21].Oam.CharNo = 96;

			// ************** 魔法状態が一段階目時のみ処理 ************** S
			if( PlayerMagic[0].status == 1){

				// ************** 魔法フラグがOFF時のみ処理を通る ************** S
				if( !PlayerMagic[0].flg ){
					// プレイヤーの向きから魔法の初期位置を設定
					switch ( PlayerNowstatus[PlayerNo].turn ){		// 方向
						case TURN_R :	// 右
							PlayerMagic[0].x = Hoffset + ( MG_RIGHT_OFFSET_X << 16 );
							PlayerMagic[0].y = Voffset + ( MG_RIGHT_OFFSET_Y << 16 );
							break;
						case TURN_L :	// 左
							PlayerMagic[0].x = Hoffset - ( MG_LEFT_OFFSET_X << 16 );
							PlayerMagic[0].y = Voffset + ( MG_LEFT_OFFSET_Y << 16 );
							break;
						case TURN_U :		// 上
							PlayerMagic[0].x = Hoffset + ( MG_UP_OFFSET_X << 16 );
							PlayerMagic[0].y = Voffset - ( MG_UP_OFFSET_Y << 16 );
							break;
						case TURN_D :	// 下
							PlayerMagic[0].x = Hoffset + ( MG_DOWN_OFFSET_X << 16 );
							PlayerMagic[0].y = Voffset + ( MG_DOWN_OFFSET_Y << 16 );
					}
					PlayerMagic[0].flg = ON;								// 魔法フラグON
					PlayerMagic[0].turn = PlayerNowstatus[PlayerNo].turn;		// プレイヤーの向きを格納
				}				//PlayerNowStartus
				// ************** 魔法フラグがOFF時のみ処理を通る ************** E

				// 魔法の移動
				switch ( PlayerMagic[0].turn ){		// 方向
					case TURN_R :	// 右
						PlayerMagic[0].x += MAGIC_SPEED << 16;
						break;
					case TURN_L :	// 左
						PlayerMagic[0].x -= MAGIC_SPEED << 16;
						break;
					case TURN_U :		// 上
						PlayerMagic[0].y -= MAGIC_SPEED << 16;
						break;
					case TURN_D :	// 下
						PlayerMagic[0].y += MAGIC_SPEED << 16;
				}
				Mg_local_x = ( PlayerMagic[0].x - Hoffset ) + (HERO_CENTER_X << 16);
				Mg_local_y = ( PlayerMagic[0].y - Voffset ) + (HERO_CENTER_Y << 16);
				

				// スプライトの表示 正常終了後次の段階へ
				if( Action( 21, OBJ_MODE0_VRAM+1024*3, MG_SHOT_S, (Mg_local_x >> 16), (Mg_local_y >> 16), &PlayerMagic[0].cnt, &PlayerMagic[0].anime) ){
					PlayerMagic[0].status = 2;
				}
				
				NowAnime = (ANIME*)MG_SHOT_S;			// 攻撃力を格納する
			}
			// ************** 魔法状態が一段階目時のみ処理 ************** E

			else {
				Mg_local_x = ( PlayerMagic[0].x - Hoffset ) + (HERO_CENTER_X << 16);
				Mg_local_y = ( PlayerMagic[0].y - Voffset ) + (HERO_CENTER_Y << 16);

				if( Action( 21, OBJ_MODE0_VRAM+1024*3, MG_SHOT_B, (Mg_local_x >> 16), (Mg_local_y >> 16), &PlayerMagic[0].cnt, &PlayerMagic[0].anime) ){
					PlayerMagic[0].status = PlayerMagic[0].flg = OFF;		// 魔法状態を初期化
					PlayerMagic[0].x = PlayerMagic[0].y = 255;				// 画面外へスプライト表示を退避
					Mg_local_x = Mg_local_y = 0;
				}
				NowAnime = (ANIME*)MG_SHOT_B;			// 攻撃力を格納する
			}
			
	}
	// ************** 魔法が発動中の時のみ処理 ************** E

	return;
}