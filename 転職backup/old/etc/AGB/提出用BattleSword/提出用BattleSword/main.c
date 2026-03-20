//*****************************************************************************
//						BATTLE SWORD
//		
//*****************************************************************************
//#define		NDEBUG		// リリース時に宣言します（宣言によってプリントデバッグなどを排除します）
#include	<agb.h>			// 任天堂ＡＧＢライブラリ
#include	"hard_init.h"	// 任天堂サンプルに付属のユーティリティ

//******************************* キーアサイン ********************************S
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
volatile u16	nowKey, oldKey;	// キー入力（キーデータがキャッシュされないようにvolatileで宣言）
//******************************* キーアサイン ********************************E

//******************************* ＯＢＪデータ取り込み ************************S
//-------------------------------プレイヤー右向き時----------------------------
#include	".\graph\Player1.c"		//基本位置
#include	".\graph\Player1_1.c"	//一歩目
#include	".\graph\Player1_2.c"	//二歩め
#include	".\graph\p_at1.c"		//攻撃の一番目
#include	".\graph\p_at2.c"		//攻撃の二番目
#include	".\graph\wave.c"		//プレイヤーの剣から出る波動
#include	".\graph\p_g1.c"		//防御

//-------------------------------プレイヤー左向き時------------------------------------
#include	".\graph\Player2.c"		//基本体勢
#include	".\graph\p2_at1.c"		//攻撃の一番目
#include	".\graph\p2_at2.c"		//攻撃の二番目
#include	".\graph\p_g2.c"		//防御

//-------------------------------ボスキャラ用------------------------------------
#include	".\graph\boss.c"		//ボスキャラ本体
#include	".\graph\b_fire.c"		//ボスの弾

//-------------------------------ダメージ用------------------------------------
#include	".\graph\life.c"		//LIFEの文字
#include	".\graph\ht.c"			//ハート

//-------------------------------その他------------------------------------
#include	".\graph\bg1.c"			//BG1枚目用
#include	".\graph\bg2.c"			//BG2枚目用
#include	".\graph\bg3.c"			//BG3枚目用
#include	".\graph\bg4.c"			//BG3枚目用
#include	".\graph\start.c"		//STARTの文字
#include	".\graph\push.c"		//PUSHの文字

//******************************* ＯＢＪデータ取り込み ************************E

//******************************* バッファ転送用構造体定義 ********************S
typedef struct _oam_type{
	u16		attr0;
	u16		attr1;
	u16		attr2;
}OAM_TYPE;
OAM_TYPE	oam_buffer[128];	// ＯＡＭ へ ＤＭＡ転送するためのバッファ

//******************************* バッファ転送用構造体定義 ********************E

//******************************** 変数の定義 *********************************S
//-------------------------------プレイヤー用------------------------------------
  	u16	pos_x, pos_y;		//プレイヤーキャラX,Y座標指定用変数
  	u8	jump_ok,jump_cnt;	//プレイヤージャンプ判定フラグ,ジャンプテーブル値参照用カウンタ
  	u8	ph,at;				//プレイヤー反転フラグ,攻撃中判定フラグ
  	u8	at_cnt;				//プレイヤー攻撃アニメ用カウンタ
  	u8	m_cnt;				//プレイヤー移動アニメーション用カウンタ 	
  	u16	wave_x,wave_y;		//プレイヤー攻撃時の波動のX,Y座標設定用変数
  	u8	p_dm_cnt;			//プレイヤーダメージ喰らってるカウント
  	u8	p_dmg,p_hp;			//プレイヤーダメージ中フラグ、プレイヤーキャラHP
  	u8	p_g;				//プレイヤー防御フラグ
  	
//-------------------------------ボスキャラ用------------------------------------
  	u8	cnt;				//ボスキャラ移動テーブル値参照用カウンタ
  	u16	boss_x,boss_y;		//ボスキャラX,Y座標指定用変数
	u16	b_fire_x,b_fire_y;	//ボスキャラの弾用X,Y座標指定用変数
	u16	bfp_x,bfp_y;		//弾移動値セット用変数
  	u8	hanten;				//ボスキャラ反転フラグ
  	u8	b_at;				//ボスキャラ攻撃中判定フラグ
  	u16 b_at_cnt;			//ボスキャラ攻撃用ウエイトカウンタ
  	u8	b_dm_cnt;			//ボスキャラダメージ喰らってるカウント
  	u8	b_dmg,b_hp;			//ボスキャラダメージ中フラグ、ボスキャラHP
  	u8	bfx;				//ボスの弾のX向きの移動値セット用変数（シールドで弾かれたときとノーマル時の区別をつけるためのもの）
  	
//-------------------------------その他------------------------------------
  	int	i;					//DMAバッファ転送初期化処理のカウンタ用変数
  	u8	game_mode;			//ゲームのモード判定用（OP,GAME,GAMEOVER,GAMECLEARの判定用変数）
  	u8	end_cnt;			//GAMEOVER,GAMECLEAR時のウエイト用変数
  	u8	start_cnt;			//ゲームスタート時のウエイトセット用変数
  	
//******************************** 変数の定義 *********************************E

//****************************** テーブル移動値定義 ***************************S
//-------------------------------プレイヤージャンプ用テーブル値------------------------------------
u16	jump[] = {0,14,12,10,8,6,4,4,3,2,2,0xED};		//後から修正がききやすいようにとっている。
												//(最後を99にしておくと、間を増やそうが減らそうが判定のプログラムを固定できる。)
  	
