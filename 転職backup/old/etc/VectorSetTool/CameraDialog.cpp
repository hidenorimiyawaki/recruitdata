// CameraDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "vectorsettool.h"
#include "CameraDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraDialog ダイアログ


CCameraDialog::CCameraDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCameraDialog)
	m_Move_X = 0;
	m_Move_Y = 0;
	m_Move_Z = 0;
	m_Edit_Offset = 0;
	//}}AFX_DATA_INIT
}


void CCameraDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraDialog)
	DDX_Control(pDX, IDC_COMBO_OBJECT, m_Combo_Object);
	DDX_Text(pDX, IDC_EDIT_MOVE_X, m_Move_X);
	DDX_Text(pDX, IDC_EDIT_MOVE_Y, m_Move_Y);
	DDX_Text(pDX, IDC_EDIT_MOVE_Z, m_Move_Z);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_Edit_Offset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCameraDialog, CDialog)
	//{{AFX_MSG_MAP(CCameraDialog)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, OnButtonMove)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, OnButtonDefault)
	ON_BN_CLICKED(IDC_BUTTON_SET_POINT, OnButtonSetPoint)
	ON_BN_CLICKED(IDC_BUTTON_SET_OBJECT, OnButtonSetObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraDialog メッセージ ハンドラ

void CCameraDialog::OnButtonMove() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	UpdateData(true);


	pApp->Dx.camera.Position[0] += m_Move_X;
	pApp->Dx.camera.Position[1] += m_Move_Y;
	pApp->camera_offset_x += m_Move_X;
	pApp->camera_offset_y += m_Move_Y;
	
	pApp->Dx.camera.SetCameraValue(0, 0, m_Move_Z);

	pApp->draw_flg = 1;
}

void CCameraDialog::OnButtonUp() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	UpdateData(true);

	pApp->Dx.camera.Position[1] += m_Edit_Offset;
	pApp->camera_offset_y += m_Edit_Offset;

	pApp->draw_flg = 1;
	
}

void CCameraDialog::OnButtonDown() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	UpdateData(true);

	pApp->Dx.camera.Position[1] += m_Edit_Offset * -1;
	pApp->camera_offset_y += m_Edit_Offset * -1;

	pApp->draw_flg = 1;
	
}

void CCameraDialog::OnButtonLeft() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	UpdateData(true);

	pApp->Dx.camera.Position[0] += m_Edit_Offset * -1;
	pApp->camera_offset_x += m_Edit_Offset * -1;

	pApp->draw_flg = 1;
	
}

void CCameraDialog::OnButtonRight() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	UpdateData(true);

	pApp->Dx.camera.Position[0] += m_Edit_Offset;
	pApp->camera_offset_x += m_Edit_Offset;

	pApp->draw_flg = 1;
	
}

void CCameraDialog::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	CDialog::OnCancel();
}

void CCameraDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CDialog::OnOK();
}

void CCameraDialog::OnButtonSetPoint() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	if(pApp->Point_flg == 0){

		pApp->point[pApp->point_cnt].x = pApp->camera_offset_x + (SCREEN_WIDTH / 2);

		if(pApp->SnapFlg == ON && pApp->point_cnt != 0){
			pApp->point[pApp->point_cnt].y = pApp->point[pApp->point_cnt-1].y;
		}else{
			pApp->point[pApp->point_cnt].y = SET_OFFSET + pApp->camera_offset_y;
		}
		pApp->Point_Cheker++;
		pApp->point_cnt++;
	}
	if(pApp->Point_flg == 1){
		pApp->point[pApp->Point_Cheker].x = pApp->camera_offset_x + (SCREEN_WIDTH / 2);
		if(pApp->SnapFlg == ON && pApp->Point_Cheker-1 >= 0){
			pApp->point[pApp->Point_Cheker].y = pApp->point[pApp->Point_Cheker-1].y;
		}else{
			pApp->point[pApp->Point_Cheker].y = SET_OFFSET + pApp->camera_offset_y;
		}
		pApp->Point_Cheker++;
	}
	pApp->draw_flg = 1;

}

