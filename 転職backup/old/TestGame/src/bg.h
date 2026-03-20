/****************************************************************
*							bg.h								*
*																*
*	このファイルでは、背景に使用するモデルのためのクラス		*
*	定義をします。												*
*																*
****************************************************************/


class BG{
	//----- 変数
	public:
		//----- キャラクターステータス用変数
		float						x, y, z;					// 座標
		float						dx, dy, dz;					// 移動量
		float						rotx, roty, rotz;			// 角度
		float						drx,dry,drz;				// 角度変更量
		int							model_no;					// モデル参照番号
		int							texture_no;					// テクスチャー参照番号
		D3DXMATRIX					matrix;						// 変換マトリックス
		
		//----- モデル用変数
		int							num_vertex;					// 頂点数
		int							num_index;					// 面数
		LPDIRECT3DVERTEXBUFFER8		vertex_buffer;				// 頂点バッファ
		LPDIRECT3DINDEXBUFFER8		index_buffer;				// インデックスバッファ
		LPDIRECT3DTEXTURE8			texture;					// テクスチャオブジェクト
		LPD3DXMESH					mesh;						// メッシュオブジェクト
		D3DMATERIAL8				mat;						// マテリアルの現在のカラー
		D3DMATERIAL8				defmat;						// マテリアルの初期設定カラー

	//----- 関数
	public:
		//----- モデル用関数
		CleanupGraphics();										// グラフィック関連のクリーンアップ
		SetModelData(HWND,LPDIRECT3DDEVICE8,char**,char**);		// モデルデータセットアップ
		
		//----- キャラクター用関数
		BG();													// コンストラクタ
		~BG();													// デストラクタ
		SetMove(float,float,float);								// キャラクタの移動
		SetPoint(float,float,float);							// キャラクタの位置設定
		SetRot();												// 回転処理
		SetRotPoint(float,float,float);							// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8);								// 描画呼び出し
		Initialize(YUKA_DATA);									// 初期化


};
