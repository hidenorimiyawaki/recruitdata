//=======================================================================================
//
//	  ゲームのプロトタイプ
//		
//
//=======================================================================================

//-------- インクルードヘッダ
#include "main.h"
#include "data.h"
#include "global.H"
#include "motiondata.h"

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
void	SetView();
void	EnemyHitCheck(ENEMY*,TAMA*);
void	PlayerHitCheck(TAMA*);
void	BeatCounter();
void	ScoreCounter();
void	ZintaiManager();
void	TimeCounter();
//---------------------------------------------------------------------------------------
//	メイン
//---------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow)
{
	HWND	hWnd;
	MSG		msg;
	DWORD	dwExecLastTime, dwFPSLastTime, dwCurrentTime, dwFrameCount;
	float	dt;

	pInstance = hInstance;
	int i;
	char	dir_buf[256];
	GetModuleFileName(hInstance, dir_buf, 256);
	for(i = strlen(dir_buf); dir_buf[i] != '\\'; --i) dir_buf[i] = NULL;
	strcpy(&dir_buf[i+1],"config.ini");
	bWindow		= GetPrivateProfileInt("quarrel bomber","WINDOW",	0,dir_buf);
	SHADOW_CHECK= GetPrivateProfileInt("quarrel bomber","SHADOW",	1,dir_buf);
	BLOOD_CHECK = GetPrivateProfileInt("quarrel bomber","BLOOD",	1,dir_buf);
	SOUND_CHECK = GetPrivateProfileInt("quarrel bomber","SOUND",	1,dir_buf);
	FPS_CHECK = GetPrivateProfileInt("quarrel bomber","FPS",	1,dir_buf);

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
	if(FAILED(InitializeGraphics(hWnd, bWindow))) return false;		// ここで初期化

	// 各種初期化
	srand(timeGetTime());
	dwFPSLastTime = dwExecLastTime = timeGetTime();		// 現在のシステムタイマーを取得
	dwFrameCount = 0;

	Initialize_Data(hWnd);

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
					ExecPat(hWnd,g_pD3DDevice);							// パターン移動実行
					RenderGraphics();									// レンダリング
					dwFrameCount++;										// フレームカウントを＋１
				}
			}
		}
	}
	CleanupGraphics();		// グラフィック環境のクリーンアップ
	timeEndPeriod(1);		// システムタイマーの分解能を元に戻す
	return msg.wParam;
}

