// BillBord.cpp: CBillBord クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnimationTool.h"
#include "BillBord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CBillBord::CBillBord()
{
	CleanupGraphics();
	vertex_buffer = NULL;
}
CBillBord::~CBillBord()
{
	CleanupGraphics();
}
CBillBord::Initialize(BBORD_DATA Bbord_Data,RECT Texture_Offset)
{
	CleanupGraphics();

	// 座標設定
	x = Bbord_Data.x;
	y = Bbord_Data.y;
	z = Bbord_Data.z;

	// 移動値設定
	dx = Bbord_Data.dx;
	dy = Bbord_Data.dy;
	dz = Bbord_Data.dz;

	pdx = pdy = pdz = 0;

	// 頂点数・面数設定
	num_vertex = Bbord_Data.num_vertex;
	num_index = Bbord_Data.num_index;

	// 回転値設定
	rotx = Bbord_Data.rotx;
	roty = Bbord_Data.roty;
	rotz = Bbord_Data.rotz;

	// テクスチャファイルのサイズ設定
	texture_size_x = Bbord_Data.texture_size_x;
	texture_size_y = Bbord_Data.texture_size_y;

	// テクスチャ定義配列の参照値設定
	texture_no = Bbord_Data.texture_no;

	// 裏表設定
	turn = Bbord_Data.turn;

	// バッファ初期化
	vertex_buffer = NULL;

	// テクスチャファイル内の座標設定
	texRect.top = Texture_Offset.top;
	texRect.left = Texture_Offset.left;
	texRect.bottom = Texture_Offset.bottom;
	texRect.right = Texture_Offset.right;

	// ボードサイズ設定
	pRect.bottom = Texture_Offset.bottom - Texture_Offset.top + 1;
	pRect.right = Texture_Offset.right - Texture_Offset.left + 1;
	pRect.top = 0;
	pRect.left = 0;

	kasan_flg = Bbord_Data.kasan;

	draw_flg = 1;

	draw_cnt = 0;

	anime_cnt = 0;
	anime_frame = Bbord_Data.anime_frame;
	anime_max = Bbord_Data.anime_max;

	status = 0;

	// 通常マテリアル設定
	mat.Diffuse.r = 1.0f; 
	mat.Diffuse.g = 1.0f; 
	mat.Diffuse.b = 1.0f; 
	mat.Diffuse.a = Bbord_Data.alpha; 

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

CBillBord::CleanupGraphics()//開放
{
	SAFE_RELEASE(texture);	// テクスチャオブジェクトを解放
	vertex_buffer = NULL;
	pVertex = NULL;
}
CBillBord::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}
CBillBord::SetRot()		//マトリクス合成
{
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);					// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;	// マトリックスを合成（順序に注意！）
}
CBillBord::SetPPoint(float px,float py,float pz){
	pdy = py;
	pdz = pz;
	pdx = px;
}

CBillBord::SetModelData(HWND hwnd,LPDIRECT3DDEVICE8 p_Device,char** texture_name){

	// テクスチャファイルを読み込む
	D3DXCreateTextureFromFile(p_Device, texture_name[0], &texture);
	D3DXCreateTextureFromFileExA(p_Device, texture_name[0],0,0,0,NULL,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,NULL,NULL,NULL,&ita,NULL,&texture);
	p_Device->CreateVertexBuffer(4*sizeof(VERTEX),0,FVF_VERTEX,D3DPOOL_DEFAULT,&vertex_buffer);
	

}
CBillBord::SetVbuffer(LPDIRECT3DDEVICE8 p_Device){

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

CBillBord::Draw(LPDIRECT3DDEVICE8 p_Device){

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

CBillBord::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;
}
CBillBord::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}
CBillBord::FrameAnimation(RECT* Texture_Offset){
	texRect.left = Texture_Offset[anime_frame].left;
	texRect.right = Texture_Offset[anime_frame].right;
	anime_cnt++; 
	if(anime_cnt == anime_max){
		anime_cnt = 0;
		anime_frame++;
	}

}
CBillBord::OffsetAnimation(RECT* Texture_Offset){
	texRect.left = Texture_Offset[anime_cnt / anime_frame].left;
	texRect.right = Texture_Offset[anime_cnt / anime_frame].right;
	anime_cnt++;
	if(anime_cnt / anime_frame == anime_max){
		anime_cnt = 0;
	}

}
CBillBord::Timer(){
	if(draw_cnt != 0){
		draw_cnt--;
		if(draw_cnt == 0)draw_flg = 0;
	}
}
CBillBord::Initialize(LPDIRECT3DDEVICE8 p_Device,char* texture_path){

	D3DXCreateTextureFromFile(p_Device, texture_path, &texture);
	D3DXCreateTextureFromFileExA(p_Device, texture_path,0,0,0,NULL,D3DFMT_UNKNOWN,D3DPOOL_DEFAULT,NULL,NULL,NULL,&ita,NULL,&texture);

	// 座標設定
	x = 0;
	y = 0;
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

	kasan_flg = 0;

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

}