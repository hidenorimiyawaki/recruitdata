//=================================================================================================
//    [ Shadow ] DirectX Graphics 3D sample
//    シャドウマトリックスサンプル
//
//    操作
//    　カーソル		視点移動
//
//=================================================================================================
//-------- インクルードヘッダ
#define STRICT
#include <windows.h>		// Windowsプログラムにはこれを付ける
#include <d3d8.h>			// DirectX Graphics 関連のヘッダー
#include <d3dx8.h>			// DirectX Graphics 関連のヘッダー
#include <stdio.h>			// 文字列処理で使用
#include <mmsystem.h>		// 時間管理で使用

//-------- ライブラリのリンク（こう記述しておけば別途リンク設定が不要となる）
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//-------- マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if(x){ x->Release(); x=NULL; }
#endif

//----- モデル、テクスチャ用ファイル名データ
char	*modelfile[]   = {"sozai/land.x"  , "sozai/donuts.x"  , };
char	*texturefile[] = {"sozai/land.bmp", "sozai/donuts.bmp", };
#define MODEL_QTY	2		// モデル総数
enum MODEL_SERIAL {
	MN_LAND = 0,
	MN_DONUTS,
};

//-------- 定数定義
#define CLASS_NAME		"Shadow"								// ウィンドウクラス名
#define CAPTION_NAME	"[ Shadow ] DirectX Sample Program"		// キャプション名

const float FRAME_RATE		= 1000/60;							// フレームレート
const int	SCREEN_WIDTH	= 640;								// スクリーンの幅
const int	SCREEN_HEIGHT	= 480;								// スクリーンの高さ
const float	PI				= (float)3.141592653589;			// 円周率
const float	RAD				= PI/180;							// ラジアン
const int	DONUTS_QTY		= 16;								// ドーナツの個数
const int	LIGHT_DETAIL	= 32;								// 点光源のディテールレベル

//----- 頂点フォーマット定義
struct VERTEX {
	float		x, y, z;			// 頂点座標（座標変換あり）
	float		nx, ny, nz;			// 法線ベクトル
	float		tu, tv;				// テクスチャ座標
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct TLVERTEX {
	float		x, y, z;			// 頂点座標（座標変換あり）
	DWORD		diffuse;			// ディフューズ
};
#define	FVF_TLVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

//----- 構造体定義
struct LAND {								//----- 地面
	int			status;							// ステータス
	D3DXMATRIX	matrix;							// ローカルワールド変換行列
};

struct DONUTS {								//----- ドーナツ
	int			status;							// ステータス
	D3DXVECTOR3	position;						// 座標
	D3DXVECTOR3	rotation;						// 回転量
	D3DXVECTOR3	rot_speed;						// 回転速度
	D3DXMATRIX	matrix;							// ローカルワールド変換行列
	D3DXMATRIX	shadow_matrix;					// シャドウワールド変換行列
};

struct POINTLIGHT {							//----- 点光源
	int			status;							// ステータス
	D3DXVECTOR3	position;						// 座標
	D3DXVECTOR3	base_cycle;						// 中心移動用回転値
	D3DXVECTOR3	base_speed;						// 中心移動用回転速度値
	TLVERTEX	vertex[LIGHT_DETAIL + 2];		// 頂点データ
	float		cycle[LIGHT_DETAIL + 2];		// 頂点変化サインカーブ角度値
 	float		speed[LIGHT_DETAIL + 2];		// 頂点変化サインカーブ角速度値
 	float		range1, range2;					// 頂点変化サインカーブ変化値
};

struct MODELINFO {							//----- モデル
	LPD3DXMESH				lpD3DXMesh;			// D3DXMESH インターフェイス
	LPDIRECT3DVERTEXBUFFER8	lpD3DVertexBuffer;	// Direct3DVertexBuffer8 オブジェクト
	LPDIRECT3DINDEXBUFFER8	lpD3DIndexBuffer;	// Direct3DIndexBuffer8 オブジェクト
	int						iNumVertex;			// 頂点数
	int						iNumIndex;			// インデックス数
	LPDIRECT3DTEXTURE8		lpD3DTexture;		// Direct3DTexture8 オブジェクト
};

//----- グローバル変数

// DirectX 関連
LPDIRECT3D8				g_pD3D;						// Direct3D8 オブジェクト
LPDIRECT3DDEVICE8		g_pD3DDevice;				// Direct3DDevice8 オブジェクト
D3DPRESENT_PARAMETERS	g_D3DPresentParam;			// プレゼンテーションパラメータ
LPD3DXFONT				g_pD3DXFont;				// D3DXFont オブジェクト
D3DLIGHT8				g_Light[2];					// D3DLIGHT8 オブジェクト

LAND					g_Land;						// 地面表示オブジェクト
DONUTS					g_Donuts[DONUTS_QTY];		// ドーナツ表示オブジェクト
POINTLIGHT				g_PointLight;				// 点光源オブジェクト
TLVERTEX				g_GuideLine[2];				// ガイドライン頂点データ
MODELINFO				g_ModelInfo[MODEL_QTY];		// 表示モデルオブジェクト

D3DXMATRIX				g_MatView;					// ビューマトリックス
float					g_fRotation;				// ビュー回転角
float					g_fHeight;					// ビュー高度
char					g_DebugStr[4096];			// 出力文字列バッファ
float					g_FPS;						// フレーム数カウント用

//----- プロトタイプ宣言
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
long Initialize3DEnvironment(HWND hWnd, bool bWindow);
HRESULT Cleanup3DEnvironment(HWND hWnd);
HRESULT Render3DEnvironment();
int SetModelData(HWND hWnd);
void ExecLand();
void DrawLand();
void ExecDonuts();
void DrawDonuts();
void DrawGuideLine();
void ExecPointLight();
void DrawPointLight();

//-------------------------------------------------------------------------------------------------
// メイン
//-------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow)
{
	HWND	hWnd;
	MSG		msg;
	DWORD	dwExecLastTime, dwFPSLastTime, dwCurrentTime, dwFrameCount;
	float	dt;
	bool	bWindow;

	// ウィンドウクラスを登録
	WNDCLASS wndClass = {
			CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInst, LoadIcon(hInst, IDI_APPLICATION),
			LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH), NULL, CLASS_NAME
	};
	if(RegisterClass(&wndClass) == 0) return false;
	
