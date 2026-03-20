// MapEditorView.cpp : CMapEditorView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "MapEditor.h"

#include "MapEditorDoc.h"
#include "MapEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView

IMPLEMENT_DYNCREATE(CMapEditorView, CView)

BEGIN_MESSAGE_MAP(CMapEditorView, CView)
	//{{AFX_MSG_MAP(CMapEditorView)
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView クラスの構築/消滅

CMapEditorView::CMapEditorView()
{
	// TODO: この場所に構築用のコードを追加してください。
	MapPoint.x = 0;
	MapPoint.y = 0;

	MousePat = false;

	CursolBrush.CreateStockObject(HOLLOW_BRUSH);
	CursolPen.CreatePen(PS_SOLID,1,RGB(0,0,255));

	AttrPen[0].CreatePen(PS_SOLID,1,RGB(255,255,255));
	AttrPen[1].CreatePen(PS_SOLID,1,RGB(128,255,000));
	AttrPen[2].CreatePen(PS_SOLID,1,RGB(000,128,000));
	AttrPen[3].CreatePen(PS_SOLID,1,RGB(255,000,000));
	AttrPen[4].CreatePen(PS_SOLID,1,RGB(255,128,000));
	AttrPen[5].CreatePen(PS_SOLID,1,RGB(128,000,255));
	AttrPen[6].CreatePen(PS_SOLID,1,RGB(128,128,128));
	AttrPen[7].CreatePen(PS_SOLID,1,RGB(000,255,255));
	AttrPen[8].CreatePen(PS_SOLID,1,RGB(000,000,255));
	AttrPen[9].CreatePen(PS_SOLID,1,RGB(000,000,128));
	AttrPen[10].CreatePen(PS_SOLID,1,RGB(255,128,128));
	AttrPen[11].CreatePen(PS_SOLID,1,RGB(128,000,128));
	AttrPen[12].CreatePen(PS_SOLID,1,RGB(255,000,128));
	AttrPen[13].CreatePen(PS_SOLID,1,RGB(000,000,000));
	AttrPen[14].CreatePen(PS_SOLID,1,RGB(128,000,000));
	AttrPen[15].CreatePen(PS_SOLID,1,RGB(255,255,000));
	
}

CMapEditorView::~CMapEditorView()
{
}

BOOL CMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView クラスの描画

