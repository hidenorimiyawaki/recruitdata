// AttrData.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapEditor.h"
#include "AttrData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttrData

CAttrData::CAttrData()
{
	AttrData = 0;
}

CAttrData::~CAttrData()
{
}


BEGIN_MESSAGE_MAP(CAttrData, CWnd)
	//{{AFX_MSG_MAP(CAttrData)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAttrData メッセージ ハンドラ

UINT CAttrData::GetAttrDatta(int x, int y)
{
	return	AttrData;
}

void CAttrData::SetAttrData(int x, int y, int pat)
{
	AttrData = pat;
}


