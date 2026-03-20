#include "main.h"
//----- 内容定義
ENEMY::ENEMY(){
}
ENEMY::~ENEMY(){
}

ENEMY::Initialize(DEF_PARAM	Enemy_State){
	pos.x = Enemy_State.x;
	pos.y = Enemy_State.y;
	pos.z = Enemy_State.z;

	drot.x = drot.y = drot.z = 0;

	dpos.x = dpos.y = dpos.z = 0;

	rot.x = Enemy_State.rotx;
	rot.y = Enemy_State.roty;
	rot.z = Enemy_State.rotz;

	tama_max = Enemy_State.bllit_max;

	move_flg = 0;
	
	hp = Enemy_State.hp;

	tama_pat_no = Enemy_State.bllit_pat_no;

	move_cnt = 0;

	death = 0;

	hit = 0;

	offset_cnt = 0;

	shoot_cnt = rand() % 360;

	death_cnt = 180;

	target_trg = 0;

	shoot_flg = 0;

	speed = 20;
	dir = 0;
	anime_frame =  0;

	anime_time = 99;

	anime_max =0;

	anime_end = 1;

}

ENEMY::SetMove(float px,float py,float pz){
	pos.x += px;
	pos.y += py;
	pos.z += pz;
}
ENEMY::SetHp(int damage){
	hp = hp - damage;
	if(hp <= 0 ) {
		death = 1;
		hp = 0;
		move_flg = 0;
		SetPoint(80000,80000,80000);
	}
}
ENEMY::Attack(TAMA* Enemy_Tama){
	Enemy_Tama->SetPoint(pos.x-16,pos.y,pos.z);
	rot.y = dir = (float)atan2(enemy.x,enemy.z);

	Enemy_Tama->dx = (float)sin(dir + 180*RAD) * 100;
	Enemy_Tama->dz = (float)cos(dir + 180*RAD) * 100;
	Enemy_Tama->trg = 1;

}
ENEMY::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rot.x);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, rot.y);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rot.z);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);				// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}
ENEMY::SetPoint(float vx,float vy,float vz){
	pos.x = vx;
	pos.y = vy;
	pos.z = vz;
}
ENEMY::SetRotPoint(float vrotx,float vroty,float vrotz){
	rot.x += vrotx;
	rot.y += vroty;
	rot.z += vrotz;
}

ENEMY::Draw(LPDIRECT3DDEVICE8 p_Device,MODEL* model){
	if(hit == 0){
	}
	else{
		hit_cnt--;
		if(hit_cnt <= 0) hit = 0;
	}
	model->Draw(p_Device,pos,rot,hit);

}

