// Parts.cpp: CParts クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MothionEditor.h"
#include "Parts.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//----- パーツ初期データ
struct PARTSINFO {
	int			model;					// モデル番号
	int			parent;					// 親パーツ番号
	float		px, py, pz;				// 座標
	float		rotx, roty, rotz;		// 回転量
};

PARTSINFO partsinfo[] = {
	//      model         parent    px    py    pz  rotx  roty  rotz
	{MODEL_BODY_0,            -1,    0,    0,    0,    0,    0,    0},	// 0
	{MODEL_BODY_1, PARTS_BODY_0 ,    0,  100,    0,    0,    0,    0},	// 1
	{MODEL_HEAD  , PARTS_BODY_1 ,    0,  110,    0,    0,    0,    0},	// 2
	{MODEL_ARM_0 , PARTS_BODY_1 ,  130,  100,    0,    0,    0,    0},	// 3
	{MODEL_ARM_1 , PARTS_R_ARM_0,    0, -100,    0,    0,    0,    0},	// 4
	{MODEL_ARM_2 , PARTS_R_ARM_1,    0, -100,    0,    0,    0,    0},	// 5
	{MODEL_ARM_0 , PARTS_BODY_1 , -130,  100,    0,    0,    0,    0},	// 6
	{MODEL_ARM_1 , PARTS_L_ARM_0,    0, -100,    0,    0,    0,    0},	// 7
	{MODEL_ARM_2 , PARTS_L_ARM_1,    0, -100,    0,    0,    0,    0},	// 8
	{MODEL_LEG_0 , PARTS_BODY_0 ,   70,   30,    0,    0,    0,    0},	// 9
	{MODEL_LEG_1 , PARTS_R_LEG_0,    0, -120,    0,    0,    0,    0},	// 10
	{MODEL_LEG_2 , PARTS_R_LEG_1,    0, -150,    0,    0,    0,    0},	// 11
	{MODEL_LEG_0 , PARTS_BODY_0 ,  -70,   30,    0,    0,    0,    0},	// 12
	{MODEL_LEG_1 , PARTS_L_LEG_0,    0, -120,    0,    0,    0,    0},	// 13
	{MODEL_LEG_2 , PARTS_L_LEG_1,    0, -150,    0,    0,    0,    0},	// 14
};

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CParts::CParts(int index)
{
	SetInitialData(index);		// 初期値を設定
}

CParts::~CParts()
{

}

void CParts::Draw(bool current)
{
	// パーツの座標軸データ
	LVERTEX axis_model[] = {
		{0.0f, 0.0f, 0.0f, 0xffffff00},	{200.0f,   0.0f,   0.0f, 0xffffff00},	// Ｘ軸
		{0.0f, 0.0f, 0.0f, 0xff00ff00},	{  0.0f, 200.0f,   0.0f, 0xff00ff00},	// Ｙ軸
		{0.0f, 0.0f, 0.0f, 0xff00ffff},	{  0.0f,   0.0f, 200.0f, 0xff00ffff},	// Ｚ軸
	};
	int t_model, t_parent;
	D3DXMATRIX t_matrix;

	// アプリケーションオブジェクトのポインタを取得
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	t_model  = model;
	t_parent = parent;
	t_matrix = matrix;
	while(t_parent != -1) {
		t_matrix = t_matrix * pApp->zintai.parts[t_parent]->matrix;	// 親パーツのマトリックスを合成
		t_parent = pApp->zintai.parts[t_parent]->parent;			// さらなる親を探す
	}
	pApp->direct_x.D3DDevice->SetTransform(D3DTS_WORLD, &t_matrix);	// ワールドマトリクスをセット

	// オブジェクトを描画
	if(current) {
		pApp->direct_x.D3DDevice->SetRenderState(D3DRS_LIGHTING, (pApp->frame_count & 4)? true: false);	// 点滅
	} else {
		pApp->direct_x.D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	}
	pApp->direct_x.D3DDevice->SetVertexShader(FVF_VERTEX);											// 頂点フォーマット設定
	pApp->direct_x.D3DDevice->SetTexture(0, pApp->model_manager.model[t_model]->texture);			// テクスチャ設定
	pApp->direct_x.D3DDevice->SetStreamSource(0,
											pApp->model_manager.model[t_model]->vertex_buffer,
											sizeof(VERTEX));										// 頂点バッファ設定
	pApp->direct_x.D3DDevice->SetIndices(pApp->model_manager.model[t_model]->index_buffer, 0);		// インデックスバッファ設定
	pApp->direct_x.D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,								// 描画
											0, pApp->model_manager.model[t_model]->vertex_qty,
											0, pApp->model_manager.model[t_model]->index_qty);

	// 座標軸を描画
	if(current) {
		pApp->direct_x.D3DDevice->SetVertexShader(FVF_LVERTEX);						// 頂点フォーマット設定
		pApp->direct_x.D3DDevice->SetRenderState(D3DRS_LIGHTING, false);			// ライト無効化
		pApp->direct_x.D3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 3,
												&axis_model[0], sizeof(LVERTEX));	// 描画
	}
}