//---------------------------------------------------------------------------------------
//	ウィンドウプロシージャ
//---------------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	char	dir_buf[256];
	int i;

	switch(uiMessage) {
		case WM_DESTROY:				//----- 終了指示がきた
			g_bQuit = true;					// 終了フラグをセット

			// INIファイルの作成
			GetModuleFileName(pInstance, dir_buf, 256);
			for(i = strlen(dir_buf); dir_buf[i] != '\\'; --i) dir_buf[i] = NULL;
			strcpy(&dir_buf[i+1],"config.ini");
			char	config_buf[1024];
			wsprintf(config_buf,"[quarrel bomber]\n\n;●ウインドウモードで表示\n;　0：フルスクリーンモード、\n;　1：ウインドウモードです。\n");
			wsprintf(&config_buf[strlen(config_buf)],"WINDOW = %d\n\n",bWindow);
			wsprintf(&config_buf[strlen(config_buf)],";●影の表示\n;　0：影を表示しません。\n;　1：影を表示します。\n");
			wsprintf(&config_buf[strlen(config_buf)],"SHADOW = %d\n\n",SHADOW_CHECK);
			wsprintf(&config_buf[strlen(config_buf)],";●血の表示\n;　0：血を表示しません。\n;　1：血を表示します。\n");
			wsprintf(&config_buf[strlen(config_buf)],"BLOOD = %d\n\n",BLOOD_CHECK);
			wsprintf(&config_buf[strlen(config_buf)],";●サウンドの設定\n;　0：サウンドを使用しません。\n;　1：サウンドを使用します。\n");
			wsprintf(&config_buf[strlen(config_buf)],"SOUND = %d\n\n",SOUND_CHECK);
			wsprintf(&config_buf[strlen(config_buf)],";●FPS表示の設定\n;　0：FPSを表示しません。\n;　1：FPSを表示します。\n");
			wsprintf(&config_buf[strlen(config_buf)],"FPS = %d\n\n",FPS_CHECK);

			FILE *fp;
			fp = fopen(dir_buf,"w");
			fwrite(config_buf,strlen(config_buf),1,fp);
			fclose(fp);
			PostQuitMessage(0);				// システムにスレッドの終了を要求
			break;
		case WM_KEYDOWN:				//----- キーボードが押された
			switch(wParam) {
			case 'W':	g_bNoWait   = (g_bNoWait  )? false: true;	break;	// ウェイト切替

			case VK_ESCAPE:	if(GAME_STATE == 2){
								GAME_STATE = 0;				// [ESC]キーが押された
								key_trg = 1;
								BGMSound[1].Stop();
								Initialize_Data(hWnd);
							}

			break;
			}
			break;
		case WM_KEYUP:
			switch(wParam) {
			case 'Z': if(GAME_STATE == 2)player.attack_key = 0;break;
			case 'X': if(GAME_STATE == 2)player.jump_key = 0;	break;

			case VK_UP: key_trg = 0;	break;
			case VK_DOWN: key_trg = 0;	break;
			case VK_LEFT: key_trg = 0;	break;
			case VK_RIGHT: key_trg = 0;	break;

			break;
			}
			break;

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
	D3DXMatrixPerspectiveFovLH(&matProj,45 * RAD, ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
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
	char	str[1024];
	
	// ビューポートをクリア
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,60,60), 1.0, 0);

	if(SUCCEEDED(g_pD3DDevice->BeginScene())) {		// シーン開始

		DrawPat();		// パターンを描画

		// デバッグストリング描画
		if(FPS_CHECK == 1){
			str[0] = NULL;
			SetRect(&strRect, 0, 0, 640, 480);
			sprintf(str, "FPS : %4.1f\n", g_FPS);			// ＦＰＳを画面に描画するための文字列を作成
			g_pD3DXFont->DrawText(str, -1, &strRect, 0, D3DCOLOR_ARGB(0xff, 0xf0, 0xf0, 0xf0));
		}

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

	BeatCnt = 0;
	BeatTime = 0;
	MaxHit = 0;

	GAME_START_CNT = 60;
	GAME_START_FLG = 0;

	GAME_STATE = 0;
	MenuCheck = 0;
	GAME_END_CNT = 0;
	key_trg = 0;

	GAME_TIME = 99;
	GAME_TIME_CNT = 0;

	all_death = 0;

	Camera_Y = 0;
	Camera_Z = 0;

	main_material.Diffuse.r = 1.0f; 	// ゲーム本体用マテリアル設定
	main_material.Diffuse.g = 0.0f; 
	main_material.Diffuse.b = 0.0f; 
	main_material.Diffuse.a = 1.0f; 

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

	AllModel[0].SetModelData(hWnd,g_pD3DDevice,file_name_x,0);
	AllModel[1].SetModelData(hWnd,g_pD3DDevice,file_name_x,1);
	AllModel[2].SetModelData(hWnd,g_pD3DDevice,file_name_x,2);
	zintai.anime_max = 1;
	zintai.anime_time = 99;
	pZintai = stop_motion;

	EffectSound[0].Initialize(SoundFileName[0]);
	EffectSound[1].Initialize(SoundFileName[1]);
	EffectSound[2].Initialize(SoundFileName[2]);
	EffectSound[3].Initialize(SoundFileName[3]);
	EffectSound[4].Initialize(SoundFileName[4]);

	BGMSound[0].loop_flg = 1;
	BGMSound[0].Initialize(BGMFileName[0]);

	BGMSound[1].loop_flg = 1;
	BGMSound[1].Initialize(BGMFileName[1]);

	BGMSound[2].loop_flg = 1;
	BGMSound[2].Initialize(BGMFileName[2]);

	BGMSound[3].loop_flg = 1;
	BGMSound[3].Initialize(BGMFileName[3]);

	player.Initialize();

	model_manager.SetupModels(g_pD3DDevice,xfileinfo);

	for(i = 0; i < ENEMY_MAX; i++){
		test_enemy[i].Initialize(Def_Enemy[i]);
	}

	P_Tama.Initialize(Bbord_Data[BORD_TAMA],texture2_offset[TEXOFFSET2_TAMA]);
	P_Tama.pRect.bottom = 64;
	P_Tama.pRect.right = 64;
	P_Tama.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	for(i = 0; i < player.tama_max; i++){
		Player_Tama[i].SetData(Tama_Type_All[0]);
		Player_Tama[i].SetMove(1500000,1500000,1500000);
		BulletEffect[i].SetData(Tama_Type_All[0]);
		BulletEffect[i].SetMove(1500000,1500000,1500000);
	}
	Bullet.Initialize(Bbord_Data[BORD_BULLET],texture1_offset[TEXOFFSET1_BULLET]);
	Bullet.pRect.bottom = (long)(Bullet.pRect.bottom * 1.5);
	Bullet.pRect.right = (long)(Bullet.pRect.right * 1.5);
	Bullet.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	for(i = 0; i < ENEMY_MAX; i++){
		Enemy_Tama[i].SetData(Tama_Type_All[1]);
		Enemy_Tama[i].SetMove(1500000,1500000,1500000);
	}

	for(i = 0; i < YUKA_MAX; i++){
		BG[i].Initialize(Yuka_Data_Bottom[i]);	// 床初期化
		BG[i].SetModelData(hWnd,g_pD3DDevice,file_name_x,file_name_bg_mesh);

	}	

	LifeBord[0].Initialize(Bbord_Data[BORD_GAUGE],other_offset[OTHEROFFSET_GAUGE]);
	LifeBord[0].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	LifeBord[1].Initialize(Bbord_Data[BORD_BAR],other_offset[OTHEROFFSET_BAR]);
	LifeBord[1].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	//---タイトル画面初期化
	TitleBord[0].Initialize(Bbord_Data[BORD_TITLE],title_offset[TITLEOFFSET_TITLE]);
	TitleBord[0].pRect.bottom = 480;
	TitleBord[0].pRect.right = 640;
	TitleBord[0].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	TitleBord[1].Initialize(Bbord_Data[BORD_START],title_offset[TITLEOFFSET_START]);
	TitleBord[1].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	TitleBord[2].Initialize(Bbord_Data[BORD_OPTION],title_offset[TITLEOFFSET_OPTION]);
	TitleBord[2].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	TitleBord[3].Initialize(Bbord_Data[BORD_QUIT],title_offset[TITLEOFFSET_QUIT]);
	TitleBord[3].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);


	GameOverBord.Initialize(Bbord_Data[BORD_GAMEOVER],gameover_offset);
	GameOverBord.pRect.bottom = 480;
	GameOverBord.pRect.right = 640;
	GameOverBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	GameClearBord.Initialize(Bbord_Data[BORD_GAMECLEAR],gameclear_offset);
	GameClearBord.pRect.bottom = 480;
	GameClearBord.pRect.right = 640;
	GameClearBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	//---オプション画面用ボード初期化
	OptionBord[0].Initialize(Bbord_Data[BORD_OPTIONBORD],option_offset[OPTIONOFFSET_OPTION]);
	OptionBord[0].pRect.bottom = 480;
	OptionBord[0].pRect.right = 640;
	OptionBord[0].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	OptionBord[1].Initialize(Bbord_Data[BORD_BLOODON],option_offset[OPTIONOFFSET_ON]);
	OptionBord[1].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	OptionBord[2].Initialize(Bbord_Data[BORD_BLOODOFF],option_offset[OPTIONOFFSET_OFF]);
	OptionBord[2].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	OptionBord[3].Initialize(Bbord_Data[BORD_SHADOWON],option_offset[OPTIONOFFSET_ON]);
	OptionBord[3].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	OptionBord[4].Initialize(Bbord_Data[BORD_SHADOWOFF],option_offset[OPTIONOFFSET_OFF]);
	OptionBord[4].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	OptionBord[5].Initialize(Bbord_Data[BORD_EXIT],option_offset[OPTIONOFFSET_EXIT]);
	OptionBord[5].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);


	//---ビートエフェクト初期化
	BeatEffect.Initialize(Bbord_Data[BORD_BEAT],texture1_offset[TEXOFFSET1_BEAT]);
	BeatEffect.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	BeatEffect.draw_flg = 0;


	//---カウンタの数字エフェクト初期化
	CountEffect[0].Initialize(Bbord_Data[BORD_COUNTER1],texture1_offset[TEXOFFSET1_ONE]);
	CountEffect[0].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	CountEffect[0].draw_flg = 0;

	CountEffect[1].Initialize(Bbord_Data[BORD_COUNTER2],texture1_offset[TEXOFFSET1_ZERO]);
	CountEffect[1].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	CountEffect[1].draw_flg = 0;

	CountEffect[2].Initialize(Bbord_Data[BORD_COUNTER3],texture1_offset[TEXOFFSET1_ZERO]);
	CountEffect[2].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	CountEffect[2].draw_flg = 0;


	//---炎のエフェクト初期化
	FireEffect.Initialize(Bbord_Data[BORD_FIRE],texture1_offset[TEXOFFSET1_FIRE1]);
	FireEffect.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	FireEffect.draw_flg = 0;


	//---マズルフラッシュエフェクト初期化
	Muzzle_Flash.Initialize(Bbord_Data[BORD_FLASH],texture2_offset[TEXOFFSET2_FLASH2]);
	Muzzle_Flash.pRect.bottom = MUZZLEFLASH_SIZE_X;
	Muzzle_Flash.pRect.right = MUZZLEFLASH_SIZE_Y;
	Muzzle_Flash.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	Muzzle_Flash.draw_flg = 0;


	Shadow.Initialize(Bbord_Data[BORD_SHADOW],shadow_offset);
	Shadow.pRect.bottom = 450;
	Shadow.pRect.right = 450;
	Shadow.mat.Diffuse.a = 0.5f;
	Shadow.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	Shadow.rotx = 1.5f;

	EnemyHitBord.Initialize(Bbord_Data[BORD_FLASH2],texture2_offset[TEXOFFSET2_FLASH]);
	EnemyHitBord.pRect.bottom = HITFLASH_SIZE_X;
	EnemyHitBord.pRect.right = HITFLASH_SIZE_Y;
	EnemyHitBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);
	EnemyHitBord.draw_flg = 0;

	Blood.Initialize(Bbord_Data[BORD_BLOOD],texture2_offset[TEXOFFSET2_BLOOD]);
	Blood.pRect.bottom = BLOOD_SIZE_X;
	Blood.pRect.right = BLOOD_SIZE_Y;
	Blood.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	Sparks.Initialize(Bbord_Data[BORD_BLOOD],texture2_offset[TEXOFFSET2_SPARKS]);
	Sparks.pRect.bottom = SPARKS_SIZE_X;
	Sparks.pRect.right = SPARKS_SIZE_Y;
	Sparks.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	StartBord[0].Initialize(Bbord_Data[BORD_READY],other_offset[OTHEROFFSET_READY]);
	StartBord[0].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	StartBord[1].Initialize(Bbord_Data[BORD_GO],other_offset[OTHEROFFSET_GO]);
	StartBord[1].SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	for(i = 0;i < BLOOD_MAX;i++){
		BloodEffect[i].SetData(Tama_Type_All[0]);
		BloodEffect[i].SetMove(1500000,1500000,1500000);
	}

	for(i = 0;i < SPARKS_MAX;i++){
		SparksEffect[i].SetData(Tama_Type_All[0]);
		SparksEffect[i].SetMove(1500000,1500000,1500000);
	}

	ScoreBord.Initialize(Bbord_Data[BORD_SCORE],score_offset[SCOREOFFSET_SCORE]);
	ScoreBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	TotalBord.Initialize(Bbord_Data[BORD_TOTAL],score_offset[SCOREOFFSET_TOTAL]);
	TotalBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	MaxBord.Initialize(Bbord_Data[BORD_MAXHIT],score_offset[SCOREOFFSET_MAXHIT]);
	MaxBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	NumBord.Initialize(Bbord_Data[BORD_NUM],score_offset[SCOREOFFSET_ZERO]);
	NumBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	KakeBord.Initialize(Bbord_Data[BORD_KAKE],score_offset[SCOREOFFSET_KAKE]);
	KakeBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	TimeBord.Initialize(Bbord_Data[BORD_TIME],score_offset[SCOREOFFSET_TIME]);
	TimeBord.SetModelData(hWnd,g_pD3DDevice,file_name_bg_mesh);

	BGMSound[0].Play();

}


