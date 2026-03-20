//**************************************************************************** S
//
//	 ソース名称		:	MultiSio.c
//
//==============================================================================
//	 コメント		:	通信関連
//	 最終更新日		:	0000/00/00 (Zzz)
//**************************************************************************** E
//#define CODE32
#include "All.h"


/*-------------------- グローバル 変数  ----------------------------*/

extern const IntrFuncp IntrTable[13];
extern IntrFuncp IntrTableBuf[14];
extern void intr_main(void);

MultiSioArea     Ms;            // マルチプレイ通信ワークエリア

#ifdef MULTI_SIO_DI_FUNC_FAST
u32 RecvFuncBuf[0x40/4];        // 受信データ・チェックバッファ変更ルーチンRAM実行用バッファ
u32 IntrFuncBuf[0x140/4];       // 割り込みルーチンRAM実行用バッファ
#endif

static const u8 MultiSioLib_Var[]="MultiSio010918";


/*------------------------------------------------------------------*/
/*                      マルチプレイ通信初期化                      */
/*------------------------------------------------------------------*/
extern u32 MultiSioRecvBufChange(void);

void MultiSioInit(void)
{
    int     i;

    *(vu16 *)REG_IME = 0;
    *(vu16 *)REG_IE &= ~(SIO_INTR_FLAG                  // SIO＆タイマー割込不許可
                       | MULTI_SIO_TIMER_INTR_FLAG);
    *(vu16 *)REG_IME = 1;

    *(vu16 *)REG_RCNT    = R_SIO_MASTER_MODE;
    *(vu32 *)REG_SIOCNT  = SIO_MULTI_MODE;
    *(vu16 *)REG_SIOCNT |= SIO_IF_ENABLE | MULTI_SIO_BAUD_RATE_NO;

    CpuClear(0, &Ms, sizeof(Ms), 32);                   // マルチプレイ通信ワークエリア クリア

#ifdef MULTI_SIO_DI_FUNC_FAST                           // 関数のコピー
    CpuCopy(MultiSioRecvBufChange, RecvFuncBuf, sizeof(RecvFuncBuf), 32);
    CpuCopy(MultiSioIntr,          IntrFuncBuf, sizeof(IntrFuncBuf), 32);
#endif

    Ms.SendBufCounter  = -1;

    Ms.NextSendBufp    = (u16 *)&Ms.SendBuf[0];         // 送信バッファポインタ セット
    Ms.CurrentSendBufp = (u16 *)&Ms.SendBuf[1];

    for (i=0; i<MULTI_SIO_PLAYERS_MAX; i++) {           // 受信バッファポインタ セット
        Ms.CurrentRecvBufp[i] = (u16 *)&Ms.RecvBuf[i][0];
        Ms.LastRecvBufp[i]    = (u16 *)&Ms.RecvBuf[i][1];
        Ms.RecvCheckBufp[i]   = (u16 *)&Ms.RecvBuf[i][2];
    }

    *(vu16 *)REG_IME = 0;
    *(vu16 *)REG_IE |= SIO_INTR_FLAG;                   // SIO割込許可
    *(vu16 *)REG_IME = 1;
}


/*------------------------------------------------------------------*/
/*                      マルチプレイ通信スタート                    */
/*------------------------------------------------------------------*/

void MultiSioStart(void)
{
    if (Ms.Type)    Ms.StartFlag = 1;                   // スタートフラグ セット
}

/*------------------------------------------------------------------*/
/*                      マルチプレイ通信ストップ                    */
/*------------------------------------------------------------------*/

void MultiSioStop(void)
{
    *(vu16 *)REG_IME = 0;
    *(vu16 *)REG_IE &= ~(SIO_INTR_FLAG                  // SIO＆タイマー割込不許可
                       | MULTI_SIO_TIMER_INTR_FLAG);
    *(vu16 *)REG_IME = 1;

    *(vu16 *)REG_SIOCNT = SIO_MULTI_MODE                // SIO停止
                        | MULTI_SIO_BAUD_RATE_NO;
    *(vu32 *)REG_MULTI_SIO_TIMER                        // タイマー停止
                        = MULTI_SIO_TIMER_COUNT;

    *(vu16 *)REG_IF = SIO_INTR_FLAG                     // IF リセット
                    | MULTI_SIO_TIMER_INTR_FLAG;

    Ms.StartFlag = 0;                                   // スタートフラグ リセット
}


/*------------------------------------------------------------------*/
/*                      マルチプレイ通信メイン                      */
/*------------------------------------------------------------------*/

