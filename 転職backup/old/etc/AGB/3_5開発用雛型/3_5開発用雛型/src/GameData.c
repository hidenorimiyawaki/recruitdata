//**************************************************************************** S
//
//	 ソース名称		:	GameData.c
//
//==============================================================================
//	 コメント		:	外部データの読み込み（主にグラフィックデータ）
//						同時に、global.hでextern宣言を行うこと
//	 最終更新日		:	2002/10/27 (Sun)
//**************************************************************************** E
#include	<agb.h>

// ここで外部データを読み込む

// *********************** 背景データ ************************ S
#include	"..\image\bg_woods.c"
#include	"..\image\bg_woods_main.c"
#include	"..\image\game_over_logo.c"			// エンド

// *********************** 背景データ ************************ E


// ******************** スプライトデータ ********************* S
#include	"..\image\Palette.c"				// パレット
#include	"..\image\system.c"					// 文字フォントデータ 背景フォントにも共用

#include	"..\image\select\select_beast.c"	// キャラクターセレクト用のキャラクター
#include	"..\image\select\select_power.c"
#include	"..\image\select\select_magic.c"
#include	"..\image\select\select_petit.c"
#include	"..\image\select\select_speed.c"


// ************* プレイヤー ************** S

#include	"..\image\speed\sp_01_f.c"			// スピード
#include	"..\image\speed\sp_01_s.c"
#include	"..\image\speed\sp_01_r.c"

#include	"..\image\speed\sp_11_f.c"
#include	"..\image\speed\sp_12_f.c"
#include	"..\image\speed\sp_13_f.c"
#include	"..\image\speed\sp_14_f.c"

#include	"..\image\speed\sp_11_s.c"
#include	"..\image\speed\sp_12_s.c"
#include	"..\image\speed\sp_13_s.c"
#include	"..\image\speed\sp_14_s.c"

#include	"..\image\speed\sp_11_r.c"
#include	"..\image\speed\sp_12_r.c"
#include	"..\image\speed\sp_13_r.c"
#include	"..\image\speed\sp_14_r.c"

#include	"..\image\speed\sp_21_f.c"
#include	"..\image\speed\sp_22_f.c"
#include	"..\image\speed\sp_23_f.c"
#include	"..\image\speed\sp_24_f.c"
#include	"..\image\speed\sp_25_f.c"
#include	"..\image\speed\sp_26_f.c"
#include	"..\image\speed\sp_27_f.c"

#include	"..\image\speed\sp_21_s.c"
#include	"..\image\speed\sp_22_s.c"
#include	"..\image\speed\sp_23_s.c"
#include	"..\image\speed\sp_24_s.c"
#include	"..\image\speed\sp_25_s.c"
#include	"..\image\speed\sp_26_s.c"
#include	"..\image\speed\sp_27_s.c"
#include	"..\image\speed\sp_28_s.c"

#include	"..\image\speed\sp_21_r.c"
#include	"..\image\speed\sp_22_r.c"
#include	"..\image\speed\sp_23_r.c"
#include	"..\image\speed\sp_24_r.c"
#include	"..\image\speed\sp_25_r.c"
#include	"..\image\speed\sp_26_r.c"
#include	"..\image\speed\sp_27_r.c"
#include	"..\image\speed\sp_28_r.c"

#include	"..\image\speed\sp_31_f.c"
#include	"..\image\speed\sp_32_f.c"
#include	"..\image\speed\sp_33_f.c"
#include	"..\image\speed\sp_34_f.c"
#include	"..\image\speed\sp_35_f.c"

#include	"..\image\speed\sp_31_s.c"
#include	"..\image\speed\sp_32_s.c"
#include	"..\image\speed\sp_33_s.c"
#include	"..\image\speed\sp_34_s.c"
#include	"..\image\speed\sp_35_s.c"

#include	"..\image\speed\sp_31_r.c"
#include	"..\image\speed\sp_32_r.c"
#include	"..\image\speed\sp_33_r.c"
#include	"..\image\speed\sp_34_r.c"
#include	"..\image\speed\sp_35_r.c"

#include	"..\image\speed\sp_41_f.c"
#include	"..\image\speed\sp_42_f.c"
#include	"..\image\speed\sp_43_f.c"
#include	"..\image\speed\sp_44_f.c"

#include	"..\image\speed\sp_41_s.c"
#include	"..\image\speed\sp_42_s.c"
#include	"..\image\speed\sp_43_s.c"
#include	"..\image\speed\sp_44_s.c"

