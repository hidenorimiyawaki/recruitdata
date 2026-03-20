//**************************************************************************** S
//
//	ヘッダー名称	:	MultiSio.h
//
//==============================================================================
//	 コメント		:	通信関連の関数ヘッダー
//	 最終更新日		:	0000/00/00 ()
//**************************************************************************** E
#ifndef _MULTI_SIO_H
#define _MULTI_SIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <agb.h>

// 下記の設定値はソフトの仕様に合わせて最適化して下さい。

#define MULTI_SIO_BLOCK_SIZE        24       // 通信データブロックサイズ（最大24Byte）

#define MULTI_SIO_PLAYERS_MAX       4       // 最大プレイヤー数

#define MULTI_SIO_SYNC_DATA         0xfefe  // 同期データ（0x0000／0xffffは禁止）

// CPU内部ワークRAMに余裕がなければコメントアウトして下さい。
#define MULTI_SIO_DI_FUNC_FAST              // SIO割り込み禁止関数高速化フラグ（CPU内部RAM実行）


// 通信割り込みの最大遅延が下記の値より大きくなる場合は更新して下さい。
#define MULTI_SIO_INTR_DELAY_MAX    2000    // 通信割り込み許容遅延クロック数

#ifdef  MULTI_SIO_DI_FUNC_FAST
#define MULTI_SIO_INTR_CLOCK_MAX    400     // 通信割り込み処理最大クロック数
#else
#define MULTI_SIO_INTR_CLOCK_MAX    1000
#endif

#define MULTI_SIO_1P_SEND_CLOCKS    3000    // 1台当りの通信時間

#if     MULTI_SIO_PLAYERS_MAX == 4
#define MULTI_SIO_START_BIT_WAIT    0       // スタートビット待ち時間
#else
#define MULTI_SIO_START_BIT_WAIT    512
#endif

// 開発途中では NDEBUG を未定義にして下記の値を 0 にし、
// 最終チェック段階では定義して 600 に変更した状態で動作確認をして下さい
// （設定値を増やしても通信間隔が延びるだけで処理が重くなることはありません）。
//#define NDEBUG                              // Makefile（MakefileDemo）での定義でも可
#ifdef  NDEBUG
#define MULTI_SIO_INTR_MARGIN       600     // 通信割り込み発生誤差保証値
#else
#define MULTI_SIO_INTR_MARGIN       0
#endif


#define MULTI_SIO_BAUD_RATE         115200          // ボーレート
#define MULTI_SIO_BAUD_RATE_NO      SIO_115200_BPS  // ボーレートＮｏ


#define MULTI_SIO_TIMER_NO          3       // タイマーＮｏ
#define MULTI_SIO_TIMER_INTR_FLAG   (TIMER0_INTR_FLAG << MULTI_SIO_TIMER_NO)
                                            // タイマー割り込みフラグ
#define REG_MULTI_SIO_TIMER         (REG_TM0CNT + MULTI_SIO_TIMER_NO * 4)
#define REG_MULTI_SIO_TIMER_L        REG_MULTI_SIO_TIMER
#define REG_MULTI_SIO_TIMER_H       (REG_MULTI_SIO_TIMER + 2)
                                            // タイマーレジスタ

// タイマーカウント数は通信データブロックサイズから算出します。
#define MULTI_SIO_TIMER_COUNT_TMP   (SYSTEM_CLOCK/60/((2 + 4 + MULTI_SIO_BLOCK_SIZE + 6)/(16/8)))
                                            // タイマーカウント暫定値
#define MULTI_SIO_TIMER_COUNT_MIN   ( MULTI_SIO_1P_SEND_CLOCKS * MULTI_SIO_PLAYERS_MAX    \
                                    + MULTI_SIO_START_BIT_WAIT + MULTI_SIO_INTR_MARGIN    \
                                    + MULTI_SIO_INTR_DELAY_MAX + MULTI_SIO_INTR_CLOCK_MAX)
                                            // タイマーカウント最小値
#define MULTI_SIO_TIMER_COUNT_MAX   0x10000 // タイマーカウント最大値
#define MULTI_SIO_TIMER_COUNT       (MULTI_SIO_TIMER_COUNT_MAX - MULTI_SIO_TIMER_COUNT_TMP)
                                            // タイマーカウント数
