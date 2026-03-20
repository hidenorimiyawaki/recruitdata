//**************************************************************************** S
//
//	 ソース名称		:	global.h
//
//==============================================================================
//	 コメント		:	グローバル変数の宣言を行うヘッダー（初期化はしないこと）
//						外部で宣言された変数のextern宣言も行う
//	 最終更新日		:	2002/10/28 (Mon)
//**************************************************************************** E

#ifndef	___GLOBAL_H___		// このヘッダファイルが読み込まれていなければ
  #define	___GLOBAL_H___	
  #define	EX				// EXの定義のみをする
#else						// このヘッダファイルが読み込まれていれば
  #undef	EX
  #define	EX	extern		// EXの定義をextern（外部参照宣言）にする
#endif


// ======= グローバル変数宣言部 ======= S
EX	vu16		GameTimer;				// フレームカウンタ
EX	SPRITE		ObjBuf[128];			// 仮想OAM RAM領域
EX	u8			StringNo;				// 表示文字列スプライトNo

EX	vu16		Key, Trg, OldKey;

EX	vu16		SioKey[4];				// 現在のキー入力
EX	vu16		SioTrg[4];				// 現在のトリガー入力
EX	vu16		SioOldKey[4];			// 一つ前のキー入力

EX	s32			Hoffset, Voffset;

EX	ANIME		*NowAnime;				// 現時点のアニメーション先頭アドレス
EX	ANIME		*NowAnime2;				// 現時点の敵アニメーション先頭アドレス
EX	u8			SpBgCnt;				// 画面フラッシュ用のカウンタ


EX	PLAYER			PlayerNowstatus[4];			// 現在のプレイヤーステータス
EX	ENEMY			EnemyNowstatus[4];			// 現在の敵のステータス
EX	EFFECT			PlayerEffect[4];			// プレイヤーエフェクト用
EX	EFFECT			PlayerDamEffect[4];			// プレイヤーダメージエフェクト用
EX	EFFECT			EnemyEffect[4];				// 敵用エフェクト
EX	MAGIC_EFFECT	PlayerMagic[1];				// プレイヤー魔法
EX	MAGIC_EFFECT	EnemyMagic[4];				// 敵魔法及び飛び道具
EX	ITEM			Coin[4];					// コイン


// ******** 通信用 *********
EX	u32			IntrMainBuf[0x100/4];				// 割り込みメインルーチン用バッファ

EX	vu16		SendBuf[MULTI_SIO_BLOCK_SIZE/2];	// ユーザ送信バッファ
EX	vu16		RecvBuf[MULTI_SIO_PLAYERS_MAX][MULTI_SIO_BLOCK_SIZE/2];
													// ユーザ受信バッファ
EX	u32			SioFlags;							// 通信状態
EX	u32			SioFlagsBak;
EX	u8			SioStartFlag;						// 通信開始フラグ

EX enum { START, C_SELECT, S_SELECT, MAIN, END } GameStatus;

// ======= グローバル変数宣言部 ======= E

// ======= ゲームデータの外部参照宣言部 ======= S
extern const u32	c_SinTbl[256+64];		// サインテーブル
extern const u32	c_DivRoot2[];

extern const HIT_TYPE	ATTACK[];				// 攻撃範囲データ
extern const ENEMY		ENEMY_STATUS[];			// 敵 基本ステータス

// ======= ゲームデータの外部参照宣言部 ======= E

// ======= グラフィックデータの外部参照宣言部 ======= S

// *******   背景   ********

extern const u8		bg_sanctuary_main_Character[8*8/2*209];	// 神殿 キャラデータ
extern const u16	bg_sanctuary_main_Map[128*128];			//      マップデータ
extern const u8		bg_sanctuary_Wall[128][128];			//      壁データ
extern const u16	bg_sanctuary_main_Palette[16];			//      パレットデータ

extern const u16	system_Palette[16];					// 背景フォントパレットデータ
extern const u8		system_Char[32*128/8*64/8 + 0];		// 背景フォントキャラクターデータ

// 基本フレーム		3つとも共通のパレット
extern const u16	char_select_frame_Palette[16];
extern const u8		char_select_frame_Character[8*8/2*112];
extern const u16	char_select_frame_Map[32*32];
extern const u8		winner_frame_Character[8*8/2*96];
extern const u16	winner_frame_Map[32*32];

extern const u16	title_16_bg_Palette[16];			// タイトル
extern const u8		title_16_bg_Character[8*8/2*273];
extern const u16	title_16_bg_Map[32*32];

extern const u16	title_cloud_bg_Palette[16];			// タイトル雲
extern const u8		title_cloud_bg_Character[8*8/2*244];
extern const u16	title_cloud_bg_Map[32*32];

extern const u16	game_over_logo_Palette[16];			// ゲームオーバー
extern const u8		game_over_logo_Character[8*8/2*145];
extern const u16	game_over_logo_Map[30*20];

extern const u16	special_flash_01_Palette[16];
extern const u8 	special_flash_01_Character[8*8/2*62];
extern const u8		special_flash_02_Character[8*8/2*31];
extern const u8		special_flash_03_Character[8*8/2*17];
extern const u8		special_flash_04_Character[8*8/2*22];
extern const u8		special_flash_05_Character[8*8/2*12];
extern const u8		special_flash_06_Character[8*8/2*9];

extern const u16	special_flash_01_Map[30*20];
extern const u16	special_flash_02_Map[30*20];
extern const u16	special_flash_03_Map[30*20];
extern const u16	special_flash_04_Map[30*20];
extern const u16	special_flash_05_Map[30*20];
extern const u16	special_flash_06_Map[30*20];


