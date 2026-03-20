// MapEditorDoc.cpp : CMapEditorDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "MapEditor.h"

#include "MapEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc

IMPLEMENT_DYNCREATE(CMapEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CMapEditorDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc クラスの構築/消滅

CMapEditorDoc::CMapEditorDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CMapEditorDoc::~CMapEditorDoc()
{
}

BOOL CMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc シリアライゼーション

void CMapEditorDoc::Serialize(CArchive& ar)
{
	CMapEditorApp* pMapEditor = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pMapEditor);

	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
		ar.Write(&pMapEditor->MapData,sizeof(CMapData));
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
		ar.Read(&pMapEditor->MapData,sizeof(CMapData));
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc クラスの診断

#ifdef _DEBUG
void CMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEditorDoc コマンド
