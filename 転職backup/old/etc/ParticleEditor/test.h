// test.h : test アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"       // メイン シンボル
#include "EditDialog.h"
#include "SetColorDialog.h"

// CtestApp:
// このクラスの実装については、test.cpp を参照してください。
//

class CtestApp : public CWinApp
{
public:
	CtestApp();
	CDirectX direct_x;
	CBillbord* billbord;
	CParticle* particle;
	int end_check;
	int play_flg;
	UINT frame_count;
	UINT bftime;
	int time;
	CString filename;
	bool fileload;
	bool drawflg;
	bool captureflg;
	CEditDialog EditDialog;
	CSetColorDialog ColorDialog;
	POSITION4 pos;
	FLG4	posflg;
	POSITION4 rot;
	FLG4	rotflg;
	POSITION4 scale;
	FLG4	scaleflg;
	float		dir;
	float	gravity;

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	afx_msg void OnSetColorA();
	afx_msg void OnSetColorB();
};

extern CtestApp theApp;
