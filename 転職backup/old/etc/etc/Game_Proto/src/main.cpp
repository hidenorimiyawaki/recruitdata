//=======================================================================================
//
//	  ゲームのプロトタイプ
//		Ｘファイルを読み込んで表示＋完全クラス化で作成
//
//=======================================================================================
//-------- インクルードヘッダ
#define STRICT
#include <windows.h>		// Windowsプログラムにはこれを付ける
#include <d3d8.h>			// DirectX Graphics 関連のヘッダー
#include <d3dx8.h>			// DirectX Graphics 関連のヘッダー
#include <D3d8types.h>
#include <stdio.h>			// 文字列処理で使用
#include <mmsystem.h>		// 時間管理で使用

#include <dmusici.h>
#include <Dxerr8.h>

#define RESOURCETYPE_WAVE	"WAVE"	// Waveデータのリソース・タイプ
#define RESOURCETYPE_MIDI	"MIDI"	// MIDIデータのリソース・タイプ

#include "resource.h"
#include "main.h"

//-------- ライブラリのリンク（こう記述しておけば別途リンク設定が不要となる）
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//=======================================================================================
// プロトタイプ宣言
//=======================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam);
HRESULT InitializeGraphics(HWND hWnd, bool bWindow);
HRESULT	CleanupGraphics();
HRESULT	RenderGraphics();
void	Initialize_Data(HWND hWnd);
void	ExecPat(HWND hWnd,LPDIRECT3DDEVICE8 p_Device);
void	DrawPat();
void	EnemyHitCheck(ENEMY*);
void	PlayerHitCheck(TAMA*);
void	SetView();
void	BossHitCheck(ENEMY*);
//---------------------------------------------------------------------------------------
//	メイン
//---------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow)
{
	HWND	hWnd;
	MSG		msg;
	DWORD	dwExecLastTime, dwFPSLastTime, dwCurrentTime, dwFrameCount;
	float	dt;
	bool	bWindow;

	// ウィンドウクラスの登録
	WNDCLASSEX wc = {sizeof(WNDCLASSEX), 
					 NULL, 
					 WindowProc,
					 0, 
					 0, 
					 hInstance,
					 LoadIcon(hInstance, IDI_APPLICATION), 
					 LoadCursor(NULL, IDC_ARROW),
					 (HBRUSH)GetStockObject(WHITE_BRUSH),
					 NULL,
					 CLASS_NAME,
					 NULL
	};
	if(RegisterClassEx(&wc) == 0) return false;		// ウィンドウクラスを登録

	// ウィンドウを作成
	hWnd = CreateWindowEx(
			NULL, CLASS_NAME, CAPTION_NAME, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 100, 100,
			SCREEN_WIDTH  + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
			SCREEN_HEIGHT + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
			NULL, NULL, hInstance, NULL);
	if(hWnd == NULL) return false;
	ShowWindow(hWnd, iCmdShow);		// ウィンドウを表示
	UpdateWindow(hWnd);				// ウィンドウをアップデート

	// グラフィック環境の初期化
	bWindow = true;
	if(FAILED(InitializeGraphics(hWnd, bWindow))) return false;		// ここで初期化

	// 各種初期化
	srand(timeGetTime());
	dwFPSLastTime = dwExecLastTime = timeGetTime();		// 現在のシステムタイマーを取得
	dwFrameCount = 0;
	Initialize_Data(hWnd);
	InitDInput(hInstance,hWnd);

	// メッセージループ
	timeBeginPeriod(1);					// システムタイマーの分解能を１ｍｓに設定
	g_bQuit     = false;
	g_bNoWait   = false;
	while(!g_bQuit) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {		// メッセージをチェック
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// この辺でフレーム数カウント
			dwCurrentTime = timeGetTime();								// 現在のタイマー値を取得
			if(dwCurrentTime - dwFPSLastTime >= 500) {					// ０．５秒ごとに計測
				dt = (float)(dwCurrentTime - dwFPSLastTime) / 1000;		// フレーム数を計算
				g_FPS = (float)dwFrameCount / dt;
				dwFPSLastTime = dwCurrentTime;							// タイマー値を更新
				dwFrameCount = 0;										// フレームカウンタをリセット
			}
			// この辺で時間管理
			if(g_bNoWait || dwCurrentTime - dwExecLastTime >= FRAME_RATE) {	// 一定時間が経過したら・・・
				dwExecLastTime = dwCurrentTime;							// タイマー値を更新
				if(!g_bQuit) {
					ExecPat(hWnd,g_pD3DDevice);											// パターン移動実行
					RenderGraphics();									// レンダリング
					dwFrameCount++;										// フレームカウントを＋１
				}
			}
		}
	}
	CleanupGraphics();		// グラフィック環境のクリーンアップ
	ReleaseDInput();
	timeEndPeriod(1);		// システムタイマーの分解能を元に戻す
	return msg.wParam;
}

