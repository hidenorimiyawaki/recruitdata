// EditDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MothionEditor.h"
#include "EditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDialog ダイアログ


CEditDialog::CEditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDialog)
	m_Edit_Parts_No = 0;
	m_Edit_PosX = 0;
	m_Edit_PosY = 0;
	m_Edit_PosZ = 0;
	m_Edit_RotX = 0;
	m_Edit_RotY = 0;
	m_Edit_RotZ = 0;
	m_Edit_Frame = 0;
	m_Edit_Time = 0;
	//}}AFX_DATA_INIT
}


void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDialog)
	DDX_Control(pDX, IDC_SLIDER_TIME, m_Slider_Time);
	DDX_Control(pDX, IDC_CHECK_ANIMATION, m_Check_Animation);
	DDX_Control(pDX, IDC_SLIDER_FRAME, m_Slider_Frame);
	DDX_Control(pDX, IDC_CHECK_ATTACK, m_Check_Attack);
	DDX_Control(pDX, IDC_CHECK_GARD, m_Check_Gard);
	DDX_Control(pDX, IDC_SLIDER_ROTZ, m_Slider_RotZ);
	DDX_Control(pDX, IDC_SLIDER_ROTY, m_Slider_RotY);
	DDX_Control(pDX, IDC_SLIDER_ROTX, m_Slider_RotX);
	DDX_Control(pDX, IDC_SLIDER_POSZ, m_Slider_PosZ);
	DDX_Control(pDX, IDC_SLIDER_POSY, m_Slider_PosY);
	DDX_Control(pDX, IDC_SLIDER_POSX, m_Slider_PosX);
	DDX_Control(pDX, IDC_SLIDER_PARTS_NO, m_Slider_Parts_No);
	DDX_Text(pDX, IDC_EDIT_PARTS_NO, m_Edit_Parts_No);
	DDV_MinMaxInt(pDX, m_Edit_Parts_No, 0, 99);
	DDX_Text(pDX, IDC_EDIT_POSX, m_Edit_PosX);
	DDX_Text(pDX, IDC_EDIT_POSY, m_Edit_PosY);
	DDX_Text(pDX, IDC_EDIT_POSZ, m_Edit_PosZ);
	DDX_Text(pDX, IDC_EDIT_ROTX, m_Edit_RotX);
	DDX_Text(pDX, IDC_EDIT_ROTY, m_Edit_RotY);
	DDX_Text(pDX, IDC_EDIT_ROTZ, m_Edit_RotZ);
	DDX_Text(pDX, IDC_EDIT_FRAME, m_Edit_Frame);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Edit_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDialog, CDialog)
	//{{AFX_MSG_MAP(CEditDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_ATTACK, OnCheckAttack)
	ON_BN_CLICKED(IDC_CHECK_GARD, OnCheckGard)
	ON_BN_CLICKED(IDC_CHECK_ANIMATION, OnCheckAnimation)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDialog メッセージ ハンドラ

