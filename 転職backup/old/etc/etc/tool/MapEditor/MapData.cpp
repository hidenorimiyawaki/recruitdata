// MapData.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapData

CMapData::CMapData()
{
	MapData = 0;
	Palette = 0;
}

CMapData::~CMapData()
{
}


BEGIN_MESSAGE_MAP(CMapData, CWnd)
	//{{AFX_MSG_MAP(CMapData)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMapData メッセージ ハンドラ

void CMapData::SetMapData(int x, int y, int pat)
{
	MapData = pat;
}

UINT CMapData::GetMapData(int x, int y)
{
	return	MapData;
}
