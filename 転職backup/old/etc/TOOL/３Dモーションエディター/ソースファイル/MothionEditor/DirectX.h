// DirectX.h: CDirectX クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTX_H__7BF157C9_0F4F_4427_ACB6_5B661756941C__INCLUDED_)
#define AFX_DIRECTX_H__7BF157C9_0F4F_4427_ACB6_5B661756941C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	HRESULT Cleanup();
	HRESULT Render();
	HRESULT Initialize(HWND hwnd);
	CDirectX();
	virtual ~CDirectX();

};

#endif // !defined(AFX_DIRECTX_H__7BF157C9_0F4F_4427_ACB6_5B661756941C__INCLUDED_)
