/************************************************************
*						ENEMY.H								*
*															*
*	このファイルでは、敵キャラクラスの定義をします。		*
*															*
*				作成日：2003/09/17							*
*			最終更新日：2003/09/19							*
*															*
************************************************************/


class ENEMY{
	public:
		//----- キャラクターステータス用変数
		float		x, y, z;			// 座標
		float		dx, dy, dz;			// 移動量
		float		rotx, roty, rotz;	// 角度
		float		drx,dry,drz;		// 角度移動量
		int			tama_max;			// 撃てる弾の最大数
		int			hp;					// キャラクターのヒットポイント
		int			move_flg;			// 行動判定フラグ
		int			status;				// キャラクターステータス
		D3DXMATRIX	matrix;				// 変換マトリックス
		int			move_pat_no;		// 移動パターンNo
		int			tama_pat_no;		// 弾パターンNo
		int			model_no;			// モデルファイルNo
		int			texture_no;			// テクスチャファイルNo
		int			move_cnt;			// 移動用カウンタ
		int			shoot_flg;			// 弾発射フラグ
		int			effect_flg;			// エフェクト起動フラグ
		int			offset_cnt;			// オフセットで移動するためのカウンタ
		int			shoot_cnt;			// 発射感覚
		int			death;				// 死亡判定フラグ
		int			death_cnt;			//
		int			hit;				// ダメージ状態フラグ
		int			hit_cnt;			// ダメージ時間カウント
		int			effect_cnt;
		float		ef_move;
		float		enemy_x,enemy_y,enemy_z;
		float		range_max_x,range_max_y;
		float		range_min_x,range_min_y;
		int			target_trg;			// ターゲット取得フラグ
//		BILLBORD	effect[5];			// エフェクト用ビルボード（ダメージ用＊４＋爆発＊１）


	public:

		//----- キャラクター用関数
		ENEMY();								// コンストラクタ(標準）
		~ENEMY();								// デストラクタ
		SetMove(float,float,float);				// キャラクタの移動
		SetPoint(float,float,float);			// キャラクタの位置設定
		SetHp(int);								// 現在の状態によるヒットポイントの設定
		SetStatus();							// 現在の状態によるステータスの設定
		SetRot();								// 回転処理
		SetRotPoint(float,float,float);			// 回転用の値を設定
		Attack(TAMA*);							// 攻撃処理
		Draw(LPDIRECT3DDEVICE8,CModel*);				// 描画呼び出し
		Move(MOVE_OFFSET*,TAMA*);				// 移動設定2
		GetPlayerPos(float,float,float);		// プレイヤー座標取得
//		SetEffect();	// エフェクト呼び出し
		Initialize(DEF_PARAM);
		Death(ENEMY *);
};

//----- 内容定義
ENEMY::ENEMY(){
}
ENEMY::~ENEMY(){
}
ENEMY::Initialize(DEF_PARAM	Enemy_State){

	x = Enemy_State.x;
	y = Enemy_State.y;
	z = Enemy_State.z;

	drx = dry = drz = 0;

	rotx = Enemy_State.rotx;
	roty = Enemy_State.roty;
	rotz = Enemy_State.rotz;

	tama_max = Enemy_State.bllit_max;

	move_flg = 0;
	
	hp = Enemy_State.hp;

	status = Enemy_State.status;

	tama_pat_no = Enemy_State.bllit_pat_no;

	move_pat_no = Enemy_State.move_pat_no;

	model_no = Enemy_State.model_no;

	texture_no = Enemy_State.texture_no;

	move_cnt = 0;

	shoot_flg = 0;

	death = 0;

	hit = 0;

	range_max_x = ENEMY_RANGE_X;
	range_max_y = ENEMY_RANGE_Y;

	range_min_x = range_max_x * -1;
	range_min_y = range_max_y * -1;

	enemy_x = enemy_y = 0;

	target_trg = 0;	

	rotx = 6; 

	effect_flg = 0;

	offset_cnt = 0;

	shoot_cnt = 0;

	ef_move = EF_OFFSET;

	death_cnt = 20;

	effect_cnt = 20;

}

