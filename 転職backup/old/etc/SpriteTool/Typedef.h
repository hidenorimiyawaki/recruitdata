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


//--- ビルボード初期データ設定用構造体定義
typedef struct {
	float		x,y,z;
	float		rotx,roty,rotz;
	float		dx, dy, dz;					// 移動量
	int			num_vertex;
	int			num_index;
	int			texture_size_x;
	int			texture_size_y;
	int			texture_no;
	int			turn;						// 裏表フラグ
	int			kasan;
	float		alpha;
	int			anime_max;
	int			anime_frame;
}BBORD_DATA;


#endif