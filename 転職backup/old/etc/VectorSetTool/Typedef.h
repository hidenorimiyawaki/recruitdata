#ifndef	___TYPEDEF_H___
#define	___TYPEDEF_H___

//----- 頂点フォーマット定義
struct VERTEX{
	float		x, y, z;			// 頂点座標（座標変換あり）
	float		nx, ny, nz;			// 法線ベクトル
	float		tu, tv;				// テクスチャ座標
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)


//--- 座標軸用定義
struct LVERTEX{
	float		x, y, z;			// 頂点
	D3DCOLOR	color;				// ディフューズ色
};
#define	FVF_LVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#endif
