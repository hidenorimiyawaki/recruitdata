// VectorSetToolView.cpp : CVectorSetToolView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "VectorSetTool.h"

#include "VectorSetToolDoc.h"
#include "VectorSetToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolView

IMPLEMENT_DYNCREATE(CVectorSetToolView, CView)

BEGIN_MESSAGE_MAP(CVectorSetToolView, CView)
	//{{AFX_MSG_MAP(CVectorSetToolView)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolView クラスの構築/消滅

CVectorSetToolView::CVectorSetToolView()
{
	// TODO: この場所に構築用のコードを追加してください。
	L_Button = false;
	R_Button = false;

}

CVectorSetToolView::~CVectorSetToolView()
{
}

BOOL CVectorSetToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolView クラスの描画

void CVectorSetToolView::OnDraw(CDC* pDC)
{
	CVectorSetToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolView クラスの診断

#ifdef _DEBUG
void CVectorSetToolView::AssertValid() const
{
	CView::AssertValid();
}

void CVectorSetToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVectorSetToolDoc* CVectorSetToolView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVectorSetToolDoc)));
	return (CVectorSetToolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolView クラスのメッセージ ハンドラ

void CVectorSetToolView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	L_Button = false;
	pApp->NowPoint = point;
	if(pApp->Point_flg == 0){
		if(pApp->point_cnt < MAX_DATA){
			pApp->point[pApp->point_cnt].x = point.x + pApp->camera_offset_x;

			if(pApp->SnapFlg == ON && pApp->point_cnt != 0){
				pApp->point[pApp->point_cnt].y = pApp->point[pApp->point_cnt-1].y;
			}else{
				pApp->point[pApp->point_cnt].y = point.y + pApp->camera_offset_y;
			}
			PointL = point;
		}
		pApp->point_cnt++;
	}
	if(pApp->Point_flg == 3){
		if(pApp->object_flg == 0 || pApp->shift_flg == 1){
			if(pApp->ballon_point_cnt < MAX_DATA){
				pApp->ballon_point[pApp->ballon_point_cnt].x = point.x + pApp->camera_offset_x;

				if(pApp->SnapFlg == ON && pApp->ballon_point_cnt != 0){
					pApp->ballon_point[pApp->ballon_point_cnt].y = pApp->ballon_point[pApp->ballon_point_cnt-1].y;
				}else{
					pApp->ballon_point[pApp->ballon_point_cnt].y = point.y + pApp->camera_offset_y;
				}
				PointL = point;
			}
			pApp->ballon_point_cnt++;
		}
		if(pApp->object_flg == 1 || pApp->cnt_flg == 1){
			if(pApp->drum_point_cnt < MAX_DATA){
				pApp->drum_point[pApp->drum_point_cnt].x = point.x + pApp->camera_offset_x;

				if(pApp->SnapFlg == ON && pApp->drum_point_cnt != 0){
					pApp->drum_point[pApp->drum_point_cnt].y = pApp->drum_point[pApp->drum_point_cnt-1].y;
				}else{
					pApp->drum_point[pApp->drum_point_cnt].y = point.y + pApp->camera_offset_y;
				}
				PointL = point;
			}
			pApp->drum_point_cnt++;
		}

	}

	pApp->draw_flg = 1;
	
	CView::OnLButtonUp(nFlags, point);
}