	// ウインドウを作成
	hWnd = CreateWindow(
		CLASS_NAME, CAPTION_NAME, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH  + GetSystemMetrics(SM_CXSIZEFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CYSIZEFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL, NULL, hInst, NULL);
	if(hWnd == 0) return false;

	bWindow = false;
	if(IDYES == MessageBox(hWnd, "ウィンドウモードで実行しますか？", "画面モード", MB_YESNO))
		bWindow = true;
	if(FAILED(Initialize3DEnvironment(hWnd, bWindow))) return 0;	// ３Ｄ環境の初期化

	// モデルデータの準備
	SetModelData(hWnd);

	// 変数初期化
	timeBeginPeriod(1);									// システムタイマーの分解能を１ｍｓに設定
	dwFPSLastTime = dwExecLastTime = timeGetTime();		// 現在のシステムタイマーを取得
	dwFrameCount = 0;
	g_fRotation = (float)RAD*(-90);
	g_fHeight = 400.0f;
	// オブジェクトステータスを初期化
	g_Land.status = 0;
	for(int i = 0; i < DONUTS_QTY; i++) {
		g_Donuts[i].status = 0;
	}
	g_PointLight.status = 0;

	// メインウインドウループ
    msg.message = WM_NULL;
	while(WM_QUIT != msg.message) {									// WM_QUIT がくるまでループ
		if(PeekMessage(&msg,NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			dwCurrentTime = timeGetTime();								// 現在のタイマー値を取得
			if(dwCurrentTime - dwFPSLastTime >= 500) {					// ０．５秒ごとに計測
				dt = (float)(dwCurrentTime - dwFPSLastTime) / 1000;		// フレーム数を計算
				g_FPS = (float)dwFrameCount / dt;
				dwFPSLastTime = dwCurrentTime;							// タイマー値を更新
				dwFrameCount = 0;										// フレームカウンタをリセット
			}
			// この辺で時間管理
			if(dwCurrentTime - dwExecLastTime >= FRAME_RATE) {			// 一定時間が経過したら・・・
				dwExecLastTime = dwCurrentTime;							// タイマー値を更新
				ExecLand();												// 地面処理
				ExecDonuts();											// ドーナツ処理
				ExecPointLight();										// 点光源処理
				Render3DEnvironment();									// 描画処理
				dwFrameCount++;											// フレームカウントを＋１
			}
		}
	}
	timeEndPeriod(1);						// システムタイマーの分解能を元に戻す
	Cleanup3DEnvironment(hWnd);
	return msg.wParam;
}

//-------------------------------------------------------------------------------------------------
// メッセージハンドラ
//-------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage) {
	case WM_DESTROY:
		ShowCursor(true);
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:	DestroyWindow(hWnd);	break;
		}
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------
// ３Ｄ環境の初期化
//-------------------------------------------------------------------------------------------------
HRESULT Initialize3DEnvironment(HWND hWnd, bool bWindow)
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
	D3DXMATRIX		matProj;			// プロジェクションマトリックス

