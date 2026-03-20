//**************************************************************************** S
//
//	 ヘッダー名称	:	string.h
//
//==============================================================================
//	 コメント		:	string.cの為の関数ヘッダー（マクロ付き）
//	 最終更新日		:	2002/11/16 (Sat)
//**************************************************************************** E

#ifndef		___STRING_H___
#define		___STRING_H___

// ------ 定数定義 ------
#define		FONT_TOP_ADDRESS		0x0380	// フォントキャラクターデータの先頭アドレス
#define 	BG_SC_DATA_SIZE			2		// BGスクリーンデータのサイズ（2Byte)
#define		JIS_SPACE_ADDRESS		0x20	// JISコード' 'のアドレス
#define		JIS_NUM_ADDRESS			0x30	// JISコード'0'のアドレス
#define		JIS_ALPHA_ADDRESS		0x41	// JISコード'A'のアドレス


// ------ プロトタイプ宣言部 ------
u8	ObjStringPrint( u8 *, u8, u8, u8 );				// OBJでの文字列表示
	// 終端のX座標 ( 文字列, y座標, x座標, パレット )

u8	ObjNumPrint( u32, u8, u8, u8, u8, u8 );			// OBJでの変数表示
	// 終端のX座標 ( 表示対象, y座標, x座標, 基数, 変数サイズ )

u8	BgStringPrint( u8 *, u8, u8, u8, u8 );			// BGでの文字列表示
	// 表示文字数 ( 文字列, y座標, x座標, パレット, BGNo )

u8	BgNumPrint( u32, u8, u8, u8, u8, u8, u8 );		// BGでの変数表示
	// 表示文字数 ( 表示対象, y座標, x座標, パレット, 基数, 変数サイズ, BGNo )
void ObjKeyPrint( vu16, u8, u8, u8 );
void BgKeyPrint(  vu16 , u8, u8, u8, u8 );


//**************************************************************************** S
//	 マクロ名	:	ObjNumberPrint
//	   機能		:	符号付の変数内容をスプライトで描画
//	  引数 1	:	表示対象変数（数値）
//	  引数 2	:	縦表示位置（0～255）
//	  引数 3	:	横表示位置（0～255）
//	  引数 4	:	パレットNo（0～15)
//	  引数 5	:	表示形式（DEX:10進数 HEX:16進数）
//	  戻り値	:	無し
//	 主要変数	:	無し
//==============================================================================
//	 コメント	:	±を自動判別しくれるのでObjNumPrintよりこちらを推奨
//  最終更新日	:	2002/11/16 (Sat)
//**************************************************************************** E
#define	ObjNumberPrint( num, y, x, pltt, type )											\
{																						\
	u8	offset;																			\
	if ( num >= 0 || type == HEX ){														\
		ObjNumPrint( (u32)num, y, x, pltt, type, sizeof(num) );							\
	} else {																			\
		offset = ObjStringPrint( "-", y, x , pltt );									\
		ObjNumPrint( ((u32)num ^ 0xFFFFFFFF)+1, y, offset, pltt, type, sizeof(num) );	\
	}																					\
}


//**************************************************************************** S
//	 マクロ名	:	ObjDataOut
//	   機能		:	符号付の変数名、内容をスプライトで描画
//	  引数 1	:	表示対象変数（数値）
//	  引数 2	:	縦表示位置（0～255）
//	  引数 3	:	横表示位置（0～255）
//	  引数 4	:	パレットNo（0～15)
//	  引数 5	:	表示形式（DEX:10進数 HEX:16進数）
//	  戻り値	:	無し
//	 主要変数	:	無し
//==============================================================================
//	 コメント	:	主にデバッグ用
//  最終更新日	:	2002/11/16 (Sat)
//**************************************************************************** E
#define	ObjDataOut( num, y, x, pltt, type )												\
{																						\
	u8	offset;																			\
	if ( num >= 0 || type == HEX ){														\
		offset = ObjStringPrint( #num"=", y, x , pltt );								\
		ObjNumPrint( (u32)num, y, offset, pltt, type, sizeof(num) );					\
	} else {																			\
		offset = ObjStringPrint( #num"=-", y, x , pltt );								\
		ObjNumPrint( ((u32)num ^ 0xFFFFFFFF)+1, y, offset, pltt, type, sizeof(num) );	\
	}																					\
}


//**************************************************************************** S
//	 マクロ名	:	BgNumberPrint
//	   機能		:	符号付の変数内容を背景で描画
//	  引数 1	:	表示対象変数（数値）
//	  引数 2	:	縦表示位置（キャラクター数：0～31）
//	  引数 3	:	横表示位置（キャラクター数：0～31）
//	  引数 4	:	パレットNo（0～15)
//	  引数 5	:	表示形式（DEX:10進数 HEX:16進数）
//	  引数 6	:	使用する背景No（0～3）
//	  戻り値	:	無しN
//	 主要変数	:	無し
//==============================================================================
//	 コメント	:	±を自動判別しくれるのでBgNumPrintよりこちらを推奨
//  最終更新日	:	2002/11/16 (Sat)
//**************************************************************************** E
#define	BgNumberPrint( num, y, x, pltt, type, bg_no )										\
{																							\
	u8	offset;																				\
	if ( num >= 0 || type == HEX ){															\
		BgNumPrint( (u32)num, y, x, pltt, type, sizeof(num), bg_no );						\
	} else {																				\
		offset = BgStringPrint( "-", y, x , pltt, bg_no );									\
		BgNumPrint( ((u32)num^0xFFFFFFFF)+1, y, x+offset, pltt, type, sizeof(num), bg_no );	\
	}																						\
}


//**************************************************************************** S
//	 マクロ名	:	BgDataOut
//	   機能		:	符号付の変数名、内容をスプライトで描画
//	  引数 1	:	表示対象変数（数値）
//	  引数 2	:	縦表示位置（キャラクター数：0～31）
//	  引数 3	:	横表示位置（キャラクター数：0～31）
//	  引数 4	:	パレットNo（0～15)
//	  引数 5	:	表示形式（DEX:10進数 HEX:16進数）
//	  引数 6	:	使用する背景No（0～3）
//	  戻り値	:	無し
//	 主要変数	:	無し
//==============================================================================
//	 コメント	:	主にデバッグ用
//  最終更新日	:	2002/11/16 (Sat)
//**************************************************************************** E
#define	BgDataOut( num, y, x, pltt, type, bg_no )											\
{																							\
	u8	offset;																				\
	if ( num >= 0 || type == HEX ){															\
		offset = BgStringPrint( #num"=", y, x , pltt, bg_no );								\
		BgNumPrint( (u32)num, y, x+offset, pltt, type, sizeof(num), bg_no );				\
	} else {																				\
		offset = BgStringPrint( #num"=-", y, x , pltt, bg_no );								\
		BgNumPrint( ((u32)num^0xFFFFFFFF)+1, y, x+offset, pltt, type, sizeof(num), bg_no );	\
	}																						\
}

#endif