//---------------------------------------------------------------------------------------
//	ウィンドウプロシージャ
//---------------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uiMessage) {
	case WM_DESTROY:				//----- 終了指示がきた
		g_bQuit = true;					// 終了フラグをセット
		PostQuitMessage(0);				// システムにスレッドの終了を要求
		break;
	case WM_KEYDOWN:				//----- キーボードが押された
		switch(wParam) {
		case 'W':	g_bNoWait   = (g_bNoWait  )? false: true;	break;	// ウェイト切替
		case VK_ESCAPE:					// [ESC]キーが押された
			if(GAME_STATE == 0) PostMessage(hWnd, WM_DESTROY, 0, 0);	// 終了のメッセージを発生させる
			else {
				GAME_STATE = 2;
			}
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, uiMessage, wParam, lParam);
	}
	return 0;
}

//=======================================================================================
//    DirectX Graphics 関連
//=======================================================================================

//---------------------------------------------------------------------------------------
// グラフィック環境の初期化
//---------------------------------------------------------------------------------------
HRESULT InitializeGraphics(HWND hWnd, bool bWindow)
{
	// デバイス情報テーブル
	struct TCreateDevice {
		D3DDEVTYPE type;			// デバイスの種類
		DWORD      behavior;		// デバイスの動作
	};
	const int c_nMaxDevice = 3;
	const TCreateDevice device[c_nMaxDevice] = {
	    { D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING },	// T&L HAL
	    { D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// HAL
	    { D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING },	// REF
	};
	HFONT			hFont;				// フォントオブジェクト
	D3DDISPLAYMODE	disp;				// ディスプレイモードを記述
	int				nDev;				// デバイス種別カウンタ
	D3DXMATRIX		matView, matProj;	// ビューマトリックス、プロジェクションマトリックス
	D3DMATERIAL8	mtrl;				// マテリアルオブジェクト
	D3DXVECTOR3		vecDir;				// 方向を指定するベクトル
	D3DLIGHT8		light;				// ライトオブジェクト


	// Direct3Dオブジェクトを生成
	if((g_pD3D = Direct3DCreate8(D3D_SDK_VERSION)) == NULL) {
		MessageBox(hWnd, "Direct3Dオブジェクトの作成に失敗しました", "error", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	// 現在の画面モードを取得
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp))) {
		MessageBox(hWnd, "ディスプレイモードの取得に失敗しました", "error", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	// Direct3D 初期化パラメータの設定
	ZeroMemory(&g_D3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));
	g_D3DPresentParam.BackBufferWidth        = SCREEN_WIDTH;			// ゲーム画面サイズ
	g_D3DPresentParam.BackBufferHeight       = SCREEN_HEIGHT;
	g_D3DPresentParam.Windowed               = bWindow;					// ウィンドウモードか?
	g_D3DPresentParam.BackBufferFormat       = (bWindow)? disp.Format : D3DFMT_R5G6B5;	// バックバッファ
	g_D3DPresentParam.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	g_D3DPresentParam.EnableAutoDepthStencil = true;					// Ｚバッファ有効
	g_D3DPresentParam.AutoDepthStencilFormat = D3DFMT_D16;				// Ｚバッファフォーマット

	// デバイスオブジェクトを作成
	for(nDev = 0; nDev < c_nMaxDevice; nDev++) {
		if(SUCCEEDED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[nDev].type, hWnd,	// デバイスを作成
					device[nDev].behavior, &g_D3DPresentParam, &g_pD3DDevice))) break;
	}
	if(nDev >= c_nMaxDevice) {
		MessageBox(hWnd, "デバイスの作成に失敗しました", "error", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// 情報表示用フォントを設定
	hFont = CreateFont(FONT_SIZE, 0, 0, 0, FW_DONTCARE, false, false, false, SHIFTJIS_CHARSET,
						OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONT_TYPE);
	D3DXCreateFont(g_pD3DDevice, hFont, &g_pD3DXFont);
	DeleteObject(hFont);				// フォントを削除

	// レンダリングステートを設定
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);						// Ｚバッファ有効化
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00303030);				// 環境光の設定

	//-------- ここから３Ｄ関連
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&matView,
						&D3DXVECTOR3(  0.0, 300.0,-2000.0),					// 視点座標
						&D3DXVECTOR3(  0.0,  0.0,    0.0),					// 注視点座標
						&D3DXVECTOR3(  0.0,  1.0,    0.0));					// アップベクトル
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&matProj, 45 * RAD, ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	// マテリアルの設定
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL8));								// いったんゼロでクリア
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0;
	mtrl.Ambient.r = mtrl.Ambient.g = mtrl.Ambient.b = mtrl.Ambient.a = 1.0;
	g_pD3DDevice->SetMaterial(&mtrl);

	// ライトの設定
	ZeroMemory(&light, sizeof(D3DLIGHT8));
	light.Type = D3DLIGHT_DIRECTIONAL;										// 平行光源
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0;
	vecDir = D3DXVECTOR3(1.0, -1.0, 1.0);									// 光の向きを決める
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);				// 正規化したベクトルを返す
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);										// ライト０を有効

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);						// ライト有効化
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);	// テクスチャの色を使用
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);	// 頂点の色を使用
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);	// レンダリング時の色の計算方法の設定
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);	// テクスチャの色を使用
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);	// 頂点の色を使用
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	return S_OK;
}