void ExecPat(HWND hWnd,LPDIRECT3DDEVICE8 p_Device)
{
	switch(GAME_STATE){
		case 0:
		if(GAME_START_FLG == 0){
			if(GetAsyncKeyState(VK_UP	) & 0x8000 && key_trg == 0){
				key_trg = 1;
				MenuCheck--;
				EffectSound[1].Play();
			}
			if(GetAsyncKeyState(VK_DOWN	) & 0x8000 && key_trg == 0){
				key_trg = 1;
				MenuCheck++;
				EffectSound[1].Play();
			}
			if(MenuCheck <= 0)MenuCheck = 0;
			if(MenuCheck >= 2)MenuCheck = 2;
		}

		switch(MenuCheck){
			case 0: // タイトル画面
				TitleBord[1].mat.Emissive.r = 1.0f; 
				TitleBord[1].mat.Emissive.g = 1.0f; 
				TitleBord[1].mat.Emissive.b = 1.0f; 
				TitleBord[2].mat.Emissive.r = 0.3f; 
				TitleBord[2].mat.Emissive.g = 0.3f; 
				TitleBord[2].mat.Emissive.b = 0.3f; 
				TitleBord[3].mat.Emissive.r = 0.3f; 
				TitleBord[3].mat.Emissive.g = 0.3f; 
				TitleBord[3].mat.Emissive.b = 0.3f;
				if(GetAsyncKeyState('Z') & 0x8000 && key_trg == 0){
					if(GAME_START_FLG == 0) EffectSound[0].Play();
					GAME_START_FLG = 1;
				}
				break;
			case 1:
				TitleBord[1].mat.Emissive.r = 0.3f; 
				TitleBord[1].mat.Emissive.g = 0.3f; 
				TitleBord[1].mat.Emissive.b = 0.3f; 
				TitleBord[2].mat.Emissive.r = 1.0f; 
				TitleBord[2].mat.Emissive.g = 1.0f; 
				TitleBord[2].mat.Emissive.b = 1.0f; 
				TitleBord[3].mat.Emissive.r = 0.3f; 
				TitleBord[3].mat.Emissive.g = 0.3f; 
				TitleBord[3].mat.Emissive.b = 0.3f; 
				if(GetAsyncKeyState('Z') & 0x8000 && key_trg == 0){
					if(GAME_START_FLG == 0) EffectSound[0].Play();					
					GAME_START_FLG = 2;
				}
			break;
			case 2:
				TitleBord[1].mat.Emissive.r = 0.3f; 
				TitleBord[1].mat.Emissive.g = 0.3f; 
				TitleBord[1].mat.Emissive.b = 0.3f; 
				TitleBord[2].mat.Emissive.r = 0.3f; 
				TitleBord[2].mat.Emissive.g = 0.3f; 
				TitleBord[2].mat.Emissive.b = 0.3f; 
				TitleBord[3].mat.Emissive.r = 1.0f; 
				TitleBord[3].mat.Emissive.g = 1.0f; 
				TitleBord[3].mat.Emissive.b = 1.0f; 
				if(GetAsyncKeyState('Z') & 0x8000 && key_trg == 0){
					if(GAME_START_FLG == 0) EffectSound[0].Play();					
					GAME_START_FLG = 3;
				}
				break;
		}
		if(GAME_START_FLG == 1){
			GAME_START_CNT--;
			if((GAME_START_CNT / 5)&0x0001)TitleBord[1].draw_flg = 0;
			else{
				TitleBord[1].draw_flg = 1;
			}
			if(GAME_START_CNT <= 0){
				GAME_STATE = 2;
				BGMSound[0].Stop();
				BGMSound[1].Play();
				GAME_START_CNT = START_COUNT;
			}
		}
		if(GAME_START_FLG == 2){
			GAME_START_CNT--;
			if((GAME_START_CNT / 5)&0x0001)TitleBord[2].draw_flg = 0;
			else{
				TitleBord[2].draw_flg = 1;
			}
			if(GAME_START_CNT <= 0){
				GAME_STATE = 1;
				MenuCheck = 0;
				BGMSound[0].Stop();
				BGMSound[2].Play();
			}
		}		
		if(GAME_START_FLG == 3){
			GAME_START_CNT--;
			if((GAME_START_CNT / 5)&0x0001)TitleBord[3].draw_flg = 0;
			else{
				TitleBord[3].draw_flg = 1;
			}
			if(GAME_START_CNT <= 0){
				g_bQuit = true;
			}
		}
		break;

		case 1: // オプション画面
		if(GetAsyncKeyState(VK_UP	) & 0x8000 && key_trg == 0){
			key_trg = 1;
			MenuCheck--;
			EffectSound[1].Play();
		}
		if(GetAsyncKeyState(VK_DOWN	) & 0x8000 && key_trg == 0){
			key_trg = 1;
			MenuCheck++;
			EffectSound[1].Play();
		}
		if(MenuCheck <= 0)MenuCheck = 0;
		if(MenuCheck >= 2)MenuCheck = 2;

		switch(MenuCheck){
			case 0: // 1段目
				if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && key_trg == 0){
					key_trg = 1;
					BLOOD_CHECK = 0;
					EffectSound[1].Play();
				}
				if(GetAsyncKeyState(VK_LEFT	) & 0x8000 && key_trg == 0){
					key_trg = 1;
					BLOOD_CHECK = 1;
					EffectSound[1].Play();
				}
				if(GetAsyncKeyState('X') & 0x8000 && key_trg == 0){
					EffectSound[0].Play();					
					GAME_STATE = 0;
					MenuCheck = 1;
					GAME_START_FLG = 0;
					GAME_START_CNT = 60;
					key_trg = 1;
					BGMSound[2].Stop();
					BGMSound[0].Play();
				}

				if(BLOOD_CHECK == 0){
					OptionBord[1].mat.Emissive.r = 0.5f; 
					OptionBord[1].mat.Emissive.g = 0.5f; 
					OptionBord[1].mat.Emissive.b = 0.5f; 
					OptionBord[2].mat.Emissive.r = 1.0f; 
					OptionBord[2].mat.Emissive.g = 1.0f; 
					OptionBord[2].mat.Emissive.b = 1.0f; 
				}else if(BLOOD_CHECK == 1){
					OptionBord[1].mat.Emissive.r = 1.0f; 
					OptionBord[1].mat.Emissive.g = 1.0f; 
					OptionBord[1].mat.Emissive.b = 1.0f; 
					OptionBord[2].mat.Emissive.r = 0.5f; 
					OptionBord[2].mat.Emissive.g = 0.5f; 
					OptionBord[2].mat.Emissive.b = 0.5f; 
				}
				if(SHADOW_CHECK == 0){
					OptionBord[3].mat.Emissive.r = 0.3f; 
					OptionBord[3].mat.Emissive.g = 0.3f; 
					OptionBord[3].mat.Emissive.b = 0.3f;
					OptionBord[4].mat.Emissive.r = 0.7f; 
					OptionBord[4].mat.Emissive.g = 0.7f; 
					OptionBord[4].mat.Emissive.b = 0.7f;
				}else if(SHADOW_CHECK == 1){
					OptionBord[3].mat.Emissive.r = 0.7f; 
					OptionBord[3].mat.Emissive.g = 0.7f; 
					OptionBord[3].mat.Emissive.b = 0.7f;
					OptionBord[4].mat.Emissive.r = 0.3f; 
					OptionBord[4].mat.Emissive.g = 0.3f; 
					OptionBord[4].mat.Emissive.b = 0.3f;
				}
				OptionBord[5].mat.Emissive.r = 0.3f; 
				OptionBord[5].mat.Emissive.g = 0.3f; 
				OptionBord[5].mat.Emissive.b = 0.3f;

				break;
			case 1:
				if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && key_trg == 0){
					key_trg = 1;
					SHADOW_CHECK = 0;
					EffectSound[1].Play();
				}
				if(GetAsyncKeyState(VK_LEFT	) & 0x8000 && key_trg == 0){
					key_trg = 1;
					SHADOW_CHECK = 1;
					EffectSound[1].Play();
				}

				if(BLOOD_CHECK == 0){
					OptionBord[1].mat.Emissive.r = 0.3f; 
					OptionBord[1].mat.Emissive.g = 0.3f; 
					OptionBord[1].mat.Emissive.b = 0.3f; 
					OptionBord[2].mat.Emissive.r = 0.7f; 
					OptionBord[2].mat.Emissive.g = 0.7f; 
					OptionBord[2].mat.Emissive.b = 0.7f; 
				}else if(BLOOD_CHECK == 1){
					OptionBord[1].mat.Emissive.r = 0.7f; 
					OptionBord[1].mat.Emissive.g = 0.7f; 
					OptionBord[1].mat.Emissive.b = 0.7f; 
					OptionBord[2].mat.Emissive.r = 0.3f; 
					OptionBord[2].mat.Emissive.g = 0.3f; 
					OptionBord[2].mat.Emissive.b = 0.3f; 
				}
				if(SHADOW_CHECK == 0){
					OptionBord[3].mat.Emissive.r = 0.5f; 
					OptionBord[3].mat.Emissive.g = 0.5f; 
					OptionBord[3].mat.Emissive.b = 0.5f;
					OptionBord[4].mat.Emissive.r = 1.0f; 
					OptionBord[4].mat.Emissive.g = 1.0f; 
					OptionBord[4].mat.Emissive.b = 1.0f;
				}else if(SHADOW_CHECK == 1){
					OptionBord[3].mat.Emissive.r = 1.0f; 
					OptionBord[3].mat.Emissive.g = 1.0f; 
					OptionBord[3].mat.Emissive.b = 1.0f;
					OptionBord[4].mat.Emissive.r = 0.5f; 
					OptionBord[4].mat.Emissive.g = 0.5f; 
					OptionBord[4].mat.Emissive.b = 0.5f;
				}
				OptionBord[5].mat.Emissive.r = 0.3f; 
				OptionBord[5].mat.Emissive.g = 0.3f; 
				OptionBord[5].mat.Emissive.b = 0.3f;

			break;
			case 2:
				if(BLOOD_CHECK == 0){
					OptionBord[1].mat.Emissive.r = 0.3f; 
					OptionBord[1].mat.Emissive.g = 0.3f; 
					OptionBord[1].mat.Emissive.b = 0.3f;
					OptionBord[2].mat.Emissive.r = 0.7f; 
					OptionBord[2].mat.Emissive.g = 0.7f; 
					OptionBord[2].mat.Emissive.b = 0.7f;
				}else if(BLOOD_CHECK == 1){
					OptionBord[1].mat.Emissive.r = 0.7f; 
					OptionBord[1].mat.Emissive.g = 0.7f; 
					OptionBord[1].mat.Emissive.b = 0.7f;
					OptionBord[2].mat.Emissive.r = 0.3f; 
					OptionBord[2].mat.Emissive.g = 0.3f; 
					OptionBord[2].mat.Emissive.b = 0.3f;
				}
				if(SHADOW_CHECK == 0){
					OptionBord[3].mat.Emissive.r = 0.3f; 
					OptionBord[3].mat.Emissive.g = 0.3f; 
					OptionBord[3].mat.Emissive.b = 0.3f;
					OptionBord[4].mat.Emissive.r = 0.7f; 
					OptionBord[4].mat.Emissive.g = 0.7f; 
					OptionBord[4].mat.Emissive.b = 0.7f;
				}else if(SHADOW_CHECK == 1){
					OptionBord[3].mat.Emissive.r = 0.7f; 
					OptionBord[3].mat.Emissive.g = 0.7f; 
					OptionBord[3].mat.Emissive.b = 0.7f;
					OptionBord[4].mat.Emissive.r = 0.3f; 
					OptionBord[4].mat.Emissive.g = 0.3f; 
					OptionBord[4].mat.Emissive.b = 0.3f;
				}
				OptionBord[5].mat.Emissive.r = 1.0f; 
				OptionBord[5].mat.Emissive.g = 1.0f; 
				OptionBord[5].mat.Emissive.b = 1.0f;
				if(GetAsyncKeyState('Z') & 0x8000 && key_trg == 0){
					EffectSound[0].Play();					
					GAME_STATE = 0;
					MenuCheck = 1;
					GAME_START_FLG = 0;
					GAME_START_CNT = 60;
					key_trg = 1;
					BGMSound[2].Stop();
					BGMSound[0].Play();
				}

				break;
		}
		break;

		case 2: // ゲーム本編
		if(GAME_START_CNT == 0){
			GAME_START_CNT = -1;
			StartBord[0].draw_flg = 0;
			StartBord[1].draw_flg = 0;
			EffectSound[0].Play();
		}

		if(GAME_START_CNT <= 0){ 
			//---------プレイヤー関数呼び出し-------------
	//		player.GetEnemyPos(test_enemy);
			
			player.GetKey(Player_Tama,&EffectSound[2]);

			if(player.flash_flg == 1){
				for(i = 0; i <= player.tama_max; i++){
					if(BulletEffect[i].trg == 0){
						BulletEffect[i].EffectSet3(&player.pos,player.dir);
						i = player.tama_max;
					}
				}
			}

			player.Flash(&Muzzle_Flash);

			Muzzle_Flash.Timer();
			
			player.Jump(Jump_Offset);
			for(i = 0; i < player.tama_max; i++){
				Player_Tama[i].Move();
				BulletEffect[i].Move();
			}
			
			for(i = 0; i < ENEMY_MAX ; i++){
				test_enemy[i].GetEnemyPos(player.pos);
				test_enemy[i].Move(&Enemy_Tama[i],&EffectSound[4]);
				test_enemy[i].DeathChecker(Def_Enemy);
				Enemy_Tama[i].Move();
				if(Enemy_Tama[i].trg == 1) PlayerHitCheck(&Enemy_Tama[i]);
			}

			//---------エフェクト処理---------------------

			FireEffect.OffsetAnimation(&texture1_offset[TEXOFFSET1_FIRE1]);

			for(i = 0; i < ENEMY_MAX; i++){
				for(int j = 0; j < player.tama_max; j++){
					if(Player_Tama[j].trg == 1) EnemyHitCheck(&test_enemy[i],&Player_Tama[j]);
				}
			}


			if(BeatTime >= 0){
				BeatTime--;
				if(BeatTime == 0){
					BeatCnt = 0;
					FireEffect.draw_flg = 0;
					FireEffect.anime_cnt = 0;
					BeatEffect.draw_flg = 0;
					CountEffect[0].draw_flg = 0;
					CountEffect[0].anime_cnt = 0;
					CountEffect[1].draw_flg = 0;
					CountEffect[1].anime_cnt = 0;
					CountEffect[2].draw_flg = 0;
					CountEffect[2].anime_cnt = 0;
				}
			}

			EnemyHitBord.Timer();
			if(BLOOD_CHECK == 1){
				for(i = 0; i <= BLOOD_MAX-1; i++){
					BloodEffect[i].Move();
				}
			}

			for(i = 0; i <= SPARKS_MAX; i++){
				SparksEffect[i].Move();
			}

		}
		else {
			StartBord[0].y -= 3;
			if(StartBord[0].y <= POS_READY_Y){
				StartBord[0].draw_flg = 0;
				StartBord[1].y = POS_GO_Y;
				if(GAME_START_CNT >= 0)GAME_START_CNT--;
				Camera_Y += 6;
				Camera_Z -= 4;
			}
		}
		break;
		case 3:
			if(GetAsyncKeyState('Z') & 0x8000 && key_trg == 0){
				BGMSound[3].Stop();
				Initialize_Data(hWnd);
			}

		break;
		case 4:
			if(GetAsyncKeyState('Z') & 0x8000 && key_trg == 0){
				BGMSound[3].Stop();
				Initialize_Data(hWnd);
			}

		break;

	}
}



