#pragma once

class CCamera
{
public:
	D3DXMATRIX matView;
	D3DXVECTOR3 GetPosition();
	void AllReset();
	void AddOffset(float offx, float offy);
	D3DXVECTOR3 Offset;
	void SetCameraValue(int dx, int dy, int dw);
	void SetViewMatrix();
	float Scale;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Direction;
	CCamera(void);
	~CCamera(void);
};
