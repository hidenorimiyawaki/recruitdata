/********************************************************
*						tama.h							*
*														*
*	このファイルでは、弾クラスの定義をします。			*
*	このクラスは、弾だけでなくエフェクトとしての		*
*	小型ビルボードの移動処理にも使用します。			*
*														*									
********************************************************/

class TAMA
{
	//----- 変数
	public:
		float		dx, dy, dz;								// 移動量
		float		x, y, z;								// 座標
		float		rotx, roty, rotz;						// 角度
		float		drx,dry,drz;							// 角度変更量
		D3DXMATRIX	matrix;									// 変換マトリックス
		int			cnt;									// カウント用
		int			damage;									// 攻撃力
		int			trg;									// 稼動状態判定トリガー
		int			status;									// ステータス
		int			effect_flg;								// エフェクトとして使用する際のフラグ(イレギュラーなので初期化データには含まれない)
		int			effect_cnt;								// エフェクトを時間で動かすためのカウンタ
		int			move_max;								// 弾の移動最大フレーム値
		int			move;									// 弾の移動フレームカウンタ

	//----- 関数
	public:
		TAMA();												// コンストラクタ
		SetData(TAMA_DATA);									// 弾としてのステータス初期化
		~TAMA();											// デストラクタ
		SetPos(float,float,float,float);					// 絶対位置の指定移動
		SetMove(float,float,float);							// キャラクタの移動
		SetPoint(float,float,float);						// キャラクタの位置設定
		SetRot();											// 回転処理
		SetRotPoint(float,float,float);						// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8,BILLBORD*,D3DXMATRIX);		// 描画呼び出し(ビルボードクラスの描画を使用する)
		Move();												// 弾としての移動
		EffectSet(POSITION*);								// エフェクトとして使用する場合の移動処理(血用）
		EffectSet2(POSITION*);								// エフェクトとして使用する場合の移動処理(火花用）
		EffectSet3(POSITION*,float);						// エフェクトとして使用する場合の移動処理(薬きょう用）
};