//---------------------------------------------------------------------------------------
//　描画処理
//---------------------------------------------------------------------------------------
void DrawPat()
{
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x90, 0xc0), 1.0f, 0);

	switch(GAME_STATE){
		case 0:
			g_pD3DDevice->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定

			//**************タイトル画面描画******************
			D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
			D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
			g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
			g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);

			TitleBord[0].SetRot();
			TitleBord[0].Draw(g_pD3DDevice);

			TitleBord[1].SetRot();
			TitleBord[1].Draw(g_pD3DDevice);

			TitleBord[2].SetRot();
			TitleBord[2].Draw(g_pD3DDevice);

			TitleBord[3].SetRot();
			TitleBord[3].Draw(g_pD3DDevice);

		break;

		case 1:
			g_pD3DDevice->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定

			//**************オプション画面描画******************
			D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
			D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
			g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
			g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);

			OptionBord[0].SetRot();
			OptionBord[0].Draw(g_pD3DDevice);
			OptionBord[1].SetRot();
			OptionBord[1].Draw(g_pD3DDevice);
			OptionBord[2].SetRot();
			OptionBord[2].Draw(g_pD3DDevice);
			OptionBord[3].SetRot();
			OptionBord[3].Draw(g_pD3DDevice);
			OptionBord[4].SetRot();
			OptionBord[4].Draw(g_pD3DDevice);
			OptionBord[5].SetRot();
			OptionBord[5].Draw(g_pD3DDevice);
		break;


		case 2:

		//**************フォグの設定******************

			fog_start = player.pos.z + 3000.0f;
			fog_end = player.pos.z + 70000.0f;

			g_pD3DDevice->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定
			g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					// フォグの設定
			g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR,0x0ff0f0f0);				// フォグの設定
			g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE,D3DFOG_LINEAR);		// フォグの設定
			g_pD3DDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD *)&fog_start);		// フォグの設定
			g_pD3DDevice->SetRenderState(D3DRS_FOGEND,*(DWORD *)&fog_end);			// フォグの設定


		//**************ゲームメイン描画******************
			SetView();

			for(i = 0;i < YUKA_MAX;i++){
				BG[i].SetRot();
				BG[i].Draw(g_pD3DDevice);
			}


			if(SHADOW_CHECK == 1){

				Shadow.x = (float)(player.pos.x - SHADOW_OFFSET_X - sin(player.dir) * 70);
				Shadow.y = -490;
				Shadow.z = (float)(player.pos.z - SHADOW_OFFSET_Z - cos(player.dir) * 70);
				Shadow.SetRot();
				Shadow.Draw(g_pD3DDevice);
				
				for(i = 0; i < ENEMY_MAX; i++){
					if(test_enemy[i].death == 0){
						Shadow.x = (float)(test_enemy[i].pos.x - SHADOW_OFFSET_X - sin(test_enemy[i].rot.y) * 70);
						Shadow.y = -490;
						Shadow.z = (float)(test_enemy[i].pos.z - SHADOW_OFFSET_Z - cos(test_enemy[i].rot.y) * 70);
						Shadow.SetRot();
						Shadow.Draw(g_pD3DDevice);
					}
				}
			}

			if(BLOOD_CHECK == 1){
				for(i = 0; i < BLOOD_MAX; i++){
					if(BloodEffect[i].trg == 1){
						BloodEffect[i].SetRot();
						Blood.matrix = BloodEffect[i].matrix;
						BloodEffect[i].Draw(g_pD3DDevice,&Blood,viewMat);
					}
				}
			}

			for(i = 0; i < SPARKS_MAX; i++){
				if(SparksEffect[i].trg == 1){
					SparksEffect[i].SetRot();
					Sparks.matrix = SparksEffect[i].matrix;
					SparksEffect[i].Draw(g_pD3DDevice,&Sparks,viewMat);
				}
			}

			for(i = 0; i < player.tama_max; i++){
				if(Player_Tama[i].trg == 1){
					Player_Tama[i].SetRot();
					P_Tama.matrix = Player_Tama[i].matrix;
					Player_Tama[i].Draw(g_pD3DDevice,&P_Tama,viewMat);
				}

				if(BulletEffect[i].trg == 1){
					BulletEffect[i].SetRot();
					Bullet.matrix = BulletEffect[i].matrix;	
					if(BulletEffect[i].y >= -490){
						 BulletEffect[i].Draw(g_pD3DDevice,&Bullet,viewMat);
					}
					else if((BulletEffect[i].effect_cnt % 8) != 0){
						 BulletEffect[i].Draw(g_pD3DDevice,&Bullet,viewMat);
					}

				}

			}


			for(i = 0; i < ENEMY_MAX; i++){
				if(Enemy_Tama[i].trg == 1){
					Enemy_Tama[i].SetRot();
					P_Tama.matrix = Enemy_Tama[i].matrix;
					Enemy_Tama[i].Draw(g_pD3DDevice,&P_Tama,viewMat);
				}
			}

			Muzzle_Flash.SetRot();
			Muzzle_Flash.Draw(g_pD3DDevice,viewMat);

			for(i = 0; i < ENEMY_MAX; i++){
				test_enemy[i].Draw(g_pD3DDevice,&AllModel[ENEMY_MODEL]);

//				ZintaiManager();
//				zintai.Animation(pZintai,&test_enemy[i].pos,&test_enemy[i].rot);
//				zintai.Draw(g_pD3DDevice,&model_manager,test_enemy[i].hit);	
			}

			EnemyHitBord.SetRot();
			EnemyHitBord.Draw(g_pD3DDevice,viewMat);