//-------------------------------ボスキャラ移動用テーブル値------------------------------------
  	u16	boss_idou_x[40] = {3,3,3,3,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,8,8,8,3,3,3,3};//X座標用
  	u16	boss_idou_y[40] = {2,2,2,3,6,6,6,8,8,8,4,4,5,5,5,5,0,0,0,0,0,0,-5,-5,-5,-5,-4,-4,-8,-8,-8,-6,-6,-6,-3,-2,-2,-2};//Y座標用
  
//****************************** テーブル移動値定義 ***************************E

//***************************** 関数プロトタイプ宣言 *****************************S
//-------------------------------プレイヤー用------------------------------------
void	p_move(void);		//プレイヤー移動用関数
void	p_at(void);			//プレイヤー攻撃用関数
void	p_jump(void);		//プレイヤージャンプ用関数
void	p_anime(void);		//プレイヤー移動アニメーション用関数
void	p_dm_pa(void);		//プレイヤーダメージパレットアニメーション用関数
void	p_dm(void);			//プレイヤーダメージ判定用関数
void	p_gd(void);			//プレイヤー防御用関数
void	p_death(void);		//プレイヤーダメージ＆死亡判定

//-------------------------------ボスキャラ用------------------------------------
void	b_move(void);		//ボスキャラ移動用関数
void	b_atack(void);		//ボスキャラ攻撃用関数
void	bf_move(void);		//ボスキャラ弾移動用関数
void	b_dm_pa(void);		//ボスキャラダメージパレットアニメーション用関数
void	b_dm(void);			//ボスキャラダメージ判定用関数
void	b_death(void);		//ボスキャラダメージ＆死亡判定

//-------------------------------その他------------------------------------
void	KeyManager(void);	//60分の1秒にキーを取得する関数
void	op(void);			//ゲームがループした時のデータ初期化用関数

//***************************** 関数プロトタイプ宣言 *****************************E

