// DirectX.cpp: CDirectX クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpriteTool.h"
#include "DirectX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////


CDirectX::CDirectX()
{
	// Initializeでやるので、とくになにもしません
	CleanUp();											// たしなみ程度にクリーンアップ
}

CDirectX::~CDirectX()
{
	// とくになにもしません
	CleanUp();											// たしなみ程度にクリーンアップ
}

bool CDirectX::Initialize(HWND hWnd)
{
	HRESULT	hRes;
	D3DDISPLAYMODE disp;
 
	IsInitialize = false;
	ViewScale	 = 3000.0f;

	VecRotation = D3DXVECTOR3(0.0f,0.0f,0.0f);

	// Dirext3D8オブジェクトを取得
	D3D8 = Direct3DCreate8(D3D_SDK_VERSION);
	if(!D3D8){
		MessageBox(hWnd,"Direct3DCreate8に失敗しました。","error",MB_OK | MB_ICONSTOP);
		return false;
	}

	// Direct3D 初期化パラメータの設定
	ZeroMemory(&D3DPresentParam,sizeof(D3DPRESENT_PARAMETERS));
	D3D8->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp);
	D3DPresentParam.BackBufferFormat = disp.Format;
	D3DPresentParam.Windowed = true;
	D3DPresentParam.FullScreen_RefreshRateInHz = 0;
	D3DPresentParam.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// 表示領域サイズの設定
	D3DPresentParam.BackBufferWidth  = SCREEN_WIDTH;
	D3DPresentParam.BackBufferHeight = SCREEN_HEIGHT;
	D3DPresentParam.SwapEffect		 = D3DSWAPEFFECT_DISCARD;
	// Zバッファの自動作成
	D3DPresentParam.EnableAutoDepthStencil = true;
	D3DPresentParam.AutoDepthStencilFormat = D3DFMT_D16;
	// ハードウェアT&Lレンダリングデバイスを作成
	hRes = D3D8->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
							D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DPresentParam, &D3DDevice8);

	if(FAILED(hRes)){
		// ハードウェアレンダリングデバイスを作成
		hRes = D3D8->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,&D3DPresentParam,&D3DDevice8);
		if(FAILED(hRes)){
			// HALが無理なのでREFで試す
			hRes = D3D8->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,&D3DPresentParam,&D3DDevice8);
			if(FAILED(hRes)){
				MessageBox(hWnd,"CreateDeviceに失敗しました。","error",MB_OK | MB_ICONSTOP);
				return false;
			}
		}
	}

	// フォントセットアップ
	HFONT hFont = CreateFont(FONT_SIZE, 0, 0, 0, FW_DONTCARE, false, false, false, SHIFTJIS_CHARSET,
						OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONT_TYPE);
	D3DXCreateFont(D3DDevice8,hFont,&D3DXFont);
	DeleteObject(hFont);

	// レンダリングステートを設定
	D3DDevice8->SetRenderState(D3DRS_ZENABLE,true);
	D3DDevice8->SetRenderState(D3DRS_AMBIENT,0x00ffffff);

	D3DDevice8->SetRenderState(D3DRS_LIGHTING, false);						// ライト有効化
	D3DDevice8->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);


	D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);	// テクスチャの色を使用
	D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);	// 頂点の色を使用
	D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);	// レンダリング時の色の計算方法の設定
	D3DDevice8->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);	// テクスチャの色を使用
	D3DDevice8->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);	// 頂点の色を使用
	D3DDevice8->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	// ビューマトリックス設定
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
						&D3DXVECTOR3(  0.0, 300.0,-2000.0),					// 視点座標
						&D3DXVECTOR3(  0.0,  0.0,    0.0),					// 注視点座標
						&D3DXVECTOR3(  0.0,  1.0,    0.0));					// アップベクトル
	D3DDevice8->SetTransform(D3DTS_VIEW, &matView);

	// プロジェクションマトリックス設定
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,45 * RAD, ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
	D3DDevice8->SetTransform(D3DTS_PROJECTION, &matProj);


	// マテリアルの設定
	ZeroMemory(&AxisMaterial,sizeof(D3DMATERIAL8));
	AxisMaterial.Diffuse.r = AxisMaterial.Diffuse.g = AxisMaterial.Diffuse.b = 1.0f;
	AxisMaterial.Diffuse.a = 1.0f;
	AxisMaterial.Ambient.r = AxisMaterial.Ambient.g = AxisMaterial.Ambient.b = 1.0f;
	AxisMaterial.Ambient.a = 1.0f;
	D3DDevice8->SetMaterial(&AxisMaterial);

	IsInitialize = true;

	return true;
}

void CDirectX::CleanUp()
{
	SAFE_RELEASE(D3DXFont);
	SAFE_RELEASE(D3DDevice8);
	SAFE_RELEASE(D3D8);
}