//			player.Draw(g_pD3DDevice,&AllModel[PLAYER_MODEL]);
			player.HitCheck();

			ZintaiManager();
			zintai.Animation(pZintai,&player.pos,&player.rot);
			zintai.Draw(g_pD3DDevice,&model_manager,player.hit,player.jump_trg);	

			D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
			D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
			g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
			g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);
			if(GAME_TIME == 0){
				BGMSound[1].Stop();
				BGMSound[3].Play();
				key_trg = 1;
				GAME_TIME = -1;
			}else if(GAME_TIME >= 0){
				TimeCounter();
			}
			if(GAME_TIME == -1){
				ScoreCounter();
			}

			StartBord[0].SetRot();
			StartBord[0].Draw(g_pD3DDevice);

			StartBord[1].SetRot();
			StartBord[1].Draw(g_pD3DDevice);

			FireEffect.SetRot();
			FireEffect.Draw(g_pD3DDevice);

			BeatEffect.SetRot();
			BeatEffect.Draw(g_pD3DDevice);

			CountEffect[0].SetRot();
			CountEffect[0].Draw(g_pD3DDevice);

			CountEffect[1].SetRot();
			CountEffect[1].Draw(g_pD3DDevice);

			CountEffect[2].SetRot();
			CountEffect[2].Draw(g_pD3DDevice);

			LifeBord[0].SetRot();
			LifeBord[0].Draw(g_pD3DDevice);
			LifeBord[1].SetRot();
			LifeBord[1].Draw(g_pD3DDevice);

		break;

		case 3:
		//**************ゲームオーバー描画******************
			D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
			D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
			g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
			g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);

			GameOverBord.SetRot();
			GameOverBord.Draw(g_pD3DDevice);

		break;
		case 4:
		//**************ゲームクリア描画******************
			D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
			D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
			g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
			g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);

			GameClearBord.SetRot();
			GameClearBord.Draw(g_pD3DDevice);

		break;


	}



}


