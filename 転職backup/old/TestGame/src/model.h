/****************************************************************
*						model.h									*
*																*
*	このファイルでは、アニメーションをしないキャラクター		*
*	のためのモデルクラスの定義をします。						*
*																*
****************************************************************/

class MODEL  
{
	//----- 変数
	public:
		POSITION	pos;										// 座標
		POSITION	rot;										// 回転値

		//----- モデル用変数
		int						num_vertex;						// 頂点数
		int						num_index;						// 面数
		D3DMATERIAL8			mat;							// マテリアルの現在のカラー
		LPDIRECT3DTEXTURE8*		ppTexture;						// メッシュファイルに設定されているテクスチャ
		D3DMATERIAL8*			pMaterial;						// メッシュファイルに設定されているマテリアル
		DWORD					meshSubsets;					// メッシュファイルのオブジェクト数
		LPD3DXMESH				pMesh;							// メッシュファイル用のポインタ
		LPD3DXBUFFER			pMatBuf;						// メッシュファイル用のバッファ
		D3DXMATERIAL*			pMat;							// メッシュファイル用のマテリアルのポインタ
		DWORD					i,n;							// メッシュファイル用のループカウンタ
		D3DXMATRIX				matrix;							// 変換マトリックス
		int						NumVertex;						// 頂点数2
		int						NumIndex;						// 面数2
		LPDIRECT3DTEXTURE8		Texture;						// メッシュファイルに設定されているテクスチャ
		LPDIRECT3DVERTEXBUFFER8	lpD3DVertexBuffer;				// Direct3DVertexBuffer8 オブジェクト
		LPDIRECT3DINDEXBUFFER8	lpD3DIndexBuffer;				// Direct3DIndexBuffer8 オブジェクト

	//----- 関数
	public:
		MODEL();												// コンストラクタ
		virtual ~MODEL();										// デストラクタ
		CleanUp();												// クリーンアップ(モデル用変数の開放)
		Draw(LPDIRECT3DDEVICE8,POSITION,POSITION,int);			// 描画呼び出し
		CleanupGraphics();										// グラフィック関連のクリーンアップ
		SetModelData(HWND,LPDIRECT3DDEVICE8,char**,int);		// モデルデータセットアップ
		SetRot();												// 回転処理

		//-----背景データ用の設定
		SetModelDataEx(HWND,LPDIRECT3DDEVICE8,char**,char**);	// モデルデータセットアップ(背景モデル用)
		DrawEx(LPDIRECT3DDEVICE8,POSITION);						// 描画呼び出し(背景モデル用)


};