//*********************************************************S
//					メインエントリ
int main(void)
{
	ClearRamAll();			// ＲＡＭクリア（メモリへのアクセスウェイトも設定しています）
	InitVBlank();			// Vブランク初期化
	InitHardware();			// ＯＢＪ・ＢＧの設定などを行っています、詳しくは hard_init.c 参照
	
	//**************** 変数の初期化 ***************************S
	//-------------------------------プレイヤー用------------------------------------
		jump_ok = 0;		
		jump_cnt = 0;
		p_dm_cnt = 0;
		p_dmg = 0;
		p_hp = 8;
		ph = 0;
		at = 0;
		at_cnt = 0;
		wave_x = 240;
		wave_y = 0;
		pos_x = 30;
		pos_y = 120;
		p_g = 0;
		
	//-------------------------------ボスキャラ用------------------------------------
		hanten = 0;
		cnt = 0;
		boss_x = 175;
		boss_y = 20;
		b_fire_x = 240;
		b_fire_y = 0;
		bfp_x = 0;
		bfp_y = 0;
		bfx = 0;
		b_dm_cnt = 0;
		b_dmg = 0;
		b_hp = 30;
		b_at = 0;
		b_at_cnt = 0;
	
	//-------------------------------その他------------------------------------
		game_mode = 0;
		start_cnt = 0;
		end_cnt = 0;
	
	//**************** 変数の初期化 ***************************E
	
	//**************** ＯＢＪ表示のための準備 *****************S
		for( i=0 ; i<128 ; i++ ){	// ＤＭＡ転送用のバッファ初期化
			oam_buffer[i].attr0 = oam_buffer[i].attr1 = oam_buffer[i].attr2 = 0;
		}
		
	//-------------------------------プレイヤー用------------------------------------
		DmaArrayCopy( 3, Player1_Palette, OBJ_PLTT, 16 );
		DmaArrayCopy( 3, Player1_Char, OBJ_MODE0_VRAM, 16 );
		
		oam_buffer[0].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[0].attr1 = (OAM_SIZE_32x32 >> 16);
		oam_buffer[0].attr2 = 0x0000;
		
		//-------------------------------プレイヤーの弾用------------------------------------
		DmaArrayCopy( 3, wave_Palette, OBJ_PLTT+32*1, 16 );
		DmaArrayCopy( 3, wave_Char, OBJ_MODE0_VRAM+32*16, 16 );
		
		oam_buffer[1].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[1].attr1 = (OAM_SIZE_32x32 >> 16);
		oam_buffer[1].attr2 = 0x1010;	
	
	//-------------------------------ボスキャラの弾用------------------------------------
		DmaArrayCopy( 3, b_fire_Palette, OBJ_PLTT+32*2, 16 );
		DmaArrayCopy( 3, b_fire_Char, OBJ_MODE0_VRAM+32*32, 16 );
		
		oam_buffer[2].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[2].attr1 = (OAM_SIZE_16x16 >> 16);
		oam_buffer[2].attr2 = 0x2020;
		
	//-------------------------------ボスキャラ用------------------------------------
		DmaArrayCopy( 3, boss_Palette, OBJ_PLTT+32*3, 16 );
		DmaArrayCopy( 3, boss_Char, OBJ_MODE0_VRAM+32*36, 16 );
		
		oam_buffer[3].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[3].attr1 = (OAM_SIZE_64x64 >> 16);
		oam_buffer[3].attr2 = 0x3024;
		
	//-------------------------------ライフ文字用------------------------------------
		DmaArrayCopy( 3, life_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, life_Char, OBJ_MODE0_VRAM+32*100, 16 );
		
		oam_buffer[4].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[4].attr1 = (OAM_SIZE_32x32 >> 16)|0;
		oam_buffer[4].attr2 = 0x4064;
		
	//-------------------------------ライフ１用------------------------------------
	//	DmaArrayCopy( 3, ht_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*116, 16 );
		
		oam_buffer[5].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[5].attr1 = (OAM_SIZE_16x16 >> 16)|32;
		oam_buffer[5].attr2 = 0x4074;
	
	//-------------------------------ライフ２用------------------------------------
	//	DmaArrayCopy( 3, ht_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*120, 16 );
		
		oam_buffer[6].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[6].attr1 = (OAM_SIZE_16x16 >> 16)|48;
		oam_buffer[6].attr2 = 0x4078;
	
	//-------------------------------ライフ３用------------------------------------
	//	DmaArrayCopy( 3, ht_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*124, 16 );
		
		oam_buffer[7].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[7].attr1 = (OAM_SIZE_16x16 >> 16)|64;
		oam_buffer[7].attr2 = 0x407c;
		
	//-------------------------------ライフ４用------------------------------------
	//	DmaArrayCopy( 3, ht_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*128, 16 );
		
		oam_buffer[8].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[8].attr1 = (OAM_SIZE_16x16 >> 16)|80;
		oam_buffer[8].attr2 = 0x4080;
	
	//-------------------------------ライフ５用------------------------------------
	//	DmaArrayCopy( 3, ht_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*132, 16 );
		
		oam_buffer[9].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[9].attr1 = (OAM_SIZE_16x16 >> 16)|96;
		oam_buffer[9].attr2 = 0x4084;

	//-------------------------------ライフ６用------------------------------------
	//	DmaArrayCopy( 3, ht_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*136, 16 );
		
		oam_buffer[10].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[10].attr1 = (OAM_SIZE_16x16 >> 16)|112;
		oam_buffer[10].attr2 = 0x4088;
		
	//-------------------------------ライフ７用------------------------------------
	//	DmaArrayCopy( 3, ht_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*140, 16 );
		
		oam_buffer[11].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[11].attr1 = (OAM_SIZE_16x16 >> 16)|128;
		oam_buffer[11].attr2 = 0x408c;
		
	//-------------------------------start文字用------------------------------------
		DmaArrayCopy( 3, start_Palette, OBJ_PLTT+32*5, 16 );
		DmaArrayCopy( 3, start_Char, OBJ_MODE0_VRAM+32*144, 16 );
		
		oam_buffer[12].attr0 = OAM_SQUARE | OAM_COLOR_16 | 80;
		oam_buffer[12].attr1 = (OAM_SIZE_64x64 >> 16)|100;
		oam_buffer[12].attr2 = 0x4090;
	
	//**************** ＯＢＪ表示のための準備 *****************E
	
	//**************** ＢＧ表示のための準備 *****************S
	//-------------------------------BG1用------------------------------------
		*(vu16*)REG_BG0CNT = 0x1803;
		DmaArrayCopy( 3, bg1_Palette, BG_PLTT, 16);
		DmaArrayCopy( 3, bg1_Character, BG_VRAM+0x0000, 16);
		DmaArrayCopy( 3, bg1_Map, BG_VRAM+0xc000, 16 );
		
	//-------------------------------BG2用------------------------------------
		*(vu16*)REG_BG1CNT = 0x1904;
		DmaArrayCopy( 3, bg2_Palette, BG_PLTT, 16);
		DmaArrayCopy( 3, bg2_Character, BG_VRAM+0x4000, 16);
		DmaArrayCopy( 3, bg2_Map, BG_VRAM+0xc800, 16 );
	
	//**************** ＢＧ表示のための準備 *****************E
		
	while(1){			// ←ゲームループ
		
		switch(game_mode){
			case 0:													//オープニング
			
			*(vu16 *)REG_BG1CNT = 0x1904;							//BG1の場所は2枚目の位置で、配置データは25の位置です。
			DmaArrayCopy( 3, bg2_Palette, BG_PLTT, 16);				//BG1にオープニング用のBMP(bg2.c)を転送
			DmaArrayCopy( 3, bg2_Character, BG_VRAM+0x4000, 16);
			DmaArrayCopy( 3, bg2_Map, BG_VRAM+0xc800, 16 );
			
			if( oldKey & KEY_START ){}								//もしスタートキーが押しっぱなしなら何もするな。
			else if( nowKey & KEY_START ){							//そうではなくて今スタートキーが押された。
				game_mode = 1;										//ならば、ゲームを開始する。
				op();												//ついでに、変数とキャラクタを初期化
			}
			*(vu16 *)REG_DISPCNT =0x0200;							//BG1のみを使用します。
			
			break;													//処理を抜けます。
			
			case 1:													//メインゲーム中。
			*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_OBJ_CHAR_1D_MAP;	//BGの0番目とOBJを表示します。
			if(start_cnt < 60)	{									//開始から1秒以内？
				start_cnt++;										//ならば、60分の1秒加算。
				oam_buffer[12].attr0 = OAM_SQUARE | OAM_COLOR_16 | 80;		//画面中央辺りに、STARTの文字を表示。
				oam_buffer[12].attr1 = (OAM_SIZE_64x64 >> 16)|100;
			}
			else{
																	//開始から1秒経過したならばゲーム用の各処理呼び出し。
			if(b_hp != 0){
				p_move();											//プレイヤー移動
				p_at();												//プレイヤー攻撃
				p_jump();											//プレイヤージャンプ
			//	p_anime();											//プレイヤー移動アニメーション
				p_dm_pa();											//プレイヤーダメージパレットアニメーション
				p_dm();												//プレイヤーあたり判定
				p_gd();												//プレイヤーガード
				p_death();											//プレイヤー死亡＆ダメージカウンタ処理
				
				b_move();											//ボスキャラ自動移動
				b_atack();											//ボスキャラ攻撃
				b_dm_pa();											//ボスキャラパレットアニメーション
				b_dm();												//ボスキャラあたり判定
			}
				b_death();											//ボスキャラ死亡＆ダメージカウンタ処理
				
				oam_buffer[12].attr0 = OAM_SQUARE | OAM_COLOR_16 | 160;//スタートの文字を画面外へ
				oam_buffer[12].attr1 = (OAM_SIZE_64x64 >> 16)|100;
			}
			break;													//処理終了
		
			case 2:													//ゲームクリア
			end_cnt ++;												//終了してよい時間までカウンタインクリメント
			*(vu16*)REG_BG1CNT = 0x1904;							//BG1を使用いたします。
			DmaArrayCopy( 3, bg4_Palette, BG_PLTT, 16);				//BG1にゲームクリア画面を上書き
			DmaArrayCopy( 3, bg4_Character, BG_VRAM+0x4000, 16);
			DmaArrayCopy( 3, bg4_Map, BG_VRAM+0xc800, 16 );
		
			*(vu16 *)REG_DISPCNT =0x0200;							//今はBG1だけ表示してね。
			if(end_cnt ==180)game_mode = 0;							//3秒たったら、オープニング処理へいってね。
			break;
			
			case 3:
			end_cnt ++;												//終了してよい時間までカウンタインクリメント
			*(vu16*)REG_BG1CNT = 0x1904;							//BG1を使用いたします。
			DmaArrayCopy( 3, bg3_Palette, BG_PLTT, 16);				//BG1にゲームオーバー画面を上書き
			DmaArrayCopy( 3, bg3_Character, BG_VRAM+0x4000, 16);
			DmaArrayCopy( 3, bg3_Map, BG_VRAM+0xc800, 16 );
			
			*(vu16 *)REG_DISPCNT =0x0200;							//今はBG1だけ表示してね。
			if(end_cnt ==180)game_mode = 0;							//3秒たったら、オープニング処理へいってね。
			break;
			
		}
			
		//-------------------------------プレイヤー移動値セット------------------------------------
		oam_buffer[0].attr0 = ((oam_buffer[0].attr0) & 0xff00) | (pos_y & 0x00ff);	// ｙ移動値のセット
		oam_buffer[0].attr1 = ((oam_buffer[0].attr1) & 0xfe00) | (pos_x & 0x01ff);	// ｘ移動値のセット
		
		//-------------------------------プレイヤーの波動移動値セット---------------------------------
		oam_buffer[1].attr0 = ((oam_buffer[1].attr0) & 0xff00) | (wave_y & 0x00ff);	// ｙ移動値のセット
		oam_buffer[1].attr1 = ((oam_buffer[1].attr1) & 0xfe00) | (wave_x & 0x01ff);	// ｘ移動値のセット

		//-------------------------------ボスキャラの弾移動値セット---------------------------------
		oam_buffer[2].attr0 = ((oam_buffer[2].attr0) & 0xff00) | (b_fire_y & 0x00ff);	// ｙ移動値のセット
		oam_buffer[2].attr1 = ((oam_buffer[2].attr1) & 0xfe00) | (b_fire_x & 0x01ff);	// ｘ移動値のセット
		
		//-------------------------------ボスキャラ移動値セット------------------------------------
		oam_buffer[3].attr0 = ((oam_buffer[3].attr0) & 0xff00) | (boss_y & 0x00ff);	// ｙ移動値のセット
		oam_buffer[3].attr1 = ((oam_buffer[3].attr1) & 0xfe00) | (boss_x & 0x01ff);	// ｘ移動値のセット
		
		DmaCopy(3, oam_buffer, OAM, 104 , 32);		// ＯＡＭデータを転送します
		V_Wait();		// V-Blank割り込みが発生し、登録関数を処理するまで待ちます
		KeyManager();	// キー入力状況の取得
	}
	return	0;
}


