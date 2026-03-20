/************************************************************
*						global.h							*
*															*
*		このファイルでは、グローバル変数の定義をします。	*
*															*
*															*
************************************************************/

#ifndef	___GLOBAL_H___		// このヘッダファイルが読み込まれていなければ
#define	___GLOBAL_H___	


#ifndef	EX
#define	EX 
#else	
#define EX extern
#endif


//=======================================================================================
// グローバル変数定義
//=======================================================================================


//--------------------- DirectX関連の変数定義 -----------------------------------------------------S

	EX bool						g_bQuit;						// 終了検出フラグ
	EX bool						g_bNoWait;						// ウェイトフラグ
	EX LPDIRECT3D8				g_pD3D;							// Direct3D8 オブジェクト
	EX LPDIRECT3DDEVICE8		g_pD3DDevice;					// Direct3DDevice8 オブジェクト
	EX D3DPRESENT_PARAMETERS	g_D3DPresentParam;				// PRESENT PARAMETERS
	EX LPD3DXFONT				g_pD3DXFont;					// D3DXFont オブジェクト
	EX float					g_FPS;							// フレーム数カウント用
	EX LPDIRECT3DTEXTURE8		g_pD3DTexture;					// Direct3DTexture8 オブジェクト
	EX HINSTANCE				pInstance;						// インスタンス(INIファイル読み込みよう)
	EX float					fog_start,fog_end;				// フォグの開始・終了位置
	EX D3DMATERIAL8				main_material;					// マテリアルの現在のカラー

//--------------------- DirectX関連の変数定義 -----------------------------------------------------E




//--------------------- カメラ関連の変数定義 ------------------------------------------------------S

	EX D3DXMATRIX				viewMat;						// ビューマトリックス
	EX D3DXMATRIX				persMat;						// パースマトリックス
	EX D3DXMATRIX				camera;							// カメラ(置き場所)
	EX D3DXMATRIX				ecamera;						// カメラ(注視点)
	EX float					Camera_Y;						// スタート時に変化するカメラのオフセット
	EX float					Camera_Z;						// スタート時に変化するカメラのオフセット

//--------------------- カメラ関連の変数定義 ------------------------------------------------------E




//--------------------- INIファイル関連の変数定義 -------------------------------------------------S

	EX int						SOUND_CHECK;					// サウンド使用チェック
	EX int						SHADOW_CHECK;					// 影使用チェック

	EX int						BLOOD_CHECK;					// 血のエフェクト使用チェック
	EX int						FPS_CHECK;						// FPS表示チェック

	EX int						bWindow;						// ウィンドウ状態判定変数

//--------------------- INIファイル関連の変数定義 -------------------------------------------------E





//--------------------- ゲーム全体関連の変数定義 --------------------------------------------------S

	EX int						game_cnt;						// ゲーム中のカウンタ

	EX int						debug;							// デバッグ判断変数

	EX int						MESSAGE;						// メッセージ表示用定義
	EX int						GAME_STATE;						// ゲームステータス定義

	EX int						GAME_START_FLG;					// ゲームの初期状態判定
	EX int						GAME_START_CNT;					// ゲームの初期状態カウンタ
	EX int						GAME_END_CNT;					// ゲームの終了状態カウンタ


	EX int						GAME_TIME;						// ゲームの秒数カウンタ
	EX int						GAME_TIME_CNT;					// ゲームの秒数(60分の?)カウンタ

	EX int						key_trg;						// キーのトリガー

	EX int						all_death;						// 全体撃破数

	EX int						i;								// 汎用カウンタ
	EX int						BeatCnt;						// 連殺カウンタ
	EX int						MaxHit;							// 最大ヒット数

	EX int						BeatTime;						// 連殺カウンタが途切れるか否かのカウンタ

	EX int						MenuCheck;						// メニューの板チェック
	EX int						score;							// スコア

	EX int						work_death;						// 最大撃破数を表示するためのワークカウンタ
	EX int						work_hit;						// 最大ヒット数を表示するためのワークカウンタ
	EX int						work_score;						// スコアを表示するためのワークカウンタ

