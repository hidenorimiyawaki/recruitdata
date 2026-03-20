#ifndef _DEFINE_H
#define _DEFINE_H

//----- 定数
#define	SCREEN_WIDTH	640			// スクリーンの幅
#define	SCREEN_HEIGHT	480			// スクリーンの高さ
#define NEAR_CLIP		100.0f		// ニアクリップを行う距離
#define FAR_CLIP		30000.0f	// ファークリップを行う距離
#define	PI				(float)3.1415926535897932
#define FRAME_RATE		(float)1000/60

// モデル番号列挙
enum {
	MODEL_BODY_0 = 0,	MODEL_BODY_1,	MODEL_HEAD,
	MODEL_ARM_0,	MODEL_ARM_1,	MODEL_ARM_2,
	MODEL_LEG_0,	MODEL_LEG_1,	MODEL_LEG_2,
	MODEL_QTY,
};

// パーツ番号列挙
enum {
	PARTS_BODY_0 = 0,	PARTS_BODY_1,	PARTS_HEAD,
	PARTS_R_ARM_0,	PARTS_R_ARM_1,	PARTS_R_ARM_2,
	PARTS_L_ARM_0,	PARTS_L_ARM_1,	PARTS_L_ARM_2,
	PARTS_R_LEG_0,	PARTS_R_LEG_1,	PARTS_R_LEG_2,
	PARTS_L_LEG_0,	PARTS_L_LEG_1,	PARTS_L_LEG_2,
	PARTS_QTY,
};

#define FRAME_QTY	32		// バンクあたりフレーム数
#define BANK_QTY	32		// バンク数
#define TIME_MAX	1000	// フレームタイム上限値

#define ROT_MAX		314		// パーツ回転リミット値
#define POS_MAX		500		// パーツ座標リミット値

//----- マクロ
#define	SAFE_RELEASE(o)	if(o){o->Release();o=NULL;}

//----- 頂点フォーマット定義
struct VERTEX {
	float x, y, z;		// 座標
	float nx, ny, nz;	// 法線
	float tu, tv;		// テクスチャ
};
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// 座標軸表示用フォーマット
struct LVERTEX {
	float x, y, z;		// 座標
	DWORD diffuse;		// ディフューズ色
};
#define	FVF_LVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

//----- 人体用パーツ構造体
struct OBJECT {
	int			status;					// ステータス
	int			index;					// パーツ番号
	int			model;					// モデル番号
	int			parent;					// 親パーツ番号
	float		px, py, pz;				// 座標
	float		rotx, roty, rotz;		// 回転量
	D3DXMATRIX	matrix;					// ローカルワールド変換行列
};

//----- 人体用構造体
struct ZINTAI {
	int			status;					// ステータス
	float		px, py, pz;				// 座標
	float		rotx, roty, rotz;		// 回転量
	int			cur_parts;				// 注目しているパーツ
	OBJECT		parts[PARTS_QTY];		// 各パーツ
};

//----- データセーブ用構造体
struct FRAME {
	short		time;		// 表示時間
	short		attr;		// 属性
	float		px[PARTS_QTY], py[PARTS_QTY], pz[PARTS_QTY];		// 座標
	float		rotx[PARTS_QTY], roty[PARTS_QTY], rotz[PARTS_QTY];	// 回転量
};

//----- 内部使用フレームデータ用構造体
struct FRAME2 {
	UINT	time;		// 表示時間
	UINT	attr;		// 属性
};

//----- パーツ角度、位置情報用構造体
struct PARTS_ROT_POINT {
	float rot[3];		// 回転量
	float point[3];		// 座標
};


struct FLG{
	int attack;
	int gard;
};

struct MOTION_DATA{
	float x,y,z;
	float rotx,roty,rotz;
	int	  attack;
	int	  gard;
	int	  frame;
};
#endif
