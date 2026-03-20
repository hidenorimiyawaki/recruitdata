#include "StdAfx.h"
#include ".\directx.h"
#include "test.h"

//----- ベース座標軸用頂点データ -----
LVERTEX baseaxis[] = {
	{-1000.0f,    0.0f,-1000.0f, 0xffffffff},	{ 1000.0f,   0.0f,-1000.0f, 0xffffffff},	// Ｘ方向０
	{-1000.0f,    0.0f, 1000.0f, 0xffffffff},	{ 1000.0f,   0.0f, 1000.0f, 0xffffffff},	// Ｘ方向１
	{-1000.0f,    0.0f,-1000.0f, 0xffffffff},	{-1000.0f,   0.0f, 1000.0f, 0xffffffff},	// Ｚ方向０
	{ 1000.0f,    0.0f,-1000.0f, 0xffffffff},	{ 1000.0f,   0.0f, 1000.0f, 0xffffffff},	// Ｚ方向１

	{-1000.0f,    0.0f,   0.0f, 0xffff0000},	{ 1030.0f,   0.0f,   0.0f, 0xffff0000},	// Ｘ軸
	{ 1030.0f,    0.0f,   0.0f, 0xffff0000},	{ 1000.0f,  30.0f,   0.0f, 0xffff0000},	// Ｘ軸(矢印)
	{ 1030.0f,    0.0f,   0.0f, 0xffff0000},	{ 1000.0f, -30.0f,   0.0f, 0xffff0000},	// Ｘ軸(矢印)
	{ 1000.0f,  -30.0f,   0.0f, 0xffff0000},	{ 1000.0f,  30.0f,   0.0f, 0xffff0000},	// Ｘ軸(矢印)
	{ 1000.0f,    0.0f, -30.0f, 0xffff0000},	{ 1000.0f,   0.0f,  30.0f, 0xffff0000},	// Ｘ軸(矢印)
	{ 1030.0f,    0.0f,   0.0f, 0xffff0000},	{ 1000.0f,   0.0f,  30.0f, 0xffff0000},	// Ｘ軸(矢印)
	{ 1030.0f,    0.0f,   0.0f, 0xffff0000},	{ 1000.0f,   0.0f, -30.0f, 0xffff0000},	// Ｘ軸(矢印)

	{   0.0f,     0.0f,   0.0f, 0xff00ff00},	{   0.0f, 1000.0f,   0.0f, 0xff00ff00},	// Ｙ軸
	{   0.0f,  1000.0f,   0.0f, 0xff00ff00},	{   0.0f,  970.0f,  30.0f, 0xff00ff00},	// Ｙ軸(矢印)
	{   0.0f,  1000.0f,   0.0f, 0xff00ff00},	{   0.0f,  970.0f, -30.0f, 0xff00ff00},	// Ｙ軸(矢印)
	{   0.0f,  1000.0f,   0.0f, 0xff00ff00},	{  30.0f,  970.0f,   0.0f, 0xff00ff00},	// Ｙ軸(矢印)
	{   0.0f,  1000.0f,   0.0f, 0xff00ff00},	{ -30.0f,  970.0f,   0.0f, 0xff00ff00},	// Ｙ軸(矢印)
	{   0.0f,   970.0f, -30.0f, 0xff00ff00},	{   0.0f,  970.0f,  30.0f, 0xff00ff00},	// Ｙ軸(矢印)
	{   0.0f,   970.0f, -30.0f, 0xff00ff00},	{   0.0f,  970.0f,  30.0f, 0xff00ff00},	// Ｙ軸(矢印)
	{ -30.0f,   970.0f,   0.0f, 0xff00ff00},	{  30.0f,  970.0f,   0.0f, 0xff00ff00},	// Ｙ軸(矢印)

	{   0.0f,    0.0f,-1000.0f, 0xff0000ff},	{   0.0f,   0.0f, 1030.0f, 0xff0000ff},	// Ｚ軸
	{   0.0f,    0.0f, 1030.0f, 0xff0000ff},	{   0.0f,  30.0f, 1000.0f, 0xff0000ff},	// Ｚ軸
	{   0.0f,    0.0f, 1030.0f, 0xff0000ff},	{   0.0f, -30.0f, 1000.0f, 0xff0000ff},	// Ｚ軸
	{   0.0f,    0.0f, 1030.0f, 0xff0000ff},	{  30.0f,   0.0f, 1000.0f, 0xff0000ff},	// Ｚ軸
	{   0.0f,    0.0f, 1030.0f, 0xff0000ff},	{ -30.0f,   0.0f, 1000.0f, 0xff0000ff},	// Ｚ軸
	{  30.0f,    0.0f, 1030.0f, 0xff0000ff},	{ -30.0f,   0.0f, 1000.0f, 0xff0000ff},	// Ｚ軸
	{   0.0f,   30.0f, 1000.0f, 0xff0000ff},	{   0.0f, -30.0f, 1000.0f, 0xff0000ff},	// Ｚ軸

};

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDirectX::CDirectX()
{
	is_initialize = false;
	Cleanup();
	color_r = DEFAULT_COLOR_R;
	color_g = DEFAULT_COLOR_G;
	color_b = DEFAULT_COLOR_B;

}

