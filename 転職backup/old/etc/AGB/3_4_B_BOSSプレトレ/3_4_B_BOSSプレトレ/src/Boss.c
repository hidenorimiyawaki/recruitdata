#include "All.h"
#include "Boss.h"

void Dragon(void);
u8 DraAction( BG_ANIME*, u8 );

enum { STAND, WALK, CLAW, FIRE, SPECIAL, DAMAGE } DraStatus;
Boss Dragon;

void Dragon( void )
{
	switch ( DraStatus )
		case STAND :
			if ( DraAction( DRA_STAND, 4 ) )
				DraStatus = WALK;
			break;
		case WALK :
			if ( DraAction( DRA_WALK, 4 ) )
				DraStatus = CLAW;
			break;
		case CLAW :
			if ( DraAction( DRA_CLAW, 4 ) )
				DraStatus = FIRE;
			break;
		case FIRE :
			if ( DraAction( DRA_FIRE, 4 ) )
				DraStatus = SPECIAL;
			break;
		case SPECIAL :
			if ( DraAction( DRA_SPECIAL, 4 ) )
				DraStatus = DAMAGE;
			break;
		case DAMAGE :
			if ( DraAction( DRA_DAMAGE, 4 ) )
				DraStatus = STAND;
			break;
		default :
			DraStatus = STAND;
			break;
	}

	return;
}




u8	DraAction( BG_ANIME* Srcp, u8 bg )
{
	vu8*	CharDestp;
	vu16*	MapDestp;

	CharDestp = (vu16 *)( ( (*(vu16 *)(REG_BG0CNT + bg*2) & BG_CHAR_BASE_MASK  ) << 13 ) + BG_VRAM );
	MapDestp  = (vu16 *)( ( (*(vu16 *)(REG_BG0CNT + bg*2) & BG_SCREEN_BASE_MASK) <<  3 ) + BG_VRAM );

	ClearMapData( bg );
	CpuCopy( (Srcp+Dragon.Anm)->pChar, CharDestp, (Srcp+Dragon.Anm)->CharSize, 16 );
	CpuCopy( (Srcp+Dragon.Anm)->pMap,  MapDestp,  (Srcp+Dragon.Anm)->MapSize,  16 );

	// ======= グラフィックの更新 ======= S
	if ( (Srcp + Dragon.Anm)->Frame ){
		if ( (Srcp + Dragon.Anm)->Frame == Dragon.Cnt ){
			Dragon.Anm++;
			Dragon.Cnt = 0;
		}
		Dragon.Cnt++;
	}
	if ((Srcp+Dragon.Anm)->pChar == NULL ){	// 終端データ
		Dragon.Anm = Dragon.Cnt = 0;	// カウンタの初期化
		return 1;	// 正常終了なら1を返す
	}
	else{
		return 0;	// アニメーションの途中なら0を返す
	}
	// ======= グラフィックの更新 ======= E
}