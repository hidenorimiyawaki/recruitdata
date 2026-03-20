// CursolSizeDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapEditor.h"
#include "CursolSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCursolSizeDialog ダイアログ


CCursolSizeDialog::CCursolSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCursolSizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCursolSizeDialog)
	m_cursol_x = 16;
	m_cursol_y = 16;
	//}}AFX_DATA_INIT
}


void CCursolSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCursolSizeDialog)
	DDX_Text(pDX, IDC_EDIT_CURSOL_X_SIZE, m_cursol_x);
	DDV_MinMaxUInt(pDX, m_cursol_x, 8, 256);
	DDX_Text(pDX, IDC_EDIT_CURSOL_Y_SIZE, m_cursol_y);
	DDV_MinMaxUInt(pDX, m_cursol_y, 8, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCursolSizeDialog, CDialog)
	//{{AFX_MSG_MAP(CCursolSizeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCursolSizeDialog メッセージ ハンドラ

void CCursolSizeDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	UpdateData(TRUE);

	if((m_cursol_x % 8) != 0){
		MessageBox("横のサイズが８の倍数ではありません\n設定は反映されません。","警告",MB_OK);
		m_cursol_x = work_x;
		m_cursol_y = work_y;
	}
	if((m_cursol_y % 8) != 0){
		MessageBox("縦のサイズが８の倍数ではありません\n設定は反映されません。","警告",MB_OK); 
		m_cursol_x = work_x;
		m_cursol_y = work_y;
	}
	UpdateData(FALSE);

	CDialog::OnOK();
}
