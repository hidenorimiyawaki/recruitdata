#include "StdAfx.h"
#include ".\particleediter.h"
#include ".\camera.h"

CCamera::CCamera()
{
	//----- ここから -----
	Offset.x    = 0.0f;		Offset.y    = 180.0f;	Offset.z    = 0.0f;
	Direction.x = 0.0f;		Direction.y = 0.0f;		Direction.z = 0.0f;
	Position.x  = 0.0f;		Position.y  = 0.0f;		Position.z  = 0.0f;
	Scale       = 2000.0f;
	//----- ここまで -----
}

CCamera::~CCamera()
{

}

void CCamera::SetViewMatrix()
{
	D3DXMATRIX  matRotX, matRotY, matRotZ, tmpmat;
	D3DXVECTOR3 tmpvec;

	// アプリケーションオブジェクトのポインタを取得
	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	// 各軸ごとの回転マトリックスを生成
	D3DXMatrixRotationX(&matRotX, Direction[0]);
	D3DXMatrixRotationY(&matRotY, Direction[1]);
	D3DXMatrixRotationZ(&matRotZ, Direction[2]);
	tmpmat = matRotX * matRotY * matRotZ;	// マトリックスを合成
	
	tmpvec.x = 0.0f;	tmpvec.y = 0.0f;	tmpvec.z = 1.0f * Scale;
	D3DXVec3TransformCoord(&Position, &tmpvec, &tmpmat);	// ベクトルを回転させる
	Position += Offset;		// オフセット分移動

	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&matView, &Position, &Offset, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	pApp->direct_x.D3DDevice->SetTransform(D3DTS_VIEW, &matView);

}

void CCamera::SetCameraValue(int dx, int dy, int dw)
{
	// カメラ位置を設定
	Direction.x += (float)dx / 100.0f;
	Direction.y += (float)dy / 100.0f;
	Scale       += (float)dw;
	SetViewMatrix();
}

void CCamera::AddOffset(float offx, float offy)
{
	// オフセット値を移動
	Offset.x += offx;
	Offset.y += offy;
	SetViewMatrix();
}

void CCamera::AllReset()
{
	// 初期値を設定
	Offset.x    = 0.0f;		Offset.y    = 180.0f;	Offset.z    = 0.0f;
	Direction.x = 0.0f;		Direction.y = 0.0f;		Direction.z = 0.0f;
	Position.x  = 0.0f;		Position.y  = 0.0f;		Position.z  = 0.0f;
	Scale       = 2000.0f;
	SetViewMatrix();
}

D3DXVECTOR3 CCamera::GetPosition()
{
	// 座標値を返す
	return Position;
}
