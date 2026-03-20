
#include "main.h"

CModel::CModel(int index)
{
	model_index = index;
	texture = 0;
	mesh = 0;
}

CModel::~CModel()
{
	SAFE_RELEASE(texture);	// テクスチャオブジェクトを解放
	SAFE_RELEASE(mesh);		// メッシュオブジェクトを解放
}

bool CModel::LoadData(LPDIRECT3DDEVICE8 p_Device,XFILEINFO* xfileinfo)
{
	

	// Ｘファイルからメッシュデータを読み込む
	if(D3DXLoadMeshFromX(xfileinfo[model_index].xfile, D3DXMESH_MANAGED, p_Device,
						NULL, &pMatBuf, NULL, &mesh) != D3D_OK) {
		return false;
	}

	vertex_qty = mesh->GetNumVertices();		// 頂点数をゲット
	mesh->GetVertexBuffer(&vertex_buffer);		// 頂点バッファオブジェクトへのポインタをゲット
	index_qty = mesh->GetNumFaces();			// 面数をゲット
	mesh->GetIndexBuffer(&index_buffer);		// インデックスバッファオブジェクトへのポインタをゲット

	pMat = (D3DXMATERIAL*)pMatBuf->GetBufferPointer();

	pMaterial = pMat[0].MatD3D;

	SAFE_RELEASE(pMatBuf);

	// テクスチャ読み込み
	if(D3DXCreateTextureFromFileEx(p_Device, xfileinfo[model_index].bmpfile,
								0, 0, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
								D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0, NULL, NULL, &texture) != D3D_OK) {
		return false;
	}
	return true;
	
}