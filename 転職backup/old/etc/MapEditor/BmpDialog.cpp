// BmpDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapEditor.h"
#include "BmpDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpDialog ダイアログ


CBmpDialog::CBmpDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBmpDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBmpDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
	int x,y;

	CursolBrush.CreateStockObject(HOLLOW_BRUSH);
	CursolPen.CreatePen(PS_SOLID,1,RGB(0,255,255));

	MousePoint.x = 0;
	MousePoint.y = 0;

	for(x = 0;x <= 32;x++){
		GlidPointX[x].x = x * 8;
		GlidPointX[x].y = 0;

		GlidPointX[x + 32].x = x * 8;
		GlidPointX[x + 32].y = 256;
	}

	for(y = 0;y <= 32;y++){
		GlidPointY[y].x = 0;
		GlidPointY[y].y = y * 8;
		GlidPointY[y + 32].x = 256;
		GlidPointY[y + 32].y = y * 8;
	}

		
}


void CBmpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBmpDialog)
	DDX_Control(pDX, IDC_FIELD_BMP, m_bmp_field);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBmpDialog, CDialog)
	//{{AFX_MSG_MAP(CBmpDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpDialog メッセージ ハンドラ

BOOL CBmpDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CBmpDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	if(pMapEditor->LoadBitmap){

		MousePoint.x = point.x;
		MousePoint.y = point.y;

		ClientToScreen(&MousePoint);

		m_bmp_field.ScreenToClient(&MousePoint);

		if(MousePoint.x + pMapEditor->CSDialog.m_cursol_x <= 0){
			MousePoint.x = 0;
		}
		if(MousePoint.y + pMapEditor->CSDialog.m_cursol_y <= 0){
			MousePoint.y = 0;
		}
		if(MousePoint.x + pMapEditor->CSDialog.m_cursol_x >= BITMAP_FIELD_WIDTH){
			MousePoint.x = BITMAP_FIELD_WIDTH - pMapEditor->CSDialog.m_cursol_x;
		}
		if(MousePoint.y + pMapEditor->CSDialog.m_cursol_y >= BITMAP_FIELD_WIDTH){
			MousePoint.y = BITMAP_FIELD_WIDTH - pMapEditor->CSDialog.m_cursol_y;
		}
		
		if(MousePoint.x >= 0 && MousePoint.y >= 0 &&
			MousePoint.x <= BITMAP_FIELD_WIDTH && MousePoint.y <= BITMAP_FIELD_WIDTH){
			int mx, my;
			mx = ((MousePoint.x / 8 ) * 8);
			my = ((MousePoint.y / 8 ) * 8);
			mx = mx / 8;
			my = my / 8;
			my = my * (BITMAP_FIELD_WIDTH / 8);
			mx = mx + my;
			pMapEditor->NewChipNo = mx;
		}
	}
	Invalidate(false);
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CBmpDialog::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
	// 描画用メッセージとして CDialog::OnPaint() を呼び出してはいけません

	// アプリケーションオブジェクトのポインタを取得
	CMapEditorApp* pApp = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	if(pApp->LoadBitmap) {	// すでにビットマップはロードされているか？

		// ＢＭＰダイアログ内ピクチャーコントロールのＤＣを取得
		CDC* pDC = m_bmp_field.GetDC();

		// ビットマップを関係づける
		CBitmap *pbmpOld = pApp->DC.SelectObject(&pApp->Bitmap);
		// ピクチャーコントロールにビットマップを描画
		pDC->BitBlt(0, 0, BITMAP_FIELD_WIDTH, BITMAP_FIELD_HEIGHT, &pApp->DC, 0, 0, SRCCOPY);
		// オブジェクトの関連付けを元に戻す
		pApp->DC.SelectObject(pbmpOld);

		if(pApp->BmpDlgGlid){
		
			GlidPen.DeleteObject();
			GlidPen.CreatePen(PS_SOLID,1,RGB(pApp->GlidColorDialog.m_Edit_R,pApp->GlidColorDialog.m_Edit_G,pApp->GlidColorDialog.m_Edit_B));
			pDC->SelectObject(GlidPen);
			int i;

			for(i = 0;i <= 32;i++){
				pDC->MoveTo(GlidPointX[i]);
				pDC->LineTo(GlidPointX[i + 32]);
			}
			for(i = 0;i <= 32;i++){
				pDC->MoveTo(GlidPointY[i]);
				pDC->LineTo(GlidPointY[i + 32]);
			}
		}


		// マウスカーソルを描画
		int mx, my;
		mx = (MousePoint.x / 8 ) * 8;
		my = (MousePoint.y / 8 ) * 8;

		pDC->SelectObject(CursolBrush);
		pDC->SelectObject(CursolPen);
		pDC->Rectangle(mx, my, mx + pApp->CSDialog.m_cursol_x, my + pApp->CSDialog.m_cursol_y);	// 矩形を描画

		// デバイスコンテキストを解放
		m_bmp_field.ReleaseDC(pDC);

	}

}

void CBmpDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	Invalidate(false);
	
}

