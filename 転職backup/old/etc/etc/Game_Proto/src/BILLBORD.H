class BILLBORD{
	public:
		//----- キャラクターステータス用変数
		float		x, y, z;					// 座標
		float		dx, dy, dz;					// 移動量
		float		pdx,pdy,pdz;				// 変形量(ポイント移動量)
		float		rotx, roty, rotz;			// 角度
		float		drx,dry,drz;				// 角度変更量
		int			texture_size_x;				// テクスチャファイルの横幅
		int			texture_size_y;				// テクスチャファイルの縦幅
		RECT		texRect;					// テクスチャの絵の任意座標
		int			texture_no;					// テクスチャナンバー
		D3DXMATRIX	matrix;						// 変換マトリックス
		RECT		pRect;						// テクスチャを張る板のサイズ
		int			turn;						// 裏表フラグ
		int			status;
		int			draw_flg;
		int			draw_cnt;
		int			kasan_flg;

		//----- モデル用変数
		int						num_vertex;		// 頂点数
		int						num_index;		// 面数
		LPDIRECT3DTEXTURE8		texture;		// テクスチャオブジェクト
		LPDIRECT3DVERTEXBUFFER8	vertex_buffer;	// 頂点バッファ
		VERTEX					*pVertex;		// 頂点設定時に使用するポインタ
		D3DMATERIAL8			mat;			// マテリアルの現在のカラー
		D3DMATERIAL8			defmat;			// マテリアルの初期設定カラー



		//----- モデル用関数
		CleanupGraphics();						// グラフィック関連のクリーンアップ
		SetModelData(HWND,LPDIRECT3DDEVICE8,char**);	// モデルデータセットアップ

		
		//----- キャラクター用関数
		BILLBORD();
		~BILLBORD();							// デストラクタ
		SetMove(float,float,float);				// キャラクタの移動
		SetPoint(float,float,float);			// キャラクタの位置設定
		SetVbuffer(LPDIRECT3DDEVICE8);			// 描画用頂点作成関数
		SetRot();								// 回転処理
		SetRotPoint(float,float,float);			// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8);				// 描画呼び出し
		SerPPoint(float,float,float);			// 変形量の設定
		Initialize(BBORD);

};
BILLBORD::BILLBORD()
{
	CleanupGraphics();
	vertex_buffer = NULL;
}
BILLBORD::~BILLBORD()
{
	CleanupGraphics();
}
BILLBORD::Initialize(BBORD Bbord)
{
	CleanupGraphics();

	// 座標設定
	x = Bbord.bbord_data[Bbord.bbord_data_no].x;
	y = Bbord.bbord_data[Bbord.bbord_data_no].y;
	z = Bbord.bbord_data[Bbord.bbord_data_no].z;

	// 移動値設定
	dx = Bbord.bbord_data[Bbord.bbord_data_no].dx;
	dy = Bbord.bbord_data[Bbord.bbord_data_no].dy;
	dz = Bbord.bbord_data[Bbord.bbord_data_no].dz;

	pdx = pdy = pdz = 0;

	// 頂点数・面数設定
	num_vertex = Bbord.bbord_data[Bbord.bbord_data_no].num_vertex;
	num_index = Bbord.bbord_data[Bbord.bbord_data_no].num_index;

	// 回転値設定
	rotx = Bbord.bbord_data[Bbord.bbord_data_no].rotx;
	roty = Bbord.bbord_data[Bbord.bbord_data_no].roty;
	rotz = Bbord.bbord_data[Bbord.bbord_data_no].rotz;

	// テクスチャファイルのサイズ設定
	texture_size_x = Bbord.bbord_data[Bbord.bbord_data_no].texture_size_x;
	texture_size_y = Bbord.bbord_data[Bbord.bbord_data_no].texture_size_y;

	// テクスチャ定義配列の参照値設定
	texture_no = Bbord.bbord_data[Bbord.bbord_data_no].texture_no;

	// 裏表設定
	turn = Bbord.bbord_data[Bbord.bbord_data_no].turn;

	// バッファ初期化
	vertex_buffer = NULL;

	// テクスチャファイル内の座標設定
	texRect.top = Bbord.texture_offset[Bbord.texture_offset_no].top;
	texRect.left = Bbord.texture_offset[Bbord.texture_offset_no].left;
	texRect.bottom = Bbord.texture_offset[Bbord.texture_offset_no].bottom;
	texRect.right = Bbord.texture_offset[Bbord.texture_offset_no].right;

	// ボードサイズ設定
	pRect.bottom = Bbord.texture_offset[Bbord.texture_offset_no].bottom - Bbord.texture_offset[Bbord.texture_offset_no].top + 1;
	pRect.right = Bbord.texture_offset[Bbord.texture_offset_no].right - Bbord.texture_offset[Bbord.texture_offset_no].left + 1;
	pRect.top = 0;
	pRect.left = 0;

	kasan_flg = 0;

	draw_flg = 1;

	draw_cnt = 0;

	status = 0;

	// 通常マテリアル設定
	mat.Diffuse.r = 1.0f; 
	mat.Diffuse.g = 1.0f; 
	mat.Diffuse.b = 1.0f; 
	mat.Diffuse.a = 1.0f; 

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

BILLBORD::CleanupGraphics()//開放
{
	SAFE_RELEASE(texture);	// テクスチャオブジェクトを解放
	vertex_buffer = NULL;
	pVertex = NULL;
}
BILLBORD::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}
BILLBORD::SetRot()		//マトリクス合成
{
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);					// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;	// マトリックスを合成（順序に注意！）
}
BILLBORD::SerPPoint(float px,float py,float pz){
	pdy = py;
	pdz = pz;
	pdx = px;
}

