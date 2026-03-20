
@*********************************************************S
@					スタートアップ
@	tab		4
@	Copyright (C) コンピュータ総合学園 HAL
@*********************************************************E

	.INCLUDE	"AgbDefine.s"			@ 各種定義
	.INCLUDE	"AgbMemoryMap.s"		@ AGBメモリマップ
	.INCLUDE	"AgbSyscallDefine.s"	@ 各種システムコール
	.INCLUDE	"AgbMacro.s"			@ 各種マクロ
	.TEXT

	.GLOBAL		_start					@ スタートアップベクタ
										@ GCCのファーストエントリーは
										@ startです
_start:
	.INCLUDE	"rom_header.s"			@ ライセンス製品には必要

@*********************************************************S
@			スタートアップエントリー（リセット）

	.EXTERN		main					@ Cのスタートエントリ
	.GLOBAL		start_vector
	.CODE 32
start_vector:
		mov		r0, #PSR_IRQ_MODE       @ IRQモードへ切り換え
		msr		cpsr, r0
		ldr		sp, sp_irq              @ SP_irq のセット
		mov		r0, #PSR_SYS_MODE       @ システムモードへ切り換え
		msr		cpsr, r0
		ldr		sp, sp_usr              @ SP_usr のセット
		ldr		r1, =INTR_VECTOR_BUF    @ 割り込みアドレスのセット
		adr		r0, intr_main
		str		r0, [r1]
		ldr		r1, =main	            @ スタート ＆ 16bitコードへの切換
		mov		lr, pc
		bx		r1
		b		start_vector            @ リセット

	.ALIGN
sp_usr:	.word	WRAM_END - 0x100		@ ユーザスタックの指定
sp_irq:	.word	WRAM_END - 0x60			@ システムコールスタックの指定


@*********************************************************S
@			割り込み分岐処理（テーブル引き）32Bit

	.EXTERN		IntrTable
	.GLOBAL		intr_main
	.ALIGN
	.CODE 32
intr_main:
		mov		r3, #REG_BASE							@ IE/IF チェック
		add		r3, r3, #OFFSET_REG_IE					@ r3: REG_IE
		ldr		r2, [r3]
		and		r1, r2, r2, lsr #16						@ r1: IE & IF
		ands	r0, r1, #CASSETTE_INTR_FLAG				@ カートリッジ 割り込み
loop:	bne		loop
		mov		r2, #0
		ands	r0, r1, #V_BLANK_INTR_FLAG				@ Vブランク 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #H_BLANK_INTR_FLAG				@ Hブランク 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #V_COUNT_INTR_FLAG				@ Vカウンタ 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #TIMER0_INTR_FLAG				@ タイマー0 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #TIMER1_INTR_FLAG				@ タイマー1 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #TIMER2_INTR_FLAG				@ タイマー2 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #TIMER3_INTR_FLAG				@ タイマー3 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #SIO_INTR_FLAG					@ シリアル通信 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #DMA0_INTR_FLAG					@ DMA0 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #DMA1_INTR_FLAG					@ DMA1 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #DMA2_INTR_FLAG					@ DMA2 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #DMA3_INTR_FLAG					@ DMA3 割り込み
		bne		jump_intr
		add		r2, r2, #4
		ands	r0, r1, #KEY_INTR_FLAG					@ キー 割り込み
jump_intr:
		strh	r0, [r3, #2]							@ IF クリア           11c
		ldr		r1, =IntrTable							@ ユーザIRQ処理へジャンプ
		add		r1, r1, r2
		ldr		r0, [r1]
		bx		r0

	.END