// タイマーカウント設定エラー
#if   MULTI_SIO_TIMER_COUNT_TMP < MULTI_SIO_TIMER_COUNT_MIN
    #error MULTI_SIO_TIMER_COUNT is too short,
    #error because MULTI_SIO_BLOCK_SIZE or MULTI_SIO_INTR_DELAY_MAX is too large.
#elif MULTI_SIO_TIMER_COUNT_TMP > MULTI_SIO_TIMER_COUNT_MAX
    #error MULTI_SIO_TIMER_COUNT is too long.
#endif


// マルチプレイ通信パケット構造体
typedef struct {
    u8  FrameCounter;                       // フレームカウンタ
    u8  RecvErrorFlags;                     // 受信エラーフラグ
    u16 CheckSum;                           // チェックサム
    u16 Data[MULTI_SIO_BLOCK_SIZE/2];       // 通信データ
    u16 OverRunCatch[2];                    // オーバーラン保護領域
} MultiSioPacket;


// マルチプレイ通信ワークエリア構造体
typedef struct {
    u8  Type;                               // 接続関係（親／子）
    u8  State;                              // 通信関数の状態
    u8  ConnectedFlags;                     // 接続履歴フラグ
    u8  RecvSuccessFlags;                   // 受信成功フラグ

    u8  SyncRecvFlag[4];                    // 受信確認フラグ

    u8  StartFlag;                          // 通信開始フラグ

    u8  HardError;                          // ハードエラー

    u8  RecvFlagsAvailableCounter;          // 受信成功フラグ有効カウンタ

    u8  SendFrameCounter;                   // 送信フレームカウンタ
    u8  RecvFrameCounter[4][2];             // 受信フレームカウンタ

    s32 SendBufCounter;                     // 送信バッファカウンタ
    s32 RecvBufCounter[4];                  // 受信バッファカウンタ

    u16 *NextSendBufp;                      // 送信バッファポインタ
    u16 *CurrentSendBufp;
    u16 *CurrentRecvBufp[4];                // 受信バッファポインタ
    u16 *LastRecvBufp[4];
    u16 *RecvCheckBufp[4];

    MultiSioPacket  SendBuf[2];             // 送信バッファ（ダブルバッファ）
    MultiSioPacket  RecvBuf[MULTI_SIO_PLAYERS_MAX][3];
                                            // 受信バッファ（トリプルバッファ）
} MultiSioArea;


extern u32 RecvFuncBuf[];                   // CPU内部RAM実行用バッファ
extern u32 IntrFuncBuf[];

extern MultiSioArea     Ms;                 // マルチプレイ通信ワークエリア


/*------------------------------------------------------------------*/
/*                      マルチプレイ通信初期化                      */
/*------------------------------------------------------------------*/

extern void MultiSioInit(void);

//・シリアル通信モードをマルチプレイモードにします。
//・レジスタやバッファの初期化を行ないます。

/*------------------------------------------------------------------*/
/*                      マルチプレイ通信スタート                    */
/*------------------------------------------------------------------*/

void MultiSioStart(void);

//・親機認識後であれば送信を開始するフラグをセットします。
//・子機あるいは親機認識前の時は何もしません。

/*------------------------------------------------------------------*/
/*                      マルチプレイ通信ストップ                    */
/*------------------------------------------------------------------*/

void MultiSioStop(void);

//・通信を停止します。

/*------------------------------------------------------------------*/
/*                      マルチプレイ通信メイン                      */
/*------------------------------------------------------------------*/

extern u32  MultiSioMain(void *Sendp, void *Recvp);

//・まず、親機か子機かを判別し、親機と認識された場合は通信を開始します。
//・MultiSioSendDataSet()を呼び出し、送信データをセットします。
//・MultiSioRecvDataCheck()を呼び出し、正常に受信できたかどうかを調べ、
//  Recvpへ受信データをコピーします。
//
//・１フレーム中のできるだけ近いタイミングで呼び出されるようにして下さい。
//・接続関係確定前にはフラグデータ（SIO_SYNC_DATA）と一致するデータは
//  送信しない方が安全です。
//
//・引数：
//    void *Sendp  ユーザ送信バッファポインタ
//    void *Recvp  ユーザ受信バッファポインタ

