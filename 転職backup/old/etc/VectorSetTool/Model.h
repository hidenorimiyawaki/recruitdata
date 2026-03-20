// Model.h: CModel クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_H__26D36A48_5489_47AE_A843_E91DE1BF3494__INCLUDED_)
#define AFX_MODEL_H__26D36A48_5489_47AE_A843_E91DE1BF3494__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModel  
{
public:
	void Draw();
	int model_index;
	bool LoadData();
	LPDIRECT3DTEXTURE8 texture;
	LPDIRECT3DINDEXBUFFER8 index_buffer;
	LPDIRECT3DVERTEXBUFFER8 vertex_buffer;
	int index_qty;
	int vertex_qty;
	LPD3DXMESH mesh;
	CModel(int index);
	CModel();
	virtual ~CModel();
	float		x,y,z;

	LPSTR*					ppTexture;		// メッシュファイルに設定されているテクスチャ
	LPDIRECT3DTEXTURE8*		pTexture;
	D3DMATERIAL8*			pMaterial;		// メッシュファイル二設定されているマテリアル
	DWORD					meshSubsets;	// メッシュファイルのオブジェクト数
	LPD3DXMESH				pMesh;			// メッシュファイル用のポインタ
	LPD3DXBUFFER			pMatBuf;		// メッシュファイル用のバッファ
	D3DXMATERIAL*			pMat;			// メッシュファイル用のマテリアルのポインタ
	DWORD					i,n;			// メッシュファイル用のループカウンタ
	float					rotx,roty,rotz;
	D3DXMATRIX	matrix;						// 変換マトリックス

};
#endif // !defined(AFX_MODEL_H__26D36A48_5489_47AE_A843_E91DE1BF3494__INCLUDED_)
