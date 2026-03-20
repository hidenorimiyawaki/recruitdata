// SpriteToolView.cpp : CSpriteToolView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "SpriteTool.h"

#include "SpriteToolDoc.h"
#include "SpriteToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolView

IMPLEMENT_DYNCREATE(CSpriteToolView, CView)

BEGIN_MESSAGE_MAP(CSpriteToolView, CView)
	//{{AFX_MSG_MAP(CSpriteToolView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolView クラスの構築/消滅

CSpriteToolView::CSpriteToolView()
{
	// TODO: この場所に構築用のコードを追加してください。

}

CSpriteToolView::~CSpriteToolView()
{
}

BOOL CSpriteToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolView クラスの描画

void CSpriteToolView::OnDraw(CDC* pDC)
{
	CSpriteToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolView クラスの診断

#ifdef _DEBUG
void CSpriteToolView::AssertValid() const
{
	CView::AssertValid();
}

void CSpriteToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpriteToolDoc* CSpriteToolView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpriteToolDoc)));
	return (CSpriteToolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolView クラスのメッセージ ハンドラ

void CSpriteToolView::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->draw_flg = 1;
	// 描画用メッセージとして CView::OnPaint() を呼び出してはいけません
}

void CSpriteToolView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->lbutton = true;
	pApp->start = point;
	pApp->now = point;

	if(pApp->start.x < 128) pApp->start.x = 128;
	if(pApp->start.y < 0) pApp->start.y = 0;

	if(pApp->start.x >= (float)(pApp->Dx.mainbord.ita.Width + 128)) pApp->start.x = pApp->Dx.mainbord.ita.Width + 128;
	if(pApp->start.y >= (float)(pApp->Dx.mainbord.ita.Height)) pApp->start.y = pApp->Dx.mainbord.ita.Height;

	if(pApp->SnapFlg == ON){
		if((pApp->start.x % pApp->GLID_WIDTH) <= pApp->GLID_WIDTH / 2) pApp->start.x = (pApp->start.x / pApp->GLID_WIDTH) * pApp->GLID_WIDTH;
		else{
			pApp->start.x = ((pApp->start.x / pApp->GLID_WIDTH) + 1) * pApp->GLID_WIDTH;
		}
		if((pApp->start.y % pApp->GLID_HEIGHT) <= pApp->GLID_HEIGHT /2) pApp->start.y = (pApp->start.y / pApp->GLID_HEIGHT) * pApp->GLID_HEIGHT;
		else {
			pApp->start.y = ((pApp->start.y / pApp->GLID_HEIGHT) + 1) * pApp->GLID_HEIGHT;
		}
	}

	pApp->end = pApp->now = pApp->start;

	pApp->Dx.workbord.texRect.top = pApp->start.y;
	pApp->Dx.workbord.texRect.left = pApp->start.x -128;
	pApp->Dx.workbord.texRect.bottom = pApp->end.y;
	pApp->Dx.workbord.texRect.right = pApp->end.x -128;

	pApp->Dx.mainbord.texRect.top = 0;
	pApp->Dx.mainbord.texRect.left = 0;
	pApp->Dx.mainbord.texRect.bottom = pApp->Dx.mainbord.ita.Height;
	pApp->Dx.mainbord.texRect.right = pApp->Dx.mainbord.ita.Width;

	RectDraw();

	SIZE	linesize;
	linesize.cx = 1;
	linesize.cy = 1;
	CRect 	rect(pApp->start.x,pApp->start.y,point.x,point.y);
	CDC *pDC;															// デバイスコンテキスト用の取得用変数作成
	pDC = GetDC();														// デバイスコンテキスト取得
	memDC.BitBlt(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,pDC,0,0,SRCCOPY);
	ReleaseDC(pDC);														// デバイスコンテキスト開放
	memDC.DrawDragRect( rect, linesize, NULL, linesize,&pApp->CursolBrush,&pApp->CursolBrush);

	Invalidate(false);
	
	CView::OnLButtonDown(nFlags, point);
}