#include	"..\image\speed\sp_41_r.c"
#include	"..\image\speed\sp_42_r.c"
#include	"..\image\speed\sp_43_r.c"
#include	"..\image\speed\sp_44_r.c"

#include	"..\image\speed\sp_51_f.c"
#include	"..\image\speed\sp_51_s.c"
#include	"..\image\speed\sp_51_r.c"

#include	"..\image\speed\sp_61_f.c"
#include	"..\image\speed\sp_62_f.c"
#include	"..\image\speed\sp_63_f.c"

#include	"..\image\speed\sp_61_s.c"
#include	"..\image\speed\sp_62_s.c"
#include	"..\image\speed\sp_63_s.c"

#include	"..\image\speed\sp_61_r.c"
#include	"..\image\speed\sp_62_r.c"
#include	"..\image\speed\sp_63_r.c"

#include	"..\image\speed\sp_90_f.c"


#include	"..\image\magic\mg_01_f.c"			// マジシャン
#include	"..\image\magic\mg_01_s.c"
#include	"..\image\magic\mg_01_r.c"

#include	"..\image\magic\mg_11_f.c"
#include	"..\image\magic\mg_12_f.c"
#include	"..\image\magic\mg_13_f.c"
#include	"..\image\magic\mg_14_f.c"

#include	"..\image\magic\mg_11_s.c"
#include	"..\image\magic\mg_12_s.c"
#include	"..\image\magic\mg_13_s.c"
#include	"..\image\magic\mg_14_s.c"

#include	"..\image\magic\mg_11_r.c"
#include	"..\image\magic\mg_12_r.c"
#include	"..\image\magic\mg_13_r.c"
#include	"..\image\magic\mg_14_r.c"

#include	"..\image\magic\mg_21_f.c"
#include	"..\image\magic\mg_22_f.c"
#include	"..\image\magic\mg_23_f.c"
#include	"..\image\magic\mg_24_f.c"

#include	"..\image\magic\mg_21_s.c"
#include	"..\image\magic\mg_22_s.c"
#include	"..\image\magic\mg_23_s.c"
#include	"..\image\magic\mg_24_s.c"

#include	"..\image\magic\mg_21_r.c"
#include	"..\image\magic\mg_22_r.c"
#include	"..\image\magic\mg_23_r.c"
#include	"..\image\magic\mg_24_r.c"

#include	"..\image\magic\mg_31_f.c"
#include	"..\image\magic\mg_32_f.c"
#include	"..\image\magic\mg_33_f.c"

#include	"..\image\magic\mg_31_s.c"
#include	"..\image\magic\mg_32_s.c"
#include	"..\image\magic\mg_33_s.c"

#include	"..\image\magic\mg_31_r.c"
#include	"..\image\magic\mg_32_r.c"
#include	"..\image\magic\mg_33_r.c"

#include	"..\image\magic\mg_41_f.c"
#include	"..\image\magic\mg_42_f.c"
#include	"..\image\magic\mg_43_f.c"
#include	"..\image\magic\mg_44_f.c"
#include	"..\image\magic\mg_45_f.c"

#include	"..\image\magic\mg_51_f.c"
#include	"..\image\magic\mg_51_s.c"
#include	"..\image\magic\mg_51_r.c"

#include	"..\image\magic\mg_61_f.c"
#include	"..\image\magic\mg_62_f.c"
#include	"..\image\magic\mg_63_f.c"
#include	"..\image\magic\mg_64_f.c"
#include	"..\image\magic\mg_65_f.c"

#include	"..\image\magic\mg_90_f.c"


#include	"..\image\petit\pt_01_f.c"			// プチ
#include	"..\image\petit\pt_01_s.c"
#include	"..\image\petit\pt_01_r.c"

#include	"..\image\petit\pt_11_f.c"
#include	"..\image\petit\pt_12_f.c"
#include	"..\image\petit\pt_13_f.c"
#include	"..\image\petit\pt_14_f.c"

#include	"..\image\petit\pt_11_s.c"
#include	"..\image\petit\pt_12_s.c"
#include	"..\image\petit\pt_13_s.c"
#include	"..\image\petit\pt_14_s.c"

#include	"..\image\petit\pt_11_r.c"
#include	"..\image\petit\pt_12_r.c"
#include	"..\image\petit\pt_13_r.c"
#include	"..\image\petit\pt_14_r.c"

