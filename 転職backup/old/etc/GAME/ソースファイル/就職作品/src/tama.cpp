#include "main.h"
TAMA::TAMA(){
}
TAMA::~TAMA(){
}

TAMA::SetData(TAMA_DATA Tama_Status){

	status = Tama_Status.status;

	drx = Tama_Status.rotx;
	dry = Tama_Status.roty;
	drz = Tama_Status.rotz;
	
	damage = 20;

	dx = dy = 0;
	dz = Tama_Status.speed;

	trg = 0;
	effect_flg = 0;
	effect_cnt = 0;

	move_max = 70;
	move = 0;
}

TAMA::Draw(LPDIRECT3DDEVICE8 p_Device,BILLBORD* ita,D3DXMATRIX	matWorld){

	ita->draw_flg = 1;
	ita->Draw(p_Device,matWorld);
	ita->draw_flg = 0;
}

TAMA::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);						// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}

TAMA::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}

TAMA::SetPos(float plx,float ply,float enx,float eny){
}


TAMA::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}

TAMA::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;
}

TAMA::Move(){

	if(trg == 1 && effect_flg == 0){
		x += dx;
		y += dy;
		z += dz;
		move++;
		if(move_max <= move || move <= move_max *-1){
			move = 0;
			SetPoint(8000,8000,8000);
			trg = 0;
		}
	}
	if(trg == 1 && effect_flg == 1){
		x += dx;
		y += dy;
		z += dz;
		dy -= 4.9f;			// 重力加速値
		effect_cnt--;	
		if(effect_cnt <= 0){
			SetPoint(15000,15000,15000);
			trg = 0;
		}
	}

	if(trg == 1 && effect_flg == 2){
		x += dx;
		y += dy;
		z += dz;
		dy += 9.8f;			// 逆重力加速値
		effect_cnt--;	
		if(effect_cnt <= 0){
			SetPoint(15000,15000,15000);
			trg = 0;
		}
	}
	if(trg == 1 && effect_flg == 3){
		if(y >= -490){
			x += dx;
			y += dy;
			z += dz;
			dy -= 6.0f;			// 重力加速値
			dx += 1.5f;			// 重力加速値
		}
		else{ 
			rotz += 0.01f;
			effect_cnt--;	
			if(effect_cnt <= 0){
				SetPoint(15000,15000,15000);
				trg = 0;
			}
		}

	}


}
TAMA::EffectSet(POSITION* pPos){

	// 初期化
	x = pPos->x;
	y = pPos->y;
	z = pPos->z;

	// 飛び出す方向を乱数で決める
	dx = (float)(rand() % 80);
	dy = (float)(rand() % 80);
	dz = (float)(rand() % 80);
	trg = 1;
	effect_cnt = 15;
	effect_flg = 1;
}

TAMA::EffectSet2(POSITION* pPos){

	// 初期化
	x = pPos->x;
	y = pPos->y;
	z = pPos->z;

	// 飛び出す方向を乱数で決める
	dx = (float)(rand() % 80);
	dy = (float)(rand() % 80);
	dz = (float)(rand() % 80);
	trg = 1;
	effect_cnt = 10;
	effect_flg = 2;
}

TAMA::EffectSet3(POSITION* pPos,float dir){

	// 初期化
	x = pPos->x - 16;
	y = pPos->y+250;
	z = pPos->z;

	// 飛び出す方向を乱数で決める
	dx = (float)sin(dir) * 10;
	dy = (float)(rand() % 60);
	dz = (float)cos(dir) * (float)(rand() % 60) * 1.5;

	if(dir == 0){
		dx = 30;
		dy = (float)(rand() % 60);
		dz = (float)(rand() % 60) * 1.5;
	}

	trg = 1;
	effect_cnt = 40;
	effect_flg = 3;

}