BILLBORD::SetModelData(HWND hwnd,LPDIRECT3DDEVICE8 p_Device,char** texture_name){

	// テクスチャファイルを読み込む
	D3DXCreateTextureFromFile(p_Device, texture_name[texture_no], &texture);
	p_Device->CreateVertexBuffer(4*sizeof(VERTEX),0,FVF_VERTEX,D3DPOOL_DEFAULT,&vertex_buffer);


}
BILLBORD::SetVbuffer(LPDIRECT3DDEVICE8 p_Device){

	vertex_buffer->Lock(0,0,(BYTE**)(&pVertex),0);

	if(turn == 1){

		// 裏(ワールドに対して）
		pVertex->x = (float)pRect.right;
		pVertex->y = (float)pRect.bottom;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.left / texture_size_x;
		pVertex->tv = (float)texRect.top / texture_size_y;
		pVertex++;

		pVertex->x = (float)pRect.left + (int)(pRect.right / pdx);
		pVertex->y = (float)pRect.bottom;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.right / texture_size_x;
		pVertex->tv = (float)texRect.top / texture_size_y;
		pVertex++;

		pRect.left += (int)(pRect.right / pdx);
		pdx = 0;
		pVertex->x = (float)pRect.left;
		pVertex->y = (float)pRect.top;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.right / texture_size_x;
		pVertex->tv = (float)texRect.bottom / texture_size_y;
		pVertex++;

		pVertex->x = (float)pRect.right;
		pVertex->y = (float)pRect.top ;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.left / texture_size_x;
		pVertex->tv = (float)texRect.bottom / texture_size_y;
	}
	// 表(ワールドに対して）
	else{
		pVertex->x = (float)pRect.left;
		pVertex->y = (float)pRect.bottom;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.left / texture_size_x;
		pVertex->tv = (float)texRect.top / texture_size_y;
		pVertex++;

		pVertex->x = (float)pRect.right;
		pVertex->y = (float)pRect.bottom;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.right / texture_size_x;
		pVertex->tv = (float)texRect.top / texture_size_y;
		pVertex++;

		pVertex->x = (float)pRect.right;
		pVertex->y = (float)pRect.top;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.right / texture_size_x;
		pVertex->tv = (float)texRect.bottom / texture_size_y;
		pVertex++;

		pVertex->x = (float)pRect.left;
		pVertex->y = (float)pRect.top;
		pVertex->z = 0;
		pVertex->tu = (float)texRect.left / texture_size_x;
		pVertex->tv = (float)texRect.bottom / texture_size_y;
	}

	vertex_buffer->Unlock();

}

BILLBORD::Draw(LPDIRECT3DDEVICE8 p_Device){

	if(draw_flg == 1){
		SetVbuffer(p_Device);

		p_Device->SetMaterial(&mat);
		p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		p_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

		if(kasan_flg == 0) p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		else{
			p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
		}

		p_Device->SetTexture(0,texture);								// テクスチャ設定
		p_Device->SetTransform(D3DTS_WORLD,&matrix);
		p_Device->SetStreamSource(0,vertex_buffer,sizeof(VERTEX));
		p_Device->DrawPrimitive(D3DPT_TRIANGLEFAN,0,2);

		p_Device->SetMaterial(&defmat);
		p_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
		p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);

	}
}
BILLBORD::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;

	if(x >= 960) x = -320; 
	if(y <= -960) y = 960;
}
BILLBORD::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}

