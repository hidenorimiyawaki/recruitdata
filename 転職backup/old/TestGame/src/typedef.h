/************************************************************
*						typedef.h							*
*															*
*		このファイルでは、構造体の定義をします。			*
*															*
*															*
************************************************************/

#ifndef	___TYPEDEF_H___
#define	___TYPEDEF_H___

//----- 頂点フォーマット定義
struct VERTEX{
	float		x, y, z;					// 頂点座標（座標変換あり）
	float		nx, ny, nz;					// 法線ベクトル
	float		tu, tv;						// テクスチャ座標
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)


//--- 座標軸用定義
struct LVERTEX{
	float		x, y, z;					// 頂点
	D3DCOLOR	color;						// ディフューズ色
};
#define	FVF_LVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

//--- 座標用定義(座標・回転併用)
typedef struct{
	float x,y,z;							// 座標・回転用の各軸用X,Y,Z変数
}POSITION;

//--- 初期化パラメータ値設定用構造体
typedef struct {
	float	x,y,z;							// 初期座標
	float	rotx,roty,rotz;					// 初期角度
	int		move_pat_no;					// 移動パターンNo
	int		hp;								// 体力
	int		bllit_max;						// 弾の最大数
	int		bllit_pat_no;					// 弾のパターンNo
	int		status;							// 初期状態の設定フラグ
}DEF_PARAM;

//--- 移動値設定用構造体
typedef struct {
	float	ex,ey,ez;						// 移動する終点
	float	erotx,eroty,erotz;				// 回転する終点
	int		shoot_cnt;						// 攻撃するまでのカウント
	int		gard_cnt;						// 防御するまでのカウント
	int		move_cnt;						// 移動する時間(フレーム)
	int		status;							// その他状態変化のためのフラグ
}MOVE_OFFSET;


//--- 弾移動パターン設定用構造体
typedef struct {
	float   speed;							// 弾の移動速度
	float	rotx,roty,rotz;					// 回転する値
	int		damage;							// 攻撃力
	int		status;							// その他状態変化のためのフラグ
}TAMA_DATA;

//--- 床初期データ設定用構造体
typedef struct {
	float		x,y,z;						// 座標
	float		dx,dy,dz;					// 回転値
	float		drx,dry,drz;				// 回転用オフセット値
	int			model_no;					// モデルの配列参照番号
	int			texture_no;					// テクスチャーの配列参照番号
}YUKA_DATA;

//--- ビルボード初期データ設定用構造体
typedef struct {
	float		x,y,z;						// 座標
	float		rotx,roty,rotz;				// 回転値
	float		dx, dy, dz;					// 移動オフセット量
	int			num_vertex;					// 頂点数
	int			num_index;					// 面数
	int			texture_size_x;				// テクスチャーの横幅
	int			texture_size_y;				// テクスチャーの縦幅
	int			texture_no;					// テクスチャーの配列参照番号
	int			turn;						// 裏表フラグ
	int			kasan;						// 加算半透明フラグ
	float		alpha;						// アルファ値
	int			anime_max;					// アニメーションの最大数
	int			anime_frame;				// アニメーションのフレーム数
}BBORD_DATA;

//----- 頂点フォーマット定義２
struct TLVERTEX {
	float		x, y, z;					// 頂点座標（座標変換あり）
	DWORD		diffuse;					// ディフューズ
};
#define	FVF_TLVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)


//--- 人体用Xファイルとそのテクスチャー参照設定用構造体
struct XFILEINFO {
	char* xfile;							// Ｘファイル名
	char* bmpfile;							// ＢＭＰファイル名
};

//----- パーツ初期化データ設定用構造体
struct PARTSINFO {
	int			model;						// モデル番号
	int			parent;						// 親パーツ番号
	float		px, py, pz;					// 座標
	float		rotx, roty, rotz;			// 回転量
};


//----- 人体用パーツ構造体
struct OBJECT {
	int			status;						// ステータス
	int			index;						// パーツ番号
	int			model;						// モデル番号
	int			parent;						// 親パーツ番号
	float		px, py, pz;					// 座標
	float		rotx, roty, rotz;			// 回転量
	D3DXMATRIX	matrix;						// ローカルワールド変換行列
};

//----- 人体用構造体
struct ZINTAI {
	int			status;						// ステータス
	float		px, py, pz;					// 座標
	float		rotx, roty, rotz;			// 回転量
	int			cur_parts;					// 注目しているパーツ
	OBJECT		parts[PARTS_QTY];			// 各パーツ
};

//----- パーツ角度、位置情報用構造体
struct PARTS_ROT_POINT {
	float rot[3];							// 回転量
	float point[3];							// 座標
};

//----- モデルアニメーションデータ用構造体
struct MOTION_DATA{
	float x;								// X座標移動値	
	float y;								// Y座標移動値
	float z;								// Z座標移動値
	float rotx;								// X座標回転値
	float roty;								// Y座標回転値
	float rotz;								// Z座標回転値
	int	  attack;							// 攻撃フラグ
	int	  gard;								// 防御フラグ
	int	  frame;							// 表示フレーム
};

#endif