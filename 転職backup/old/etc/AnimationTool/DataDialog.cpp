// DataDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "animationtool.h"
#include "DataDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataDialog ダイアログ


CDataDialog::CDataDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDataDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataDialog)
	m_All_Time = 0;
	m_Frame_Time = 0;
	m_Next_Frame = 0;
	m_Now_Frame = 0;
	m_U_Size = 0.0f;
	m_V_Size = 0.0f;
	m_X_Size = 0;
	m_Y_Size = 0;
	m_U_Size2 = 0.0f;
	m_V_Size2 = 0.0f;
	m_Edit_Kukei = 0;
	//}}AFX_DATA_INIT
}


void CDataDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDialog)
	DDX_Control(pDX, IDC_SLIDER_NOWFRAME, m_Slider_Now_Frame);
	DDX_Control(pDX, IDC_SLIDER_NEXTFRAME, m_Slider_Next_Frame);
	DDX_Control(pDX, IDC_SLIDER_FRAMETIME, m_Slider_Frame_Time);
	DDX_Control(pDX, IDC_CHECK_ALPHA, m_Check_Alpha);
	DDX_Text(pDX, IDC_EDIT_ALLTIME, m_All_Time);
	DDX_Text(pDX, IDC_EDIT_FRAMETIME, m_Frame_Time);
	DDX_Text(pDX, IDC_EDIT_NEXTFRAME, m_Next_Frame);
	DDX_Text(pDX, IDC_EDIT_NOWFRAME, m_Now_Frame);
	DDX_Text(pDX, IDC_EDIT_USIZE, m_U_Size);
	DDX_Text(pDX, IDC_EDIT_VSIZE, m_V_Size);
	DDX_Text(pDX, IDC_EDIT_XSIZE, m_X_Size);
	DDX_Text(pDX, IDC_EDIT_YSIZE, m_Y_Size);
	DDX_Text(pDX, IDC_EDIT_USIZE2, m_U_Size2);
	DDX_Text(pDX, IDC_EDIT_VSIZE2, m_V_Size2);
	DDX_Text(pDX, IDC_EDIT_KUKEI, m_Edit_Kukei);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataDialog, CDialog)
	//{{AFX_MSG_MAP(CDataDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_ALPHA, OnCheckAlpha)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_KUKEI, OnButtonCheckKukei)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataDialog メッセージ ハンドラ

void CDataDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if((CSliderCtrl*)pScrollBar == &m_Slider_Frame_Time) {
		m_Frame_Time = m_Slider_Frame_Time.GetPos();

		pApp->frame_data[m_Now_Frame] = m_Frame_Time;

		m_All_Time = 0;
		for(int i = 0; i < MAX_DATA;i++){
			m_All_Time += pApp->frame_data[i];
		}

	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_Next_Frame) {
		m_Next_Frame = m_Slider_Next_Frame.GetPos();

		pApp->next_frame[m_Now_Frame] = m_Next_Frame;
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_Now_Frame) {
		pApp->attach_kukei[m_Now_Frame] = m_Edit_Kukei;
		m_Now_Frame = m_Slider_Now_Frame.GetPos();

		pApp->start.y = (long)pApp->data[m_Now_Frame][TOP];
		pApp->start.x = (long)pApp->data[m_Now_Frame][LEFT] + 128;
		pApp->end.y = (long)pApp->data[m_Now_Frame][DOWN];
		pApp->end.x = (long)pApp->data[m_Now_Frame][RIGHT] + 128;

		m_Frame_Time = pApp->frame_data[m_Now_Frame];
		m_Slider_Frame_Time.SetPos(m_Frame_Time);

		m_Next_Frame = pApp->next_frame[m_Now_Frame];
		m_Slider_Next_Frame.SetPos(m_Next_Frame);
		pApp->Dx.workbord.texRect.top = pApp->start.y;
		pApp->Dx.workbord.texRect.left = pApp->start.x -128;
		pApp->Dx.workbord.texRect.bottom = pApp->end.y;
		pApp->Dx.workbord.texRect.right = pApp->end.x -128;

		m_Edit_Kukei = pApp->attach_kukei[m_Now_Frame];

		pApp->DrawExec();
	}
	
	UpdateData(false);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CDataDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_Slider_Frame_Time.SetRange(0,300, true);
	m_Slider_Frame_Time.SetPageSize(1);	m_Slider_Frame_Time.SetLineSize(1);	m_Slider_Frame_Time.SetPos(0);

	m_Slider_Next_Frame.SetRange(0,MAX_DATA, true);
	m_Slider_Next_Frame.SetPageSize(1);	m_Slider_Next_Frame.SetLineSize(1);	m_Slider_Next_Frame.SetPos(0);

	m_Slider_Now_Frame.SetRange(0,MAX_DATA, true);
	m_Slider_Now_Frame.SetPageSize(1);	m_Slider_Now_Frame.SetLineSize(1);	m_Slider_Now_Frame.SetPos(0);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDataDialog::Update()
{
	UpdateData(false);
}

