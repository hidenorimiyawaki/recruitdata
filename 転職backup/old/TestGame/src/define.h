/************************************************************
*						DEFINE.H							*
*															*
*		このファイルでは、定数定義をします。				*
*															*
************************************************************/
#ifndef	___DEFINE_H___
#define	___DEFINE_H___

//------------------------	ゲームメインに関する定数定義　---------------------------------------S

#define CLASS_NAME			"quarrel bomber"				// ウィンドウクラス名
#define CAPTION_NAME		"quarrel bomber"				// キャプション名

#define RESOURCETYPE_WAVE	"WAVE"							// Waveデータのリソース・タイプ
#define RESOURCETYPE_MIDI	"MIDI"							// MIDIデータのリソース・タイプ

#define FRAME_RATE			1000/60							// フレームレート
#define SCREEN_WIDTH		640								// スクリーンの幅
#define SCREEN_HEIGHT		480								// スクリーンの高さ
#define ASPECT_RATIO		SCREEN_WIDTH/SCREEN_HEIGHT		// アスペクト比
#define FONT_SIZE			20								// デバッグ文字フォントサイズ
#define FONT_TYPE			"ＭＳ ゴシック"					// デバッグ文字フォント種別
#define NEAR_CLIP			(float)100.0					// ニアクリップを行う距離
#define FAR_CLIP			(float)30000.0					// ファークリップを行う距離
#define PI					3.141592653589					// 円周率
#define RAD					(float)PI/180					// ラジアン

#define ROTATE_SPEED		0.04							// 回転速度
#define MOVE_SPEED			10.0							// 移動速度
#define HIT_SIZE			40.0							// 当たり判定サイズ

#define	PLAYER_MOVE			15								// プレイヤーのオフセット

#define	PLAYER_RANGE_X		400								// プレイヤーの射程レンジX
#define	PLAYER_RANGE_Y		300								// プレイヤーの射程レンジY

#define	JUMP_MAX			20								// プレイヤーのジャンプカウント

#define BLOOD_MAX			50								// 血のエフェクトの最大数
#define SPARKS_MAX			40								// 爆発のエフェクトの最大数

#define TAMA_SIZE			64								// 弾のサイズ
#define BEAT_WAIT_TIME		90								// ビートカウントが変わるまでの時間

#define DEFAULT_PLAYER_X	0								// プレイヤーの開始時のオフセットのX座標
#define DEFAULT_PLAYER_Y	-300							// プレイヤーの開始時のオフセットのY座標
#define DEFAULT_PLAYER_Z	-5000							// プレイヤーの開始時のオフセットのZ座標

#define	YUKA_MAX			5								// 床モデルの最大値
#define ENEMY_MAX			5								// 敵キャラクターの最大数

#define FRAME_QTY			32								// バンクあたりフレーム数
#define BANK_QTY			32								// バンク数
#define TIME_MAX			1000							// フレームタイム上限値

#define ROT_MAX				314								// パーツ回転リミット値
#define POS_MAX				500								// パーツ座標リミット値

//------------------------	ゲームメインに関する定数定義　---------------------------------------E





//------------------------	テクスチャーに関する定数定義　---------------------------------------S

