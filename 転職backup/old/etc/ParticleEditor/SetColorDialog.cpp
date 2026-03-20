// SetColorDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "test.h"
#include "SetColorDialog.h"
#include ".\setcolordialog.h"


// CSetColorDialog ダイアログ

IMPLEMENT_DYNAMIC(CSetColorDialog, CDialog)
CSetColorDialog::CSetColorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetColorDialog::IDD, pParent)
{
}

CSetColorDialog::~CSetColorDialog()
{
}

void CSetColorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_COLOR_R, m_Slider_Color_R);
	DDX_Control(pDX, IDC_SLIDER_COLOR_G, m_Slider_Color_G);
	DDX_Control(pDX, IDC_SLIDER_COLOR_B, m_Slider_Color_B);
}


BEGIN_MESSAGE_MAP(CSetColorDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, OnBnClickedButtonDefault)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CSetColorDialog メッセージ ハンドラ

void CSetColorDialog::OnBnClickedButtonDefault()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->direct_x.color_r = color_r = DEFAULT_COLOR_R;
	pApp->direct_x.color_g = color_g = DEFAULT_COLOR_G;
	pApp->direct_x.color_b = color_b = DEFAULT_COLOR_B;
	m_Slider_Color_R.SetPos(pApp->direct_x.color_r);
	m_Slider_Color_G.SetPos(pApp->direct_x.color_g);
	m_Slider_Color_B.SetPos(pApp->direct_x.color_b);

}

void CSetColorDialog::OnBnClickedOk()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	color_r = pApp->direct_x.color_r;
	color_g = pApp->direct_x.color_g;
	color_b = pApp->direct_x.color_b;

	OnOK();
}

void CSetColorDialog::OnBnClickedCancel()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->direct_x.color_r = color_r;
	pApp->direct_x.color_g = color_g;
	pApp->direct_x.color_b = color_b;
	OnCancel();
}

void CSetColorDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->direct_x.color_r = m_Slider_Color_R.GetPos();
	pApp->direct_x.color_g = m_Slider_Color_G.GetPos();
	pApp->direct_x.color_b = m_Slider_Color_B.GetPos();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CSetColorDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// TODO :  ここに初期化を追加してください
	m_Slider_Color_R.SetRange(0, 255, true);
	m_Slider_Color_R.SetPageSize(1);	m_Slider_Color_R.SetLineSize(1);	m_Slider_Color_R.SetPos(0);
	m_Slider_Color_R.SetPos(pApp->direct_x.color_r);

	m_Slider_Color_G.SetRange(0, 255, true);
	m_Slider_Color_G.SetPageSize(1);	m_Slider_Color_G.SetLineSize(1);	m_Slider_Color_G.SetPos(0);
	m_Slider_Color_G.SetPos(pApp->direct_x.color_g);

	m_Slider_Color_B.SetRange(0, 255, true);
	m_Slider_Color_B.SetPageSize(1);	m_Slider_Color_B.SetLineSize(1);	m_Slider_Color_B.SetPos(0);
	m_Slider_Color_B.SetPos(pApp->direct_x.color_b);

	color_r = pApp->direct_x.color_r;
	color_g = pApp->direct_x.color_g;
	color_b = pApp->direct_x.color_b;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
