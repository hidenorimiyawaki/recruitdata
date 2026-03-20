// MothionEditorView.cpp : CMothionEditorView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "MothionEditor.h"

#include "MothionEditorDoc.h"
#include "MothionEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorView

IMPLEMENT_DYNCREATE(CMothionEditorView, CView)

BEGIN_MESSAGE_MAP(CMothionEditorView, CView)
	//{{AFX_MSG_MAP(CMothionEditorView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorView クラスの構築/消滅

CMothionEditorView::CMothionEditorView()
{
	// TODO: この場所に構築用のコードを追加してください。
	L_Button = false;
	R_Button = false;

}

CMothionEditorView::~CMothionEditorView()
{
}

BOOL CMothionEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorView クラスの描画

void CMothionEditorView::OnDraw(CDC* pDC)
{
	CMothionEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorView クラスの診断

#ifdef _DEBUG
void CMothionEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMothionEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMothionEditorDoc* CMothionEditorView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMothionEditorDoc)));
	return (CMothionEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorView クラスのメッセージ ハンドラ

void CMothionEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	PointL = point;
	L_Button = true;
	
	CView::OnLButtonDown(nFlags, point);
}

void CMothionEditorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	L_Button = false;
	
	CView::OnLButtonUp(nFlags, point);
}

void CMothionEditorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	int	dx, dy;

	// アプリケーションオブジェクトのポインタを取得
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
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
	CView::OnMouseMove(nFlags, point);
}

BOOL CMothionEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	pApp->direct_x.camera.SetCameraValue(0, 0, zDelta);
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMothionEditorView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	R_Button = false;
	
	CView::OnRButtonUp(nFlags, point);
}

void CMothionEditorView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	PointR = point;
	R_Button = true;
	
	CView::OnRButtonDown(nFlags, point);
}