// ******* パレット ********
extern const u16	ply_sp_Palette[16];
extern const u16	ply_bs_Palette[16];
extern const u16	ply_pw_Palette[16];
extern const u16	emy_sl_Palette[16];
extern const u16	emy_pz_Palette[16];
extern const u16	emy_kn_Palette[16];
extern const u16	emy_go_Palette[16];
extern const u16	eft_mg_Palette[16];
extern const u16	eft_sp_Palette[16];
extern const u16	damage_plt_Palette[16];
extern const u16	start_logo_Palette[16];
extern const u16	rank_Palette[16];
extern const u16	system_Palette[16];
// ******* 色違いキャラ用パレット ********
extern const u16	ply_sp_02_Palette[16];
extern const u16	ply_sp_03_Palette[16];
extern const u16	ply_sp_04_Palette[16];
extern const u16	ply_pw_02_Palette[16];
extern const u16	ply_pw_03_Palette[16];
extern const u16	ply_pw_04_Palette[16];
extern const u16	ply_bs_02_Palette[16];
extern const u16	ply_bs_03_Palette[16];
extern const u16	ply_bs_04_Palette[16];

// ******* ランク表示 *******
extern const u8		rank1_Char[];
extern const u8		rank2_Char[];
extern const u8		rank3_Char[];
extern const u8		rank4_Char[];

// *******  立ち絵  ********
extern const u8		title_beast_Char[];
extern const u8		title_magic_Char[];
extern const u8		title_petit_Char[];
extern const u8		title_power_Char[];
extern const u8		title_speed_Char[];

extern const u8		select_beast_Char[];
extern const u8		select_magic_Char[];
extern const u8		select_petit_Char[];
extern const u8		select_power_Char[];
extern const u8		select_speed_Char[];

// *******  通常絵  ********
extern const u8		sp_01_f_Char[];						// スピード
extern const u8		sp_01_s_Char[];
extern const u8		sp_01_r_Char[];

extern const u8		sp_11_f_Char[];
extern const u8		sp_12_f_Char[];
extern const u8		sp_13_f_Char[];
extern const u8		sp_14_f_Char[];

extern const u8		sp_11_s_Char[];
extern const u8		sp_12_s_Char[];
extern const u8		sp_13_s_Char[];
extern const u8		sp_14_s_Char[];

extern const u8		sp_11_r_Char[];
extern const u8		sp_12_r_Char[];
extern const u8		sp_13_r_Char[];
extern const u8		sp_14_r_Char[];

extern const u8		sp_21_f_Char[];
extern const u8		sp_22_f_Char[];
extern const u8		sp_23_f_Char[];
extern const u8		sp_24_f_Char[];
extern const u8		sp_25_f_Char[];
extern const u8		sp_26_f_Char[];
extern const u8		sp_27_f_Char[];

extern const u8		sp_21_s_Char[];
extern const u8		sp_22_s_Char[];
extern const u8		sp_23_s_Char[];
extern const u8		sp_24_s_Char[];
extern const u8		sp_25_s_Char[];
extern const u8		sp_26_s_Char[];
extern const u8		sp_27_s_Char[];
extern const u8		sp_28_s_Char[];

extern const u8		sp_21_r_Char[];
extern const u8		sp_22_r_Char[];
extern const u8		sp_23_r_Char[];
extern const u8		sp_24_r_Char[];
extern const u8		sp_25_r_Char[];
extern const u8		sp_26_r_Char[];
extern const u8		sp_27_r_Char[];
extern const u8		sp_28_r_Char[];

extern const u8		sp_31_f_Char[];
extern const u8		sp_32_f_Char[];
extern const u8		sp_33_f_Char[];
extern const u8		sp_34_f_Char[];
extern const u8		sp_35_f_Char[];

extern const u8		sp_31_s_Char[];
extern const u8		sp_32_s_Char[];
extern const u8		sp_33_s_Char[];
extern const u8		sp_34_s_Char[];
extern const u8		sp_35_s_Char[];

extern const u8		sp_31_r_Char[];
extern const u8		sp_32_r_Char[];
extern const u8		sp_33_r_Char[];
extern const u8		sp_34_r_Char[];
extern const u8		sp_35_r_Char[];

extern const u8		sp_41_f_Char[];
extern const u8		sp_42_f_Char[];
extern const u8		sp_43_f_Char[];
extern const u8		sp_44_f_Char[];

extern const u8		sp_41_s_Char[];
extern const u8		sp_42_s_Char[];
extern const u8		sp_43_s_Char[];
extern const u8		sp_44_s_Char[];

extern const u8		sp_41_r_Char[];
extern const u8		sp_42_r_Char[];
extern const u8		sp_43_r_Char[];
extern const u8		sp_44_r_Char[];

extern const u8		sp_51_f_Char[];
extern const u8		sp_51_s_Char[];
extern const u8		sp_51_r_Char[];

extern const u8		sp_61_f_Char[];
extern const u8		sp_62_f_Char[];
extern const u8		sp_63_f_Char[];

extern const u8		sp_61_s_Char[];
extern const u8		sp_62_s_Char[];
extern const u8		sp_63_s_Char[];

extern const u8		sp_61_r_Char[];
extern const u8		sp_62_r_Char[];
extern const u8		sp_63_r_Char[];

extern const u8		sp_90_f_Char[];


extern const u8		mg_01_f_Char[];				// マジシャン
extern const u8		mg_01_s_Char[];
extern const u8		mg_01_r_Char[];

