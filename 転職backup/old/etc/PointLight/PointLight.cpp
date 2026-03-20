//=============================================================================
//    [ PointLight ] DirectX Graphics 3D Sample 点光源っぽい表現
//    　カーソル　視点移動
//    　スペース　光源　移動／一時停止　切り替え
//    　Ｓ　　　　シェーディング切り替え
//    　Ａ　　　　αブレンディング切り替え
//
//=============================================================================
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
//----- 定数
#define CLASS_NAME		"PointLight"								// ウィンドウクラス名
#define CAPTION_NAME	"[ PointLight ] DirectX Sample Program"		// キャプション名
const int	SCREEN_WIDTH	= 640;						// スクリーンの幅
const int	SCREEN_HEIGHT	= 480;						// スクリーンの高さ
const float FRAME_RATE		= 1000/60;					// フレームレート
const float NEAR_CLIP		= 100.0f;					// ニアクリップを行う距離
const float FAR_CLIP		= 30000.0f;					// ファークリップを行う距離
const float PI				= 3.1415926535897932f;		// 円周率
const float RAD				= PI/180.0f;				// ラジアン
const int	LIGHT_QTY		= 64;						// 点光源の最大数
const int	LIGHT_DETAIL	= 32;						// 点光源のディテールレベル

//----- 構造体
struct VERTEX {					//--- 頂点を定義する構造体
	float		x, y, z;							// 頂点
	D3DCOLOR	diffuse;							// 法線ベクトル
};
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct POINTLIGHT {				//--- 点光源を定義する構造体
	int			status;								// ステータス
	float		base_point[3];						// 中心座標
	float		base_cycle[3];						// 中心移動用回転値
	float		base_speed[3];						// 中心移動用回転速度値
	float		base_range[3];						// 中心移動用回転半径値
	VERTEX		vertex[LIGHT_DETAIL + 2];			// 頂点データ
	float		cycle[LIGHT_DETAIL + 2];			// 頂点変化サインカーブ角度値
 	float		speed[LIGHT_DETAIL + 2];			// 頂点変化サインカーブ角速度値
 	float		range1, range2;						// 頂点変化サインカーブ変化値
};

//----- グローバル変数
LPDIRECT3D8				g_pD3D;						// Direct3D8 オブジェクト
LPDIRECT3DDEVICE8		g_pD3DDevice;				// Direct3DDevice8 オブジェクト
D3DPRESENT_PARAMETERS	g_D3DPresentParam;			// PRESENT PARAMETERS
LPD3DXFONT				g_pD3DXFont;				// D3DXFont オブジェクト
POINTLIGHT				g_PointLight[LIGHT_QTY];	// 点光源オブジェクト
float					g_FPS;						// フレーム数カウント用
char					g_DebugStr[4096];			// 出力文字列バッファ
D3DXMATRIX				g_MatView;					// ビューマトリックス
float					g_fRotation;				// ビュー回転角
float					g_fRange;					// ビュー回転半径
bool					g_bOnMove;					// 光源移動フラグ
bool					g_bOnWireFrame;				// ワイヤーフレーム描画フラグ
bool					g_bOnAlphaBlend;			// αブレンディングフラグ

//----- プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
HRESULT Initialize3DEnvironment(HWND hWnd, bool bWindow);
HRESULT Cleanup3DEnvironment();
HRESULT Render3DEnvironment();
void ExecPointLight(int index);
void DrawPointLight(int index);

