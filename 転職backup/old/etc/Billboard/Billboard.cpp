//=================================================================================================
//    [ Billboard ] DirectX Graphics 3D sample
//    ビルボードサンプル
//
//    操作
//    　「Ｂ」　　ビルボードＯＮ・ＯＦＦ
//    　「Ｗ」　　ウエイトＯＮ・ＯＦＦ
//    　カーソル　視点移動
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
#define CLASS_NAME		"Billboard"									// ウィンドウクラス名
#define CAPTION_NAME	"[ Billboard ] DirectX Sample Program"		// キャプション名

const int	MODEL_QTY		= 2;									// モデル数
const float FRAME_RATE		= 1000/60;								// フレームレート
const int	SCREEN_WIDTH	= 640;									// スクリーンの幅
const int	SCREEN_HEIGHT	= 480;									// スクリーンの高さ
const float	PI				= (float)3.141592653589;				// 円周率
const float	RAD				= PI/180;								// ラジアン

//----- 頂点フォーマット定義
struct VERTEX {
	float		x, y, z;			// 頂点座標（座標変換あり）
	float		nx, ny, nz;			// 法線ベクトル
	float		tu, tv;				// テクスチャ座標
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

typedef struct {
	LPD3DXMESH				lpD3DXMesh;				// メッシュインターフェイス
	LPDIRECT3DVERTEXBUFFER8	lpD3DVertexBuffer;		// Direct3DVertexBuffer8 オブジェクト
	LPDIRECT3DINDEXBUFFER8	lpD3DIndexBuffer;		// Direct3DIndexBuffer8 オブジェクト
	int						iNumVertex;				// 頂点数
	int						iNumIndex;				// インデックス数
	LPDIRECT3DTEXTURE8		lpD3DTexture;			// Direct3DTexture8 オブジェクト
	float					x, y, z;				// 座標
} MESHOBJ;

//----- グローバル変数

// DirectX 関連
LPDIRECT3D8				g_pD3D;						// Direct3D8 オブジェクト
LPDIRECT3DDEVICE8		g_pD3DDevice;				// Direct3DDevice8 オブジェクト
D3DPRESENT_PARAMETERS	g_D3DPresentParam;			// プレゼンテーションパラメータ
LPD3DXFONT				g_pD3DXFont;				// D3DXFont オブジェクト

MESHOBJ					g_Object[MODEL_QTY];		// 表示オブジェクト
char					g_DebugStr[4096];			// 出力文字列バッファ
float					g_FPS;						// フレーム数カウント用
float					g_fRotation;				// ビュー回転角
float					g_fRange;					// ビュー回転半径
bool					g_bNoWait;					// ウェイトスイッチ
bool					g_bBBoard;					// ビルボードスイッチ

//----- プロトタイプ宣言
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
long Initialize3DEnvironment(HWND hWnd, bool bWindow);
HRESULT Cleanup3DEnvironment(HWND hWnd);
HRESULT Render3DEnvironment();
int SetModelData(HWND hWnd);

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
	g_bNoWait   = false;
	g_bBBoard   = false;
	g_fRotation = (float)RAD*(-90);
	g_fRange    = 600.0f;

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
		case 'W':		g_bNoWait = (g_bNoWait)? false: true;	break;
		case 'B':		g_bBBoard = (g_bBBoard)? false: true;	break;
		case VK_ESCAPE:	DestroyWindow(hWnd);					break;
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
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE         , true);				// Ｚバッファ有効化
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING        , false);			// ライト無効化
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);				// αブレンディングを使ってカラーキーを処理
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND        , D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND       , D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE , true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF        , 0x80);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC       , D3DCMP_GREATEREQUAL);

	return S_OK;
}

