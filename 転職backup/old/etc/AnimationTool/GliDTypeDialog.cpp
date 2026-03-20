// GliDTypeDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "animationtool.h"
#include "GliDTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGliDTypeDialog ダイアログ


CGliDTypeDialog::CGliDTypeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGliDTypeDialog::IDD, pParent)
{
	// とりあえずダイアログの初期化に伴った変数の初期化

	//{{AFX_DATA_INIT(CGliDTypeDialog)
	m_Edit_B = 0;											// RGBのBの値を初期化
	m_Edit_G = 0;											// RGBのGの値を初期化
	m_Edit_R = 0;											// RGBのRの値を初期化
	//}}AFX_DATA_INIT
}


void CGliDTypeDialog::DoDataExchange(CDataExchange* pDX)
{
	// MFCの機能としてダイアログの各種コントロールと変数を関連付け

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGliDTypeDialog)
	DDX_Control(pDX, IDC_STATIC_COLOR, m_Static_Color);		// 変数とサンプルカラー領域を関連付け
	DDX_Control(pDX, IDC_SLIDER_R, m_Slider_R);				// 変数とR用スライダーを関連付け
	DDX_Control(pDX, IDC_SLIDER_G, m_Slider_G);				// 変数とG用スライダーを関連付け
	DDX_Control(pDX, IDC_SLIDER_B, m_Slider_B);				// 変数とB用スライダーを関連付け
	DDX_Control(pDX, IDC_COMBO_WIDTH, m_Combo_Width);		// 変数とグリッドの横幅用コンボボックスを関連付け
	DDX_Control(pDX, IDC_COMBO_HEIGHT, m_Combo_Height);		// 変数とグリッドの縦幅用コンボボックスを関連付け
	DDX_Text(pDX, IDC_EDIT_R, m_Edit_R);					// 変数とR用のエディットボックスを関連付け
	DDX_Text(pDX, IDC_EDIT_G, m_Edit_G);					// 変数とG用のエディットボックスを関連付け
	DDX_Text(pDX, IDC_EDIT_B, m_Edit_B);					// 変数とB用のエディットボックスを関連付け
	//}}AFX_DATA_MAP
}

// MFCの機能としてメッセージマッピングを設定する
BEGIN_MESSAGE_MAP(CGliDTypeDialog, CDialog)
	//{{AFX_MSG_MAP(CGliDTypeDialog)
	ON_WM_HSCROLL()											// バーやスライダー等が水平スクロールされたメッセージ
	ON_WM_PAINT()											// 描画すべきタイミングのメッセージ
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGliDTypeDialog メッセージ ハンドラ

