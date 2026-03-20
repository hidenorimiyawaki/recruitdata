// particleediterDoc.cpp : CparticleediterDoc クラスの実装
//

#include "stdafx.h"
#include "particleediter.h"

#include "particleediterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CparticleediterDoc

IMPLEMENT_DYNCREATE(CparticleediterDoc, CDocument)

BEGIN_MESSAGE_MAP(CparticleediterDoc, CDocument)
END_MESSAGE_MAP()


// CparticleediterDoc コンストラクション/デストラクション

CparticleediterDoc::CparticleediterDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CparticleediterDoc::~CparticleediterDoc()
{
}

BOOL CparticleediterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CparticleediterDoc シリアル化

void CparticleediterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}


// CparticleediterDoc 診断

#ifdef _DEBUG
void CparticleediterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CparticleediterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CparticleediterDoc コマンド
