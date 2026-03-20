//*****************************************************************************S
//									メイン関数
//	tab		4
//	Copyright (C)	コンピュータ総合学園 HAL
//*****************************************************************************E
//#define		NDEBUG		// リリース時に宣言します（宣言によってプリントデバッグなどを排除します）
//	 コメント		:	メイン関数
//	 最終更新日		:	2002/10/18 (Fri)

#include	"all.h"			// 自作ヘッダ
#define		TITLE_SPEED_X		100
#define		TITLE_SPEED_Y		74
#define		TITLE_PETIT_X		80
#define		TITLE_PETIT_Y		72
#define		TITLE_MAGIC_X		132
#define		TITLE_MAGIC_Y		74
#define		TITLE_BEAST_X		164
#define		TITLE_BEAST_Y		74
#define		TITLE_POWER_X		150
#define		TITLE_POWER_Y		70

int main(void)
{


	register u16	i;	// ループ変数

	s8	select = 0;
	
	// 表示テスト用
	u16 tempX, tempY;
	u16	tmp;
	u16 temp;
	u16 COIN;
	tmp = PlayerNowstatus[PlayerNo].keep = 0;

	// ***** ハードウェア初期化 ***** S
	ClearRamAll();	// RAMクリア（メモリへのアクセスウェイトも設定）
	InitVBlank();	// Vブランク初期化
	InitHardware();	// OBJ・BGの設定など (hard_init.c 参照)
	// ***** ハードウェア初期化 ***** E

	SetAll();

	// ======= BG表示のための準備 ======= E	
	while (1){	// ゲームループ
		StringNo = OBJ_MAX - 1;						// 最大スプライトNoの格納
		for ( i = 0; i < OBJ_MAX; i++ ){			// 以下4行は表示桁数が減る時に0が残るのを回避しているらしい
			OamBuf[i].Bit32 = OAM_OBJ_OFF;			// スプライトを非表示に
		}

		SioKey[PlayerNo] = *(vu16 *)REG_KEYINPUT ^ ALL_KEY_MASK;		// キー入力情報取得
		SioTrg[PlayerNo] = SioKey[PlayerNo] & (BackKey[PlayerNo] ^ SioKey[PlayerNo]);						// 1ループだけの入力データ
		BackKey[PlayerNo] = SioKey[PlayerNo];									// SioKey[PlayerNo]と同じ
		

		switch ( GameStatus ){
			case START :
				*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_BG2_ON | DISP_BG3_ON| DISP_OBJ_CHAR_1D_MAP;

				// 背景表示

				DmaArrayCopy( 3, title_ground_bg_Character, BG_VRAM , 16);	// 0番
				DmaArrayCopy( 3, title_ground_bg_Palette,   BG_PLTT , 16);		// 
				*(vu16 *)REG_BG0CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0 | \
									  23 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;

				DmaArrayCopy( 3, title_cloud_bg_Character,  BG_VRAM + 0x4000, 16);	// 2番
				DmaArrayCopy( 3, title_cloud_bg_Palette,    BG_PLTT + 32*1,   16);	// 
				*(vu16 *)REG_BG2CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_2 | \
									  15 << BG_SCREEN_BASE_SHIFT | 1 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;

				DmaArrayCopy( 3, title_16_bg_Character,     BG_VRAM + 0x8000, 16);		// 3番
				DmaArrayCopy( 3, title_16_bg_Palette,       BG_PLTT + 32*2,   16);	// 
				*(vu16 *)REG_BG3CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_3 | \
									  7  << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;


				ClearMapData( 1 );							// 文字用

				ClearMapData( 0 );
				MakeMap( &title_ground_bg_Map, 32, 32, 0 );				// BG0 崖
		
				ClearMapData( 2 );
				MakeMap( &title_cloud_bg_Map,  32, 32, 2 );				// BG2 雲

				ClearMapData( 3 );
				MakeMap( &title_16_bg_Map,     32, 32, 3 );				// BG3 遠景




				// 立ち絵表示
				for ( i=0; i<5; i++ ){
					OamBuf[i].Bit32  = OAM_OBJ_ON;
					OamBuf[i].Oam.Pltt   = 0;
					OamBuf[i].Oam.CharNo = 64 * i;
				}
				OamBuf[3].Oam.Pltt   = 1;	// ビースト
				OamBuf[4].Oam.Pltt   = 2;	// パワー
				Action( 0, OBJ_MODE0_VRAM+2048*0, TITLE_SPEED, TITLE_SPEED_X, TITLE_SPEED_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
				Action( 1, OBJ_MODE0_VRAM+2048*1, TITLE_PETIT, TITLE_PETIT_X, TITLE_PETIT_Y, &PlayerNowstatus[1].cnt, &PlayerNowstatus[1].anime);
				Action( 2, OBJ_MODE0_VRAM+2048*2, TITLE_MAGIC, TITLE_MAGIC_X, TITLE_MAGIC_Y, &PlayerNowstatus[2].cnt, &PlayerNowstatus[2].anime);
				Action( 3, OBJ_MODE0_VRAM+2048*3, TITLE_BEAST, TITLE_BEAST_X, TITLE_BEAST_Y, &PlayerNowstatus[3].cnt, &PlayerNowstatus[3].anime);
				Action( 4, OBJ_MODE0_VRAM+2048*4, TITLE_POWER, TITLE_POWER_X, TITLE_POWER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);

				// スタートボタンでキャラセレへ
				if ( SioTrg[PlayerNo] & A_BUTTON ){
					GameStatus = C_SELECT;
					ClearMapData( 0 );
				}
				break;
			case C_SELECT :
				*(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON | DISP_BG1_ON | DISP_OBJ_CHAR_1D_MAP;

				*(vu16*)REG_BG0HOFS = 0;
				*(vu16*)REG_BG0VOFS = 0;

				*(vu16*)REG_BG1HOFS = 0;
				*(vu16*)REG_BG1VOFS = 0;

				ClearMapData( 0 );
				ClearMapData( 1 );
				ClearMapData( 2 );
				ClearMapData( 3 );
				DmaArrayCopy( 3, bg_woods_main_01_Character, BG_VRAM, 16 );		// キャラクタデータ
				DmaArrayCopy( 3, bg_woods_main_01_Palette,   BG_PLTT, 16 );		// パレットデータ
				*(vu16 *)REG_BG0CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1 | 8 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;

				BgStringPrint( "CHARACTER SELECT",2,2,15,1 );
				BgStringPrint( "<      >",10,11,15,1 );
				BgStringPrint( "PUSH A BUTTON",13, 9,15,1 );
				if ( SioTrg[PlayerNo] & L_KEY )	select++;
				if ( SioTrg[PlayerNo] & R_KEY )	select--;
				if ( select >= 5 )	select = 0;
				if ( select < 0 )	select = 4;
				if ( SioTrg[PlayerNo] & A_BUTTON ){
					GameStatus = MAIN;
					ClearMapData( 1 );
				}
				OamBuf[0].Bit32  = OAM_OBJ_ON;
				OamBuf[0].Oam.CharNo =0;

				switch (select){
					case 0 : 
						OamBuf[0].Oam.Pltt = 0;
						Action( 0, OBJ_MODE0_VRAM, SP_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].name = SPEED;
						break;
					case 1 :
						OamBuf[0].Oam.Pltt = 0;
						Action( 0, OBJ_MODE0_VRAM, MG_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].name = MAGIC;
						break;
					case 2 :
						OamBuf[0].Oam.Pltt = 0;
						Action( 0, OBJ_MODE0_VRAM, PT_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].name = PETIT;
						break;
					case 3 :
						OamBuf[0].Oam.Pltt = 2;
						Action( 0, OBJ_MODE0_VRAM, PW_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].name = POWER;
						break;
					case 4 :
						OamBuf[0].Oam.Pltt = 1;
						Action( 0, OBJ_MODE0_VRAM, BS_STAND_F, HERO_CENTER_X, HERO_CENTER_Y, &PlayerNowstatus[PlayerNo].cnt, &PlayerNowstatus[PlayerNo].anime);
						PlayerNowstatus[PlayerNo].name = BEAST;
						break;
					default :
				}
				PlayerNowstatus[PlayerNo].hp = 300;
				PlayerNowstatus[PlayerNo].turn = TURN_D;

				break;
			case MAIN :
				ClearMapData( 1 );
				PlayerNowstatus[PlayerNo].x = Hoffset;
				PlayerNowstatus[PlayerNo].y = Voffset;

				OamBuf[0].Bit32 = OAM_OBJ_ON;
				OamBuf[0].Oam.CharNo = 0;

				
				if( PlayerNowstatus[PlayerNo].invincible ){
					PlayerNowstatus[PlayerNo].invincible -= 1;
				}
				if( PlayerNowstatus[PlayerNo].dead ){
					PlayerNowstatus[PlayerNo].dead -= 1;
					if( PlayerNowstatus[PlayerNo].dead == 0 ) PlayerNowstatus[PlayerNo].hp = 300;
				}


				if( ( PlayerNowstatus[PlayerNo].invincible % 2 ) == 1 ){
					OamBuf[0].Bit32  = OAM_OBJ_OFF;
				}
				else{
					OamBuf[0].Bit32  = OAM_OBJ_ON;
				}

				Hero();
				tmp = PlayerNowstatus[PlayerNo].keep;
				Magic();
				for ( EnemyNo=0; EnemyNo<ENEMY_MAX; EnemyNo++ ){		
					Enemy();
					Battle();
					Item();
					if( EnemyCnt > ENEMY_CNT_MAX ) EnemyCnt = 0;
				}

				OamBuf[24].Bit32 = OAM_OBJ_ON;
				OamBuf[24].Oam.Pltt = 10;
				OamBuf[24].Oam.CharNo = 32*4 + 32*10 + 32*4;

				Action( 24, OBJ_MODE0_VRAM+1024*18, E_BAR_PROTO, 16, 120, &PlayerNowstatus[1].cnt, &PlayerNowstatus[1].anime);
				
//				if ( (Hoffset >> 16) == 0xffff )		Hoffset = 0xffff -  15;			// 負のオーバーフロー時の処理1
//				if ( (Voffset >> 16) == 0xffff )		Voffset = 0xffff - 255;
				if ( (Hoffset >> 16) > 0xffff - 15 )	Hoffset = 0;					// 負のオーバーフロー時の処理2
				if ( (Voffset >> 16) > 0xffff - 255 )	Voffset = 0;
//				if ( !((Hoffset >> 16) > ( 1024 - 240 )) )*(vu16*)REG_BG0VOFS = (Voffset>>16) & 0x0007;	// オフセットの値は0～7まで

				// 負のオーバーフロー時の処理2
				if ( (Hoffset >> 16) >= ( 1024 - 240 ) )	Hoffset = ( 1024 - 240 ) << 16;
				if ( (Voffset >> 16) >= ( 1024 - 160 ) )	Voffset = ( 1024 - 160 ) << 16;
				*(vu16*)REG_BG0VOFS = (Voffset>>16) & 0x0007;
				*(vu16*)REG_BG0HOFS = (Hoffset>>16) & 0x0007;
				tempX = (PlayerNowstatus[PlayerNo].x>>16);
				tempY = (PlayerNowstatus[PlayerNo].y>>16);
				// ------ スプライトテスト ------
				ObjDataOut( tempX, 8, 8, 15, DEX );
				ObjDataOut( tempY, 16, 8, 15, DEX );
				COIN = PlayerNowstatus[PlayerNo].coin;

				ObjDataOut( COIN ,32,8,15,DEX );



		//		BgDataOut( Hoffset>>16, 3, 1, 15, DEX, 1 );
		//		BgDataOut( Voffset>>16, 4, 1, 15, DEX, 1 );
		//		MapOutPut( c_WorldMap, WORLD_H_CHARA_MAX, WORLD_V_CHARA_MAX, BG_VRAM+0x4000 );	

				MakeMap( bg_woods_main_01_Map, 128, 128, 0 );				// ワールドマップの描画
//				MakeMap( &c_WorldMap[0][0], WORLD_H_CHARA_MAX, WORLD_V_CHARA_MAX, 0 );				// ワールドマップの描画

//				*(vu16 *)REG_BG0CNT |= 0x0003;
//				*(vu16 *)REG_BG1CNT |= 0x0000;
				temp = PlayerNowstatus[PlayerNo].sp;
				ObjDataOut( temp ,24,8,15,DEX );
				break;
		case END :
				Hoffset = Voffset = 0;
				ClearMapData( 0 );
				ClearMapData( 1 );

				*(vu16*)REG_BG0HOFS = 0;
				*(vu16*)REG_BG0VOFS = 0;

				*(vu16 *)REG_DISPCNT = DISP_MODE_0  | DISP_BG0_ON | DISP_BG1_ON | DISP_OBJ_CHAR_1D_MAP;

				*(vu16 *)REG_BG0CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_1 | \
									  7 << BG_SCREEN_BASE_SHIFT | 0 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;
				DmaArrayCopy( 3, game_over_logo_Character, BG_VRAM, 16 );		// キャラクタデータ
				DmaArrayCopy( 3, game_over_logo_Palette,   BG_PLTT, 16 );		// パレットデータ

				MakeMap( &game_over_logo_Map, 30, 20, 0 );				// ワールドマップの描画

				BgStringPrint( "RETRY START BUTTON",13, 9,15,1 );
				if ( SioTrg[PlayerNo] & START_BUTTON ){
					SetAll();
					GameStatus = START;
					ClearMapData( 1 );
					Clear = 0;
					PlayerNowstatus[PlayerNo].type = STAND;
					PlayerNowstatus[PlayerNo].turn = TURN_D;
				}
				break;
		}
		DmaCopy(3, OamBuf, OAM, 1024 , 32);				// 用意したOAMデータを OAM領域へ転送

		V_Wait();
	}
	return	0;
}

//*****************************************************************************S
//	  関数名	:	セットオール
//	   機能		:	ハードの初期化、及びBG・OBJのセッティング
//	   引数		:	無し
//	  戻り値	:	無し
//	 主要変数	:	無し
//==============================================================================
//	 コメント	:	
// 最終更新日時 :	2003/02/19 (水)
//*****************************************************************************E
void SetAll(void)
{
	
	// ***** 表示のための準備 ***** S
	DmaArrayCopy( 3, ply_sp_Palette, OBJ_PLTT,       16 );	// No0  スピード/ プチ/ マジック
	DmaArrayCopy( 3, ply_bs_Palette, OBJ_PLTT+32*1,  16 );	// No1  ビースト
	DmaArrayCopy( 3, ply_pw_Palette, OBJ_PLTT+32*2,  16 );	// No2  パワー
	DmaArrayCopy( 3, emy_sl_Palette, OBJ_PLTT+32*3,  16 );	// No3  スライム/ ウサギ/ スシ/ ラフリー
	DmaArrayCopy( 3, emy_pz_Palette, OBJ_PLTT+32*4,  16 );	// No4  プラズマー/ ウニ/ トリ/ カエル
	DmaArrayCopy( 3, emy_kn_Palette, OBJ_PLTT+32*5,  16 );	// No5  キノコ/ 蝙蝠
	DmaArrayCopy( 3, emy_go_Palette, OBJ_PLTT+32*6,  16 );	// No6  ゴースト/ ドム/ サソリ
	DmaArrayCopy( 3, eft_mg_Palette, OBJ_PLTT+32*10, 16 );	// No10 魔法エフェクト
	DmaArrayCopy( 3, eft_sp_Palette, OBJ_PLTT+32*11, 16 );	// No11 魔法エフェクト

	DmaArrayCopy( 3, start_logo_Palette, OBJ_PLTT+32*14, 16 );	// No11 魔法エフェクト
	DmaArrayCopy( 3, system_Palette,     OBJ_PLTT+32*15, 16 );	// No15 白文字

	DmaArrayCopy( 3, system_Char,	 OBJ_MODE0_VRAM + 0x7000, 16 );		// 文字フォントデータを末尾に

	// フォントデータ	BG1
	DmaArrayCopy( 3, system_Char,      BG_VRAM+0xC000, 16 );		// 3番 キャラクターデータベースブロック
	DmaArrayCopy( 3, system_Palette,   BG_PLTT+32*15,  16 );		// パレットデータ
	*(vu16 *)REG_BG1CNT = BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0 | 31 << BG_SCREEN_BASE_SHIFT | 3 << BG_CHAR_BASE_SHIFT | BG_MOS_OFF;


	// ***** 表示のための準備 ***** E

	// ***** 初期設定 ***** S
	ClearMapData( 3 );

	GameStatus = START;						// ゲームステータスを初期状態に
	PlayerNowstatus[PlayerNo].type = STAND;						// プレイヤーステータスを初期状態に
	PlayerNowstatus[PlayerNo].turn = TURN_D;	// プレイヤーの向きを正面に
	PlayerNowstatus[PlayerNo].name = SPEED;						// プレイヤー選択画面のデフォルト（スピード）

	PlayerMagic[0].status = 0;				// 魔法状態初期化
	PlayerMagic[0].flg    = OFF;
	PlayerNowstatus[PlayerNo].invincible =	PlayerNowstatus[PlayerNo].dead = PlayerNowstatus[PlayerNo].coin = 0;
	PlayerNowstatus[PlayerNo].sp = 100;

	Voffset = Hoffset = 0;	// ワールド座標の初期化
	PlayerNowstatus[PlayerNo].localX = 104;
	PlayerNowstatus[PlayerNo].localY = 64;
	EnemyCnt = 4;
	Clear = 0;
	PlayerNowstatus[PlayerNo].skillflg = 0;
	PlayerNowstatus[PlayerNo].atk = 0;
	SpBgCnt = 0;
	EnemyNo = 0;
	for ( EnemyNo=0; EnemyNo<ENEMY_MAX; EnemyNo++ ){
		EnemyNowstatus[EnemyNo] = ENEMY_STATUS[EnemyNo];
		EnemyNowstatus[EnemyNo].x = (EnemyNowstatus[EnemyNo].x << 16);
		EnemyNowstatus[EnemyNo].y = (EnemyNowstatus[EnemyNo].y << 16);
		EnemyMagic[EnemyNo].status  = 0;
		EnemyMagic[EnemyNo].flg     = OFF;
		Coin[EnemyNo].x = Coin[EnemyNo].y = 1024 << 16;
		Coin[EnemyNo].flg = OFF;
	}
	// ***** 初期設定 ***** E

	return;
}

//*****************************  PROGRAM END  **********************************

