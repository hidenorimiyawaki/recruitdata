//**************************************************************************** S
//
//	 ソース名称		:	Move.h
//
//==============================================================================
//	 コメント		:	Move.cで使用するものを定義するためのもの。
//	 最終更新日		:	2003/03/05 (Wed)
//**************************************************************************** E
#ifndef	___MOVE_H___
#define	___MOVE_H___

// 斜め
#define	WALK_SPEED		2				// 斜め移動でどの√をとるか
#define WALK_MAGIC		1
#define WALK_PETIT		1
#define WALK_POWER		19
#define WALK_BEAST		2

// 上下左右
#define	WALK2_SPEED		0x0001F000		// 1.9375
#define WALK2_MAGIC		0x0000F000		// 0.9375
#define WALK2_PETIT		0x00010000		// 1
#define WALK2_POWER		0x0000C000		// 0.75
#define WALK2_BEAST		0x0001C000		// 1.75

#define	SP_DASH		5					// スキル移動時の慣性をつけるためのもの

#define	SPECIAL_SPEED		4			// 必殺技時のスピードキャラの移動量
#define	BEAST_SPEED			4			// 必殺技時のビーストキャラの移動量

/*
0x00002434, 0x00005A82, 0x00007EB6
17 0.2√2	18 0.5√2	19 0.7√2

0x00010000		// 1
0x00018000		// 1.5
0x0001C000		// 1.75
0x0001E000		// 1.875
0x0001F000		// 1.9375
0x00008000		// 0.5
0x0000C000		// 0.75
0x0000E000		// 0.875
0x0000F000		// 0.9375
*/

s32 work_h,work_v;


void Move(u8);						// 関数呼び出し。
void SkillMove(u8);						// 関数呼び出し。
void SpecialMove(u8);						// 関数呼び出し。


#endif