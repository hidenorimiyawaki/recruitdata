// ChildFrm.cpp : CChildFrame クラスの実装
//
#include "stdafx.h"
#include "test.h"

#include "ChildFrm.h"
#include ".\childfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CChildFrame コンストラクション/デストラクション

CChildFrame::CChildFrame()
: R_Button(false)
, L_Button(false)
{
	// TODO: メンバ初期化コードをここに追加してください。
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs を変更して、Window クラスまたはスタイルを変更します。
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME;

    cs.cx    = SCREEN_WIDTH  + GetSystemMetrics(SM_CXFIXEDFRAME) * 2; 
    cs.cy    = SCREEN_HEIGHT + GetSystemMetrics(SM_CYFIXEDFRAME) * 2
							 + GetSystemMetrics(SM_CYCAPTION)
							 + GetSystemMetrics(SM_CYMENU);
    cs.x     = 50;
    cs.y     = 50;


	return TRUE;
}


// CChildFrame 診断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame メッセージ ハンドラ

void CChildFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO : ここにメッセージ ハンドラ コードを追加します。
	// 描画メッセージで CMDIChildWnd::OnPaint() を呼び出さないでください。
	SetTimer(1,FRAME_RATE,NULL);
}

void CChildFrame::OnTimer(UINT nIDEvent)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	pApp->direct_x.Render();

	POINT pt;
	GetCursorPos(&pt);

	RECT rect;
	GetWindowRect(&rect);

	if(!pApp->captureflg){
		if((rect.left+GetSystemMetrics(SM_CYFIXEDFRAME)*2 <= pt.x && rect.right-GetSystemMetrics(SM_CYFIXEDFRAME)*2 >= pt.x)
			&&(rect.top + GetSystemMetrics(SM_CYCAPTION)*2 <= pt.y && rect.bottom-GetSystemMetrics(SM_CYFIXEDFRAME)*2 >= pt.y)){
			SetCapture();
			SetFocus();
			capture = true;
		}
		else {
			if(capture){
				if(!L_Button&&!R_Button){
					ReleaseCapture();
					capture = false;
				}
			}
		}
	}
	else {
		if(capture)	{
			ReleaseCapture();
			capture = false;
		}
	}
	SetWindowText("プレビュー");

	CMDIChildWnd::OnTimer(nIDEvent);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO :  ここに特定な作成コードを追加してください。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	if(pApp->direct_x.Initialize(m_hWnd) != S_OK) return 1;

	SetTimer(1,FRAME_RATE,NULL);

	capture = false;

	return 0;
}

void CChildFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	PointL = point;
	L_Button = true;

	CMDIChildWnd::OnLButtonDown(nFlags, point);
}

void CChildFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	L_Button = false;

	CMDIChildWnd::OnLButtonUp(nFlags, point);
}

void CChildFrame::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	PointR = point;
	R_Button = true;

	CMDIChildWnd::OnRButtonDown(nFlags, point);
}

void CChildFrame::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	R_Button = false;

	CMDIChildWnd::OnRButtonUp(nFlags, point);
}

void CChildFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	int	dx, dy;

	// アプリケーションオブジェクトのポインタを取得
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	// 左ボタンプッシュ
	if(L_Button) {
		dx = point.x - PointL.x;
		dy = point.y - PointL.y;
		PointL = point;
		pApp->direct_x.camera.SetCameraValue(-dy, dx, 0);	// カメラ位置を設定

	}

	// 右ボタンプッシュ
	if(R_Button) {
		dx = point.x - PointR.x;
		dy = point.y - PointR.y;
		PointR = point;
		pApp->direct_x.camera.AddOffset((float)dx, (float)dy);	// カメラのオフセットを設定
	}
	CMDIChildWnd::OnMouseMove(nFlags, point);
}

BOOL CChildFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	pApp->direct_x.camera.SetCameraValue(0, 0, zDelta);

	return CMDIChildWnd::OnMouseWheel(nFlags, zDelta, pt);
}