#include	"..\image\petit\pt_21_f.c"
#include	"..\image\petit\pt_22_f.c"
#include	"..\image\petit\pt_23_f.c"

#include	"..\image\petit\pt_21_s.c"
#include	"..\image\petit\pt_22_s.c"
#include	"..\image\petit\pt_23_s.c"

#include	"..\image\petit\pt_21_r.c"
#include	"..\image\petit\pt_22_r.c"
#include	"..\image\petit\pt_23_r.c"

#include	"..\image\petit\pt_31_f.c"
#include	"..\image\petit\pt_32_f.c"
#include	"..\image\petit\pt_33_f.c"

#include	"..\image\petit\pt_31_s.c"
#include	"..\image\petit\pt_32_s.c"
#include	"..\image\petit\pt_33_s.c"

#include	"..\image\petit\pt_31_r.c"
#include	"..\image\petit\pt_32_r.c"
#include	"..\image\petit\pt_33_r.c"

#include	"..\image\petit\pt_41_f.c"
#include	"..\image\petit\pt_42_f.c"

#include	"..\image\petit\pt_41_s.c"
#include	"..\image\petit\pt_42_s.c"

#include	"..\image\petit\pt_41_r.c"
#include	"..\image\petit\pt_42_r.c"

#include	"..\image\petit\pt_51_f.c"
#include	"..\image\petit\pt_51_s.c"
#include	"..\image\petit\pt_51_r.c"

#include	"..\image\petit\pt_61_f.c"
#include	"..\image\petit\pt_62_f.c"
#include	"..\image\petit\pt_63_f.c"

#include	"..\image\petit\pt_90_f.c"


#include	"..\image\beast\bs_01_f.c"			// ビースト
#include	"..\image\beast\bs_01_s.c"
#include	"..\image\beast\bs_01_r.c"

#include	"..\image\beast\bs_11_f.c"
#include	"..\image\beast\bs_12_f.c"
#include	"..\image\beast\bs_13_f.c"
#include	"..\image\beast\bs_14_f.c"

#include	"..\image\beast\bs_11_s.c"
#include	"..\image\beast\bs_12_s.c"
#include	"..\image\beast\bs_13_s.c"
#include	"..\image\beast\bs_14_s.c"

#include	"..\image\beast\bs_11_r.c"
#include	"..\image\beast\bs_12_r.c"
#include	"..\image\beast\bs_13_r.c"
#include	"..\image\beast\bs_14_r.c"

#include	"..\image\beast\bs_21_f.c"
#include	"..\image\beast\bs_22_f.c"
#include	"..\image\beast\bs_23_f.c"
#include	"..\image\beast\bs_24_f.c"
#include	"..\image\beast\bs_25_f.c"
#include	"..\image\beast\bs_26_f.c"
#include	"..\image\beast\bs_27_f.c"
#include	"..\image\beast\bs_28_f.c"
#include	"..\image\beast\bs_29_f.c"

#include	"..\image\beast\bs_21_s.c"
#include	"..\image\beast\bs_22_s.c"
#include	"..\image\beast\bs_23_s.c"
#include	"..\image\beast\bs_24_s.c"
#include	"..\image\beast\bs_25_s.c"
#include	"..\image\beast\bs_26_s.c"
#include	"..\image\beast\bs_27_s.c"
#include	"..\image\beast\bs_28_s.c"
#include	"..\image\beast\bs_29_s.c"

#include	"..\image\beast\bs_21_r.c"
#include	"..\image\beast\bs_22_r.c"
#include	"..\image\beast\bs_23_r.c"
#include	"..\image\beast\bs_24_r.c"
#include	"..\image\beast\bs_25_r.c"
#include	"..\image\beast\bs_26_r.c"
#include	"..\image\beast\bs_27_r.c"
#include	"..\image\beast\bs_28_r.c"
#include	"..\image\beast\bs_29_r.c"

#include	"..\image\beast\bs_31_f.c"
#include	"..\image\beast\bs_32_f.c"
#include	"..\image\beast\bs_33_f.c"

#include	"..\image\beast\bs_31_s.c"
#include	"..\image\beast\bs_32_s.c"
#include	"..\image\beast\bs_33_s.c"

#include	"..\image\beast\bs_31_r.c"
#include	"..\image\beast\bs_32_r.c"
#include	"..\image\beast\bs_33_r.c"

