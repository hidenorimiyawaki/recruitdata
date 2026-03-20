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

void IntrDummy(void);
void VBlankIntr(void);

#endif
