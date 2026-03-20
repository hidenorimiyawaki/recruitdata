#include "key.h"

//コントローラ用変数
 	DWORD joystate[NUM_CONTROL];
 	DWORD	phisycal_joystate[NUM_CONTROL];

 	DWORD key_assign[20];


//キーボード用変数
 	int	kb_left;
 	int	kb_right;
 	int	kb_up;
 	int	kb_down;
 	int	kb_a;
 	int	kb_b;
 	int	kb_c;
 	int	kb_d;
 	int	kb_l;
 	int	kb_r;

// DirectInputの変数
 	LPDIRECTINPUT8 g_pDInput;					// DirectInput
 	LPDIRECTINPUTDEVICE8 g_pDIDevice;			// DirectInputデバイス
 	DIDEVCAPS g_diDevCaps;						// ジョイスティックの能力

//これらはDInput初期化に使用
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);


//************************************************
//DInput初期化
//返り値
//成功：true
//失敗：false
//************************************************
bool InitDInput(HINSTANCE app_hinst,HWND app_hwnd)
{
	HRESULT hr;

	// *****************************************
	// DirectInputの作成
	hr = DirectInput8Create(app_hinst, DIRECTINPUT_VERSION, 
							IID_IDirectInput8, (void**)&g_pDInput, NULL); 
	if (FAILED(hr)) 
	{
		return false;
	}

	// デバイスを列挙して作成
	hr = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
							NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr) || g_pDIDevice==NULL)
	{
		return false;
	}
 
	// データ形式を設定
	hr = g_pDIDevice->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(hr))
	{
		return false;
	}

	//モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevice->SetCooperativeLevel(app_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		return false;
	}

	// コールバック関数を使って各軸のモードを設定
	hr = g_pDIDevice->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS);
	if (FAILED(hr))
	{
		return false;
	}

	// 軸モードを設定（絶対値モードに設定。デフォルトなので必ずしも設定は必要ない）
	DIPROPDWORD diprop;
	diprop.diph.dwSize	= sizeof(diprop); 
	diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
	diprop.diph.dwObj	= 0;
	diprop.diph.dwHow	= DIPH_DEVICE;
	diprop.dwData		= DIPROPAXISMODE_ABS;
//	diprop.dwData		= DIPROPAXISMODE_REL;	// 相対値モードの場合
	hr = g_pDIDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(hr))
	{
		return false;
	}

	// バッファリング・データを取得するため、バッファ・サイズを設定
	diprop.dwData = DIDEVICE_BUFFERSIZE;
	hr = g_pDIDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
	if (FAILED(hr))
	{
		return false;
	}

	// 入力制御開始
	g_pDIDevice->Acquire();

	key_assign[0] = KEY_A;
	key_assign[1] = KEY_B;
	key_assign[2] = KEY_C;
	key_assign[3] = KEY_D;
	return true;
}

//************************************************
// ジョイスティックを列挙する関数
//返り値
//成功：true
//失敗：false
//************************************************
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;

	// 列挙されたジョイスティックへのインターフェイスを取得する。
	hr = g_pDInput->CreateDevice(pdidInstance->guidInstance, &g_pDIDevice, NULL);
	if (FAILED(hr)) 
		return DIENUM_CONTINUE;

	// ジョイスティックの能力を調べる
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDevice->GetCapabilities(&g_diDevCaps);
	if (FAILED(hr))
	{
		// ジョイスティック能力の取得に失敗
		SAFE_RELEASE(g_pDIDevice);
		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

// ジョイスティックの軸を列挙する関数
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;

	// 軸の値の範囲を設定（-1000～1000）
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize	= sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwObj	= lpddoi->dwType;
	diprg.diph.dwHow	= DIPH_BYID;
	diprg.lMin	= -1000;
	diprg.lMax	= +1000;
	hr = g_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	if (FAILED(hr))
		return DIENUM_STOP;

	return DIENUM_CONTINUE;
}

/*-------------------------------------------
	DirectInputの解放処理
--------------------------------------------*/
void ReleaseDInput(void)
{
	// DirectInputのデバイスを解放
	if (g_pDIDevice)
		g_pDIDevice->Unacquire(); 
	SAFE_RELEASE(g_pDIDevice);
	SAFE_RELEASE(g_pDInput);

}

//************************************************
//キーボードの状態取得
//************************************************
void KeyManager(){
	phisycal_joystate[0] =0;
	joystate[0] = 0;
	if (g_pDIDevice!=NULL)
	{
		HRESULT hr;
		int y = 0;

		hr = g_pDIDevice->Poll();
		if (FAILED(hr))
		{
			hr = g_pDIDevice->Acquire();
			while (hr==DIERR_INPUTLOST)
				hr = g_pDIDevice->Acquire();
		}

		DIJOYSTATE2 dijs;
		hr = g_pDIDevice->GetDeviceState(sizeof(DIJOYSTATE2), &dijs);
		if (SUCCEEDED(hr))
		{
			if (dijs.lX < 0){
				joystate[0] |= KEY_LEFT;
			}
			if (dijs.lX > 0){
				joystate[0] |= KEY_RIGHT;
			}
			if (dijs.lY < 0){
				joystate[0] |= KEY_UP;
			}
			if (dijs.lY > 0){
				joystate[0] |= KEY_DOWN;
			}
			for (int i = 0;i<NUM_BUTTON;i++){
				if(dijs.rgbButtons[i] & 0x80){
					joystate[0] |= key_assign[i];
					phisycal_joystate[0] |= (1<<i);
				}
			}
		}
		else if (hr==DIERR_INPUTLOST)
			g_pDIDevice->Acquire();
	}
	if (kb_left)	joystate[0] |= KEY_LEFT;
	if (kb_right)	joystate[0] |= KEY_RIGHT;
	if (kb_up)		joystate[0] |= KEY_UP;
	if (kb_down)	joystate[0] |= KEY_DOWN;
	if (kb_a)		joystate[0] |= KEY_A;
	if (kb_b)		joystate[0] |= KEY_B;
	if (kb_c)		joystate[0] |= KEY_C;
	if (kb_l)		joystate[0] |= KEY_L;
	if (kb_r)		joystate[0] |= KEY_R;

}
