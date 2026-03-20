// DirectX.cpp: CDirectX クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MothionEditor.h"
#include "DirectX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//----- ベース座標軸用頂点データ -----
LVERTEX baseaxis[] = {
	{-600.0f,    0.0f,   0.0f, 0xffff0000},	{ 600.0f,   0.0f,   0.0f, 0xffff0000},	// Ｘ軸
	{-600.0f,    0.0f,-600.0f, 0xffffffff},	{ 600.0f,   0.0f,-600.0f, 0xffffffff},	// Ｘ方向０
	{-600.0f,    0.0f, 600.0f, 0xffffffff},	{ 600.0f,   0.0f, 600.0f, 0xffffffff},	// Ｘ方向１
	{   0.0f,    0.0f,   0.0f, 0xff00ff00},	{   0.0f, 600.0f,   0.0f, 0xff00ff00},	// Ｙ軸
	{   0.0f,    0.0f,-600.0f, 0xff0000ff},	{   0.0f,   0.0f, 600.0f, 0xff0000ff},	// Ｚ軸
	{-600.0f,    0.0f,-600.0f, 0xffffffff},	{-600.0f,   0.0f, 600.0f, 0xffffffff},	// Ｚ方向０
	{ 600.0f,    0.0f,-600.0f, 0xffffffff},	{ 600.0f,   0.0f, 600.0f, 0xffffffff},	// Ｚ方向１
};

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDirectX::CDirectX()
{
	is_initialize = false;
}

CDirectX::~CDirectX()
{

}
HRESULT CDirectX::Initialize(HWND hwnd)
{
	HRESULT hRes;

	// Direct3D8 オブジェクトを取得
	D3D = Direct3DCreate8(D3D_SDK_VERSION);
	if(!D3D) {
		MessageBox(hwnd, "DirectX8 : Direct3DCreate8 に失敗しました", "error", MB_OK | MB_ICONSTOP);
		return E_FAIL;
	}
	// Direct3D 初期化パラメータの設定
	ZeroMemory(&D3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));
	// ウィンドウモードで設定
	D3DDISPLAYMODE disp;
	D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp);		// 現在の画面モードを取得
	D3DPresentParam.BackBufferFormat = disp.Format;
	D3DPresentParam.Windowed = true;
	D3DPresentParam.FullScreen_RefreshRateInHz = 0;
	D3DPresentParam.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	// 表示領域サイズの設定
	D3DPresentParam.BackBufferWidth  = SCREEN_WIDTH;
	D3DPresentParam.BackBufferHeight = SCREEN_HEIGHT;
	D3DPresentParam.SwapEffect = D3DSWAPEFFECT_COPY;
	// Ｚバッファの自動作成
	D3DPresentParam.EnableAutoDepthStencil = true;
	D3DPresentParam.AutoDepthStencilFormat = D3DFMT_D16;
	// ハードウェアＴ＆Ｌ対応レンダリングデバイスを作成
	hRes = D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
							D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DPresentParam, &D3DDevice);
	if(FAILED(hRes)) {
		// ハードウェアレンダリングデバイスを作成
		hRes = D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3DPresentParam, &D3DDevice);
		if(FAILED(hRes)) {
			// ＨＡＬが無理なのでＲＧＢで試す
			hRes = D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hwnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3DPresentParam, &D3DDevice);
			if(FAILED(hRes)) {
				MessageBox(hwnd, "DirectX8 : CreateDevice に失敗しました", "error", MB_OK | MB_ICONSTOP);
				return hRes;
			}
		}
	}

	// フォントセットアップ
	HFONT hFont = CreateFont(0, 0, 0, 0, FW_DONTCARE, 0, 0, 0, SHIFTJIS_CHARSET, OUT_CHARACTER_PRECIS,
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, NULL);
	D3DXCreateFont(D3DDevice, hFont, &D3DXFont);
	DeleteObject(hFont);

	// ビューマトリックス設定
	camera.SetViewMatrix();

	// プロジェクションマトリックス設定
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, 30.0f * PI / 180.0f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
								NEAR_CLIP, FAR_CLIP);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	// マテリアルの設定
	D3DMATERIAL8	mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL8));
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient.r = mtrl.Ambient.g = mtrl.Ambient.b = mtrl.Ambient.a = 1.0f;
	D3DDevice->SetMaterial(&mtrl);

	// ライトの設定
	D3DXVECTOR3		vecDir;
	D3DLIGHT8		light;
	ZeroMemory(&light, sizeof(D3DLIGHT8));
	light.Type = D3DLIGHT_DIRECTIONAL;		// 平行光源
	light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = light.Diffuse.a = 1.0f;
	vecDir = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);		// ３Ｄベクトルの正規化したベクトルを返す
	D3DDevice->SetLight(0, &light);
	D3DDevice->LightEnable(0, true);
	
	// レンダリングステートを設定
	D3DDevice->SetRenderState(D3DRS_ZENABLE, true);					// Ｚバッファ有効化
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);				// ライト有効化
	D3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00404040);			// 環境光の設定

	is_initialize = true;		// 初期化完了
	return hRes;


}

HRESULT CDirectX::Render()
{
	// アプリケーションオブジェクトのポインタを取得
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	debug_str[0] = NULL;	// デバッグストリングバッファ初期化
	
	// ビューポートをクリア
	D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00,0x00,0x80), 1.0f, 0);

	// シーンを開始
	D3DDevice->BeginScene();
	
	// 座標軸を描画
	D3DXMATRIX IdentityMatrix;
	D3DXMatrixIdentity(&IdentityMatrix);						// 単位行列を生成
	D3DDevice->SetTransform(D3DTS_WORLD, &IdentityMatrix);		// ワールドマトリクスをセット
	D3DDevice->SetVertexShader(FVF_LVERTEX);					// 頂点フォーマット設定
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);			// ライト無効化
	D3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 7, &baseaxis[0], sizeof(LVERTEX));	// 描画
	
	// オブジェクトを描画
	pApp->zintai.Draw();

	// デバッグストリング描画
	RECT strRect;
	char str[256];
	D3DXVECTOR3 cm_pos;
	cm_pos = pApp->direct_x.camera.GetPosition();
	sprintf(str, "カメラ：位置(%8.2f, %8.2f, %8.2f)\n", cm_pos.x, cm_pos.y, cm_pos.z);	strcat(debug_str, str);
	SetRect(&strRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	D3DXFont->DrawText(debug_str, -1, &strRect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// シーンを終了
	D3DDevice->EndScene();

	// バックバッファをプライマリにコピー
	if(FAILED(D3DDevice->Present(NULL, NULL, NULL, NULL))) D3DDevice->Reset(&D3DPresentParam);
	return S_OK;
}

HRESULT CDirectX::Cleanup()
{
	SAFE_RELEASE(D3DXFont);			// D3DXFont オブジェクトを解放
	SAFE_RELEASE(D3DDevice);		// Direct3DDevice オブジェクトを解放
	SAFE_RELEASE(D3D);				// Direct3D オブジェクトを解放
	return 0;
}
