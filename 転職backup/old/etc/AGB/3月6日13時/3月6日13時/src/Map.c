//**************************************************************************** S
//
//	 ソース名称		:	map.c
//
//==============================================================================
//	 コメント		:	背景処理関連
//	 最終更新日		:	2002/11/29 (Fri)
//**************************************************************************** E
#include	"all.h"
#include	"map.h"

//**************************************************************************** S
//	  関数名	:	MakeMap
//	   機能		:	マップデータを精製して背景を描画する
//	  引数 1	:	描画する背景の大元のマップデータ
//	  引数 2	:	大元のマップデータの横の最大キャラクター数
//	  引数 3	:	大元のマップデータの縦の最大キャラクター数
//	  引数 4	:	使用する背景No(0～3)
//	  戻り値	:	無し
//	 主要変数	:	u16	map[MAP_CHAR_MAX][MAP_CHAR_MAX] 精製したマップデータを格納
//==============================================================================
//	 コメント	:	マップデータを精製する物であり、単純な背景描画ではない
//					BGサイズは256×256の固定
//  最終更新日	:	2002/10/18 (Fri)
//**************************************************************************** E
void MakeMap( const u16 *srcp, u16 h_max, u16 v_max, u8 bg_no )
{
	register int	i;						// ループカウンタ

	u16	read_x;								// 読み込み横位置
	u16	read_y;								// 読み込み縦位置
	u16	over_x;								// 超過縦位置
	u16	over_y;								// 超過横位置

	u16	map[MAP_CHAR_MAX][MAP_CHAR_MAX];	// 精製されるマップデータ

	u16	h_dot_max = h_max * 8;				// 大元のマップデータの横最大ドット数
	u16	v_dot_max = v_max * 8;				// 大元のマップデータの縦最大ドット数


	// ======= はみ出しているキャラクター数の割り出し ====== S
	if ( (Hoffset >> 16)%h_dot_max > h_dot_max-MAP_DOT_MAX )
		over_x = ( (Hoffset >> 16) % h_dot_max - (h_dot_max - MAP_DOT_MAX) ) >> 3;	// 横オーバー
	else
		over_x = 0;

	if ( (Voffset >> 16)%v_dot_max > v_dot_max-MAP_DOT_MAX )
		over_y = ( (Voffset >> 16) % v_dot_max - (v_dot_max - MAP_DOT_MAX) ) >> 3;	// 縦オーバー
	else
		over_y = 0;
	// ======= はみ出しているキャラクター数の割り出し ====== E

	// ======= ワールドマップから表示するマップデータの切り出し ======= S
	read_x = (Hoffset >> 16) % h_dot_max >> 3;		// 読み出し地点割り出し
	read_y = (Voffset >> 16) % v_dot_max >> 3;

	if ( over_x ){			// 横（と縦）にはみ出している
		for ( i = 0; i < MAP_CHAR_MAX - over_y; i++ ) {
			CpuCopy( srcp + (read_y+i) * h_max + read_x,
					 &map[i][0], sizeof(u16)*(MAP_CHAR_MAX-over_x), 16 );

			CpuCopy( srcp + (read_y+i)*h_max,
					 &map[i][MAP_CHAR_MAX-over_x], sizeof(u16)*over_x, 16 );
		}
		for ( ; i < MAP_CHAR_MAX; i++ ) {
			CpuCopy( srcp + (i-(MAP_CHAR_MAX-over_y)) * h_max + read_x,
					 &map[i][0], sizeof(u16)*(MAP_CHAR_MAX-over_x), 16 );

			CpuCopy( srcp + (i-(MAP_CHAR_MAX-over_y))*h_max,
					 &map[i][MAP_CHAR_MAX-over_x], sizeof(u16)*over_x, 16 );
		}
	}
	else if ( over_y ) {	// 縦のみにはみ出している
		for ( i = 0; i < MAP_CHAR_MAX - over_y; i++ ){
			CpuCopy( srcp + (read_y+i)*h_max + read_x,
					 &map[i][0], sizeof(u16)*MAP_CHAR_MAX, 16 );
		}
		for ( ; i < MAP_CHAR_MAX; i++ ) {
			CpuCopy( srcp + (i-(MAP_CHAR_MAX-over_y))*h_max + read_x,
					 &map[i][0],  sizeof(u16)*MAP_CHAR_MAX, 16 );
		}
	}
	else {				// はみ出していない
		for ( i = 0; i < MAP_CHAR_MAX; i++ ) {
			CpuCopy( srcp + (read_y+i)*h_max + read_x,
					 &map[i][0], sizeof(u16)*MAP_CHAR_MAX, 16 );
		}
	}
	// ======= ワールドマップから表示するマップデータの切り出し ======= E

	// ------ マップデータの転送 ------
	CpuArrayCopy( map,
				  (u32)(BG_VRAM + ( ( *(vu16 *)(REG_BG0CNT + bg_no*2) & BG_SCREEN_BASE_MASK ) << 3 )),
				  16 );
				// ベースブロックの値を8bit右シフト、1ブロック分の0x0800を乗算(11bit左シフト)→3bit左シフト
	return;
}


//**************************************************************************** S
//	  関数名	:	ClearMapData
//	   機能		:	マップデータを0クリアする
//	  引数		:	使用する背景No(0～3)
//	  戻り値	:	無し
//	 主要変数	:	vu16 bg_cnt BGコントロールレジスタの内容を格納
//==============================================================================
//	 コメント	:	回転拡大縮小BGには非対応
//  最終更新日	:	2002/11/29 (Fri)
//**************************************************************************** E
void ClearMapData( u8 bg_no )
{
	vu16	bg_cnt = *(vu16 *)(REG_BG0CNT + bg_no * 2);
	u16		size;

	// ------- サイズの取得 -------
	switch ( bg_cnt & BG_SCREEN_SIZE_MASK ) {
		case BG_SCREEN_SIZE_0:	// 256*256 dot
			size = 2000;
			break;
		case BG_SCREEN_SIZE_1:	// 512*256 dot
		case BG_SCREEN_SIZE_2:	// 256*512 dot
			size = 4000;
			break;
		case BG_SCREEN_SIZE_3:	// 512*512 dot
			size = 8000;
			break;
		default:	// 上記4パターン以外は存在しない
	}

	// ------ 0クリア ------
	CpuClear( 0, BG_VRAM + ((bg_cnt & BG_SCREEN_BASE_MASK) << 3),
			  size, 32 );

	return;
}