void CMapEditorView::OnDraw(CDC* pDC)
{
	CMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	int x,y;

	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	CRect clrect;

	GetClientRect(&clrect);

	pMapEditor->Scroll_Max_x = pMapEditor->SizeDialog.m_x_size - clrect.right;
	pMapEditor->Scroll_Max_y = pMapEditor->SizeDialog.m_y_size - clrect.bottom;

	SetScrollRange(SB_HORZ,0,pMapEditor->Scroll_Max_x,false);
	SetScrollRange(SB_VERT,0,pMapEditor->Scroll_Max_y,false);

	SetScrollPos(SB_HORZ,pMapEditor->ScrollPoint.x,true);
	SetScrollPos(SB_VERT,pMapEditor->ScrollPoint.y,true);

	if(clrect.right >= (long)pMapEditor->SizeDialog.m_x_size) {
		ShowScrollBar(SB_HORZ, false);		// 非表示
	} else{
		ShowScrollBar(SB_HORZ, true);		// 表示
	}
	if(clrect.bottom >= (long)pMapEditor->SizeDialog.m_y_size) {
		ShowScrollBar(SB_VERT, false);		// 非表示
	} else {
		ShowScrollBar(SB_VERT, true);		// 表示
	}


	if(pMapEditor->LoadBitmap) {
		// 表示するためにデバイスコンテキストを作成してビットマップを関係づける
		CBitmap *pbmpOld = pMapEditor->DC.SelectObject(&pMapEditor->Bitmap);
		// ＢＭＰパターンを描画
		CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
		ASSERT_VALID(pMapEditor);
		int pat, left, top;
		int	pt_y ,wk_y;
			
		wk_y = pMapEditor->SizeDialog.MAP_X;
		for(UINT y = 0; y < pMapEditor->SizeDialog.MAP_Y; y++) {
			for(UINT x = 0; x < pMapEditor->SizeDialog.MAP_X; x++) {
			// 画面にビットマップを描画する
				pt_y = y * wk_y;
				pat = pMapEditor->MapData[x + pt_y].GetMapData(x,pt_y);
				left = pat % (BITMAP_FIELD_WIDTH  / 8 );
				top  = pat / (BITMAP_FIELD_HEIGHT / 8);
				pDC->BitBlt(x * MAP_CHIP_WIDTH  - pMapEditor->ScrollPoint.x,
							y * MAP_CHIP_HEIGHT - pMapEditor->ScrollPoint.y,
							MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT,
							&pMapEditor->DC, left * MAP_CHIP_WIDTH, top * MAP_CHIP_HEIGHT, SRCCOPY);
				}
			}
			pMapEditor->DC.SelectObject(pbmpOld);
		}

	if(pMapEditor->DispAttr){
		CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
		ASSERT_VALID(pMapEditor);
		int pat;
		int	pt_y ,wk_y;

		pDC->SelectObject(CursolBrush);
		
		wk_y = pMapEditor->SizeDialog.MAP_X;
		for(y = 0; y < pMapEditor->SizeDialog.MAP_Y; y++) {
			for(x = 0; x < pMapEditor->SizeDialog.MAP_X; x++) {
				pt_y = y * wk_y;
				pat = pMapEditor->AttrData[x + pt_y].AttrData;
				if(pat == 0){
					pDC->SelectObject(AttrPen[0]);
				}
				else if(pat == 4){
					pDC->SelectObject(AttrPen[1]);
				}
				else if(pat == 8){
					pDC->SelectObject(AttrPen[2]);
				}
				else if(pat == 16){
					pDC->SelectObject(AttrPen[3]);
				}
				else if(pat == 20){
					pDC->SelectObject(AttrPen[4]);
				}
				else if(pat == 24){
					pDC->SelectObject(AttrPen[5]);
				}
				else if(pat == 1){
					pDC->SelectObject(AttrPen[6]);
				}
				else if(pat == 2){
					pDC->SelectObject(AttrPen[7]);
				}
				else if(pat == 6){
					pDC->SelectObject(AttrPen[8]);
				}
				else if(pat == 10){
					pDC->SelectObject(AttrPen[9]);
				}
				else if(pat == 18){
					pDC->SelectObject(AttrPen[10]);
				}
				else if(pat == 22){
					pDC->SelectObject(AttrPen[11]);
				}
				else if(pat == 26){
					pDC->SelectObject(AttrPen[12]);
				}
				else if(pat == 12){
					pDC->SelectObject(AttrPen[13]);
				}
				else if(pat == 28){
					pDC->SelectObject(AttrPen[14]);
				}
				else if(pat == 3){
					pDC->SelectObject(AttrPen[15]);
				}
				else{
				}

				pDC->Rectangle(x * 8 - pMapEditor->ScrollPoint.x , y * 8 - pMapEditor->ScrollPoint.y,
								(x * 8 - pMapEditor->ScrollPoint.x)+8,(y * 8 - pMapEditor->ScrollPoint.y)+8);
			}
		}		
	}

	if(pMapEditor->MainGlid){
		UINT i;


		GlidPen.CreatePen(PS_SOLID,1,RGB(pMapEditor->GlidColorDialog.m_Edit_R,pMapEditor->GlidColorDialog.m_Edit_G,pMapEditor->GlidColorDialog.m_Edit_B));

		pDC->SelectObject(GlidPen);
		for(i = 0;i < pMapEditor->SizeDialog.MAP_X;i++){
			pDC->MoveTo(pMapEditor->GlidPointX[i]);
			pDC->LineTo(pMapEditor->GlidPointX[i + pMapEditor->SizeDialog.MAP_X]);
		}
		for(i = 0;i < pMapEditor->SizeDialog.MAP_Y;i++){
			pDC->MoveTo(pMapEditor->GlidPointY[i]);
			pDC->LineTo(pMapEditor->GlidPointY[i + pMapEditor->SizeDialog.MAP_Y]);
		}
		GlidPen.DeleteObject();
	}
	
	int mx, my;
	mx = (MapPoint.x / 8 ) * 8 - pMapEditor->ScrollPoint.x;
	my = (MapPoint.y / 8 ) * 8 - pMapEditor->ScrollPoint.y;
	if(mx + pMapEditor->CSDialog.m_cursol_x >= pMapEditor->SizeDialog.m_x_size){
		mx = pMapEditor->SizeDialog.m_x_size - pMapEditor->CSDialog.m_cursol_x;
	}
	if(my + pMapEditor->CSDialog.m_cursol_y >= pMapEditor->SizeDialog.m_y_size){
 		my = pMapEditor->SizeDialog.m_y_size - pMapEditor->CSDialog.m_cursol_y;
	}
	pDC->SelectObject(CursolPen);
	pDC->SelectObject(CursolBrush);
	pDC->Rectangle(mx, my, mx + pMapEditor->CSDialog.m_cursol_x, my + pMapEditor->CSDialog.m_cursol_y);	// 矩形を描画


}