	// Direct3D オブジェクトを作成
	g_pD3D = Direct3DCreate8(D3D_SDK_VERSION);
	if(!g_pD3D) {
		MessageBox(NULL, "Direct3D オブジェクトの作成に失敗しました。", "Error", MB_OK | MB_ICONSTOP);
		return E_FAIL;
	}
	// Direct3D 初期化パラメータを設定
	ZeroMemory(&g_D3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));
	if(bWindow)	{
		// ウィンドウモード
		g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp);	// 現在の画面モードを取得
		g_D3DPresentParam.BackBufferFormat = disp.Format;
		g_D3DPresentParam.Windowed = 1;
		g_D3DPresentParam.FullScreen_RefreshRateInHz = 0;
		g_D3DPresentParam.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	} else {
		// フルスクリーンモード
		ShowCursor(false);
		g_D3DPresentParam.BackBufferFormat = D3DFMT_R5G6B5;
		g_D3DPresentParam.Windowed = 0;
		g_D3DPresentParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		g_D3DPresentParam.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// VSYNCを待たない
	}
	// 表示領域サイズの設定
	g_D3DPresentParam.BackBufferWidth  = SCREEN_WIDTH;
	g_D3DPresentParam.BackBufferHeight = SCREEN_HEIGHT;
	g_D3DPresentParam.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	// Ｚバッファの自動作成
	g_D3DPresentParam.EnableAutoDepthStencil = 1;
	g_D3DPresentParam.AutoDepthStencilFormat = D3DFMT_D16;

	// デバイスオブジェクトを作成
	for(nDev = 0; nDev < c_nMaxDevice; nDev++) {
		if(SUCCEEDED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, device[nDev].type, hWnd,	// デバイスを作成
					device[nDev].behavior, &g_D3DPresentParam, &g_pD3DDevice))) break;
	}
	if(nDev >= c_nMaxDevice) {
		MessageBox(hWnd, "デバイスの作成に失敗しました", "error", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	// フォントセットアップ
	hFont = CreateFont(10, 0, 0, 0, FW_DONTCARE, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS,
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal");
	D3DXCreateFont(g_pD3DDevice, hFont, &g_pD3DXFont);
	DeleteObject(hFont);				// フォントを削除

	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&matProj, 60.0f * PI/180.0f, (float)SCREEN_WIDTH/SCREEN_HEIGHT, 100.0f, 10000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);	// プロジェクションマトリックスをセット

	// マテリアルの設定
	D3DMATERIAL8 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL8));
	mtrl.Diffuse.r  = 1.0f;	mtrl.Diffuse.g  = 1.0f;	mtrl.Diffuse.b  = 1.0f;
	mtrl.Ambient.r  = 0.2f;	mtrl.Ambient.g  = 0.2f;	mtrl.Ambient.b  = 0.2f;
	g_pD3DDevice->SetMaterial(&mtrl);

	// ライトの設定
	ZeroMemory(&g_Light[0], sizeof(D3DLIGHT8));			// [0] 白色光
	g_Light[0].Type       = D3DLIGHT_DIRECTIONAL;		// 平行光源
	g_Light[0].Diffuse.r  = 1.0f;	g_Light[0].Diffuse.g  = 1.0f;	g_Light[0].Diffuse.b  = 1.0f;
	g_Light[0].Ambient.r  = 0.4f;	g_Light[0].Ambient.g  = 0.4f;	g_Light[0].Ambient.b  = 0.4f;
	ZeroMemory(&g_Light[1], sizeof(D3DLIGHT8));			// [1] 黒色光（？）
	g_Light[1].Type       = D3DLIGHT_DIRECTIONAL;		// 平行光源
	g_Light[1].Diffuse.r  = 0.0f;	g_Light[1].Diffuse.g  = 0.0f;	g_Light[1].Diffuse.b  = 0.0f;
	g_Light[1].Ambient.r  = 0.0f;	g_Light[1].Ambient.g  = 0.0f;	g_Light[1].Ambient.b  = 0.0f;

	return S_OK;
}