//*************************************************************
//						キーマネージャ
//
// フレーム毎にこの関数を呼ぶことで、キー入力状態がセットされる
//
void KeyManager(void)
{
	oldKey = nowKey;							// 前回のキー内容の退避
	nowKey = (*(vu16 *)REG_KEYINPUT ^ 0x03ff);	// 今回のキー内容の取得
}

//*************************************************************
//						ボス自動移動
//
// フレーム毎にこの関数を呼ぶことで、ボスキャラが自動移動する。
//
void b_move(void)
{
		if(b_dmg == 0 && b_at == 0 && hanten == 0)			//ボスキャラが、左向きでダメージ受けてなくて、攻撃中ではないか？
		{													//そうならば左向きに移動開始
			boss_y += boss_idou_y[cnt];						//ボスのY座標に現在の移動テーブル値を加算
			boss_x -= boss_idou_x[cnt];						//ボスのX座標に現在の移動テーブル値を減算
			cnt++;											//移動テーブル値を加算
		}
		
		if(b_dmg == 0 && b_at ==0 && hanten == 1)			//ボスキャラが、右向きでダメージ受けてなくて、攻撃中ではないか？
		{													//そうならば右向きに移動開始
			boss_y -= boss_idou_y[cnt];						//ボスのY座標に現在の移動テーブル値を減算
			boss_x += boss_idou_x[cnt];						//ボスのX座標に現在の移動テーブル値を加算
			cnt--;											//移動テーブル値を減算
		}
		
		if(b_dmg == 0 && b_at == 0 && cnt == 39)			//カウンタがMAX（左まで行ききった）か？
		{													//そうならば
			hanten = 1;										//反転移動許可（右側へ）
			boss_y = 20;									//ボスキャラY座標初期化
			oam_buffer[3].attr1 |= 0x1000;					//ボスキャラ右向きに反転
			b_at = 1;										//ボスキャラ攻撃許可（左側版）
			b_fire_x = boss_x+55;							//弾を目の前に持ってくる（X座標用）
			b_fire_y = boss_y+40;							//弾を目の前に持ってくる（Y座標用）
		}
		
		if(b_dmg == 0 && hanten == 1 && cnt == 0)			//カウンタが初期値で、右向きか？（往復したか？）
		{
			hanten = 0;										//反転移動許可（左側へ）
			boss_y = 20;									//ボスキャラY座標初期化
			oam_buffer[3].attr1 &= ~(0x1000);				//ボスキャラ左向きに反転
			b_at = 2;										//ボスキャラ攻撃許可（右側版）
			b_fire_x = boss_x-5;							//弾を目の前に持ってくる（X座標用）
			b_fire_y = boss_y+40;							//弾を目の前に持ってくる（Y座標用）
		}
}
//*************************************************************
//						ボスの攻撃
//
// フレーム毎にこの関数を呼ぶことで、ボスキャラが攻撃をする。
// ただし、右端にいるときと、左端にいるときだけ。
//
void b_atack(void)
{	if(b_hp != 0){
	
											//ボスキャラ攻撃
		if(b_at == 1)							//ボスキャラ攻撃してもいい？（左側版）
		{										//いいならば
			if(b_at_cnt == 0)bfx = 3;
			b_at_cnt ++;						//攻撃用ウエイトインクリメント
			if(b_fire_y < 160) bf_move();		//弾が画面下を突き抜けてなければ弾移動関数呼び出し
		}
		if(b_at == 1 && b_at_cnt == 90)		//攻撃終了した？（左側版）
		{										//そうならば
			b_at = 0;							//ボスキャラ攻撃許可解除
		}

		if(b_at == 2)							//ボスキャラ攻撃してもいい？（左側版）
		{										//いいならば
			if(b_at_cnt == 90)bfx = 3;
			b_at_cnt --;						//攻撃用ウエイトデクリメント
			if(b_fire_y < 160) bf_move();		//弾が画面下を突き抜けてなければ弾移動関数呼び出し
		}
		if(b_at == 2 && b_at_cnt == 0)		//攻撃終了した？（左側版）
		{										//そうならば
			b_at = 0;							//ボスキャラ攻撃許可解除
		}
	}
}