//---------------------------------------------------------------------------------------
//　当たり判定処理
//---------------------------------------------------------------------------------------

void EnemyHitCheck(ENEMY* pEnemy ,TAMA* pTama){

	POSITION wPos;
	if(pEnemy->death == 0 && pEnemy->hit == 0){
		if(pEnemy->pos.x  - TAMA_SIZE - 70 <= pTama->x && pEnemy->pos.x + 200.0 >= pTama->x){
			if(pEnemy->pos.y - TAMA_SIZE - 70 <= pTama->y && pEnemy->pos.y + 450.0 >= pTama->y){
				if(pEnemy->pos.z  - TAMA_SIZE - 70 <= pTama->z && pEnemy->pos.z + 200.0 >= pTama->z){
						pEnemy->SetHp(pTama->damage);
						EffectSound[3].Play();

						wPos.x = pTama->x;
						wPos.y = pTama->y;
						wPos.z = pTama->z;
						pEnemy->DamegeHit(&EnemyHitBord,wPos);
						wPos.x = pTama->x;


						if(pEnemy->death == 1){
							all_death++;
							EffectSound[0].Play();
							wPos.y = -480;
							for(i = 0;i <= SPARKS_MAX-1;i++){
								SparksEffect[i].EffectSet2(&wPos);
								if(i % 2 == 1) SparksEffect[i].dx *= -1;  
							}
						}
						else if(BLOOD_CHECK == 1){
							for(i = 0;i <= BLOOD_MAX-1;i++){
								BloodEffect[i].EffectSet(&wPos);
								if(i % 2 == 1) BloodEffect[i].dx *= -1;  
							}
						}


						BeatCounter();
						pTama->SetPoint(80000,80000,80000);
						pTama->trg = 0;
				}
			}
		}
	}
}
void PlayerHitCheck(TAMA* pTama) {

	if(player.death == 0 && player.hit == 0){
		if(player.pos.x - TAMA_SIZE  - 40 <= pTama->x && player.pos.x + 100.0 >= pTama->x){
			if(player.pos.y - TAMA_SIZE  - 40 <= pTama->y && player.pos.y + 100.0 >= pTama->y){
				if(player.pos.z - TAMA_SIZE  - 40 <= pTama->z && player.pos.z + 100.0 >= pTama->z){

					player.SetHp(pTama->damage);

					player.DamegeHit(&EnemyHitBord,player.pos);
					EffectSound[1].Play();
					
					if(BLOOD_CHECK == 1){
						for(i = 0;i <= BLOOD_MAX-1;i++){
							BloodEffect[i].EffectSet(&player.pos);
							if(i % 2 == 1) BloodEffect[i].dx *= -1;  
						}
					}
					

					LifeBord[1].SetPPoint( ((float)(player.hp_max / pTama->damage) - 1),0,0);
					
					pTama->SetPoint(80000,80000,80000);
					pTama->trg = 0;
					if(player.death == 1 || player.hp <= 0){
						BGMSound[1].Stop();
						player.status = DEATH;
					}
					g_pD3DDevice->SetMaterial(&main_material);
					g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
					g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);

					pTama->trg = 0;
				}
			}
		}
	}

}

