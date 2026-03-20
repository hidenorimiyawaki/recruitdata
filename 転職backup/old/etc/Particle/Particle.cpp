//=================================================================================================
//    [ Particle ] DirectX Graphics 3D sample
//    パーティクルサンプル
//
//    操作
//    　「Ｐ」			ポーズＯＮ・ＯＦＦ
//    　「Ｓ」			ワイヤーフレームＯＮ・ＯＦＦ
//    　「Ｗ」			ウエイトＯＮ・ＯＦＦ
//    　カーソル		視点移動
//    　HOME/END		パーティクル増減
//    　PageUp/PageDown	噴火レベル増減
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

//-------- 定数定義
#define CLASS_NAME		"Particle"									// ウィンドウクラス名
#define CAPTION_NAME	"[ Particle ] DirectX Sample Program"		// キャプション名

const int	PARTICLE_MAX		= 1000;									// パーティクル最大数
const int	PARTICLE_INIT		= 100;									// パーティクル初期数
const int	BURSTLEVEL_INIT		= 70;									// 噴火レベル初期値
const int	PARTICLE_AFTERIMAGE	= 16;									// パーティクル残像数
const float FRAME_RATE			= 1000/60;								// フレームレート
const int	SCREEN_WIDTH		= 640;									// スクリーンの幅
const int	SCREEN_HEIGHT		= 480;									// スクリーンの高さ
const float	PI					= (float)3.141592653589;				// 円周率
const float	RAD					= PI/180;								// ラジアン

//----- 頂点フォーマット定義
struct VERTEX {
	float		x, y, z;			// 頂点座標（座標変換あり）
	float		nx, ny, nz;			// 法線ベクトル
	float		tu, tv;				// テクスチャ座標
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct VERTEX2 {
	float		x, y, z;			// 頂点
	D3DCOLOR	diffuse;			// ディフューズ
	float		tu, tv;				// テクスチャ座標
};
#define	FVF_VERTEX2 (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//----- モデル、テクスチャ用ファイル名データ
char	*modelfile[]   = {"sozai/land.x"};									// Ｘファイル
enum _MODEL {
	MD_LAND = 0,
	MODEL_QTY,
};

char	*texturefile[] = {"sozai/land.bmp", "sozai/firework.bmp", };		// テクスチャファイル
enum _TEXTURE {
	TX_LAND = 0,
	TX_PARTICLE,
	TEXTURE_QTY,
};

//----- メッシュ
typedef struct {
	LPD3DXMESH				lpD3DXMesh;				// メッシュインターフェイス
	LPDIRECT3DVERTEXBUFFER8	lpD3DVertexBuffer;		// Direct3DVertexBuffer8 オブジェクト
	LPDIRECT3DINDEXBUFFER8	lpD3DIndexBuffer;		// Direct3DIndexBuffer8 オブジェクト
	int						iNumVertex;				// 頂点数
	int						iNumIndex;				// インデックス数
} MESHOBJ;

//----- 地面
typedef struct {
	int			status;		// ステータス
	float		x, y, z;	// 座標
	D3DXMATRIX	matrix;		// ローカルワールド変換行列
} LAND;

//----- パーティクル
typedef struct {
	int			status;						// ステータス
	D3DXVECTOR3	pos[PARTICLE_AFTERIMAGE];	// 座標
	D3DXVECTOR3	delta;						// 移動量
} PARTICLE;

//----- グローバル変数

// DirectX 関連
LPDIRECT3D8				g_pD3D;						// Direct3D8 オブジェクト
LPDIRECT3DDEVICE8		g_pD3DDevice;				// Direct3DDevice8 オブジェクト
D3DPRESENT_PARAMETERS	g_D3DPresentParam;			// プレゼンテーションパラメータ
LPD3DXFONT				g_pD3DXFont;				// D3DXFont オブジェクト
LPDIRECT3DTEXTURE8		g_pD3DTexture[2];			// Direct3DTexture8 オブジェクト
D3DXMATRIX				g_ViewMatrix;				// ビューマトリックス

LAND					g_Land;						// 地面表示オブジェクト
PARTICLE				g_Particle[PARTICLE_MAX];	// パーティクル表示オブジェクト
MESHOBJ					g_Mesh[MODEL_QTY];			// メッシュオブジェクト
char					g_DebugStr[4096];			// 出力文字列バッファ
float					g_FPS;						// フレーム数カウント用
bool					g_bPause;					// ポーズスイッチ
bool					g_bNoWait;					// ウェイトスイッチ
bool					g_bOnWireFrame;				// ワイヤーフレーム描画フラグ
float					g_fRotation;				// ビュー回転角
float					g_fHeight;					// ビュー回転半径
int						g_iBurstLevel;				// 噴火度合い
int						g_iParticleQty;				// パーティクル数

//----- プロトタイプ宣言
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
long Initialize3DEnvironment(HWND hWnd, bool bWindow);
HRESULT Cleanup3DEnvironment(HWND hWnd);
HRESULT Render3DEnvironment();
int SetModelData(HWND hWnd);
void InitLand();
void ExecLand();
void DrawLand();
void InitParticle();
void ExecParticle();
void DrawParticle();

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

