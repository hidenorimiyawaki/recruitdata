// DirectX.h: CDirectX クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTX_H__55D4DBF2_BF5F_4A88_A23C_D1D64C1C13F7__INCLUDED_)
#define AFX_DIRECTX_H__55D4DBF2_BF5F_4A88_A23C_D1D64C1C13F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDirectX  
{
public:

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
	CBillBord				mainbord;					// メインウィンドウ用ビルボード
	CBillBord				workbord;					// もう一個ワーク描画用ビルボード(現在未使用)
	CBillBord				exbord;						// もう一個ワーク描画用ビルボード(現在未使用)


	CDirectX();											// コンストラクタ
	virtual ~CDirectX();								// デストラクタ
	void WorkRender();									// 仮描画(途中で使用するための完全ではない描画)関数
	void WorkRenderEx();								// 仮描画(途中で使用するための完全ではない描画)関数
	void Exec();										// 回転・移動マトリックス設定
	void SetViewMatrix(D3DXVECTOR3 position);			// ビューマトリックス設定
	void Render();										// 描画
	void CleanUp();										// 各種開放
	bool Initialize(HWND hWnd);							// 初期化設定

};

#endif // !defined(AFX_DIRECTX_H__55D4DBF2_BF5F_4A88_A23C_D1D64C1C13F7__INCLUDED_)
