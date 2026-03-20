#include "main.h"
PLAYER::PLAYER(){
	attack_key = jump_key = 0;
}
PLAYER::~PLAYER(){
}

PLAYER::Initialize(){
	pos.x = DEFAULT_PLAYER_X;
	pos.y = DEFAULT_PLAYER_Y;
	pos.z = DEFAULT_PLAYER_Z;
	
	dpos.x = dpos.y = dpos.z = 0;

	drot.x = drot.y = drot.z = 0;

	enemy.x = enemy.y = enemy.z = 0;

	rot.x = rot.y = rot.z = (float)0.0;

	hp = hp_max = 500;

	tama_max = 7;

	key_trg = key_cnt = 0;
	jump_trg = jump_cnt = 0;

	death = 0;

	hit = 0;

	flash_flg = 0;

	speed = 60;

	dir = 0;

	attack_key = jump_key = 0;

	status = STAND;

	anime_flg = 0;
	target_trg = 0;
	anime_frame =  0;

	anime_time = 99;

	anime_max =0;

	anime_end = 1;

}
PLAYER::GetKey(TAMA* Player_Tama,MUSIC* EffectSound){
	int i;

	if(death == 0 && hit == 0){
		if(anime_flg == 0){
			if(jump_trg == 0){
				if((GetAsyncKeyState(VK_UP) & 0x8000)){
					status = DASH;
				}
				else if((GetAsyncKeyState(VK_DOWN) & 0x8000)){
					status = BACK;
				}
				else if((GetAsyncKeyState(VK_LEFT) & 0x8000)){
					status = LSTEP;
				}
				else if((GetAsyncKeyState(VK_RIGHT) & 0x8000)){
					status = RSTEP;
				}
				else {
					status = STAND;
				}

				if((GetAsyncKeyState(VK_UP) & 0x8000) && (GetAsyncKeyState(VK_LEFT) & 0x8000)){
					status = LDASH;
				}
				else if((GetAsyncKeyState(VK_UP) & 0x8000) && (GetAsyncKeyState(VK_RIGHT) & 0x8000)){
					status = RDASH;
				}
				else if((GetAsyncKeyState(VK_DOWN) & 0x8000) && (GetAsyncKeyState(VK_LEFT) & 0x8000)){
					status = LBACK;
				}
				else if((GetAsyncKeyState(VK_DOWN) & 0x8000) && (GetAsyncKeyState(VK_RIGHT) & 0x8000)){
					status = RBACK;
				}
			}
		}

		if(status == DASH){
			speed = 60;
			SetMove();
		}
		else if(status == BACK) {
			speed = -40;
			SetMove();
		}

		if(status == LSTEP){
			dir -= 1 * RAD;
			rot.y -= 1 * RAD;
			if(dir < 0) dir += 360*RAD;
			if(rot.y < 0) rot.y += 360*RAD;
		}
		else if(status == RSTEP) {
			dir += 1 * RAD;
			rot.y += 1 * RAD;
			if(dir > 360*RAD) dir -= 360*RAD;
			if(rot.y > 360*RAD) rot.y -= 360*RAD;
		}

		if(status == LDASH){
			dir -= 1 * RAD;
			rot.y -= 1 * RAD;
			if(dir < 0) dir += 360*RAD;
			if(rot.y < 0) rot.y += 360*RAD;
			speed = 60;
			SetMove();
		}
		else if(status == RDASH) {
			dir += 1 * RAD;
			rot.y += 1 * RAD;
			if(dir > 360*RAD) dir -= 360*RAD;
			if(rot.y > 360*RAD) rot.y -= 360*RAD;
			speed = 60;
			SetMove();
		}

		if(status == LBACK){
			dir -= 1 * RAD;
			rot.y -= 1 * RAD;
			if(dir < 0) dir += 360*RAD;
			if(rot.y < 0) rot.y += 360*RAD;
			speed = -40;
			SetMove();
		}
		else if(status == RBACK) {
			dir += 1 * RAD;
			rot.y += 1 * RAD;
			if(dir > 360*RAD) dir -= 360*RAD;
			if(rot.y > 360*RAD) rot.y -= 360*RAD;
			speed = -40;
			SetMove();
		}
		if(key_trg == 0 && key_cnt == 0){ 
			for(i = 0; i <= tama_max; i++){
				if(Player_Tama->trg == 0){
					if(GetAsyncKeyState('Z') & 0x8000 && attack_key == 0){
						EffectSound->Play();
						Attack(Player_Tama);
						attack_key = 1;
						key_cnt = 5;
						key_trg = 1;
						i = tama_max;
						status = ATTACK;
						anime_flg = 1;
		
					}
				}
				else if(Player_Tama->trg == 1){
					Player_Tama++;
				}
			}
		}
		if(key_trg == 1 && key_cnt != 0){
			key_cnt--;
			if(key_cnt == 0) key_trg = 0;
		}

	}
	else {
		status = DEATH;
	}
}

