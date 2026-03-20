/************************************************************
*						PLAYER.H							*
*															*
*	このファイルでは、プレイヤークラスの定義をします。		*
*															*
*				作成日：2003/09/17							*
*			最終更新日：2003/09/19							*
*															*
************************************************************/


class PLAYER{
	public:
//----- キャラクターステータス用変数
		float		dx, dy, dz;					// 移動量
		float		cmx,cmy,cmz;				// カメラ用
		int			tama_max;					// 撃てる弾の最大数
		int			power;						// パワーアップ等の追加状態用
		int			hp;							// キャラクターのヒットポイント
		int			hp_max;						// ヒットポイントの最大値
		int			bp;							// キャラクターのバリア出力時間
		int			bp_max;						// バリアポイントの最大出力時間
		int			key_trg;					// キーのトリガー状態
		int			key_cnt;					// キーの発射間隔
		int			barrier_flg;				// バリアの稼動許可フラグ
		int			barrier_trg;				// バリアの稼動中フラグ
		int			hyper_point;				// ハイパーゲージポイント
		int			hyper_max;					// ハイパーゲージの最大値
		int			hyper_flg;					// ハイパー攻撃フラグ
		int			hit;						// ヒット状態フラグ
		int			death_cnt;
		int			effect_cnt;
		float		ef_move;
		float		x, y, z;					// 座標
		float		rotx, roty, rotz;			// 角度
		float		drx,dry,drz;				// 角度変更量
		D3DXMATRIX	matrix;						// 変換マトリックス
		int			death;
		int			change;
		float		enemy_x,enemy_y,enemy_z;
		float		range_max_x,range_max_y;
		float		range_min_x,range_min_y;
		int			target_trg;
		BILLBORD	effect[5];			// エフェクト用ビルボード（ダメージ用＊４＋爆発＊１）


		//----- モデル用変数
		LPD3DXMESH				mesh;			// メッシュオブジェクト
		int						num_vertex;		// 頂点数
		int						num_index;		// 面数
		LPDIRECT3DVERTEXBUFFER8	vertex_buffer;	// 頂点バッファ
		LPDIRECT3DINDEXBUFFER8	index_buffer;	// インデックスバッファ
		LPDIRECT3DTEXTURE8		texture;		// テクスチャオブジェクト
		D3DMATERIAL8			material;
		DWORD					num_material;

		LPDIRECT3DTEXTURE8*		ppTexture;
		D3DMATERIAL8*			pMaterial;
		DWORD					meshSubsets;
		LPD3DXMESH				pMesh;
		LPD3DXBUFFER			pMatBuf;
		D3DXMATERIAL*			pMat;
		DWORD					i,n;

	public:

		//----- モデル用関数
		CleanupGraphics();						// グラフィック関連のクリーンアップ
		SetModelData(HWND,LPDIRECT3DDEVICE8,char**,char**);	// モデルデータセットアップ

//----- キャラクター用関数
		PLAYER();								// コンストラクタ(標準）
		~PLAYER();								// デストラクタ
		GetKey(TAMA*);							// キー入力判定
		SetMove(float,float,float);				// キャラクタの移動
		SetPoint(float,float,float);			// キャラクタの位置設定
		SetHp(int);								// 現在の状態によるヒットポイントの設定
		SetRot();								// 回転処理
		SetRotPoint(float,float,float);			// 回転用の値を設定
		Attack(TAMA*);							// 攻撃処理
		Draw(LPDIRECT3DDEVICE8);				// 描画呼び出し
		GetEnemyPos(float,float,float);			// 敵座標取得
		Barrier();								// バリア呼び出し
		SetEffect();							// エフェクト呼び出し
		Initialize();							// 初期化呼び出し
};

//----- 内容定義
PLAYER::PLAYER(){
	CleanupGraphics();
	for(i = 0; i <= 4; i++){
		effect[i].CleanupGraphics();
	}
}