//*************************************************************
//						ボスの弾の移動
//
// この関数を呼ぶことで、ボスキャラが出した弾が移動する。
//
void bf_move(void)
{
	if(b_at == 1){
		b_fire_x += bfx;
		b_fire_y += 3;
	}
	if(b_at == 2){
		b_fire_x -= bfx;
		b_fire_y += 3;
	}
}

//*************************************************************
//		ボスキャラダメージ判定用関数
//
// この関数を呼ぶことで、ボスキャラがダメージを受けるようになる。
// 
void b_dm(void){
	if(boss_x < wave_x+10 && boss_y < wave_y+10){
		if(boss_x+63 > wave_x+10 && boss_y+63 > wave_y+10){
			if(b_dmg == 0) b_dmg = 1;
		}
	}
}

//*************************************************************
//		ボスキャラダメージパレットアニメーション用関数
//
// この関数を呼ぶことで、ボスキャラがダメージを受けたときに、
// パレットアニメーションをする
void b_dm_pa(void){
	
	if( b_dmg == 1 )	b_dm_cnt++;
	
	if( b_dm_cnt == 4 && b_dmg == 1){
		oam_buffer[3].attr2 = 0x2024;
	}
	
	if( b_dm_cnt == 8 && b_dmg == 1){
		oam_buffer[3].attr2 = 0x3024;
	}
	
	if( b_dm_cnt == 12 && b_dmg == 1){
		oam_buffer[3].attr2 = 0x2024;
	}
	
	if( b_dm_cnt == 16 && b_dmg == 1){
		oam_buffer[3].attr2 = 0x3024;
	}
	
	if( b_dm_cnt == 20 && b_dmg == 1){
		oam_buffer[3].attr2 = 0x3024;
	}
	
	if( b_dm_cnt == 24 && b_dmg == 1){
		oam_buffer[3].attr2 = 0x3024;
		b_dm_cnt = 0;
		b_dmg = 0;
		b_hp--;
	}
	
}
//*************************************************************
//						ボス死亡関数
//
// この関数を呼ぶことで、条件がみたされているならボスが死ぬ。
// 
//
void b_death(void)
{
	if(b_hp == 0){
		boss_y += 3;
		b_fire_y = 160;
		oam_buffer[3].attr1 |= 0x2000;
		if(boss_y >=200){
			game_mode = 2;
		}
	}

}
//*************************************************************
//						プレーヤー移動
//
// フレーム毎にこの関数を呼ぶことで、プレーヤーがキー入力で移動をする。
// 
//
void p_move(void)
{											//プレイヤー移動
	if(nowKey & KEY_LEFT && p_g ==0 && p_dmg == 0){					//今、左キー押していて、さらに防御中でもダメージ中でもない？
																	//そうならば
			DmaArrayCopy( 3, Player2_Char, OBJ_MODE0_VRAM, 16 );	//キャラクター左向きにする。
			ph = 1;													//プレイヤー左向いてますとフラグに送信。
			if(pos_x >= 5){											//今左端に来てますか？
				pos_x -= 3;											//来てなかったら、左へいってね。
			}
			
		}
	
	else if(  nowKey & KEY_RIGHT  && p_g == 0 && p_dmg == 0){		//今、右キー押していて、さらに防御中でもダメージ中でもない？
																	//そうならば
			DmaArrayCopy( 3, Player1_Char, OBJ_MODE0_VRAM, 16 );	//キャラクター右向きにする。
			ph = 0;													//プレイヤー右向いてますとフラグに送信
			m_cnt++;												//移動アニメカウントインクリメント
			if(pos_x <= 200){										//右端に来てますか？
			pos_x += 3;												//来てなかったら、右へいってね。
			}
		}
		
}
//*************************************************************
//						プレーヤー移動アニメ
//
// フレーム毎にこの関数を呼ぶことで、プレーヤーがキー入力で移動をしているなら、
// 歩くアニメーションをする。（予定...）
//
void p_anime(void){
}
//*************************************************************
//						プレイヤー攻撃処理
//
// フレーム毎にこの関数を呼ぶことで、プレーヤーがキー入力で攻撃を許可しているなら、
// 攻撃する。
//		
void p_at(void)
{
	if(  oldKey & KEY_B ){}												//前に攻撃ボタン押したままなら、何もするな。
																		//（オート連射防止）
	else if(  nowKey & KEY_B && at == 0 && ph == 0 && p_g == 0 && p_dmg == 0){	//今、右向きでジャンプ以外の行動をしていない？
		at = 1;																	//ならば右向き時の攻撃を許可する。
	}
		
	else if(  nowKey & KEY_B && at == 0 && ph == 1 && p_g == 0 && p_dmg == 0){	//今、左向きでジャンプ以外の行動をしていない？
		at = 2;
	}
		
	if( at == 1 || at == 2 )	at_cnt++;
	
	if( at_cnt == 4 && ph == 0){
		DmaArrayCopy( 3, p_at1_Char, OBJ_MODE0_VRAM, 16 );
		oam_buffer[1].attr1 |= 0x1000;
		wave_x = pos_x+24;
		wave_y = pos_y;
	}
	
	if( at_cnt == 8 && ph == 0){
		DmaArrayCopy( 3, p_at2_Char, OBJ_MODE0_VRAM, 16 );
		wave_x += 8;
	}
	
	if( at_cnt == 12 && ph == 0){
		DmaArrayCopy( 3, Player1_Char, OBJ_MODE0_VRAM, 16 );
		at_cnt = 0;
		at = 0;
		wave_x = 240;
		wave_y = 0;
	}

	if( at_cnt == 4 && ph == 1){
		DmaArrayCopy( 3, p2_at1_Char, OBJ_MODE0_VRAM, 16 );
		oam_buffer[1].attr1 &= ~(0x1000);
		wave_x = pos_x-24;
		wave_y = pos_y;
	}
		
	if( at_cnt == 8 && ph == 1){
		DmaArrayCopy( 3, p2_at2_Char, OBJ_MODE0_VRAM, 16 );
		wave_x -= 8;
	}
	
	if( at_cnt == 12 && ph == 1){
		DmaArrayCopy( 3, Player2_Char, OBJ_MODE0_VRAM, 16 );
		at_cnt = 0;
		at = 0;
		wave_x = 240;
		wave_y = 0;
	}
}