BOOL CEditDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください

	m_Slider_RotX.SetRange(-ROT_MAX, ROT_MAX, true);
	m_Slider_RotX.SetPageSize(1);	m_Slider_RotX.SetLineSize(1);	m_Slider_RotX.SetPos(0);

	m_Slider_RotY.SetRange(-ROT_MAX, ROT_MAX, true);
	m_Slider_RotY.SetPageSize(1);	m_Slider_RotY.SetLineSize(1);	m_Slider_RotY.SetPos(0);

	m_Slider_RotZ.SetRange(-ROT_MAX, ROT_MAX, true);
	m_Slider_RotZ.SetPageSize(1);	m_Slider_RotZ.SetLineSize(1);	m_Slider_RotZ.SetPos(0);

	m_Slider_PosX.SetRange(-POS_MAX, POS_MAX, true);
	m_Slider_PosX.SetPageSize(1);	m_Slider_PosX.SetLineSize(1);	m_Slider_PosX.SetPos(0);

	m_Slider_PosY.SetRange(-POS_MAX, POS_MAX, true);
	m_Slider_PosY.SetPageSize(1);	m_Slider_PosY.SetLineSize(1);	m_Slider_PosY.SetPos(0);

	m_Slider_PosZ.SetRange(-POS_MAX, POS_MAX, true);
	m_Slider_PosZ.SetPageSize(1);	m_Slider_PosZ.SetLineSize(1);	m_Slider_PosZ.SetPos(0);

	m_Slider_Parts_No.SetRange(0, PARTS_QTY - 1, true);
	m_Slider_Parts_No.SetPageSize(1);	m_Slider_Parts_No.SetLineSize(1);	m_Slider_Parts_No.SetPos(0);

	m_Slider_Frame.SetRange(0, 99, true);
	m_Slider_Frame.SetPageSize(1);	m_Slider_Frame.SetLineSize(1);	m_Slider_Frame.SetPos(0);

	m_Slider_Time.SetRange(0, 59, true);
	m_Slider_Time.SetPageSize(1);	m_Slider_Time.SetLineSize(1);	m_Slider_Time.SetPos(0);

	UpdateData(false);		// コントロールに反映	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CEditDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
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

void CEditDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{ 
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if((CSliderCtrl*)pScrollBar == &m_Slider_RotX) {
		m_Edit_RotX = (float)m_Slider_RotX.GetPos() / 100.0f;		// Ｘ軸回転
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_RotY) {
		m_Edit_RotY = (float)m_Slider_RotY.GetPos() / 100.0f;		// Ｙ軸回転
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_RotZ) {
		m_Edit_RotZ = (float)m_Slider_RotZ.GetPos() / 100.0f;		// Ｚ軸回転
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_PosX) {
		m_Edit_PosX = (float)m_Slider_PosX.GetPos();				// Ｘ座標
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_PosY) {
		m_Edit_PosY = (float)m_Slider_PosY.GetPos();				// Ｙ座標
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_PosZ) {
		m_Edit_PosZ = (float)m_Slider_PosZ.GetPos();				// Ｚ座標
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_Parts_No) {
		m_Edit_Parts_No = (float)m_Slider_Parts_No.GetPos();		// 
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_Time) {
		m_Edit_Time = (float)m_Slider_Time.GetPos();			// 
		pApp->frame_time[0][pApp->zintai.cur_frame] = m_Edit_Time;
	}
	if((CSliderCtrl*)pScrollBar == &m_Slider_Frame) {
		m_Edit_Frame = (float)m_Slider_Frame.GetPos();				// フレーム

		PARTS_ROT_POINT* pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
		pt->rot[0]   = m_Edit_RotX;
		pt->rot[1]   = m_Edit_RotY;
		pt->rot[2]   = m_Edit_RotZ;
		pt->point[0] = m_Edit_PosX;
		pt->point[1] = m_Edit_PosY;
		pt->point[2] = m_Edit_PosZ;
		pApp->flgset[0][pApp->zintai.cur_frame].attack = m_Check_Attack.GetCheck();
		pApp->flgset[0][pApp->zintai.cur_frame].gard = m_Check_Gard.GetCheck();
		pApp->zintai.parts[pApp->zintai.cur_parts]->SetMatrix();	// マトリックスを更新	
		pApp->zintai.cur_parts = m_Edit_Parts_No;

		pApp->zintai.cur_frame = m_Edit_Frame;

		pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
		m_Edit_RotX = pt->rot[0];
		m_Edit_RotY = pt->rot[1];
		m_Edit_RotZ = pt->rot[2];
		m_Slider_RotX.SetPos((int)(m_Edit_RotX * 100));
		m_Slider_RotY.SetPos((int)(m_Edit_RotY * 100));
		m_Slider_RotZ.SetPos((int)(m_Edit_RotZ * 100));
		m_Edit_PosX = pt->point[0];
		m_Edit_PosY = pt->point[1];
		m_Edit_PosZ = pt->point[2];
		m_Slider_PosX.SetPos((int)m_Edit_PosX);
		m_Slider_PosY.SetPos((int)m_Edit_PosY);
		m_Slider_PosZ.SetPos((int)m_Edit_PosZ);
		m_Check_Attack.SetCheck(pApp->flgset[0][pApp->zintai.cur_frame].attack);
		m_Check_Gard.SetCheck(pApp->flgset[0][pApp->zintai.cur_frame].gard);
		pApp->flgset[0][pApp->zintai.cur_frame].gard = m_Check_Gard.GetCheck();

		for(int i = 0; i < PARTS_QTY; i++) {
			pApp->zintai.parts[i]->SetMatrix();			// マトリックスを更新	
		}

		if(pApp->end_check == pApp->zintai.cur_frame)m_Check_Animation.SetCheck(1);
		else if(pApp->end_check != pApp->zintai.cur_frame){
			m_Check_Animation.SetCheck(0);
		}

		m_Edit_Time = pApp->frame_time[0][pApp->zintai.cur_frame];
		m_Slider_Time.SetPos(m_Edit_Time);			// 

	}

	UpdateData(false);


	PARTS_ROT_POINT* pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
	pt->rot[0]   = m_Edit_RotX;
	pt->rot[1]   = m_Edit_RotY;
	pt->rot[2]   = m_Edit_RotZ;
	pt->point[0] = m_Edit_PosX;
	pt->point[1] = m_Edit_PosY;
	pt->point[2] = m_Edit_PosZ;
	pApp->zintai.parts[pApp->zintai.cur_parts]->SetMatrix();	// マトリックスを更新	
	pApp->zintai.cur_parts = m_Edit_Parts_No;
	SetControl();		// コントロールの値を設定

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEditDialog::SetControl()
{
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	PARTS_ROT_POINT* pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
	m_Edit_RotX = pt->rot[0];
	m_Edit_RotY = pt->rot[1];
	m_Edit_RotZ = pt->rot[2];
	m_Slider_RotX.SetPos((int)(m_Edit_RotX * 100));
	m_Slider_RotY.SetPos((int)(m_Edit_RotY * 100));
	m_Slider_RotZ.SetPos((int)(m_Edit_RotZ * 100));
	m_Edit_PosX = pt->point[0];
	m_Edit_PosY = pt->point[1];
	m_Edit_PosZ = pt->point[2];
	m_Slider_PosX.SetPos((int)m_Edit_PosX);
	m_Slider_PosY.SetPos((int)m_Edit_PosY);
	m_Slider_PosZ.SetPos((int)m_Edit_PosZ);
	m_Edit_Time = pApp->frame_time[0][pApp->zintai.cur_frame];
	m_Slider_Time.SetPos((int)pApp->frame_time[0][pApp->zintai.cur_frame]);
	UpdateData(false);		// コントロールに反映
}

void CEditDialog::OnCheckAttack() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->flgset[0][pApp->zintai.cur_frame].attack = m_Check_Attack.GetCheck();
	
}

