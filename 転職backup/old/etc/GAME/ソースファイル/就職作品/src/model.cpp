#include "main.h"
MODEL::MODEL()
{
	CleanupGraphics();

	// 通常マテリアル設定
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

MODEL::~MODEL()
{
	CleanupGraphics();
}
MODEL::SetModelData(HWND hwnd,LPDIRECT3DDEVICE8 p_Device,char** xfile_name,int model_no){

	D3DXLoadMeshFromX(xfile_name[model_no], D3DXMESH_MANAGED, p_Device, NULL,&pMatBuf,&n,&pMesh);

	meshSubsets = n;

	NumVertex = pMesh->GetNumVertices();			// 頂点数をゲット
	pMesh->GetVertexBuffer(&lpD3DVertexBuffer);	// 頂点バッファオブジェクトへのポインタをゲット
	NumIndex = pMesh->GetNumFaces();
	pMesh->GetIndexBuffer(&lpD3DIndexBuffer);		// インデックスバッファオブジェクトへのポインタをゲット

	//マテリアルとテクスチャの設定
	pMat = (D3DXMATERIAL*)pMatBuf->GetBufferPointer();
	ppTexture = new LPDIRECT3DTEXTURE8[n];
	pMaterial = new D3DMATERIAL8[n];


	for(i=0;i<n;i++){
		pMaterial[i] = pMat[i].MatD3D;
		ppTexture[i] = NULL;
		//テクスチャ読み込み
		if(pMat[i].pTextureFilename != NULL){
			D3DXCreateTextureFromFile(p_Device,pMat[i].pTextureFilename,&ppTexture[i]);
		}
	}
	SAFE_RELEASE(pMatBuf);

}
MODEL::CleanupGraphics(){	
	SAFE_RELEASE(pMesh);		// メッシュオブジェクトを解放
}

MODEL::Draw(LPDIRECT3DDEVICE8 p_Device,POSITION pPos,POSITION pRot,int hit)
{
	// アプリケーションオブジェクトのポインタを取得

	pos = pPos;
	rot = pRot;
	SetRot();
	p_Device->SetTransform(D3DTS_WORLD, &matrix);					// ワールドマトリクスをセット

	for(int i=0;i < (int)meshSubsets;i++){
		if(hit == 0){
			p_Device->SetMaterial(&pMaterial[i]);
		}
		else{
			p_Device->SetMaterial(&mat);
			p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
			p_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		}

		p_Device->SetTexture(0,ppTexture[i]);
		pMesh->DrawSubset(i);
	}
}
MODEL::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rot.x);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, rot.y);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rot.z);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);				// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}