void CDirectX::Render()
{
	// アプリケーションオブジェクトのポインタを取得
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	DebugStr[0] = NULL;

	// ビューポートをクリア
	D3DDevice8->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_XRGB(0x00,0x60,0x60),1.0f,0);

	D3DDevice8->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定

	if(SUCCEEDED(D3DDevice8->BeginScene())){

	D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
	D3DXMatrixPerspectiveLH(&persMat,656,512,300,0);
	D3DDevice8->SetTransform(D3DTS_VIEW,&viewMat);
	D3DDevice8->SetTransform(D3DTS_PROJECTION,&persMat);

	if(pApp->AlphaFlg == ON){
		D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);	// テクスチャの色を使用
	}
	else{
		D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_DISABLE);	// テクスチャの色を使用
	}

	if(pApp->fileload == 1){
		mainbord.SetRot();
		mainbord.Draw(D3DDevice8);
	}

	// デバッグストリング表示
	RECT strRect;
	char str[256];
	sprintf(str,"サイズ \n(%d,%d)\n\n",
		mainbord.ita.Width ,
		mainbord.ita.Height);

	strcat(DebugStr,str);


	sprintf(str,"始点 \n(%d,%d)\n\n",
		pApp->start.x - 128,
		pApp->start.y);

	strcat(DebugStr,str);

	sprintf(str,"終点 \n(%d,%d)\n\n",
		pApp->end.x - 128,
		pApp->end.y);
/*	strcat(DebugStr,str);

	sprintf(str,"今の点 \n(%d,%d)\n\n",
		pApp->work.x - 128,
		pApp->work.y);
*/
	strcat(DebugStr,str);
	SetRect(&strRect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

	D3DXFont->DrawText(DebugStr,-1,&strRect,DT_LEFT,D3DCOLOR_ARGB(0xff,0xff,0xff,0xff));


	D3DDevice8->EndScene();

	}

	if(FAILED(D3DDevice8->Present(NULL,NULL,NULL,NULL))) D3DDevice8->Reset(&D3DPresentParam);
}

void CDirectX::SetViewMatrix(D3DXVECTOR3 position)
{
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,&position,
						&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,1.0f,0.0f));
	D3DDevice8->SetTransform(D3DTS_VIEW,&matView);
}

void CDirectX::Exec()
{
	// マトリックスをセット
	D3DXMATRIX matWorld,matRotX,matRotY,matRotZ;
	D3DXVECTOR3 tmpvec;
	// アプリケーションオブジェクトのポインタを取得
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	// 回転マトリックスの設定
	D3DXMatrixRotationX(&matRotX,VecRotation[1]);
	D3DXMatrixRotationY(&matRotY,VecRotation[0]);
	D3DXMatrixRotationZ(&matRotZ,VecRotation[2]);
	matWorld = matRotZ * matRotY * matRotX;
	pApp->Dx.D3DDevice8->SetTransform(D3DTS_WORLD,&matWorld);

}

void CDirectX::WorkRender()
{
	// アプリケーションオブジェクトのポインタを取得
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// ビューポートをクリア
	D3DDevice8->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_XRGB(0x00,0x60,0x60),1.0f,0);

	D3DDevice8->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定

	if(SUCCEEDED(D3DDevice8->BeginScene())){

	D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
	D3DXMatrixPerspectiveLH(&persMat,656,512,300,0);
	D3DDevice8->SetTransform(D3DTS_VIEW,&viewMat);
	D3DDevice8->SetTransform(D3DTS_PROJECTION,&persMat);

	if(pApp->AlphaFlg == ON){
		D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	}
	else{
		D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_DISABLE);
	}

	if(pApp->fileload == 1){
		workbord.SetRot();
		workbord.Draw(D3DDevice8);
	}



	D3DDevice8->EndScene();

	}

	if(FAILED(D3DDevice8->Present(NULL,NULL,NULL,NULL))) D3DDevice8->Reset(&D3DPresentParam);

}
void CDirectX::WorkRenderEx()
{
	// アプリケーションオブジェクトのポインタを取得
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// ビューポートをクリア
	D3DDevice8->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_XRGB(0x00,0x60,0x60),1.0f,0);

	D3DDevice8->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定

	if(SUCCEEDED(D3DDevice8->BeginScene())){

	D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(320,240,300),&D3DXVECTOR3(320,240,0),&D3DXVECTOR3(0,1,0));
	D3DXMatrixPerspectiveLH(&persMat,656,512,300,0);
	D3DDevice8->SetTransform(D3DTS_VIEW,&viewMat);
	D3DDevice8->SetTransform(D3DTS_PROJECTION,&persMat);

	if(pApp->AlphaFlg == ON){
		D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	}
	else{
		D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_DISABLE);
	}

	if(pApp->fileload == 1){
		exbord.SetRot();
		exbord.Draw(D3DDevice8);
	}



	D3DDevice8->EndScene();

	}

	if(FAILED(D3DDevice8->Present(NULL,NULL,NULL,NULL))) D3DDevice8->Reset(&D3DPresentParam);

}
