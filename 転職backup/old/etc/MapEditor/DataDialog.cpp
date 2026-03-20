// DataDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapEditor.h"
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
	m_palet = 0;
	//}}AFX_DATA_INIT
	data = 0;

}


void CDataDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDialog)
	DDX_Control(pDX, IDC_COMBO_STEP, m_combo_step);
	DDX_Control(pDX, IDC_COMBO_FLOOR, m_combo_floor);
	DDX_Control(pDX, IDC_COMBO_DAMAGE, m_combo_damage);
	DDX_Text(pDX, IDC_EDIT_PALET, m_palet);
	DDV_MinMaxUInt(pDX, m_palet, 0, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataDialog, CDialog)
	//{{AFX_MSG_MAP(CDataDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataDialog メッセージ ハンドラ

BOOL CDataDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください

	m_combo_floor.InsertString(-1,"通常床");
	m_combo_floor.InsertString(-1,"落とし穴");
	m_combo_floor.InsertString(-1,"水");
	m_combo_floor.InsertString(-1,"イベント");

	m_combo_step.InsertString(-1,"通常");
	m_combo_step.InsertString(-1,"段１");
	m_combo_step.InsertString(-1,"段２");
	m_combo_step.InsertString(-1,"通行不可");

	m_combo_damage.InsertString(-1,"無し");
	m_combo_damage.InsertString(-1,"有り");
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDataDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください

	m_combo_floor.GetWindowText(floor);
	m_combo_step.GetWindowText(step);
	m_combo_damage.GetWindowText(damage);

	if(floor == ""){
		floor_data = 0;
	}
	else if(floor == "通常床"){
		floor_data = 0;
	}
	else if(floor == "落とし穴"){
		floor_data = 1;
	}
	else if(floor == "水"){
		floor_data = 2;
	}
	else{
		floor_data = 3;
	}

	if(step == ""){
		step_data = 0;
	}
	else if(step == "通常"){
		step_data = 0;
	}
	else if(step == "段１"){
		step_data = 1;
	}
	else if(step == "段２"){
		step_data = 2;
	}
	else{
		step_data = 3;
	}

	if(damage == ""){
		damage_data = 0;
	}
	else if(damage == "無し"){
		damage_data = 0;
	}
	else{
		damage_data = 1;
	}

	step_data = step_data * 4;
	damage_data = damage_data * 16;

	if(floor_data == 1){
		damage_data = 0;
		step_data = 0;
	}
	else if(floor_data == 3){
		damage_data = 0;
		step_data = 0;
	}
	else if(step_data == 3){
		floor_data = 0;
	}
	else{
	}

	data = floor_data;
	data = data + step_data;
	data = data + damage_data;

	CDialog::OnOK();
}

CDataDialog::~CDataDialog()
{
	
}
