#include "main.h"

CParts::CParts(int index)
{
	mat.Diffuse.r = 0.0f; 
	mat.Diffuse.g = 0.0f; 
	mat.Diffuse.b = 0.0f; 
	mat.Diffuse.a = 0.5f; 

	mat.Ambient.r = 0; 
	mat.Ambient.g = 0; 
	mat.Ambient.b = 0; 
	mat.Ambient.a = 0; 

	mat.Specular.r = 0; 
	mat.Specular.g = 0; 
	mat.Specular.b = 0; 
	mat.Specular.a = 0; 
	mat.Power = 0; 

	mat.Emissive.r = 0.7f;
	mat.Emissive.g = 0.7f;
	mat.Emissive.b = 0.7f;
	mat.Emissive.a = 1.0f;
}

CParts::~CParts()
{

}

void CParts::Draw(bool current,LPDIRECT3DDEVICE8 p_Device,CModelManager* model_manager,int hit)
{
	p_Device->SetVertexShader(FVF_VERTEX);									// 頂点フォーマット設定
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);				// αブレンディング設定
	p_Device->SetRenderState(D3DRS_ZENABLE, true);							// Ｚバッファ有効化
	p_Device->SetRenderState(D3DRS_LIGHTING, true);							// ライト有効化

	p_Device->SetTransform(D3DTS_WORLD, &t_matrix);	// ワールドマトリクスをセット

	if(hit == 0){
		p_Device->SetMaterial(&model_manager->model[t_model]->pMaterial);
	}
	else{
		p_Device->SetMaterial(&mat);
		p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
		p_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	}

	// オブジェクトを描画
	p_Device->SetTexture(0, model_manager->model[t_model]->texture);			// テクスチャ設定
	p_Device->SetStreamSource(0,model_manager->model[t_model]->vertex_buffer,sizeof(VERTEX));	// 頂点バッファ設定
	p_Device->SetIndices(model_manager->model[t_model]->index_buffer, 0);		// インデックスバッファ設定
	p_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,								// 描画
											0, model_manager->model[t_model]->vertex_qty,
											0, model_manager->model[t_model]->index_qty);

}

void CParts::SetMatrix()
{

	// アプリケーションオブジェクトのポインタを取得
	D3DXMATRIX	matWorld, matRotateX, matRotateY, matRotateZ, matTrans;

	PARTS_ROT_POINT* pt = &rot_point;
	D3DXMatrixRotationX(&matRotateX, pt->rot[0]);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, pt->rot[1]);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, pt->rot[2]);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, pt->point[0], pt->point[1], pt->point[2]);	// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}

void CParts::Exec(MOTION_DATA* motion,int anime_time,int anime_frame,int i)
{
	float		rot0, rot1;

	// 回転の補間値を計算
	rot0 = motion[(anime_frame * PARTS_QTY) + i].rotx;
	rot1 = motion[((anime_frame + 1) * PARTS_QTY) + i].rotx;
	rot_point.rot[0] = rot0 + (rot1 - rot0) * anime_time /60;

	rot0 = motion[(anime_frame * PARTS_QTY) + i].roty;
	rot1 = motion[((anime_frame + 1) * PARTS_QTY) + i].roty;
	rot_point.rot[1] = rot0 + (rot1 - rot0) * anime_time /60;

	rot0 = motion[(anime_frame * PARTS_QTY) + i].rotz;
	rot1 = motion[((anime_frame + 1) * PARTS_QTY) + i].rotz;
	rot_point.rot[2] = rot0 + (rot1 - rot0) * anime_time /60;

	// 座標の補間値を計算
	rot0 = motion[(anime_frame * PARTS_QTY) + i].x;
	rot1 = motion[((anime_frame + 1) * PARTS_QTY) + i].x;
	rot_point.point[0] = rot0 + (rot1 - rot0) * anime_time /60;

	rot0 = motion[(anime_frame * PARTS_QTY) + i].y;
	rot1 = motion[((anime_frame + 1) * PARTS_QTY) + i].y;
	rot_point.point[1] = rot0 + (rot1 - rot0) * anime_time /60;

	rot0 = motion[(anime_frame * PARTS_QTY) + i].z;
	rot1 = motion[((anime_frame + 1) * PARTS_QTY) + i].z;
	rot_point.point[2] = rot0 + (rot1 - rot0) * anime_time /60;

}

void CParts::SetInitialData(int index)
{
	
	model  = partsinfo[index].model;
	parent = partsinfo[index].parent;

	rot_point.point[0] = partsinfo[index].px;
	rot_point.point[1] = partsinfo[index].py;
	rot_point.point[2] = partsinfo[index].pz;
	rot_point.rot[0]   = partsinfo[index].rotx;
	rot_point.rot[1]   = partsinfo[index].roty;
	rot_point.rot[2]   = partsinfo[index].rotz;

	// ワールドマトリクスを初期化
	D3DXMatrixIdentity(&matrix);		// 単位行列を生成
	matrix._41 = rot_point.point[0];
	matrix._42 = rot_point.point[1];
	matrix._43 = rot_point.point[2];
	
}