//-------------------------------------------------------------------------------------------------
// ３Ｄ環境のクリーンアップ
//-------------------------------------------------------------------------------------------------
HRESULT Cleanup3DEnvironment(HWND hWnd)
{
	int		nModel;
	MESHOBJ	*pt;

	SAFE_RELEASE(g_pD3DXFont);					// D3DXFont解放
	for(nModel = 0; nModel < MODEL_QTY; nModel++) {
		pt = &g_Object[nModel];
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
	D3DXMATRIX	matView;		// ビューマトリックス
	MESHOBJ		*pt;
	int			nModel;
	float		xx, zz;
	char		str[256];
	static RECT	strRect = {0, 0, 640, 480};
	
	g_DebugStr[0] = NULL;		// デバッグストリングバッファ初期化
	// キーによる視点位置および球の移動
	if(GetAsyncKeyState(VK_UP     ) & 0x8000) g_fRange -= 4.00f;		// カーソル（上）
	if(GetAsyncKeyState(VK_DOWN   ) & 0x8000) g_fRange += 4.00f;		// カーソル（下）
	if(GetAsyncKeyState(VK_LEFT   ) & 0x8000) g_fRotation += 0.01f;		// カーソル（左）
	if(GetAsyncKeyState(VK_RIGHT  ) & 0x8000) g_fRotation -= 0.01f;		// カーソル（右）

	// バックバッファとＺバッファをクリア
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x60, 0x80), 1.0f, 0);

	// ビューマトリックス設定
	xx = (float)cos(g_fRotation) * g_fRange;
	zz = (float)sin(g_fRotation) * g_fRange;
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(xx, 300, zz), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);	// ビューマトリックスをセット

	if(SUCCEEDED(g_pD3DDevice->BeginScene())) {		// シーン開始

		pt = &g_Object[0];
		for(nModel = 0; nModel < MODEL_QTY; nModel++, pt++) {
			// 単位行列を設定
			D3DXMatrixIdentity(&matWorld);
			// 球を描画するときに通常の方法かビルボードかでワールドマトリックスを変える
			if(nModel == 1 && g_bBBoard == true) {
				// ビルボード用に回転部分はビューマトリックスの逆行列を設定（転置行列でＯＫ）
				matWorld._11 = matView._11;		matWorld._12 = matView._21;		matWorld._13 = matView._31;
				matWorld._21 = matView._12;		matWorld._22 = matView._22;		matWorld._23 = matView._32;
				matWorld._31 = matView._13;		matWorld._32 = matView._23;		matWorld._33 = matView._33;
			}
			// 描画
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);							// ワールドマトリックスをセット
			g_pD3DDevice->SetVertexShader(FVF_VERTEX);									// 頂点フォーマット設定
			g_pD3DDevice->SetTexture(0,pt->lpD3DTexture);								// テクスチャ設定
			g_pD3DDevice->SetStreamSource(0, pt->lpD3DVertexBuffer, sizeof(VERTEX));	// 使用する頂点バッファの設定
			g_pD3DDevice->SetIndices(pt->lpD3DIndexBuffer, 0);							// 使用するインデックスバッファの設定
			g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,	0, pt->iNumVertex, 0,	pt->iNumIndex);
		}

		// デバッグストリング描画
		sprintf(str, "FPS : %4.1f\n", g_FPS);			strcat(g_DebugStr, str);
		sprintf(str, "[B] : BillBoard ON/OFF\n\n");		strcat(g_DebugStr, str);
		if(g_bBBoard) {
			sprintf(str, "Billboard ON !!\n");			strcat(g_DebugStr, str);
		}
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
	static char		*modelfile[]   = {"sozai/land.x"  , "sozai/ball.x"  , };		// Ｘファイル
	static char		*texturefile[] = {"sozai/land.bmp", "sozai/ball.bmp", };		// テクスチャファイル
	DWORD			dwNumMaterials = 0L;
    LPD3DXBUFFER	pD3DXMtrlBuffer;
	MESHOBJ			*pt;
	int				nModel;

	pt = &g_Object[0];
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
		pt->x = pt->y = pt->z = 0.0f;
	}
	return 0;
}

//=================================================================================================
//	end of file
//=================================================================================================
