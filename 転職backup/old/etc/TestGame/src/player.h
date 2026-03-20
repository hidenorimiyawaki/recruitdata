/****************************************************************
*						player.h								*
*																*
*	このファイルでは、プレイヤーとして使用するキャラクター		*
*	のクラス定義をします。										*
*																*
****************************************************************/

class PLAYER
{
	//----- 変数
	public:
		int			hp_max;						// ヒットポイントの最大値
		POSITION	pos;						// 座標
		POSITION	rot;						// 角度
		POSITION	drot;						// 角度変更量
		POSITION	dpos;						// 移動量
		POSITION	enemy;						// 敵の座標(ターゲット決定に使用)
		int			tama_max;					// 撃てる弾の最大数
		int			hp;							// キャラクターのヒットポイント
		int			gp;							// キャラクターのバリアポイント
		int			sp_point;					// スペシャルゲージポイント
		int			sp_max;						// スペシャルゲージの最大値
		int			sp_flg;						// スペシャル攻撃フラグ
		int			hit;						// ヒット状態フラグ
		int			hit_cnt;					// ヒットの無敵時間カウント
		int			death;						// 死亡状態フラグ
		int			status;						// ステータスフラグ
		int			attack_key;					// 攻撃のキートリガー
		int			jump_key;					// ジャンプのキートリガー
		int			key_trg;					// 十字キーのトリガー
		int			key_cnt;					// キーのトリガーのためのカウンタ
		int			jump_trg;					// ジャンプの状態判定トリガー
		int			jump_cnt;					// ジャンプの状態カウント
		int			flash_flg;					// マズルフラッシュのフラグ
		float		speed;						// 移動のスピード
		float		dir;						// プレイヤーの向き(主に攻撃用)
		D3DXMATRIX	matrix;						// 変換マトリックス
		int			anime_flg;					// アニメーションフラグ
		int			target_trg;					// ターゲット取得のトリガー
		int			anime_time;					// アニメーションの時間
		int			anime_frame;				// アニメーションのフレーム
		int			anime_max;					// アニメーションの最大値
		int			anime_end;					// アニメーションの終了判定

	//----- 関数
	public:
		PLAYER();								// コンストラクタ(標準）
		~PLAYER();								// デストラクタ
		GetKey(TAMA*,MUSIC*);					// キー入力判定
		SetMove(float,float,float);				// キャラクタの移動
		SetMove();								// キャラクタの移動
		SetPoint(POSITION);						// キャラクタの位置設定
		SetHp(int);								// 現在の状態によるヒットポイントの設定
		SetRot();								// 回転処理
		SetRotPoint(POSITION);					// 回転用の値を設定
		Attack(TAMA*);							// 攻撃処理
		Draw(LPDIRECT3DDEVICE8,MODEL*);			// 描画呼び出し(モデルクラスの描画を使用する)
		Initialize();							// 初期化呼び出し
		Jump(float*);							// ジャンプ処理
		Flash(BILLBORD*);						// マズルフラッシュ描画呼び出し
		GetEnemyPos(ENEMY*);					// 敵座標取得
		DamegeHit(BILLBORD*,POSITION);			// 攻撃を受けたときの処理関数
		HitCheck();								// 無敵時間処理
};


