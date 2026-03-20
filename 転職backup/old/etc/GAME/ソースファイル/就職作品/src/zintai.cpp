#include "main.h"

CZintai::CZintai(PARTSINFO* partsinfo)
{
	cur_parts = 0;
	for(int i = 0; i < PARTS_QTY; i++) {
		parts[i] = new CParts(i);
		parts[i]->partsinfo = partsinfo;
		parts[i]->SetInitialData(i);
	}

	anime_frame =  0;

	anime_time = 99;

	anime_max =0;

	anime_end = 1;

}

CZintai::~CZintai()
{
	for(int i = 0; i < PARTS_QTY; i++) {
		delete parts[i];
	}
}

void CZintai::Draw(LPDIRECT3DDEVICE8 p_Device,CModelManager* model_manager,int hit,int jump)		// 描画
{
	int flg;
	

	for(int i = 0; i < PARTS_QTY; i++) {
		parts[i]->SetMatrix();			// マトリックスを更新	
	}

	for(i = 0; i < PARTS_QTY; i++) {
		flg =  (i == cur_parts)? true: false;
		// パーツの座標軸データ

		parts[i]->t_model  = parts[i]->model;
		parts[i]->t_parent = parts[i]->parent;
		parts[i]->t_matrix = parts[i]->matrix;

		while(parts[i]->t_parent != -1) {
			parts[i]->t_matrix = parts[i]->t_matrix * parts[parts[i]->t_parent]->matrix;	// 親パーツのマトリックスを合成
			parts[i]->t_parent = parts[parts[i]->t_parent]->parent;			// さらなる親を探す
		}
	}

	if(jump == 0){	
		for(i = PARTS_QTY -1; i >= 0; i--) {
			parts[i]->Draw(flg,p_Device,model_manager,hit);
		}
	}
	else{
		for(i = PARTS_QTY -1; i >= 0; i--) {
			parts[i]->Draw(flg,p_Device,model_manager,hit);
		}
		parts[0]->Draw(flg,p_Device,model_manager,hit);
		parts[1]->Draw(flg,p_Device,model_manager,hit);
		parts[2]->Draw(flg,p_Device,model_manager,hit);

	}

}

void CZintai::ResetData()
{
	for(int i = 0; i < PARTS_QTY; i++) {
		parts[i]->SetInitialData(i);		// データの再セット
	}
}

void CZintai::Animation(MOTION_DATA* motion,POSITION* pos,POSITION* rot)
{
	
	int i;

	parts[0]->rot_point.point[0] = pos->x + motion[(anime_frame * PARTS_QTY)].x;
	parts[0]->rot_point.point[1] = pos->y + motion[(anime_frame * PARTS_QTY)].y;
	parts[0]->rot_point.point[2] = pos->z + motion[(anime_frame * PARTS_QTY)].z;

	parts[0]->rot_point.rot[0] = rot->x + motion[(anime_frame * PARTS_QTY)].rotx;
	parts[0]->rot_point.rot[1] = rot->y + motion[(anime_frame * PARTS_QTY)].roty;
	parts[0]->rot_point.rot[2] = rot->z + motion[(anime_frame * PARTS_QTY)].rotz;

	if(anime_max > 1){
		for(i = 1; i < PARTS_QTY; i++) {
			parts[i]->Exec(motion,anime_time,anime_frame,i);
		}
	}
	else {
		for(i = 1; i < PARTS_QTY; i++) {
			parts[i]->rot_point.point[0] = motion[(anime_frame * PARTS_QTY) + i].x;
			parts[i]->rot_point.point[1] = motion[(anime_frame * PARTS_QTY) + i].y;
			parts[i]->rot_point.point[2] = motion[(anime_frame * PARTS_QTY) + i].z;

			parts[i]->rot_point.rot[0] = motion[(anime_frame * PARTS_QTY) + i].rotx;
			parts[i]->rot_point.rot[1] = motion[(anime_frame * PARTS_QTY) + i].roty;
			parts[i]->rot_point.rot[2] = motion[(anime_frame * PARTS_QTY) + i].rotz;
		}
	}

	anime_time++;
	anime_end = 0;

	if(anime_time >= motion[anime_frame * (PARTS_QTY - 1)].frame){

		anime_frame++; 
		anime_time = 0;

		if(anime_frame >= anime_max){
			anime_frame = 0;
			anime_end = 1;
		}

	}
}