//*************************************************************
//		プレイヤーダメージ判定用関数
//
// この関数を呼ぶことで、プレイヤーがダメージを受けるようになる。
// 
void p_dm(void){
	if(pos_x < b_fire_x && pos_y < b_fire_y && p_g == 0){
		if(pos_x+32 > b_fire_x && pos_y+32 > b_fire_y && p_g == 0){
			if(p_dmg == 0) p_dmg = 1;
		}
	}
	
	if(pos_x+27 < b_fire_x && pos_y+5 < b_fire_y && p_g == 1 && ph == 0 && hanten == 0 ){
		if(pos_x+32 > b_fire_x && pos_y+27 > b_fire_y && p_g == 1 && ph == 0 && hanten == 0){
			bfx = -3;
		}
	}
	
	else if(pos_x < b_fire_x && pos_y < b_fire_y && p_g == 1 && ph == 0){
			if(pos_x+32 > b_fire_x && pos_y+32 > b_fire_y && p_g == 1 && ph == 0){
				if(p_dmg == 0) p_dmg = 1;
			}
		}
	
	if(pos_x-3 < b_fire_x && pos_y+4 < b_fire_y && p_g == 1 && ph == 1 && hanten == 1){
		if(pos_x > b_fire_x && pos_y+28 > b_fire_y && p_g == 1 && ph == 1 && hanten == 1){
			bfx = -3;
		}
	}
	
	else if(pos_x < b_fire_x && pos_y < b_fire_y && p_g == 1 && ph == 1){
			if(pos_x+32 > b_fire_x && pos_y+32 > b_fire_y && p_g == 1 && ph == 1){
				if(p_dmg == 0) p_dmg = 1;
			}
		}
	
	if(pos_x < boss_x+25 && pos_y < boss_y+25){
		if(pos_x+32 > boss_x+40 && pos_y+32 > boss_y+40){
			if(p_dmg == 0) p_dmg = 1;
		}
	}
}