void BeatCounter(){
	int work;

	FireEffect.draw_flg = 1;
	BeatEffect.draw_flg = 1;
	CountEffect[0].draw_flg = 1;
	BeatTime = BEAT_WAIT_TIME;
	BeatCnt++;
	if(BeatCnt >= 999) BeatCnt = 999;
	if(BeatCnt > MaxHit) MaxHit = BeatCnt;
	CountEffect[0].anime_frame = BeatCnt % 10;
	CountEffect[0].anime_cnt = 0;
	CountEffect[0].FrameAnimation(texture1_offset);
	if(BeatCnt >= 10){
		work = BeatCnt;
		(int)work /= 10;
		if(work >= 10) work %= 10;
		CountEffect[1].draw_flg = 1;
		CountEffect[1].anime_frame = work;
		CountEffect[1].anime_cnt = 0;
		CountEffect[1].FrameAnimation(texture1_offset);
	}
	if(BeatCnt >= 100){
		work = BeatCnt;
		(int)work /= 100;
		if(work >= 10 ) work %= 10;
		CountEffect[2].draw_flg = 1;
		CountEffect[2].anime_frame = work;
		CountEffect[2].anime_cnt = 0;
		CountEffect[2].FrameAnimation(texture1_offset);
	}
}

void ZintaiManager(){
		if(player.hit == 1){
			player.status = DAMAGE;
		}

		switch(player.status){
			case STAND:
				if(zintai.anime_end == 1){
					zintai.anime_max = 1;
					zintai.anime_time = 99;
					pZintai = stop_motion;
				}
				break;
			case DASH:
				if(zintai.anime_end == 1){
					zintai.anime_max = 8;
					zintai.anime_time = 99;
					pZintai = dash_motion;
				}
				break;
			case BACK:
				if(zintai.anime_end == 1){
					zintai.anime_max = 7;
					zintai.anime_time = 99;
					pZintai = back_motion;
				}
				break;
			case LSTEP:
				if(zintai.anime_end == 1){
					zintai.anime_max = 1;
					zintai.anime_time = 99;
					pZintai = stop_motion;
				}
				break;
			case RSTEP:
				if(zintai.anime_end == 1){
					zintai.anime_max = 1;
					zintai.anime_time = 99;
					pZintai = stop_motion;
				}
				break;
			case LDASH:
				if(zintai.anime_end == 1){
					zintai.anime_max = 8;
					zintai.anime_time = 99;
					pZintai = dash_motion;
				}
				break;
			case RDASH:
				if(zintai.anime_end == 1){
					zintai.anime_max = 8;
					zintai.anime_time = 99;
					pZintai = dash_motion;
				}
				break;
			case LBACK:
				if(zintai.anime_end == 1){
					zintai.anime_max = 7;
					zintai.anime_time = 99;
					pZintai = back_motion;
				}
				break;
			case RBACK:
				if(zintai.anime_end == 1){
					zintai.anime_max = 7;
					zintai.anime_time = 99;
					pZintai = back_motion;
				}
				break;

			case ATTACK:
				if(zintai.anime_end == 1){
					zintai.anime_max = 6;
					zintai.anime_time = 99;
					pZintai = attack_motion;
				}
				break;
			case DAMAGE:
				if(zintai.anime_end == 1){
					zintai.anime_max = 2;
					zintai.anime_time = 99;
					pZintai = damage_motion;
				}
				break;
			case JUMP:
				if(zintai.anime_end == 1){
					zintai.anime_max = 1;
					zintai.anime_time = 99;
					pZintai = jump_motion;
				}
				break;				
			case DEATH:
				if(zintai.anime_end == 1){
					zintai.anime_max = 8;
					zintai.anime_time = 99;
					pZintai = death_motion;
					zintai.anime_end = 0;
				}
				break;				

		}
		if(zintai.anime_end == 1 && player.status == ATTACK && player.anime_flg == 1){
			player.anime_flg = 0;
			player.status = STAND;
		}
		if(player.status == DEATH && zintai.anime_frame == zintai.anime_max - 1){
			GAME_STATE = 3;
			BGMSound[3].Play();
		}

}
void ScoreCounter(){

	int work;

	D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
	D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
	g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);

	ScoreBord.SetRot();
	ScoreBord.Draw(g_pD3DDevice);

	TotalBord.SetRot();
	TotalBord.Draw(g_pD3DDevice);

	MaxBord.SetRot();
	MaxBord.Draw(g_pD3DDevice);

	//----敵撃破スコア
	NumBord.x = 280;
	NumBord.y = 305;
	NumBord.anime_frame = 3;
	NumBord.anime_cnt = 0;
	NumBord.FrameAnimation(score_offset);
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	NumBord.x = 260;
	NumBord.y = 305;
	NumBord.anime_frame = 0;
	NumBord.anime_cnt = 0;
	NumBord.FrameAnimation(score_offset);
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	NumBord.x = 240;
	NumBord.y = 305;
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	KakeBord.x = 180;
	KakeBord.y = 305;
	KakeBord.SetRot();
	KakeBord.Draw(g_pD3DDevice);

	NumBord.x = 280;
	NumBord.y = 205;
	NumBord.anime_frame = 1;
	NumBord.anime_cnt = 0;
	NumBord.FrameAnimation(score_offset);
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	NumBord.x = 260;
	NumBord.y = 205;
	NumBord.anime_frame = 0;
	NumBord.anime_cnt = 0;
	NumBord.FrameAnimation(score_offset);
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	NumBord.x = 240;
	NumBord.y = 205;
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	KakeBord.x = 180;
	KakeBord.y = 205;
	KakeBord.SetRot();
	KakeBord.Draw(g_pD3DDevice);

	score = (all_death * 300) + (MaxHit * 100);

	if(work_death <= all_death){
		work_death++;
	}
	else {
		work = work_death / 10;
		if(work != 0){
			NumBord.x = 125;
			NumBord.y = 305;
			NumBord.anime_frame = work;
			NumBord.anime_cnt = 0;
			NumBord.FrameAnimation(score_offset);
			NumBord.SetRot();
			NumBord.Draw(g_pD3DDevice);
		}

		work = work_death;
		work %= 10;
		NumBord.x = 100;
		NumBord.y = 305;
		NumBord.anime_frame = work;
		NumBord.anime_cnt = 0;
		NumBord.FrameAnimation(score_offset);
		NumBord.SetRot();
		NumBord.Draw(g_pD3DDevice);


		if(work_hit < MaxHit)work_hit++;
		work = work_hit / 100;
		if(work != 0){
			NumBord.x = 145;
			NumBord.y = 205;
			NumBord.anime_frame = work;
			NumBord.anime_cnt = 0;
			NumBord.FrameAnimation(score_offset);
			NumBord.SetRot();
			NumBord.Draw(g_pD3DDevice);
		}

		work = work_hit / 10;
		if(work != 0){
			NumBord.x = 125;
			NumBord.y = 205;
			NumBord.anime_frame = work;
			NumBord.anime_cnt = 0;
			NumBord.FrameAnimation(score_offset);
			NumBord.SetRot();
			NumBord.Draw(g_pD3DDevice);
		}

		work = work_hit % 10;
		NumBord.x = 100;
		NumBord.y = 205;
		NumBord.anime_frame = work;
		NumBord.anime_cnt = 0;
		NumBord.FrameAnimation(score_offset);
		NumBord.SetRot();
		NumBord.Draw(g_pD3DDevice);
	}

	work = score / 100000;
	work %= 10; 

	if(score > 100000){
		NumBord.x = 205;
		NumBord.y = 105;
		NumBord.anime_frame = work;
		NumBord.anime_cnt = 0;
		NumBord.FrameAnimation(score_offset);
		NumBord.SetRot();
		NumBord.Draw(g_pD3DDevice);
	}

	work = score / 10000;
	work %= 10; 
	if(score > 10000){
		NumBord.x = 185;
		NumBord.y = 105;
		NumBord.anime_frame = work;
		NumBord.anime_cnt = 0;
		NumBord.FrameAnimation(score_offset);
		NumBord.SetRot();
		NumBord.Draw(g_pD3DDevice);
	}

	work = score / 1000;
	work %= 10; 
	if(score > 1000){
		NumBord.x = 165;
		NumBord.y = 105;
		NumBord.anime_frame = work;
		NumBord.anime_cnt = 0;
		NumBord.FrameAnimation(score_offset);
		NumBord.SetRot();
		NumBord.Draw(g_pD3DDevice);
	}

	work = score / 100;
	work %= 10; 
	if(score > 100){
		NumBord.x = 145;
		NumBord.y = 105;
		NumBord.anime_frame = work;
		NumBord.anime_cnt = 0;
		NumBord.FrameAnimation(score_offset);
		NumBord.SetRot();
		NumBord.Draw(g_pD3DDevice);
	}

	work = score / 10;
	work %= 10; 
	if(score > 10){
		NumBord.x = 125;
		NumBord.y = 105;
		NumBord.anime_frame = work;
		NumBord.anime_cnt = 0;
		NumBord.FrameAnimation(score_offset);
		NumBord.SetRot();
		NumBord.Draw(g_pD3DDevice);
	}

	work = score % 10;
	NumBord.x = 100;
	NumBord.y = 105;
	NumBord.anime_frame = work;
	NumBord.anime_cnt = 0;
	NumBord.FrameAnimation(score_offset);
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	GAME_END_CNT++;

	if(GAME_END_CNT >= 300){
		GAME_STATE = 4;
		key_trg = 0;
	}
}
void TimeCounter(){

	int work;

	if(GAME_START_CNT <= 0){
		GAME_TIME_CNT++;
		if(GAME_TIME_CNT >= 60){
			GAME_TIME--;
			GAME_TIME_CNT = 0;
		}
	}

	D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
	D3DXMatrixPerspectiveLH(&persMat,640,480,300,0);
	g_pD3DDevice->SetTransform(D3DTS_VIEW,&viewMat);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION,&persMat);

	TimeBord.x = 250;
	TimeBord.y = 445;
	TimeBord.SetRot();
	TimeBord.Draw(g_pD3DDevice);

	work = GAME_TIME / 10;
	NumBord.x = 290;
	NumBord.y = 405;
	NumBord.anime_frame = work;
	NumBord.anime_cnt = 0;
	NumBord.FrameAnimation(score_offset);
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);

	work = GAME_TIME % 10;
	NumBord.x = 270;
	NumBord.y = 405;
	NumBord.anime_frame = work;
	NumBord.anime_cnt = 0;
	NumBord.FrameAnimation(score_offset);
	NumBord.SetRot();
	NumBord.Draw(g_pD3DDevice);


}