// ビルボード初期化構造体用参照データ
#define BORD_COUNTER1		0								// 数字カウントの一桁目用の絵
#define BORD_COUNTER2		BORD_COUNTER1 + 1				// 数字カウントの二桁目用の絵
#define BORD_COUNTER3		BORD_COUNTER2 + 1				// 数字カウントの三桁目用の絵
#define BORD_BEAT			BORD_COUNTER3 + 1				// 数字カウント用の文字用の絵（BEAT！！）
#define BORD_FIRE			BORD_BEAT + 1					// 炎の絵
#define BORD_BULLET			BORD_FIRE + 1					// 薬きょうの絵
#define BORD_TAMA			BORD_BULLET	 + 1				// 弾の絵
#define BORD_FLASH			BORD_TAMA + 1					// マズルフラッシュの絵
#define BORD_FLASH2			BORD_FLASH + 1					// マズルフラッシュ2の絵
#define BORD_BLOOD			BORD_FLASH2 + 1					// 血の絵
#define BORD_TITLE			BORD_BLOOD + 1					// タイトル絵
#define BORD_START			BORD_TITLE + 1					// satartの絵
#define BORD_OPTION			BORD_START + 1					// optionの絵
#define BORD_QUIT			BORD_OPTION + 1					// quitの絵
#define BORD_OPTIONBORD		BORD_QUIT + 1					// オプション絵
#define BORD_BLOODON		BORD_OPTIONBORD + 1				// ON(blood)の絵
#define BORD_BLOODOFF		BORD_BLOODON + 1				// OFF(blood)の絵
#define BORD_SHADOWON		BORD_BLOODOFF + 1				// ON(shadow)の絵
#define BORD_SHADOWOFF		BORD_SHADOWON + 1				// OFF(shadow)の絵
#define BORD_EXIT			BORD_SHADOWOFF + 1				// exitの絵
#define BORD_HP				BORD_EXIT + 1					// HPゲージの絵
#define BORD_GAMEOVER		BORD_HP + 1						// GAMEOVERの絵
#define BORD_GAMECLEAR		BORD_GAMEOVER + 1				// GAMECLEARの絵
#define BORD_READY			BORD_GAMECLEAR + 1				// READYの絵
#define BORD_GO				BORD_READY + 1					// GOの絵
#define BORD_GAUGE			BORD_GO + 1						// GAUGEの絵
#define BORD_BAR			BORD_GAUGE + 1					// BARの絵
#define BORD_SHADOW			BORD_BAR + 1					// SHADOWの絵
#define BORD_SCORE			BORD_SHADOW + 1					// SCOREの絵
#define BORD_TOTAL			BORD_SCORE + 1					// TOTALの絵
#define BORD_MAXHIT			BORD_TOTAL + 1					// MAXHITの絵
#define BORD_KAKE			BORD_MAXHIT	+ 1					// KAKEの絵
#define BORD_NUM			BORD_KAKE	+ 1					// NUMの絵
#define BORD_TIME			BORD_NUM	+ 1					// TIMEの絵


// 各テクスチャーのオフセットの参照データ
#define TEXOFFSET1_ONE		0								// 数字カウントの絵(1)
#define TEXOFFSET1_TWO		1								// 数字カウントの絵(2)
#define TEXOFFSET1_THREE	2								// 数字カウントの絵(3)
#define TEXOFFSET1_FOUR		3								// 数字カウントの絵(4)
#define TEXOFFSET1_FIVE		4								// 数字カウントの絵(5)
#define TEXOFFSET1_SIX		5								// 数字カウントの絵(6)
#define TEXOFFSET1_SEVEN	6								// 数字カウントの絵(7)
#define TEXOFFSET1_EIGHT	7								// 数字カウントの絵(8)
#define TEXOFFSET1_NINE		8								// 数字カウントの絵(9)
#define TEXOFFSET1_ZERO		9								// 数字カウントの絵(0)
#define TEXOFFSET1_BRANK	10								// 汎用的に使う空白の絵
#define TEXOFFSET1_BEAT		11								// 数字カウント用の文字用の絵（BEAT！！）
#define TEXOFFSET1_FIRE1	12								// 炎の絵(一コマ目)
#define TEXOFFSET1_FIRE2	13								// 炎の絵(二コマ目)
#define TEXOFFSET1_FIRE3	14								// 炎の絵(三コマ目)
#define TEXOFFSET1_BULLET	15								// 炎の絵(三コマ目)

#define TEXOFFSET2_TAMA		0								// 弾
#define TEXOFFSET2_FLASH	1								// マズルフラッシュ
#define TEXOFFSET2_FLASH2	2								// マズルフラッシュ2
#define TEXOFFSET2_BLOOD	3								// 血
#define TEXOFFSET2_SPARKS 	4								// 火の粉

#define TITLEOFFSET_TITLE	0								// タイトル絵
#define TITLEOFFSET_START	1								// start
#define TITLEOFFSET_OPTION	2								// option
#define TITLEOFFSET_QUIT	3								// quit

#define OPTIONOFFSET_OPTION	0								// メイン絵
#define OPTIONOFFSET_ON		1								// on
#define OPTIONOFFSET_OFF	2								// off
#define OPTIONOFFSET_EXIT	3								// exit

#define OTHEROFFSET_READY	0								// READY
#define OTHEROFFSET_GO		1								// GO!!
#define OTHEROFFSET_BAR		2								// LIFEバー
#define OTHEROFFSET_GAUGE	3								// LIFEゲージ