#include	"..\image\beast\bs_41_f.c"
#include	"..\image\beast\bs_42_f.c"
#include	"..\image\beast\bs_43_f.c"

#include	"..\image\beast\bs_41_s.c"
#include	"..\image\beast\bs_42_s.c"
#include	"..\image\beast\bs_43_s.c"

#include	"..\image\beast\bs_41_r.c"
#include	"..\image\beast\bs_42_r.c"
#include	"..\image\beast\bs_43_r.c"

#include	"..\image\beast\bs_51_f.c"
#include	"..\image\beast\bs_51_s.c"
#include	"..\image\beast\bs_51_r.c"

#include	"..\image\beast\bs_61_f.c"
#include	"..\image\beast\bs_62_f.c"
#include	"..\image\beast\bs_63_f.c"
#include	"..\image\beast\bs_64_f.c"
#include	"..\image\beast\bs_65_f.c"

#include	"..\image\beast\bs_90_f.c"


#include	"..\image\power\pw_01_f.c"			// パワー
#include	"..\image\power\pw_01_s.c"
#include	"..\image\power\pw_01_r.c"

#include	"..\image\power\pw_11_f.c"
#include	"..\image\power\pw_12_f.c"
#include	"..\image\power\pw_13_f.c"
#include	"..\image\power\pw_14_f.c"

#include	"..\image\power\pw_11_s.c"
#include	"..\image\power\pw_12_s.c"
#include	"..\image\power\pw_13_s.c"
#include	"..\image\power\pw_14_s.c"

#include	"..\image\power\pw_11_r.c"
#include	"..\image\power\pw_12_r.c"
#include	"..\image\power\pw_13_r.c"
#include	"..\image\power\pw_14_r.c"

#include	"..\image\power\pw_21_f.c"
#include	"..\image\power\pw_22_f.c"
#include	"..\image\power\pw_23_f.c"
#include	"..\image\power\pw_24_f.c"

#include	"..\image\power\pw_21_s.c"
#include	"..\image\power\pw_22_s.c"
#include	"..\image\power\pw_23_s.c"
#include	"..\image\power\pw_24_s.c"

#include	"..\image\power\pw_21_r.c"
#include	"..\image\power\pw_22_r.c"
#include	"..\image\power\pw_23_r.c"
#include	"..\image\power\pw_24_r.c"

#include	"..\image\power\pw_31_f.c"
#include	"..\image\power\pw_32_f.c"
#include	"..\image\power\pw_33_f.c"

#include	"..\image\power\pw_31_s.c"
#include	"..\image\power\pw_32_s.c"
#include	"..\image\power\pw_33_s.c"

#include	"..\image\power\pw_31_r.c"
#include	"..\image\power\pw_32_r.c"
#include	"..\image\power\pw_33_r.c"

#include	"..\image\power\pw_41_f.c"
#include	"..\image\power\pw_42_f.c"

#include	"..\image\power\pw_41_s.c"
#include	"..\image\power\pw_42_s.c"

#include	"..\image\power\pw_41_r.c"
#include	"..\image\power\pw_42_r.c"

#include	"..\image\power\pw_51_f.c"
#include	"..\image\power\pw_51_s.c"
#include	"..\image\power\pw_51_r.c"

#include	"..\image\power\pw_61_f.c"
#include	"..\image\power\pw_62_f.c"

#include	"..\image\power\pw_61_s.c"
#include	"..\image\power\pw_62_s.c"

#include	"..\image\power\pw_61_r.c"
#include	"..\image\power\pw_62_r.c"

#include	"..\image\power\pw_90_f.c"


// ************* プレイヤー ************** E


// *********** 敵キャラクター ************ S

#include	"..\image\enemy\slime\sl_01_f.c"			// スライム
#include	"..\image\enemy\slime\sl_02_f.c"
#include	"..\image\enemy\slime\sl_03_f.c"
#include	"..\image\enemy\slime\sl_04_f.c"
#include	"..\image\enemy\slime\sl_21.c"

#include	"..\image\enemy\nuu\nu_01_f.c"				// ヌー
#include	"..\image\enemy\nuu\nu_02_f.c"
#include	"..\image\enemy\nuu\nu_01_r.c"
#include	"..\image\enemy\nuu\nu_02_r.c"
#include	"..\image\enemy\nuu\nu_11_f.c"
#include	"..\image\enemy\nuu\nu_12_f.c"
#include	"..\image\enemy\nuu\nu_11_r.c"
#include	"..\image\enemy\nuu\nu_12_r.c"
#include	"..\image\enemy\nuu\nu_21.c"