extern const u8		mg_11_f_Char[];
extern const u8		mg_12_f_Char[];
extern const u8		mg_13_f_Char[];
extern const u8		mg_14_f_Char[];

extern const u8		mg_11_s_Char[];
extern const u8		mg_12_s_Char[];
extern const u8		mg_13_s_Char[];
extern const u8		mg_14_s_Char[];

extern const u8		mg_11_r_Char[];
extern const u8		mg_12_r_Char[];
extern const u8		mg_13_r_Char[];
extern const u8		mg_14_r_Char[];

extern const u8		mg_21_f_Char[];
extern const u8		mg_22_f_Char[];
extern const u8		mg_23_f_Char[];
extern const u8		mg_24_f_Char[];

extern const u8		mg_21_s_Char[];
extern const u8		mg_22_s_Char[];
extern const u8		mg_23_s_Char[];
extern const u8		mg_24_s_Char[];

extern const u8		mg_21_r_Char[];
extern const u8		mg_22_r_Char[];
extern const u8		mg_23_r_Char[];
extern const u8		mg_24_r_Char[];

extern const u8		mg_31_f_Char[];
extern const u8		mg_32_f_Char[];
extern const u8		mg_33_f_Char[];

extern const u8		mg_31_s_Char[];
extern const u8		mg_32_s_Char[];
extern const u8		mg_33_s_Char[];

extern const u8		mg_31_r_Char[];
extern const u8		mg_32_r_Char[];
extern const u8		mg_33_r_Char[];

extern const u8		mg_41_f_Char[];
extern const u8		mg_42_f_Char[];
extern const u8		mg_43_f_Char[];
extern const u8		mg_44_f_Char[];
extern const u8		mg_45_f_Char[];

extern const u8		mg_51_f_Char[];
extern const u8		mg_51_s_Char[];
extern const u8		mg_51_r_Char[];

extern const u8		mg_61_f_Char[];
extern const u8		mg_62_f_Char[];
extern const u8		mg_63_f_Char[];
extern const u8		mg_64_f_Char[];
extern const u8		mg_65_f_Char[];

extern const u8		mg_90_f_Char[];


extern const u8		pt_01_f_Char[];			// プチ
extern const u8		pt_01_s_Char[];
extern const u8		pt_01_r_Char[];

extern const u8		pt_11_f_Char[];
extern const u8		pt_12_f_Char[];
extern const u8		pt_13_f_Char[];
extern const u8		pt_14_f_Char[];

extern const u8		pt_11_s_Char[];
extern const u8		pt_12_s_Char[];
extern const u8		pt_13_s_Char[];
extern const u8		pt_14_s_Char[];

extern const u8		pt_11_r_Char[];
extern const u8		pt_12_r_Char[];
extern const u8		pt_13_r_Char[];
extern const u8		pt_14_r_Char[];

extern const u8		pt_21_f_Char[];
extern const u8		pt_22_f_Char[];
extern const u8		pt_23_f_Char[];

extern const u8		pt_21_s_Char[];
extern const u8		pt_22_s_Char[];
extern const u8		pt_23_s_Char[];

extern const u8		pt_21_r_Char[];
extern const u8		pt_22_r_Char[];
extern const u8		pt_23_r_Char[];

extern const u8		pt_31_f_Char[];
extern const u8		pt_32_f_Char[];
extern const u8		pt_33_f_Char[];

extern const u8		pt_31_s_Char[];
extern const u8		pt_32_s_Char[];
extern const u8		pt_33_s_Char[];

extern const u8		pt_31_r_Char[];
extern const u8		pt_32_r_Char[];
extern const u8		pt_33_r_Char[];

extern const u8		pt_41_f_Char[];
extern const u8		pt_42_f_Char[];

extern const u8		pt_41_s_Char[];
extern const u8		pt_42_s_Char[];

extern const u8		pt_41_r_Char[];
extern const u8		pt_42_r_Char[];

extern const u8		pt_51_f_Char[];
extern const u8		pt_51_s_Char[];
extern const u8		pt_51_r_Char[];

extern const u8		pt_61_f_Char[];
extern const u8		pt_62_f_Char[];
extern const u8		pt_63_f_Char[];

extern const u8		pt_90_f_Char[];


extern const u8		bs_01_f_Char[];			// ビースト
extern const u8		bs_01_s_Char[];
extern const u8		bs_01_r_Char[];

extern const u8		bs_11_f_Char[];
extern const u8		bs_12_f_Char[];
extern const u8		bs_13_f_Char[];
extern const u8		bs_14_f_Char[];

extern const u8		bs_11_s_Char[];
extern const u8		bs_12_s_Char[];
extern const u8		bs_13_s_Char[];
extern const u8		bs_14_s_Char[];

extern const u8		bs_11_r_Char[];
extern const u8		bs_12_r_Char[];
extern const u8		bs_13_r_Char[];
extern const u8		bs_14_r_Char[];

extern const u8		bs_21_f_Char[];
extern const u8		bs_22_f_Char[];
extern const u8		bs_23_f_Char[];
extern const u8		bs_24_f_Char[];
extern const u8		bs_25_f_Char[];
extern const u8		bs_26_f_Char[];
extern const u8		bs_27_f_Char[];
extern const u8		bs_28_f_Char[];
extern const u8		bs_29_f_Char[];

extern const u8		bs_21_s_Char[];
extern const u8		bs_22_s_Char[];
extern const u8		bs_23_s_Char[];
extern const u8		bs_24_s_Char[];
extern const u8		bs_25_s_Char[];
extern const u8		bs_26_s_Char[];
extern const u8		bs_27_s_Char[];
extern const u8		bs_28_s_Char[];
extern const u8		bs_29_s_Char[];