//---------------------------------------------------------------------------------------
//　視点設定処理
//---------------------------------------------------------------------------------------
void SetView(){

	if(player.jump_trg == 1){

		camera[0] = player.pos.x + (cosf(player.dir)+sinf(player.dir)*-1300.0f);
		camera[1] = player.pos.y + Camera_Y + 400;
		camera[2] = player.pos.z + (cosf(player.dir) + cosf(player.dir)*-1300.0f);

		if(player.target_trg == 1){
			ecamera[0] = player.enemy.x;
			ecamera[1] = player.enemy.y;
			ecamera[2] = player.enemy.z;
		}
		else {
			ecamera[0] = player.pos.x;
			ecamera[1] = player.pos.y;
			ecamera[2] = player.pos.z;
		}

		D3DXMatrixLookAtLH(&viewMat,
							&D3DXVECTOR3( camera[0], camera[1],camera[2]),					// 視点座標
							&D3DXVECTOR3( ecamera[0],ecamera[1],ecamera[2]),				// 注視点座標
							&D3DXVECTOR3(  0.0,  1.0,    0.0));								// アップベクトル
		g_pD3DDevice->SetTransform(D3DTS_VIEW, &viewMat);
	}
	else {
		camera[0] = player.pos.x + (cosf(player.dir)+sinf(player.dir)*-1300.0f);
		camera[1] = player.pos.y + Camera_Y + 400;
		camera[2] = player.pos.z + (cosf(player.dir) + cosf(player.dir)*-1300.0f);


		D3DXMatrixLookAtLH(&viewMat,
							&D3DXVECTOR3( camera[0], camera[1],camera[2]),					// 視点座標
							&D3DXVECTOR3(  player.pos.x, 200,player.pos.z),					// 注視点座標
							&D3DXVECTOR3(  0.0,  1.0,    0.0));								// アップベクトル
		g_pD3DDevice->SetTransform(D3DTS_VIEW, &viewMat);
	}

}
//=======================================================================================
//	end of files
//=======================================================================================