void CEditDialog::OnCheckGard() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->flgset[0][pApp->zintai.cur_frame].gard = m_Check_Gard.GetCheck();
	
}

void CEditDialog::OnCheckAnimation() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	if(m_Check_Animation.GetCheck() == true) pApp->end_check = pApp->zintai.cur_frame;
	
}

void CEditDialog::OnButtonPlay() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	pApp->play_flg = 1;
}

void CEditDialog::OnButtonStop() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	pApp->play_flg = 0;
	
}

void CEditDialog::OnButtonBack() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	PARTS_ROT_POINT* pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
	pt->rot[0]   = m_Edit_RotX;
	pt->rot[1]   = m_Edit_RotY;
	pt->rot[2]   = m_Edit_RotZ;
	pt->point[0] = m_Edit_PosX;
	pt->point[1] = m_Edit_PosY;
	pt->point[2] = m_Edit_PosZ;
	pApp->zintai.parts[pApp->zintai.cur_parts]->SetMatrix();	// マトリックスを更新	
	pApp->zintai.cur_parts = m_Edit_Parts_No;

	pApp->zintai.cur_frame = 0;

	pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
	m_Edit_RotX = pt->rot[0];
	m_Edit_RotY = pt->rot[1];
	m_Edit_RotZ = pt->rot[2];
	m_Slider_RotX.SetPos((int)(m_Edit_RotX * 100));
	m_Slider_RotY.SetPos((int)(m_Edit_RotY * 100));
	m_Slider_RotZ.SetPos((int)(m_Edit_RotZ * 100));
	m_Edit_PosX = pt->point[0];
	m_Edit_PosY = pt->point[1];
	m_Edit_PosZ = pt->point[2];
	m_Slider_PosX.SetPos((int)m_Edit_PosX);
	m_Slider_PosY.SetPos((int)m_Edit_PosY);
	m_Slider_PosZ.SetPos((int)m_Edit_PosZ);	
	m_Slider_Frame.SetPos(0);
	m_Edit_Frame = 0;
	UpdateData(false);

	pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
	pt->rot[0]   = m_Edit_RotX;
	pt->rot[1]   = m_Edit_RotY;
	pt->rot[2]   = m_Edit_RotZ;
	pt->point[0] = m_Edit_PosX;
	pt->point[1] = m_Edit_PosY;
	pt->point[2] = m_Edit_PosZ;
	pApp->zintai.parts[pApp->zintai.cur_parts]->SetMatrix();	// マトリックスを更新	
	pApp->zintai.cur_parts = m_Edit_Parts_No;

	SetControl();		// コントロールの値を設定

}

