//**************************************************************************** S
//
//	 ヘッダー名称	:	sprite.h
//
//==============================================================================
//	 コメント		:	sprite.cの為の関数ヘッダー（マクロ付き）
//	 最終更新日		:	2002/11/16 (Sat)
//**************************************************************************** E

#ifndef	___SPRITE_H___
#define	___SPRITE_H___


BOOL ObjAction( u8, const ANIME * );
// アニメーションの経過( ObjNo, アニメデータ )

void OamManager(void);



#define		VRAM_RANK				OBJ_MODE0_VRAM
#define		VRAM_RANK_SIZE			32

#define		VRAM_SKILL				(VRAM_RANK+VRAM_RANK_SIZE*4)
#define		VRAM_SKILL_SIZE			(32*8*8)

#define		VRAM_SPECIAL			(VRAM_SKILL+VRAM_SKILL_SIZE*8)
#define		VRAM_SPECIAL_SIZE		(32*8*8)

#define		VRAM_MAGIC				(VRAM_SPECIAL+VRAM_SPECIAL_SIZE*4)
#define		VRAM_MAGIC_SIZE			(32*4*4)

#define		VRAM_ENEMY_SHOT			(VRAM_MAGIC+VRAM_MAGIC_SIZE*4)
#define		VRAM_ENEMY_SHOT_SIZE	(32*4*4)

#define		VRAM_PLAYER_DAMAGE		(VRAM_ENEMY_SHOT+VRAM_ENEMY_SHOT_SIZE*10)
#define		VRAM_PLAYER_DAMAGE_SIZE	(32*4*4)

#define		VRAM_ENEMY_DAMAGE		(VRAM_PLAYER_DAMAGE+VRAM_PLAYER_DAMAGE*4)
#define		VRAM_ENEMY_DAMAGE_SIZE	(32*4*4)

#define		VRAM_PLAYER				(VRAM_ENEMY_DAMAGE+VRAM_ENEMY_DAMAGE_SIZE*10)
#define		VRAM_PLAYER_SIZE		(32*8*4)

#define		VRAM_ENEMY				(VRAM_PLAYER+VRAM_PLAYER_SIZE*4)
#define		VRAM_ENEMY_SIZE			(32*4*4)

#define		VRAM_BOSS				(VRAM_ENEMY+VRAM_ENEMY_SIZE*10)
#define		VRAM_BOSS_SIZE			(32*8*8)

#define		VRAM_COIN				(VRAM_BOSS+VRAM_BOSS_SIZE*2)
#define		VRAM_COIN_SIZE			(32*2*2)

#define		VRAM_OTHER				(VRAM_COIN+VRAM_COIN_SIZE)


#endif