BOOL CGliDTypeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// 各種コントロールを初期化
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();// アプリケーションポインタを取得
	ASSERT_VALID(pApp);										// エラーがないか判定

	// 縦幅用コンボボックスを初期化(16の2掛けで増える)
	m_Combo_Height.InsertString(-1,"16");					// 1段目16
	m_Combo_Height.InsertString(-1,"32");					// 2段目32
	m_Combo_Height.InsertString(-1,"64");					// 3段目64
	m_Combo_Height.InsertString(-1,"128");					// 4段目128

	// 横幅用コンボボックスを初期化(16の2掛けで増える)
	m_Combo_Width.InsertString(-1,"16");					// 1段目16
	m_Combo_Width.InsertString(-1,"32");					// 2段目32
	m_Combo_Width.InsertString(-1,"64");					// 3段目64
	m_Combo_Width.InsertString(-1,"128");					// 4段目128

	// グリッドの縦幅の初期値からコンボボックスのカーソル位置をセット					
	switch(pApp->GLID_HEIGHT){								// グリッドの縦の幅は？
		case 16:											// 16ならば
			m_Combo_Height.SetCurSel(0);					// 0番目(1段目)に設定
			break;

		case 32:											// 32ならば
			m_Combo_Height.SetCurSel(1);					// 1番目(2段目)に設定
			break;
		
		case 64:											// 64ならば
			m_Combo_Height.SetCurSel(2);					// 2番目(3段目)に設定
			break;

		case 128:											// 128ならば
			m_Combo_Height.SetCurSel(3);					// 3番目(4段目)に設定
			break;

		default:											// デフォルト処理は無しで(一応互換性のためとかでおいときます)
			break;
	}

	// グリッドの横幅の初期値からコンボボックスのカーソル位置をセット					
	switch(pApp->GLID_WIDTH){								// グリッドの横の幅は？
		case 16:											// 16ならば
			m_Combo_Width.SetCurSel(0);						// 0番目(1段目)に設定
			break;

		case 32:											// 32ならば
			m_Combo_Width.SetCurSel(1);						// 1番目(2段目)に設定
			break;
		
		case 64:											// 64ならば
			m_Combo_Width.SetCurSel(2);						// 2番目(3段目)に設定
			break;

		case 128:											// 128ならば
			m_Combo_Width.SetCurSel(3);						// 3番目(4段目)に設定
			break;

		default:											// デフォルト処理は無しで(一応互換性のためとかでおいときます)
			break;
	}

	// R用スライダーを初期化
	m_Slider_R.SetRange(0,255, true);						// 幅を0～255まで設定
	m_Slider_R.SetPageSize(1);								// ページ数を1に
	m_Slider_R.SetLineSize(1);								// ライン数を1に
	m_Slider_R.SetPos(m_Edit_R);							// 今の値のところにカーソルを合わせる

	// G用スライダーを初期化
	m_Slider_G.SetRange(0,255, true);						// 幅を0～255まで設定
	m_Slider_G.SetPageSize(1);								// ページ数を1に
	m_Slider_G.SetLineSize(1);								// ライン数を1に
	m_Slider_G.SetPos(m_Edit_G);							// 今の値のところにカーソルを合わせる

	// B用スライダーを初期化
	m_Slider_B.SetRange(0,255, true);						// 幅を0～255まで設定
	m_Slider_B.SetPageSize(1);								// ページ数を1に
	m_Slider_B.SetLineSize(1);								// ライン数を1に
	m_Slider_B.SetPos(m_Edit_B);							// 今の値のところにカーソルを合わせる


	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CGliDTypeDialog::OnOK() 
{
	// OKボタンが押されたとき、各種設定を反映させる
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();// アプリケーションポインタを取得
	ASSERT_VALID(pApp);										// エラーがないか判定


	switch(m_Combo_Height.GetCurSel()){						// コンボボックス(縦幅用)のカーソルの場所は？
		case 0:												// 0番目(1段目)ならば
			pApp->GLID_HEIGHT = 16;							// グリッドの縦幅を16に
		break;

		case 1:												// 1番目(2段目)ならば
			pApp->GLID_HEIGHT = 32;							// グリッドの縦幅を32に
			break;
		
		case 2:												// 2番目(3段目)ならば
			pApp->GLID_HEIGHT = 64;							// グリッドの縦幅を64に
			break;

		case 3:												// 3番目(4段目)ならば
			pApp->GLID_HEIGHT = 128;						// グリッドの縦幅を128に
			break;

		default:											// デフォルト処理は無しで(一応互換性のためとかでおいときます)
			break;
	}

	switch(m_Combo_Width.GetCurSel()){						// コンボボックス(横幅用)のカーソルの場所は？
		case 0:												// 0番目(1段目)ならば
			pApp->GLID_WIDTH = 16;							// グリッドの横幅を16に
		break;

		case 1:												// 1番目(2段目)ならば
			pApp->GLID_WIDTH = 32;							// グリッドの横幅を32に
			break;
		
		case 2:												// 2番目(3段目)ならば
			pApp->GLID_WIDTH = 64;							// グリッドの横幅を64に
			break;

		case 3:												// 3番目(4段目)ならば
			pApp->GLID_WIDTH = 128;							// グリッドの横幅を128に
			break;

		default:											// デフォルト処理は無しで(一応互換性のためとかでおいときます)
			break;
	}

	pApp->draw_flg = ON;									// ダイアログが閉じたらアイドル時間にメインウィンドウ描画ね

	CDialog::OnOK();
}

void CGliDTypeDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// スライダーがスクロールされたら、各種関連カラーを設定
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();// アプリケーションポインタを取得
	ASSERT_VALID(pApp);										// エラーがないか判定

	if((CSliderCtrl*)pScrollBar == &m_Slider_R) {			// 操作されたスライダーはR用スライダー？
		m_Edit_R = (int)m_Slider_R.GetPos();				// じゃあ、R用スライダーの位置の値を変数に保存
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_G) {			// 操作されたスライダーはG用スライダー？
		m_Edit_G = (int)m_Slider_G.GetPos();				// じゃあ、G用スライダーの位置の値を変数に保存
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_B) {			// 操作されたスライダーはB用スライダー？
		m_Edit_B = (int)m_Slider_B.GetPos();				// じゃあ、B用スライダーの位置の値を変数に保存
	}

	CursolBrush.DeleteObject();								// 前回作成したサンプルカラーブラシを削除
	CursolBrush.CreateSolidBrush(RGB((int)m_Slider_R.GetPos(),(int)m_Slider_G.GetPos(),(int)m_Slider_B.GetPos()));
															// 各スライダーの値(任意のRGB値)でサンプルカラーブラシ作成

	pApp->GlidPen.DeleteObject();							// 前回作成したグリッドの太枠ペンを削除
	pApp->GlidPen.CreatePen(PS_SOLID,2,RGB((int)m_Slider_R.GetPos(),(int)m_Slider_G.GetPos(),(int)m_Slider_B.GetPos()));
															// 各スライダーの値(任意のRGB値)でグリッドの太枠ペン作成

	Invalidate(false);										// システム描画コールでペイント関数呼び出し
	UpdateData(false);										// データをアップデート(エディットの値を今の値に)

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGliDTypeDialog::OnPaint() 
{
	// サンプルカラー領域にサンプルカラーを描画
	CPaintDC dc(this);										// 描画用のデバイスコンテキスト(MFCが勝手に取ってる変数)
	
	CDC* pDC = m_Static_Color.GetDC();						// サンプルカラーの描画許可取得
	
	pDC->SelectObject(CursolBrush);							// サンプルカラー描画用のブラシ関連付け
	pDC->Rectangle(0,0,110,48);								// サンプルカラー描画
	
	m_Static_Color.ReleaseDC(pDC);							// サンプルカラーの描画許可開放

}