extern const u8		bs_21_r_Char[];
extern const u8		bs_22_r_Char[];
extern const u8		bs_23_r_Char[];
extern const u8		bs_24_r_Char[];
extern const u8		bs_25_r_Char[];
extern const u8		bs_26_r_Char[];
extern const u8		bs_27_r_Char[];
extern const u8		bs_28_r_Char[];
extern const u8		bs_29_r_Char[];

extern const u8		bs_31_f_Char[];
extern const u8		bs_32_f_Char[];
extern const u8		bs_33_f_Char[];

extern const u8		bs_31_s_Char[];
extern const u8		bs_32_s_Char[];
extern const u8		bs_33_s_Char[];

extern const u8		bs_31_r_Char[];
extern const u8		bs_32_r_Char[];
extern const u8		bs_33_r_Char[];

extern const u8		bs_41_f_Char[];
extern const u8		bs_42_f_Char[];
extern const u8		bs_43_f_Char[];

extern const u8		bs_41_s_Char[];
extern const u8		bs_42_s_Char[];
extern const u8		bs_43_s_Char[];

extern const u8		bs_41_r_Char[];
extern const u8		bs_42_r_Char[];
extern const u8		bs_43_r_Char[];

extern const u8		bs_51_f_Char[];
extern const u8		bs_51_s_Char[];
extern const u8		bs_51_r_Char[];

extern const u8		bs_61_f_Char[];
extern const u8		bs_62_f_Char[];
extern const u8		bs_63_f_Char[];
extern const u8		bs_64_f_Char[];
extern const u8		bs_65_f_Char[];

extern const u8		bs_90_f_Char[];


extern const u8		pw_01_f_Char[];			// プチ
extern const u8		pw_01_s_Char[];
extern const u8		pw_01_r_Char[];

extern const u8		pw_11_f_Char[];
extern const u8		pw_12_f_Char[];
extern const u8		pw_13_f_Char[];
extern const u8		pw_14_f_Char[];

extern const u8		pw_11_s_Char[];
extern const u8		pw_12_s_Char[];
extern const u8		pw_13_s_Char[];
extern const u8		pw_14_s_Char[];

extern const u8		pw_11_r_Char[];
extern const u8		pw_12_r_Char[];
extern const u8		pw_13_r_Char[];
extern const u8		pw_14_r_Char[];

extern const u8		pw_21_f_Char[];
extern const u8		pw_22_f_Char[];
extern const u8		pw_23_f_Char[];
extern const u8		pw_24_f_Char[];

extern const u8		pw_21_s_Char[];
extern const u8		pw_22_s_Char[];
extern const u8		pw_23_s_Char[];
extern const u8		pw_24_s_Char[];

extern const u8		pw_21_r_Char[];
extern const u8		pw_22_r_Char[];
extern const u8		pw_23_r_Char[];
extern const u8		pw_24_r_Char[];

extern const u8		pw_31_f_Char[];
extern const u8		pw_32_f_Char[];
extern const u8		pw_33_f_Char[];

extern const u8		pw_31_s_Char[];
extern const u8		pw_32_s_Char[];
extern const u8		pw_33_s_Char[];

extern const u8		pw_31_r_Char[];
extern const u8		pw_32_r_Char[];
extern const u8		pw_33_r_Char[];

extern const u8		pw_41_f_Char[];
extern const u8		pw_42_f_Char[];

extern const u8		pw_41_s_Char[];
extern const u8		pw_42_s_Char[];

extern const u8		pw_41_r_Char[];
extern const u8		pw_42_r_Char[];

extern const u8		pw_51_f_Char[];
extern const u8		pw_51_s_Char[];
extern const u8		pw_51_r_Char[];

extern const u8		pw_61_f_Char[];
extern const u8		pw_62_f_Char[];

extern const u8		pw_61_s_Char[];
extern const u8		pw_62_s_Char[];

extern const u8		pw_61_r_Char[];
extern const u8		pw_62_r_Char[];

extern const u8		pw_90_f_Char[];



// **** スライム
extern const u8		sl_01_f_Char[];
extern const u8		sl_02_f_Char[];
extern const u8		sl_03_f_Char[];
extern const u8		sl_04_f_Char[];
extern const u8		sl_21_Char[];

// **** ヌー
extern const u8		nu_01_f_Char[];
extern const u8		nu_02_f_Char[];
extern const u8		nu_01_r_Char[];
extern const u8		nu_02_r_Char[];
extern const u8		nu_11_f_Char[];
extern const u8		nu_12_f_Char[];
extern const u8		nu_11_r_Char[];
extern const u8		nu_12_r_Char[];
extern const u8		nu_21_Char[];

// **** ラフリー
extern const u8		rf_01_f_Char[];
extern const u8		rf_02_f_Char[];
extern const u8		rf_03_f_Char[];
extern const u8		rf_01_r_Char[];
extern const u8		rf_02_r_Char[];
extern const u8		rf_03_r_Char[];
extern const u8		rf_11_Char[];
extern const u8		rf_12_Char[];
extern const u8		rf_21_Char[];
extern const u8		rf_31_Char[];
extern const u8		rf_32_Char[];
extern const u8		rf_33_Char[];
extern const u8		rf_34_Char[];
extern const u8		rf_35_Char[];
extern const u8		rf_36_Char[];
extern const u8		rf_37_Char[];