PLAYER::SetMove(float px,float py,float pz){
	pos.x += px;
	pos.y += py;
	pos.z += pz;
}
PLAYER::SetMove(){
	float	work;
	if(jump_trg == 0){
		pos.x += (float)sin(dir) * speed;
		work = (float)sin(dir) * speed; 
		pos.z += (float)cos(dir) * speed;
	}
	if(pos.x <= -11000) pos.x = -11000;
	if(pos.x >= 11000) pos.x = 11000;

	if(pos.z <= -11000) pos.z = -11000;
	if(pos.z >= 27000) pos.z = 27000;

}
PLAYER::SetHp(int damage){
	hp = hp - damage;
	if(hp <= 0 ) {
		death = 1;
		hp = 0;
		status = DEATH;
	}

}
PLAYER::Attack(TAMA* Player_Tama){

	float work;

	if(death == 0){
		if(jump_trg == 0){
			Player_Tama->SetPoint(pos.x-16,pos.y+250,pos.z);

			if(target_trg == 1){
				work = (float)atan2(enemy.x,enemy.z);
				if(work < 0) work += 360*RAD;
				if(work > 360*RAD) work -= 360*RAD;
				dir = rot.y = work;
				enemy.x = 0;
				enemy.y = 0;
				enemy.z = 0;
			}
		
			Player_Tama->trg = 1;
			Player_Tama->dx = (float)sin(dir) * 150;
			Player_Tama->dy = 0;
			Player_Tama->dz = (float)cos(dir) * 150;
			flash_flg = 1;
		}
		else{
			Player_Tama->SetPoint(pos.x-16,pos.y+250,pos.z);
			if(target_trg == 1){

				work = (float)atan2(enemy.x,enemy.z);
				if(work < 0) work += 360*RAD;
				if(work > 360*RAD) work -= 360*RAD;
				dir = rot.y = work;

				Player_Tama->trg = 1;
				Player_Tama->dx = enemy.x / jump_cnt;
				Player_Tama->dy = (enemy.y - pos.y) / jump_cnt;
				Player_Tama->dz = enemy.z / jump_cnt;
				flash_flg = 1;
			}
			else{
				Player_Tama->trg = 1;
				Player_Tama->dx = (float)sin(dir) * 150;
				Player_Tama->dy = pos.y / jump_cnt * -1;
				Player_Tama->dz = (float)cos(dir) * 150;
				flash_flg = 1;

			}

		}
	}

}
PLAYER::Jump(float* JumpOffset){
	float work;
	if(death == 0 && hit == 0){

		if(GetAsyncKeyState('X') & 0x8000 && jump_trg == 0 && jump_cnt == 0 && jump_key == 0){
			jump_trg = 1;
			jump_key = 1;
			status = JUMP;
		}

		if(jump_trg == 1){
			pos.y += JumpOffset[jump_cnt];
			status = JUMP;
			jump_cnt++;

			if(jump_cnt == JUMP_MAX){
				jump_trg = 0;
				jump_cnt = 0;
				status = STAND;
				anime_flg = 0;
			}
			if(target_trg == 1){
				work = (float)atan2(enemy.x,enemy.z);
				if(work < 0) work += 360*RAD;
				if(work > 360*RAD) work -= 360*RAD;
				dir = rot.y = work;
			}

		}
	}


}
PLAYER::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;					// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;											// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rot.x);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, rot.y);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rot.z);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);			// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

	D3DXVECTOR3	vec_normal, vec_surf;
	D3DXVECTOR3	vec_xtmp, vec_ytmp, vec_ztmp;

}
PLAYER::SetPoint(POSITION pPos){
	pos.x = pPos.x;
	pos.y = pPos.y;
	pos.z = pPos.z;
}
PLAYER::SetRotPoint(POSITION pRPos){
	rot.x = pRPos.x;
	rot.y = pRPos.y;
	rot.z = pRPos.z;
}
PLAYER::Draw(LPDIRECT3DDEVICE8 p_Device,MODEL* model){
	if(hit == 0){
	}
	else{
		hit_cnt--;
		if(hit_cnt <= 0) hit = 0;
	}
	model->matrix = matrix;
	model->Draw(p_Device,pos,rot,hit);
}
PLAYER::Flash(BILLBORD* FlashBord){
	if(flash_flg == 1){
		FlashBord->draw_flg = 1;
		FlashBord->draw_cnt= 5;
		FlashBord->SetPoint(pos.x - 16,pos.y+250,pos.z);
		flash_flg = 0;
	}
}
PLAYER::GetEnemyPos(ENEMY* enemys){

	if(enemys[0].death == 0){
		if((pos.x - enemys[0].pos.x < 4000 && pos.x - enemys[0].pos.x > -4000) && ( pos.z - enemys[0].pos.z < 4000 && pos.z - enemys[0].pos.z > -4000)){
			target_trg = 1;
			enemy.x = enemys[0].pos.x;
			enemy.y = enemys[0].pos.y;
			enemy.z = enemys[0].pos.z;
		}
	}
	else {
		target_trg = 0;
	}

	for(int i = 1; i < ENEMY_MAX; i++){
		if(enemys[i].death == 0){
			if((pos.x - enemys[i].pos.x < 4000 && pos.x - enemys[i].pos.x > -4000) && ( pos.z - enemys[i].pos.z < 4000 && pos.z - enemys[i].pos.z > -4000)){
				if(enemy.x > enemys[i].pos.x && enemy.z > enemys[i].pos.z){
					target_trg = 1;
					enemy.x = enemys[i].pos.x;
					enemy.y = enemys[i].pos.y;
					enemy.z = enemys[i].pos.z;
				}
			}
		}
		else {
			target_trg = 0;
		}
	}


	enemy.x = enemy.x - pos.x;
	enemy.z = enemy.z - pos.z;

	if((enemy.x < 4000 && enemy.x > -4000) && (enemy.z < 4000 && enemy.z > -4000)) target_trg = 1;
	else {
		target_trg = 0;
	}
}
PLAYER::DamegeHit(BILLBORD* HitBord,POSITION pPos){
	if(hit == 0){
		hit = 1; 
		hit_cnt = 20;
		HitBord->draw_flg = 1;
		HitBord->draw_cnt= 5;
		HitBord->SetPoint(pPos.x,pPos.y,pPos.z);
		status = DAMAGE;
	}
}
PLAYER::HitCheck(){
	if(hit == 0){
		
	}
	else{
		hit_cnt--;
		if(hit_cnt <= 0){
			hit = 0;
			attack_key = 0;
			key_trg = key_cnt = 0;
			status = STAND;
		}
	}
}
