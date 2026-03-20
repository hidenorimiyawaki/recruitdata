// MainFrm.cpp : CMainFrame クラスの実装
//

#include "stdafx.h"
#include "particleediter.h"
#include "Define.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
END_MESSAGE_MAP()


// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()
{
	// TODO: メンバ初期化コードをここに追加してください。
}

CMainFrame::~CMainFrame()
{
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。
    cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER;
    cs.cx    = SCREEN_WIDTH  + GetSystemMetrics(SM_CXFIXEDFRAME) * 2; 
    cs.cy    = SCREEN_HEIGHT + GetSystemMetrics(SM_CYFIXEDFRAME) * 2
							 + GetSystemMetrics(SM_CYCAPTION)
							 + GetSystemMetrics(SM_CYMENU);
    cs.x     = 0;
    cs.y     = 0; 

	return TRUE;
}


// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame メッセージ ハンドラ

