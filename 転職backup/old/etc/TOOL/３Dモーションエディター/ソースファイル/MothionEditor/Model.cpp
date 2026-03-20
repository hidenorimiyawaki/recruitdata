// Model.cpp: CModel クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MothionEditor.h"
#include "Model.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//----- モデルデータファイル定義 -----
struct XFILEINFO {
	char* xfile;				// Ｘファイル名
	char* bmpfile;				// ＢＭＰファイル名
};

XFILEINFO xfileinfo[] = {
	{"model/body_0.x", "model/texture.bmp"},		// 0
	{"model/body_1.x", "model/texture.bmp"},		// 1
	{"model/head.x",   "model/texture.bmp"},		// 2
	{"model/arm_0.x",  "model/texture.bmp"},		// 3
	{"model/arm_1.x",  "model/texture.bmp"},		// 4
	{"model/arm_2.x",  "model/texture.bmp"},		// 5
	{"model/leg_0.x",  "model/texture.bmp"},		// 6
	{"model/leg_1.x",  "model/texture.bmp"},		// 7
	{"model/leg_2.x",  "model/texture.bmp"},		// 8
};

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

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
	
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// Ｘファイルからメッシュデータを読み込む
	if(D3DXLoadMeshFromX(xfileinfo[model_index].xfile, D3DXMESH_SYSTEMMEM, pApp->direct_x.D3DDevice,
						NULL, NULL, NULL, &mesh) != D3D_OK) {
		str.Format("%s : ファイルが見つかりません", xfileinfo[model_index].xfile);
		MessageBox(NULL, str, "Error", MB_OK | MB_ICONERROR);
		return false;
	}
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
	return true;
}