//---------------------------------------------------------------------------------------
// グラフィック環境のクリーンアップ
//---------------------------------------------------------------------------------------
HRESULT CleanupGraphics()
{
	SAFE_RELEASE(g_pD3DXFont);		// D3DXFont オブジェクトを解放
	SAFE_RELEASE(g_pD3DDevice);		// Direct3DDevice オブジェクトを解放
	SAFE_RELEASE(g_pD3D);			// Direct3D オブジェクトを解放
	return S_OK;
}

//---------------------------------------------------------------------------------------
// グラフィック環境のレンダリング
//---------------------------------------------------------------------------------------
HRESULT RenderGraphics()
{
	RECT	strRect;
	char	str[1024];//, tmp[256];
	
	// ビューポートをクリア
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0, 0);

	if(SUCCEEDED(g_pD3DDevice->BeginScene())) {		// シーン開始

		DrawPat();		// パターンを描画

		// デバッグストリング描画
		str[0] = NULL;
		SetRect(&strRect, 0, 0, 640, 480);
		sprintf(str, "FPS : %4.1f\n", g_FPS);			// ＦＰＳを画面に描画するための文字列を作成
		g_pD3DXFont->DrawText(str, -1, &strRect, 0, D3DCOLOR_ARGB(0xff, 0xf0, 0xf0, 0xf0));

		str[0] = NULL;
		SetRect(&strRect, 300, 0, 640, 480);
		sprintf(str, "SEC : %d\n",GAME_TIME);			// GAME TIMEを画面に描画するための文字列を作成
		g_pD3DXFont->DrawText(str, -1, &strRect, 0, D3DCOLOR_ARGB(0xff, 0xf0, 0xf0, 0xf0));

		g_pD3DDevice->EndScene();					// シーン終了

	}

	// バックバッファに描画した内容を表示
	if(FAILED(g_pD3DDevice->Present(NULL, NULL, NULL, NULL))) {
		g_pD3DDevice->Reset(&g_D3DPresentParam);
	}

	return S_OK;
}


