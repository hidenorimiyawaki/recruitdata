// particleediter.h : particleediter アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"       // メイン シンボル

#include "EditDialog.h"

// CparticleediterApp:
// このクラスの実装については、particleediter.cpp を参照してください。
//

class CparticleediterApp : public CWinApp
{
public:
	CparticleediterApp();
	UINT frame_count;
	UINT bftime;
	UINT time;
	CDirectX direct_x;
	int end_check;
	int play_flg;
	CEditDialog EditDialog;
	CBillbord* billbord;
	CParticle* particle;

// オーバーライド
public:
	virtual BOOL InitInstance();
	void DrawExec();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
	virtual int ExitInstance();
};

extern CparticleediterApp theApp;
