// Zintai.cpp: CZintai クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MothionEditor.h"
#include "Zintai.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CZintai::CZintai()
{
	cur_parts = 0;
	for(int i = 0; i < PARTS_QTY; i++) {
		parts[i] = new CParts(i);
	}
}

CZintai::~CZintai()
{
	for(int i = 0; i < PARTS_QTY; i++) {
		delete parts[i];
	}
}

void CZintai::Draw()		// 描画
{
	for(int i = 0; i < PARTS_QTY; i++) {
		parts[i]->Draw((i == cur_parts)? true: false);
	}
}

void CZintai::ResetData()
{
	for(int i = 0; i < PARTS_QTY; i++) {
		parts[i]->SetInitialData(i);		// データの再セット
	}
	for(int j = 0; j < BANK_QTY; j++) {
		for(int k = 0; k < FRAME_QTY; k++) {
			frame[j][k].time = 0;
			frame[j][k].attr = 0;
		}
	}
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);
}