ENEMY::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;
}
ENEMY::GetPlayerPos(float plx,float ply,float plz){
	enemy_x = plx;
	enemy_y = ply;
	enemy_z = plz;

	target_trg = 1;

	if(enemy_x - x >= range_max_x){
		enemy_x = x - range_max_x;

		if(enemy_y - y >= range_max_y){
			enemy_y = y - range_max_y;
		}
		else if(enemy_y - y <= range_min_y){
			enemy_y = y + range_min_y;
		}
		target_trg = 0;

	}
	else if(enemy_x - x <= range_min_x){
		enemy_x = x + range_min_x;

		if(enemy_y - y >= range_max_y){
			enemy_y = y - range_max_y;
		}
		else if(enemy_y - y <= range_min_y){
			enemy_y = y + range_min_y;
		}
		target_trg = 0;
	}

	if(enemy_y - y >= range_max_y){
		enemy_y = y - range_max_y;

		if(enemy_x - x >= range_max_x){
			enemy_x = x - range_max_x;
		}
		else if(enemy_x - x <= range_min_x){
			enemy_x = x + range_min_x;
		}
		target_trg = 0;

	}
	else if(enemy_y - y <= range_min_y){
		enemy_y = y + range_min_y;

		if(enemy_x - x >= range_max_x){
			enemy_x = x - range_max_x;
		}
		else if(enemy_x - x <= range_min_x){
			enemy_x = x + range_min_x;
		}
		target_trg = 0;
	}


}
ENEMY::SetHp(int damage){
	hp = hp - damage;
	if(hp <= 0 ) {
		death = 1;
		hp = 0;
		move_flg = 0;
		//SetPoint(5000,5000,5000);
	}
}
ENEMY::Attack(TAMA* Enemy_Tama){
	float wk;

	if(Enemy_Tama->trg == 0){
		Enemy_Tama->SetPoint(x,y,z);
		if(target_trg == 1){

			wk = z - enemy_z;
			wk = wk / Enemy_Tama->dz;

			Enemy_Tama->dx = x - enemy_x;
			Enemy_Tama->dy = y - enemy_y;

			Enemy_Tama->dx = (Enemy_Tama->dx / wk);
			Enemy_Tama->dy = (Enemy_Tama->dy / wk); 
			Enemy_Tama->trg = 1;

		}
		else{
			Enemy_Tama->trg = 1;
			Enemy_Tama->dx = 0;
			Enemy_Tama->dy = 0;
		}

	}


}
ENEMY::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);				// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}
ENEMY::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}
ENEMY::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}

ENEMY::Draw(LPDIRECT3DDEVICE8 p_Device,CModel* model){
	if(hit == 0){
	}
	else{
		hit_cnt--;
		if(hit_cnt <= 0) hit = 0;
	}

	model[model_no].Draw(p_Device,x,y,z,rotx,roty,rotz,hit);
}

ENEMY::Move(MOVE_OFFSET* Offset_Pat,TAMA* Enemy_Tama){

	if(death == 0){
		if(Offset_Pat[offset_cnt].status != 99 && move_cnt == 0){
			move_cnt = Offset_Pat[offset_cnt].move_cnt;

			dx = Offset_Pat[offset_cnt].ex / Offset_Pat[offset_cnt].move_cnt;
			if(Offset_Pat[offset_cnt].ex == 0 )dx = 0; 

			dy = Offset_Pat[offset_cnt].ey / Offset_Pat[offset_cnt].move_cnt;
			if(Offset_Pat[offset_cnt].ey == 0 )dy = 0; 

			dz = Offset_Pat[offset_cnt].ez / Offset_Pat[offset_cnt].move_cnt;
			if(Offset_Pat[offset_cnt].ez == 0 )dz = 0; 

			drx = Offset_Pat[offset_cnt].erotx / Offset_Pat[offset_cnt].move_cnt;
			dry = Offset_Pat[offset_cnt].eroty / Offset_Pat[offset_cnt].move_cnt;
			drz = Offset_Pat[offset_cnt].erotz / Offset_Pat[offset_cnt].move_cnt;

			shoot_cnt = Offset_Pat[offset_cnt].shoot_cnt;
			offset_cnt++;
		}
		else if(Offset_Pat[offset_cnt].status != 99 && move_cnt != 0){
			if(move_cnt == shoot_cnt)	Attack(Enemy_Tama);
			SetMove(dx,dy,dz);	
			SetRotPoint(drx,dry,drz);
			move_cnt--;
		}
		else if(Offset_Pat[offset_cnt].status == 99 && move_cnt != 0){
			offset_cnt = 0;
		}

	}
	if(death == 1){
		SetPoint(8000,8000,8000);
		move_flg = 0;
	}

	if(z <= -500 || z >= 5000 || x <= -3000 || x >= 3000 || y <= -3000 || y >= 3000){
		move_flg = 0;
		death = 1;
	}

}
ENEMY::Death(ENEMY* pEnemy){
	if(death == 1){
		pEnemy->move_flg = 1;
	}
}

/*
ENEMY::SetEffect(){

	if(effect[0].draw_flg == 0 && hit == 1){
		effect[0].SetPoint(x - 30,y - 20,z);
		effect[1].SetPoint(x + 30,y - 20,z);
		effect[2].SetPoint(x,y + 50,z);
		effect[3].SetPoint(x,y + 50,z);

		effect[0].draw_flg = 1;
		effect[1].draw_flg = 1;
		effect[2].draw_flg = 1;
		effect[3].draw_flg = 1;
	}

	if(effect[0].draw_flg == 1){
		effect[0].SetMove(-10,ef_move,10);
		effect[1].SetMove(10,ef_move,10);
		effect[2].SetMove(-10,ef_move,10);
		effect[3].SetMove(10,ef_move,10);
		if(effect_cnt == 0){
			effect[0].draw_flg = 0;
			effect[1].draw_flg = 0;
			effect[2].draw_flg = 0;
			effect[3].draw_flg = 0;
			ef_move = EF_OFFSET;
			effect_cnt = 20;
		}
		ef_move--;
		effect_cnt--;
		hit = 0;
	}

	if(death == 1) {
		effect[4].draw_flg = 1;
		effect[4].SetPoint(x - 180,y - 140,z - 120);
		death_cnt--;
		if(death_cnt <= 0){
			death_cnt = 0;
			SetPoint(8000,8000,8000);
		}
	}
}
*/