PLAYER::Initialize(){
	x = 0;
	y = 0;
	z = -500;

	range_max_x = PLAYER_RANGE_X;
	range_max_y = PLAYER_RANGE_Y;

	range_min_x = range_max_x * -1;
	range_min_y = range_max_y * -1;
	
	dx = dy = dz = PLAYER_MOVE;

	drx = dry = drz = (float)0.3;

	rotx = roty = rotz = (float)0.0;

	hp = hp_max = 200;

	bp = bp_max = 123;

	hyper_point = 0;

	hyper_max = 100;

	tama_max = 7;

	key_trg = key_cnt = 0;
	cmx = cmy = cmz = 0;

	death = 0;

	change = 0;

	num_material = 0L;

	pMatBuf = NULL;

	enemy_x = enemy_y = 0;

	target_trg = 0;

	barrier_flg = 0;

	barrier_trg = 0;

	hit = 0;

	ef_move = EF_OFFSET;

	effect_cnt = 20;

	death_cnt = 20;

	hyper_flg = 0;

}
PLAYER::~PLAYER(){
	CleanupGraphics();
}
PLAYER::SetModelData(HWND hwnd,LPDIRECT3DDEVICE8 p_Device,char** file_name, char** texture_name){


    // Ｘファイルからメッシュデータを読み込む

	D3DXLoadMeshFromX(file_name[1], D3DXMESH_MANAGED, p_Device, NULL,&pMatBuf,&n,&pMesh);

	mesh = pMesh;

	meshSubsets = n;

	//マテリアルとテクスチャの設定
	pMat = (D3DXMATERIAL*)pMatBuf->GetBufferPointer();
	ppTexture = new LPDIRECT3DTEXTURE8[n];
	pMaterial = new D3DMATERIAL8[n];

	for(i=0;i<n;i++){
		pMaterial[i] = pMat[i].MatD3D;
		ppTexture[i] = NULL;
		//テクスチャ読み込み
		if(pMat[i].pTextureFilename)
			D3DXCreateTextureFromFile(p_Device,pMat[i].pTextureFilename,&ppTexture[i]);
	}

	SAFE_RELEASE(pMatBuf);

}
PLAYER::CleanupGraphics(){	
	SAFE_RELEASE(texture);	// テクスチャオブジェクトを解放
	SAFE_RELEASE(mesh);		// メッシュオブジェクトを解放
	vertex_buffer = NULL;	// 頂点バッファ
	index_buffer = NULL;	// インデックスバッファ
}
PLAYER::GetKey(TAMA* Player_Tama){
	int i;

	if(death == 0){
		if(GetAsyncKeyState(VK_UP	) & 0x8000 || KEY_PUSH_UP(0)) SetMove(  0, dy,  0);
		if(GetAsyncKeyState(VK_DOWN	) & 0x8000 || KEY_PUSH_DOWN(0)) SetMove(  0,-dy,  0);
		if(GetAsyncKeyState(VK_LEFT	) & 0x8000 || KEY_PUSH_LEFT(0)) SetMove(-dx,  0,  0);
		if(GetAsyncKeyState(VK_RIGHT) & 0x8000 || KEY_PUSH_RIGHT(0)) SetMove( dx,  0,  0);

		if(key_trg == 0 && key_cnt == 0){ 
			for(i = 0; i <= tama_max; i++){
				if(Player_Tama->trg == 0){
					if(GetAsyncKeyState('Z') & 0x8000 || KEY_PUSH_A(0)) Attack(Player_Tama);
					key_cnt = 5;
					key_trg = 1;
					i = tama_max;
					target_trg = 0;
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

}
PLAYER::SetMove(float px,float py,float pz){
	x += px;
	y += py;
	z += pz;

	cmx += px  / 2;

	if(x <= -800){
		x += px * -1;
		cmx += px / 2* -1;
	}

	if(x >= 800){
		x += px * -1;
		cmx += px / 2* -1;
	}


	if(y <= -340){
		y += py * -1;
	}

	if(y >= 480){
		y += py * -1;
	}


}
PLAYER::SetHp(int damage){
	hp = hp - damage;
	if(hp <= 0 ) {
		death = 1;
		hp = 0;
	}
}

PLAYER::GetEnemyPos(float enx,float eny,float enz){

	if(enemy_z > z + 20){
		if(enemy_x <= enx && enemy_y <= eny && enemy_x + 50 >= enx && enemy_y + 50 >= eny){
			enemy_x = enx;
			enemy_y = eny;
			enemy_z = enz;
		}
	}

	if(enemy_x - x >= range_max_x){
		enemy_x = x - range_max_x;
		target_trg = 0;
	}
	else if(enemy_x - x <= range_min_x){
		enemy_x = x + range_min_x;
		target_trg = 0;
	}
	if(enemy_y - y >= range_max_y){
		enemy_y = y - range_max_y;
		target_trg = 0;
	}
	else if(enemy_y - y <= range_min_y){
		enemy_y = y + range_min_y;
		target_trg = 0;
	}

}
PLAYER::Attack(TAMA* Player_Tama){
	float wk;

	if(death == 0){
		Player_Tama->SetPoint(x-16,y,z);

		if(target_trg == 1){
			wk = (z - enemy_z) / Player_Tama->dz;

			Player_Tama->dx = (x - enemy_x) / wk;
			Player_Tama->dy = (y - enemy_y) / wk; 
			Player_Tama->trg = 1;
		}
		else{
			Player_Tama->trg = 1;
			Player_Tama->dx = 0;
			Player_Tama->dy = 0;
		}
	}
}
PLAYER::Barrier(){

	if((GetAsyncKeyState('X') & 0x8000 || KEY_PUSH_B(0)) && barrier_trg == 0) barrier_flg = 1;
	else if(!(GetAsyncKeyState('X') & 0x8000 || KEY_PUSH_B(0))) barrier_flg = 0;

	if(barrier_flg == 1) {
		bp--;
		if(bp <= 0 - 1){
			barrier_flg = 0;
			barrier_trg = 1;
			bp = 0;
		}
	}
	else if(barrier_flg == 0 ) {
		bp++;
		if(bp >= bp_max + 1){
			bp = bp_max;
			if(barrier_trg == 1) barrier_trg = 0;
		}
	}
}
PLAYER::SetRot(){
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;		// 回転マトリックス（３種）
	D3DXMATRIX	matTrans;								// 平行移動マトリックス

	D3DXMatrixRotationX(&matRotateX, rotx);							// Ｘ軸回転マトリックスを生成
	D3DXMatrixRotationY(&matRotateY, roty);							// Ｙ軸回転マトリックスを生成
	D3DXMatrixRotationZ(&matRotateZ, rotz);							// Ｚ軸回転マトリックスを生成
	D3DXMatrixTranslation(&matTrans, x, y, z);						// 平行移動マトリックスを生成
	matrix = matRotateX * matRotateY * matRotateZ * matTrans;		// マトリックスを合成（順序に注意！）

}
PLAYER::SetPoint(float vx,float vy,float vz){
	x = vx;
	y = vy;
	z = vz;
}

PLAYER::SetRotPoint(float vrotx,float vroty,float vrotz){
	rotx += vrotx;
	roty += vroty;
	rotz += vrotz;
}
PLAYER::Draw(LPDIRECT3DDEVICE8 p_Device){
	p_Device->SetTransform(D3DTS_WORLD, &matrix);					// ワールドマトリクスをセット

	for(int i=0;i < (int)meshSubsets;i++){
		p_Device->SetMaterial(&pMaterial[i]);
		p_Device->SetTexture(0,ppTexture[i]);
		mesh->DrawSubset(i);
	}
}
PLAYER::SetEffect(){

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

	if(hp <= 0){
		effect[4].draw_flg = 1;
		effect[4].SetPoint(x - 180,y - 140,z - 120);
		death_cnt--;
		if(death_cnt <= 0){
			death_cnt = 0;
		}
	}	

}