// **** ウサ
extern const u8		us_01_f_Char[];
extern const u8		us_02_f_Char[];
extern const u8		us_03_f_Char[];
extern const u8		us_01_r_Char[];
extern const u8		us_02_r_Char[];
extern const u8		us_03_r_Char[];
extern const u8		us_11_f_Char[];
extern const u8		us_11_r_Char[];
extern const u8		us_21_Char[];

// **** プラズマー
extern const u8		pz_01_f_Char[];
extern const u8		pz_02_f_Char[];
extern const u8		pz_03_f_Char[];
extern const u8		pz_04_f_Char[];
extern const u8		pz_01_r_Char[];
extern const u8		pz_02_r_Char[];
extern const u8		pz_03_r_Char[];
extern const u8		pz_04_r_Char[];
extern const u8		pz_11_f_Char[];
extern const u8		pz_12_f_Char[];
extern const u8		pz_13_f_Char[];
extern const u8		pz_11_r_Char[];
extern const u8		pz_12_r_Char[];
extern const u8		pz_13_r_Char[];
extern const u8		pz_21_Char[];

// **** ウニ
extern const u8		ui_01_f_Char[];
extern const u8		ui_02_f_Char[];
extern const u8		ui_03_f_Char[];
extern const u8		ui_01_r_Char[];
extern const u8		ui_02_r_Char[];
extern const u8		ui_03_r_Char[];
extern const u8		ui_04_f_Char[];
extern const u8		ui_04_r_Char[];
extern const u8		ui_11_f_Char[];
extern const u8		ui_12_f_Char[];
extern const u8		ui_13_f_Char[];
extern const u8		ui_14_f_Char[];
extern const u8		ui_15_f_Char[];
extern const u8		ui_11_r_Char[];
extern const u8		ui_12_r_Char[];
extern const u8		ui_13_r_Char[];
extern const u8		ui_14_r_Char[];
extern const u8		ui_15_r_Char[];
extern const u8		ui_21_Char[];

// **** トリ
extern const u8		tr_01_f_Char[];
extern const u8		tr_02_f_Char[];
extern const u8		tr_03_f_Char[];
extern const u8		tr_01_r_Char[];
extern const u8		tr_02_r_Char[];
extern const u8		tr_03_r_Char[];
extern const u8		tr_11_f_Char[];
extern const u8		tr_12_f_Char[];
extern const u8		tr_13_f_Char[];
extern const u8		tr_14_f_Char[];
extern const u8		tr_15_f_Char[];
extern const u8		tr_16_f_Char[];
extern const u8		tr_11_r_Char[];
extern const u8		tr_12_r_Char[];
extern const u8		tr_13_r_Char[];
extern const u8		tr_14_r_Char[];
extern const u8		tr_15_r_Char[];
extern const u8		tr_16_r_Char[];
extern const u8		tr_21_Char[];

// **** カエル
extern const u8		ke_01_f_Char[];
extern const u8		ke_02_f_Char[];
extern const u8		ke_03_f_Char[];

// **** キノコ
extern const u8		kn_01_f_Char[];
extern const u8		kn_02_f_Char[];
extern const u8		kn_03_f_Char[];
extern const u8		kn_01_r_Char[];
extern const u8		kn_02_r_Char[];
extern const u8		kn_03_r_Char[];
extern const u8		kn_11_f_Char[];
extern const u8		kn_12_f_Char[];
extern const u8		kn_13_f_Char[];
extern const u8		kn_14_f_Char[];
extern const u8		kn_15_f_Char[];
extern const u8		kn_16_f_Char[];
extern const u8		kn_11_r_Char[];
extern const u8		kn_12_r_Char[];
extern const u8		kn_13_r_Char[];
extern const u8		kn_14_r_Char[];
extern const u8		kn_15_r_Char[];
extern const u8		kn_16_r_Char[];
extern const u8		kn_21_Char[];

// *** ゴースト
extern const u8		go_01_f_Char[];
extern const u8		go_02_f_Char[];
extern const u8		go_03_f_Char[];
extern const u8		go_04_f_Char[];
extern const u8		go_01_r_Char[];
extern const u8		go_02_r_Char[];
extern const u8		go_03_r_Char[];
extern const u8		go_04_r_Char[];
extern const u8		go_11_f_Char[];
extern const u8		go_12_f_Char[];
extern const u8		go_13_f_Char[];
extern const u8		go_14_f_Char[];
extern const u8		go_11_r_Char[];
extern const u8		go_12_r_Char[];
extern const u8		go_13_r_Char[];
extern const u8		go_14_r_Char[];
extern const u8		go_21_Char[];

// *** ドム
extern const u8		do_01_f_Char[];
extern const u8		do_02_f_Char[];
extern const u8		do_03_f_Char[];
extern const u8		do_01_r_Char[];
extern const u8		do_02_r_Char[];
extern const u8		do_03_r_Char[];
extern const u8		do_11_f_Char[];
extern const u8		do_12_f_Char[];
extern const u8		do_13_f_Char[];
extern const u8		do_14_f_Char[];
extern const u8		do_11_r_Char[];
extern const u8		do_12_r_Char[];
extern const u8		do_13_r_Char[];
extern const u8		do_14_r_Char[];
extern const u8		do_21_Char[];