	SetModelData(hWnd);		// モデルデータの準備
	InitLand();				// 地面初期化
	InitParticle();			// パーティクル初期化

	// 変数初期化
	timeBeginPeriod(1);									// システムタイマーの分解能を１ｍｓに設定
	dwFPSLastTime = dwExecLastTime = timeGetTime();		// 現在のシステムタイマーを取得
	dwFrameCount = 0;
	g_bPause       = false;
	g_bNoWait      = false;
	g_bOnWireFrame = false;
	g_fRotation    = (float)RAD*(-90);
	g_fHeight      = 300.0f;
	g_iBurstLevel  = BURSTLEVEL_INIT;
	g_iParticleQty = PARTICLE_INIT;

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
			if(g_bNoWait || dwCurrentTime - dwExecLastTime >= FRAME_RATE) {	// 一定時間が経過したら・・・
				dwExecLastTime = dwCurrentTime;								// タイマー値を更新
				ExecLand();													// 地面処理
				ExecParticle();												// パーティクル処理
				Render3DEnvironment();										// 描画処理
				dwFrameCount++;												// フレームカウントを＋１
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
		case 'P':	g_bPause       = (g_bPause       )? false: true;	break;	// ポーズ切り替え
		case 'S':	g_bOnWireFrame = (g_bOnWireFrame )? false: true;	break;	// ワイヤーフレーム切り替え
		case 'W':	g_bNoWait      = (g_bNoWait      )? false: true;	break;	// ウェイト切り替え
		case VK_ESCAPE:	DestroyWindow(hWnd);				break;
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

	// レンダリングステートを設定
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE         , false);			// Ｚバッファ有効化
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING        , false);			// ライト無効化
	// テクスチャステージの設定 
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	return S_OK;
}