//---------------------------------------------------------------------------------------
//　パターン処理
//---------------------------------------------------------------------------------------
void Initialize_Data(HWND hWnd){

	int	i;
	//----レンダリング系の初期化-------

	fog_start = 4000.0f;
	fog_end = 23000.0f;

	main_material.Diffuse.r = 1.0f; 	// ゲーム本体用マテリアル設定
	main_material.Diffuse.g = 1.0f; 
	main_material.Diffuse.b = 1.0f; 
	main_material.Diffuse.a = 0.5f; 

	main_material.Ambient.r = 0; 
	main_material.Ambient.g = 0; 
	main_material.Ambient.b = 0; 
	main_material.Ambient.a = 0; 

	main_material.Specular.r = 0; 
	main_material.Specular.g = 0; 
	main_material.Specular.b = 0; 
	main_material.Specular.a = 0;
	
	main_material.Power = 0; 

	main_material.Emissive.r = 0.0f;
	main_material.Emissive.g = 0.0f;
	main_material.Emissive.b = 0.0f;
	main_material.Emissive.a = 0.0f;



	//----各クラスの初期化-------

	g_Player.Initialize();							// プレイヤー初期化
	g_Player.effect[0].Initialize(Bbord[16]);
	g_Player.effect[1].Initialize(Bbord[16]);
	g_Player.effect[2].Initialize(Bbord[16]);
	g_Player.effect[3].Initialize(Bbord[16]);
	g_Player.effect[4].Initialize(Bbord[17]);

	P_Tama.Initialize(Bbord[1]);
	E_Tama.Initialize(Bbord[2]);

	barrier.Initialize(Bbord[15]);

	target_cursol[0].Initialize(Bbord[11]);	
	target_cursol[1].Initialize(Bbord[12]);	

	g_Enemy.Initialize(Def_Enemy[0]);				// 敵キャラ初期化

	for(i = 0; i <= 2;i++){
		Enemy_grp1[i].Initialize(Def_Enemy[i+1]);
	}

	//-----ここから------
	Enemy[0].Initialize(Def_Enemy[4]);
	Enemy[1].Initialize(Def_Enemy[5]);
	Enemy[2].Initialize(Def_Enemy[4]);
	Enemy[3].Initialize(Def_Enemy[5]);
	Enemy[4].Initialize(Def_Enemy[4]);
	Enemy[5].Initialize(Def_Enemy[5]);
	Enemy[6].Initialize(Def_Enemy[4]);
	Enemy[7].Initialize(Def_Enemy[5]);
    //-----ここまで------

	g_Bg_Bottom[0].Initialize(Yuka_Data_Bottom[0]);	// 床初期化
	g_Bg_Bottom[1].Initialize(Yuka_Data_Bottom[1]);
	g_Bg_Bottom[2].Initialize(Yuka_Data_Bottom[2]);
	g_Bg_Bottom[3].Initialize(Yuka_Data_Bottom[3]);
	g_Bg_Bottom[4].Initialize(Yuka_Data_Bottom[4]);

	g_Bg_Top[0].Initialize(Yuka_Data_Top[0]);		// 天井初期化
	g_Bg_Top[1].Initialize(Yuka_Data_Top[1]);
	g_Bg_Top[2].Initialize(Yuka_Data_Top[2]);
	g_Bg_Top[3].Initialize(Yuka_Data_Top[3]);
	g_Bg_Top[4].Initialize(Yuka_Data_Top[4]);

	gauge.Initialize(Bbord[0]);						// ゲージ枠の初期化

	hp_gauge.Initialize(Bbord[3]);					// 体力ゲージ初期化
	gard_gauge.Initialize(Bbord[13]);
	hyper_gauge.Initialize(Bbord[14]);

	title[0].Initialize(Bbord[8]);					// タイトル画面パネル初期化
	title[1].Initialize(Bbord[9]);
	title[2].Initialize(Bbord[5]);
	title[3].Initialize(Bbord[4]);
	title[4].Initialize(Bbord[10]);

	game_over_bord.Initialize(Bbord[7]);

	kyoku.Initialize(hWnd);


	//----モデルデータの初期化-------

	g_Player.SetModelData(hWnd,g_pD3DDevice,file_name_x,file_name_mesh);			// プレイヤーのモデルを設定
	gauge.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	hp_gauge.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	gard_gauge.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	P_Tama.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	P_Tama.kasan_flg = 1;
	E_Tama.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	E_Tama.kasan_flg = 1;

	g_Model[0].SetModelData(hWnd,g_pD3DDevice,file_name_x,file_name_mesh,5);
	g_Model[1].SetModelData(hWnd,g_pD3DDevice,file_name_x,file_name_mesh,4);
	g_Model[2].SetModelData(hWnd,g_pD3DDevice,file_name_x,file_name_mesh,2);
	g_Model[3].SetModelData(hWnd,g_pD3DDevice,file_name_x,file_name_mesh,3);

	hyper_gauge.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	hyper_gauge.pRect.left = 0;
	hyper_gauge.pRect.right = 0;

	game_over_bord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	barrier.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	barrier.pRect.right  += 100;
	barrier.pRect.bottom  += 100;
	barrier.mat.Diffuse.a = 0.7f;
	barrier.kasan_flg = 1;
	barrier.draw_flg = 0;

	g_Enemy.model_no = 0;

	target_cursol[0].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	target_cursol[1].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	target_cursol[0].kasan_flg = 1;
	target_cursol[1].kasan_flg = 1;

	for(i = 0;i <= TITLE_MAX;i++){
		title[i].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	}

	title[1].pRect.right = 1280;
	title[1].pRect.bottom = 960;
	title[0].pRect.right = 1280;
	title[0].pRect.bottom = 960;
	title[4].draw_flg = 0;
	title[4].draw_cnt = 20;

	for(i = 0;i <= YUKA_MAX;i++){
		g_Bg_Bottom[i].SetModelData(hWnd,g_pD3DDevice,file_name_bg_x,file_name_bg_mesh);
		g_Bg_Top[i].SetModelData(hWnd,g_pD3DDevice,file_name_bg_x,file_name_bg_mesh);
	}

	for(i = 0; i <= 4; i++){
		g_Player.effect[i].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
		g_Player.effect[i].draw_flg = 0;
	}
	g_Player.effect[4].pRect.right  += 200;
	g_Player.effect[4].pRect.bottom  += 200;

	for(i = 0; i <= g_Player.tama_max; i++){
		g_Player_Tama[i].SetData(Tama_Type_All[0] ,g_pD3DDevice);
		g_Player_Tama[i].SetMove((float)i*60,(float)i*30,(float)i*30);
	}
	
	g_Enemy_Tama.SetData(Tama_Type_All[1],g_pD3DDevice);
	for(i = 0;i <= 2;i++){
		Enemy_grp2_Tama[i][0].SetData(Tama_Type_All[1],g_pD3DDevice);
		Enemy_grp2_Tama[i][1].SetData(Tama_Type_All[1],g_pD3DDevice);	
		Enemy_grp2_Tama[i][2].SetData(Tama_Type_All[1],g_pD3DDevice);
	}
	for(i = 0; i <= ENEMY_GROUP;i++){
		Enemy_Tama[i].SetData(Tama_Type_All[1],g_pD3DDevice);
	}
	
	//----ゲーム用変数の初期化-------

	game_cnt = 0;

	MESSAGE		= 0;		// メッセージ表示用定義
	GAME_STATE	= 0;		// ゲームステータス定義

	GAME_START_FLG = 0;
	GAME_START_CNT = 0;

	GAME_TIME = 0;
	GAME_SEC = 0;

	debug = 0;
}