// *** コウモリ
extern const u8		ko_01_f_Char[];
extern const u8		ko_02_f_Char[];
extern const u8		ko_03_f_Char[];
extern const u8		ko_01_r_Char[];
extern const u8		ko_02_r_Char[];
extern const u8		ko_03_r_Char[];
extern const u8		ko_11_f_Char[];
extern const u8		ko_12_f_Char[];
extern const u8		ko_13_f_Char[];
extern const u8		ko_14_f_Char[];
extern const u8		ko_15_f_Char[];
extern const u8		ko_16_f_Char[];
extern const u8		ko_17_f_Char[];
extern const u8		ko_11_r_Char[];
extern const u8		ko_12_r_Char[];
extern const u8		ko_13_r_Char[];
extern const u8		ko_14_r_Char[];
extern const u8		ko_15_r_Char[];
extern const u8		ko_16_r_Char[];
extern const u8		ko_17_r_Char[];
extern const u8		ko_21_Char[];

// *** サソリ
extern const u8		sa_01_f_Char[];
extern const u8		sa_02_f_Char[];
extern const u8		sa_03_f_Char[];
extern const u8		sa_01_r_Char[];
extern const u8		sa_02_r_Char[];
extern const u8		sa_03_r_Char[];
extern const u8		sa_11_f_Char[];
extern const u8		sa_12_f_Char[];
extern const u8		sa_13_f_Char[];
extern const u8		sa_11_r_Char[];
extern const u8		sa_12_r_Char[];
extern const u8		sa_13_r_Char[];
extern const u8		sa_21_Char[];

// *** 敵エフェクト
extern const u8		go_shot_01_Char[];
extern const u8		go_shot_02_Char[];
extern const u8		go_shot_11_Char[];
extern const u8		go_shot_12_Char[];
extern const u8		go_shot_13_Char[];

extern const u8		rf_shot_01_Char[];
extern const u8		rf_shot_02_Char[];
extern const u8		rf_shot_03_Char[];
extern const u8		rf_shot_04_Char[];

// ボスデータ
extern const u8		knight_01_Char[];		// 装甲魔人
extern const u8		knight_02_Char[];
extern const u8		knight_03_Char[];
extern const u8		knight_10_Char[];
extern const u8		knight_11_Char[];
extern const u8		knight_12_Char[];
extern const u8		knight_13_Char[];
extern const u8		knight_12_half_Char[];
extern const u8		knight_13_half_Char[];

// *** ダメージエフェクト
extern const u8		dmg_ef_01_Char[];
extern const u8		dmg_ef_02_Char[];
extern const u8		dmg_ef_03_Char[];
extern const u8		dmg_ef_04_Char[];

// *** 煙エフェクト
extern const u8		smk_ef_01_Char[];
extern const u8		smk_ef_02_Char[];
extern const u8		smk_ef_03_Char[];
extern const u8		smk_ef_04_Char[];

// *** 魔法攻撃エフェクト
extern const u8		mg_shot_01_Char[];
extern const u8		mg_shot_02_Char[];
extern const u8		mg_shot_03_Char[];

extern const u8		mg_shot_11_Char[];
extern const u8		mg_shot_12_Char[];
extern const u8		mg_shot_13_Char[];
extern const u8		mg_shot_14_Char[];

extern const u8		mg_skill_ef_01_Char[];
extern const u8		mg_skill_ef_02_Char[];
extern const u8		mg_skill_ef_03_Char[];
extern const u8		mg_skill_ef_04_Char[];

extern const u8		mg_special_ef_01_Char[];
extern const u8		mg_special_ef_02_Char[];
extern const u8		mg_special_ef_03_Char[];
extern const u8		mg_special_ef_04_Char[];
extern const u8		mg_special_ef_05_Char[];
extern const u8		mg_special_ef_06_Char[];

extern const u8		pw_special_ef_01_Char[];
extern const u8		pw_special_ef_02_Char[];
extern const u8		pw_special_ef_03_Char[];
extern const u8		pw_special_ef_04_Char[];

extern const u8		sp_special_ef_01_f_Char[];
extern const u8		sp_special_ef_02_f_Char[];
extern const u8		sp_special_ef_03_f_Char[];
extern const u8		sp_special_ef_01_s_Char[];
extern const u8		sp_special_ef_02_s_Char[];
extern const u8		sp_special_ef_03_s_Char[];
extern const u8		sp_special_ef_01_r_Char[];
extern const u8		sp_special_ef_02_r_Char[];
extern const u8		sp_special_ef_03_r_Char[];

extern const u8		pt_fire_f_01_Char[];
extern const u8		pt_fire_f_02_Char[];
extern const u8		pt_fire_f_03_Char[];
extern const u8		pt_fire_s_01_Char[];
extern const u8		pt_fire_s_02_Char[];
extern const u8		pt_fire_s_03_Char[];
extern const u8		pt_fire_r_01_Char[];
extern const u8		pt_fire_r_02_Char[];
extern const u8		pt_fire_r_03_Char[];

extern const u8		splash_ef_f_01_Char[];	// プチ用必殺技エフェクト
extern const u8		splash_ef_f_02_Char[];
extern const u8		splash_ef_f_03_Char[];
extern const u8		splash_ef_f_04_Char[];

extern const u8		splash_ef_s_01_Char[];
extern const u8		splash_ef_s_02_Char[];
extern const u8		splash_ef_s_03_Char[];

extern const u8		splash_ef_r_01_Char[];
extern const u8		splash_ef_r_02_Char[];
extern const u8		splash_ef_r_03_Char[];
extern const u8		splash_ef_r_04_Char[];

// *** ＨＰゲージ
extern const u8		e_bar_proto_Char[];

extern const u8		coin_small_01_Char[];
extern const u8		coin_small_02_Char[];
extern const u8		coin_small_03_Char[];
extern const u8		coin_small_04_Char[];


