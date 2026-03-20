//**************************************************************************** S
//
//	 ソース名称		:	all.h
//
//==============================================================================
//	 コメント		:	全てのヘッダーファイルのインクルードヘッダー
//	 最終更新日		:	2002/10/27 (Sun)
//**************************************************************************** E

#ifndef	___ALL_H___
#define	___ALL_H___

#define		DEBUGING			// デバッグのON or OFF

#include	<agb.h>				// 任天堂AGBライブラリ

// ここで必要なヘッダーをインクルード
#include	"MultiSio.h"		// 通信関連

#include	"Define.h"			// デファイン（定数定義）
#include	"Typedef.h"			// 型宣言
#include	"Global.h"			// グローバル変数宣言
#include	"Prototype.h"		// 関数プロトタイプ宣言
#include	"Macro.h"			// マクロ定義


#include	"String.h"			// 文字列表示
#include	"Input.h"			// キー入力
#include	"Sprite.h"			// スプライト処理
#include	"Title.h"			// タイトル
#include	"hard_init.h"		// ハードウェア設定

#include	"Position.h"
#include	"Hero.h"			// キャラクターの行動処理
#include	"Move.h"			// キャラクターの移動処理
#include	"Jump.h"			// キャラクターのジャンプ移動処理
#include	"Attack.h"			// キャラクターの攻撃行動処理
#include	"Magic.h"			// キャラクターの魔法攻撃行動処理

#endif