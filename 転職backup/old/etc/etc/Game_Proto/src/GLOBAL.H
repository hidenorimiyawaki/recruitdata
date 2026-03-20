//=======================================================================================
// グローバル変数定義
//=======================================================================================
bool						g_bQuit;				// 終了検出フラグ
bool						g_bNoWait;				// ウェイトフラグ
LPDIRECT3D8					g_pD3D;					// Direct3D8 オブジェクト
LPDIRECT3DDEVICE8			g_pD3DDevice;			// Direct3DDevice8 オブジェクト
D3DPRESENT_PARAMETERS		g_D3DPresentParam;		// PRESENT PARAMETERS
LPD3DXFONT					g_pD3DXFont;			// D3DXFont オブジェクト
float						g_FPS;					// フレーム数カウント用
LPDIRECT3DTEXTURE8			g_pD3DTexture;			// Direct3DTexture8 オブジェクト

PLAYER						g_Player;				// プレイヤー変数定義
int							game_cnt;

CModel						g_Model[4];
TAMA						g_Player_Tama[8];		// プレイヤー用弾


//TAMA						g_Enemy_Tama[3];		// 敵キャラ用弾

ENEMY						g_Enemy;				// 敵キャラ変数定義
ENEMY						Enemy_grp2[2];				// 敵キャラ変数定義
ENEMY						Enemy[ENEMY_GROUP + 1];
ENEMY						Enemy_grp1[3];

TAMA						g_Enemy_Tama;			// 敵キャラ用弾
TAMA						Enemy_grp2_Tama[2][3];			// 敵キャラ用弾
TAMA						Enemy_Tama[ENEMY_GROUP + 1];			// 敵キャラ用弾

BG							g_Bg_Bottom[5];
BG							g_Bg_Top[5];

BILLBORD					gauge;

BILLBORD					hp_gauge;
BILLBORD					gard_gauge;
BILLBORD					hyper_gauge;

BILLBORD					title[5];

BILLBORD					game_over_bord;

BILLBORD					target_cursol[2];
BILLBORD					barrier;

BILLBORD					P_Tama;
BILLBORD					E_Tama;

int							debug;

BGM							kyoku;

int							MESSAGE;		// メッセージ表示用定義
int							GAME_STATE;		// ゲームステータス定義

int							GAME_START_FLG;
int							GAME_START_CNT;

int							GAME_TIME;
int							GAME_SEC;
				
int							i;
D3DXMATRIX viewMat;
D3DXMATRIX persMat;

float			fog_start,fog_end;			// フォグの開始・終了位置
D3DMATERIAL8	main_material;			// マテリアルの現在のカラー


