//**************************************************************************** S
//
//	 ソース名称		:	prototype.h
//	  作成者名		:	矢野 智士 （Yano Satoshi）
//
//==============================================================================
//	 コメント		:	関数プロトタイプ宣言ヘッダー
//	 最終更新日		:	  2002/10/18 (Fri)
//**************************************************************************** E

#ifndef	___PROTOTYPE_H___
#define	___PROTOTYPE_H___


// ここにプロトタイプ宣言を書く
void SetAll(void);											// 初期化

void MakeMap( const u16 *, u16, u16, u8 );					// マップデータの作成と転送
	// 無し ( 転送元アドレス, 縦最大キャラ数, 横最大キャラ数, 背景No )

u8 Action( u8, u32, const ANIME *, u16, u16, u8*, u8* );	// アニメーション処理
void Hero(void);											// プレイヤー行動処理
void Enemy (void);											// 敵の行動処理
void Battle(void);											// 命中判定処理
void Magic (void);											// 魔法処理
void Skill (void);											// スキル処理
void Special (void);										// 特殊攻撃処理
void Item (void);											// アイテム処理
void Move (void);											// 移動処理

#endif