#include "all.h"

//**************************************************************************** S
//	  関数名		:	プレイヤーの命中判定
//	   引数			:	無し
//	  戻り値		:	無し
//==============================================================================
//	 コメント		:	
//	 最終更新日		:	2003/02/07 (金)
//**************************************************************************** E
void Battle( void )
{
		u8	PlayerAtk = 0;
		u8	PlayerDam = 0;
		u8	EnemyAtk = 0;
		u8	EnemyDam = 0;

		u16	PlayerHP = PlayerNowstatus[PlayerNo].hp;		// 表示テスト用
		u16	EnemyHP = EnemyNowstatus[EnemyNo].hp;
		
		// ************** プレイヤーの攻撃判定 *************** S

		// 魔法攻撃か近接攻撃でそれぞれの攻撃値を格納する
		if ( PlayerMagic[0].flg ){
			PlayerAtk = (NowAnime + PlayerMagic[0].anime)->Atk;			// 攻撃範囲
			PlayerDam = (NowAnime + PlayerMagic[0].anime)->Dam;			// 攻撃力
		}else{
			PlayerAtk = (NowAnime + PlayerNowstatus[PlayerNo].anime)->Atk;						// 攻撃範囲
			PlayerDam = (NowAnime + PlayerNowstatus[PlayerNo].anime)->Dam;						// 攻撃力
		}
		
		// 攻撃判定が出ていた場合
		if ( NowAnime -> Atk ){
			// キャラ反転フラグを足しこんで攻撃範囲を反転させる
			if ( HitSquare( ATTACK[ PlayerAtk+OamBuf[0].Oam.HFlip ],ATTACK[ 1 ] ) || HitSquare2( ATTACK[ PlayerAtk ],ATTACK[ 1 ] )){
				// 近接攻撃もしくは魔法攻撃があたっていた場合の処理
				if(!( PlayerNowstatus[PlayerNo].name == MAGIC && PlayerNowstatus[PlayerNo].type == SKILL ) || !( PlayerNowstatus[PlayerNo].name == POWER && PlayerNowstatus[PlayerNo].type == SKILL )){
					EnemyNowstatus[EnemyNo].hp -= PlayerDam;		// 体力からダメージを引く
					OamBuf[EnemyNo+1].Oam.Pltt      = 0;
				}else{
					OamBuf[EnemyNo+1].Oam.Pltt   = EnemyNowstatus[EnemyNo].coloer;
				}
				if( EnemyNowstatus[EnemyNo].hp <= 0 ) {
					Coin[EnemyNo].x = EnemyNowstatus[EnemyNo].x;
					Coin[EnemyNo].y = EnemyNowstatus[EnemyNo].y;
					Coin[EnemyNo].flg = ON;
					EnemyNowstatus[EnemyNo] = ENEMY_STATUS[EnemyCnt];
					EnemyNowstatus[EnemyNo].x = (EnemyNowstatus[EnemyNo].x << 16);
					EnemyNowstatus[EnemyNo].y = (EnemyNowstatus[EnemyNo].y << 16);
					EnemyMagic[EnemyNo].status = 0;
					EnemyMagic[EnemyNo].flg = 0;
					EnemyCnt++;
					OamBuf[40 + EnemyNo].Bit32 = OAM_OBJ_OFF;
					EnemyNowstatus[EnemyNo].effect = OFF;
				}
				if(!( PlayerNowstatus[PlayerNo].name == MAGIC && PlayerNowstatus[PlayerNo].type == SKILL )){
					OamBuf[EnemyNo+1].Oam.Pltt      = 15;
					EnemyNowstatus[EnemyNo].cnt     = 0;
					EnemyNowstatus[EnemyNo].anime   = 0;
					EnemyNowstatus[EnemyNo].type    = DAMAGE;
					EnemyNowstatus[EnemyNo].effect  = ON;			// 命中エフェクトフラグON
				}
				if ( PlayerMagic[0].flg ) PlayerMagic[0].status = 2;		// 魔法攻撃の場合命中アニメーション状態へ
				if( !(EnemyNowstatus[EnemyNo].name == RAFRY)){
					if( ( EnemyNowstatus[EnemyNo].x >> 16) > ( ( PlayerNowstatus[PlayerNo].x >> 16) + HERO_CENTER_X + 10 )){
						EnemyNowstatus[EnemyNo].x += (8 << 16);
					}
					else if( ( EnemyNowstatus[EnemyNo].x >> 16) < ( ( PlayerNowstatus[PlayerNo].x >> 16) + HERO_CENTER_X - 10 )){
						EnemyNowstatus[EnemyNo].x -= (8 << 16);
					}
					else{
					}
					if( ( EnemyNowstatus[EnemyNo].y >> 16) > ( ( PlayerNowstatus[PlayerNo].y >> 16) + HERO_CENTER_Y + 10 )){
						EnemyNowstatus[EnemyNo].y += (8 << 16);
					}
					else if( ( EnemyNowstatus[EnemyNo].y >> 16) < ( ( PlayerNowstatus[PlayerNo].y >> 16) + HERO_CENTER_Y - 10 )){
						EnemyNowstatus[EnemyNo].y -= (8 << 16);
					}
					else{
					}
				}
				if( !(PlayerNowstatus[PlayerNo].type == SPECIAL) ) PlayerNowstatus[PlayerNo].sp += 5;

				if( PlayerNowstatus[PlayerNo].sp >= 100 ){
					PlayerNowstatus[PlayerNo].sp = 100;
				}

			}
		}
		// ************** プレイヤーの攻撃判定 *************** E

		// ****************** 敵の攻撃判定 ******************* S

		// 魔法攻撃か近接攻撃でそれぞれの攻撃値を格納する
		if ( EnemyMagic[EnemyNo].flg ){
			EnemyAtk = (NowAnime2 + EnemyMagic[EnemyNo].anime)->Atk;			// 攻撃範囲
			EnemyDam = (NowAnime2 + EnemyMagic[EnemyNo].anime)->Dam;			// 攻撃力
		}else {
			EnemyAtk = (NowAnime2 + EnemyNowstatus[EnemyNo].anime)->Atk;						// 攻撃範囲
			EnemyDam = (NowAnime2 + EnemyNowstatus[EnemyNo].anime)->Dam;						// 攻撃力
		}
		
		// 攻撃判定が出ていた場合
		if ( !PlayerNowstatus[PlayerNo].invincible && NowAnime2 -> Atk ){
			if(!( PlayerNowstatus[PlayerNo].name == MAGIC && PlayerNowstatus[PlayerNo].type == SKILL )){		// 体力からダメージを引く
					// キャラ反転フラグを足しこんで攻撃範囲を反転させる
				if ( HitSquare3( ATTACK[ EnemyAtk+OamBuf[EnemyNo].Oam.HFlip ],ATTACK[ 1 ] ) ){
					if((!( PlayerNowstatus[PlayerNo].name == MAGIC && PlayerNowstatus[PlayerNo].type == SKILL )) || (!( PlayerNowstatus[PlayerNo].name == BEAST && PlayerNowstatus[PlayerNo].type == SKILL ))){
						PlayerNowstatus[PlayerNo].hp -= EnemyDam;		// 体力からダメージを引く
						// 近接攻撃もしくは魔法攻撃があたっていた場合の処理
						PlayerNowstatus[PlayerNo].cnt = 0;
						PlayerNowstatus[PlayerNo].anime = 0;
						PlayerNowstatus[PlayerNo].type = DAMAGE;
						if( ( EnemyNowstatus[EnemyNo].x >> 16) > ( ( PlayerNowstatus[PlayerNo].x >> 16) + HERO_CENTER_X + 10 )){
							PlayerNowstatus[PlayerNo].x -= (8 << 16);
						}
						else if( ( EnemyNowstatus[EnemyNo].x >> 16) < ( ( PlayerNowstatus[PlayerNo].x >> 16) + HERO_CENTER_X - 10 )){
							PlayerNowstatus[PlayerNo].x += (8 << 16);
						}
						else{
						}
						if( ( EnemyNowstatus[EnemyNo].y >> 16) > ( ( PlayerNowstatus[PlayerNo].y >> 16) + HERO_CENTER_Y + 10 )){
							PlayerNowstatus[PlayerNo].y -= (8 << 16);
						}
						else if( ( EnemyNowstatus[EnemyNo].y >> 16) < ( ( PlayerNowstatus[PlayerNo].y >> 16) + HERO_CENTER_Y - 10 )){
							PlayerNowstatus[PlayerNo].y += (8 << 16);
						}
						else{
						}

//						EnemyNowstatus[EnemyNo].effect = ON;		// 命中エフェクトフラグON
					
						if ( EnemyMagic[EnemyNo].flg ) EnemyMagic[EnemyNo].status = 2;

						PlayerNowstatus[PlayerNo].coin -= 1;

						if( PlayerNowstatus[PlayerNo].coin <= 0 ){
							PlayerNowstatus[PlayerNo].coin = 0;
						}

						if ( PlayerNowstatus[PlayerNo].hp <= 0 ) {
							PlayerNowstatus[PlayerNo].dead = 90;
							PlayerNowstatus[PlayerNo].type = DEAD;
						}
					}
				}
//					OamBuf[1].Oam.Pltt = 15;
			}			// 魔法攻撃の場合命中アニメーション状態へ
		}
		
		// ****************** 敵の攻撃判定 ******************* E

		// **************** エフェクト出現処理 *************** S
		if ( EnemyNowstatus[EnemyNo].effect ) {
			OamBuf[40 + EnemyNo].Bit32 = OAM_OBJ_ON;
			OamBuf[40 + EnemyNo].Oam.Pltt = 4;
			OamBuf[40 + EnemyNo].Oam.CharNo = 32*4 + 16*4 + 16*8 + 16*EnemyNo;
			
			EnemyEffect[EnemyNo].x = ( EnemyNowstatus[EnemyNo].x - Hoffset ) >> 16;
			EnemyEffect[EnemyNo].y = ( EnemyNowstatus[EnemyNo].y - Voffset ) >> 16;
			switch ( EnemyNowstatus[0].turn ){		// 方向
				case TURN_R :	// 右
					EnemyEffect[EnemyNo].x -= ( ATTACK[EnemyAtk+OamBuf[0].Oam.HFlip ].wid / 2 );
					break;
				case TURN_L :	// 左
					EnemyEffect[EnemyNo].x += ( ATTACK[EnemyAtk+OamBuf[0].Oam.HFlip ].wid / 2 );
					break;
				case TURN_U :		// 上
					EnemyEffect[EnemyNo].y += ( ATTACK[EnemyAtk+OamBuf[0].Oam.HFlip ].hei / 2 );
					break;
				case TURN_D :	// 下
					EnemyEffect[EnemyNo].y -= ( ATTACK[EnemyAtk+OamBuf[0].Oam.HFlip ].hei / 2 );
			}
			if( Action( 40 + EnemyNo, OBJ_MODE0_VRAM+10240 + 512*(EnemyNo), EFFECT_DAMAGE  ,EnemyEffect[EnemyNo].x, EnemyEffect[EnemyNo].y, &EnemyEffect[EnemyNo].cnt, &EnemyEffect[EnemyNo].anime) ){
				OamBuf[40 + EnemyNo].Bit32 = OAM_OBJ_OFF;
				EnemyNowstatus[EnemyNo].effect = OFF;
			}
		}
		// **************** エフェクト出現処理 *************** E
		if ( SioTrg[PlayerNo] & START_BUTTON ) GameStatus = END;
		BgDataOut( PlayerAtk,  8, 1, 15, DEX, 1 );
		BgDataOut( EnemyDam,  9, 1, 15, DEX, 1 );
		BgDataOut( PlayerHP,  10, 1, 15, DEX, 1 );
		BgDataOut( EnemyHP,  11, 1, 15, DEX, 1 );

	return;
}