#define SCOREOFFSET_ZERO	0								// 数字カウントの絵(0)
#define SCOREOFFSET_ONE		1								// 数字カウントの絵(1)
#define SCOREOFFSET_TWO		2								// 数字カウントの絵(2)
#define SCOREOFFSET_THREE	3								// 数字カウントの絵(3)
#define SCOREOFFSET_FOUR	4								// 数字カウントの絵(4)
#define SCOREOFFSET_FIVE	5								// 数字カウントの絵(5)
#define SCOREOFFSET_SIX		6								// 数字カウントの絵(6)
#define SCOREOFFSET_SEVEN	7								// 数字カウントの絵(7)
#define SCOREOFFSET_EIGHT	8								// 数字カウントの絵(8)
#define SCOREOFFSET_NINE	9								// 数字カウントの絵(9)
#define SCOREOFFSET_SCORE	10								// スコアの絵
#define SCOREOFFSET_TOTAL	11								// トータルの絵
#define SCOREOFFSET_MAXHIT	12								// マックスヒットの絵
#define SCOREOFFSET_KAKE	13								// ×の絵
#define SCOREOFFSET_TIME	14								// TIMEの絵

//------------------------	テクスチャーに関する定数定義　---------------------------------------E





//------------------------	テクスチャーの表示オフセットに関する定数定義　-----------------------S

// 各テクスチャーの座標オフセット
#define POS_NUMERAL1_X		107								// 数字カウントの一桁目のX座標
#define POS_NUMERAL1_Y		220								// 数字カウントの一桁目のY座標

#define POS_NUMERAL2_X		137								// 数字カウントの二桁目のX座標
#define POS_NUMERAL2_Y		220								// 数字カウントの二桁目のY座標

#define POS_NUMERAL3_X		167								// 数字カウントの三桁目のX座標
#define POS_NUMERAL3_Y		220								// 数字カウントの三桁目のY座標

#define POS_BEAT_X			0								// BEATの絵のX座標
#define POS_BEAT_Y			220								// BEATの絵のY座標

#define POS_FIRE_X			20								// 炎エフェクトのX座標
#define POS_FIRE_Y			180								// 炎エフェクトのY座標

#define POS_START_X			280								// STARTのX座標
#define POS_START_Y			230								// STARTのY座標

#define POS_OPTION_X		270								// OPTIONのX座標
#define POS_OPTION_Y		140								// OPTIONのY座標

#define POS_QUIT_X			295								// QUITのX座標
#define POS_QUIT_Y			50								// QUITのY座標

#define POS_BLOOD_ON_X		250								// BLOOD用のONのX座標
#define POS_BLOOD_ON_Y		250								// BLOOD用のONのY座標

#define POS_BLOOD_OFF_X		50								// BLOOD用のOFFのX座標
#define POS_BLOOD_OFF_Y		250								// BLOOD用のOFFのY座標

#define POS_SHADOW_ON_X		250								// SHADOW用のONのX座標
#define POS_SHADOW_ON_Y		130								// SHADOW用のONのY座標

#define POS_SHADOW_OFF_X	50								// SHADOW用のOFFのX座標
#define POS_SHADOW_OFF_Y	130								// SHADOW用のOFFのX座標

#define POS_EXIT_X			300								// EXITのX座標
#define POS_EXIT_Y			50								// EXITのY座標

#define POS_HP_X			370								// HPのX座標
#define POS_HP_Y			440								// HPのY座標

#define POS_READY_X			110								// READYのX座標
#define POS_READY_Y			200								// READYのY座標

#define POS_GO_X			160								// GOのX座標
#define POS_GO_Y			200								// GOのY座標

#define POS_GAUGE_X			340								// HPゲージ枠のX座標
#define POS_GAUGE_Y			400								// HPゲージ枠のY座標

#define POS_BAR_X			POS_GAUGE_X	+ 18				// HPゲージのバーのX座標
#define POS_BAR_Y			POS_GAUGE_Y	+ 17				// HPゲージのバーのY座標

#define POS_SCORE_X			380								// SCOREのX座標
#define POS_SCORE_Y			300								// SCOREのY座標

