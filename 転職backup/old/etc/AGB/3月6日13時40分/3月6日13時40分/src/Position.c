#include "All.h"
// ******* 座標変換プログラム ******
void Position( void )
{
	int i;
	s16 CenterX, CenterY;
	CenterX = ObjBuf[OBJ_PLAYER_NO + ((SioMultiCnt *)REG_SIOCNT)->ID].PosX >> 16;
	CenterX = ObjBuf[OBJ_PLAYER_NO + ((SioMultiCnt *)REG_SIOCNT)->ID].PosY >> 16;

	// ====== スプライトの表示座標変換 ======= S
	for (  i = 0; i < OBJ_MAX; i++) {
		// 画面内に座標の納まりきるスプライト
		if (    ObjBuf[i].PosX >= (CenterX-HERO_CENTER_X)<<16 && ObjBuf[i].PosX <= (CenterX-HERO_CENTER_X+240)<<16
		     && ObjBuf[i].PosY >= (CenterY-HERO_CENTER_Y)<<16 && ObjBuf[i].PosY <= (CenterY-HERO_CENTER_Y+160)<<16 )
		{
			ObjBuf[i].Oam.HPos = (ObjBuf[i].PosX >> 16) - CenterX + HERO_CENTER_X;
			ObjBuf[i].Oam.VPos = (ObjBuf[i].PosY >> 16) - CenterY + HERO_CENTER_Y;		// 表示
		}
		// X,Y共に画面外から一部表示されるスプライト
		else if (   ObjBuf[i].PosX > (CenterX-HERO_CENTER_X-64)<<16 && ObjBuf[i].PosX < (CenterX-HERO_CENTER_X)<<16
		         && ObjBuf[i].PosY > (CenterY-HERO_CENTER_Y-64)<<16 && ObjBuf[i].PosY < (CenterY-HERO_CENTER_Y)<<16 )
		{
			ObjBuf[i].Oam.HPos = (ObjBuf[i].PosX >> 16) - CenterX + HERO_CENTER_X + 308;
			ObjBuf[i].Oam.VPos = (ObjBuf[i].PosY >> 16) - CenterY + HERO_CENTER_Y + 228;
		}
		// Xだけ画面外から一部表示されるスプライト
		else if (   ObjBuf[i].PosX > (CenterX-HERO_CENTER_X-64)<<16 && ObjBuf[i].PosX < (CenterX-HERO_CENTER_X    )<<16
		         && ObjBuf[i].PosY > (CenterY-HERO_CENTER_Y   )<<16 && ObjBuf[i].PosY < (CenterY-HERO_CENTER_Y+160)<<16 )
		{
			ObjBuf[i].Oam.HPos = (ObjBuf[i].PosX >> 16) - CenterX + HERO_CENTER_X + 308;
			ObjBuf[i].Oam.VPos = (ObjBuf[i].PosY >> 16) - CenterY + HERO_CENTER_Y;		// 表示
		}
		// Yだけ画面外から一部表示されるスプライト
		else if (   ObjBuf[i].PosX > (CenterX-HERO_CENTER_X   )<<16 && ObjBuf[i].PosX < (CenterX-HERO_CENTER_X+240)<<16
		         && ObjBuf[i].PosY > (CenterY-HERO_CENTER_Y-64)<<16 && ObjBuf[i].PosY < (CenterY-HERO_CENTER_Y    )<<16 )
		{
			ObjBuf[i].Oam.HPos = (ObjBuf[i].PosX >> 16) - CenterX + HERO_CENTER_X;
			ObjBuf[i].Oam.VPos = (ObjBuf[i].PosY >> 16) - CenterY + HERO_CENTER_Y + 228;
		}
		// 画面内に一切表示されないスプライト
		else
		{
			ObjBuf[i].Oam.AffineMode = 2;	// 非表示
		}
	}
	// ====== スプライトの表示座標変換 ======= E
	
	return;
}