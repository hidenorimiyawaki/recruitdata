/****************************************************************
*						billbord.h								*
*																*
*	このファイルでは、汎用的に使用するビルボードのための		*
*	のクラス定義をします。										*
*																*
****************************************************************/

class BILLBORD{
	//----- 変数
	public:
		//ステータス用変数
		float					x, y, z;				// 座標
		float					dx, dy, dz;				// 移動量
		float					pdx,pdy,pdz;			// 変形量(ポイント移動量)
		float					rotx, roty, rotz;		// 角度
		float					drx,dry,drz;			// 角度変更量
		int						texture_size_x;			// テクスチャファイルの横幅
		int						texture_size_y;			// テクスチャファイルの縦幅
		RECT					texRect;				// テクスチャの絵の任意座標
		int						texture_no;				// テクスチャの参照番号
		D3DXMATRIX				matrix;					// 変換マトリックス
		RECT					pRect;					// テクスチャを張る板のサイズ
		int						turn;					// 裏表フラグ
		int						status;					// 板のステータス
		int						draw_flg;				// 描画判定フラグ
		int						draw_cnt;				// 描画するまでのカウンタ
		int						kasan_flg;				// 加算半透明判定フラグ
		int						anime_cnt;				// アニメーションカウンタ
		int						anime_max;				// アニメーションカウンタの最大値
		int						anime_frame;			// アニメーションが何フレーム目の絵かの判定変数

		//モデル用変数
		int						num_vertex;				// 頂点数
		int						num_index;				// 面数
		LPDIRECT3DTEXTURE8		texture;				// テクスチャオブジェクト
		LPDIRECT3DVERTEXBUFFER8	vertex_buffer;			// 頂点バッファ
		VERTEX					*pVertex;				// 頂点設定時に使用するポインタ
		D3DMATERIAL8			mat;					// マテリアルの現在のカラー
		D3DMATERIAL8			defmat;					// マテリアルの初期設定カラー


	//----- 関数
	public:
		//キャラクター用関数
		BILLBORD();										// コンストラクタ
		~BILLBORD();									// デストラクタ
		SetMove(float,float,float);						// キャラクタの移動
		SetPoint(float,float,float);					// キャラクタの位置設定
		SetVbuffer(LPDIRECT3DDEVICE8);					// 描画用頂点作成関数
		SetRot();										// 回転処理
		SetRotPoint(float,float,float);					// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8,D3DXMATRIX);				// 描画呼び出し(ワールド座標変換用)
		Draw(LPDIRECT3DDEVICE8);						// 描画呼び出し(スクリーンべた張り用)
		SetPPoint(float,float,float);					// 変形量の設定
		Initialize(BBORD_DATA,RECT);					// 初期化呼び出し
		FrameAnimation(RECT*);							// アニメーション（フレームの時間でアニメーション）
		OffsetAnimation(RECT*);							// アニメーション（オフセットでアニメーション）
		Timer();										// 描画タイマー

		//モデル用関数
		CleanupGraphics();								// グラフィック関連のクリーンアップ
		SetModelData(HWND,LPDIRECT3DDEVICE8,char**);	// モデルデータセットアップ

};