void CSpriteToolView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->lbutton = false;

	if(pApp->SnapFlg == ON){
		if((pApp->start.x % pApp->GLID_WIDTH)!= 0)  pApp->start.x = (pApp->start.x / pApp->GLID_WIDTH) * pApp->GLID_WIDTH; 
		if((pApp->start.y % pApp->GLID_HEIGHT)!= 0)  pApp->start.y = (pApp->start.y / pApp->GLID_HEIGHT) * pApp->GLID_HEIGHT; 
		if((pApp->end.x % pApp->GLID_WIDTH)!= 0)  pApp->end.x = (pApp->end.x / pApp->GLID_WIDTH) * pApp->GLID_WIDTH; 
		if((pApp->end.y % pApp->GLID_HEIGHT)!= 0)  pApp->end.y = (pApp->end.y / pApp->GLID_HEIGHT) * pApp->GLID_HEIGHT; 
	}

	if(((pApp->start.x != pApp->end.x) && (pApp->start.y != pApp->end.y)) && pApp->fileload == ON){
		if(	pApp->CashDialog.m_List_Cash.GetCurSel() == 0 && pApp->cash_cnt < CASH_MAX){
			CString		work;
			pApp->cash_data[pApp->cash_cnt].top = pApp->start.y;
			pApp->cash_data[pApp->cash_cnt].left = pApp->start.x;
			pApp->cash_data[pApp->cash_cnt].bottom = pApp->end.y;
			pApp->cash_data[pApp->cash_cnt].right = pApp->end.x;

			work.Format("%d:矩形(%d,%d,%d,%d) // %s",pApp->cash_cnt+1,(int)pApp->cash_data[pApp->cash_cnt].left -128,(int)pApp->cash_data[pApp->cash_cnt].top,(int)pApp->cash_data[pApp->cash_cnt].right -128,
						(int)pApp->cash_data[pApp->cash_cnt].bottom,pApp->cash_string[pApp->cash_cnt]);
			pApp->CashDialog.m_List_Cash.InsertString(pApp->cash_cnt + 1,work);
			pApp->cash_cnt++;

		}
	}
	CDC *pDC;															// デバイスコンテキスト用の取得用変数作成
	pDC = GetDC();														// デバイスコンテキスト取得	

	pApp->Dx.workbord.texRect.top = pApp->start.y;
	pApp->Dx.workbord.texRect.left = pApp->start.x -128;
	pApp->Dx.workbord.texRect.bottom = pApp->end.y;
	pApp->Dx.workbord.texRect.right = pApp->end.x -128;
	pApp->Dx.WorkRender();
	pApp->CashDialog.memDC.BitBlt(0,0,180,180,pDC,466,330,SRCCOPY);
	pApp->CashDialog.DrawExec();
	ReleaseDC(pDC);														// デバイスコンテキスト開放

	RectDraw();

	if(pApp->SnapFlg == ON){
		if((float)(pApp->start.x % pApp->GLID_WIDTH)>= (float)(pApp->Dx.mainbord.ita.Width % pApp->GLID_WIDTH))  pApp->start.x = pApp->Dx.mainbord.ita.Width % pApp->GLID_WIDTH; 
		if((float)(pApp->start.y % pApp->GLID_HEIGHT)>= (float)(pApp->Dx.mainbord.ita.Height % pApp->GLID_HEIGHT))  pApp->start.y = pApp->Dx.mainbord.ita.Height % pApp->GLID_HEIGHT; 
		if((float)(pApp->end.x % (pApp->GLID_WIDTH * 16))>= (float)(pApp->Dx.mainbord.ita.Width % pApp->GLID_WIDTH))  pApp->end.x = pApp->Dx.mainbord.ita.Width % pApp->GLID_WIDTH; 
		if((float)(pApp->end.y % (pApp->GLID_HEIGHT * 16))>= (float)(pApp->Dx.mainbord.ita.Height % pApp->GLID_HEIGHT))  pApp->end.y = pApp->Dx.mainbord.ita.Height % pApp->GLID_HEIGHT; 
	}

	CView::OnLButtonUp(nFlags, point);
}