//*************************************************************
//		プレイヤーダメージパレットアニメーション用関数
//
// この関数を呼ぶことで、プレイヤーがダメージを受けたときに、
// パレットアニメーションをする
//
void p_dm_pa(void){
	
	if( p_dmg == 1 )	p_dm_cnt++;
	
	if( p_dm_cnt == 4 && p_dmg == 1){
		if(hanten == 1){
			pos_x += 3;
		}
		else if(hanten == 0){
			pos_x -= 3;
		}
		oam_buffer[0].attr2 = 0x8000;
	}
	
	if( p_dm_cnt == 8 && p_dmg == 1){
		if(hanten == 1){
			pos_x += 3;
		}
		else if(hanten == 0){
			pos_x -= 3;
		}
		oam_buffer[0].attr2 = 0x0000;
	}
	
	if( p_dm_cnt == 12 && p_dmg == 1){
		if(hanten == 1){
			pos_x += 3;
		}
		else if(hanten == 0){
			pos_x -= 3;
		}
		oam_buffer[0].attr2 = 0x8000;
	}
	
	if( p_dm_cnt == 16 && p_dmg == 1){
		if(hanten == 1){
			pos_x += 2;
		}
		else if(hanten == 0){
			pos_x -= 2;
		}
		oam_buffer[0].attr2 = 0x0000;
	}
	
	if( p_dm_cnt == 20 && p_dmg == 1){
		if(hanten == 1){
			pos_x += 2;
		}
		else if(hanten == 0){
			pos_x -= 2;
		}
		oam_buffer[0].attr2 = 0x8000;
	}
	
	if( p_dm_cnt == 24 && p_dmg == 1){
		oam_buffer[0].attr2 = 0x0000;
		p_dm_cnt = 0;
		p_dmg = 0;
		p_hp -= 1;

	}
	
}
//*************************************************************
//		プレイヤー防御用関数
//
// この関数を呼ぶことで、プレイヤーが盾を使い、防御することができる。
// 
//
void p_gd(void){
	if(nowKey & KEY_R && p_g == 0 && p_dmg == 0){
		p_g = 1;
		if(ph == 0){
			DmaArrayCopy( 3, p_g1_Char, OBJ_MODE0_VRAM, 16 );
		}
		
		else if(ph == 1){
			DmaArrayCopy( 3, P_g2_Char, OBJ_MODE0_VRAM, 16 );
		}
	}
	
	if(nowKey & KEY_R && p_g == 1){}
	else if(p_g == 1){
		if(ph == 0){
			DmaArrayCopy( 3, Player1_Char, OBJ_MODE0_VRAM, 16 );
			p_g = 0;
		}
		
		else if(ph == 1){
			DmaArrayCopy( 3, Player2_Char, OBJ_MODE0_VRAM, 16 );
			p_g = 0;
		}
	}
}
//******* ジャンプ処理 *************************************
void p_jump(void){
	if(  oldKey & KEY_A ){}
		
		else if(  nowKey & KEY_A && jump_ok == 0 && p_dmg == 0){
			jump_ok = 1;
			jump_cnt = 0;
		}
		
		if(jump[jump_cnt] == 0xED){
			jump_ok = 2;
			jump_cnt -= 1;
		}
		
		if(jump_ok == 1){
			pos_y -= jump[jump_cnt];
			jump_cnt++;
		}
		
		if(jump_ok == 2 && jump_cnt == 0){
			jump_ok = 0;
		}
		
		if(jump_ok == 2){
			pos_y += jump[jump_cnt];
			jump_cnt--;
		}
}

void p_death(void){
	if(p_hp == 7){
		oam_buffer[11].attr0 = 0xa0;
	}
	if(p_hp == 6){
		oam_buffer[10].attr0 = 0xa0;
	}
	if(p_hp == 5){
		oam_buffer[9].attr0 = 0xa0;
	}
	if(p_hp == 4){
		oam_buffer[8].attr0 = 0xa0;
	}
	if(p_hp == 3){
		oam_buffer[7].attr0 = 0xa0;
	}
	if(p_hp == 2){
		oam_buffer[6].attr0 = 0xa0;
	}
	if(p_hp == 1){
		oam_buffer[5].attr0 = 0xa0;
	}
	if(p_hp == 0){
		game_mode = 3;
	}
}