//-------------------------------------------------------------------------------------------------
// ３Ｄ環境のクリーンアップ
//-------------------------------------------------------------------------------------------------
HRESULT Cleanup3DEnvironment(HWND hWnd)
{
	int			nModel;
	MODELINFO	*pt;

	SAFE_RELEASE(g_pD3DXFont);					// D3DXFont解放
	for(nModel = 0; nModel < MODEL_QTY; nModel++) {
		pt = &g_ModelInfo[nModel];
		SAFE_RELEASE(pt->lpD3DVertexBuffer);	// 頂点バッファ解放
		SAFE_RELEASE(pt->lpD3DIndexBuffer);		// インデックスバッファ解放
		SAFE_RELEASE(pt->lpD3DXMesh);			// メッシュ解放
		SAFE_RELEASE(pt->lpD3DTexture);			// テクスチャ解放
	}
	SAFE_RELEASE(g_pD3DDevice);					// Direct3DDevice オブジェクト解放
	SAFE_RELEASE(g_pD3D);						// Direct3D オブジェクト解放
	return S_OK;
}

//-------------------------------------------------------------------------------------------------
// ３Ｄ環境のレンダリング
//-------------------------------------------------------------------------------------------------
HRESULT Render3DEnvironment()
{
	D3DXMATRIX	matWorld;		// ワールドマトリックス
	float		xx, zz;
	char		str[256];
	static RECT	strRect = {0, 0, 640, 480};
	
	g_DebugStr[0] = NULL;		// デバッグストリングバッファ初期化
	// キーによる視点位置の移動
	if(GetAsyncKeyState(VK_UP     ) & 0x8000) g_fHeight   += 20.00f;	// カーソル（上）
	if(GetAsyncKeyState(VK_DOWN   ) & 0x8000) g_fHeight   -= 20.00f;	// カーソル（下）
	if(GetAsyncKeyState(VK_LEFT   ) & 0x8000) g_fRotation += 0.05f;		// カーソル（左）
	if(GetAsyncKeyState(VK_RIGHT  ) & 0x8000) g_fRotation -= 0.05f;		// カーソル（右）
	D3DXVECTOR3	vecDir = -1.0f * g_PointLight.position;
	D3DXVec3Normalize((D3DXVECTOR3*)&g_Light[0].Direction, &vecDir);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_Light[1].Direction, &vecDir);

	// バックバッファとＺバッファをクリア
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x90, 0xc0), 1.0f, 0);

	// ビューマトリックス設定
	xx = (float)cos(g_fRotation) * 1400.0f;
	zz = (float)sin(g_fRotation) * 1400.0f;
	D3DXMatrixLookAtLH(&g_MatView, &D3DXVECTOR3(xx, g_fHeight, zz), &D3DXVECTOR3(0, 500.0f, 0), &D3DXVECTOR3(0, 1, 0));
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_MatView);

	if(SUCCEEDED(g_pD3DDevice->BeginScene())) {		// シーン開始
		DrawLand();						// 地面描画
		DrawDonuts();					// ドーナツ描画
//		DrawGuideLine();				// ガイドライン描画
//		DrawPointLight();				// 点光源描画

		// デバッグストリング描画
		sprintf(str, "FPS : %4.1f\n", g_FPS);			strcat(g_DebugStr, str);
		g_pD3DXFont->DrawText(g_DebugStr, -1, &strRect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		g_pD3DDevice->EndScene();		// 描画終了
	}

	// バックバッファをプライマリバッファにコピー
	if(FAILED(g_pD3DDevice->Present(NULL,NULL,NULL,NULL))) g_pD3DDevice->Reset(&g_D3DPresentParam);

	return S_OK;
}

