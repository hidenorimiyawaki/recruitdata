/************************************************************
*						parts.h								*
*															*
*	このファイルでは、人体クラスに使用するパーツ用クラス	*
*	の定義をします。										*
*	このファイルはアニメーション作成ツールとの互換性を		*
*	持たせています。(ほぼ同じ処理ということです)			*
*															*									
************************************************************/

class CParts  
{
	//----- 変数
	public:
		PARTS_ROT_POINT rot_point;									// 座標・回転用の構造体
		int				parent;										// パーツの説明
		int				model;										// モデルの説明
		int				t_model, t_parent;							// 別わけのパーツ・モデルの参照値
		D3DXMATRIX		matrix;										// 回転マトリックス
		PARTSINFO*		partsinfo;									// パーツの初期化構造体のポインタ
		D3DXMATRIX		t_matrix;									// 別わけの回転マトリックス
		D3DMATERIAL8	mat;										// このモデルのマテリアル

	//----- 関数
	public:
		CParts(int index);											// コンストラクタ(パーツのインデックスを受け取る)
		virtual ~CParts();											// デストラクタ
		void SetInitialData(int index);								// 位置・回転の初期化(コンストラクタから呼び出す)
		void Exec(MOTION_DATA*,int,int,int);						// 補完処理
		void SetMatrix();											// 移動・回転マトリックスのセット
		void Draw(bool,LPDIRECT3DDEVICE8,CModelManager*,int);		// 描画呼び出し
};
