// Camera.cpp: CCamera クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VectorSetTool.h"
#include "Camera.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CCamera::CCamera()
{
	//----- ここから -----
	Offset.x    = 0.0f;		Offset.y    = 30.0f;	Offset.z    = 0.0f;
	Direction.x = 0.0f;		Direction.y = 0.0f;		Direction.z = 0.0f;
	Position.x  = 0.0f;		Position.y  = 1.69643f*20;		Position.z  = -7.99759f*20;
	Scale       = 0.0f;
	//----- ここまで -----
}

CCamera::~CCamera()
{

}

void CCamera::SetViewMatrix()
{
	D3DXMATRIX matView, matRotX, matRotY, matRotZ, tmpmat;
	D3DXVECTOR3 tmpvec;

	// アプリケーションオブジェクトのポインタを取得
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
/*	
	// 各軸ごとの回転マトリックスを生成
	D3DXMatrixRotationX(&matRotX, Direction[0]);
	D3DXMatrixRotationY(&matRotY, Direction[1]);
	D3DXMatrixRotationZ(&matRotZ, Direction[2]);
	tmpmat = matRotX * matRotY * matRotZ;	// マトリックスを合成
	
	tmpvec.x = 0.0f;	tmpvec.y = 0.0f;	tmpvec.z = 1.0f * Scale;
	D3DXVec3TransformCoord(&Position, &tmpvec, &tmpmat);	// ベクトルを回転させる
	Position += Offset;		// オフセット分移動
*/

	pApp->point_offset_x = pApp->point_offset_y = 0;
	D3DXMatrixLookAtLH(&matView,
						&D3DXVECTOR3( Position[0], Position[1] ,Position[2] + Scale),					// 視点座標
						&D3DXVECTOR3( Position[0] ,Position[1]-(0.19643f*20) ,Position[2]+(7.99759f*20) + Scale),				// 注視点座標
						&D3DXVECTOR3(  0.0,  1.0,    0.0));								// アップベクトル

	// ビューマトリックス設定
//	D3DXMatrixLookAtLH(&matView, &Position, &Offset, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	pApp->Dx.D3DDevice8->SetTransform(D3DTS_VIEW, &matView);
}

void CCamera::SetCameraValue(int dx, int dy, int dw)
{
	// カメラ位置を設定
	if(dx != 0)	Direction.x += (float)dx / 1000.0f;
	if(dy != 0) Direction.y += (float)dy / 1000.0f;
	if(dw != 0) Scale       += (float)dw / 10.0f;
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
	Offset.x    = 0.0f;		Offset.y    = 30.0f;	Offset.z    = 0.0f;
	Direction.x = 0.0f;		Direction.y = 0.0f;		Direction.z = 0.0f;
	Position.x  = 0.0f;		Position.y  = 30.0f;		Position.z  = 0.0f;
	Scale       = 0.0f;
	SetViewMatrix();
}

D3DXVECTOR3 CCamera::GetPosition()
{
	// 座標値を返す
	return Position;
}