void CVectorSetToolView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	PointL = pApp->NowPoint = point;
	if(pApp->Point_flg == 1 || pApp->Point_flg == 2){
		for(int i = 0;i < MAX_DATA-1;i++){
			if(((pApp->point[i].x - 10 < point.x + pApp->camera_offset_x)&&(pApp->point[i].y - 10 < point.y + pApp->camera_offset_y))&&
				((pApp->point[i].x + 10 > point.x + pApp->camera_offset_x)&&(pApp->point[i].y + 10 > point.y + pApp->camera_offset_y))){
					pApp->Point_Cheker = i;
					i = MAX_DATA;
			}
		}
	}
	if(pApp->Point_flg == 4 || pApp->Point_flg == 5){
		if(pApp->object_flg == 0 || pApp->shift_flg == 1){
			for(int i = 0;i < MAX_DATA-1;i++){
				if(((pApp->ballon_point[i].x - 10 < point.x + pApp->camera_offset_x)&&(pApp->ballon_point[i].y - 10 < point.y + pApp->camera_offset_y))&&
					((pApp->ballon_point[i].x + 10 > point.x + pApp->camera_offset_x)&&(pApp->ballon_point[i].y + 10 > point.y + pApp->camera_offset_y))){
						pApp->ballon_Point_Cheker = i;
						i = MAX_DATA;
				}
			}
		}
		else if(pApp->object_flg == 1 || pApp->cnt_flg == 1){
			for(int i = 0;i < MAX_DATA-1;i++){
				if(((pApp->drum_point[i].x - 10 < point.x + pApp->camera_offset_x)&&(pApp->drum_point[i].y - 10 < point.y + pApp->camera_offset_y))&&
					((pApp->drum_point[i].x + 10 > point.x + pApp->camera_offset_x)&&(pApp->drum_point[i].y + 10 > point.y + pApp->camera_offset_y))){
						pApp->drum_Point_Cheker = i;
						i = MAX_DATA;
				}
			}
		}

	}

	pApp->draw_flg = 1;

	L_Button = true;
	
	CView::OnLButtonDown(nFlags, point);
}
void CVectorSetToolView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	int	dx, dy;

	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	pApp->NowPoint = point;
	if(R_Button == true) {
		
		dx = point.x - PointR.x;
		dy = point.y - PointR.y;
		PointR = point;
//		pApp->Dx.camera.AddOffset((float)dx, (float)dy);	// カメラのオフセットを設定
		pApp->mainmodel.roty += dx;
//		pApp->Dx.camera.Position[1] += dy;
//		pApp->camera_offset_x += dx;
//		pApp->camera_offset_y += dy;
		
		pApp->draw_flg = 1;

	}
	if(L_Button && pApp->Point_flg == 0){
		pApp->point[pApp->point_cnt].x = point.x + pApp->camera_offset_x;

		if(pApp->SnapFlg == ON && pApp->point_cnt != 0){
			pApp->point[pApp->point_cnt].y = pApp->point[pApp->point_cnt-1].y;
		}else{
			pApp->point[pApp->point_cnt].y = point.y + pApp->camera_offset_y;
		}

		pApp->draw_flg = 1;
	}
	if(L_Button && pApp->Point_flg == 1){
		pApp->point[pApp->Point_Cheker].x = point.x + pApp->camera_offset_x;
		if(pApp->SnapFlg == ON){
			pApp->point[pApp->Point_Cheker].y = pApp->point[pApp->Point_Cheker-1].y;
		}else{
			pApp->point[pApp->Point_Cheker].y = point.y + pApp->camera_offset_y;
		}

		pApp->draw_flg = 1;
	}

	if(L_Button && pApp->Point_flg == 3){
		if(pApp->object_flg == 0 || pApp->shift_flg == 1){
			pApp->ballon_point[pApp->ballon_point_cnt].x = point.x + pApp->camera_offset_x;

			if(pApp->SnapFlg == ON && pApp->ballon_point_cnt != 0){
				pApp->ballon_point[pApp->ballon_point_cnt].y = pApp->ballon_point[pApp->ballon_point_cnt-1].y;
			}else{
				pApp->ballon_point[pApp->ballon_point_cnt].y = point.y + pApp->camera_offset_y;
			}
		}
		if(pApp->object_flg == 1 || pApp->cnt_flg == 1){
			pApp->drum_point[pApp->drum_point_cnt].x = point.x + pApp->camera_offset_x;

			if(pApp->SnapFlg == ON && pApp->drum_point_cnt != 0){
				pApp->drum_point[pApp->drum_point_cnt].y = pApp->drum_point[pApp->drum_point_cnt-1].y;
			}else{
				pApp->drum_point[pApp->drum_point_cnt].y = point.y + pApp->camera_offset_y;
			}
		}
		pApp->draw_flg = 1;
	}

	if(L_Button && pApp->Point_flg == 4){
		if(pApp->object_flg == 0 || pApp->shift_flg == 1){
			pApp->ballon_point[pApp->ballon_Point_Cheker].x = point.x + pApp->camera_offset_x;

			if(pApp->SnapFlg == ON && pApp->ballon_point_cnt != 0){
				pApp->ballon_point[pApp->ballon_Point_Cheker].y = pApp->ballon_point[pApp->ballon_Point_Cheker-1].y;
			}else{
				pApp->ballon_point[pApp->ballon_Point_Cheker].y = point.y + pApp->camera_offset_y;
			}
		}
		if(pApp->object_flg == 1 || pApp->cnt_flg == 1){
			pApp->drum_point[pApp->drum_Point_Cheker].x = point.x + pApp->camera_offset_x;

			if(pApp->SnapFlg == ON && pApp->drum_point_cnt != 0){
				pApp->drum_point[pApp->drum_Point_Cheker].y = pApp->drum_point[pApp->drum_Point_Cheker-1].y;
			}else{
				pApp->drum_point[pApp->drum_Point_Cheker].y = point.y + pApp->camera_offset_y;
			}
		}
		pApp->draw_flg = 1;
	}

	CView::OnMouseMove(nFlags, point);
}