//-------------------------------------------------------------------------------------------------
// モデルデータセットアップ
//-------------------------------------------------------------------------------------------------
int SetModelData(HWND hWnd)
{
	DWORD			dwNumMaterials = 0L;
    LPD3DXBUFFER	pD3DXMtrlBuffer;
	MODELINFO		*pt;
	int				nModel;

	pt = &g_ModelInfo[0];
	for(nModel = 0; nModel < MODEL_QTY; nModel++, pt++) {
		// Ｘファイルからメッシュデータを読み込む
		D3DXLoadMeshFromX(modelfile[nModel], D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL,
							&pD3DXMtrlBuffer, &dwNumMaterials, &pt->lpD3DXMesh);
		pt->iNumVertex = pt->lpD3DXMesh->GetNumVertices();			// 頂点数をゲット
		pt->lpD3DXMesh->GetVertexBuffer(&pt->lpD3DVertexBuffer);	// 頂点バッファオブジェクトへのポインタをゲット
		pt->iNumIndex = pt->lpD3DXMesh->GetNumFaces();				// 面数をゲット
		pt->lpD3DXMesh->GetIndexBuffer(&pt->lpD3DIndexBuffer);		// インデックスバッファオブジェクトへのポインタをゲット

		// テクスチャ読み込み
		D3DXCreateTextureFromFileEx(g_pD3DDevice, texturefile[nModel], 0, 0, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
			0xff000000, NULL, NULL, &pt->lpD3DTexture);				// カラーキーを有効にしている
	}
	return 0;
}

//-----------------------------------------------------------------------------
// 地面オブジェクト
//-----------------------------------------------------------------------------
void ExecLand()
{
	LAND* gpt = &g_Land;
	switch(gpt->status) {
	case 0:		// 初期化
		// ワールドマトリクスを初期化
		D3DXMatrixIdentity(&gpt->matrix);		// 単位行列を生成
		gpt->status = 1;
	case 1:		// メイン
		break;
	default:
		break;
	}
}

//----- 地面描画
void DrawLand()
{
	MODELINFO* mpt = &g_ModelInfo[MN_LAND];
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_Land.matrix);					// ワールドマトリクス設定
	g_pD3DDevice->SetVertexShader(FVF_VERTEX);									// 頂点フォーマット設定
	g_pD3DDevice->SetTexture(0, mpt->lpD3DTexture);								// テクスチャ設定
	g_pD3DDevice->SetStreamSource(0, mpt->lpD3DVertexBuffer, sizeof(VERTEX));	// 頂点バッファ設定
	g_pD3DDevice->SetIndices(mpt->lpD3DIndexBuffer, 0);							// インデックスバッファ設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);				// αブレンディング設定
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);							// Ｚバッファ有効化
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);							// ライト有効化
	g_pD3DDevice->SetLight(0, &g_Light[0]);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, mpt->iNumVertex, 0, mpt->iNumIndex);		// 描画
}

//-----------------------------------------------------------------------------
// ドーナツオブジェクト
//-----------------------------------------------------------------------------
void ExecDonuts()
{
	DONUTS*		gpt;
	D3DXMATRIX	rot_x, rot_y, rot_z, trans, shadow;
	D3DXVECTOR3	light;

	for(int i = 0; i < DONUTS_QTY; i++) {
		gpt = &g_Donuts[i];
		switch(gpt->status) {
		case 0:		// 初期化
			gpt->position.x = (float)(((rand() % 40) - 20) * 100);			// 座標
			gpt->position.y = (float)(((rand() % 20) - 10) *  30) + 500.0f;
			gpt->position.z = (float)(((rand() % 40) - 20) * 100);
			gpt->rotation.x = gpt->rotation.y = gpt->rotation.z = 0.0f;
			gpt->rot_speed.x = (float)((rand() % 100) - 50) / 1000.0f;		// 回転速度
			gpt->rot_speed.y = (float)((rand() % 100) - 50) / 1000.0f;
			gpt->rot_speed.z = (float)((rand() % 100) - 50) / 1000.0f;
			gpt->status = 1;
		case 1:		// メイン
			// 回転させる
			gpt->rotation += gpt->rot_speed;
			// ワールドマトリクスを設定
			D3DXMatrixRotationX(&rot_x, gpt->rotation.x);
			D3DXMatrixRotationY(&rot_y, gpt->rotation.y);
			D3DXMatrixRotationZ(&rot_z, gpt->rotation.z);
			D3DXMatrixTranslation(&trans, gpt->position.x, gpt->position.y, gpt->position.z);
			gpt->matrix = rot_x * rot_y * rot_z * trans;		// マトリックスを合成
			//===== シャドウマトリックス =====
			// 光源から物体へのベクトルを求める
			light = g_PointLight.position - g_Donuts[i].position;
			// ドーナツからシャドウマトリックスを生成
			shadow._11 = 1.0f;	shadow._12 = 0.0f;	shadow._13 = 0.0f;	shadow._14 = 0.0f;
			shadow._21 = -(light.x/light.y);
			shadow._22 = 0.0f;
			shadow._23 = -(light.z/light.y);
			shadow._24 = 0.0f;
			shadow._31 = 0.0f;	shadow._32 = 0.0f;	shadow._33 = 1.0f;	shadow._34 = 0.0f;
			shadow._41 = 0.0f;	shadow._42 = 0.0f;	shadow._43 = 0.0f;	shadow._44 = 1.0f;
			gpt->shadow_matrix = g_Donuts[i].matrix * shadow;		// ワールドにシャドウをかける
			break;
		default:
			break;
		}
	}
}

