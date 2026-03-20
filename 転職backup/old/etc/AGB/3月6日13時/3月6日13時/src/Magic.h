//**************************************************************************** S
//
//	 ソース名称		:	Magic.h
//
//==============================================================================
//	 コメント		:	Magic.cで使用するものを定義するためのもの。
//	 最終更新日		:	2003/03/05 (Wed)
//**************************************************************************** E
#ifndef	___MAGIC_H___
#define	___MAGIC_H___


#define	MAGIC_SPEED			2		// 魔法の移動スピード

// 
#define MG_RIGHT_OFFSET_X 	32
#define MG_RIGHT_OFFSET_Y 	16

#define MG_LEFT_OFFSET_X 	16
#define MG_LEFT_OFFSET_Y 	16

#define MG_UP_OFFSET_X 		8
#define MG_UP_OFFSET_Y 		16

#define MG_DOWN_OFFSET_X 	8
#define MG_DOWN_OFFSET_Y 	32


void Magic(u8);						// 関数呼び出し。


#endif