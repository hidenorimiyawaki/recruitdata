#include <windows.h>
#include <dinput.h>



void KeyManager();		//キーボードの状態取得
bool InitDInput(HINSTANCE app_hinst,HWND app_hwnd);	//初期化
void ReleaseDInput(void);//終了

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	{if(x){x->Release();x=NULL;}}
#endif


#define NUM_CONTROL	1
#define NUM_BUTTON	10

#define KEY_UP		0x0001
#define KEY_DOWN	0x0002
#define KEY_LEFT	0x0004
#define KEY_RIGHT	0x0008
#define KEY_A		0x0010
#define KEY_B		0x0020
#define KEY_C		0x0040
#define KEY_D		0x0080
#define KEY_L		0x0100
#define KEY_R		0x0200

#define KEY_PUSH_X(i)		(joystate[i] & (KEY_LEFT | KEY_RIGHT | KEY_UP | KEY_DOWN))
#define KEY_PUSH_UP(i)		(joystate[i] & KEY_UP)
#define KEY_PUSH_DOWN(i)	(joystate[i] & KEY_DOWN)
#define KEY_PUSH_RIGHT(i)	(joystate[i] & KEY_RIGHT)
#define KEY_PUSH_LEFT(i)	(joystate[i] & KEY_LEFT)
#define KEY_PUSH_A(i)		(joystate[i] & KEY_A)
#define KEY_PUSH_B(i)		(joystate[i] & KEY_B)
#define KEY_PUSH_C(i)		(joystate[i] & KEY_C)
#define KEY_PUSH_D(i)		(joystate[i] & KEY_D)
#define KEY_PUSH_L(i)		(joystate[i] & KEY_L)
#define KEY_PUSH_R(i)		(joystate[i] & KEY_R)

#define DIDEVICE_BUFFERSIZE	100						// デバイスに設定するバッファ・サイズ

//コントローラ用変数
extern	DWORD joystate[NUM_CONTROL];
extern	DWORD phisycal_joystate[NUM_CONTROL];

extern	DWORD key_assign[20];


//キーボード用変数
extern	int	kb_left;
extern	int	kb_right;
extern	int	kb_up;
extern	int	kb_down;
extern	int	kb_a;
extern	int	kb_b;
extern	int	kb_c;
extern	int	kb_d;
extern	int	kb_l;
extern	int	kb_r;

// DirectInputの変数
extern	LPDIRECTINPUT8 g_pDInput;					// DirectInput
extern	LPDIRECTINPUTDEVICE8 g_pDIDevice;			// DirectInputデバイス
extern	DIDEVCAPS g_diDevCaps;						// ジョイスティックの能力