void op(void){
	//-------------------------------プレイヤー用------------------------------------
		jump_ok = 0;		
		jump_cnt = 0;
		p_dm_cnt = 0;
		p_dmg = 0;
		p_hp = 8;
		ph = 0;
		at = 0;
		at_cnt = 0;
		wave_x = 240;
		wave_y = 0;
		pos_x = 30;
		pos_y = 120;
		p_g = 0;
	//-------------------------------ボスキャラ用------------------------------------
		hanten = 0;
		cnt = 0;
		boss_x = 175;
		boss_y = 20;
		b_fire_x = 240;
		b_fire_y = 0;
		bfp_x = 0;
		bfp_y = 0;
		bfx = 0;
		b_dm_cnt = 0;
		b_dmg = 0;
		b_hp = 30;
		b_at = 0;
		b_at_cnt = 0;
	//-------------------------------その他------------------------------------
		start_cnt = 0;
		end_cnt = 0;
	//-------------------------------プレイヤー用------------------------------------
		DmaArrayCopy( 3, Player1_Palette, OBJ_PLTT, 16 );
		DmaArrayCopy( 3, Player1_Char, OBJ_MODE0_VRAM, 16 );
		//DmaArrayCopy( 3, p_dm_Palette, OBJ_PLTT+80, 16 );
		
		oam_buffer[0].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[0].attr1 = (OAM_SIZE_32x32 >> 16);
		oam_buffer[0].attr2 = 0x0000;
		
	//-------------------------------プレイヤーの弾用------------------------------------
		DmaArrayCopy( 3, wave_Palette, OBJ_PLTT+32*1, 16 );
		DmaArrayCopy( 3, wave_Char, OBJ_MODE0_VRAM+32*16, 16 );
		
		oam_buffer[1].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[1].attr1 = (OAM_SIZE_32x32 >> 16);
		oam_buffer[1].attr2 = 0x1010;	
	
	//-------------------------------ボスキャラの弾用------------------------------------
		DmaArrayCopy( 3, b_fire_Palette, OBJ_PLTT+32*2, 16 );
		DmaArrayCopy( 3, b_fire_Char, OBJ_MODE0_VRAM+32*32, 16 );
		
		oam_buffer[2].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[2].attr1 = (OAM_SIZE_16x16 >> 16);
		oam_buffer[2].attr2 = 0x2020;
		
	//-------------------------------ボスキャラ用------------------------------------
		DmaArrayCopy( 3, boss_Palette, OBJ_PLTT+32*3, 16 );
		DmaArrayCopy( 3, boss_Char, OBJ_MODE0_VRAM+32*36, 16 );
		
		oam_buffer[3].attr0 = OAM_SQUARE | OAM_COLOR_16 ;
		oam_buffer[3].attr1 = (OAM_SIZE_64x64 >> 16);
		oam_buffer[3].attr2 = 0x3024;
		
	//-------------------------------ライフ文字用------------------------------------
		DmaArrayCopy( 3, life_Palette, OBJ_PLTT+32*4, 16 );
		DmaArrayCopy( 3, life_Char, OBJ_MODE0_VRAM+32*100, 16 );
		
		oam_buffer[4].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[4].attr1 = (OAM_SIZE_32x32 >> 16)|0;
		oam_buffer[4].attr2 = 0x4064;
		
	//-------------------------------ライフ１用------------------------------------
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*116, 16 );
		
		oam_buffer[5].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[5].attr1 = (OAM_SIZE_16x16 >> 16)|32;
		oam_buffer[5].attr2 = 0x4074;
	
	//-------------------------------ライフ２用------------------------------------
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*120, 16 );
		
		oam_buffer[6].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[6].attr1 = (OAM_SIZE_16x16 >> 16)|48;
		oam_buffer[6].attr2 = 0x4078;
	
	//-------------------------------ライフ３用------------------------------------
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*124, 16 );
		
		oam_buffer[7].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[7].attr1 = (OAM_SIZE_16x16 >> 16)|64;
		oam_buffer[7].attr2 = 0x407c;
		
	//-------------------------------ライフ４用------------------------------------
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*128, 16 );
		
		oam_buffer[8].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[8].attr1 = (OAM_SIZE_16x16 >> 16)|80;
		oam_buffer[8].attr2 = 0x4080;
	
	//-------------------------------ライフ５用------------------------------------
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*132, 16 );
		
		oam_buffer[9].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[9].attr1 = (OAM_SIZE_16x16 >> 16)|96;
		oam_buffer[9].attr2 = 0x4084;

	//-------------------------------ライフ６用------------------------------------
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*136, 16 );
		
		oam_buffer[10].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[10].attr1 = (OAM_SIZE_16x16 >> 16)|112;
		oam_buffer[10].attr2 = 0x4088;
		
	//-------------------------------ライフ７用------------------------------------
		DmaArrayCopy( 3, ht_Char, OBJ_MODE0_VRAM+32*140, 16 );
		
		oam_buffer[11].attr0 = OAM_SQUARE | OAM_COLOR_16 | 0;
		oam_buffer[11].attr1 = (OAM_SIZE_16x16 >> 16)|128;
		oam_buffer[11].attr2 = 0x408c;
		
}		
