// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__D947225A_F87B_4D94_A7E9_758D62F0356F__INCLUDED_)
#define AFX_STDAFX_H__D947225A_F87B_4D94_A7E9_758D62F0356F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <windows.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <stdio.h>
#include <mmsystem.h>

#include "Define.h"
#include "Data.h"

#include "Camera.h"
#include "DirectX.h"

#include "Model.h"
#include "ModelManager.h"
#include "Parts.h"
#include "Zintai.h"

#include "Resource.h"

#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__D947225A_F87B_4D94_A7E9_758D62F0356F__INCLUDED_)