u32 MultiSioMain(void *Sendp, void *Recvp)
{
    SioMultiCnt     SioCntBak  = *(SioMultiCnt *)REG_SIOCNT;
    int             i, ii;

    switch (Ms.State) {
        case 0: if (!SioCntBak.ID) {                                // 接続関係チェック
                    if (!SioCntBak.SD || SioCntBak.Enable)    break;
                    if (!SioCntBak.SI && Ms.SendBufCounter == -1) {
                        *(vu16 *)REG_IME = 0;
                        *(vu16 *)REG_IE &= ~SIO_INTR_FLAG;              // SIO割込不許可
                        *(vu16 *)REG_IE |=  MULTI_SIO_TIMER_INTR_FLAG;  // タイマー割込許可
                        *(vu16 *)REG_IME = 1;

                        ((SioMultiCnt *)REG_SIOCNT)->IF_Enable = 0;     // SIO-IFE リセット
                        *(vu16 *)REG_IF  =  SIO_INTR_FLAG               // IF リセット
                                         |  MULTI_SIO_TIMER_INTR_FLAG;

                        *(vu32 *)REG_MULTI_SIO_TIMER                    // タイマー初期化
                                         = MULTI_SIO_TIMER_COUNT;

                        Ms.Type = SIO_MULTI_PARENT;
                    }
                }
                Ms.State = 1;
        case 1: if (Ms.ConnectedFlags)                              // 初期化時の通信安定待ち期間
                    if (Ms.RecvFlagsAvailableCounter < 8)
                        Ms.RecvFlagsAvailableCounter++;
                    else    Ms.State = 2;
        case 2: MultiSioRecvDataCheck(Recvp);                       // 受信データ チェック
                MultiSioSendDataSet(Sendp);                         // 送信データ セット
                break;
    }

    Ms.SendFrameCounter++;

    return      Ms.RecvSuccessFlags
              | (Ms.Type == SIO_MULTI_PARENT) << 7
              | Ms.ConnectedFlags << 8
              | (Ms.HardError != 0) << 12
              | (SioCntBak.ID >= MULTI_SIO_PLAYERS_MAX) << 13
              | (Ms.RecvFlagsAvailableCounter >> 3) << 15;
}


/*------------------------------------------------------------------*/
/*                      送信データ セット                           */
/*------------------------------------------------------------------*/

void MultiSioSendDataSet(void *Sendp)
{
    s32     CheckSum = 0;
    int     i;

    ((MultiSioPacket *)Ms.NextSendBufp)->FrameCounter = (u8 )Ms.SendFrameCounter;
    ((MultiSioPacket *)Ms.NextSendBufp)->RecvErrorFlags =  Ms.ConnectedFlags ^ Ms.RecvSuccessFlags;
    ((MultiSioPacket *)Ms.NextSendBufp)->CheckSum = 0;

    CpuCopy(Sendp, (u8 *)&Ms.NextSendBufp[2], MULTI_SIO_BLOCK_SIZE, 32);  // 送信データ セット

    for (i=0; i<sizeof(MultiSioPacket)/2 - 2; i++)      // 送信データ チェックサム算出
        CheckSum += Ms.NextSendBufp[i];
    ((MultiSioPacket *)Ms.NextSendBufp)->CheckSum = ~CheckSum - sizeof(MultiSioPacket)/2;

    if (Ms.Type)
        *(vu16 *)REG_MULTI_SIO_TIMER_H = 0;             // タイマー ストップ

    Ms.SendBufCounter = -1;                             // 送信データ更新

    if (Ms.Type && Ms.StartFlag)
        *(vu16 *)REG_MULTI_SIO_TIMER_H                  // タイマー スタート
                             = (TMR_PRESCALER_1CK
                              | TMR_IF_ENABLE | TMR_ENABLE) >> 16;
}

/*------------------------------------------------------------------*/
/*                      受信データ チェック                         */
/*------------------------------------------------------------------*/

