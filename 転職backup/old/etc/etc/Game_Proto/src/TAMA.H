class TAMA{
	public:
		float		dx, dy, dz;					// 移動量
		float		x, y, z;					// 座標
		float		rotx, roty, rotz;			// 角度
		float		drx,dry,drz;				// 角度変更量
		D3DXMATRIX	matrix;						// 変換マトリックス
		int			cnt;						// カウント用
		int			damage;						// 攻撃力
		int			model_no;					// モデルファイルNo
		int			texture_no;					// テクスチャファイルNo
		int			trg;						// 稼動状態判定トリガー
		int			status;						// ステータス
		int			texture_size_x;				// テクスチャサイズX
		int			texture_size_y;				// テクスチャY
		RECT		texRect;					// 
		RECT		pRect;	
		int			turn;						// 裏表フラグ
		int			kasan_flg;

	public:

		TAMA();
		SetData(TAMA_DATA,LPDIRECT3DDEVICE8);
		~TAMA();
		SetPos(float,float,float,float);
		SetMove(float,float,float);				// キャラクタの移動
		SetPoint(float,float,float);			// キャラクタの位置設定
		SetRot();								// 回転処理
		SetRotPoint(float,float,float);			// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8,BILLBORD*);				// 描画呼び出し
		Move();
};

TAMA::TAMA(){
	x = 5000;
	y = 5000;
	z = 5000;

	trg = 0;

	dx = 0;
	dy = 0;
	dz = 50;

	kasan_flg = 0;
}
TAMA::~TAMA(){
}

TAMA::SetData(TAMA_DATA Tama_Status,LPDIRECT3DDEVICE8 p_Device){

	status = Tama_Status.status;

	drx = Tama_Status.rotx;
	dry = Tama_Status.roty;
	drz = Tama_Status.rotz;
	
	texture_no = Tama_Status.texture_no;

	damage = Tama_Status.damage;

	dz = Tama_Status.speed;
	trg = 0;

}

TAMA::Draw(LPDIRECT3DDEVICE8 p_Device,BILLBORD* ita){
	ita->draw_flg = 1;
	ita->Draw(p_Device);
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
//	dx = plx;
//	dy = vy;
//	dz = vz;
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
	if(trg == 1){
		x += dx;
		y += dy;
		z += dz;
		if(z >= 5000 || z <= -4000){
			SetPoint(8000,8000,8000);
			trg = 0;
		}
	}
}