#define POS_TOTAL_X			380								// TOTALのX座標
#define POS_TOTAL_Y			100								// TOTALのY座標

#define POS_MAXHIT_X		380								// MAXHITのX座標
#define POS_MAXHIT_Y		200								// MAXHITのY座標

#define START_CAMERA_Y		400								// ゲーム開始時のカメラのY座標
#define START_CAMERA_Z		-100							// ゲーム開始時のカメラのZ座標

#define SHADOW_OFFSET_X		250								// キャラクターから見た影に対するオフセットのX座標
#define SHADOW_OFFSET_Z		250								// キャラクターから見た影に対するオフセットのZ座標

//------------------------	テクスチャーの表示オフセットに関する定数定義　-----------------------E





//------------------------	テクスチャーの表示サイズに関する定数定義　---------------------------S

// テクスチャーの各サイズ(元の絵とずれたものとの修正データ)
#define HITFLASH_SIZE_X		100								// ダメージのエフェクトの横幅
#define HITFLASH_SIZE_Y		100								// ダメージのエフェクトの縦幅

#define MUZZLEFLASH_SIZE_X	128								// マズルフラッシュのエフェクトの横幅
#define MUZZLEFLASH_SIZE_Y	128								// マズルフラッシュのエフェクトの縦幅

#define BLOOD_SIZE_X		24								// エフェクトの血しぶき一粒の横幅
#define BLOOD_SIZE_Y		24								// エフェクトの血しぶき一粒の縦幅

#define SPARKS_SIZE_X		64								// 敵の爆発のエフェクトの横幅
#define SPARKS_SIZE_Y		64								// 敵の爆発のエフェクトの縦幅
	
//------------------------	テクスチャーの表示サイズに関する定数定義　---------------------------E





//------------------------	ビルボードのアニメーションに関する定数定義　-------------------------S

// ビルボードのアニメーションに関するデータ
#define ANIME_FIRE_MAX		3								// 炎のアニメーションの最大カウント数
#define ANIME_FIRE_FRAME	4								// 炎のアニメーションの表示フレーム数

#define ANIME_NUMERAL_MAX	10								// 数字のアニメーションの最大カウント数
#define ANIME_NUMERAL_FRAME	3								// 数字のアニメーションの表示フレーム数

//------------------------	ビルボードのアニメーションに関する定数定義　-------------------------E





//------------------------	モデルのデータに関する定数定義　-------------------------------------S

// モデルに関するデータ
#define	MODEL_MAX			3								// 固定モデルの取得最大数

#define PLAYER_MODEL		0								// 固定モデルとしてのプレイヤーモデルの参照値
#define ENEMY_MODEL			1								// 固定モデルとしての敵キャラクターモデルの参照値
#define START_COUNT			25								// ゲーム開始までの時間カウント

// モデル番号列挙
enum {
	MODEL_BODY_0 = 0,	MODEL_BODY_1,	MODEL_HEAD,
	MODEL_ARM_0,	MODEL_ARM_1,	MODEL_ARM_2,
	MODEL_LEG_0,	MODEL_LEG_1,	MODEL_LEG_2,
	MODEL_QTY
};

// パーツ番号列挙
enum {
	PARTS_BODY_0 = 0,	PARTS_BODY_1,	PARTS_HEAD,
	PARTS_R_ARM_0,	PARTS_R_ARM_1,	PARTS_R_ARM_2,
	PARTS_L_ARM_0,	PARTS_L_ARM_1,	PARTS_L_ARM_2,
	PARTS_R_LEG_0,	PARTS_R_LEG_1,	PARTS_R_LEG_2,
	PARTS_L_LEG_0,	PARTS_L_LEG_1,	PARTS_L_LEG_2,
	PARTS_QTY
};

//------------------------	モデルのデータに関する定数定義　-------------------------------------E




//------------------------	キャラクターの状態に関する定数定義　---------------------------------S

// キャラクター状態列挙
enum {
	STAND = 0, 
	DASH, 
	BACK, 
	LSTEP, 
	RSTEP, 
	LDASH, 
	RDASH, 
	LBACK, 
	RBACK, 
	ATTACK, 
	DASH_ATTACK, 
	JUMP, 
	DAMAGE, 
	DEATH
};

//------------------------	キャラクターの状態に関する定数定義　---------------------------------E

#endif