ENEMY::Move(TAMA* Enemy_Tama,MUSIC* EffectSound){

	float work;
	
	if(death == 0){

		if(!((enemy.x < 4000 && enemy.x > -4000) && (enemy.z < 4000 && enemy.z > -4000))){
			/*
			if(enemy.z > 4000){
				rot.y += 1 * RAD;
				if(rot.y > 360*RAD) rot.y -= 360*RAD;
			}
			else {
				rot.y -= 1 * RAD;
				if(rot.y < 0) rot.y += 360*RAD;
			}
*/
			work = (float)atan2(enemy.x,enemy.z);
			if(work < 0) work += 360*RAD;
			if(work > 360*RAD) work -= 360*RAD;
			dir = rot.y = work;

			pos.x -= (float)sin(rot.y) * speed;
			pos.z -= (float)cos(rot.y) * speed;
			target_trg = 1;

		}
		else if((enemy.x < 2000 && enemy.x > -2000) && (enemy.z < 2000 && enemy.z > -2000)){
			pos.x += (float)sin(rot.y) * speed;
			pos.z += (float)cos(rot.y) * speed;
		}
		else {
			if(shoot_cnt > 0 && shoot_flg == 1){
				shoot_cnt--;
				if(shoot_cnt <= 0){
					shoot_cnt = 0;
					shoot_flg = 0;
				}
			}
			else if(shoot_flg == 0){
				if(Enemy_Tama->trg == 0){
					Attack(Enemy_Tama);
					EffectSound->Play();
					shoot_cnt = rand() % 360;
					shoot_flg = 1;
				}
			}
			target_trg = 0;

		}

	}

	if(pos.x <= -11000){
		pos.x = -11000;
//		rot.y -= 180*RAD;
	}
	if(pos.x >= 11000){
		pos.x = 11000;
//		rot.y -= 180*RAD;
	}

	if(pos.z <= -11000){
		pos.z = -11000;
//		rot.y -= 180*RAD;
	}

	if(pos.z >= 27000){
		pos.z = 27000;
//		rot.y -= 180*RAD;
	}

	if(death == 1){
		SetPoint(80000,-80000,80000);
		move_flg = 0;
	}

}
ENEMY::Move(MOVE_OFFSET* Offset_Pat,TAMA* Enemy_Tama){

	if(death == 0){
		if(Offset_Pat[offset_cnt].status != 99 && move_cnt == 0){
			move_cnt = Offset_Pat[offset_cnt].move_cnt;

			dpos.x = Offset_Pat[offset_cnt].ex / Offset_Pat[offset_cnt].move_cnt;
			if(Offset_Pat[offset_cnt].ex == 0 )dpos.x = 0; 

			dpos.y = Offset_Pat[offset_cnt].ey / Offset_Pat[offset_cnt].move_cnt;
			if(Offset_Pat[offset_cnt].ey == 0 )dpos.y = 0; 

			dpos.z = Offset_Pat[offset_cnt].ez / Offset_Pat[offset_cnt].move_cnt;
			if(Offset_Pat[offset_cnt].ez == 0 )dpos.z = 0; 

			drot.x = Offset_Pat[offset_cnt].erotx / Offset_Pat[offset_cnt].move_cnt;
			drot.y = Offset_Pat[offset_cnt].eroty / Offset_Pat[offset_cnt].move_cnt;
			drot.z = Offset_Pat[offset_cnt].erotz / Offset_Pat[offset_cnt].move_cnt;

			shoot_cnt = Offset_Pat[offset_cnt].shoot_cnt;
			offset_cnt++;
		}
		else if(Offset_Pat[offset_cnt].status != 99 && move_cnt != 0){
			if(move_cnt == shoot_cnt)	Attack(Enemy_Tama);
			SetMove(dpos.x,dpos.y,dpos.z);	
			SetRotPoint(drot.x,drot.y,drot.z);
			move_cnt--;
		}
		else if(Offset_Pat[offset_cnt].status == 99 && move_cnt != 0){
			offset_cnt = 0;
		}

	}
	if(death == 1){
		SetPoint(80000,-80000,80000);
		move_flg = 0;
	}

	if(pos.z <= -500 || pos.z >= 5000 || pos.x <= -3000 || pos.x >= 3000 || pos.y <= -3000 || pos.y >= 3000){
		move_flg = 0;
		death = 1;
	}

}
ENEMY::DamegeHit(BILLBORD* HitBord,POSITION pPos){
	if(hit == 0){
		hit = 1; 
		hit_cnt = 10;
		HitBord->draw_flg = 1;
		HitBord->draw_cnt= 5;
		HitBord->SetPoint(pPos.x,pPos.y,pPos.z);
	}
}
ENEMY::GetEnemyPos(POSITION penemy){
	enemy.x = pos.x - penemy.x;
	enemy.y = penemy.y;
	enemy.z = pos.z - penemy.z;

}
ENEMY::HitCheck(){
	if(hit == 0){
	}
	else{
		hit_cnt--;
		if(hit_cnt <= 0) hit = 0;
	}
}
ENEMY::DeathChecker(DEF_PARAM* Def_Enemy){
	if(death == 0){
	}
	else{
		death_cnt--;
		if(death_cnt <= 0) hit = 0;
		Initialize(Def_Enemy[(int)(rand() % 11)]);
	}
}


