// SizeDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapEditor.h"
#include "SizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSizeDialog ダイアログ


CSizeDialog::CSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSizeDialog)
	m_y_size = 256;
	m_x_size = 256;
	m_plaet_no = 0;
	//}}AFX_DATA_INIT

	MAP_X = m_x_size / 8;
	MAP_Y = m_y_size / 8;
}


void CSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSizeDialog)
	DDX_Text(pDX, IDC_EDIT_Y_SIZE, m_y_size);
	DDV_MinMaxUInt(pDX, m_y_size, 256, 2000);
	DDX_Text(pDX, IDC_EDIT_X_SIZE, m_x_size);
	DDV_MinMaxUInt(pDX, m_x_size, 256, 2000);
	DDX_Text(pDX, IDC_EDIT_PALET_No, m_plaet_no);
	DDV_MinMaxUInt(pDX, m_plaet_no, 0, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSizeDialog, CDialog)
	//{{AFX_MSG_MAP(CSizeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSizeDialog メッセージ ハンドラ

void CSizeDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	UpdateData(TRUE);
	
	if((m_x_size % 8) != 0){
		MessageBox("横のサイズが８の倍数ではありません\n各列一つ分繰り下げられます。","警告",MB_OK);
		m_x_size = (m_x_size / 8) * 8;
	}
	if((m_y_size % 8) != 0){
		MessageBox("縦のサイズが８の倍数ではありません\n一列分繰り下げられます。","警告",MB_OK); 
		m_y_size = (m_y_size / 8) * 8;
	}

	if(pMapEditor->MapData != 0){
		delete [] pMapEditor->MapData;
	}
	if(pMapEditor->AttrData != 0){
		delete [] pMapEditor->AttrData;
	}
	if(pMapEditor->GlidPointX != 0){
		delete [] pMapEditor->GlidPointX;
	}
	if(pMapEditor->GlidPointY != 0){
		delete [] pMapEditor->GlidPointY;
	}

	MAP_X = m_x_size / 8;
	MAP_Y = m_y_size / 8;

	pMapEditor->MapData = new CMapData[MAP_X * MAP_Y];
	pMapEditor->AttrData = new CAttrData[MAP_X * MAP_Y];
	pMapEditor->GlidPointX = new CPoint[MAP_X * 2];
	pMapEditor->GlidPointY = new CPoint[MAP_Y * 2];

	UINT pl;

	for(pl = 0;pl < MAP_X * MAP_Y;pl++){
		pMapEditor->MapData[pl].Palette = m_plaet_no;
	}


	UINT x,y;

	for(x = 0; x < MAP_X;x++){
		pMapEditor->GlidPointX[x].x = x * 8;
		pMapEditor->GlidPointX[x].y = 0;
		pMapEditor->GlidPointX[x + MAP_X].x = x * 8;
		pMapEditor->GlidPointX[x + MAP_X].y = m_x_size;
	}

	for(y = 0;y < MAP_Y ;y++){
		pMapEditor->GlidPointY[y].x = 0;
		pMapEditor->GlidPointY[y].y = y * 8;
		pMapEditor->GlidPointY[y + MAP_Y].x = m_y_size;
		pMapEditor->GlidPointY[y + MAP_Y].y = y * 8;
	}
	
	CDialog::OnOK();
}
