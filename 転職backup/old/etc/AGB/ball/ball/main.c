//*****************************************************************************S
//								ミニゲーム作成
//
//								メイン関数
//	tab		4
//
//	AP-12B-132	No.51	宮脇秀則
//*********************************************************************************

//#define		NDEBUG		// リリース時に宣言します（宣言によってプリントデバッグなどを排除します）

#include	<agb.h>			// 任天堂ＡＧＢライブラリ
#include	"hard_init.h"	// 任天堂サンプルに付属のユーティリティ

//******************************* キーアサイン ************************************
#define		KEY_L		(0x0200)
#define		KEY_R		(0x0100)
#define		KEY_DOWN	(0x0080)
#define		KEY_UP		(0x0040)
#define		KEY_LEFT	(0x0020)
#define		KEY_RIGHT	(0x0010)
#define		KEY_START	(0x0008)
#define		KEY_SELECT	(0x0004)
#define		KEY_B		(0x0002)
#define		KEY_A		(0x0001)
volatile u16	nowKey, oldKey;	// キー入力用変数（キーデータがキャッシュされないようにvolatileで宣言）

//***************************** ＯＢＪキャラクタ ************************************
#include	".\graph\Player1.c"		//OBJ１取り込み
#include	".\graph\Player2.c"		//OBJ２取り込み
#include	".\graph\ball.c"		//OBJ３取り込み
#include	".\graph\out_1.c"		//OBJ３取り込み
#include	".\graph\out_2.c"		//OBJ３取り込み

typedef struct _oam_type{
	u16		attr0;					//OBJアトリビュート０用変数
	u16		attr1;					//OBJアトリビュート１用変数
	u16		attr2;					//OBJアトリビュート２用変数
}OAM_TYPE;
OAM_TYPE	oam_buffer[128];	// ＯＡＭ へ ＤＭＡ転送するためのバッファを構造体で宣言

//***************************** 関数プロトタイプ宣言 ******************************
void	KeyManager(void);			//1/60秒ごとのキー入力を記憶するためのサブ関数

