#include	"All.h"

u8 ObjAction( u8 No, const ANIME *pAnime )
{
	u16 ObjH = (u32)ObjBuf[No].PosX >> 16;
	u16 ObjV = (u32)ObjBuf[No].PosY >> 16;
	
	ObjBuf[No].Oam.Shape = (pAnime + ObjBuf[No].Anime)->Size >> 4;		// 形の決定
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
	SPRITE	WorkObj;			// 一時格納スプライト管理型
	SPRITE	WorkObjBuf[128];	// 上記の配列
	int	i, j;					// ループカウンタ

	CpuFastArrayCopy( ObjBuf, WorkObjBuf );

	// 底辺座標の取得
	for ( i = 0; i < 128; i++ ) {
		switch ( *(u32 *)(&WorkObjBuf[i].Oam) & (OAM_SHAPE_MASK | OAM_SIZE_MASK) ){
			case OAM_SIZE_8x8:
			case OAM_SIZE_16x8:
			case OAM_SIZE_32x8:
				WorkObjBuf[i].PosY += 8 << 16;
				break;
			case OAM_SIZE_8x16:
			case OAM_SIZE_16x16:
			case OAM_SIZE_32x16:
				WorkObjBuf[i].PosY += 16 << 16;
				break;
			case OAM_SIZE_8x32:
			case OAM_SIZE_16x32:
			case OAM_SIZE_32x32:
			case OAM_SIZE_64x32:
				WorkObjBuf[i].PosY += 32 << 16;
				break;
			case OAM_SIZE_32x64:
			case OAM_SIZE_64x64:
				WorkObjBuf[i].PosY += 64 << 16;
				break;
		}
	}
	// 表示座標によるソート
	for ( i = 128; i > 2; i-- ) {
		for ( j = 0; j < i - 1; j++ ) {
			if ( WorkObjBuf[j].Priority == WorkObjBuf[j+1].Priority ) {
				if ( WorkObjBuf[j].PosY < WorkObjBuf[j+1].PosY ) {
					WorkObj = WorkObjBuf[j];
					WorkObjBuf[j] = WorkObjBuf[j+1];
					WorkObjBuf[j+1] = WorkObj;
				}
			}
		}
	}

	for ( i = 0; i < 128; i++ )
		*((OamData *)OAM+i) = WorkObjBuf[i].Oam;

	return;
}


void ObjInit( void )
{
	int i = 0,j;
	// ランキング
	for ( j = 0; j < 4; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_RANK + VRAM_RANK_SIZE * j;
		ObjBuf[i].Priority = 1;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
		ObjBuf[i].Oam.Pltt = 12;
	}
	// 必殺技
	for ( j = 0; j < 8; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_SKILL + VRAM_SKILL_SIZE * j;
		ObjBuf[i].Priority = 2;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// 必殺技発動前エフェクト
	for ( j = 0; j < 4; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_SPECIAL + VRAM_SPECIAL_SIZE * j;
		ObjBuf[i].Priority = 3;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// プレイヤー魔法（飛び道具）
	for ( j = 0; j < 4; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_MAGIC + VRAM_MAGIC_SIZE * j;
		ObjBuf[i].Priority = 4;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// エネミー飛び道具
	for ( j = 0; j < 10; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_ENEMY_SHOT + VRAM_ENEMY_SHOT_SIZE * j;
		ObjBuf[i].Priority = 5;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// プレイヤーダメージエフェクト
	for ( j = 0; j < 4; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_PLAYER_DAMAGE + VRAM_PLAYER_DAMAGE_SIZE * j;
		ObjBuf[i].Priority = 6;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// エネミーダメージエフェクト
	for ( j = 0; j < 10; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_ENEMY_DAMAGE + VRAM_ENEMY_DAMAGE_SIZE * j;
		ObjBuf[i].Priority = 7;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// プレイヤー
	for ( j = 0; j < 4; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_PLAYER + VRAM_PLAYER_SIZE * j;
		ObjBuf[i].Priority = 8;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// エネミー
	for ( j = 0; j < 10; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_ENEMY + VRAM_ENEMY_SIZE * j;
		ObjBuf[i].Priority = 9;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// ボス
	for ( j = 0; j < 2; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_BOSS + VRAM_BOSS_SIZE * j;
		ObjBuf[i].Priority = 10;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
	// コイン
	for ( j = 0; j < 32; j++, i++ ) {
		ObjBuf[i].Destp = VRAM_COIN;
		ObjBuf[i].Priority = 11;
		ObjBuf[i].Oam.CharNo = ( ObjBuf[i].Destp - OBJ_MODE0_VRAM ) / 32;
	}
}