// ************ アニメーションデータ配列 *************
extern const ANIME	SP_STAND_F[];
extern const ANIME	SP_STAND_S[];
extern const ANIME	SP_STAND_R[];
extern const ANIME	SP_WALK_F[];
extern const ANIME	SP_WALK_S[];
extern const ANIME	SP_WALK_R[];
extern const ANIME	SP_ATK_F[];
extern const ANIME	SP_ATK_S[];
extern const ANIME	SP_ATK_R[];
extern const ANIME	SP_ATK2_F[];
extern const ANIME	SP_ATK2_S[];
extern const ANIME	SP_ATK2_R[];
extern const ANIME	SP_JUMP_F[];
extern const ANIME	SP_JUMP_S[];
extern const ANIME	SP_JUMP_R[];
extern const ANIME	SP_SKILL_F[];
extern const ANIME	SP_SKILL_S[];
extern const ANIME	SP_SKILL_R[];
extern const ANIME	SP_DAM_F[];
extern const ANIME	SP_DAM_S[];
extern const ANIME	SP_DAM_R[];
extern const ANIME	SP_SPECIAL_F[];
extern const ANIME	SP_SPECIAL_S[];
extern const ANIME	SP_SPECIAL_R[];
extern const ANIME	SP_DEATH_F[];

extern const ANIME	MG_STAND_F[];
extern const ANIME	MG_STAND_S[];
extern const ANIME	MG_STAND_R[];
extern const ANIME	MG_WALK_F[];
extern const ANIME	MG_WALK_S[];
extern const ANIME	MG_WALK_R[];
extern const ANIME	MG_ATK_F[];
extern const ANIME	MG_ATK_S[];
extern const ANIME	MG_ATK_R[];
extern const ANIME	MG_JUMP_F[];
extern const ANIME	MG_JUMP_S[];
extern const ANIME	MG_JUMP_R[];
extern const ANIME	MG_SKILL_F[];
extern const ANIME	MG_DAM_F[];
extern const ANIME	MG_DAM_S[];
extern const ANIME	MG_DAM_R[];
extern const ANIME	MG_SPECIAL_F[];
extern const ANIME	MG_DEATH_F[];

extern const ANIME	PT_STAND_F[];
extern const ANIME	PT_STAND_S[];
extern const ANIME	PT_STAND_R[];
extern const ANIME	PT_WALK_F[];
extern const ANIME	PT_WALK_S[];
extern const ANIME	PT_WALK_R[];
extern const ANIME	PT_ATK_F[];
extern const ANIME	PT_ATK_S[];
extern const ANIME	PT_ATK_R[];
extern const ANIME	PT_JUMP_F[];
extern const ANIME	PT_JUMP_S[];
extern const ANIME	PT_JUMP_R[];
extern const ANIME	PT_SKILL_F[];
extern const ANIME	PT_SKILL_S[];
extern const ANIME	PT_SKILL_R[];
extern const ANIME	PT_DAM_F[];
extern const ANIME	PT_DAM_S[];
extern const ANIME	PT_DAM_R[];
extern const ANIME	PT_SPECIAL_F[];
extern const ANIME	PT_DEATH_F[];

extern const ANIME	BS_STAND_F[];
extern const ANIME	BS_STAND_S[];
extern const ANIME	BS_STAND_R[];
extern const ANIME	BS_WALK_F[];
extern const ANIME	BS_WALK_S[];
extern const ANIME	BS_WALK_R[];
extern const ANIME	BS_ATK_F[];
extern const ANIME	BS_ATK_S[];
extern const ANIME	BS_ATK_R[];
extern const ANIME	BS_ATK2_F[];
extern const ANIME	BS_ATK2_S[];
extern const ANIME	BS_ATK2_R[];
extern const ANIME	BS_ATK3_F[];
extern const ANIME	BS_ATK3_S[];
extern const ANIME	BS_ATK3_R[];
extern const ANIME	BS_JUMP_F[];
extern const ANIME	BS_JUMP_S[];
extern const ANIME	BS_JUMP_R[];
extern const ANIME	BS_SKILL_F[];
extern const ANIME	BS_SKILL_S[];
extern const ANIME	BS_SKILL_R[];
extern const ANIME	BS_DAM_F[];
extern const ANIME	BS_DAM_S[];
extern const ANIME	BS_DAM_R[];
extern const ANIME	BS_SPECIAL_F[];
extern const ANIME	BS_DEATH_F[];

extern const ANIME	PW_STAND_F[];
extern const ANIME	PW_STAND_S[];
extern const ANIME	PW_STAND_R[];
extern const ANIME	PW_WALK_F[];
extern const ANIME	PW_WALK_S[];
extern const ANIME	PW_WALK_R[];
extern const ANIME	PW_ATK_F[];
extern const ANIME	PW_ATK_S[];
extern const ANIME	PW_ATK_R[];
extern const ANIME	PW_JUMP_F[];
extern const ANIME	PW_JUMP_S[];
extern const ANIME	PW_JUMP_R[];
extern const ANIME	PW_SKILL_F[];
extern const ANIME	PW_SKILL_S[];
extern const ANIME	PW_SKILL_R[];
extern const ANIME	PW_DAM_F[];
extern const ANIME	PW_DAM_S[];
extern const ANIME	PW_DAM_R[];
extern const ANIME	PW_SPECIAL_F[];
extern const ANIME	PW_SPECIAL_S[];
extern const ANIME	PW_SPECIAL_R[];
extern const ANIME	PW_DEATH_F[];