//-----------------------------------------------------------------------------
// メイン
//-----------------------------------------------------------------------------
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
	ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

	// ３Ｄ環境の初期化
	bWindow = false;
	if(IDYES == MessageBox(hWnd, "ウィンドウモードで実行しますか？", "画面モード", MB_YESNO))
		bWindow = true;
	if(FAILED(Initialize3DEnvironment(hWnd, bWindow))) return 0;	// ３Ｄ環境の初期化
	// 各種初期化
	timeBeginPeriod(1);									// システムタイマーの分解能を１ｍｓに設定
	dwFPSLastTime = dwExecLastTime = timeGetTime();		// 現在のシステムタイマーを取得
	dwFrameCount = 0;
	g_fRotation     = 0.0f;
	g_fRange        = 5000.0f;
	g_bOnMove       = true;
	g_bOnWireFrame  = false;
	g_bOnAlphaBlend = true;
	for(int i = 0; i < LIGHT_QTY; i++) g_PointLight[i].status = 0;	// オブジェクトステータスを初期化

	// メインループ
    msg.message = WM_NULL;
	while(WM_QUIT != msg.message) {										// WM_QUIT がくるまでループ
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {					// メッセージをチェック
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
			if(dwCurrentTime - dwExecLastTime >= FRAME_RATE) {			// 一定時間が経過したら・・・
				dwExecLastTime = dwCurrentTime;							// タイマー値を更新
				for(i = 0; i < LIGHT_QTY; i++) ExecPointLight(i);		// 点光源を処理
				Render3DEnvironment();									// レンダリング
				dwFrameCount++;											// フレームカウントを＋１
			}
		}
	}
	Cleanup3DEnvironment();		// ３Ｄ環境のクリーンアップ
	timeEndPeriod(1);			// システムタイマーの分解能を元に戻す
	return msg.wParam;
}

//-----------------------------------------------------------------------------
// メッセージハンドラ
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage) {
	case WM_DESTROY:
		ShowCursor(true);			// マウスカーソルを再表示
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch(wParam) {
		case VK_SPACE:	g_bOnMove       = (g_bOnMove      )? false: true;	break;
		case 'S':		g_bOnWireFrame  = (g_bOnWireFrame )? false: true;	break;
		case 'A':		g_bOnAlphaBlend = (g_bOnAlphaBlend)? false: true;	break;
		case VK_ESCAPE:	DestroyWindow(hWnd);	break;
		}
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

//-----------------------------------------------------------------------------
// ３Ｄ環境の初期化
//-----------------------------------------------------------------------------
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
	g_D3DPresentParam.EnableAutoDepthStencil = 1;				// Ｚバッファの自動作成
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
	D3DXMatrixPerspectiveFovLH(&matProj, 45.0f * RAD, (float)SCREEN_WIDTH/SCREEN_HEIGHT, NEAR_CLIP, FAR_CLIP);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	// レンダリングステートを設定
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00303030);				// 環境光の設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);				// αブレンディング有効
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);						// Ｚバッファ無効化
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);					// ライト無効化
	return S_OK;
}

//-----------------------------------------------------------------------------
// ３Ｄ環境のクリーンアップ
//-----------------------------------------------------------------------------
HRESULT Cleanup3DEnvironment()
{
	SAFE_RELEASE(g_pD3DXFont);			// D3DXFont解放
	SAFE_RELEASE(g_pD3DDevice);			// Direct3DDevice オブジェクト解放
	SAFE_RELEASE(g_pD3D);				// Direct3D オブジェクト解放
	return 0;
}