void CDataDialog::OnCheckAlpha() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->DrawExec();
}

void CDataDialog::OnButtonPlay() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	pApp->frame_count = 0;
	pApp->animation_flg = 1;
}

void CDataDialog::OnButtonStop() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->animation_flg = 0;

}

void CDataDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	CDialog::OnOK();
}

void CDataDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CDialog::OnCancel();
}


BOOL CDataDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);


	switch(pMsg->message) {
		case WM_KEYDOWN:
			switch(pMsg->wParam) {
			case VK_RETURN:		return true;	// 「押されてなかった事にする」
			case VK_ESCAPE:		return true;	// 「押されてなかった事にする」
			}
			break;
		case WM_KEYUP:
			switch(pMsg->wParam){
			case VK_RETURN:
				UpdateData(true);
				if(m_Frame_Time <= 0)m_Frame_Time = 0;
				if(m_Frame_Time >= 180)m_Frame_Time = 180;

				if(m_Next_Frame <= 0)m_Next_Frame = 0;
				if(m_Next_Frame >= MAX_DATA)m_Next_Frame = MAX_DATA;

				if(m_Now_Frame <= 0)m_Now_Frame = 0;
				if(m_Now_Frame >= MAX_DATA)m_Now_Frame = MAX_DATA;


				m_Slider_Frame_Time.SetPos(m_Frame_Time);

				m_Slider_Next_Frame.SetPos(m_Next_Frame);

				m_Slider_Now_Frame.SetPos(m_Now_Frame);

				m_All_Time = 0;
				for(int i = 0; i < MAX_DATA;i++){
					m_All_Time += pApp->frame_data[i];
				}
				UpdateData(false);
			return true;
			}
			break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDataDialog::OnButtonGet() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	int work_cnt;
	work_cnt = pApp->GlidDialog.m_List_Cash.GetCurSel();		
	pApp->data[pApp->DataDialog.m_Now_Frame][TOP]  = (float)pApp->cash_data[work_cnt -1].top;
	pApp->data[pApp->DataDialog.m_Now_Frame][LEFT] = (float)(pApp->cash_data[work_cnt -1].left -128);
	pApp->data[pApp->DataDialog.m_Now_Frame][DOWN] = (float)pApp->cash_data[work_cnt -1].bottom;
	pApp->data[pApp->DataDialog.m_Now_Frame][RIGHT] = (float)(pApp->cash_data[work_cnt -1].right -128);


	m_Edit_Kukei = work_cnt;
	UpdateData(false);
}



void CDataDialog::OnButtonCheckKukei() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	UpdateData(true);
	pApp->GlidDialog.m_List_Cash.SetCurSel(pApp->attach_kukei[m_Now_Frame]);
	pApp->GlidDialog.DrawExecEx();
	UpdateData(false);
}

void CDataDialog::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	UpdateData(true);
	if(m_Frame_Time <= 0)m_Frame_Time = 0;
	if(m_Frame_Time >= 300)m_Frame_Time = 300;

	if(m_Next_Frame <= 0)m_Next_Frame = 0;
	if(m_Next_Frame >= MAX_DATA)m_Next_Frame = MAX_DATA;

	if(m_Now_Frame <= 0)m_Now_Frame = 0;
	if(m_Now_Frame >= MAX_DATA)m_Now_Frame = MAX_DATA;


	m_Slider_Frame_Time.SetPos(m_Frame_Time);

	m_Slider_Next_Frame.SetPos(m_Next_Frame);

	m_Slider_Now_Frame.SetPos(m_Now_Frame);

	m_All_Time = 0;
	for(int i = 0; i < MAX_DATA;i++){
		m_All_Time += pApp->frame_data[i];
	}
	UpdateData(false);

}