//----- ドーナツ描画
void DrawDonuts()
{
	DONUTS*		gpt;
	MODELINFO* mpt = &g_ModelInfo[MN_DONUTS];
	g_pD3DDevice->SetVertexShader(FVF_VERTEX);									// 頂点フォーマット設定
	g_pD3DDevice->SetStreamSource(0, mpt->lpD3DVertexBuffer, sizeof(VERTEX));	// 頂点バッファ設定
	g_pD3DDevice->SetIndices(mpt->lpD3DIndexBuffer, 0);							// インデックスバッファ設定
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);							// Ｚバッファ有効化
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);				// αブレンディング設定
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);							// ライト有効化
	g_pD3DDevice->LightEnable(0, true);

	g_pD3DDevice->SetTexture(0, mpt->lpD3DTexture);								// テクスチャ設定
	g_pD3DDevice->SetLight(0, &g_Light[0]);
	for(int i = 0; i < DONUTS_QTY; i++) {
		gpt = &g_Donuts[i];
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &gpt->matrix);						// ワールドマトリクス設定
		g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
										0, mpt->iNumVertex, 0, mpt->iNumIndex);		// 描画
	}

	g_pD3DDevice->SetTexture(0, NULL);											// テクスチャ設定
	g_pD3DDevice->SetLight(0, &g_Light[1]);
	for(i = 0; i < DONUTS_QTY; i++) {
		gpt = &g_Donuts[i];
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &gpt->shadow_matrix);				// シャドウマトリクス設定
		g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
										0, mpt->iNumVertex, 0, mpt->iNumIndex);		// 描画
	}
}

//-----------------------------------------------------------------------------
// ガイドライン描画
//-----------------------------------------------------------------------------
void DrawGuideLine()
{

	D3DXMATRIX mtrx;
	D3DXMatrixIdentity(&mtrx);											// 単位行列を生成
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtrx);						// ワールドマトリクス設定
	g_pD3DDevice->SetVertexShader(FVF_TLVERTEX);						// 頂点フォーマット設定
	g_pD3DDevice->SetTexture(0, NULL);									// テクスチャ設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);		// αブレンディング設定
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	for(int i = 0; i < DONUTS_QTY; i++) {
		// ライン端点の頂点を設定
		g_GuideLine[0].x       = g_PointLight.position.x;
		g_GuideLine[0].y       = g_PointLight.position.y;
		g_GuideLine[0].z       = g_PointLight.position.z;
		g_GuideLine[0].diffuse = D3DCOLOR_XRGB(0,255,0);
		g_GuideLine[1].x       = g_Donuts[i].position.x + (g_PointLight.position.x - g_Donuts[i].position.x) * -500.0f;
		g_GuideLine[1].y       = g_Donuts[i].position.y + (g_PointLight.position.y - g_Donuts[i].position.y) * -500.0f;
		g_GuideLine[1].z       = g_Donuts[i].position.z + (g_PointLight.position.z - g_Donuts[i].position.z) * -500.0f;
		g_GuideLine[1].diffuse = D3DCOLOR_XRGB(0,255,0);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &g_GuideLine[0], sizeof(TLVERTEX));		// 描画
	}

}

