#include "StdAfx.h"
#include ".\billbord.h"
#include "particleediter.h"

CBillbord::CBillbord()
{
	texture = NULL;
	CleanupGraphics();
	vertex_buffer = NULL;
}
CBillbord::~CBillbord()
{
	CleanupGraphics();
}

CBillbord::Initialize(LPDIRECT3DDEVICE8 p_Device,char* texture_path){

	D3DXCreateTextureFromFile(p_Device, texture_path, &texture);
	D3DXCreateTextureFromFileExA(p_Device, texture_path,0,0,0,NULL,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,NULL,NULL,NULL,&ita,NULL,&texture);

	// 座標設定
	x = 0;//(ita.Width/2);
	y = 0;//(ita.Height/2);
	x*= -1;
	y *= -1;
	z = 0;

	// 移動値設定
	dx = 0;
	dy = 0;
	dz = 0;

	pdx = pdy = pdz = 0;

	// 頂点数・面数設定
	num_vertex = 4;
	num_index = 2;

	// 回転値設定
	rotx = 0;
	roty = 0;
	rotz = 0;

	scale = 10.0f;


	// テクスチャファイルのサイズ設定
	texture_size_x = ita.Width;
	texture_size_y = ita.Height;

	// 裏表設定
	turn = 1;

	// バッファ初期化
	vertex_buffer = NULL;

	// テクスチャファイル内の座標設定
	texRect.top = 0;
	texRect.left = 0;
	texRect.bottom = ita.Height;
	texRect.right = ita.Width;

	// ボードサイズ設定
	pRect.top = 0;
	pRect.left = 0;
	pRect.bottom = ita.Height;
	pRect.right = ita.Width;

	kasan_flg = 1;

	draw_flg = 1;

	draw_cnt = 0;

	anime_cnt = 0;
	anime_frame = 0;
	anime_max = 0;

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

	p_Device->CreateVertexBuffer(4*sizeof(VERTEX),0,FVF_VERTEX,D3DPOOL_DEFAULT,&vertex_buffer);
	p_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	SetVbuffer(p_Device);

}
CBillbord::CleanupGraphics()//開放
{
	SAFE_RELEASE(texture);	// テクスチャオブジェクトを解放
	vertex_buffer = NULL;
	pVertex = NULL;
}
CBillbord::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}
CBillbord::Update()		//マトリクス合成
{
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matScale;								// 拡縮マトリックス
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);					// 平行移動マトリックスを生成
	D3DXMatrixScaling(&matScale,scale,scale,scale);
	matrix = matRotateX * matRotateY * matRotateZ * matScale * matTrans;	// マトリックスを合成（順序に注意！）
}
CBillbord::SetPPoint(float px,float py,float pz){
	pdy = py;
	pdz = pz;
	pdx = px;
}

CBillbord::SetModelData(HWND hwnd,LPDIRECT3DDEVICE8 p_Device,char** texture_name){

	// テクスチャファイルを読み込む
	D3DXCreateTextureFromFile(p_Device, texture_name[0], &texture);
	D3DXCreateTextureFromFileExA(p_Device, texture_name[0],0,0,0,NULL,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,NULL,NULL,NULL,&ita,NULL,&texture);
	p_Device->CreateVertexBuffer(4*sizeof(VERTEX),0,FVF_VERTEX,D3DPOOL_DEFAULT,&vertex_buffer);
	

}
CBillbord::SetVbuffer(LPDIRECT3DDEVICE8 p_Device){

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

CBillbord::Draw(LPDIRECT3DDEVICE8 p_Device){
	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	HRESULT a;
	if(draw_flg == 1){

//		SetVbuffer(p_Device);


		p_Device->SetVertexShader(FVF_VERTEX);								// 頂点フォーマット指定

		p_Device->SetMaterial(&mat);
		p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		p_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

		if(kasan_flg == 0) p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		else{
			p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
		}

		matrix._11 = pApp->direct_x.camera.matView._11;		matrix._12 = pApp->direct_x.camera.matView._21;		matrix._13 = pApp->direct_x.camera.matView._31;
		matrix._21 = pApp->direct_x.camera.matView._12;		matrix._22 = pApp->direct_x.camera.matView._22;		matrix._23 = pApp->direct_x.camera.matView._32;
		matrix._31 = pApp->direct_x.camera.matView._13;		matrix._32 = pApp->direct_x.camera.matView._23;		matrix._33 = pApp->direct_x.camera.matView._33;

		p_Device->SetTexture(0,texture);								// テクスチャ設定
		p_Device->SetTransform(D3DTS_WORLD,&matrix);
		p_Device->SetStreamSource(0,vertex_buffer,sizeof(VERTEX));
		p_Device->DrawPrimitive(D3DPT_TRIANGLEFAN,0,2);

		p_Device->SetMaterial(&defmat);
		p_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
		p_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);

	}
}

CBillbord::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;
}
CBillbord::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}
CBillbord::FrameAnimation(RECT* Texture_Offset){
	texRect.left = Texture_Offset[anime_frame].left;
	texRect.right = Texture_Offset[anime_frame].right;
	anime_cnt++; 
	if(anime_cnt == anime_max){
		anime_cnt = 0;
		anime_frame++;
	}

}
CBillbord::OffsetAnimation(RECT* Texture_Offset){
	texRect.left = Texture_Offset[anime_cnt / anime_frame].left;
	texRect.right = Texture_Offset[anime_cnt / anime_frame].right;
	anime_cnt++;
	if(anime_cnt / anime_frame == anime_max){
		anime_cnt = 0;
	}

}
CBillbord::Timer(){
	if(draw_cnt != 0){
		draw_cnt--;
		if(draw_cnt == 0)draw_flg = 0;
	}
}
CBillbord::SetMatrix(D3DXMATRIX pmatrix)
{
	matrix = pmatrix;
}