//**************************************************************************** S
//
//	 ソース名称		:	typedef.h
//
//==============================================================================
//	 コメント		:	変数型定義（typedef)のヘッダー部
//	 最終更新日		:	  2002/10/18 (Fri)
//**************************************************************************** E

#ifndef		___TYPEDEF_H___
#define		___TYPEDEF_H___


// 型宣言があればここでする

// ======= 共通型定義 ======
typedef void (*IntrFuncp)(void);

typedef		signed short int		BOOL;	// 0か1を返すだけの変数

// --- 符号付き固定小数点数(32bit) Signed FIX ---
typedef union {
	s32 l;			// 符号付き32ビット全て(Long)
	struct{
		u16 d;		// 小数部         下位16ビット(Decimal)
		s16 i;		// 符号付き整数部 上位16ビット(Integer)
	} fix;
} SFIX;

// --- 符号無し固定小数点数(32bit) Unsigned FIX ---
typedef union{	
	u32 l;			// 符号無し32ビット全て(Long)
	struct{
		u16 d;		// 小数部         下位16ビット(Decimal)
		u16 i;		// 符号無し整数部 上位16ビット(Integer)
	} fix;
} UFIX;

// OAMバッファ型
typedef union {	// OAM 格納用の共用体
	u32		Bit32;			// アトリビュート0と1にあたる32ビット
	OamData	Oam;			// AgbTypes.h で定義されている OAM構造体

}OAM_TYPE;

// ----- SPRITE管理用構造体 -----
typedef struct {
	OamData	Oam;		// OAM構造体
	u32*	Destp;		// VRAM転送先
	s16		PosX;		// ワールド座標X
	s16		PosY;		// ワールド座標Y
	u8		Anime;		// アニメーションNo
	u8		Cnt;		// フレームカウンタ
	s16		Bottom;		// スプライトの最下部座標
	u8		Priority;	// スプライトの最下部座標
} SPRITE;

// AgbTypes.h で定義されている OAM構造体
/*
typedef struct {
    u32 VPos:8;             // Ｙ座標
    u32 AffineMode:2;       // アフィンモード
    u32 ObjMode:2;          // ＯＢＪモード
    u32 Mosaic:1;           // モザイク
    u32 ColorMode:1;        // １６色/２５６色 選択
    u32 Shape:2;            // ＯＢＪ形状

    u32 HPos:9;             // Ｘ座標
    u32 AffineParamNo_L:3;  // アフィン変換パラメータＮｏ 下位３ビット
    u32 HFlip:1;            // Ｈフリップ
    u32 VFlip:1;            // Ｖフリップ
    u32 Size:2;             // ＯＢＪサイズ

    u16 CharNo:10;          // キャラクタＮｏ
    u16 Priority:2;         // 表示優先
    u16 Pltt:4;             // パレットＮｏ
    u16 AffineParam;        // アフィン変換パラメータ
} OamData;
*/

// ------- アニメーションデータ型 -------
typedef struct {
	const u8	*Char;		// キャラクターデータ
	u8			Size;		// スプライトのサイズ
	u8			Frame;		// 表示されるフレーム数
	s8			Hofs;		// H オフセット
	s8			Vofs;		// V オフセット
	u8			Hit;		// やられ範囲の指定（別テーブルデータの要素数）
	u8			Atk;		// 攻撃範囲の指定（別テーブルデータの要素数）
	u8			Dam;		// 攻撃力
	u8			Type;		// その他特殊状態（ふっとばし等）
} ANIME;

// ------- 当たり判定型 -------
typedef struct {
	s8	x;		// 始点のX座標
	s8	y;		// 始点のY座標
	u8	wid;	// 横の長さ
	u8	hei;	// 縦の長さ
} HIT_TYPE;

// ------- 魔法型 -------
typedef struct {
	s32			x;				// X座標
	s32			y;				// Y座標
	u8			anime;			// 魔法 アニメーションのカウンタ
	u8			cnt;			// フレームのカウンタ
	u8			status : 4;		// 魔法の発動状態
	u8			flg    : 1;		// 有無のフラグ （ONかOFF)
	u8			turn   : 3;		// 向き（8方向:3bit)
} MAGIC_EFFECT;

// ------- アイテム型 -------
typedef struct {
	s32			x;			// X座標
	s32			y;			// Y座標
	u8			anime;		// アイテム アニメーションのカウンタ
	u8			cnt;		// フレームのカウンタ
	u8			flg;		// アイテム出現許可フラグ
	u8			get;		// 消えるまでのカウント（仮＝未承諾)
} ITEM;

// ------- プレイヤーステータス -------
typedef struct {
	s32	x;				// X座標:符号有り固定小数点型(16-16)
	s32	y;				// Y座標:符号有り固定小数点型(16-16)
	s16	localX;			// ローカルX座標
	s16	localY;			// ローカルY座標
	s16	hp      :12;	// ヒットポイント（-2048～2047）
	s8	sp;				// スキルポイント（-128～127）
	s8	coin;			// 取得コイン枚数（-128～127）
	u8	turn    : 2;	// 向き（4方向:2bit)
	u8	type    : 4;	// 現在の行動状態（16種類:4bit)
	u8	anime;			// アニメーションのカウンタ（0～15)
	u8	cnt;			// フレームのカウンタ
	u16	keep    :10;	// ボタン押し時間の制御（0～1023)
	u8	skillflg: 1;	// スキル発動フラグ（ON,OFF)
	u8	spflg   : 1;	// 必殺技発動フラグ（ON,OFF)
	u8	atk     : 2;	// 連続攻撃の状態を格納（4パターン:2bit)
	u8	effect  : 1;	// エフェクトフラグ（ON,OFF)
	s8	invincible;		// 無敵時間のカウンタ
	s8	dead;			// 死亡時間のカウンタ
	u8	name    : 3;	// プレイヤーキャラクターネーム(最大8種類)
	u8	coloer  : 4;	// 使用パレット（16色:4bit)
} PLAYER;

// ------- エネミーステータス -------
typedef struct {
	s32	x;				// X座標:符号有り固定小数点型(16-16)
	s32	y;				// Y座標:符号有り固定小数点型(16-16)
	s16	hp    :12;		// ヒットポイント（-2048～2047）
	u8	turn  : 2;		// 向き（4方向:2bit)
	u8	type  : 4;		// 現在の行動状態（16種類:4bit)
	u8	anime ;			// アニメーションのカウンタ
	u8	cnt;			// フレームのカウンタ
	u8	hit   : 4;		// 被弾フラグ（各1bitが各プレイヤーに対応)
	u8	name  : 5;		// 敵キャラクターネーム
	u8	coloer: 4;		// 使用パレット（16色:4bit)
	u8	count;			// 敵の攻撃間隔用カウンタ（0～255)
	u8	effect: 1; 		// エフェクトフラグ
} ENEMY;

// ------- エフェクトステータス -------
typedef struct {
	s32	x;			// X座標:符号有り固定小数点型(16-16)
	s32	y;			// Y座標:符号有り固定小数点型(16-16)
	u8	anime;		// アニメーションのカウンタ
	u8	cnt;		// フレームのカウンタ
} EFFECT;

// ------- ボスステータス -------
typedef struct {
	s32	x;			// X座標:符号有り固定小数点型(16-16)
	s32	y;			// Y座標:符号有り固定小数点型(16-16)
	s16	hp;			// ヒットポイント（0～8267）
	u8	turn;		// 向き（4方向:2bit)
	u8	type;		// その他の状態
	u8	anime;		// アニメーションのカウンタ
	u8	cnt;		// フレームのカウンタ
} BOSS;

#endif