void ExecPat(HWND hWnd,LPDIRECT3DDEVICE8 p_Device)
{
	
	KeyManager();
	//----- 処理本体
	switch(GAME_STATE){


//**************タイトル画面シーケンス******************

		case 0:
			for(i = 0;i <= TITLE_MAX;i++){
				title[i].SetRot();
			}

			title[1].SetMove(0,-5,0);
			title[0].SetMove(0,-5,0);

			if(GAME_START_FLG == 0){ 
				if(title[4].draw_flg == 1 && title[4].draw_cnt >= 40){
					title[4].draw_flg = 0;
					title[4].draw_cnt = 0;
				}
				else if(title[4].draw_flg == 0 && title[4].draw_cnt >= 20){
					title[4].draw_flg = 1;
				}
				title[4].draw_cnt++;
				if((GetAsyncKeyState('Z') & 0x8000) || (GetAsyncKeyState('X') & 0x8000) || KEY_PUSH_A(0) || KEY_PUSH_B(0)) GAME_START_FLG = 1;
			}
			else{
				if(title[4].draw_flg == 1 && title[4].draw_cnt >= 10){
					title[4].draw_flg = 0;
					title[4].draw_cnt = 0;
				}
				else if(title[4].draw_flg == 0 && title[4].draw_cnt >= 5){
					title[4].draw_flg = 1;
				}
				title[4].draw_cnt++;
				GAME_START_CNT++;
				if(GAME_START_CNT >= 40){
					GAME_STATE = 1;
					GAME_START_CNT = 0;
					for(i = 0;i <= TITLE_MAX;i++){
						title[i].CleanupGraphics();
					}
					kyoku.Play();
				}
			}
			
			break;


//**************ゲームメインシーケンス******************

		case 1:

	//-----------プレイヤー処理--------------------------


			//キー取得処理
			g_Player.GetKey(g_Player_Tama);

			//バリア関連処理
			g_Player.Barrier();
			if(g_Player.barrier_flg == 1){
				barrier.SetPoint(g_Player.x - 180,g_Player.y - 140,g_Player.z - 120);
				barrier.draw_flg = 1;
			}
			else {
				barrier.draw_flg = 0;
			}

			if(g_Player.barrier_flg == 1 && g_Player.bp >= 0) gard_gauge.SerPPoint((float)(g_Player.bp_max),0,0);
			else if(g_Player.barrier_flg == 0 && g_Player.bp + 1 <= g_Player.bp_max) {
				gard_gauge.SerPPoint( (float)(g_Player.bp_max) * -1,0,0);
			}
			if(g_Player.bp >= g_Player.bp_max){
				gard_gauge.pRect.right = 123;
				gard_gauge.pRect.left = 0;
			}

			//カーソル設定処理
			if(g_Player.target_trg == 1){
				target_cursol[1].SetPoint(g_Player.x - 32,g_Player.y - 8,g_Player.z + 1000);
				target_cursol[1].draw_flg = 1;
				target_cursol[0].draw_flg = 0;
			}
			else{
				target_cursol[1].draw_flg = 0;
				target_cursol[0].draw_flg = 1;
				target_cursol[0].SetPoint(g_Player.x - 32,g_Player.y - 8,g_Player.z + 1000);
			}

			//弾処理
			for(i = 0; i <= g_Player.tama_max; i++){
				g_Player_Tama[i].Move();
			}

			g_Player.SetEffect();
 

	//-----------敵キャラクター処理--------------------------
			if(g_Enemy.move_flg == 1){
				g_Enemy.GetPlayerPos(g_Player.x,g_Player.y,g_Player.z);

				g_Enemy.Move(Move_Offset_A,&g_Enemy_Tama);
		
			}
			g_Enemy_Tama.Move();

			if(Enemy_grp1[0].move_flg == 1) Enemy_grp1[0].Move(Move_Offset_B,&Enemy_grp2_Tama[0][0]);
			if(Enemy_grp1[1].move_flg == 1) Enemy_grp1[1].Move(Move_Offset_B,&Enemy_grp2_Tama[1][0]);
			if(Enemy_grp1[2].move_flg == 1) Enemy_grp1[2].Move(Move_Offset_B,&Enemy_grp2_Tama[0][0]);

			if(Enemy_grp2[0].move_flg == 1) Enemy_grp2[0].Move(Move_Offset_C,&Enemy_grp2_Tama[0][0]);
			if(Enemy_grp2[1].move_flg == 1) Enemy_grp2[1].Move(Move_Offset_D,&Enemy_grp2_Tama[1][0]);

			//-----ここから------

			for(i = 0;i <= ENEMY_GROUP;i++){
				if(Enemy[i].move_flg == 1){
					EnemyHitCheck(&Enemy[i]);
				}
			}

			for(i = 0;i <= ENEMY_GROUP;i++){
				if(Enemy[i].move_flg == 1){
					g_Player.GetEnemyPos(Enemy[i].x,Enemy[i].y,Enemy[i].z);
				}
			}

			if(Enemy[0].move_flg == 1) Enemy[0].Move(Move_Offset_C,&Enemy_Tama[0]);
			if(Enemy[1].move_flg == 1) Enemy[1].Move(Move_Offset_D,&Enemy_Tama[1]);
			if(Enemy[2].move_flg == 1) Enemy[2].Move(Move_Offset_E,&Enemy_Tama[2]);
			if(Enemy[3].move_flg == 1) Enemy[3].Move(Move_Offset_F,&Enemy_Tama[3]);
			if(Enemy[4].move_flg == 1) Enemy[4].Move(Move_Offset_C,&Enemy_Tama[4]);
			if(Enemy[5].move_flg == 1) Enemy[5].Move(Move_Offset_D,&Enemy_Tama[5]);
			if(Enemy[6].move_flg == 1) Enemy[6].Move(Move_Offset_E,&Enemy_Tama[6]);
			if(Enemy[7].move_flg == 1) Enemy[7].Move(Move_Offset_F,&Enemy_Tama[7]);

			for(i = 0;i <= ENEMY_GROUP;i++){
				Enemy[i].GetPlayerPos(g_Player.x,g_Player.y,g_Player.z);
				if(i <= ENEMY_GROUP -2)	Enemy[i].Death(&Enemy[i+1]);
				Enemy_Tama[i].Move();
			}
			//-----ここまで------

			//ターゲット設定処理
			if(g_Enemy.move_flg == 1) g_Player.GetEnemyPos(g_Enemy.x,g_Enemy.y,g_Enemy.z);
			if(Enemy_grp1[0].move_flg == 1) g_Player.GetEnemyPos(Enemy_grp1[0].x,Enemy_grp1[0].y,Enemy_grp1[0].z);
			if(Enemy_grp1[1].move_flg == 1) g_Player.GetEnemyPos(Enemy_grp1[1].x,Enemy_grp1[1].y,Enemy_grp1[1].z);
			if(Enemy_grp1[2].move_flg == 1) g_Player.GetEnemyPos(Enemy_grp1[2].x,Enemy_grp1[2].y,Enemy_grp1[2].z);
			for(i = 0;i <= ENEMY_GROUP;i++){
				if(Enemy[i].move_flg == 1){
					g_Player.GetEnemyPos(Enemy[i].x,Enemy[i].y,Enemy[i].z);
				}
			}




	//-----------背景処理--------------------------

			for(i = 0;i <= YUKA_MAX;i++){
				g_Bg_Bottom[i].SetMove(g_Bg_Bottom[i].dx,g_Bg_Bottom[i].dy,g_Bg_Bottom[i].dz);
				g_Bg_Top[i].SetMove(g_Bg_Top[i].dx,g_Bg_Top[i].dy,g_Bg_Top[i].dz);
			}


 	//-----------外部処理呼び出し--------------------------

			BossHitCheck(&g_Enemy);
			EnemyHitCheck(&Enemy_grp1[0]);
			EnemyHitCheck(&Enemy_grp1[1]);
			EnemyHitCheck(&Enemy_grp1[2]);

			PlayerHitCheck(&g_Enemy_Tama);
			for(i = 0;i <= ENEMY_GROUP;i++){
				PlayerHitCheck(&Enemy_Tama[i]);
			}


	//-----------回転角度設定--------------------------

			for(i = 0;i <= YUKA_MAX;i++){
				g_Bg_Bottom[i].SetRot();
				g_Bg_Top[i].SetRot();
			}

			g_Player.SetRot();

			for(i = 0; i <= 4; i++){
				g_Player.effect[i].SetRot();
			}

			gauge.SetRot();
			hp_gauge.SetRot();
			gard_gauge.SetRot();
			hyper_gauge.SetRot();
			barrier.SetRot();

			g_Enemy_Tama.SetRot();

			target_cursol[0].SetRot();
			target_cursol[1].SetRot();

			for(i = 0; i <= g_Player.tama_max; i++){
				g_Player_Tama[i].SetRot();
			}


	//----------ゲーム時間設定-------------------------
			GAME_SEC++;

			if(GAME_SEC >= 60){
				GAME_SEC = 0;
				GAME_TIME += 1; 
			}


	//----------ゲーム時間に合わせた設定-------------------------
			if(GAME_TIME == ENEMY_START2){
				Enemy_grp1[0].move_flg = 1;
			}

			if(GAME_TIME == ENEMY_START3){
				Enemy_grp1[1].move_flg = 1;
			}

			if(GAME_TIME == ENEMY_START4){
				Enemy_grp1[2].move_flg = 1;
			}

			if(GAME_TIME == ENEMY_START5){
				Enemy[0].move_flg = 1;
			}

			if(GAME_TIME == ENEMY_START1){
				g_Enemy.move_flg = 1;
			}

			if(g_Player.death_cnt <= 0) GAME_STATE = 2;

			if(g_Enemy.death == 1) GAME_STATE = 3;
			break;


//**************ゲームオーバーシーケンス******************
		case 2:			

	//----------ゲームオーバー処理-------------------------

			game_over_bord.SetRot();
			if(fog_end <= GAME_END_FOG){
				fog_end = GAME_END_FOG;
				kyoku.Stop();
				Initialize_Data(hWnd);
				GAME_STATE = 0;
			}
			else {
				fog_end -= FOG_POS;
				fog_start -= FOG_POS;
			}

			break;


//**************ゲームクリアシーケンス******************

		case 3:

			g_pD3DDevice->SetMaterial(&main_material);
			g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
			g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
			kyoku.Stop();
			Initialize_Data(hWnd);
			GAME_STATE = 0;

			break;


//**************デフォルトシーケンス******************

		default:
			break;

	}
}



