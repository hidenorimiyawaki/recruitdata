// BillBord.h: CBillBord クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BILLBORD_H__97200D21_F6D6_443B_B7E6_742E71CD0EB0__INCLUDED_)
#define AFX_BILLBORD_H__97200D21_F6D6_443B_B7E6_742E71CD0EB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBillBord  
{
	public:
		//----- キャラクターステータス用変数
		float		x, y, z;					// 座標
		float		dx, dy, dz;					// 移動量
		float		pdx,pdy,pdz;				// 変形量(ポイント移動量)
		float		rotx, roty, rotz;			// 角度
		float		drx,dry,drz;				// 角度変更量
		int			texture_size_x;				// テクスチャファイルの横幅
		int			texture_size_y;				// テクスチャファイルの縦幅
		RECT		texRect;					// テクスチャの絵の任意座標
		int			texture_no;					// テクスチャナンバー
		D3DXMATRIX	matrix;						// 変換マトリックス
		RECT		pRect;						// テクスチャを張る板のサイズ
		int			turn;						// 裏表フラグ
		int			status;
		int			draw_flg;
		int			draw_cnt;
		int			kasan_flg;
		int			anime_cnt;
		int			anime_max;
		int			anime_frame;
		D3DXIMAGE_INFO ita;
		//----- モデル用変数
		int						num_vertex;		// 頂点数
		int						num_index;		// 面数
		LPDIRECT3DTEXTURE8		texture;		// テクスチャオブジェクト
		LPDIRECT3DVERTEXBUFFER8	vertex_buffer;	// 頂点バッファ
		VERTEX*					pVertex;		// 頂点設定時に使用するポインタ
		D3DMATERIAL8			mat;			// マテリアルの現在のカラー
		D3DMATERIAL8			defmat;			// マテリアルの初期設定カラー



		//----- モデル用関数
		CleanupGraphics();						// グラフィック関連のクリーンアップ
		SetModelData(HWND,LPDIRECT3DDEVICE8,char**);	// モデルデータセットアップ

		CBillBord();
		virtual ~CBillBord();
		
		//----- キャラクター用関数
		SetMove(float,float,float);				// キャラクタの移動
		SetPoint(float,float,float);			// キャラクタの位置設定
		SetVbuffer(LPDIRECT3DDEVICE8);			// 描画用頂点作成関数
		SetRot();								// 回転処理
		SetRotPoint(float,float,float);			// 回転用の値を設定
		Draw(LPDIRECT3DDEVICE8);				// 描画呼び出し
		SetPPoint(float,float,float);			// 変形量の設定
		Initialize(BBORD_DATA,RECT);			// 初期化呼び出し
		FrameAnimation(RECT*);					// アニメーション（フレームの時間でアニメーション）
		OffsetAnimation(RECT*);					// アニメーション（オフセットでアニメーション）
		Timer();								// 描画タイマー
		Initialize(LPDIRECT3DDEVICE8,char*);	// 初期化


};

#endif // !defined(AFX_BILLBORD_H__97200D21_F6D6_443B_B7E6_742E71CD0EB0__INCLUDED_)
