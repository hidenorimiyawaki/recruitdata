//*****************************************************************************S
//									実験用プログラム
//	tab		4
//	Copyright (C)	コンピュータ総合学園 HAL　AP-12B-132 No.51 宮脇 秀則
//*****************************************************************************E

//#define		NDEBUG		// リリース時に宣言します（宣言によってプリントデバッグなどを排除します）

#include	<agb.h>
#include	"hard_init.h"

#include	"all.h"
#include	".\graph\hero_data.h"
#include	".\graph\hero_pat.c"
#include	"global.c"
#include	"global.h"
//*********************************************************S
//					メインエントリ
//
// 起動・初期化後、この関数よりプログラム実行が始まります
//



void KeyManager(void);	//60分の1秒にキーを取得する関数
u8	hero_anime(const ANIME_TABLE *anime,u8 plus);	//とりあえず瞬きするプログラム
void	InitGlobal(void);

int main(void)
{
  int	i;

	ClearRamAll();	// ＲＡＭクリア（メモリへのアクセスウェイトも設定しています）
	InitVBlank();	// Vブランク初期化
	InitHardware();	// ＯＢＪ・ＢＧの設定などを行っています、詳しくは hard_init.c 参照
	InitGlobal();
	//**************** ＯＢＪ表示のための準備 *****************S
	for( i=0 ; i<128 ; i++ ){
		oam_buffer[i].attr0 = 0x0200;
		oam_buffer[i].attr1 = oam_buffer[i].attr2 = oam_buffer[i].rot_para = 0;
	}
	
	DmaArrayCopy( 3, hero_stand_1_Palette, OBJ_PLTT, 16 );
	DmaArrayCopy( 3, hero_stand_1_Char, OBJ_MODE0_VRAM, 16 );
	DmaArrayCopy( 3, hero_stand_2_Char, OBJ_MODE0_VRAM+32*16, 16 );

	oam_buffer[0].attr0 = OAM_SQUARE | OAM_COLOR_16 | OAM_AFFINE_NONE | OAM_MOS_OFF | hero.y_pos;
	oam_buffer[0].attr1 = (OAM_SIZE_32x32 >> 16) | hero.x_pos;
	oam_buffer[0].attr2 = hero.spright;


		// ＯＡＭデータを転送します
	//**************** ＯＢＪ表示のための準備 *****************E
	
	while(1){		// ←ゲームループ
		//inc = hero_anime(p_table,inc); 
		V_Wait();	// V-Blank割り込みが発生し、登録関数を処理するまで待ちます
		KeyManager();
		DmaCopy(3, oam_buffer, OAM, 32 , 32);
	}
	return	0;		// ゲームプログラムがここに来ることはありません
}
//*********************************************************E


//**********************************************************S
//				アニメーションテーブル参照
//
//
u8 hero_anime(const ANIME_TABLE *anime ,u8 plus)
{
	anime += plus;
	if(anime->v_wait == 0xeded){
		plus = 0;
		wait = 0;
		hero.spright = 0x0000;
	}
	else if(anime->v_wait == wait){
		plus++;
		wait = 0;
		hero.spright = anime->spright_no;
	}
	else{
	 wait++;
	}
	return plus;
}

//**********************************************************S
//						アニメーション
//
//

void InitGlobal(void)
{
	hero.spright = 0x0000;
	hero.x_pos = 50;
	hero.y_pos = 60;
	inc = 0;
	wait = 0;
	p_table = spright_anime00;
}

