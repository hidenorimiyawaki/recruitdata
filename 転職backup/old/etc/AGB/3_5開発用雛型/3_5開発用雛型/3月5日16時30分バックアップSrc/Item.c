//*****************************************************************************S
//	  関数名	:	Item
//	   機能		:	アイテム関連の動きを担当
//	  戻り値	:	無し
//	 主要変数	:	無し
//==============================================================================
//	 コメント	:	
//	最終更新日	:	2003/02/24 (Mon)
//==============================================================================
#include "all.h"

void Item(void)
{			
	s32 local_x,local_y;

	local_x = Coin[EnemyNo].x - PlayerNowstatus[PlayerNo].x;
	local_y = Coin[EnemyNo].y - PlayerNowstatus[PlayerNo].y;

	if( Coin[EnemyNo].flg ){
			OamBuf[70 + EnemyNo].Bit32 = OAM_OBJ_ON;
			OamBuf[70 + EnemyNo].Oam.Pltt = 10;
			OamBuf[70 + EnemyNo].Oam.CharNo = 640+4*EnemyNo;
		if ( local_x >= -32<<16 && local_x <= 240<<16 && local_y >= -32<<16 && local_y <= 160<<16 ){
			if( Action( 70 + EnemyNo, OBJ_MODE0_VRAM + 20480 + 128*(EnemyNo), COIN_ANIME  ,local_x>>16 , local_y>>16 , &Coin[EnemyNo].cnt, &Coin[EnemyNo].anime) );
		}
		if( HitSquare5( ATTACK[ 6 ] , ATTACK[ 1 ]) ){
			PlayerNowstatus[PlayerNo].coin += 1;
			Coin[EnemyNo].flg = OFF;
			Coin[EnemyNo].x = Coin[EnemyNo].y = (1024 << 16);
		}

		if ( (Coin[EnemyNo].x >> 16) >= ( 512 - 96 ) )	Coin[EnemyNo].x = ( 512 - 128 ) << 16;
		if ( (Coin[EnemyNo].y >> 16) >= ( 512 - 96 ) )	Coin[EnemyNo].y = ( 512 - 128 ) << 16;
	
		if ( (Coin[EnemyNo].x >> 16) <= ( 0 + 96 ) )	Coin[EnemyNo].x = ( 0 + 96 ) << 16;
		if ( (Coin[EnemyNo].y >> 16) <= ( 0 + 96 ) )	Coin[EnemyNo].y = ( 0 + 96 ) << 16;
	}
}
//*****************************************************************************E
