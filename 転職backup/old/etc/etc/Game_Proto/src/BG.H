class BG{
	public:
		//----- キャラクターステータス用変数
		float		x, y, z;					// 座標
		float		dx, dy, dz;					// 移動量
		float		rotx, roty, rotz;			// 角度
		float		drx,dry,drz;				// 角度変更量
		int			model_no;
		D3DXMATRIX	matrix;						// 変換マトリックス
		
		//----- モデル用変数
		int						num_vertex;		// 頂点数
		int						num_index;		// 面数
		LPDIRECT3DVERTEXBUFFER8	vertex_buffer;	// 頂点バッファ
		LPDIRECT3DINDEXBUFFER8	index_buffer;	// インデックスバッファ
		LPDIRECT3DTEXTURE8		texture;		// テクスチャオブジェクト
		LPD3DXMESH				mesh;			// メッシュオブジェクト

		//----- モデル用関数
		CleanupGraphics();						// グラフィック関連のクリーンアップ
		SetModelData(HWND,LPDIRECT3DDEVICE8,char**,char**);	// モデルデータセットアップ
		
		//----- キャラクター用関数
		BG();									//コンストラクタ
		~BG();									//デストラクタ
		SetMove(float,float,float);				// キャラクタの移動
		SetPoint(float,float,float);			// キャラクタの位置設定
		SetRot();								// 回転処理
		SetRotPoint(float,float,float);			// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8);				// 描画呼び出し
		Initialize(YUKA_DATA);					// 初期化


};

//----- 内容定義
BG::BG()
{
	CleanupGraphics();
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
	D3DXCreateTextureFromFile(p_Device, texture_name[0], &texture);

}
BG::Draw(LPDIRECT3DDEVICE8 p_Device){
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