;********************************************************************
;*          crt0_arm.s                                              *
;*            スタートアップルーチン（ARMASM用）                    *
;*                                                                  *
;*          Copyright (C) 1999-2001 NINTENDO Co.,Ltd.               *
;********************************************************************
    INCLUDE     AgbDefineArm.s
    INCLUDE     AgbMemoryMapArm.s
    INCLUDE     AgbSyscallDefineArm.s
    INCLUDE     AgbMacroArm.s
    AREA        Init, CODE, READONLY

    INCLUDE     MultiSioDefineArm.s

    ENTRY
start
    INCLUDE     rom_header_arm.s

;--------------------------------------------------------------------
;-                      リセット                                    -
;--------------------------------------------------------------------
    EXTERN      AgbMain
    CODE32
start_vector
        mov     r0, #PSR_IRQ_MODE       ; IRQモードへ切り換え
        msr     cpsr, r0
        ldr     sp, sp_irq              ; SP_irq のセット
        mov     r0, #PSR_SYS_MODE       ; システムモードへ切り換え
        msr     cpsr, r0
        ldr     sp, sp_usr              ; SP_usr のセット
        ldr     r1, =INTR_VECTOR_BUF    ; 割り込みアドレスのセット
        adr     r0, intr_main
        str     r0, [r1]
        ldr     r1, =AgbMain            ; スタート ＆ 16bitコードへの切換
        mov     lr, pc
        bx      r1
        b       start_vector            ; リセット

    ALIGN
sp_usr  DCD     WRAM_END - 0x100
sp_irq  DCD     WRAM_END - 0x60

;--------------------------------------------------------------------
;-          割り込み分岐処理（テーブル引き）32Bit            28-63c -
;--------------------------------------------------------------------
    EXTERN      IntrTable
    GLOBAL      intr_main
    ALIGN
    CODE32
intr_main
        mov     r12, #REG_BASE           ; r12: REG_BASE
        add     r3, r12, #OFFSET_REG_IE  ; r3:  REG_IE
        ldr     r2, [r3]
        and     r1, r2, r2, lsr #16      ; r1:  IE & IF
        mov     r2, #0                       ; IE/IF チェック
        ands    r0, r1, #CASSETTE_INTR_FLAG  ; カートリッジ 割り込み
        strneb  r0, [r3, #REG_SOUNDCNT_X - REG_IE]  ; サウンド停止
loop    bne     loop

        ands    r0, r1, #SIO_INTR_FLAG | MULTI_SIO_TIMER_INTR_FLAG
        bne     jump_intr                    ; シリアル通信 割り込み
        add     r2, r2, #4                   ; or マルチプレイ通信用タイマー 割り込み

        ands    r0, r1, #V_BLANK_INTR_FLAG   ; Vブランク 割り込み
        strneh  r0, [r12, #INTR_CHECK_BUF - WRAM_END] ; 割り込みチェック セット
        bne     jump_intr
        add     r2, r2, #4

        ands    r0, r1, #H_BLANK_INTR_FLAG   ; Hブランク 割り込み
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #V_COUNT_INTR_FLAG   ; Vカウンタ 割り込み
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #TIMER0_INTR_FLAG    ; タイマー0 割り込み
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA0_INTR_FLAG      ; DMA0 割り込み
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA1_INTR_FLAG      ; DMA1 割り込み
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA2_INTR_FLAG      ; DMA2 割り込み
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #DMA3_INTR_FLAG      ; DMA3 割り込み
        bne     jump_intr
        add     r2, r2, #4
        ands    r0, r1, #KEY_INTR_FLAG       ; キー 割り込み
jump_intr
        strh    r0, [r3, #2]            ; IF クリア           11c
        ldr     r1, =IntrTable          ; ユーザIRQ処理へジャンプ
        add     r1, r1, r2
        ldr     r0, [r1]
        bx      r0


    END