//---------------------------------------------------------------------------------------
//　描画処理
//---------------------------------------------------------------------------------------
void DrawPat()
{
	int		i;

//**************フォグの設定******************

	g_pD3DDevice->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定
	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					// フォグの設定
	g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR,0xff000000);				// フォグの設定
	g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE,D3DFOG_LINEAR);		// フォグの設定
	g_pD3DDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD *)&fog_start);		// フォグの設定
	g_pD3DDevice->SetRenderState(D3DRS_FOGEND,*(DWORD *)&fog_end);			// フォグの設定


//**************外部関数呼び出し（視点設定）******************

	SetView();


//**************ゲームメイン描画******************

	if(fog_end > 7000){

		for(i = 0;i <= YUKA_MAX;i++){
			g_Bg_Bottom[i].Draw(g_pD3DDevice);
			g_Bg_Top[i].Draw(g_pD3DDevice);
		}

		g_Player.Draw(g_pD3DDevice);

		for(i = 0; i <= 4; i++){
			g_Player.effect[i].Draw(g_pD3DDevice);
		}


		target_cursol[0].Draw(g_pD3DDevice);
		target_cursol[1].Draw(g_pD3DDevice);


		if(g_Enemy.move_flg == 1) {
			g_Enemy.Draw(g_pD3DDevice,g_Model);
		}

		if(g_Enemy_Tama.trg == 1){
			g_Enemy_Tama.SetRot();
			E_Tama.matrix = g_Enemy_Tama.matrix;
			g_Enemy_Tama.Draw(g_pD3DDevice,&E_Tama);
		}

		for(i = 0; i <= ENEMY_GROUP;i++){
			if(Enemy_Tama[i].trg == 1){
				Enemy_Tama[i].SetRot();
				E_Tama.matrix = Enemy_Tama[i].matrix;
				Enemy_Tama[i].Draw(g_pD3DDevice,&E_Tama);
			}
		}

		for(i = 0; i <= g_Player.tama_max; i++){
			if(g_Player_Tama[i].trg == 1){
				g_Player_Tama[i].SetRot();
				P_Tama.matrix = g_Player_Tama[i].matrix;
				g_Player_Tama[i].Draw(g_pD3DDevice,&P_Tama);
			}
		}

		for(i = 0; i <= 2; i++){
			if(Enemy_grp1[i].move_flg == 1) Enemy_grp1[i].Draw(g_pD3DDevice,g_Model);
		}

		for(i = 0; i <= ENEMY_GROUP; i++){
			if(Enemy[i].move_flg == 1) Enemy[i].Draw(g_pD3DDevice,g_Model);
		}

		barrier.Draw(g_pD3DDevice);

		D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
		D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
		g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
		g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);
		gauge.Draw(g_pD3DDevice);

		hp_gauge.Draw(g_pD3DDevice);
		gard_gauge.Draw(g_pD3DDevice);
		hyper_gauge.Draw(g_pD3DDevice);
		
	}


