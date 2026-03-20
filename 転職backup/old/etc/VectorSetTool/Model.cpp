// Model.cpp: CModel クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VectorSetTool.h"
#include "Model.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
LVERTEX axis_model[] = {
	{0.0f, 0.0f, 0.0f, 0xffffff00},	{200.0f,   0.0f,   0.0f, 0xffffff00},	// Ｘ軸
	{0.0f, 0.0f, 0.0f, 0xff00ff00},	{  0.0f, 200.0f,   0.0f, 0xff00ff00},	// Ｙ軸
	{0.0f, 0.0f, 0.0f, 0xff00ffff},	{  0.0f,   0.0f, 200.0f, 0xff00ffff},	// Ｚ軸
};

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CModel::CModel()
{
	x = y = z = rotx = rotz = roty = 0;
	z = -60;
}

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

bool CModel::LoadData()
{
	// アプリケーションオブジェクトのポインタを取得
	CString str;
	char*				a;
	
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	a = new char[1024];
	strcpy(a,pApp->mainfile);

	// Ｘファイルからメッシュデータを読み込む
	if(D3DXLoadMeshFromX(a, D3DXMESH_MANAGED, pApp->Dx.D3DDevice8,
						NULL, &pMatBuf,&n,&pMesh) != D3D_OK) {
		str.Format("%s : ファイルが見つかりません", a);
		MessageBox(NULL, str, "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	mesh = pMesh;

	meshSubsets = n;

	//マテリアルとテクスチャの設定
	pMat = (D3DXMATERIAL*)pMatBuf->GetBufferPointer();
	ppTexture = new LPSTR[n];
	pMaterial = new D3DMATERIAL8[n];
	pTexture = new LPDIRECT3DTEXTURE8[n];

	for(i=0;i<n;i++){
		pMaterial[i] = pMat[i].MatD3D;
		ppTexture[i] = pMat[i].pTextureFilename;
		//テクスチャ読み込み
		if(ppTexture[i] != NULL){
			if(D3DXCreateTextureFromFile(pApp->Dx.D3DDevice8, pMat[i].pTextureFilename, &pTexture[i]) != D3D_OK) {
			str.Format("%s : ファイルが見つかりません", pMat[i].pTextureFilename);
			MessageBox(NULL, str, "Error", MB_OK | MB_ICONERROR);
			return false;
			}
		}
		else{
			pTexture[i] = NULL;
		}
	}
/*
	vertex_qty = mesh->GetNumVertices();		// 頂点数をゲット
	mesh->GetVertexBuffer(&vertex_buffer);		// 頂点バッファオブジェクトへのポインタをゲット
	index_qty = mesh->GetNumFaces();			// 面数をゲット
	mesh->GetIndexBuffer(&index_buffer);		// インデックスバッファオブジェクトへのポインタをゲット


	// テクスチャ読み込み
	if(D3DXCreateTextureFromFileEx(pApp->direct_x.D3DDevice, xfileinfo[model_index].bmpfile,
								0, 0, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
								D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0, NULL, NULL, &texture) != D3D_OK) {
		str.Format("%s : ファイルが見つかりません", xfileinfo[model_index].bmpfile);
		MessageBox(NULL, str, "Error", MB_OK | MB_ICONERROR);
		return false;
	}
*/
	SAFE_RELEASE(pMatBuf);
	delete a;
	return true;
}

void CModel::Draw()
{
	// パーツの座標軸データ
	// アプリケーションオブジェクトのポインタを取得
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);				// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）
	pApp->Dx.D3DDevice8->SetTransform(D3DTS_WORLD, &matrix);					// ワールドマトリクスをセット

	pApp->Dx.D3DDevice8->SetVertexShader(FVF_VERTEX);						// 頂点フォーマット設定
/*
	// オブジェクトを描画
//	pApp->Dx.D3DDevice8->SetTexture(0, pApp->mainmodel->texture);			// テクスチャ設定
	pApp->Dx.D3DDevice8->SetMaterial(&pMaterial[0]);

	pApp->Dx.D3DDevice8->SetStreamSource(0,pApp->mainmodel.vertex_buffer,
											sizeof(VERTEX));				// 頂点バッファ設定
	pApp->Dx.D3DDevice8->SetIndices(pApp->mainmodel.index_buffer, 0);		// インデックスバッファ設定
	pApp->Dx.D3DDevice8->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,			// 描画
											0, pApp->mainmodel.vertex_qty,
											0, pApp->mainmodel.index_qty);
*/
	pApp->Dx.D3DDevice8->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	pApp->Dx.D3DDevice8->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pApp->Dx.D3DDevice8->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	pApp->Dx.D3DDevice8->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	for(int i=0;i < (int)meshSubsets;i++){
		pApp->Dx.D3DDevice8->SetMaterial(&pMaterial[i]);
		if(pTexture[i] != NULL){
			pApp->Dx.D3DDevice8->SetTexture(0,pTexture[i]);
		}
		mesh->DrawSubset(i);
	}
/*
	// 座標軸を描画
	pApp->Dx.D3DDevice8->SetVertexShader(FVF_LVERTEX);					// 頂点フォーマット設定
	pApp->Dx.D3DDevice8->SetRenderState(D3DRS_LIGHTING, false);			// ライト無効化
	pApp->Dx.D3DDevice8->DrawPrimitiveUP(D3DPT_LINELIST, 3,
											&axis_model[0], sizeof(LVERTEX));	// 描画
*/
}