//-----------------------------------------------------------------------------
// 点光源オブジェクト
//-----------------------------------------------------------------------------
//----- メイン
void ExecPointLight()
{
	POINTLIGHT*		pt;
	int				i;
	float			x;
	unsigned char	col_r, col_g, col_b;

	pt = &g_PointLight;
	switch(pt->status) {
	case 0:			// 初期化
		// 頂点データを設定
		pt->base_cycle.x = (float)rand() / 10;			// 基準座標の回転値
		pt->base_cycle.y = (float)rand() / 10;			// 基準座標の回転値
		pt->base_cycle.z = (float)rand() / 10;			// 基準座標の回転値
		pt->base_speed.x = (float)rand() / 4000000;		// 基準座標の回転速度値
		pt->base_speed.y = (float)rand() / 4000000;		// 基準座標の回転速度値
		pt->base_speed.z = (float)rand() / 4000000;		// 基準座標の回転速度値
		pt->vertex[0].x = 0;		// 最初の頂点（＝中心）の座標
		pt->vertex[0].y = 0;
		pt->vertex[0].z = 0;
		pt->vertex[0].diffuse = D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff);	// 中心は「白・不透明」
		col_r = rand() & 0xff;		// 光源全体をカラーを指定
		col_g = rand() & 0xff;
		col_b = rand() & 0xff;
		for(i = 0; i <= LIGHT_DETAIL; i++) {
			pt->vertex[i + 1].z       = pt->vertex[0].z;
			pt->vertex[i + 1].diffuse = D3DCOLOR_RGBA(col_r, col_g, col_b, 0x00);
			pt->cycle[i + 1] = (float)rand() / 1000;
			pt->speed[i + 1] = (float)rand() / 1000000;
			pt->range1       = (float)(150 + (rand() % 100));
			pt->range2       = (float)( 50 + (rand() %  50));
		}
		pt->cycle[i] = pt->cycle[1];	// 最後の頂点は最初の頂点と同じ
		pt->speed[i] = pt->speed[1];
		pt->status = 1;
	case 1:			// メイン
		for(i = 0; i <= LIGHT_DETAIL; i++) {
			x = (float)cos(pt->cycle[i + 1]);
			pt->vertex[i + 1].x = pt->vertex[0].x
								+ (float)sin((i * 360 / LIGHT_DETAIL) * RAD) * (pt->range1 + x * pt->range2);
			pt->vertex[i + 1].y = pt->vertex[0].y
								+ (float)cos((i * 360 / LIGHT_DETAIL) * RAD) * (pt->range1 + x * pt->range2);
			pt->cycle[i + 1] += pt->speed[i + 1];
		}
		pt->position.x = (float)sin(pt->base_cycle[0]) * 1500.0f;
		pt->position.y = (float)sin(pt->base_cycle[1]) * 200.0f + 1500.0f;
		pt->position.z = (float)sin(pt->base_cycle[2]) * 1500.0f;
		pt->base_cycle += pt->base_speed;		// 基準座標を移動（回転）させる
		break;
	default:
		break;
	}
}

//----- 描画
void DrawPointLight()
{
	D3DXMATRIX	matWorld;										// ワールドマトリックス
	g_pD3DDevice->SetVertexShader(FVF_TLVERTEX);				// 頂点フォーマット設定
	g_pD3DDevice->SetTexture(0, NULL);							// テクスチャ設定
	// ビルボード用に回転部分はビューマトリックスの逆行列を設定（転置行列でＯＫ）
	matWorld._11 = g_MatView._11;		matWorld._12 = g_MatView._21;		matWorld._13 = g_MatView._31;
	matWorld._21 = g_MatView._12;		matWorld._22 = g_MatView._22;		matWorld._23 = g_MatView._32;
	matWorld._31 = g_MatView._13;		matWorld._32 = g_MatView._23;		matWorld._33 = g_MatView._33;
	matWorld._14 = matWorld._24 = matWorld._34 = 0.0f;
	matWorld._41 = g_PointLight.position.x;
	matWorld._42 = g_PointLight.position.y;
	matWorld._43 = g_PointLight.position.z;
	matWorld._44 = 1.0f;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);						// ワールドマトリックスをセット
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);				// αブレンディング設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// 描画
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, LIGHT_DETAIL, &g_PointLight.vertex[0], sizeof(TLVERTEX));
}


//=================================================================================================
//	end of file
//=================================================================================================
