/************************************************************
*					ModelManager.h							*
*															*
*	このファイルでは、人体クラスに使用するモデルの管理		*
*	をするためのクラスの定義をします。						*
*	このファイルはアニメーション作成ツールとの互換性を		*
*	持たせています。(ほぼ同じ処理ということです)			*
*															*
************************************************************/

class CModelManager  
{
	//----- 変数
	public:
		CModel* model[MODEL_QTY];							// 使用最大数のモデル

	//----- 関数
	public:
		CModelManager();									// コンストラクタ
		virtual ~CModelManager();							// デストラクタ
		bool SetupModels(LPDIRECT3DDEVICE8,XFILEINFO*);		// モデルのセットアップ
};
