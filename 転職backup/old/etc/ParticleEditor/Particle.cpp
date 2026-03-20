#include "StdAfx.h"
#include ".\particle.h"
#include "test.h"

CParticle::CParticle(void)
{
	status = 0;
	x = y = z = 0;
	dx = dy = dz = 0;
	drx = dry = drz = 0;
	rotx = roty = rotz = 0;
	rangex = rangey = rangez = 0;
	sclx = scly = sclz = 1;

	alpha = 1.0f;

	trg = 0;
	effect_flg = 0;
	effect_cnt = 0;

	move_max = 70;
	move = 0;

	gravity = 0;

	scale = 1.0f;

	speed = 1.0f;
	time = 0;

	radius = 0;

	dir = 0;
}

CParticle::~CParticle(void)
{
}

CParticle::Draw(LPDIRECT3DDEVICE8 p_Device,CBillbord* ita){

	ita->draw_flg = 1;
	ita->SetMatrix(matrix);
	ita->SetAlpha(alpha);
	ita->SetRotPoint(rotx*0.01f,roty*0.01f,rotz*0.01f);
	ita->SetScaleXYZ(sclx,scly,sclz);
	ita->SetScale(scale);
	ita->Draw(p_Device);
	ita->draw_flg = 0;
}

CParticle::Update(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matScale,matScale2;								// 拡縮マトリックス
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);						// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);						// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);						// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);					// 平行移動マトリックスを生成
	D3DXMatrixScaling(&matScale,scale,scale,scale);
	D3DXMatrixScaling(&matScale2,sclx,scly,sclz);
	matrix = matTrans * matRotateX * matRotateY * matRotateZ;// * matScale * matScale2;
}

CParticle::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}

CParticle::SetPos(float plx,float ply,float enx,float eny){
}


CParticle::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx = vrotx;
	roty = vroty;
	rotz = vrotz;
}

CParticle::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;
}

CParticle::Move(){
	POSITION3 work;

	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	if(pApp->rotflg.x){
		// 円筒座標系
		if(!pApp->rotflg.z) {
			x = radius*cos(drx)*speed+posx;
			y += pApp->pos.y*0.01f*speed;
			z = radius*sin(drx)*speed+posz;
			dy -= gravity*0.1f*4.9f*speed;			// 重力加速値
			effect_cnt--;
			drx += (360)/time;

			radius += pApp->rot.w/time;

			if(drx >= 360){
				drx = 0;
			}

			if(pApp->EditDialog.m_Check_Time_Alpha.GetCheck()){
				alpha -= 1.0f/(float)time;
				if(alpha <= 0) alpha = 0;
			}
			else alpha = 1.0f;

		}
		else {
			// 原点を元に計算する場合
			x = radius*cos(drx)*speed+posx;
			y += pApp->pos.y*0.01f*speed;
			z = radius*sin(drx)*speed+posz;
			dy -= gravity*0.1f*4.9f*speed;			// 重力加速値
			effect_cnt--;
			drx += (360)/time;

			if(drx >= 360){
				drx = 0;
			}

			if(pApp->EditDialog.m_Check_Time_Alpha.GetCheck()){
				alpha -= 1.0f/(float)time;
				if(alpha <= 0) alpha = 0;
			}
			else alpha = 1.0f;

		}

		if(effect_cnt <= 0){
			work.x = pApp->EditDialog.m_Edit_Pos_X;
			work.y = pApp->EditDialog.m_Edit_Pos_Y;
			work.z = pApp->EditDialog.m_Edit_Pos_Z;
			EffectSet(&work);
			speed = pApp->pos.w*0.01f;
			gravity = pApp->gravity;
			x = radius*cos(drx)*speed+posx;
			y += pApp->pos.y*0.01f*speed;
			z = radius*sin(drx)*speed+posz;
			alpha = 1.0f;
		}
	}
	else if(pApp->rotflg.y){
		// 極座標系
		x = radius*cos(drx)*cos(dir)*speed+posx;
		y = radius*sin(dir)*speed+posy;
		z = radius*sin(drx)*cos(dir)*speed+posz;
		dy -= gravity*0.1f*4.9f*speed;			// 重力加速値
		effect_cnt--;
		drx += (360)/time;
		dir -= (pApp->dir)/time;

		if(drx >= 360){
			drx = 0;
		}
		if(dir <= 0){
			dir = 0;
		}

		if(pApp->EditDialog.m_Check_Time_Alpha.GetCheck()){
			alpha -= 1.0f/(float)time;
			if(alpha <= 0) alpha = 0;
		}
		else alpha = 1.0f;

		if(effect_cnt <= 0){
			work.x = pApp->EditDialog.m_Edit_Pos_X;
			work.y = pApp->EditDialog.m_Edit_Pos_Y;
			work.z = pApp->EditDialog.m_Edit_Pos_Z;
			EffectSet(&work);
			radius = pApp->rot.w;
			speed = pApp->pos.w*0.01f;
			gravity = pApp->gravity;
			x = radius*cos(drx)*cos(dir)+posx;
			y = radius*sin(dir)+posy;
			z = radius*sin(drx)*cos(dir)+posz;
			alpha = 1.0f;
		}
	}
	else {
		x += dx*speed;
		y += dy*speed;
		z += dz*speed;
		dy -= gravity*0.1f*4.9f*speed;			// 重力加速値
		effect_cnt--;
		
		if(pApp->EditDialog.m_Check_Time_Alpha.GetCheck()){
			alpha -= 1.0f/(float)time;
			if(alpha <= 0) alpha = 0;
		}
		else alpha = 1.0f;

		if(effect_cnt <= 0){
			work.x = pApp->EditDialog.m_Edit_Pos_X;
			work.y = pApp->EditDialog.m_Edit_Pos_Y;
			work.z = pApp->EditDialog.m_Edit_Pos_Z;
			EffectSet(&work);
			speed = pApp->pos.w*0.01f;
			gravity = pApp->gravity;
			alpha = 1.0f;
		}
	}



	if(pApp->scaleflg.x){
		sclx += pApp->scale.x/(float)time;
	}
	else sclx = pApp->scale.x;

	if(pApp->scaleflg.y){
		scly += pApp->scale.y/(float)time;
	}
	else scly = pApp->scale.y;

	if(pApp->scaleflg.z){
		sclz += pApp->scale.z/(float)time;
	}
	else sclz = pApp->scale.z;


}
CParticle::EffectSet(POSITION3* pPos){

	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	float wk;
	int wk2;


	// 初期化
	x = pPos->x;
//	x -= (pApp->direct_x.texrect.right/2);
	if((int)rangex == 0){
		x += 0;
	}
	else if(rangex > 0){
		wk2 = (int)(pApp->EditDialog.m_Edit_Slider_Range_X.GetPos()*0.01f);
		wk = pApp->EditDialog.m_Edit_Slider_Range_X.GetPos()*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0 || wk < 0 )x += (rand() % (int)wk)*0.01f;
		if(wk2 > 0 || wk2 < 0 )x += (rand() % wk2);
	}
	else {
		wk2 = (int)((pApp->EditDialog.m_Edit_Slider_Range_X.GetPos()*-1)*0.01f);
		wk = (pApp->EditDialog.m_Edit_Slider_Range_X.GetPos()*-1)*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0 || wk < 0 )x += (rand() % (int)wk)*0.01f*-1;
		if(wk2 > 0 || wk2 < 0 )x += (rand() % wk2)*-1;
	}
	y = pPos->y;
