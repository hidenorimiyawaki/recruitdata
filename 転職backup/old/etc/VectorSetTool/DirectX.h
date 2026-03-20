// DirectX1.h: CDirectX クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTX1_H__AA0320C2_9061_49F8_80D5_2F474CD70310__INCLUDED_)
#define AFX_DIRECTX1_H__AA0320C2_9061_49F8_80D5_2F474CD70310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDirectX  
{
public:
	CCamera					camera;						// カメラ
	D3DXVECTOR3				VecRotation;				// ベクトル
	LPDIRECT3D8				D3D8;						// 初期化に使用
	LPDIRECT3DDEVICE8		D3DDevice8;					// おなじみのデバイス変数
	D3DPRESENT_PARAMETERS	D3DPresentParam;			// パラメータ設定変数
	LPD3DXFONT				D3DXFont;					// フォント設定変数
	D3DMATERIAL8			AxisMaterial;				// マテリアル色
	UINT					DrawType;					// 描画のタイプフラグ
	float					ViewScale;					// ビューのスケールね
	bool					IsInitialize;				// 初期化終わったんかい？フラグ
	CHAR					DebugStr[4096];				// デバッグ用文字列保存変数
	D3DXMATRIX				viewMat;					// ビューマトリックス
	D3DXMATRIX				persMat;					// パースマトリックス
	D3DXVECTOR3 cm_pos;

	CDirectX();											// コンストラクタ
	virtual ~CDirectX();								// デストラクタ
	void Exec();										// 回転・移動マトリックス設定
	void SetViewMatrix(D3DXVECTOR3 position);			// ビューマトリックス設定
	void Render();										// 描画
	void CleanUp();										// 各種開放
	bool Initialize(HWND hWnd);							// 初期化設定

};

#endif // !defined(AFX_DIRECTX1_H__AA0320C2_9061_49F8_80D5_2F474CD70310__INCLUDED_)
