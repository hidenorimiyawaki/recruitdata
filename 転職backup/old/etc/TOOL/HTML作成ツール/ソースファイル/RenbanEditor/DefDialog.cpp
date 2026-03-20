// DefDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "RenbanEditor.h"
#include "DefDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefDialog ダイアログ


CDefDialog::CDefDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDefDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefDialog)
	m_EditDefTime = 3;
	m_MaxHtmlNum = 2;
	//}}AFX_DATA_INIT
}


void CDefDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefDialog)
	DDX_Text(pDX, IDC_EDITDEFTIME, m_EditDefTime);
	DDX_Text(pDX, IDC_MAXHTMLNUM, m_MaxHtmlNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefDialog, CDialog)
	//{{AFX_MSG_MAP(CDefDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefDialog メッセージ ハンドラ

void CDefDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	UpdateData(true);
	CDialog::OnOK();
}