void CParts::SetMatrix()
{
	D3DXMATRIX	matWorld, matRotateX, matRotateY, matRotateZ, matTrans;

	// アプリケーションオブジェクトのポインタを取得
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	PARTS_ROT_POINT* pt = &rot_point[0][pApp->zintai.cur_frame];
	D3DXMatrixRotationX(&matRotateX, pt->rot[0]);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, pt->rot[1]);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, pt->rot[2]);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, pt->point[0], pt->point[1], pt->point[2]);	// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}

void CParts::Exec()
{
	D3DXMATRIX	matWorld, matRotateX, matRotateY, matRotateZ, matTrans;
	float		timevalue, rot, rot0, rot1, tmpx, tmpy, tmpz;

	// アプリケーションオブジェクトのポインタを取得
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// 線型補間
	PARTS_ROT_POINT* frmpt0 = &rot_point[0][pApp->zintai.cur_frame    ];
	PARTS_ROT_POINT* frmpt1 = &rot_point[0][pApp->zintai.cur_frame + 1];

	// 回転の補間値を計算
	rot0 = frmpt0->rot[0];
	rot1 = frmpt1->rot[0];
	rot = rot0 + (rot1 - rot0) * pApp->anime_time /60;
	D3DXMatrixRotationX(&matRotateX, rot);				// Ｘ軸回転マトリックスを生成
	rot0 = frmpt0->rot[1];
	rot1 = frmpt1->rot[1];
	rot = rot0 + (rot1 - rot0) * pApp->anime_time /60;
	D3DXMatrixRotationY(&matRotateY, rot);				// Ｙ軸回転マトリックスを生成
	rot0 = frmpt0->rot[2];
	rot1 = frmpt1->rot[2];
	rot = rot0 + (rot1 - rot0) * pApp->anime_time /60;
	D3DXMatrixRotationZ(&matRotateZ, rot);				// Ｚ軸回転マトリックスを生成

	// 座標の補間値を計算
	rot0 = frmpt0->point[0];
	rot1 = frmpt1->point[0];
	tmpx = rot0 + (rot1 - rot0) * pApp->anime_time /60;
	rot0 = frmpt0->point[1];
	rot1 = frmpt1->point[1];
	tmpy = rot0 + (rot1 - rot0) * pApp->anime_time /60;
	rot0 = frmpt0->point[2];
	rot1 = frmpt1->point[2];
	tmpz = rot0 + (rot1 - rot0) * pApp->anime_time /60;
	D3DXMatrixTranslation(&matTrans, tmpx, tmpy, tmpz);				// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}

void CParts::SetInitialData(int index)
{
	model  = partsinfo[index].model;
	parent = partsinfo[index].parent;
	for(int j = 0; j < BANK_QTY; j++) {
		for(int i = 0; i < FRAME_QTY; i++) {
			rot_point[j][i].point[0] = partsinfo[index].px;
			rot_point[j][i].point[1] = partsinfo[index].py;
			rot_point[j][i].point[2] = partsinfo[index].pz;
			rot_point[j][i].rot[0]   = partsinfo[index].rotx;
			rot_point[j][i].rot[1]   = partsinfo[index].roty;
			rot_point[j][i].rot[2]   = partsinfo[index].rotz;
		}
	}
	// ワールドマトリクスを初期化
	D3DXMatrixIdentity(&matrix);		// 単位行列を生成
	matrix._41 = rot_point[0][0].point[0];
	matrix._42 = rot_point[0][0].point[1];
	matrix._43 = rot_point[0][0].point[2];
}