void CVectorSetToolView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	PointR = point;
	R_Button = true;
	
	CView::OnRButtonDown(nFlags, point);
}

void CVectorSetToolView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	R_Button = false;
	
	CView::OnRButtonUp(nFlags, point);
}

BOOL CVectorSetToolView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->Dx.camera.SetCameraValue(0, 0, zDelta);
	pApp->draw_flg = 1;
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CVectorSetToolView::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->draw_flg = 1;
	// 描画用メッセージとして CView::OnPaint() を呼び出してはいけません
}



BOOL CVectorSetToolView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	switch(pMsg->message) {													// 今来たメッセージは？

		case WM_KEYUP:														// キーアップだったら
			switch(pMsg->wParam) {											// 何キーですか？
				default:
				break;
				case VK_DELETE:													// DELETEキーなら処理しましょう
					if(pApp->Point_flg == 2){
						for(int i = pApp->Point_Cheker;i < MAX_DATA-1;i++){
							pApp->point[i].x = pApp->point[i+1].x;
							pApp->point[i].y = pApp->point[i+1].y;
						}
						pApp->point_cnt -= 1;
						pApp->draw_flg = 1;
					}
					if(pApp->Point_flg == 5){
						if(pApp->object_flg == 0){
							for(int i = pApp->ballon_Point_Cheker;i < MAX_DATA-1;i++){
								pApp->ballon_point[i].x = pApp->ballon_point[i+1].x;
								pApp->ballon_point[i].y = pApp->ballon_point[i+1].y;
							}
							pApp->ballon_point_cnt -= 1;
						}
						else if(pApp->object_flg == 1){
							for(int i = pApp->drum_Point_Cheker;i < MAX_DATA-1;i++){
								pApp->drum_point[i].x = pApp->drum_point[i+1].x;
								pApp->drum_point[i].y = pApp->drum_point[i+1].y;
							}
							pApp->drum_point_cnt -= 1;
						}
						pApp->draw_flg = 1;
					}
					return true;
					break;
				case VK_CONTROL:
					pApp->cnt_flg = 0;
					return true;
					break;

				case VK_SHIFT:
					pApp->shift_flg = 0;
					return true;
					break;
			}


		case WM_KEYDOWN:														// キーアップだったら
			switch(pMsg->wParam) {											// 何キーですか？
			default:
			break;
			case VK_UP:	
				pApp->Dx.camera.Position[1] += 1;
				pApp->camera_offset_y += 1;
				pApp->draw_flg = 1;
				return true;
				break;
			case VK_DOWN:
				pApp->Dx.camera.Position[1] += -1;
				pApp->camera_offset_y -= 1;
				pApp->draw_flg = 1;
				return true;
				break;
			case VK_LEFT:	
				pApp->Dx.camera.Position[0] += -1;
				pApp->camera_offset_x -= 1;
				pApp->draw_flg = 1;
				return true;
				break;
			case VK_RIGHT:							
				pApp->Dx.camera.Position[0] += 1;
				pApp->camera_offset_x += 1;
				pApp->draw_flg = 1;
				return true;
				break;
			case VK_CONTROL:
				pApp->cnt_flg = 1;
				return true;
				break;

			case VK_SHIFT:
				pApp->shift_flg = 1;
				return true;
				break;
			}

	}	
	return CView::PreTranslateMessage(pMsg);
}
