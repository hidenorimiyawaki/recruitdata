#pragma once

#include "Billbord.h"
class CDirectX
{
public:
	CCamera camera;
	bool is_initialize;
	char debug_str[4096];
	LPD3DXFONT D3DXFont;
	D3DPRESENT_PARAMETERS D3DPresentParam;
	LPDIRECT3DDEVICE8 D3DDevice;
	LPDIRECT3D8 D3D;
	D3DXVECTOR3				VecRotation;				// ベクトル
	D3DXMATRIX				viewMat;					// ビューマトリックス
	D3DXMATRIX				persMat;					// パースマトリックス
	D3DMATERIAL8			AxisMaterial;				// マテリアル色
	CBillbord*				mainbord;					// メインウィンドウ用ビルボード
	int						DrawIndex[PARTICLE_MAX];
	float					DrawVec[PARTICLE_MAX];
	RECT					texrect;
	int						color_r,color_g,color_b;

public:
	HRESULT Cleanup();
	HRESULT Render();
	HRESULT Initialize(HWND hwnd);
	void Exec();										// 回転・移動マトリックス設定
	void SetViewMatrix(D3DXVECTOR3 position);			// ビューマトリックス設定
	void DrawSprite();

	CDirectX(void);
	~CDirectX(void);
};