u32 MultiSioRecvDataCheck(void *Recvp)
{
    u32 (*MultiSioRecvBufChangeOnRam)(void) = (u32 (*)(void))RecvFuncBuf;
    u16     *BufpTmp;
    s32      CheckSum;
    vu32     RecvCheck = 0;
    u8       SyncRecvFlagBak[4];
    u8       CounterDiff;
    int      i, ii;

#ifdef MULTI_SIO_DI_FUNC_FAST                           // 受信データ・チェックバッファ更新
    *(u32 *)SyncRecvFlagBak = MultiSioRecvBufChangeOnRam();
#else

    *(vu16 *)REG_IME = 0;                               // 割込不許可（約80クロック）

    for (i=0; i<4; i++) {
        BufpTmp = Ms.RecvCheckBufp[i];                  // 受信データ・チェックバッファ更新
        Ms.RecvCheckBufp[i] = Ms.LastRecvBufp[i];
        Ms.LastRecvBufp[i] = BufpTmp;
    }
    *(u32 *)SyncRecvFlagBak = *(u32 *)Ms.SyncRecvFlag;  // 受信確認フラグ コピー
    *(u32 *)Ms.SyncRecvFlag = 0;

    *(vu16 *)REG_IME = 1;                               // 割込許可
#endif


    Ms.RecvSuccessFlags = 0;

    for (i=0; i<MULTI_SIO_PLAYERS_MAX; i++) {
        CheckSum = 0;                                   // 受信データ チェックサム算出
        for (ii=0; ii<sizeof(MultiSioPacket)/2 - 2; ii++)
            CheckSum +=  Ms.RecvCheckBufp[i][ii];

        if (SyncRecvFlagBak[i])                         // 受信成功確認
            if ((s16 )CheckSum == (s16 )(-1 - sizeof(MultiSioPacket)/2)) {
                CpuCopy(&((u8 *)Ms.RecvCheckBufp[i])[4],
                        &((u8 *)Recvp)[i*MULTI_SIO_BLOCK_SIZE], MULTI_SIO_BLOCK_SIZE, 32);
                Ms.RecvSuccessFlags |= 1 << i;
            }

        CpuClear(0, &((u8 *)Ms.RecvCheckBufp[i])[4], MULTI_SIO_BLOCK_SIZE, 32);
    }

    Ms.ConnectedFlags |= Ms.RecvSuccessFlags;           // 接続完了フラグ セット

    return Ms.RecvSuccessFlags;
}


/*==================================================================*/
/*                  マルチプレイ通信割り込み ルーチン               */
/*==================================================================*/

#ifndef MULTI_SIO_DI_FUNC_FAST

void MultiSioIntr(void)
{
    u16      RecvTmp[4];
    u16     *BufpTmp;
    int     i, ii;


    // 受信データ退避

    *(u64 *)RecvTmp = *(u64 *)REG_SIOMLT_RECV;


    // ハードエラー検出

    Ms.HardError = ((SioMultiCnt *)REG_SIOCNT)->Error;


    // 送信データ処理

    if (Ms.SendBufCounter == -1) {                      // 同期データ セット
        ((SioMultiCnt *)REG_SIOCNT)->Data = MULTI_SIO_SYNC_DATA;

        BufpTmp = Ms.CurrentSendBufp;                   // 送信バッファ変更
        Ms.CurrentSendBufp = Ms.NextSendBufp;
        Ms.NextSendBufp = BufpTmp;
    } else if (Ms.SendBufCounter >= 0) {                // 送信データ セット
        ((SioMultiCnt *)REG_SIOCNT)->Data = Ms.CurrentSendBufp[Ms.SendBufCounter];
    }
    if (Ms.SendBufCounter < (s32 )(sizeof(MultiSioPacket)/2 - 1))  Ms.SendBufCounter++;


    // 受信データ処理（最大約350クロック／ウェイト期間に含まれる）

    for (i=0; i<MULTI_SIO_PLAYERS_MAX; i++) {
        if (RecvTmp[i] == MULTI_SIO_SYNC_DATA
         && Ms.RecvBufCounter[i] > (s32 )(sizeof(MultiSioPacket)/2 - 3)) {
            Ms.RecvBufCounter[i] = -1;
        } else {
            Ms.CurrentRecvBufp[i][Ms.RecvBufCounter[i]] = RecvTmp[i];
                                                        // 受信データ格納
            if (Ms.RecvBufCounter[i] == (s32 )(sizeof(MultiSioPacket)/2 - 3)) {
                BufpTmp = Ms.LastRecvBufp[i];           // 受信バッファ変更
                Ms.LastRecvBufp[i] = Ms.CurrentRecvBufp[i];
                Ms.CurrentRecvBufp[i] = BufpTmp;
                Ms.SyncRecvFlag[i] = 1;                 // 受信完了
            }
        }
        if (Ms.RecvBufCounter[i] < (s32 )(sizeof(MultiSioPacket)/2 - 1))  Ms.RecvBufCounter[i]++;
    }


    // 親機送信開始

    if (Ms.Type == SIO_MULTI_PARENT) {
        *(vu16 *)REG_MULTI_SIO_TIMER_H = 0;             // タイマー ストップ
        *(vu16 *)REG_SIOCNT |= SIO_ENABLE;              // 送信再開
        *(vu16 *)REG_MULTI_SIO_TIMER_H                  // タイマー再開
                             = (TMR_PRESCALER_1CK
                              | TMR_IF_ENABLE | TMR_ENABLE) >> 16;
    }
}

