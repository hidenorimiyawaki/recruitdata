#include "StdAfx.h"
#include ".\particle.h"
#include "particleediter.h"

CParticle::CParticle(void)
{
	status = 0;
	x = y = z = 0;
	dx = dy = dz = 0;

	rotx = roty = rotz = 0;
	drx = 0;
	dry = 0;
	drz = 0;
	
	damage = 20;

	dx = dy = 0;
	dz = 1;

	trg = 0;
	effect_flg = 0;
	effect_cnt = 0;

	move_max = 70;
	move = 0;

	gravity = 0;

	scale = 1.0f;
}

CParticle::~CParticle(void)
{
}

CParticle::Draw(LPDIRECT3DDEVICE8 p_Device,CBillbord* ita){

	ita->draw_flg = 1;
	ita->SetMatrix(matrix);
	ita->Draw(p_Device);
	ita->draw_flg = 0;
}

CParticle::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matScale;								// 拡縮マトリックス
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);					// 平行移動マトリックスを生成
	D3DXMatrixScaling(&matScale,scale,scale,scale);
	matrix = matRotateX * matRotateY * matRotateZ * matScale * matTrans;	// マトリックスを合成（順序に注意！）

}

CParticle::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}

CParticle::SetPos(float plx,float ply,float enx,float eny){
}


CParticle::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}

CParticle::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;
}

CParticle::Move(){
	POSITION3 work;

	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);

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
		dy -= (gravity);			// 重力加速値
		effect_cnt--;
//		scale = pApp->EditDialog.m_Edit_Scale;
		if(effect_cnt <= 0){
			SetPoint(0,0,0);
			work.x = pApp->EditDialog.m_Edit_Pos_X;
			work.y = pApp->EditDialog.m_Edit_Pos_Y;
			work.z = pApp->EditDialog.m_Edit_Pos_Z;
			EffectSet(&work);
			//trg = 0;
		}
	}



}
CParticle::EffectSet(POSITION3* pPos){

	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// 初期化
	x = pPos->x;
	y = pPos->y;
	z = pPos->z;

	// 飛び出す方向を乱数で決める
	if(pApp->EditDialog.m_Edit_Dir_X == 0)dx = 0;
	else {
		dx = (float)(rand() % pApp->EditDialog.m_Edit_Dir_X);
		if((rand()%2) == 1) dx *= -1;	
	}
	if(pApp->EditDialog.m_Edit_Dir_Y == 0)dy = 0;
	else {
		dy = (float)(rand() % pApp->EditDialog.m_Edit_Dir_Y);
		if((rand()%2) == 1) dy *= -1;	
	}

	if(pApp->EditDialog.m_Edit_Dir_Z == 0)dz = 0;
	else {
		dz = (float)(rand() % pApp->EditDialog.m_Edit_Dir_Z);
		if((rand()%2) == 1) dz *= -1;
	}
	trg = 1;
	effect_cnt = pApp->EditDialog.m_Edit_Time;
	effect_flg = 1;
}
