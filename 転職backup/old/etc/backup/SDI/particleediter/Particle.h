#pragma once

class CParticle
{

	public:
		float		dx, dy, dz;								// 移動量
		float		x, y, z;								// 座標
		float		rotx, roty, rotz;						// 角度
		float		drx,dry,drz;							// 角度変更量
		float		scale;									// 拡大縮小値
		D3DXMATRIX	matrix;									// 変換マトリックス
		int			cnt;									// カウント用
		int			damage;									// 攻撃力
		int			trg;									// 稼動状態判定トリガー
		int			status;									// ステータス
		int			effect_flg;								// エフェクトとして使用する際のフラグ(イレギュラーなので初期化データには含まれない)
		int			effect_cnt;								// エフェクトを時間で動かすためのカウンタ
		int			move_max;								// 弾の移動最大フレーム値
		int			move;									// 弾の移動フレームカウンタ
		int			gravity;								// 重力増加量

	//----- 関数
	public:
		CParticle(void);
		~CParticle(void);
		SetPos(float,float,float,float);					// 絶対位置の指定移動
		SetMove(float,float,float);							// キャラクタの移動
		SetPoint(float,float,float);						// キャラクタの位置設定
		SetRot();											// 回転処理
		SetRotPoint(float,float,float);						// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8,CBillbord*);					// 描画呼び出し(ビルボードクラスの描画を使用する)
		Move();												// 弾としての移動
		EffectSet(POSITION3*);								// パーティクルの移動値設定
};
