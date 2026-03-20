/************************************************************
*						TYPEDEF.H							*
*															*
*		このファイルでは、主に構造体の定義をします。		*
*															*
*				作成日：2003/09/19							*
*			最終更新日：2003/09/19							*
*															*
************************************************************/


//----- 頂点フォーマット定義
struct VERTEX {
	float		x, y, z;			// 頂点座標（座標変換あり）
	float		nx, ny, nz;			// 法線ベクトル
	float		tu, tv;				// テクスチャ座標
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)


//--- 座標軸用定義
struct LVERTEX {
	float		x, y, z;			// 頂点
	D3DCOLOR	color;				// ディフューズ色
};
#define	FVF_LVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)


//--- 初期化パラメータ値設定用構造体定義
typedef struct {
	float	x,y,z;					// 初期座標
	float	rotx,roty,rotz;			// 初期角度
	int		move_pat_no;			// 移動パターンNo
	int		hp;						// 体力
	int		bllit_max;				// 弾の最大数
	int		bllit_pat_no;			// 弾のパターンNo
	int		status;					// 初期状態の設定フラグ
	int		model_no;				// モデルNo.
	int		texture_no;				// テクスチャNo.
}DEF_PARAM;

//--- 移動値設定用構造体定義
typedef struct {
	float	ex,ey,ez;				// 移動する終点
	float	erotx,eroty,erotz;		// 回転する終点
	int		shoot_cnt;				// 攻撃するまでのカウント
	int		gard_cnt;				// 防御するまでのカウント
	int		move_cnt;				// 移動する時間(フレーム)
	int		status;					// その他状態変化のためのフラグ
}MOVE_OFFSET;


//--- 弾移動パターン設定用構造体定義
typedef struct {
	float	rotx,roty,rotz;			// 回転する値
	int		texture_no;
	int		damage;					// 攻撃力
	int		status;					// その他状態変化のためのフラグ
	float   speed;
}TAMA_DATA;

//--- 床初期データ設定用構造体定義
typedef struct {
	float		x,y,z;
	float		dx,dy,dz;
	float		drx,dry,drz;
	int			model_no;
}YUKA_DATA;

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
	int			texture_offset_no;
	int			bord_size_no;
	int			turn;						// 裏表フラグ
}BBORD_DATA;

typedef struct {
	BBORD_DATA*	bbord_data;
	RECT*		texture_offset;
	int			bbord_data_no;
	int			texture_offset_no;
}BBORD;