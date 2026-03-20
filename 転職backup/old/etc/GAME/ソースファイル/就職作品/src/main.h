/************************************************************
*						MAIN.H								*
*															*
*	このファイルでは、ヘッダーファイルの読み込みをします。	*
*															*
*															*
************************************************************/
#ifndef  __ALL_HEADER__
#define  __ALL_HEADER__

//-------- ライブラリのリンク
#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//-------- ヘッダ
#include <windows.h>		// Windowsプログラム
#include <d3d8.h>			// DirectX Graphics 関連のヘッダー
#include <d3dx8.h>			// DirectX Graphics 関連のヘッダー
#include <D3d8types.h>
#include <stdio.h>			// 文字列処理で使用
#include <mmsystem.h>		// 時間管理で使用

#include <dmusici.h>
#include <Dxerr8.h>

#include <objbase.h>
#include <malloc.h>
#include <stdio.h>

//-------- 自作ヘッダ
#include "define.h"
#include "typedef.h"
#include "macro.h"
#include "bg.h"
#include "billbord.h"
#include "model.h"
#include "music.h"
#include "tama.h"
#include "enemy.h"
#include "player.h"
#include "skinmodel.h"
#include "ModelManager.h"
#include "Parts.h"
#include "Zintai.h"

#endif


