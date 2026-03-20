//******************************* キーアサイン ********************************S
#define		KEY_L		(0x0200)
#define		KEY_R		(0x0100)
#define		KEY_DOWN	(0x0080)
#define		KEY_UP		(0x0040)
#define		KEY_LEFT	(0x0020)
#define		KEY_RIGHT	(0x0010)
#define		KEY_START	(0x0008)
#define		KEY_SELECT	(0x0004)
#define		KEY_B		(0x0002)
#define		KEY_A		(0x0001)
volatile u16	KeyTrg, KeyCont;	// キー入力（キーデータがキャッシュされないようにvolatileで宣言）
//******************************* キーアサイン ********************************E


//**********************************************************S
//						キーマネージャ
//
// フレーム毎にこの関数を呼ぶことで、キー入力状態がセットされる
//
void KeyManager(void)
{
 	u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ ALL_KEY_MASK);
    KeyTrg  = ReadData & (ReadData ^ KeyCont);            // トリガ 入力
    KeyCont = ReadData;                                //   ベタ 入力
}
//*********************************************************E

