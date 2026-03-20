// GlidColorDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapEditor.h"
#include "GlidColorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlidColorDialog ダイアログ


CGlidColorDialog::CGlidColorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGlidColorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGlidColorDialog)
	m_Edit_B = 0;
	m_Edit_G = 0;
	m_Edit_R = 0;
	//}}AFX_DATA_INIT
}


void CGlidColorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGlidColorDialog)
	DDX_Control(pDX, IDC_SAMPLE_COLOR, m_Sample_Color);
	DDX_Text(pDX, IDC_EDIT_B, m_Edit_B);
	DDV_MinMaxUInt(pDX, m_Edit_B, 0, 255);
	DDX_Text(pDX, IDC_EDIT_G, m_Edit_G);
	DDV_MinMaxUInt(pDX, m_Edit_G, 0, 255);
	DDX_Text(pDX, IDC_EDIT_R, m_Edit_R);
	DDV_MinMaxUInt(pDX, m_Edit_R, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGlidColorDialog, CDialog)
	//{{AFX_MSG_MAP(CGlidColorDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SAMPLE_BUTTON, OnSampleButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlidColorDialog メッセージ ハンドラ


void CGlidColorDialog::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
	// 描画用メッセージとして CDialog::OnPaint() を呼び出してはいけません
	
	
	SampleBrush.CreateSolidBrush(RGB(m_Edit_R,m_Edit_G,m_Edit_B));
	CDC* pDC = m_Sample_Color.GetDC();

	
	pDC->SelectObject(SampleBrush);
	pDC->Rectangle(0,0,50,50);
	

	m_Sample_Color.ReleaseDC(pDC);
	SampleBrush.DeleteObject();
}

void CGlidColorDialog::OnSampleButton() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	Invalidate(false);
	
}