//	y -= (pApp->direct_x.texrect.bottom/2);
	if((int)rangey == 0){
	}
	else if(rangey > 0){
		wk2 = (int)(pApp->EditDialog.m_Edit_Slider_Range_Y.GetPos()*0.01f);
		wk = pApp->EditDialog.m_Edit_Slider_Range_Y.GetPos()*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0 || wk < 0 )y += (rand() % (int)wk)*0.01f;
		if(wk2 > 0 || wk2 < 0 )y += (rand() % wk2);
	}
	else {
		wk2 = (int)((pApp->EditDialog.m_Edit_Slider_Range_Y.GetPos()*-1)*0.01f);
		wk = (pApp->EditDialog.m_Edit_Slider_Range_Y.GetPos()*-1)*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0 || wk < 0 )y += (rand() % (int)wk)*0.01f*-1;
		if(wk2 > 0 || wk2 < 0 )y += (rand() % wk2)*-1;
	}

	z = pPos->z;
	if((int)rangez == 0){
	}
	else if(rangez > 0){
		wk2 = (int)(pApp->EditDialog.m_Edit_Slider_Range_Z.GetPos()*0.01f);
		wk = pApp->EditDialog.m_Edit_Slider_Range_Z.GetPos()*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0 || wk < 0 )z += (rand() % (int)wk)*0.01f;
		if(wk2 > 0 || wk2 < 0 )z += (rand() % wk2);
	}
	else {
		wk2 = (int)((pApp->EditDialog.m_Edit_Slider_Range_Z.GetPos()*-1)*0.01f);
		wk = (pApp->EditDialog.m_Edit_Slider_Range_Z.GetPos()*-1)*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0 || wk < 0 )z += (rand() % (int)wk)*0.01f*-1;
		if(wk2 > 0 || wk2 < 0 )z += (rand() % wk2)*-1;
	}



	// 飛び出す方向を乱数で決める
	if(pApp->pos.x== 0)dx = 0;
	else if(pApp->pos.x > 0){
		wk2 = (int)(pApp->pos.x*0.01f);
		wk = pApp->pos.x*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0.0f || wk < 0.0f ){
			dx = (rand() % (int)wk)*0.01f;
			if(wk2 > 0.0f || wk2 < 0.0f )dx += (rand() % wk2);
		}
		else {
			if(wk2 > 0.0f || wk2 < 0.0f )dx = (float)(rand() % wk2);
		}
		if(pApp->EditDialog.m_Check_Side_X.GetCheck() == (int)true){
			if((rand()%2) == 1) dx *= -1;
		}
	}
	else {
		wk2 = (int)((pApp->pos.x*-1)*0.01f);
		wk = (pApp->pos.x*-1)*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0.0f || wk < 0.0f ){
			dx = (rand() % (int)wk)*0.01f;
			if(wk2 > 0.0f || wk2 < 0.0f )dx += (rand() % wk2)*-1;
		}
		else {
			if(wk2 > 0.0f || wk2 < 0.0f )dx = (float)(rand() % wk2)*-1;
		}
		if(pApp->EditDialog.m_Check_Side_X.GetCheck() == (int)true){
			if((rand()%2) == 1) dx *= -1;
		}
	}

	if(pApp->pos.y == 0)dy = 0;
	else if(pApp->pos.y > 0){
		wk2 = (int)(pApp->pos.y*0.01f);
		wk = pApp->pos.y*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0.0f || wk < 0.0f ){
			dy = (rand() % (int)wk)*0.01f;
			if(wk2 > 0.0f || wk2 < 0.0f )dy += (rand() % wk2);
		}
		else {
			if(wk2 > 0.0f || wk2 < 0.0f )dy = (float)(rand() % wk2);
		}
		if(pApp->EditDialog.m_Check_Side_Y.GetCheck() == (int)true){
			if((rand()%2) == 1) dy *= -1;
		}
	}
	else {
		wk2 = (int)((pApp->pos.y*-1)*0.01f);
		wk = (pApp->pos.y*-1)*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0.0f || wk < 0.0f ){
			dy = (rand() % (int)wk)*0.01f*-1;
			if(wk2 > 0.0f || wk2 < 0.0f )dy += (rand() % wk2)*-1;
		}
		else {
			if(wk2 > 0.0f || wk2 < 0.0f )dy = (float)(rand() % wk2)*-1;
		}
		if(pApp->EditDialog.m_Check_Side_Y.GetCheck() == (int)true){
			if((rand()%2) == 1) dy *= -1;
		}
	}

	if(pApp->pos.z == 0)dz = 0;
	else if(pApp->pos.z > 0){
		wk2 = (int)(pApp->pos.z*0.01f);
		wk = pApp->pos.z*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0.0f || wk < 0.0f ){
			dz = (rand() % (int)wk)*0.01f;
			if(wk2 > 0.0f || wk2 < 0.0f )dz += (rand() % wk2);
		}
		else {
			if(wk2 > 0.0f || wk2 < 0.0f )dz = (float)(rand() % wk2);
		}
		if(pApp->EditDialog.m_Check_Side_Z.GetCheck() == (int)true){
			if((rand()%2) == 1) dz *= -1;
		}
	}
	else {
		wk2 = (int)((pApp->pos.z*-1)*0.01f);
		wk = (pApp->pos.z*-1)*0.01f;
		wk -= wk2;
		wk *= 100;
		if(wk > 0.0f || wk < 0.0f ){
			dz = (rand() % (int)wk)*0.01f*-1;
			if(wk2 > 0.0f || wk2 < 0.0f )dz += (rand() % wk2)*-1;
		}
		else {
			if(wk2 > 0.0f || wk2 < 0.0f )dz = (float)(rand() % wk2)*-1;
		}
		if(pApp->EditDialog.m_Check_Side_Z.GetCheck() == (int)true){
			if((rand()%2) == 1) dz *= -1;
		}
	}


	if(pApp->EditDialog.m_Check_Size.GetCheck()){
		wk2 = (int)(pApp->EditDialog.m_Edit_Scale);
		wk = pApp->EditDialog.m_Edit_Scale+1;
		wk -= wk2;
		wk *= 100.0f;
		if((int)wk != 0 ){
			scale = (rand() % (int)wk)*0.01f;
			if(wk2 != 0.0f )scale += (rand() % wk2);
		}
		else {
			if(wk2 > 0.0f || wk2 < 0.0f )scale = (rand() % wk2);
		}
	}
	else {
		scale = pApp->EditDialog.m_Edit_Scale;
	}

	if(pApp->EditDialog.m_Check_Time.GetCheck()) {

		effect_cnt = rand() % (int)pApp->EditDialog.m_Edit_Time;
		if(effect_cnt <= 0) effect_cnt = 1;
	}
	else {
		effect_cnt = pApp->EditDialog.m_Edit_Time;
	}

	posx = x;
	posy = y;
	posz = z;

	trg = 1;

	time = pApp->EditDialog.m_Edit_Time;

	gravity = pApp->gravity;

	SetRotPoint(pApp->rot.x,pApp->rot.y,pApp->rot.z);

	if(pApp->rotflg.z) radius = pApp->rot.w;
	else radius = 0;
			
	drx = 0;
	dry = 0;
	drz = 0;
	
	if(pApp->dir != 0) {
#if 0
		do{
			dir = (float)(rand() / (int)(pApp->dir));
		}while(dir == 0);
#else
		dir = (float)(rand() / (int)(pApp->dir));
#endif
	}
	else dir = 0;

	alpha = 1.0f;


	if(pApp->scaleflg.x){
		sclx = 0;
	}
	else sclx = pApp->scale.x;

	if(pApp->scaleflg.y){
		scly = 0;
	}
	else scly = pApp->scale.y;

	if(pApp->scaleflg.z){
		sclz = 0;
	}
	else sclz = pApp->scale.z;


}