CDirectX::~CDirectX()
{
	Cleanup();
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
	HFONT hFont = CreateFont(FONT_SIZE, 0, 0, 0, FW_DONTCARE, false, false, false, SHIFTJIS_CHARSET,
						OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONT_TYPE);
	D3DXCreateFont(D3DDevice,hFont,&D3DXFont);
	DeleteObject(hFont);

	// レンダリングステートを設定
	D3DDevice->SetRenderState(D3DRS_ZENABLE,true);
	D3DDevice->SetRenderState(D3DRS_AMBIENT,0x00ffffff);

	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);						// ライト有効化
	D3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
	D3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

	D3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_ADD);	// テクスチャの色を使用
	D3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);	// 頂点の色を使用
	D3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);	// レンダリング時の色の計算方法の設定
	D3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);	// テクスチャの色を使用
	D3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);	// 頂点の色を使用
	D3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);


	// ビューマトリックス設定
	camera.SetViewMatrix();

	// プロジェクションマトリックス設定
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, 30.0f * PI / 180.0f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
								NEAR_CLIP, FAR_CLIP);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	// マテリアルの設定
	ZeroMemory(&AxisMaterial,sizeof(D3DMATERIAL8));
	AxisMaterial.Diffuse.r = AxisMaterial.Diffuse.g = AxisMaterial.Diffuse.b = 1.0f;
	AxisMaterial.Diffuse.a = 1.0f;
	AxisMaterial.Ambient.r = AxisMaterial.Ambient.g = AxisMaterial.Ambient.b = 1.0f;
	AxisMaterial.Ambient.a = 1.0f;
	D3DDevice->SetMaterial(&AxisMaterial);

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

	is_initialize = true;		// 初期化完了
	return hRes;


}

