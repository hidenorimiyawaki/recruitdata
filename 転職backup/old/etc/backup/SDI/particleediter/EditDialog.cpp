// EditDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "particleediter.h"
#include "EditDialog.h"
#include ".\editdialog.h"


// CEditDialog ダイアログ

IMPLEMENT_DYNAMIC(CEditDialog, CDialog)
CEditDialog::CEditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDialog::IDD, pParent)
	, m_Edit_Num(0)
	, m_Edit_Scale(0)
	, m_Edit_Pos_X(0)
	, m_Edit_Pos_Y(0)
	, m_Edit_Pos_Z(0)
	, m_Edit_Time(0)
	, m_Edit_Dir_X(0)
	, m_Edit_Dir_Y(0)
	, m_Edit_Dir_Z(0)
	, m_Edit_Gravity(0)
{
}

CEditDialog::~CEditDialog()
{
}

void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_NUM, m_Edit_Slider_Num);
	DDX_Text(pDX, IDC_EDIT_NUM, m_Edit_Num);
	DDX_Text(pDX, IDC_EDIT_SCALE, m_Edit_Scale);
	DDX_Control(pDX, IDC_SLIDER_SCALE, m_Edit_Slider_Size);
	DDX_Text(pDX, IDC_EDIT_POS_X, m_Edit_Pos_X);
	DDX_Text(pDX, IDC_EDIT_POS_Y, m_Edit_Pos_Y);
	DDX_Text(pDX, IDC_EDIT_POS_Z, m_Edit_Pos_Z);
	DDX_Control(pDX, IDC_SLIDER_POS_X, m_Edit_Slider_Pos_X);
	DDX_Control(pDX, IDC_SLIDER_POS_Y, m_Edit_Slider_Pos_Y);
	DDX_Control(pDX, IDC_SLIDER_POS_Z, m_Edit_Slider_Pos_Z);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Edit_Time);
	DDX_Control(pDX, IDC_SLIDER_TIME, m_Edit_Slider_Time);
	DDX_Text(pDX, IDC_EDIT_DIR_X, m_Edit_Dir_X);
	DDX_Text(pDX, IDC_EDIT_DIR_Y, m_Edit_Dir_Y);
	DDX_Text(pDX, IDC_EDIT_DIR_Z, m_Edit_Dir_Z);
	DDX_Text(pDX, IDC_EDIT_GRAVITY, m_Edit_Gravity);
	DDX_Control(pDX, IDC_SLIDER_DIR_X, m_Edit_Slider_Dir_X);
	DDX_Control(pDX, IDC_SLIDER_DIR_Y, m_Edit_Slider_Dir_Y);
	DDX_Control(pDX, IDC_SLIDER_DIR_Z, m_Edit_Slider_Dir_Z);
	DDX_Control(pDX, IDC_SLIDER_GRAVITY, m_Edit_Slider_Gravity);
}


BEGIN_MESSAGE_MAP(CEditDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_HSCROLL()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CEditDialog メッセージ ハンドラ

void CEditDialog::OnBnClickedOk()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	return;
	OnOK();
}

void CEditDialog::OnBnClickedCancel()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	return;
	OnCancel();
}

void CEditDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int work;
	// アプリケーションオブジェクトのポインタを取得
	CparticleediterApp* pApp = (CparticleediterApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Num) {
		m_Edit_Num = m_Edit_Slider_Num.GetPos()+1;
		for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
			pApp->particle[i].effect_cnt = m_Edit_Time;
			pApp->particle[i].scale = m_Edit_Scale;
			pApp->particle[i].gravity = m_Edit_Gravity;
		}
	}
	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Size){
		m_Edit_Scale = m_Edit_Slider_Size.GetPos()+1;
		for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
			pApp->particle[i].effect_cnt = m_Edit_Time;
			pApp->particle[i].scale = m_Edit_Scale;
			pApp->particle[i].gravity = m_Edit_Gravity;
		}

	}
	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Time){
		m_Edit_Time = m_Edit_Slider_Time.GetPos()+1;
		for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
			pApp->particle[i].effect_cnt = m_Edit_Time;
			pApp->particle[i].scale = m_Edit_Scale;
			pApp->particle[i].gravity = m_Edit_Gravity;
		}
	}

	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Pos_X){
		UpdateData(true);
		work = m_Edit_Pos_X;
		m_Edit_Pos_X = m_Edit_Slider_Pos_X.GetPos();
		pApp->direct_x.mainbord->SetMove((float)(m_Edit_Pos_X-work)*-1,0,0);
	}
	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Pos_Y){
		UpdateData(true);
		work = m_Edit_Pos_Y;
		m_Edit_Pos_Y = m_Edit_Slider_Pos_Y.GetPos();
		pApp->direct_x.mainbord->SetMove(0,(float)(m_Edit_Pos_Y-work)*-1,0);
	}
	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Pos_Z){
		UpdateData(true);
		work = m_Edit_Pos_Z;
		m_Edit_Pos_Z = m_Edit_Slider_Pos_Z.GetPos();
		pApp->direct_x.mainbord->SetMove(0,0,(float)(m_Edit_Pos_Z-work)*-1);
	}

	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_X){
		UpdateData(true);
		work = m_Edit_Dir_X;
		m_Edit_Dir_X = m_Edit_Slider_Dir_X.GetPos();
		pApp->direct_x.mainbord->SetMove((float)(m_Edit_Dir_X-work)*-1,0,0);
	}
	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Y){
		UpdateData(true);
		work = m_Edit_Dir_Y;
		m_Edit_Dir_Y = m_Edit_Slider_Dir_Y.GetPos();
		pApp->direct_x.mainbord->SetMove(0,(float)(m_Edit_Dir_Y-work)*-1,0);
	}
	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Dir_Z){
		UpdateData(true);
		work = m_Edit_Dir_Z;
		m_Edit_Dir_Z = m_Edit_Slider_Dir_Z.GetPos();
		pApp->direct_x.mainbord->SetMove(0,0,(float)(m_Edit_Dir_Z-work)*-1);
	}

	if((CSliderCtrl*)pScrollBar == &m_Edit_Slider_Gravity) {
		m_Edit_Gravity = m_Edit_Slider_Gravity.GetPos();
		for(int i = 0;i< pApp->EditDialog.m_Edit_Num;i++){
			pApp->particle[i].effect_cnt = m_Edit_Time;
			pApp->particle[i].scale = m_Edit_Scale;
			pApp->particle[i].gravity = m_Edit_Gravity;
		}
	}

	UpdateData(false);		// コントロールに反映	


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

int CEditDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO :  ここに特定な作成コードを追加してください。
	return 0;
}

BOOL CEditDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  ここに初期化を追加してください
	m_Edit_Slider_Num.SetRange(0, PARTICLE_MAX-1, true);
	m_Edit_Slider_Num.SetPageSize(1);	m_Edit_Slider_Num.SetLineSize(1);	m_Edit_Slider_Num.SetPos(0);
	m_Edit_Slider_Num.SetPos(100-1);

	m_Edit_Slider_Time.SetRange(0, 1200-1, true);
	m_Edit_Slider_Time.SetPageSize(1);	m_Edit_Slider_Time.SetLineSize(1);	m_Edit_Slider_Time.SetPos(0);
	m_Edit_Slider_Time.SetPos(60-1);

	m_Edit_Slider_Size.SetRange(0, PARTICLE_MAX_SCALE-1, true);
	m_Edit_Slider_Size.SetPageSize(1);	m_Edit_Slider_Size.SetLineSize(1);	m_Edit_Slider_Size.SetPos(0);
	m_Edit_Slider_Size.SetPos(0);

	m_Edit_Slider_Pos_X.SetRange(SCROLL_MIN, SCROLL_MAX, true);
	m_Edit_Slider_Pos_X.SetPageSize(1);	m_Edit_Slider_Pos_X.SetLineSize(1);	m_Edit_Slider_Pos_X.SetPos(0);
	m_Edit_Slider_Pos_X.SetPos(0);

	m_Edit_Slider_Pos_Y.SetRange(SCROLL_MIN, SCROLL_MAX, true);
	m_Edit_Slider_Pos_Y.SetPageSize(1);	m_Edit_Slider_Pos_Y.SetLineSize(1);	m_Edit_Slider_Pos_Y.SetPos(0);
	m_Edit_Slider_Pos_Y.SetPos(0);

	m_Edit_Slider_Pos_Z.SetRange(SCROLL_MIN, SCROLL_MAX, true);
	m_Edit_Slider_Pos_Z.SetPageSize(1);	m_Edit_Slider_Pos_Z.SetLineSize(1);	m_Edit_Slider_Pos_Z.SetPos(0);
	m_Edit_Slider_Pos_Z.SetPos(0);

	m_Edit_Slider_Dir_X.SetRange(-300, 300, true);
	m_Edit_Slider_Dir_X.SetPageSize(1);	m_Edit_Slider_Dir_X.SetLineSize(1);	m_Edit_Slider_Dir_X.SetPos(0);
	m_Edit_Slider_Dir_X.SetPos(0);

	m_Edit_Slider_Dir_Y.SetRange(-300, 300, true);
	m_Edit_Slider_Dir_Y.SetPageSize(1);	m_Edit_Slider_Dir_Y.SetLineSize(1);	m_Edit_Slider_Dir_Y.SetPos(0);
	m_Edit_Slider_Dir_Y.SetPos(0);

	m_Edit_Slider_Dir_Z.SetRange(-300, 300, true);
	m_Edit_Slider_Dir_Z.SetPageSize(1);	m_Edit_Slider_Dir_Z.SetLineSize(1);	m_Edit_Slider_Dir_Z.SetPos(0);
	m_Edit_Slider_Dir_Z.SetPos(0);

	m_Edit_Slider_Gravity.SetRange(-100, 100, true);
	m_Edit_Slider_Gravity.SetPageSize(1);	m_Edit_Slider_Gravity.SetLineSize(1);	m_Edit_Slider_Gravity.SetPos(0);
	m_Edit_Slider_Gravity.SetPos(0);
	m_Edit_Slider_Gravity.SetTicFreq(4);


	m_Edit_Num = m_Edit_Slider_Num.GetPos()+1;
	m_Edit_Scale = m_Edit_Slider_Size.GetPos()+1;
	m_Edit_Time = m_Edit_Slider_Time.GetPos()+1;

	m_Edit_Pos_X = m_Edit_Slider_Pos_X.GetPos();
	m_Edit_Pos_Y = m_Edit_Slider_Pos_Y.GetPos();
	m_Edit_Pos_Z = m_Edit_Slider_Pos_Z.GetPos();

	m_Edit_Dir_X = m_Edit_Slider_Dir_X.GetPos();
	m_Edit_Dir_Y = m_Edit_Slider_Dir_Y.GetPos();
	m_Edit_Dir_Z = m_Edit_Slider_Dir_Z.GetPos();

	m_Edit_Gravity = m_Edit_Slider_Gravity.GetPos();

	UpdateData(false);		// コントロールに反映	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CEditDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	switch(pMsg->message) {
	case WM_KEYDOWN:
		switch(pMsg->wParam) {
		case VK_RETURN:		return true;	// 「押されてなかった事にする」
		case VK_ESCAPE:		return true;	// 「押されてなかった事にする」
		}
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