void CSpriteToolView::RectDraw()
{
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->Dx.mainbord.texRect.top = 0;
	pApp->Dx.mainbord.texRect.left = 0;
	pApp->Dx.mainbord.texRect.bottom = pApp->Dx.mainbord.ita.Height;
	pApp->Dx.mainbord.texRect.right = pApp->Dx.mainbord.ita.Width;

	pApp->DrawExec();

}

void CSpriteToolView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	if(pApp->lbutton == (int)true){
		pApp->end = point;
		if(pApp->end.x >= (float)(pApp->Dx.mainbord.ita.Width + 128)) pApp->end.x = pApp->Dx.mainbord.ita.Width + 128;
		if(pApp->end.y >= (float)(pApp->Dx.mainbord.ita.Height)) pApp->end.y = pApp->Dx.mainbord.ita.Height;

		if(pApp->end.x < 128) pApp->end.x = 128;
		if(pApp->end.y < 0) pApp->end.y = 0;

		if(pApp->SnapFlg == ON){

			if((point.x % pApp->GLID_WIDTH) <= (pApp->GLID_WIDTH / 2) -1) pApp->end.x = (pApp->end.x / pApp->GLID_WIDTH) * pApp->GLID_WIDTH;
			else{
				pApp->end.x = ((pApp->end.x / pApp->GLID_WIDTH) + 1) * pApp->GLID_WIDTH;
			}
			if((point.y % pApp->GLID_HEIGHT) <= (pApp->GLID_HEIGHT / 2) -1) pApp->end.y = (pApp->end.y / pApp->GLID_HEIGHT) * pApp->GLID_HEIGHT;
			else {
				pApp->end.y = ((pApp->end.y / pApp->GLID_HEIGHT) + 1) * pApp->GLID_HEIGHT;
			}
			if((pApp->start.x % pApp->GLID_WIDTH)!= 0)  pApp->start.x = (pApp->start.x / pApp->GLID_WIDTH) * pApp->GLID_WIDTH; 
			if((pApp->start.y % pApp->GLID_HEIGHT)!= 0)  pApp->start.y = (pApp->start.y / pApp->GLID_HEIGHT) * pApp->GLID_HEIGHT; 
			if((pApp->end.x % pApp->GLID_WIDTH)!= 0)  pApp->end.x = (pApp->end.x / pApp->GLID_WIDTH) * pApp->GLID_WIDTH; 
			if((pApp->end.y % pApp->GLID_HEIGHT)!= 0)  pApp->end.y = (pApp->end.y / pApp->GLID_HEIGHT) * pApp->GLID_HEIGHT; 
		}

		
		SIZE	linesize;
		linesize.cx = 1;
		linesize.cy = 1;
		CRect 	rect(pApp->start.x,pApp->start.y,pApp->now.x,pApp->now.y);
		CRect	oldRect(pApp->start.x,pApp->start.y,pApp->end.x,pApp->end.y);

		memDC.DrawDragRect( rect, linesize, oldRect, linesize,NULL,NULL);

		Invalidate(false);

		pApp->now = pApp->end;
	}
	pApp->work = point;
	
	CView::OnMouseMove(nFlags, point);
}

int CSpriteToolView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CDC *pDC;															// デバイスコンテキスト用の取得用変数作成
	pDC = GetDC();														// デバイスコンテキスト取得
	memDC.CreateCompatibleDC(pDC);										// 仮想画面用メンバ変数(メモリDC)に描画許可設定	
	Bitmap.CreateCompatibleBitmap(pDC,SCREEN_WIDTH,SCREEN_HEIGHT);		// 仮想ビットマップ領域作成
	memDC.SelectObject(&Bitmap);										// メモリDCに仮想ビットマップ領域を関連付け
	memDC.ExtFloodFill(0,0,RGB(0,0,0),FLOODFILLSURFACE);				// メモリDCを白で初期化
	memDC.SelectObject(pApp->CursolBrush);
	ReleaseDC(pDC);														// デバイスコンテキスト開放
	
	return 0;
}
