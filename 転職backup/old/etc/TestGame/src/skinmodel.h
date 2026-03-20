/************************************************************
*						skinmodel.h							*
*															*
*	このファイルでは、人体クラスのために使用するモデル		*
*	クラス定義をします。									*
*	このファイルはアニメーション作成ツールとの互換性を		*
*	持たせています。(ほぼ同じ処理ということです)			*
*															*									
************************************************************/

class CModel  
{
	//----- 変数
	public:
		int						model_index;				// モデルのインデックス(何パーツ目か？)
		int						index_qty;					// 面数
		int						vertex_qty;					// 頂点数
		LPD3DXMESH				mesh;						// メッシュ変数
		D3DMATERIAL8			pMaterial;					// メッシュファイルに設定されているマテリアル
		D3DXMATERIAL*			pMat;						// メッシュファイル用のマテリアルのポインタ
		LPD3DXBUFFER			pMatBuf;					// メッシュファイル用のバッファ
		LPDIRECT3DTEXTURE8		texture;					// テクスチャー変数
		LPDIRECT3DINDEXBUFFER8	index_buffer;				// 面用のバッファ
		LPDIRECT3DVERTEXBUFFER8 vertex_buffer;				// 頂点用のバッファ

	//----- 関数
	public:
		CModel(int index);									// コンストラクタ(引数はモデルのインデックスを与える)
		virtual ~CModel();									// デストラクタ
		bool LoadData(LPDIRECT3DDEVICE8,XFILEINFO*);		// モデルデータの読み込み
};