//**************ゲームオーバー描画******************

	if(GAME_STATE == 2){
		D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
		D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
		g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
		g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);
		game_over_bord.Draw(g_pD3DDevice);
	}


//**************タイトル画面描画******************

	if(GAME_STATE == 0 ){
		D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
		D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
		g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
		g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);
		for(i = 0; i <= TITLE_MAX; i++){
			title[i].Draw(g_pD3DDevice);
		}
	}

}


//---------------------------------------------------------------------------------------
//　当たり判定処理
//---------------------------------------------------------------------------------------
void EnemyHitCheck(ENEMY* pEnemy){

	if(pEnemy->death == 0 && pEnemy->hit == 0){
		for(i = 0; i <= g_Player.tama_max; i++){
			if(pEnemy->x  - g_Player_Tama[i].pRect.right - 40 <= g_Player_Tama[i].x && pEnemy->x + 100.0 >= g_Player_Tama[i].x){
				if(pEnemy->y - g_Player_Tama[i].pRect.right - 40 <= g_Player_Tama[i].y && pEnemy->y + 100.0 >= g_Player_Tama[i].y){
					if(pEnemy->z  - g_Player_Tama[i].pRect.right - 40 <= g_Player_Tama[i].z && pEnemy->z + 100.0 >= g_Player_Tama[i].z){
							pEnemy->SetHp(g_Player_Tama[i].damage);
							g_Player_Tama[i].SetPoint(5000,5000,5000);
							g_Player_Tama[i].trg = 0;
							pEnemy->hit = 1;
							pEnemy->hit_cnt = 10;
					}
				}
			}
		}
	}
}

