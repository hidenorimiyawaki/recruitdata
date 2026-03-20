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

#define		DEBUG				// デバッグのON or OFF

#include	<agb.h>				// 任天堂AGBライブラリ

// ここで必要なヘッダーをインクルード
#include	"MultiSio.h"
#include	"define.h"			// デファイン（定数定義）
#include	"typedef.h"			// 型宣言
#include	"global.h"			// グローバル変数宣言
#include	"prototype.h"		// プロトタイプ宣言
#include	"macro.h"			// マクロ
#include	"string.h"			// 文字列表示
#include	"input.h"			// キー入力
#include	"sprite.h"			// 回転拡大縮小
#include	"Title.h"
#include	"hard_init.h"		// ハードウェア設定（関数ヘッダ）

#endif