/////////////////////////////////////////////////////////////////////////////
// CMapEditorView クラスの診断

#ifdef _DEBUG
void CMapEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMapEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditorDoc* CMapEditorView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorDoc)));
	return (CMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEditorView クラスのメッセージ ハンドラ

void CMapEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
		// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください

	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	int x,y,wkx,wky,wkc;
	int loop_x,loop_y;
	MapPoint.x = point.x + pMapEditor->ScrollPoint.x;
	MapPoint.y = point.y + pMapEditor->ScrollPoint.y;

	int mx, my;
	mx = (MapPoint.x / 8 ) * 8;
	my = (MapPoint.y / 8 ) * 8;
	if(mx + pMapEditor->CSDialog.m_cursol_x >= pMapEditor->SizeDialog.m_x_size){
		mx = pMapEditor->SizeDialog.m_x_size - pMapEditor->CSDialog.m_cursol_x;
	}
	if(my + pMapEditor->CSDialog.m_cursol_y >= pMapEditor->SizeDialog.m_y_size){
 		my = pMapEditor->SizeDialog.m_y_size - pMapEditor->CSDialog.m_cursol_y;
	}

	if(	mx >= 0 && my >= 0 &&
		mx < (long)pMapEditor->SizeDialog.m_x_size && my < (long)pMapEditor->SizeDialog.m_y_size) {

		// アプリケーションオブジェクトのポインタを取得
		CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
		ASSERT_VALID(pMapEditor);
		
		// マップチップを現在のカーソル位置にセット
		x = pMapEditor->NewMapPoint.x = mx / MAP_CHIP_WIDTH;
		y = pMapEditor->NewMapPoint.y = my / MAP_CHIP_HEIGHT;

		y = y * pMapEditor->SizeDialog.MAP_X;
		x = x + y;	
		
		if(!pMapEditor->AttrMode){
			for(loop_y = 1;loop_y <= (pMapEditor->CSDialog.m_cursol_y / 8) ;loop_y++){
				for(loop_x = 1;loop_x <= (pMapEditor->CSDialog.m_cursol_x / 8) ;loop_x++){
					wky = ((loop_y - 1) * (pMapEditor->SizeDialog.MAP_X));
					wkc = (((loop_y - 1) * (BITMAP_FIELD_WIDTH / 8)) + (loop_x -1));
					wkx = wky + (loop_x -1);

					pMapEditor->MapData[x + wkx].MapData= pMapEditor->NewChipNo+wkc;
				}
			}
			// ビューを更新	
		}
		Invalidate(false);
	}
	MousePat = true;

	CView::OnLButtonDown(nFlags, point);
}
void CMapEditorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	MousePat = false;

	CView::OnLButtonUp(nFlags, point);
}

void CMapEditorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	int x,y,wkx,wky,wkc;
	int loop_x,loop_y;
	int mx, my;
	
	if(MousePat) {
		// アプリケーションオブジェクトのポインタを取得
		CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
		ASSERT_VALID(pMapEditor);

		// マウス座標の範囲チェック＆補正
		MapPoint.x = point.x + pMapEditor->ScrollPoint.x;
		MapPoint.y = point.y + pMapEditor->ScrollPoint.y;
	
		
		mx = (MapPoint.x / 8 ) * 8;
		my = (MapPoint.y / 8 ) * 8;
		if(mx + pMapEditor->CSDialog.m_cursol_x >= pMapEditor->SizeDialog.m_x_size){
			mx = pMapEditor->SizeDialog.m_x_size - pMapEditor->CSDialog.m_cursol_x;
		}
		if(my + pMapEditor->CSDialog.m_cursol_y >= pMapEditor->SizeDialog.m_y_size){
 			my = pMapEditor->SizeDialog.m_y_size - pMapEditor->CSDialog.m_cursol_y;
		}

		if(!pMapEditor->AttrMode){
			if(	mx >= 0 && my >= 0 &&
				mx < (long)pMapEditor->SizeDialog.m_x_size && my < (long)pMapEditor->SizeDialog.m_y_size) {

				// アプリケーションオブジェクトのポインタを取得
				CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
				ASSERT_VALID(pMapEditor);
			
				// マップチップを現在のカーソル位置にセット
				x = pMapEditor->NewMapPoint.x = mx / MAP_CHIP_WIDTH;
				y = pMapEditor->NewMapPoint.y = my / MAP_CHIP_HEIGHT;

				y = y * pMapEditor->SizeDialog.MAP_X;
				x = x + y;
				for(loop_y = 1;loop_y <= (pMapEditor->CSDialog.m_cursol_y / 8) ;loop_y++){
					for(loop_x = 1;loop_x <= (pMapEditor->CSDialog.m_cursol_x / 8) ;loop_x++){
						wky = ((loop_y - 1) * (pMapEditor->SizeDialog.MAP_X));
						wkc = (((loop_y - 1) * (BITMAP_FIELD_WIDTH / 8)) + (loop_x -1));
						wkx = wky + (loop_x -1);
						pMapEditor->MapData[x + wkx].MapData = pMapEditor->NewChipNo+wkc;
					}
				}
			}
		}
		Invalidate(false); // ビューを更新
	}

	CView::OnMouseMove(nFlags, point);
}

void CMapEditorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	switch(nSBCode){
		case SB_LINEUP:
		case SB_PAGEUP:
			pMapEditor->ScrollPoint.y -= 16;
			if(pMapEditor->ScrollPoint.y < 0){
				pMapEditor->ScrollPoint.y = 0;
			}
			break;

		case SB_LINEDOWN:
		case SB_PAGEDOWN:
			pMapEditor->ScrollPoint.y += 16;
			if(pMapEditor->ScrollPoint.y > pMapEditor->Scroll_Max_y){
				pMapEditor->ScrollPoint.y = pMapEditor->Scroll_Max_y;
			}
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			pMapEditor->ScrollPoint.y = (nPos / 8) * 8;
			break;
	}
	Invalidate(false);

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMapEditorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	switch(nSBCode){
		case SB_LINELEFT:
		case SB_PAGELEFT:
			pMapEditor->ScrollPoint.x -= 16;
			if(pMapEditor->ScrollPoint.x < 0){
				pMapEditor->ScrollPoint.x = 0;
			}
			break;

		case SB_LINERIGHT:
		case SB_PAGERIGHT:
			pMapEditor->ScrollPoint.x += 16;
			if(pMapEditor->ScrollPoint.x > pMapEditor->Scroll_Max_x){
				pMapEditor->ScrollPoint.x = pMapEditor->Scroll_Max_x;
			}
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			pMapEditor->ScrollPoint.x = (nPos / 8) * 8;
			break;
	}
	Invalidate(false);

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMapEditorView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int x,y,wkx,wky;
	int loop_x,loop_y;
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	MapPoint.x = point.x + pMapEditor->ScrollPoint.x;
	MapPoint.y = point.y + pMapEditor->ScrollPoint.y;

	int mx, my;
	mx = (MapPoint.x / 8 ) * 8;
	my = (MapPoint.y / 8 ) * 8;
	if(mx + pMapEditor->CSDialog.m_cursol_x >= pMapEditor->SizeDialog.m_x_size){
		mx = pMapEditor->SizeDialog.m_x_size - pMapEditor->CSDialog.m_cursol_x;
	}
	if(my + pMapEditor->CSDialog.m_cursol_y >= pMapEditor->SizeDialog.m_y_size){
 		my = pMapEditor->SizeDialog.m_y_size - pMapEditor->CSDialog.m_cursol_y;
	}


	x = pMapEditor->NewMapPoint.x = MapPoint.x / MAP_CHIP_WIDTH;
	y = pMapEditor->NewMapPoint.y = MapPoint.y / MAP_CHIP_HEIGHT;

	y = y * pMapEditor->SizeDialog.MAP_X;
	x = x + y;
	Invalidate(false);


	for(loop_y = 1;loop_y <= (pMapEditor->CSDialog.m_cursol_y / 8) ;loop_y++){
		for(loop_x = 1;loop_x <= (pMapEditor->CSDialog.m_cursol_x / 8) ;loop_x++){
			wky = ((loop_y - 1) * (pMapEditor->SizeDialog.MAP_X));
			wkx = wky + (loop_x -1);
		
			pMapEditor->AttrData[x + wkx].AttrData = pMapEditor->DataDialog.data;
			pMapEditor->MapData[x + wkx].Palette = pMapEditor->DataDialog.m_palet;

		}
	}

	Invalidate(false);

	CView::OnRButtonDown(nFlags, point);
}


