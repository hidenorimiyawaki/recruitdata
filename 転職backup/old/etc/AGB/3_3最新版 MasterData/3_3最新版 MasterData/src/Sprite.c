//*****************************************************************************S
//	  関数名	:	SetParameter
//	   機能		:	指定した箇所に回転拡大縮小のパラメータを格納する
//	  引数1		:	u8 パラメータを格納する場所(0～31)
//	  引数2		:	u8 回転の角度(0～255 1回転を256段階に)
//	  引数3		:	f32 横方向の倍率(浮動小数点型)
//	  引数4		:	f32 縦方向の倍率(浮動小数点型)
//	  戻り値	:	無し
//	 主要変数	:	無し
//==============================================================================
//	 コメント	:	sin_tbl[]、及びマクロを使用している
//	最終更新日	:	2002/08/15 (Thu)
//==============================================================================
#include "All.h"


BOOL ObjAction( u8 No, const ANIME *pAnime )
{
	u16 ObjH = ObjBuf[No].PosX;
	u16 ObjV = ObjBuf[No].PosY;
	
	ObjBuf[No].Oam.Shape = (pAnime + ObjBuf[No].Anime)->Size >> 2;		// 形の決定
	ObjBuf[No].Oam.Size  = (pAnime + ObjBuf[No].Anime)->Size & 0x03;	// サイズの決定

	// ======= CPUコピーによる転送サイズの分岐 ======= S
	switch ( (pAnime + ObjBuf[No].Anime)->Size ){
		case SIZE8x8 :
			CpuCopy( (pAnime + ObjBuf[No].Anime)->Char, ObjBuf[No].Destp,   32, 16 );
			break;
		case SIZE16x8 :
		case SIZE8x16 :
			CpuCopy( (pAnime + ObjBuf[No].Anime)->Char, ObjBuf[No].Destp,   64, 16 );
			break;
		case SIZE16x16 :
		case SIZE32x8 :
		case SIZE8x32 :
			CpuCopy( (pAnime + ObjBuf[No].Anime)->Char, ObjBuf[No].Destp,  128, 16 );
			break;
		case SIZE32x16 :
		case SIZE16x32 :
			CpuCopy( (pAnime + ObjBuf[No].Anime)->Char, ObjBuf[No].Destp,  256, 16 );
			break;
		case SIZE32x32 :
			CpuCopy( (pAnime + ObjBuf[No].Anime)->Char, ObjBuf[No].Destp,  512, 16 );
			break;
		case SIZE64x32 :
		case SIZE32x64 :
			CpuCopy( (pAnime + ObjBuf[No].Anime)->Char, ObjBuf[No].Destp, 1024, 16 );
			break;
		case SIZE64x64 :
			CpuCopy( (pAnime + ObjBuf[No].Anime)->Char, ObjBuf[No].Destp, 2048, 16 );
			break;
		default:
	}
	// ======== CPUコピーによる転送サイズの分岐 ======= E

	// ======== 表示位置調整（オフセット） ======== S
	if ( ObjBuf[No].Oam.HFlip ){	// 水平反転時
		switch ( (pAnime + ObjBuf[No].Anime)->Size ){
			case SIZE16x8 :
				ObjH -= (pAnime + ObjBuf[No].Anime)->Hofs +  8;
				break;
			case SIZE32x8 :
			case SIZE32x16 :
				ObjH -= (pAnime + ObjBuf[No].Anime)->Hofs + 16;
				break;
			case SIZE64x32 :
				ObjH -= (pAnime + ObjBuf[No].Anime)->Hofs + 32;
				break;
			default :	// 横長の形でないなら
				ObjH -= (pAnime + ObjBuf[No].Anime)->Hofs;
		}
	}
	else {							// 水平反転無効時
		ObjH += (pAnime + ObjBuf[No].Anime)->Hofs;
	}
	ObjV += (pAnime + ObjBuf[No].Anime)->Vofs;

	ObjBuf[No].Oam.HPos = ObjH;	// Xオフセット
	ObjBuf[No].Oam.VPos = ObjV;	// Yオフセット
	// ======== 表示位置調整（オフセット） ======== E

	// ======= グラフィックの更新 ======= S
	if ( (pAnime + ObjBuf[No].Anime)->Frame ){
		if ( ObjBuf[No].Cnt == (pAnime + ObjBuf[No].Anime)->Frame ){
			ObjBuf[No].Cnt = 0;
			ObjBuf[No].Anime++;
		}
		else {
			ObjBuf[No].Cnt++;
		}
	}

	if ( (pAnime + ObjBuf[No].Anime)->Char == NULL ){	// 終端データ処理
		ObjBuf[No].Anime = ObjBuf[No].Cnt = 0;		// カウンタの初期化
		return ENABLE;					// 正常終了なら1を返す
	}
	else {
		return DISABLE;					// アニメーションの途中なら0を返す
	}
	// ======= グラフィックの更新 ======= E
}


void OamManager( void )
{
	OamData	WorkOamBuf[128];	// 一時格納OAM
	SPRITE	WorkObj;			// 一時格納スプライト管理型
	SPRITE	WorkObjBuf[128];		// 上記の配列
	int	i, j;					// ループカウンタ

	CpuFastArrayCopy( ObjBuf, WorkObjBuf );

	// 底辺座標の取得
	for ( i = 0; i <128; i++ ) {
		WorkObjBuf[i].Bottom = WorkObjBuf[i].Oam.VPos;
		switch ( *(u32 *)(WorkObjBuf + i) & (OAM_SHAPE_MASK | OAM_SIZE_MASK) ){
			case OAM_SIZE_8x8:
			case OAM_SIZE_16x8:
			case OAM_SIZE_32x8:
				WorkObjBuf[i].Bottom += 8;
				break;
			case OAM_SIZE_8x16:
			case OAM_SIZE_16x16:
			case OAM_SIZE_32x16:
				WorkObjBuf[i].Bottom += 16;
				break;
			case OAM_SIZE_8x32:
			case OAM_SIZE_16x32:
			case OAM_SIZE_32x32:
			case OAM_SIZE_64x32:
				WorkObjBuf[i].Bottom += 32;
				break;
			case OAM_SIZE_32x64:
			case OAM_SIZE_64x64:
				WorkObjBuf[i].Bottom += 64;
				break;
		}
	}

	// 表示座標によるソート
	for ( i = 128; i > 2; i-- ) {
		for ( j = 1; j > i - 1; j++ ) {
			if ( WorkObjBuf[j].Priority == WorkObjBuf[j+1].Priority ) {
				if ( WorkObjBuf[j].Bottom < WorkObjBuf[j+1].Bottom ) {
					WorkObj = WorkObjBuf[j];
					WorkObjBuf[j] = WorkObjBuf[j+1];
					WorkObjBuf[j] = WorkObj;
				}
			}
		}
	}
	for ( i = 0; i < 128; i++ ) {
		DmaCopy(3, ObjBuf, OAM, 1024 , 32);				// 用意したOAMデータを OAM領域へ転送
	}

	CpuFastArrayCopy( WorkOamBuf, OAM );	// 仮想OAMの格納
	return;
}