void CCameraDialog::OnButtonDefault() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	m_Move_X = 0;
	m_Move_Y = 0;
	m_Move_Z = 0;


	pApp->camera_offset_x += (int)pApp->Dx.camera.Position[0] * -1;
	pApp->camera_offset_y += (int)pApp->Dx.camera.Position[1] * -1;

	pApp->Dx.camera.Position[0] += pApp->Dx.camera.Position[0] * -1;
	pApp->Dx.camera.Position[1] += pApp->Dx.camera.Position[1] * -1;
	pApp->draw_flg = 1;

}

BOOL CCameraDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	object_flg = 0;

	m_Combo_Object.InsertString(-1,"風船");
	m_Combo_Object.InsertString(-1,"ドラム缶");

	m_Combo_Object.SetCurSel(0);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CCameraDialog::PreTranslateMessage(MSG* pMsg) 
{
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
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
				pApp->Dx.camera.Position[0] += m_Move_X;
				pApp->Dx.camera.Position[1] += m_Move_Y;
				pApp->camera_offset_x += m_Move_X;
				pApp->camera_offset_y += m_Move_Y;
				
				pApp->Dx.camera.SetCameraValue(0, 0, m_Move_Z);
				UpdateData(false);
			return true;
			}
			break;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}


void CCameraDialog::OnButtonSetObject() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	object_flg = m_Combo_Object.GetCurSel();

	if(pApp->Point_flg == 3){
		if(object_flg == 0){
			pApp->ballon_point[pApp->ballon_point_cnt].x = pApp->camera_offset_x + (SCREEN_WIDTH / 2);

			if(pApp->SnapFlg == ON && pApp->ballon_point_cnt != 0){
				pApp->ballon_point[pApp->ballon_point_cnt].y = pApp->ballon_point[pApp->ballon_point_cnt-1].y;
			}else{
				pApp->ballon_point[pApp->ballon_point_cnt].y = SET_OFFSET + pApp->camera_offset_y;
			}
			pApp->ballon_Point_Cheker++;
			pApp->ballon_point_cnt++;
		}
		if(object_flg == 1){
			pApp->drum_point[pApp->drum_point_cnt].x = pApp->camera_offset_x + (SCREEN_WIDTH / 2);

			if(pApp->SnapFlg == ON && pApp->drum_point_cnt != 0){
				pApp->drum_point[pApp->drum_point_cnt].y = pApp->drum_point[pApp->drum_point_cnt-1].y;
			}else{
				pApp->drum_point[pApp->drum_point_cnt].y = SET_OFFSET + pApp->camera_offset_y;
			}
			pApp->drum_Point_Cheker++;
			pApp->drum_point_cnt++;
		}
	}
	if(pApp->Point_flg == 4){
		if(object_flg == 0){
			pApp->ballon_point[pApp->ballon_Point_Cheker].x = pApp->camera_offset_x + (SCREEN_WIDTH / 2);

			if(pApp->SnapFlg == ON && pApp->Point_Cheker != 0){
				pApp->ballon_point[pApp->ballon_Point_Cheker].y = pApp->ballon_point[pApp->ballon_Point_Cheker-1].y;
			}else{
				pApp->ballon_point[pApp->ballon_Point_Cheker].y = SET_OFFSET + pApp->camera_offset_y;
			}
			pApp->ballon_Point_Cheker++;
		}
		if(object_flg == 1){
			pApp->drum_point[pApp->drum_Point_Cheker].x = pApp->camera_offset_x + (SCREEN_WIDTH / 2);

			if(pApp->SnapFlg == ON && pApp->drum_Point_Cheker != 0){
				pApp->drum_point[pApp->drum_Point_Cheker].y = pApp->drum_point[pApp->drum_Point_Cheker-1].y;
			}else{
				pApp->drum_point[pApp->drum_Point_Cheker].y = SET_OFFSET + pApp->camera_offset_y;
			}
			pApp->drum_Point_Cheker++;
		}

	}
	pApp->draw_flg = 1;
	
}