//***************************** メインエントリ ******************************
int main(void)
{
  int	i;
  u16	pos_x1, pos_y1;		//OBJ1の座標指定用変数
  u16	pos_x2, pos_y2;		//OBJ2の座標指定用変数
  u16	tama_x, tama_y;		//OBJ3の座標指定用変数
  u16	x_idou=-2;			//OBJ３のX座標初期移動値をセット
  u16	y_idou=-2;			//OBJ３のY座標初期移動値をセット
  u16	sarve=0;			//初期サーブ権をセット
  u16	out1_x,out1_y;
  u16	out2_x,out2_y;
	
	ClearRamAll();	// ＲＡＭクリア（メモリへのアクセスウェイトも設定しています）
	InitVBlank();	// Vブランク初期化
	InitHardware();	// ハードウェア初期化
	
	//**************** 	DMAバッファの初期化 **************************************************
	
	for( i=0 ; i<128 ; i++ ){
		oam_buffer[i].attr0 = oam_buffer[i].attr1 = oam_buffer[i].attr2 = 0;
	}
	
	
	//**************** ＯＢＪ座標指定変数に値を代入 ******************************************
	
	pos_x1 = 25;			//OBJ1のX座標指定用変数に値を代入
	pos_y1 = 70;			//OBJ1のY座標指定用変数に値を代入
	
	pos_x2 = 200;			//OBJ2のX座標指定用変数に値を代入
	pos_y2 = 70;			//OBJ2のY座標指定用変数に値を代入
	
	tama_x = 110;			//OBJ3のX座標指定用変数に値を代入
	tama_y = 70;			//OBJ3のY座標指定用変数に値を代入
	
	out1_x = 260;
	out1_y = 60;
	
	out2_x = 260;
	out2_y = 60;
	
	//**************** ＯＢＪ表示のための準備 ************************************************
	DmaArrayCopy( 3, Player1_Palette, OBJ_PLTT, 16 );			//OBJ1のDMA転送
	DmaArrayCopy( 3, Player1_Char, OBJ_MODE0_VRAM, 16 );		//OBJ1のDMA転送

	oam_buffer[0].attr0 = OAM_SQUARE | OAM_COLOR_16 | OAM_AFFINE_NONE | OAM_MOS_OFF |pos_y1;
	oam_buffer[0].attr1 = (OAM_SIZE_16x16 >> 16)|pos_x1;
	oam_buffer[0].attr2 = 0x0000;

	//**************** ＯＢＪ表示のための準備 2**********************************************

	DmaArrayCopy( 3, Player2_Palette, OBJ_PLTT+32, 16 );		//OBJ2のDMA転送
	DmaArrayCopy( 3, Player2_Char, OBJ_MODE0_VRAM+32*4, 16 );	//OBJ2のDMA転送

	oam_buffer[1].attr0= OAM_SQUARE | OAM_COLOR_16 | OAM_AFFINE_NONE | OAM_MOS_OFF | pos_y2;
	oam_buffer[1].attr1= (OAM_SIZE_16x16 >> 16) | pos_x2;
	oam_buffer[1].attr2 = 0x1004;

	//**************** ＯＢＪ表示のための準備 3**********************************************

	DmaArrayCopy( 3, ball_Palette, OBJ_PLTT+64, 16 );			//OBJ3のDMA転送
	DmaArrayCopy( 3, ball_Char, OBJ_MODE0_VRAM+32*8, 16 );		//OBJ3のDMA転送

	oam_buffer[2].attr0= OAM_SQUARE | OAM_COLOR_16 | OAM_AFFINE_NONE | OAM_MOS_OFF | tama_y;
	oam_buffer[2].attr1= (OAM_SIZE_8x8>> 16) | tama_x;
	oam_buffer[2].attr2= 0x2008;
	
	//**************** ＯＢＪ表示のための準備 4**********************************************
	DmaArrayCopy( 3, out_1_Palette, OBJ_PLTT+80, 16 );			//OBJ4のDMA転送
	DmaArrayCopy( 3, out_1_Char, OBJ_MODE0_VRAM+32*12, 16 );		//OBJ4のDMA転送

	oam_buffer[3].attr0= OAM_SQUARE | OAM_COLOR_16 | OAM_AFFINE_NONE | OAM_MOS_OFF | out1_y;
	oam_buffer[3].attr1= (OAM_SIZE_32x32>> 16) | out1_x;
	oam_buffer[3].attr2= 0x300c;
	
	//**************** ＯＢＪ表示のための準備 5**********************************************
	DmaArrayCopy( 3, out_2_Palette, OBJ_PLTT+96, 16 );			//OBJ5のDMA転送
	DmaArrayCopy( 3, out_2_Char, OBJ_MODE0_VRAM+32*28, 16 );		//OBJ5のDMA転送

	oam_buffer[4].attr0= OAM_SQUARE | OAM_COLOR_16 | OAM_AFFINE_NONE | OAM_MOS_OFF | out2_y;
	oam_buffer[4].attr1= (OAM_SIZE_32x32>> 16) | out2_x;
	oam_buffer[4].attr2= 0x401c;
	//*****************メインループ***********************************************************
	while(1){
		if(	tama_x < 220 && tama_x > 5 )
		{
			tama_x += x_idou;
			tama_y += y_idou;
		}
		//******* キー入力によってＯＢＪ1を移動・変化させる **********************************
		
		if( nowKey & KEY_UP && pos_y1>3)		pos_y1=pos_y1-5;// 上入力
		else if( nowKey & KEY_DOWN && pos_y1<142)	pos_y1=pos_y1+5;	// 下入力
		
		
		//******* キー入力によってＯＢＪ2を移動・変化させる **********************************
		if( nowKey & KEY_A && pos_y2>4)			pos_y2=pos_y2-5;	// A入力
		else if( nowKey & KEY_B && pos_y2<140 )		pos_y2=pos_y2+5;	// B入力
		
		
		//******* ＯＢＪ3に対する、OBJ1の当たり判定 *******************
		if( pos_x1+4 > tama_x-12 && pos_y1 > tama_y-12)
		{
			if( pos_x1+4 <= tama_x+1 && pos_y1 <= tama_y+1)
			{
				x_idou=2;
			}
		}
		if( pos_x1+8 > tama_x-1 && pos_y1+16 > tama_y)
		{
			if( pos_x1+8 <= tama_x+6 && pos_y1+16 <= tama_y+7)
			{
				x_idou=2;
			}
		}
		
		
		//******* ＯＢＪ3に対する、OBJ2の当たり判定 *******************
		if( pos_x2 > tama_x-12 && pos_y2 > tama_y-12)
		{
			if( pos_x2 <= tama_x+8 && pos_y2 <= tama_y+8)
			{
				x_idou=-2;
			}
		}
		
		if( pos_x2+8 > tama_x-12 && pos_y2+16 > tama_y-12)
		{
			if( pos_x2+8 <= tama_x+8 && pos_y2+16 <= tama_y+8)
			{
				x_idou=2;
			}
		}
		//*********サーブ権に関する判定*****************************************************************
		
		if( nowKey & KEY_L && sarve==1)	//サーブ権が１PLAYER側にある状態ならばLを押せばPLAYER1に向けて発射される
		{	
			out1_x = 260;
			out1_y = 60;
			tama_x = 110;
			tama_y = 70;
			sarve =0;
			
		}
		if( nowKey & KEY_R && sarve==2)	//サーブ権が２PLAYER側にある状態ならばRを押せばPLAYER2に向けて発射される。
		{	
			out2_x = 260;
			out2_y = 60;
			tama_x = 110;
			tama_y = 70;
			sarve =0;
			
		}
		
		if(tama_x == 10)				//プレイヤー1の後ろに玉が行ってしまった場合、プレイヤー1にサーブ権が渡される。
		{
			sarve=1;
			out1_x = 100;
			out1_y = 60;	
		}
		
		if(tama_x == 210)				//プレイヤー2の後ろに玉が行ってしまった場合、プレイヤー２にサーブ権が渡される。
		{
			sarve=2;
			out2_x = 100;
			out2_y = 60;
		}
		
		
		//*********玉のY座標の上下判定*******************************************************************
		
		if(tama_y < 2)
		{
			y_idou=2;
		}
		if(tama_y > 138)
		{
			y_idou=-2;
		}
		
		
		//**********移動値をセットさせる*****************************************************************
		
		oam_buffer[0].attr0 = ((oam_buffer[0].attr0) & 0xff00) | (pos_y1 & 0x00ff);	// OBJ1のｙ移動値セット
		oam_buffer[0].attr1 = ((oam_buffer[0].attr1) & 0xfe00) | (pos_x1 & 0x01ff);	// OBJ1のｘ移動値セット
		
		oam_buffer[1].attr0 = ((oam_buffer[1].attr0) & 0xff00) | (pos_y2 & 0x00ff);	// OBJ2のｙ移動値セット
		oam_buffer[1].attr1 = ((oam_buffer[1].attr1) & 0xfe00) | (pos_x2 & 0x01ff);	// OBJ2のｘ移動値セット
		
		oam_buffer[2].attr0 = ((oam_buffer[2].attr0) & 0xff00) | (tama_y & 0x00ff);	// OBJ3のｙ移動値セット
		oam_buffer[2].attr1 = ((oam_buffer[2].attr1) & 0xfe00) | (tama_x & 0x01ff);	// OBJ3のｘ移動値セット
		
		oam_buffer[3].attr0 = ((oam_buffer[3].attr0) & 0xff00) | (out1_y & 0x00ff);	// OBJ3のｙ移動値セット
		oam_buffer[3].attr1 = ((oam_buffer[3].attr1) & 0xfe00) | (out1_x & 0x01ff);	// OBJ3のｘ移動値セット
		
		oam_buffer[4].attr0 = ((oam_buffer[4].attr0) & 0xff00) | (out2_y & 0x00ff);	// OBJ3のｙ移動値セット
		oam_buffer[4].attr1 = ((oam_buffer[4].attr1) & 0xfe00) | (out2_x & 0x01ff);	// OBJ3のｘ移動値セット
		

		V_Wait();	// V-Blank割り込みが発生し、登録関数を処理するまで待ちます
		KeyManager();
		DmaCopy(3, oam_buffer, OAM, 40, 32);			// 用意したOAMデータを OAM領域へ転送

	}
	return	0;
}
//*********************************************************E

//*********************************************************S
//						キーマネージャ
//
// フレーム毎にこの関数を呼ぶことで、キー入力状態が
// 変数 nowKey にセットされる
//
void KeyManager(void)
{
	oldKey = nowKey;							// 前回のキー内容の退避
	nowKey = (*(vu16 *)REG_KEYINPUT ^ 0x03ff);	// 今回のキー内容
}
//*********************************************************E




