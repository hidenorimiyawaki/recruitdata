/****************************************************************
*						enemy.h									*
*																*
*	このファイルでは、敵キャラクタとして使用するキャラクター	*
*	のクラス定義をします。										*
*																*
****************************************************************/

class ENEMY
{
	//----- 変数
	private:
		int			hp_max;						// ヒットポイントの最大値
	public:
		D3DXMATRIX	matrix;						// 変換マトリックス
		POSITION	pos;						// 座標
		POSITION	rot;						// 角度
		POSITION	drot;						// 角度変更量
		POSITION	dpos;						// 移動量
		POSITION	enemy;						// 敵キャラ座標
		int			tama_max;					// 撃てる弾の最大数
		int			hp;							// キャラクターのヒットポイント
		int			move_flg;					// 行動判定フラグ
		int			move_pat_no;				// 移動パターンNo
		int			tama_pat_no;				// 弾パターンNo
		int			model_no;					// モデルファイルNo
		int			texture_no;					// テクスチャファイルNo
		int			move_cnt;					// 移動用カウンタ
		int			offset_cnt;					// オフセットで移動するためのカウンタ
		int			shoot_cnt;					// 弾の発射感覚
		int			death;						// 死亡判定フラグ
		int			death_cnt;					// 死亡カウント(復活までの時間)(予定)
		int			hit;						// ダメージ状態フラグ
		int			hit_cnt;					// ダメージ時間カウント
		int			target_trg;					// ターゲット判定
		int			shoot_flg;					// 攻撃フラグ
		int			speed;						// 移動スピード
		float		dir;						// 回転値
		int			anime_time;					// アニメーション時間
		int			anime_frame;				// アニメーションフレーム
		int			anime_max;					// アニメーション最大値
		int			anime_end;					// アニメーション終了判定


	//----- 関数
	public:
		ENEMY();								// コンストラクタ(標準）
		~ENEMY();								// デストラクタ
		SetMove(float,float,float);				// キャラクタの移動
		SetPoint(float,float,float);			// キャラクタの位置設定
		SetHp(int);								// 現在の状態によるヒットポイントの設定
		SetStatus();							// 現在の状態によるステータスの設定
		SetRot();								// 回転処理
		SetRotPoint(float,float,float);			// 回転用の値を設定
		Attack(TAMA*);							// 攻撃処理
		Draw(LPDIRECT3DDEVICE8,MODEL*);			// 描画呼び出し
		Move(TAMA*,MUSIC*);						// 移動設定
		Move(MOVE_OFFSET* ,TAMA*);				// 移動設定2
		Initialize(DEF_PARAM);					// キャラクターの初期化関数
		DamegeHit(BILLBORD*,POSITION);			// 攻撃を受けたときの処理関数
		GetEnemyPos(POSITION);					// 敵座標取得
		HitCheck();								// 無敵状態判定
		DeathChecker(DEF_PARAM*);				// 死亡復活判定
};
