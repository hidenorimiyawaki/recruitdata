// particleediterView.cpp : CparticleediterView クラスの実装
//

#include "stdafx.h"
#include "particleediter.h"

#include "particleediterDoc.h"
#include "particleediterView.h"
#include ".\particleediterview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CparticleediterView

IMPLEMENT_DYNCREATE(CparticleediterView, CView)

BEGIN_MESSAGE_MAP(CparticleediterView, CView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CparticleediterView コンストラクション/デストラクション

CparticleediterView::CparticleediterView()
: R_Button(false)
, L_Button(false)
{
	// TODO: 構築コードをここに追加します。

}

CparticleediterView::~CparticleediterView()
{
}

BOOL CparticleediterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CparticleediterView 描画

void CparticleediterView::OnDraw(CDC* /*pDC*/)
{
	CparticleediterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CparticleediterView 診断

#ifdef _DEBUG
void CparticleediterView::AssertValid() const
{
	CView::AssertValid();
}

void CparticleediterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CparticleediterDoc* CparticleediterView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CparticleediterDoc)));
	return (CparticleediterDoc*)m_pDocument;
}
#endif //_DEBUG


// CparticleediterView メッセージ ハンドラ

void CparticleediterView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO : ここにメッセージ ハンドラ コードを追加します。
	// 描画メッセージで CView::OnPaint() を呼び出さないでください。

	SetTimer(1,FRAME_RATE,NULL);

}

void CparticleediterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	PointL = point;
	L_Button = true;

	CView::OnLButtonDown(nFlags, point);
}

void CparticleediterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	L_Button = false;

	CView::OnLButtonUp(nFlags, point);
}

void CparticleediterView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	PointR = point;
	R_Button = true;

	CView::OnRButtonDown(nFlags, point);
}

void CparticleediterView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	R_Button = false;

	CView::OnRButtonUp(nFlags, point);
}

void CparticleediterView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	int	dx, dy;

	// アプリケーションオブジェクトのポインタを取得
	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	// 左ボタンプッシュ
	if(L_Button) {
		dx = point.x - PointL.x;
		dy = point.y - PointL.y;
		PointL = point;
		pApp->direct_x.camera.AddOffset((float)dx, (float)dy);	// カメラのオフセットを設定

	}

	// 右ボタンプッシュ
	if(R_Button) {
		dx = point.x - PointR.x;
		dy = point.y - PointR.y;
		PointR = point;
		pApp->direct_x.camera.SetCameraValue(-dy, dx, 0);	// カメラ位置を設定

	}
	CView::OnMouseMove(nFlags, point);
}

BOOL CparticleediterView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	pApp->direct_x.camera.SetCameraValue(0, 0, zDelta);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CparticleediterView::OnTimer(UINT nIDEvent)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);


	pApp->direct_x.Render();				// レンダリング

	CView::OnTimer(nIDEvent);
}
