#include "main.h"
//----- 内容定義
BG::BG()
{
	CleanupGraphics();
	// 通常マテリアル設定
	mat.Diffuse.r = 1.0f; 
	mat.Diffuse.g = 1.0f; 
	mat.Diffuse.b = 1.0f; 
	mat.Diffuse.a = 0.0f; 

	mat.Ambient.r = 0; 
	mat.Ambient.g = 0; 
	mat.Ambient.b = 0; 
	mat.Ambient.a = 0; 

	mat.Specular.r = 0; 
	mat.Specular.g = 0; 
	mat.Specular.b = 0; 
	mat.Specular.a = 0; 
	mat.Power = 0; 

	mat.Emissive.r = 1.0f;
	mat.Emissive.g = 1.0f;
	mat.Emissive.b = 1.0f;
	mat.Emissive.a = 0.0f;


	//デフォルトマテリアルの設定
	defmat.Diffuse.r = 1.0f; 
	defmat.Diffuse.g = 1.0f; 
	defmat.Diffuse.b = 1.0f; 
	defmat.Diffuse.a = 0.5f; 

	defmat.Ambient.r = 0; 
	defmat.Ambient.g = 0; 
	defmat.Ambient.b = 0; 
	defmat.Ambient.a = 0; 

	defmat.Specular.r = 0; 
	defmat.Specular.g = 0; 
	defmat.Specular.b = 0; 
	defmat.Specular.a = 0; 
	defmat.Power = 0; 

	defmat.Emissive.r = 0.0f;
	defmat.Emissive.g = 0.0f;
	defmat.Emissive.b = 0.0f;
	defmat.Emissive.a = 0.0f;

}
BG::~BG()
{
	CleanupGraphics();
}
BG::Initialize(YUKA_DATA Bg_Data)
{
	CleanupGraphics();

	x = Bg_Data.x;
	y = Bg_Data.y;
	z = Bg_Data.z;

	drx = Bg_Data.drx;
	dry = Bg_Data.dry;
	drz = Bg_Data.drz;

	dx = Bg_Data.dx;
	dy = Bg_Data.dy;
	dz = Bg_Data.dz;

	rotx = roty = rotz = 0;

	model_no = Bg_Data.model_no;
	texture_no = Bg_Data.texture_no;

}
BG::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;
	if(z < -8000) z = 24000-dx;
}
BG::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}
BG::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}
BG::SetRot()		//マトリクス合成
{
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);					// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;	// マトリックスを合成（順序に注意！）
}
BG::SetModelData(HWND hwnd,LPDIRECT3DDEVICE8 p_Device,char** file_name, char** texture_name){

	DWORD			dwNumMaterials = 0L;
    LPD3DXBUFFER	pD3DXMtrlBuffer;

    // Ｘファイルからメッシュデータを読み込む
	D3DXLoadMeshFromX(file_name[model_no], D3DXMESH_SYSTEMMEM, p_Device, NULL,	// ここでＸファイルを指定
						&pD3DXMtrlBuffer, &dwNumMaterials,&mesh);

	mesh->GetVertexBuffer(&vertex_buffer);		// 頂点バッファオブジェクトへのポインタをゲット
	mesh->GetIndexBuffer(&index_buffer);		// インデックスバッファオブジェクトへのポインタをゲット
	num_vertex = mesh->GetNumVertices();		// 頂点数をゲット
	num_index  = mesh->GetNumFaces();			// 面数をゲット

	// テクスチャファイルを読み込む

	D3DXCreateTextureFromFileEx(p_Device, texture_name[texture_no], 0, 0, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
			0xff000000, NULL, NULL, &texture);				// カラーキーを有効にしている


}
BG::Draw(LPDIRECT3DDEVICE8 p_Device){


	p_Device->SetVertexShader(FVF_VERTEX);									// 頂点フォーマット設定
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);				// αブレンディング設定
	p_Device->SetRenderState(D3DRS_ZENABLE, true);							// Ｚバッファ有効化
	p_Device->SetRenderState(D3DRS_LIGHTING, true);							// ライト有効化
	p_Device->SetMaterial(&mat);
	p_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	p_Device->SetTexture(0,texture);								// テクスチャ設定
	p_Device->SetTransform(D3DTS_WORLD, &matrix);					// ワールドマトリクスをセット
	p_Device->SetStreamSource(0, vertex_buffer, sizeof(VERTEX));	// 頂点バッファ設定
	p_Device->SetIndices(index_buffer, 0);							// インデックスバッファ設定
	p_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,
										num_vertex, 0, num_index); // 描画


}
BG::CleanupGraphics()//開放
{
	SAFE_RELEASE(texture);	// テクスチャオブジェクトを解放
	SAFE_RELEASE(mesh);		// メッシュオブジェクトを解放
	vertex_buffer = NULL;	// 頂点バッファ
	index_buffer = NULL;	// インデックスバッファ
}