extern const ANIME	ENEMY_SL_F[];
extern const ANIME	ENEMY_SL_DAM[];

extern const ANIME	ENEMY_NU_F[];
extern const ANIME	ENEMY_NU_R[];
extern const ANIME	ENEMY_NU_ATK_F[];
extern const ANIME	ENEMY_NU_ATK_R[];
extern const ANIME	ENEMY_NU_DAM[];

extern const ANIME	ENEMY_RF_F[];
extern const ANIME	ENEMY_RF_R[];
extern const ANIME	ENEMY_RF_ATK[];
extern const ANIME	ENEMY_RF_DAM[];
extern const ANIME	ENEMY_RF_APP[];

extern const ANIME	ENEMY_US_F[];
extern const ANIME	ENEMY_US_R[];
extern const ANIME	ENEMY_US_ATK_F[];
extern const ANIME	ENEMY_US_ATK_R[];
extern const ANIME	ENEMY_US_DAM[];

extern const ANIME	ENEMY_PZ_F[];
extern const ANIME	ENEMY_PZ_R[];
extern const ANIME	ENEMY_PZ_ATK_F[];
extern const ANIME	ENEMY_PZ_ATK_R[];
extern const ANIME	ENEMY_PZ_DAM[];

extern const ANIME	ENEMY_UI_F[];
extern const ANIME	ENEMY_UI_R[];
extern const ANIME	ENEMY_UI_ATK_F[];
extern const ANIME	ENEMY_UI_ATK_R[];
extern const ANIME	ENEMY_UI_DAM[];

extern const ANIME	ENEMY_TR_F[];
extern const ANIME	ENEMY_TR_R[];
extern const ANIME	ENEMY_TR_ATK_F[];
extern const ANIME	ENEMY_TR_ATK_R[];
extern const ANIME	ENEMY_TR_DAM[];

extern const ANIME	ENEMY_KE_F[];

extern const ANIME	ENEMY_KN_F[];
extern const ANIME	ENEMY_KN_R[];
extern const ANIME	ENEMY_KN_ATK_F[];
extern const ANIME	ENEMY_KN_ATK_R[];
extern const ANIME	ENEMY_KN_DAM[];

extern const ANIME	ENEMY_GO_F[];
extern const ANIME	ENEMY_GO_R[];
extern const ANIME	ENEMY_GO_ATK_F[];
extern const ANIME	ENEMY_GO_ATK_R[];
extern const ANIME	ENEMY_GO_DAM[];

extern const ANIME	ENEMY_DO_F[];
extern const ANIME	ENEMY_DO_R[];
extern const ANIME	ENEMY_DO_ATK_F[];
extern const ANIME	ENEMY_DO_ATK_R[];
extern const ANIME	ENEMY_DO_DAM[];

extern const ANIME	ENEMY_KO_F[];
extern const ANIME	ENEMY_KO_R[];
extern const ANIME	ENEMY_KO_ATK_F[];
extern const ANIME	ENEMY_KO_ATK_R[];
extern const ANIME	ENEMY_KO_DAM[];

extern const ANIME	ENEMY_SA_F[];
extern const ANIME	ENEMY_SA_R[];
extern const ANIME	ENEMY_SA_ATK_F[];
extern const ANIME	ENEMY_SA_ATK_R[];
extern const ANIME	ENEMY_SA_DAM[];

// ボスデータ
extern const ANIME	KNIGHT_STAND[];
extern const ANIME	KNIGHT_ATK[];

// アイテム
extern const ANIME	COIN_ANIME[];

// *** 敵エフェクト
extern const ANIME	ENEMY_GO_SHOT_S[];
extern const ANIME	ENEMY_GO_SHOT_B[];
extern const ANIME	ENEMY_RF_SHOT[];

// エフェクトデータ
extern const ANIME	EFFECT_DAMAGE[];
extern const ANIME	EFFECT_SMOKE[];
extern const ANIME	MG_SHOT_S[];
extern const ANIME	MG_SHOT_B[];
extern const ANIME	MG_SKILL_EF[];
extern const ANIME	MG_SPECIAL_EF_R[];
extern const ANIME	MG_SPECIAL_EF_L[];
extern const ANIME	PW_SPECIAL_EF[];
extern const ANIME	SP_SPECIAL_EF_F[];
extern const ANIME	SP_SPECIAL_EF_S[];
extern const ANIME	SP_SPECIAL_EF_R[];
extern const ANIME	PT_FIRE_F[];
extern const ANIME	PT_FIRE_S[];
extern const ANIME	PT_FIRE_R[];
extern const ANIME	SPLASH_EF_F[];
extern const ANIME	SPLASH_EF_S[];
extern const ANIME	SPLASH_EF_R[];

// キャラセレクト用データ
extern const ANIME	SELECT_BEAST[];
extern const ANIME	SELECT_MAGIC[];
extern const ANIME	SELECT_PETIT[];
extern const ANIME	SELECT_POWER[];
extern const ANIME	SELECT_SPEED[];

// 順位表示文字
extern const ANIME	RANK1[];
extern const ANIME	RANK2[];
extern const ANIME	RANK3[];
extern const ANIME	RANK4[];

// 結果発表画面で勝利プレイヤーを宣言するときに使用 パレットは共通
extern const u8		player1_logo_Char[];
extern const u8		player2_logo_Char[];
extern const u8		player3_logo_Char[];
extern const u8		player4_logo_Char[];

// BGアニメ 必殺エフェクト
extern const BG_ANIME	SPECIAL_FLASH_BG[];


// ======= グラフィックデータの外部参照宣言部 ======= E