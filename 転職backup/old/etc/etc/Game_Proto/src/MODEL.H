class CModel  
{
public:
	float		x,y,z;
	void CleanUp();
	Draw(LPDIRECT3DDEVICE8,float,float,float,float,float,float,int);
	bool Load();
	CleanupGraphics();						// グラフィック関連のクリーンアップ
	SetModelData(HWND,LPDIRECT3DDEVICE8,char**,char**,int);	// モデルデータセットアップ
	CModel();
	virtual ~CModel();
	SetRot();								// 回転処理

	//----- モデル用変数
	LPD3DXMESH				mesh;			// メッシュオブジェクト
	int						num_vertex;		// 頂点数
	int						num_index;		// 面数
	LPDIRECT3DVERTEXBUFFER8	vertex_buffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER8	index_buffer;	// インデックスバッファ
	LPDIRECT3DTEXTURE8		texture;		// テクスチャオブジェクト
	D3DMATERIAL8			mat;			// マテリアルの現在のカラー

	LPDIRECT3DTEXTURE8*		ppTexture;		// メッシュファイルに設定されているテクスチャ
	D3DMATERIAL8*			pMaterial;		// メッシュファイル二設定されているマテリアル
	DWORD					meshSubsets;	// メッシュファイルのオブジェクト数
	LPD3DXMESH				pMesh;			// メッシュファイル用のポインタ
	LPD3DXBUFFER			pMatBuf;		// メッシュファイル用のバッファ
	D3DXMATERIAL*			pMat;			// メッシュファイル用のマテリアルのポインタ
	DWORD					i,n;			// メッシュファイル用のループカウンタ
	float					rotx,roty,rotz;
	D3DXMATRIX	matrix;						// 変換マトリックス

};
CModel::CModel()
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

	mat.Emissive.r = 1.0f;
	mat.Emissive.g = 1.0f;
	mat.Emissive.b = 1.0f;
	mat.Emissive.a = 1.0f;

}

CModel::~CModel()
{
	CleanupGraphics();
}
CModel::SetModelData(HWND hwnd,LPDIRECT3DDEVICE8 p_Device,char** xfile_name, char** texture_name,int model_no){

	D3DXLoadMeshFromX(xfile_name[model_no], D3DXMESH_MANAGED, p_Device, NULL,&pMatBuf,&n,&pMesh);

	mesh = pMesh;

	meshSubsets = n;

	//マテリアルとテクスチャの設定
	pMat = (D3DXMATERIAL*)pMatBuf->GetBufferPointer();
	ppTexture = new LPDIRECT3DTEXTURE8[n];
	pMaterial = new D3DMATERIAL8[n];

	for(i=0;i<n;i++){
		pMaterial[i] = pMat[i].MatD3D;
		ppTexture[i] = NULL;
		//テクスチャ読み込み
		if(pMat[i].pTextureFilename)
			D3DXCreateTextureFromFile(p_Device,pMat[i].pTextureFilename,&ppTexture[i]);
	}

	SAFE_RELEASE(pMatBuf);

}
CModel::CleanupGraphics(){	
	SAFE_RELEASE(texture);	// テクスチャオブジェクトを解放
	SAFE_RELEASE(mesh);		// メッシュオブジェクトを解放
	vertex_buffer = NULL;	// 頂点バッファ
	index_buffer = NULL;	// インデックスバッファ
}

CModel::Draw(LPDIRECT3DDEVICE8 p_Device,float dx,float dy,float dz,float drx,float dry,float drz,int hit)
{
	// アプリケーションオブジェクトのポインタを取得
	x = dx;
	y = dy;
	z = dz;
	rotx = drx;
	roty = dry;
	rotz = drz;
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
		p_Device->SetTexture(0,NULL);
		mesh->DrawSubset(i);
	}
}
CModel::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);				// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}