void BossHitCheck(ENEMY* pEnemy){

	if(pEnemy->death == 0 && pEnemy->hit == 0){
		for(i = 0; i <= g_Player.tama_max; i++){
			if(pEnemy->x  - g_Player_Tama[i].pRect.right - 120 <= g_Player_Tama[i].x && pEnemy->x + 180.0 >= g_Player_Tama[i].x){
				if(pEnemy->y - g_Player_Tama[i].pRect.right - 50.0 <= g_Player_Tama[i].y && pEnemy->y + 180.0 >= g_Player_Tama[i].y){
					if(pEnemy->z  - g_Player_Tama[i].pRect.right - 120 <= g_Player_Tama[i].z && pEnemy->z + 180.0 >= g_Player_Tama[i].z){
							pEnemy->SetHp(g_Player_Tama[i].damage);
							g_Player_Tama[i].SetPoint(5000,5000,5000);
							g_Player_Tama[i].trg = 0;
							pEnemy->hit = 1;
							pEnemy->hit_cnt = 10;
					}
				}
			}
		}
	}
}

void PlayerHitCheck(TAMA* pTama) {

	if(g_Player.death == 0){
		if(g_Player.x - pTama->pRect.right  - 40 <= pTama->x && g_Player.x + 100.0 >= pTama->x){
			if(g_Player.y - pTama->pRect.right  - 40 <= pTama->y && g_Player.y + 100.0 >= pTama->y){
				if(g_Player.z - pTama->pRect.right  - 40 <= pTama->z && g_Player.z + 100.0 >= pTama->z){

					if(g_Player.barrier_flg == 0){
						g_Player.SetHp(pTama->damage);
						g_Player.hit = 1;
						hp_gauge.SerPPoint( ((float)(g_Player.hp_max / pTama->damage) - 1),0,0);
						g_pD3DDevice->SetMaterial(&main_material);
						g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
						g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
					}
					else if(g_Player.barrier_flg == 1){
						g_Player.hyper_point += 10;
						if(g_Player.hyper_point >= g_Player.hyper_max) g_Player.hyper_point = g_Player.hyper_max;

						hyper_gauge.pRect.right += 25;
						hyper_gauge.x -= 25; 
						if(hyper_gauge.pRect.right >= 250){
							hyper_gauge.pRect.right = 250;
							hyper_gauge.x = 250 + 120;
							g_Player.hyper_point = 100;
							g_Player.hyper_flg = 1;
							for(i = 0; i <= g_Player.tama_max; i++){
								g_Player_Tama[i].damage = 60;
								P_Tama.pRect.bottom = 180;
								P_Tama.pRect.right = 180;
								P_Tama.pRect.top = 0;
								P_Tama.pRect.left = 0;
								P_Tama.SetVbuffer(g_pD3DDevice);
							}
						}
					}

					pTama->SetPoint(5000,5000,5000);
					pTama->trg = 0;
				}
			}
		}
	}

}


//---------------------------------------------------------------------------------------
//　視点設定処理
//---------------------------------------------------------------------------------------
void SetView(){

	D3DXMatrixLookAtLH(&viewMat,
						&D3DXVECTOR3(0+g_Player.cmx, g_Player.cmy+100,-2000+g_Player.cmz),		// 視点座標
						&D3DXVECTOR3(0+g_Player.cmx, g_Player.cmy+100,  0.0),		// 注視点座標
						&D3DXVECTOR3(  0.0,  1.0,    0.0));		// アップベクトル
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &viewMat);

	D3DXMatrixPerspectiveFovLH(&persMat, 45 * RAD, ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &persMat);

}
//=======================================================================================
//	end of files
//=======================================================================================