#endif


void SioSetting( void )
{
	RegisterRamReset(RESET_EX_WRAM_FLAG								// CPU外部ワークRAM クリア
					| RESET_CPU_WRAM_FLAG);							// CPU内部ワークRAM クリア

	*(vu16 *)REG_WAITCNT = CST_ROM0_1ST_3WAIT | CST_ROM0_2ND_1WAIT
						 | CST_PREFETCH_ENABLE;						// 3-1ウェイトアクセス設定

	DmaCopy(3, IntrTable, IntrTableBuf, sizeof(IntrTableBuf), 32);	// 割り込みテーブル セット
	DmaCopy(3, intr_main, IntrMainBuf,  sizeof(IntrMainBuf),  32);	// 割り込みメインルーチン セット
	*(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

	*(vu16 *)REG_IE = V_BLANK_INTR_FLAG								// Vブランク割込許可
					| CASSETTE_INTR_FLAG;							// カートリッジ割込許可
	*(vu16 *)REG_STAT = STAT_V_BLANK_IF_ENABLE;
	*(vu16 *)REG_IME = 1;											// IME セット
	
	return;
}

void MultiSio( void )
{
	int i;

	SioFlagsBak = SioFlags;						// 前回の内容の退避
	SioFlags = MultiSioMain(SendBuf, RecvBuf);	// マルチプレイ通信メイン
	if (Trg) MultiSioStart();					// マルチプレイ通信スタート

//	if (SioFlags & MULTI_SIO_PARENT) {		  // 通信状態 & 親接続
//		if (!SioStartFlag)	StrTmp = "PUSH ANY KEY  ";	// 転送開始時
//		else				StrTmp = "			  ";	// 転送待ち時
//		BgStringPrint(StrTmp, 0, 2, 15, 0);	// 背景セット
//	}

	if (!SioStartFlag) {	// 初回接続認識
		if (SioFlags & MULTI_SIO_CONNECTED_ID0) {  // 親接続が確立されたならば
			SendBuf[0] = SendBuf[1] = SendBuf[2] = SendBuf[3] = 0xfc00;	// 初期転送データセット
			SioStartFlag = 1;	// 転送開始
		}
	} else {				// 転送後であれば
		for (i=0; i<MULTI_SIO_PLAYERS_MAX; i++) {
			if (SioFlags & (1 << i)) {	// 受信成功マシンのデータ処理
				SioKey[i] = RecvBuf[i][0];
				SioOldKey[i] = RecvBuf[i][1];
			} else {					// 受信失敗マシンのデータ処理
				SioKey[i] = SioOldKey[i];
			}
			// 転送データの表示
			//BgNumberPrint( i,      3+i*2, 1, 15, DEX, 0 );
			//BgKeyPrint( SioKey[i], 3+i*2, 3, 15,      0 );
		}
		//BgDataOut( SioFlags, 12, 5, 15, HEX, 0 );


		// ===== 各種エラー処理 ===== S
//		if (SioFlags & MULTI_SIO_HARD_ERROR)	// 通信エラー表示
//			StrTmp = "HARD ERROR	";
//		else if (SioFlags & MULTI_SIO_ID_OVER_ERROR) // IDオーバーエラー表示
//			StrTmp = "ID OVER ERROR ";
//		else if (SioFlags & MULTI_SIO_RECV_FLAGS_AVAILABLE
//				 // 受信成功フラグ有効
//				 && (((MultiSioReturn *)&SioFlags)->RecvSuccessFlags
//				 // 受信成功フラグ
//					 ^ ((MultiSioReturn *)&SioFlags)->ConnectedFlags))
//				 // 接続履歴フラグ
//			StrTmp = "RECV ERROR	";
//		else
//			StrTmp = "			  ";
//		BgStringPrint(StrTmp, 15, 2, 15, 0);	// 文字列セット
		// ===== 各種エラー処理 ===== E

		if ((SioFlags | SioFlagsBak) & 0xe
			// 現フレームか前フレームで子のどれかが転送に成功しており
			&& SioFlags & (1 << ((SioMultiCnt *)REG_SIOCNT)->ID)) {
			// かつ、現フレームで自機の転送に成功しているならば
			// すなわち、自機の転送が行われたとき
			SendBuf[0] = Key;
			SendBuf[1] = OldKey;
			SendBuf[2] = 0;
			SendBuf[3] = 0;	// 転送データセット
		}
	}
}