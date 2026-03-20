// Camera.h: CCamera クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__E24025AD_3D75_4E64_9548_35EB3F0BC084__INCLUDED_)
#define AFX_CAMERA_H__E24025AD_3D75_4E64_9548_35EB3F0BC084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCamera  
{
public:
	D3DXVECTOR3 GetPosition();
	void AllReset();
	void AddOffset(float offx, float offy);
	D3DXVECTOR3 Offset;
	void SetCameraValue(int dx, int dy, int dw);
	void SetViewMatrix();
	float Scale;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Direction;
	CCamera();
	virtual ~CCamera();

};
#endif // !defined(AFX_CAMERA_H__E24025AD_3D75_4E64_9548_35EB3F0BC084__INCLUDED_)