void CEditDialog::Animation()
{
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	if(pApp->play_flg == 1){
		PARTS_ROT_POINT* pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
		pApp->zintai.parts[pApp->zintai.cur_parts]->SetMatrix();	// マトリックスを更新	
		m_Edit_RotX = pt->rot[0];
		m_Edit_RotY = pt->rot[1];
		m_Edit_RotZ = pt->rot[2];
		m_Slider_RotX.SetPos((int)(m_Edit_RotX * 100));
		m_Slider_RotY.SetPos((int)(m_Edit_RotY * 100));
		m_Slider_RotZ.SetPos((int)(m_Edit_RotZ * 100));
		m_Edit_PosX = pt->point[0];
		m_Edit_PosY = pt->point[1];
		m_Edit_PosZ = pt->point[2];
		m_Slider_PosX.SetPos((int)m_Edit_PosX);
		m_Slider_PosY.SetPos((int)m_Edit_PosY);
		m_Slider_PosZ.SetPos((int)m_Edit_PosZ);	
		m_Edit_Frame = pApp->zintai.cur_frame;
		m_Slider_Frame.SetPos(m_Edit_Frame);
		SetControl();		// コントロールの値を設定
	}
}

void CEditDialog::SetData()
{
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	m_Edit_Frame = 0;				// フレーム

	PARTS_ROT_POINT* pt = &pApp->zintai.parts[pApp->zintai.cur_parts]->rot_point[0][pApp->zintai.cur_frame];
	m_Edit_RotX = pt->rot[0];
	m_Edit_RotY = pt->rot[1];
	m_Edit_RotZ = pt->rot[2];
	m_Slider_RotX.SetPos((int)(m_Edit_RotX * 100));
	m_Slider_RotY.SetPos((int)(m_Edit_RotY * 100));
	m_Slider_RotZ.SetPos((int)(m_Edit_RotZ * 100));
	m_Edit_PosX = pt->point[0];
	m_Edit_PosY = pt->point[1];
	m_Edit_PosZ = pt->point[2];
	m_Slider_PosX.SetPos((int)m_Edit_PosX);
	m_Slider_PosY.SetPos((int)m_Edit_PosY);
	m_Slider_PosZ.SetPos((int)m_Edit_PosZ);
	m_Edit_Time = pApp->frame_time[0][pApp->zintai.cur_frame];
	m_Slider_Time.SetPos((int)pApp->frame_time[0][pApp->zintai.cur_frame]);

	pApp->zintai.parts[pApp->zintai.cur_parts]->SetMatrix();	// マトリックスを更新	
	pApp->zintai.cur_parts = m_Edit_Parts_No;
	UpdateData(false);

}