#include	"..\image\enemy\rafury\rf_01_f.c"			// ラフリー
#include	"..\image\enemy\rafury\rf_02_f.c"
#include	"..\image\enemy\rafury\rf_03_f.c"
#include	"..\image\enemy\rafury\rf_01_r.c"
#include	"..\image\enemy\rafury\rf_02_r.c"
#include	"..\image\enemy\rafury\rf_03_r.c"
#include	"..\image\enemy\rafury\rf_11.c"
#include	"..\image\enemy\rafury\rf_12.c"
#include	"..\image\enemy\rafury\rf_21.c"
#include	"..\image\enemy\rafury\rf_31.c"
#include	"..\image\enemy\rafury\rf_32.c"
#include	"..\image\enemy\rafury\rf_33.c"
#include	"..\image\enemy\rafury\rf_34.c"
#include	"..\image\enemy\rafury\rf_35.c"
#include	"..\image\enemy\rafury\rf_36.c"
#include	"..\image\enemy\rafury\rf_37.c"

#include	"..\image\enemy\usa\us_01_f.c"				// ウサ
#include	"..\image\enemy\usa\us_02_f.c"
#include	"..\image\enemy\usa\us_03_f.c"
#include	"..\image\enemy\usa\us_01_r.c"
#include	"..\image\enemy\usa\us_02_r.c"
#include	"..\image\enemy\usa\us_03_r.c"
#include	"..\image\enemy\usa\us_11_f.c"
#include	"..\image\enemy\usa\us_11_r.c"
#include	"..\image\enemy\usa\us_21.c"

#include	"..\image\enemy\purazuma\pz_01_f.c"		// プラズマー
#include	"..\image\enemy\purazuma\pz_02_f.c"
#include	"..\image\enemy\purazuma\pz_03_f.c"
#include	"..\image\enemy\purazuma\pz_04_f.c"
#include	"..\image\enemy\purazuma\pz_01_r.c"
#include	"..\image\enemy\purazuma\pz_02_r.c"
#include	"..\image\enemy\purazuma\pz_03_r.c"
#include	"..\image\enemy\purazuma\pz_04_r.c"
#include	"..\image\enemy\purazuma\pz_11_f.c"
#include	"..\image\enemy\purazuma\pz_12_f.c"
#include	"..\image\enemy\purazuma\pz_13_f.c"
#include	"..\image\enemy\purazuma\pz_11_r.c"
#include	"..\image\enemy\purazuma\pz_12_r.c"
#include	"..\image\enemy\purazuma\pz_13_r.c"
#include	"..\image\enemy\purazuma\pz_21.c"

#include	"..\image\enemy\uni\ui_01_f.c"				// ウニ
#include	"..\image\enemy\uni\ui_02_f.c"
#include	"..\image\enemy\uni\ui_03_f.c"
#include	"..\image\enemy\uni\ui_01_r.c"
#include	"..\image\enemy\uni\ui_02_r.c"
#include	"..\image\enemy\uni\ui_03_r.c"
#include	"..\image\enemy\uni\ui_04_f.c"
#include	"..\image\enemy\uni\ui_04_r.c"
#include	"..\image\enemy\uni\ui_11_f.c"
#include	"..\image\enemy\uni\ui_12_f.c"
#include	"..\image\enemy\uni\ui_13_f.c"
#include	"..\image\enemy\uni\ui_14_f.c"
#include	"..\image\enemy\uni\ui_15_f.c"
#include	"..\image\enemy\uni\ui_11_r.c"
#include	"..\image\enemy\uni\ui_12_r.c"
#include	"..\image\enemy\uni\ui_13_r.c"
#include	"..\image\enemy\uni\ui_14_r.c"
#include	"..\image\enemy\uni\ui_15_r.c"
#include	"..\image\enemy\uni\ui_21.c"

