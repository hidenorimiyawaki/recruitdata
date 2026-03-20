#include "all.h"

//*****************************************************************************S
//	  関数名	:	アクション
//	   機能		:	その時に応じたアニメーションをする
//	  引数 1	:	スプライトナンバー  0～127
//	  引数 2	:	データ転送先のVRAMアドレス
//	  引数 3	:	アニメーションデータ構造体の戦闘アドレス
//	  引数 4	:	スプライトのX座標
//	  引数 5	:	スプライトのY座標
//	  戻り値	:	アニメーションを最後まで行うと1、途中なら0
//	 主要変数	:	アニメーションパターンを格納した二つの引数（配列）
//==============================================================================
//	 コメント	:	水平反転時の表示位置調整も並行で処理
// 最終更新日時 :	2002/08/15 (Thu)
//*****************************************************************************E
u8 Action( u8 obj_no, u32 destp, const ANIME *AnimeTag, u16 obj_h, u16 obj_v, u8 *cnt, u8 *anm)
{
	//*cnt	フレームのカウンタ
	//*ane	アニメーションのカウンタ
	
	OamBuf[obj_no].Oam.Shape = (AnimeTag + *anm)->Size >> 4;		// 形の決定
	OamBuf[obj_no].Oam.Size  = (AnimeTag + *anm)->Size & 0x03;	// サイズの決定

	// ----- DMAコピーによる転送サイズの分岐 ----- S
	switch ( (AnimeTag + *anm)->Size ){
		case SIZE8x8 :
			DmaCopy( 3, (AnimeTag + *anm)->Char, destp, 32, 16 );
			break;
		case SIZE16x8 :
		case SIZE8x16 :
			DmaCopy( 3, (AnimeTag + *anm)->Char, destp, 64, 16 );
			break;
		case SIZE16x16 :
		case SIZE32x8 :
		case SIZE8x32 :
			DmaCopy( 3, (AnimeTag + *anm)->Char, destp, 128, 16 );
			break;
		case SIZE32x16 :
		case SIZE16x32 :
			DmaCopy( 3, (AnimeTag + *anm)->Char, destp, 256, 16 );
			break;
		case SIZE32x32 :
			DmaCopy( 3, (AnimeTag + *anm)->Char, destp, 512, 16 );
			break;
		case SIZE64x32 :
		case SIZE32x64 :
			DmaCopy( 3, (AnimeTag + *anm)->Char, destp, 1024, 16 );
			break;
		case SIZE64x64 :
			DmaCopy( 3, (AnimeTag + *anm)->Char, destp, 2048, 16 );
	}
	// ----- DMAコピーによる転送サイズの分岐 ----- E

	// ----- 表示位置調整（オフセット） ----- S
	if ( OamBuf[obj_no].Oam.HFlip ){	// 水平反転時
		switch ( (AnimeTag + *anm)->Size ){
			case SIZE16x8 :
				obj_h -= 8 + (AnimeTag + *anm)->Hofs;
				break;
			case SIZE32x8 :
			case SIZE32x16 :
				obj_h -= 16 + (AnimeTag + *anm)->Hofs;
				break;
			case SIZE64x32 :
				obj_h -= 32 + (AnimeTag + *anm)->Hofs;
				break;
			default :	// 横長の形でないなら
				obj_h -= (AnimeTag + *anm)->Hofs;	// Ｘオフセット
		}
	}
	else{								// 水平反転無効時
		obj_h += (AnimeTag + *anm)->Hofs;			// Ｘオフセット
	}
	obj_v += (AnimeTag + *anm)->Vofs;				// Ｙオフセット
	OamBuf[obj_no].Oam.HPos = obj_h;
	OamBuf[obj_no].Oam.VPos = obj_v;
	// ----- 表示位置調整（オフセット） ----- E

	// ======= グラフィックの更新 ======= S
	if ( (AnimeTag + *anm)->Frame ){
		if ( (AnimeTag + *anm)->Frame == *cnt ){
			(*anm)++;
			*cnt = 0;
		}
		(*cnt)++;
	}
	if ( (AnimeTag + *anm)->Size == 0xED ){	// 終端データ
		*anm = *cnt = 0;	// カウンタの初期化
		return 1;	// 正常終了なら1を返す
	}
	else{
		return 0;	// アニメーションの途中なら0を返す
	}
	// ======= グラフィックの更新 ======= E
}
