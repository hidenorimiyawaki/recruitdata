// AnimeDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "animationtool.h"
#include "AnimeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimeDialog ダイアログ


CAnimeDialog::CAnimeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimeDialog)
	m_Edit_Flame = 0;
	//}}AFX_DATA_INIT
}


void CAnimeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimeDialog)
	DDX_Control(pDX, IDC_FLAME_SLIDER, m_Flame_Slider);
	DDX_Control(pDX, IDC_PLAY_WINDOW, m_Play_Window);
	DDX_Text(pDX, IDC_EDIT_FLAME, m_Edit_Flame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimeDialog, CDialog)
	//{{AFX_MSG_MAP(CAnimeDialog)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimeDialog メッセージ ハンドラ

void CAnimeDialog::OnButtonPlay() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定
	if(pApp->fileload == 1)	{
		playflg = 1;														// 画像が読み込まれていたらプレイ許可
		pApp->Dx.exbord.texRect.top = pApp->cash_data[anime_frame].top;		// とりあえず、4すみのデータ設定
		pApp->Dx.exbord.texRect.left = pApp->cash_data[anime_frame].left -128;// で、絵の参照位置更新しましょう
		pApp->Dx.exbord.texRect.bottom = pApp->cash_data[anime_frame].bottom;	
		pApp->Dx.exbord.texRect.right = pApp->cash_data[anime_frame].right -128; 
	}
}

void CAnimeDialog::OnButtonStop() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定
	if(pApp->fileload == 1)	playflg = 0;									// 画像が読み込まれていたらプレイ許可解除
}

void CAnimeDialog::OnButtonBack() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定
	if(pApp->fileload == 1)	anime_frame = 0;								// 画像が読み込まれていたら最初のフレームへ
}
BOOL CAnimeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// ダイアログが起動されたときに仮想ビットマップ領域を作成
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定

	int cnt;
	CDC *pDC;																// デバイスコンテキスト用の取得用変数作成
	pDC = m_Play_Window.GetDC();											// デバイスコンテキスト取得
	memDC.CreateCompatibleDC(pDC);											// 仮想画面用メンバ変数(メモリDC)に描画許可設定	
	Bitmap.CreateCompatibleBitmap(pDC,256,256);								// 仮想ビットマップ領域作成
	memDC.SelectObject(&Bitmap);											// メモリDCに仮想ビットマップ領域を関連付け
	memDC.ExtFloodFill(0,0,RGB(0,0,0),FLOODFILLSURFACE);					// メモリDCを白で初期化
	ReleaseDC(pDC);															// デバイスコンテキスト開放	
	pApp->DrawAnimeTest();													// 最初の描画
	playflg = anime_time = anime_frame = 0;									// アニメ関係の変数初期化
	end = 0;																// ダイアログ終了判定変数初期化
	cnt = 0;
	for(int i = 0;i < MAX_DATA;i++){
		if(pApp->next_frame[i] != 0){cnt = i + 1;}
		else{
			cnt = i + 1;
			i = MAX_DATA;
		}
		
	}
	m_Flame_Slider.SetRange(0,cnt, true);
	m_Flame_Slider.SetPageSize(1);	m_Flame_Slider.SetLineSize(1);	m_Flame_Slider.SetPos(0);


	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
void CAnimeDialog::DrawExec()
{
	Invalidate(false);
}
void CAnimeDialog::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト	
	
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定
	CDC *pDC;																// デバイスコンテキスト用の取得用変数作成
	pDC = m_Play_Window.GetDC();											// デバイスコンテキスト取得

	pDC->BitBlt(0, 0,256,256, &memDC, 0, 0, SRCCOPY);						// 仮想ビットマップを貼り付け描画
	
	ReleaseDC(pDC);															// デバイスコンテキスト開放

	// 描画用メッセージとして CDialog::OnPaint() を呼び出してはいけません
}
void CAnimeDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定

	end = 1;																// ダイアログが終わるから
	Bitmap.DeleteObject();													// ビットマップ削除
	memDC.DeleteDC();														// 仮想領域削除
	playflg = 0;															// アニメーション許可解除
	pApp->draw_flg = 1;														// メインウィンドウ描画してね

	CDialog::OnOK();
}

void CAnimeDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定

	end = 1;																// ダイアログが終わるから
	Bitmap.DeleteObject();													// ビットマップ削除
	memDC.DeleteDC();														// 仮想領域削除
	playflg = 0;															// アニメーション許可解除
	pApp->draw_flg = 1;														// メインウィンドウ描画してね

	CDialog::OnCancel();
}

void CAnimeDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if((CSliderCtrl*)pScrollBar == &m_Flame_Slider) {
		m_Edit_Flame = m_Flame_Slider.GetPos();
		UpdateData(false);
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