#include	"..\image\enemy\tori\tr_01_f.c"				// トリ
#include	"..\image\enemy\tori\tr_02_f.c"
#include	"..\image\enemy\tori\tr_03_f.c"
#include	"..\image\enemy\tori\tr_01_r.c"
#include	"..\image\enemy\tori\tr_02_r.c"
#include	"..\image\enemy\tori\tr_03_r.c"
#include	"..\image\enemy\tori\tr_11_f.c"
#include	"..\image\enemy\tori\tr_12_f.c"
#include	"..\image\enemy\tori\tr_13_f.c"
#include	"..\image\enemy\tori\tr_14_f.c"
#include	"..\image\enemy\tori\tr_15_f.c"
#include	"..\image\enemy\tori\tr_16_f.c"
#include	"..\image\enemy\tori\tr_11_r.c"
#include	"..\image\enemy\tori\tr_12_r.c"
#include	"..\image\enemy\tori\tr_13_r.c"
#include	"..\image\enemy\tori\tr_14_r.c"
#include	"..\image\enemy\tori\tr_15_r.c"
#include	"..\image\enemy\tori\tr_16_r.c"
#include	"..\image\enemy\tori\tr_21.c"

#include	"..\image\enemy\kaeru\ke_01_f.c"			// カエル
#include	"..\image\enemy\kaeru\ke_02_f.c"
#include	"..\image\enemy\kaeru\ke_03_f.c"

#include	"..\image\enemy\kinoko\kn_01_f.c"			// キノコ
#include	"..\image\enemy\kinoko\kn_02_f.c"
#include	"..\image\enemy\kinoko\kn_03_f.c"
#include	"..\image\enemy\kinoko\kn_01_r.c"
#include	"..\image\enemy\kinoko\kn_02_r.c"
#include	"..\image\enemy\kinoko\kn_03_r.c"
#include	"..\image\enemy\kinoko\kn_11_f.c"
#include	"..\image\enemy\kinoko\kn_12_f.c"
#include	"..\image\enemy\kinoko\kn_13_f.c"
#include	"..\image\enemy\kinoko\kn_14_f.c"
#include	"..\image\enemy\kinoko\kn_15_f.c"
#include	"..\image\enemy\kinoko\kn_16_f.c"
#include	"..\image\enemy\kinoko\kn_11_r.c"
#include	"..\image\enemy\kinoko\kn_12_r.c"
#include	"..\image\enemy\kinoko\kn_13_r.c"
#include	"..\image\enemy\kinoko\kn_14_r.c"
#include	"..\image\enemy\kinoko\kn_15_r.c"
#include	"..\image\enemy\kinoko\kn_16_r.c"
#include	"..\image\enemy\kinoko\kn_21.c"

#include	"..\image\enemy\gosuto\go_01_f.c"			// ゴースト
#include	"..\image\enemy\gosuto\go_02_f.c"
#include	"..\image\enemy\gosuto\go_03_f.c"
#include	"..\image\enemy\gosuto\go_04_f.c"
#include	"..\image\enemy\gosuto\go_01_r.c"
#include	"..\image\enemy\gosuto\go_02_r.c"
#include	"..\image\enemy\gosuto\go_03_r.c"
#include	"..\image\enemy\gosuto\go_04_r.c"
#include	"..\image\enemy\gosuto\go_11_f.c"
#include	"..\image\enemy\gosuto\go_12_f.c"
#include	"..\image\enemy\gosuto\go_13_f.c"
#include	"..\image\enemy\gosuto\go_14_f.c"
#include	"..\image\enemy\gosuto\go_11_r.c"
#include	"..\image\enemy\gosuto\go_12_r.c"
#include	"..\image\enemy\gosuto\go_13_r.c"
#include	"..\image\enemy\gosuto\go_14_r.c"
#include	"..\image\enemy\gosuto\go_21.c"

#include	"..\image\enemy\dom\do_01_f.c"				// ドム
#include	"..\image\enemy\dom\do_02_f.c"
#include	"..\image\enemy\dom\do_03_f.c"
#include	"..\image\enemy\dom\do_01_r.c"
#include	"..\image\enemy\dom\do_02_r.c"
#include	"..\image\enemy\dom\do_03_r.c"
#include	"..\image\enemy\dom\do_11_f.c"
#include	"..\image\enemy\dom\do_12_f.c"
#include	"..\image\enemy\dom\do_13_f.c"
#include	"..\image\enemy\dom\do_14_f.c"
#include	"..\image\enemy\dom\do_11_r.c"
#include	"..\image\enemy\dom\do_12_r.c"
#include	"..\image\enemy\dom\do_13_r.c"
#include	"..\image\enemy\dom\do_14_r.c"
#include	"..\image\enemy\dom\do_21.c"