//・戻り値：

#define MULTI_SIO_RECV_ID_MASK          0x000f  // 受信成功フラグ
#define MULTI_SIO_CONNECTED_ID_MASK     0x0f00  // 接続履歴フラグ

#define MULTI_SIO_RECV_ID_SHIFT         0
#define MULTI_SIO_CONNECTED_ID_SHIFT    8

#define MULTI_SIO_RECV_ID0              0x0001  // 受信成功フラグ 親
#define MULTI_SIO_RECV_ID1              0x0002  //                子機１
#define MULTI_SIO_RECV_ID2              0x0004  //                子機２
#define MULTI_SIO_RECV_ID3              0x0008  //                子機３
#define MULTI_SIO_TYPE                  0x0080  // 接続関係（親／子）
#define MULTI_SIO_PARENT                0x0080  // 親接続
#define MULTI_SIO_CHILD                 0x0000  // 子接続
#define MULTI_SIO_CONNECTED_ID0         0x0100  // 接続履歴フラグ 親
#define MULTI_SIO_CONNECTED_ID1         0x0200  //                子機１
#define MULTI_SIO_CONNECTED_ID2         0x0400  //                子機２
#define MULTI_SIO_CONNECTED_ID3         0x0800  //                子機３
#define MULTI_SIO_HARD_ERROR            0x1000  // ハードエラー
#define MULTI_SIO_ID_OVER_ERROR         0x2000  // IDオーバーエラー
#define MULTI_SIO_RECV_FLAGS_AVAILABLE  0x8000  // 受信成功フラグ有効


// 戻り値構造体
typedef struct {
    u32 RecvSuccessFlags:4;                 // 受信成功フラグ(親,子1,子2,子3)
    u32 Reserved_0:3;                       // 予約
    u32 Type:1;                             // 接続関係（親／子）
    u32 ConnectedFlags:4;                   // 接続履歴フラグ
    u32 HardError:1;                        // ハードエラー
    u32 ID_OverError:1;                     // IDオーバーエラー
    u32 Reserved:1;                         // 予約
    u32 RecvFlagsAvailable:1;               // 受信成功フラグ有効
} MultiSioReturn;



/*------------------------------------------------------------------*/
/*                      マルチプレイ通信割り込み                    */
/*------------------------------------------------------------------*/

extern void MultiSioIntr(void);

//・通信割り込み時に各本体からの受信データを各受信バッファへ格納し、
//  送信バッファのデータをレジスタへセットします。
//・通信エラーフラグもワークへ格納します。
//・親機であればタイマーをリセットし送信を再開します。
//
//・子機は通信割り込みで親機はタイマー割り込みで呼ばれるように
//  プログラミングして下さい。
//・必ず１パケット（OverRunCatch[]以外）が１フレームで転送できるように
//  設定値を調整して下さい。


/*------------------------------------------------------------------*/
/*                      送信データ セット                           */
/*------------------------------------------------------------------*/

extern void MultiSioSendDataSet(void *Sendp);

//・ユーザ送信バッファのデータを送信バッファへセットします。
//
//・MultiSioMain()から呼び出されます。
//・直接呼び出す必要はありません。
//
//・引数：
//    void *Sendp  ユーザ送信バッファポインタ

/*------------------------------------------------------------------*/
/*                      受信データ チェック                         */
/*------------------------------------------------------------------*/

extern u32  MultiSioRecvDataCheck(void *Recvp);

//・正常に受信できたかどうかをチェックし、正常であれば受信データを
//  ユーザ受信バッファへコピーします。
//
//・MultiSioMain()から呼び出されます。
//・直接呼び出す必要はありません。
//
//・引数：
//    void *Recvp  ユーザ受信バッファポインタ


#ifdef __cplusplus
}      /* extern "C" */
#endif

void SioSetting( void );

void MultiSio( void );



#endif /* _MULTI_SIO_H */
