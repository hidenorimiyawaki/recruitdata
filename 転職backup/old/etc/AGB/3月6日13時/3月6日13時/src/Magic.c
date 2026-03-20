#include "All.h"

//**************************************************************************** S
//	  関数名		:	魔法の判定
//	   引数 		:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	
//	 最終更新日		:	2003/02/05 (水)
//**************************************************************************** E


void Magic( u8 No )
{
		s32	Mg_local_x;
		s32	Mg_local_y;

		ObjBuf[OBJ_MAGIC_NO + No].Oam.Pltt = 9;

		// ************** 魔法が発動中の時のみ処理 ************** S
		if( PlayerMagic[No].status ){
			
			// ************** 魔法状態が一段階目時のみ処理 ************** S
			if( PlayerMagic[No].status == 1){

				// ************** 魔法フラグがOFF時のみ処理を通る ************** S
				if( !PlayerMagic[No].flg ){
					// プレイヤーの向きから魔法の初期位置を設定
					switch ( PlayerNowstatus[No].turn ){		// 方向
						case TURN_R :	// 右
							ObjBuf[OBJ_MAGIC_NO + No].PosX = ObjBuf[OBJ_PLAYER_NO + No].PosX + ( MG_RIGHT_OFFSET_X << 16 );
							ObjBuf[OBJ_MAGIC_NO + No].PosY = ObjBuf[OBJ_PLAYER_NO + No].PosY + ( MG_RIGHT_OFFSET_Y << 16 );
							break;
						case TURN_L :	// 左
							ObjBuf[OBJ_MAGIC_NO + No].PosX = ObjBuf[OBJ_PLAYER_NO + No].PosX - ( MG_LEFT_OFFSET_X << 16 );
							ObjBuf[OBJ_MAGIC_NO + No].PosY = ObjBuf[OBJ_PLAYER_NO + No].PosY + ( MG_LEFT_OFFSET_Y << 16 );
							break;
						case TURN_U :		// 上
							ObjBuf[OBJ_MAGIC_NO + No].PosX = ObjBuf[OBJ_PLAYER_NO + No].PosX + ( MG_UP_OFFSET_X << 16 );
							ObjBuf[OBJ_MAGIC_NO + No].PosY = ObjBuf[OBJ_PLAYER_NO + No].PosY - ( MG_UP_OFFSET_Y << 16 );
							break;
						case TURN_D :	// 下
							ObjBuf[OBJ_MAGIC_NO + No].PosX = ObjBuf[OBJ_PLAYER_NO + No].PosX + ( MG_DOWN_OFFSET_X << 16 );
							ObjBuf[OBJ_MAGIC_NO + No].PosY = ObjBuf[OBJ_PLAYER_NO + No].PosY + ( MG_DOWN_OFFSET_Y << 16 );
					}
					PlayerMagic[No].flg = ON;								// 魔法フラグON
					PlayerMagic[No].turn = PlayerNowstatus[No].turn;		// プレイヤーの向きを格納
				}				//PlayerNowStartus
				// ************** 魔法フラグがOFF時のみ処理を通る ************** E

				// 魔法の移動
				switch ( PlayerMagic[No].turn ){		// 方向
					case TURN_R :	// 右
						ObjBuf[OBJ_MAGIC_NO + No].PosX += MAGIC_SPEED << 16;
						break;
					case TURN_L :	// 左
						ObjBuf[OBJ_MAGIC_NO + No].PosX -= MAGIC_SPEED << 16;
						break;
					case TURN_U :		// 上
						ObjBuf[OBJ_MAGIC_NO + No].PosY -= MAGIC_SPEED << 16;
						break;
					case TURN_D :	// 下
						ObjBuf[OBJ_MAGIC_NO + No].PosY += MAGIC_SPEED << 16;
				}
				

				// スプライトの表示 正常終了後次の段階へ
				if( ObjAction( OBJ_MAGIC_NO + No,MG_SHOT_S ) ){
					PlayerMagic[No].status = 2;
				}
				ObjBuf[OBJ_MAGIC_NO + No].Oam.AffineMode = 0;
				NowAnime = (ANIME*)MG_SHOT_S;			// 攻撃力を格納する
			}
			// ************** 魔法状態が一段階目時のみ処理 ************** E

			else if( PlayerMagic[No].status == 2){
				if( ObjAction( OBJ_MAGIC_NO + No,MG_SHOT_B ) ){
					PlayerMagic[No].status = PlayerMagic[No].flg = OFF;		// 魔法状態を初期化
					ObjBuf[OBJ_MAGIC_NO + No].PosX = ObjBuf[OBJ_MAGIC_NO + No].PosY = 2000;				// 画面外へスプライト表示を退避
					ObjBuf[OBJ_MAGIC_NO + No].Oam.AffineMode = 2;
				}
				NowAnime = (ANIME*)MG_SHOT_B;			// 攻撃力を格納する
			}
/*			
			else {
				if( ObjAction( OBJ_MAGIC_NO + No,MG_SHOT_D ) ){
					PlayerMagic[No].status = PlayerMagic[No].flg = OFF;		// 魔法状態を初期化
					ObjBuf[OBJ_MAGIC_NO + No].PosX = ObjBuf[OBJ_MAGIC_NO + No].PosY = 2000;				// 画面外へスプライト表示を退避
					ObjBuf[OBJ_MAGIC_NO + No].Oam.AffineMode = 2;
				}
				NowAnime = (ANIME*)MG_SHOT_B;			// 攻撃力を格納する
			}
*/
	}
	// ************** 魔法が発動中の時のみ処理 ************** E

	return;
}