#include	"..\image\enemy\koumori\ko_01_f.c"				// コウモリ
#include	"..\image\enemy\koumori\ko_02_f.c"
#include	"..\image\enemy\koumori\ko_03_f.c"
#include	"..\image\enemy\koumori\ko_01_r.c"
#include	"..\image\enemy\koumori\ko_02_r.c"
#include	"..\image\enemy\koumori\ko_03_r.c"
#include	"..\image\enemy\koumori\ko_11_f.c"
#include	"..\image\enemy\koumori\ko_12_f.c"
#include	"..\image\enemy\koumori\ko_13_f.c"
#include	"..\image\enemy\koumori\ko_14_f.c"
#include	"..\image\enemy\koumori\ko_15_f.c"
#include	"..\image\enemy\koumori\ko_16_f.c"
#include	"..\image\enemy\koumori\ko_17_f.c"
#include	"..\image\enemy\koumori\ko_11_r.c"
#include	"..\image\enemy\koumori\ko_12_r.c"
#include	"..\image\enemy\koumori\ko_13_r.c"
#include	"..\image\enemy\koumori\ko_14_r.c"
#include	"..\image\enemy\koumori\ko_15_r.c"
#include	"..\image\enemy\koumori\ko_16_r.c"
#include	"..\image\enemy\koumori\ko_17_r.c"
#include	"..\image\enemy\koumori\ko_21.c"

#include	"..\image\enemy\sasori\sa_01_f.c"				// サソリ
#include	"..\image\enemy\sasori\sa_02_f.c"
#include	"..\image\enemy\sasori\sa_03_f.c"
#include	"..\image\enemy\sasori\sa_01_r.c"
#include	"..\image\enemy\sasori\sa_02_r.c"
#include	"..\image\enemy\sasori\sa_03_r.c"
#include	"..\image\enemy\sasori\sa_11_f.c"
#include	"..\image\enemy\sasori\sa_12_f.c"
#include	"..\image\enemy\sasori\sa_13_f.c"
#include	"..\image\enemy\sasori\sa_11_r.c"
#include	"..\image\enemy\sasori\sa_12_r.c"
#include	"..\image\enemy\sasori\sa_13_r.c"
#include	"..\image\enemy\sasori\sa_21.c"

// 敵エフェクト
#include	"..\image\enemy_ef\go_shot_01.c"				// ゴースト魂エフェクト
#include	"..\image\enemy_ef\go_shot_02.c"
#include	"..\image\enemy_ef\go_shot_11.c"
#include	"..\image\enemy_ef\go_shot_12.c"
#include	"..\image\enemy_ef\go_shot_13.c"

#include	"..\image\enemy_ef\rf_shot_01.c"				// ラフリー種エフェクト
#include	"..\image\enemy_ef\rf_shot_02.c"
#include	"..\image\enemy_ef\rf_shot_03.c"
#include	"..\image\enemy_ef\rf_shot_04.c"

//************* エフェクト ***************
#include	"..\image\effects\dmg_ef\dmg_ef_01.c"
#include	"..\image\effects\dmg_ef\dmg_ef_02.c"
#include	"..\image\effects\dmg_ef\dmg_ef_03.c"
#include	"..\image\effects\dmg_ef\dmg_ef_04.c"

#include	"..\image\effects\smk_ef\smk_ef_01.c"
#include	"..\image\effects\smk_ef\smk_ef_02.c"
#include	"..\image\effects\smk_ef\smk_ef_03.c"
#include	"..\image\effects\smk_ef\smk_ef_04.c"

#include	"..\image\effects\mg_shot\mg_shot_01.c"		// マジのショット
#include	"..\image\effects\mg_shot\mg_shot_02.c"
#include	"..\image\effects\mg_shot\mg_shot_03.c"

#include	"..\image\effects\mg_shot\mg_shot_11.c"		// マジのショット命中
#include	"..\image\effects\mg_shot\mg_shot_12.c"
#include	"..\image\effects\mg_shot\mg_shot_13.c"
#include	"..\image\effects\mg_shot\mg_shot_14.c"

#include	"..\image\effects\mg_shot\mg_skill_ef_01.c"		// マジのスキルエフェクト
#include	"..\image\effects\mg_shot\mg_skill_ef_02.c"
#include	"..\image\effects\mg_shot\mg_skill_ef_03.c"
#include	"..\image\effects\mg_shot\mg_skill_ef_04.c"