HRESULT CDirectX::Render()
{

	if(D3DDevice == NULL) return false;
	// アプリケーションオブジェクトのポインタを取得
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	debug_str[0] = NULL;	// デバッグストリングバッファ初期化
	
	// ビューポートをクリア
	D3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_XRGB(color_r,color_g,color_b),1.0f,0);

	// シーンを開始
	D3DDevice->BeginScene();
	
	// 座標軸を描画
	D3DXMATRIX IdentityMatrix;
	D3DXMatrixIdentity(&IdentityMatrix);						// 単位行列を生成
	D3DDevice->SetTransform(D3DTS_WORLD, &IdentityMatrix);		// ワールドマトリクスをセット
	D3DDevice->SetVertexShader(FVF_LVERTEX);					// 頂点フォーマット設定
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);			// ライト無効化
	D3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, sizeof(baseaxis)/sizeof(LVERTEX)/2, &baseaxis[0], sizeof(LVERTEX));	// 描画


	// デバッグストリング描画
	RECT strRect;
	char str[256];
	D3DXVECTOR3 cm_pos;
	cm_pos = pApp->direct_x.camera.GetPosition();
	sprintf(str, "カメラ：位置(%8.2f, %8.2f, %8.2f)\n", cm_pos.x, cm_pos.y, cm_pos.z);	strcat(debug_str, str);
	SetRect(&strRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	D3DXFont->DrawText(debug_str, strlen(debug_str), &strRect, DT_TOP, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


	// パーティクル描画
	DrawSprite();

	// シーンを終了
	D3DDevice->EndScene();

	// バックバッファをプライマリにコピー
	if(FAILED(D3DDevice->Present(NULL, NULL, NULL, NULL))) D3DDevice->Reset(&D3DPresentParam);

	return S_OK;
}
void CDirectX::DrawSprite()
{
	float vec;
	int work;

	// アプリケーションオブジェクトのポインタを取得
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	if(mainbord){
		if(pApp->particle){

#if 0
			// Zソート無しでの描画
			for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){

				pApp->particle[i].Move();
				pApp->particle[i].SetRot();
				pApp->particle[i].Draw(D3DDevice,mainbord);
			}

#else
			// Zソート有りでの描画

			for(int i = 0;i < pApp->EditDialog.m_Edit_Num;i++){		

				pApp->particle[i].Move();
				pApp->particle[i].Update();
			}

			for(int i = 0;i < pApp->EditDialog.m_Edit_Num;i++){						// すべてのポリゴンのカメラからの現在の距離を求める
				vec = pow((((pApp->particle[i].x+texrect.left)/2+(pApp->particle[i].x))-camera.Position.x),2)
					+pow((((pApp->particle[i].y+texrect.top)/2+(pApp->particle[i].y))-camera.Position.y),2)
					+pow(((pApp->particle[i].z)/2-camera.Position.z),2);
					DrawVec[i] = pApp->particle[i].z;
					DrawIndex[i] = i;
			}

			for(int i = 0;i < pApp->EditDialog.m_Edit_Num;i++){						// ソートを行い表示する順番を設定
				for(int j = i+1;j <  pApp->EditDialog.m_Edit_Num ;j++){
					if(DrawVec[i] > DrawVec[j]){
						work = DrawVec[i];				// 座標をソーティング
						DrawVec[i] = DrawVec[j];
						DrawVec[j] = work;

						work = DrawIndex[i];					// 描画順の並びをソーティング
						DrawIndex[i] = DrawIndex[j];
						DrawIndex[j] = work;
					}
				}
			}

			for(int i = 0;i < pApp->EditDialog.m_Edit_Num;i++){		
				pApp->particle[DrawIndex[i]].Draw(D3DDevice,mainbord);
			}

#endif
		}
	}

}

HRESULT CDirectX::Cleanup()
{
	SAFE_RELEASE(D3DXFont);			// D3DXFont オブジェクトを解放
	SAFE_RELEASE(D3DDevice);		// Direct3DDevice オブジェクトを解放
	SAFE_RELEASE(D3D);				// Direct3D オブジェクトを解放
	return 0;
}
void CDirectX::SetViewMatrix(D3DXVECTOR3 position)
{
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,&position,
						&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,1.0f,0.0f));
	D3DDevice->SetTransform(D3DTS_VIEW,&matView);
}

void CDirectX::Exec()
{
	// マトリックスをセット
	D3DXMATRIX matWorld,matRotX,matRotY,matRotZ;
	D3DXVECTOR3 tmpvec;
	// アプリケーションオブジェクトのポインタを取得
	// 回転マトリックスの設定
	D3DXMatrixRotationX(&matRotX,VecRotation[1]);
	D3DXMatrixRotationY(&matRotY,VecRotation[0]);
	D3DXMatrixRotationZ(&matRotZ,VecRotation[2]);
	matWorld = matRotZ * matRotY * matRotX;
	D3DDevice->SetTransform(D3DTS_WORLD,&matWorld);

}