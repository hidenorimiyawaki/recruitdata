/************************************************************
*						zintai.h							*
*															*
*	このファイルでは、人体クラスの定義をします。			*
*	このファイルはアニメーション作成ツールとの互換性を		*
*	持たせています。(ほぼ同じ処理ということです)			*
*															*
************************************************************/

class CZintai  
{
	//----- 変数
	public:
		CParts* parts[PARTS_QTY];								// 人体構成パーツ
		int		cur_parts;										// カレントパーツ変数
		int		anime_time;										// アニメーションの時間
		int		anime_frame;									// アニメーションの時間最大数
		int		anime_max;										// アニメーションの最大値
		int		anime_end;										// アニメーションの終了フラグ

	//----- 関数
	public:
		CZintai(PARTSINFO*);									// コンストラクタ(引数はパーツ設定用の構造体のポインタ)
		virtual ~CZintai();										// デストラクタ
		PARTS_ROT_POINT work_point[PARTS_QTY];					// 座標と回転の値
		void Draw(LPDIRECT3DDEVICE8,CModelManager*,int,int);	// 描画
		void Animation(MOTION_DATA*,POSITION*,POSITION*);		// モデルアニメーション
		void ResetData();										// データの再設定
};