#include	"..\image\effects\special_ef\mg_special_ef_01.c"		// マジの特殊技エフェクト
#include	"..\image\effects\special_ef\mg_special_ef_02.c"
#include	"..\image\effects\special_ef\mg_special_ef_03.c"
#include	"..\image\effects\special_ef\mg_special_ef_04.c"
#include	"..\image\effects\special_ef\mg_special_ef_05.c"
#include	"..\image\effects\special_ef\mg_special_ef_06.c"

#include	"..\image\effects\special_ef\pw_special_ef_01.c"		// パワーの特殊技エフェクト
#include	"..\image\effects\special_ef\pw_special_ef_02.c"
#include	"..\image\effects\special_ef\pw_special_ef_03.c"
#include	"..\image\effects\special_ef\pw_special_ef_04.c"

#include	"..\image\effects\special_ef\sp_special_ef_01_f.c"		// スピードの前特殊技エフェクト
#include	"..\image\effects\special_ef\sp_special_ef_02_f.c"
#include	"..\image\effects\special_ef\sp_special_ef_03_f.c"

#include	"..\image\effects\special_ef\sp_special_ef_01_s.c"		// スピードの横特殊技エフェクト
#include	"..\image\effects\special_ef\sp_special_ef_02_s.c"
#include	"..\image\effects\special_ef\sp_special_ef_03_s.c"

#include	"..\image\effects\special_ef\sp_special_ef_01_r.c"		// スピードの後特殊技エフェクト
#include	"..\image\effects\special_ef\sp_special_ef_02_r.c"
#include	"..\image\effects\special_ef\sp_special_ef_03_r.c"

#include	"..\image\effects\special_ef\special_flash_01.c"		// フラッシュエフェクト
#include	"..\image\effects\special_ef\special_flash_02.c"
#include	"..\image\effects\special_ef\special_flash_03.c"
#include	"..\image\effects\special_ef\special_flash_04.c"
#include	"..\image\effects\special_ef\special_flash_05.c"
#include	"..\image\effects\special_ef\special_flash_06.c"

#include	"..\image\effects\special_ef\fire_01.c"		// プチのファイア
#include	"..\image\effects\special_ef\fire_02.c"
#include	"..\image\effects\special_ef\fire_03.c"
#include	"..\image\effects\special_ef\fire_04.c"

#include	"..\image\effects\splash_ef\splash_ef_01.c"		// スプラッシュエフェクト
#include	"..\image\effects\splash_ef\splash_ef_02.c"
#include	"..\image\effects\splash_ef\splash_ef_03.c"
#include	"..\image\effects\splash_ef\splash_ef_04.c"

#include	"..\image\boss\knight\knight_01.c"
#include	"..\image\boss\knight\knight_02.c"
#include	"..\image\boss\knight\knight_03.c"
#include	"..\image\boss\knight\knight_10.c"
#include	"..\image\boss\knight\knight_11.c"
#include	"..\image\boss\knight\knight_12.c"
#include	"..\image\boss\knight\knight_13.c"
#include	"..\image\boss\knight\knight_12_half.c"
#include	"..\image\boss\knight\knight_13_half.c"

#include	"..\image\boss\kani\kani_arm_l_01.c"
#include	"..\image\boss\kani\kani_arm_l_02.c"
#include	"..\image\boss\kani\kani_arm_l_03.c"
#include	"..\image\boss\kani\kani_arm_r_01.c"
#include	"..\image\boss\kani\kani_arm_r_02.c"
#include	"..\image\boss\kani\kani_arm_r_03.c"
#include	"..\image\boss\kani\kani_body.c"
#include	"..\image\boss\kani\kani_leg_l_01.c"
#include	"..\image\boss\kani\kani_leg_l_02.c"
#include	"..\image\boss\kani\kani_leg_l_03.c"
#include	"..\image\boss\kani\kani_leg_l_04.c"
#include	"..\image\boss\kani\kani_leg_r_01.c"
#include	"..\image\boss\kani\kani_leg_r_02.c"
#include	"..\image\boss\kani\kani_leg_r_03.c"
#include	"..\image\boss\kani\kani_leg_r_04.c"


//************* その他 ********************
#include	"..\image\other\e_bar_proto.c"

#include	"..\image\items\coin_small_01.c"
#include	"..\image\items\coin_small_02.c"
#include	"..\image\items\coin_small_03.c"
#include	"..\image\items\coin_small_04.c"


//************* スプライトデータ****************E