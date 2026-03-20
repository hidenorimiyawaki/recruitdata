//*****************************************************************************S
//							ハードウェア初期化など
//	tab		4
//	Copyright (C)	コンピュータ総合学園 HAL
//*****************************************************************************E

#ifndef	__HARD_INIT_H__
#define	__HARD_INIT_H__

#undef	NULL
#define	NULL	((void *)0)

//**************** 初期化関数プロトタイプ *****************S
void ClearRamAll( void );
void ClearWorkRam( void );
void ClearGraphicRam( void );
void ClearVram( void );
void ClearOamRam( void );
void ClearPaletteRam( void );
//**************** 初期化関数プロトタイプ *****************E


//********************* 割り込み関連 **********************S
typedef void (*IntrFuncp)(void);

void InitVBlank( void );
void SetVBlankFunc( IntrFuncp fnc );
void V_Intr_Clear(void);
void V_Intr_Set(void);
void V_Wait(void);
//********************* 割り込み関連 **********************E

#endif