//-----------------------------------------------------------------------------
// ３Ｄ環境のレンダリング
//-----------------------------------------------------------------------------
HRESULT Render3DEnvironment()
{
	static RECT strRect = {0, 0, 640, 480};
	char		str[256];
	int			i;
	float		xx, zz;

	g_DebugStr[0] = NULL;	// デバッグストリングバッファ初期化
	// フラグによるシェーディング設定
	if(g_bOnWireFrame)	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	// ワイヤーフレーム
	else				g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		// 面
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bOnAlphaBlend);					// αブレンディング設定
	// キーによる視点位置の移動
	if(GetAsyncKeyState(VK_UP     ) & 0x8000) g_fRange -= 50.00f;		// カーソル（上）
	if(GetAsyncKeyState(VK_DOWN   ) & 0x8000) g_fRange += 50.00f;		// カーソル（下）
	if(GetAsyncKeyState(VK_LEFT   ) & 0x8000) g_fRotation += 0.03f;		// カーソル（左）
	if(GetAsyncKeyState(VK_RIGHT  ) & 0x8000) g_fRotation -= 0.03f;		// カーソル（右）
	// ビューマトリックス設定
	xx = (float)sin(g_fRotation) * g_fRange;
	zz = (float)cos(g_fRotation) * g_fRange;
	D3DXMatrixLookAtLH(&g_MatView, &D3DXVECTOR3(xx, 2000, zz), &D3DXVECTOR3(0, 1000, 0), &D3DXVECTOR3(0, 1, 0));
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_MatView);	// ビューマトリックスをセット
	// ビューポートをクリア
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00,0x00,0x80), 1.0f, 0);

	if(SUCCEEDED(g_pD3DDevice->BeginScene())) {		// シーン開始
		for(i = 0; i < LIGHT_QTY; i++) DrawPointLight(i);		// 点光源の描画
		// デバッグストリング描画
		sprintf(str, "FrameCount = %5.1f\n", g_FPS);		strcat(g_DebugStr, str);
		sprintf(str, "\n[ SPACE ] : Move Sw.\n");			strcat(g_DebugStr, str);
		sprintf(str, "\n[ S ]     : Wireframe Sw.\n");		strcat(g_DebugStr, str);
		sprintf(str, "\n[ A ]     : Alpha Blending Sw.\n");	strcat(g_DebugStr, str);
		g_pD3DXFont->DrawText(g_DebugStr, -1, &strRect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		g_pD3DDevice->EndScene();		// シーンを終了
	}
	// バックバッファをプライマリにコピー
	if(FAILED(g_pD3DDevice->Present(NULL, NULL, NULL, NULL))) g_pD3DDevice->Reset(&g_D3DPresentParam);
	return S_OK;
}

//-----------------------------------------------------------------------------
// 点光源エフェクトオブジェクト
//-----------------------------------------------------------------------------
//----- メイン
void ExecPointLight(int index)
{
	POINTLIGHT*		pt;
	int				i;
	float			x;
	unsigned char	col_r, col_g, col_b;

	pt = &g_PointLight[index];
	switch(pt->status) {
	case 0:			// 初期化
		// 頂点データを設定
		for(i = 0; i < 3; i++) {
			pt->base_cycle[i] = (float)rand() / 10;			// 基準座標の回転値
			pt->base_speed[i] = (float)rand() / 4000000;	// 基準座標の回転速度値
			pt->base_range[i] = (float)rand() / 10;			// 基準座標の回転半径値
		}
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
		for(i = 0; i < 3; i++) {
			pt->base_point[i] = (float)sin(pt->base_cycle[i]) * pt->base_range[i];
			if(g_bOnMove) pt->base_cycle[i] += pt->base_speed[i];		// 基準座標を移動（回転）させる
		}
		break;
	default:
		break;
	}
}

//----- 描画
void DrawPointLight(int index)
{
	D3DXMATRIX	matWorld;									// ワールドマトリックス
	g_pD3DDevice->SetVertexShader(FVF_VERTEX);				// 頂点フォーマット設定
	g_pD3DDevice->SetTexture(0, NULL);						// テクスチャ設定
	// ビルボード用に回転部分はビューマトリックスの逆行列を設定（転置行列でＯＫ）
	matWorld._11 = g_MatView._11;		matWorld._12 = g_MatView._21;		matWorld._13 = g_MatView._31;
	matWorld._21 = g_MatView._12;		matWorld._22 = g_MatView._22;		matWorld._23 = g_MatView._32;
	matWorld._31 = g_MatView._13;		matWorld._32 = g_MatView._23;		matWorld._33 = g_MatView._33;
	matWorld._14 = matWorld._24 = matWorld._34 = 0.0f;
	matWorld._41 = g_PointLight[index].base_point[0];
	matWorld._42 = g_PointLight[index].base_point[1];
	matWorld._43 = g_PointLight[index].base_point[2];
	matWorld._44 = 1.0f;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);						// ワールドマトリックスをセット
	// 描画
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, LIGHT_DETAIL, &g_PointLight[index].vertex[0], sizeof(VERTEX));
}

//=============================================================================
//	end of file
//=============================================================================