//--------------------- ゲーム全体関連の変数定義 ---------------------------------------------------E




//--------------------- キャラクタ関連の変数定義 ---------------------------------------------------S

	//-------モデル関係
	EX MODEL					AllModel[MODEL_MAX];			// 全てのモデル(非アニメーション)
	EX CModelManager			model_manager;					// 人体モデル管理クラス取得
	EX CZintai					zintai(partsinfo);				// 人体
	EX MOTION_DATA*				pZintai;						// モーションデータの参照体

	//-------プレイヤー関係
	EX PLAYER					player;							// プレイヤー変数
	EX TAMA						Player_Tama[8];					// プレイヤーの弾(最大８連射)

	//-------敵キャラ関係
	EX ENEMY					test_enemy[ENEMY_MAX];			// 敵キャラ変数(敵最大数分)
	EX ENEMY*					penemy;							// 敵キャラ変数(newで取得するためのポインタ)
	EX TAMA*					ptama;							// 敵の弾変数(newで取得するためのポインタ)

	//-------エフェクト関係
	EX TAMA						BulletEffect[8];				// 薬きょう(プレイヤーの弾にあわせた数取得)
	EX TAMA						Enemy_Tama[ENEMY_MAX];			// 敵キャラの弾(敵キャラ最大数分)
	EX TAMA						BloodEffect[BLOOD_MAX];			// 血のエフェクト用の弾
	EX TAMA						SparksEffect[SPARKS_MAX];		// 敵爆発のエフェクト用の弾

//--------------------- キャラクタ関連の変数定義 ---------------------------------------------------E




//--------------------- 絵(ビルボード)の変数定義 ---------------------------------------------------S

	EX BILLBORD					P_Tama;							// 弾の絵
	EX BILLBORD					Muzzle_Flash;					// マズルフラッシュの絵

	EX BILLBORD					CountEffect[3];					// 連殺カウンタの数字の絵
	EX BILLBORD					BeatEffect;						// 連殺カウンタのBEATの絵
	EX BILLBORD					FireEffect;						// 連殺カウンタのエフェクトの炎の絵

	EX BILLBORD					OptionBord[6];					// オプションで表示するための絵

	EX BILLBORD					TitleBord[4];					// タイトルで使用する絵
	EX BILLBORD					EnemyHitBord;					// 敵キャラのヒットエフェクト

	EX BILLBORD					GameOverBord;					// ゲームオーバー画面の絵
	EX BILLBORD					GameClearBord;					// ゲームクリア画面の絵

	EX BILLBORD					HpBord;							// ヒットポイントゲージの絵
	EX BILLBORD					StartBord[2];					// スタートに使用する絵
	EX BILLBORD					LifeBord[2];					// ライフの絵
	EX BILLBORD					Shadow;							// 影の絵

	EX BILLBORD					ScoreBord;						// スコアの文字の絵
	EX BILLBORD					TotalBord;						// トータルの文字の絵
	EX BILLBORD					MaxBord;						// マックスの文字の絵
	EX BILLBORD					KakeBord;						// ×の文字の絵
	EX BILLBORD					NumBord;						// 汎用的に使用する数字の絵
	EX BILLBORD					TimeBord;						// TIMEの文字の絵

	EX BILLBORD					Blood;							// 血のエフェクトの絵
	EX BILLBORD					Sparks;							// 敵爆発のエフェクトの絵
	EX BILLBORD					Bullet;							// 薬きょう用ビルボード(表示参照絵)

//--------------------- 絵(ビルボード)の変数定義 ---------------------------------------------------E




//--------------------- 音楽用の変数定義 -----------------------------------------------------------S

EX MUSIC					EffectSound[5];					// 全体的に使用する効果音
EX MUSIC					BGMSound[4];					// 全体的に使用するBGM

//--------------------- 音楽用の変数定義 -----------------------------------------------------------E




//--------------------- 背景用の変数定義 -----------------------------------------------------------S

EX BG						BG[YUKA_MAX];					// BGのモデルクラス取得

//--------------------- 背景用の変数定義 -----------------------------------------------------------E


#endif