//-------------------------------------------------------------------------------------------------
// ３Ｄ環境のクリーンアップ
//-------------------------------------------------------------------------------------------------
HRESULT Cleanup3DEnvironment(HWND hWnd)
{
	int		nModel, nTex;
	MESHOBJ	*pt;

	SAFE_RELEASE(g_pD3DXFont);					// D3DXFont解放
	for(nTex = 0; nTex < TEXTURE_QTY; nTex++) {
		SAFE_RELEASE(g_pD3DTexture[nTex]);		// テクスチャ解放
	}
	for(nModel = 0; nModel < MODEL_QTY; nModel++) {
		pt = &g_Mesh[nModel];
		SAFE_RELEASE(pt->lpD3DVertexBuffer);	// 頂点バッファ解放
		SAFE_RELEASE(pt->lpD3DIndexBuffer);		// インデックスバッファ解放
		SAFE_RELEASE(pt->lpD3DXMesh);			// メッシュ解放
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
	D3DXMATRIX	matView;		// ビューマトリックス
	float		xx, zz;
	char		str[256];
	static RECT	strRect = {0, 0, 640, 480};
	
	g_DebugStr[0] = NULL;		// デバッグストリングバッファ初期化
	// フラグによるシェーディング設定
	if(g_bOnWireFrame)	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	// ワイヤーフレーム
	else				g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		// 面
	// キーによる視点位置の移動など
	if(GetAsyncKeyState(VK_UP   ) & 0x8000) g_fHeight += 10.00f;	// カーソル（上）
	if(GetAsyncKeyState(VK_DOWN ) & 0x8000) g_fHeight -= 10.00f;	// カーソル（下）
	if(GetAsyncKeyState(VK_LEFT ) & 0x8000) g_fRotation += 0.05f;	// カーソル（左）
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000) g_fRotation -= 0.05f;	// カーソル（右）
	if(GetAsyncKeyState(VK_PRIOR) & 0x8000) g_iBurstLevel += 1;		// Page Up
	if(GetAsyncKeyState(VK_NEXT ) & 0x8000) g_iBurstLevel -= 1;		// page Down
	if(GetAsyncKeyState(VK_HOME ) & 0x8000) g_iParticleQty += 10;	// カーソル（上）
	if(GetAsyncKeyState(VK_END  ) & 0x8000) g_iParticleQty -= 10;	// カーソル（下）
	if(g_iBurstLevel < 1  ) g_iBurstLevel = 1;
	if(g_iBurstLevel > 100) g_iBurstLevel = 100;
	if(g_iParticleQty < 1  ) g_iParticleQty = 1;
	if(g_iParticleQty > PARTICLE_MAX) g_iParticleQty = PARTICLE_MAX;

	// バックバッファとＺバッファをクリア
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x60, 0x80), 1.0f, 0);

	// ビューマトリックス設定
	xx = (float)cos(g_fRotation) * 600.0f;
	zz = (float)sin(g_fRotation) * 600.0f;
	D3DXMatrixLookAtLH(&g_ViewMatrix, &D3DXVECTOR3(xx, g_fHeight, zz), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_ViewMatrix);	// ビューマトリックスをセット

	if(SUCCEEDED(g_pD3DDevice->BeginScene())) {		// シーン開始

		DrawLand();						// 地面描画
		DrawParticle();					// パーティクル描画

		// デバッグストリング描画
		sprintf(str, "FrameCount = %5.1f\n", g_FPS);			strcat(g_DebugStr, str);
		sprintf(str, "Particle Qty. = %d\n", g_iParticleQty);	strcat(g_DebugStr, str);
		sprintf(str, "Burst Level = %d\n", g_iBurstLevel);		strcat(g_DebugStr, str);
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
	MESHOBJ			*pt;
	int				nModel, nTex;

	pt = &g_Mesh[0];
	for(nModel = 0; nModel < MODEL_QTY; nModel++, pt++) {
		// Ｘファイルからメッシュデータを読み込む
		D3DXLoadMeshFromX(modelfile[nModel], D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL,
							&pD3DXMtrlBuffer, &dwNumMaterials, &pt->lpD3DXMesh);
		pt->iNumVertex = pt->lpD3DXMesh->GetNumVertices();			// 頂点数
		pt->lpD3DXMesh->GetVertexBuffer(&pt->lpD3DVertexBuffer);	// 頂点バッファオブジェクトへのポインタ
		pt->iNumIndex = pt->lpD3DXMesh->GetNumFaces();				// 面数
		pt->lpD3DXMesh->GetIndexBuffer(&pt->lpD3DIndexBuffer);		// インデックスバッファオブジェクトへのポインタ
	}
	for(nTex = 0; nTex < TEXTURE_QTY; nTex++) {
		// テクスチャ読み込み
		D3DXCreateTextureFromFileEx(g_pD3DDevice, texturefile[nTex], 0, 0, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR,
			NULL, NULL, NULL, &g_pD3DTexture[nTex]);
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------
// 地面オブジェクト
//-------------------------------------------------------------------------------------------------
void InitLand()
{
	g_Land.status = 0;
}

void ExecLand()
{
	LAND*		gpt;

	gpt = &g_Land;
	switch(gpt->status) {
	case 0:		// 初期化
		gpt->x = gpt->y = gpt->z = 0;
		D3DXMatrixIdentity(&gpt->matrix);		// ワールドマトリクスを初期化（単位行列）
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
	MESHOBJ*	mpt;

	mpt = &g_Mesh[0];
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_Land.matrix);					// ワールドマトリクス設定
	g_pD3DDevice->SetVertexShader(FVF_VERTEX);									// 頂点フォーマット設定
	g_pD3DDevice->SetTexture(0, g_pD3DTexture[TX_LAND]);						// テクスチャ設定
	g_pD3DDevice->SetStreamSource(0, mpt->lpD3DVertexBuffer, sizeof(VERTEX));	// 頂点バッファ設定
	g_pD3DDevice->SetIndices(mpt->lpD3DIndexBuffer, 0);							// インデックスバッファ設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);				// αブレンディング設定
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, mpt->iNumVertex, 0, mpt->iNumIndex);		// 描画
}

//-------------------------------------------------------------------------------------------------
// パーティクルオブジェクト
//-------------------------------------------------------------------------------------------------
void InitParticle()
{
	int		i;
	for(i = 0; i < PARTICLE_MAX; i++) g_Particle[i].status = 0;
}

void ExecParticle()
{
	PARTICLE*	gpt;
	int			i, j;

	gpt = &g_Particle[0];
	for(i = 0; i < PARTICLE_MAX; i++, gpt++) {
		switch(gpt->status) {
		case 0:		// 初期化
			for(j = 0; j < PARTICLE_AFTERIMAGE; j++) {
				gpt->pos[j].x = gpt->pos[j].y = gpt->pos[j].z = 0.0f;
			}
			// 飛び出す方向を乱数で決める
			gpt->delta.x = (float)(rand() % g_iBurstLevel - g_iBurstLevel/2) / 10;
			gpt->delta.y = (float)(rand() % g_iBurstLevel                  ) / 10;
			gpt->delta.z = (float)(rand() % g_iBurstLevel - g_iBurstLevel/2) / 10;
			gpt->status = 1;
		case 1:		// メイン
			if(g_bPause == false) {
				gpt->delta.y -= 0.06f;			// 重力加速値
				// 残像部分に座標をスライド
				for(j = PARTICLE_AFTERIMAGE - 1 - 1; j >= 0; j--) {
					gpt->pos[j + 1] = gpt->pos[j];		// 一つ後ろの残像へ
				}
				gpt->pos[0] += gpt->delta;		// 位置を移動
			}
			// 最後の残像が地面に到達したら終了
			if(gpt->pos[PARTICLE_AFTERIMAGE-1].y < 0.0f) gpt->status = 0;
			break;
		default:
			break;
		}
	}
}

//----- パーティクル描画
void DrawParticle()
{
	VERTEX2		vertex[] = {			// 頂点データ
		// x y z diffuse tu tv
		{-4.0f, 4.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), 0.0f, 0.0f},
		{ 4.0f, 4.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), 1.0f, 0.0f},
		{ 4.0f,-4.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), 1.0f, 1.0f},
		{-4.0f,-4.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), 0.0f, 1.0f},
	};		
	PARTICLE*	gpt;		// PARTICLE 構造体へのポインタ
	D3DXMATRIX	mtx;		// マトリックス生成用
	int			i, j;

	gpt = &g_Particle[0];
	g_pD3DDevice->SetVertexShader(FVF_VERTEX2);							// 頂点フォーマット設定
	g_pD3DDevice->SetTexture(0, g_pD3DTexture[TX_PARTICLE]);			// テクスチャ設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);			// αブレンディング設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ビルボード用に回転部分はビューマトリックスの逆行列を設定（転置行列でＯＫ）
	mtx._11 = g_ViewMatrix._11;	mtx._12 = g_ViewMatrix._21;	mtx._13 = g_ViewMatrix._31;	mtx._14 = 0.0f;
	mtx._21 = g_ViewMatrix._12;	mtx._22 = g_ViewMatrix._22;	mtx._23 = g_ViewMatrix._32;	mtx._24 = 0.0f;
	mtx._31 = g_ViewMatrix._13;	mtx._32 = g_ViewMatrix._23;	mtx._33 = g_ViewMatrix._33;	mtx._34 = 0.0f;
	mtx._44 = 1.0f;
	for(i = 0; i < g_iParticleQty; i++, gpt++) {
		for(j = 0; j < PARTICLE_AFTERIMAGE; j++) {
			mtx._41 = gpt->pos[j].x;		// 平行移動成分を設定
			mtx._42 = gpt->pos[j].y;
			mtx._43 = gpt->pos[j].z;
			if(gpt->pos[j].y >= 0.0f) {		// 地面より上にあったら描画
				// 半透明を計算しつつカラーをセット
				vertex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (float)j / (float)PARTICLE_AFTERIMAGE);
				vertex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (float)j / (float)PARTICLE_AFTERIMAGE);
				vertex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (float)j / (float)PARTICLE_AFTERIMAGE);
				vertex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (float)j / (float)PARTICLE_AFTERIMAGE);
				// ワールドマトリクス設定
				g_pD3DDevice->SetTransform(D3DTS_WORLD, &mtx);
				// 描画
				g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &vertex[0], sizeof(VERTEX2));
			}
		}
	}
}

//=================================================================================================
//	end of file
//=================================================================================================
