// testDoc.cpp : CtestDoc クラスの実装
//

#include "stdafx.h"
#include "test.h"

#include "testDoc.h"
#include ".\testdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestDoc

IMPLEMENT_DYNCREATE(CtestDoc, CDocument)

BEGIN_MESSAGE_MAP(CtestDoc, CDocument)
	ON_COMMAND(ID_TEX_OPEN_2, OnTexOpen2)
	ON_COMMAND(ID_TEX_OPEN_1, OnTexOpen1)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
END_MESSAGE_MAP()


// CtestDoc コンストラクション/デストラクション

CtestDoc::CtestDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CtestDoc::~CtestDoc()
{
}

BOOL CtestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CtestDoc シリアル化

void CtestDoc::Serialize(CArchive& ar)
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


// CtestDoc 診断

#ifdef _DEBUG
void CtestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CtestDoc コマンド

//-------------------------------------------------------------------
// func   : void OnTexOpen2()
// param  : 無し
// print  : メニューの"画像ファイルを開く"をクリックすると呼ばれる
//-------------------------------------------------------------------
void CtestDoc::OnTexOpen2()
{
	// 画像ファイルを開いてパーティクルに使用する絵として設定します
	// メニューIDの違いで1と2が別で呼ばれるが内容は同じ

	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CStdioFile			file;
	CString				mainfile;
	char*				a;

	pApp->captureflg = true;
	CFileDialog filedlg(true,"jpg", NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, 
		"画像ファイル(*.jpg *.tga *.bmp)|*.jpg; *.tga; *.bmp||");
	if(filedlg.DoModal() != IDOK) return;
	
	a = new char[512];
	mainfile = filedlg.GetPathName();
	strcpy(a,mainfile);

	pApp->direct_x.mainbord->Initialize(pApp->direct_x.D3DDevice,a);

	pApp->drawflg = true;
	pApp->captureflg = false;

	delete a;
}


//-------------------------------------------------------------------
// func   : void OnTexOpen2()
// param  : 無し
// print  : メニューの"画像ファイルを開く"をクリックすると呼ばれる
//-------------------------------------------------------------------
void CtestDoc::OnTexOpen1()
{
	// 画像ファイルを開いてパーティクルに使用する絵として設定します
	// メニューIDの違いで1と2が別で呼ばれるが内容は同じ

	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CStdioFile			file;
	CString				mainfile;
	char*				a;

	pApp->captureflg = true;
	CFileDialog filedlg(true,"jpg", NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "画像ファイル(*.jpg *.tga *.bmp)|*.jpg; *.tga; *.bmp||");
	if(filedlg.DoModal() != IDOK) return;
	
	a = new char[512];
	mainfile = filedlg.GetPathName();
	strcpy(a,mainfile);

	pApp->direct_x.mainbord->Initialize(pApp->direct_x.D3DDevice,a);

	pApp->drawflg = true;
	pApp->captureflg = false;

	delete a;
}


//-------------------------------------------------------------------
// func   : void OnFileNew()
// param  : 無し
// print  : メニューの"新規作成"をクリックすると呼ばれる
//-------------------------------------------------------------------
void CtestDoc::OnFileNew()
{
	// 現在設定されているデータを全て破棄し、初期化します
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->fileload = false;
}


//-------------------------------------------------------------------
// func   : void OnFileOpen()
// param  : 無し
// print  : メニューの"データファイルを開く"をクリックすると呼ばれる
//-------------------------------------------------------------------
void CtestDoc::OnFileOpen()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CStdioFile			file;
	CString				mainfile;
	char*				a;

	pApp->captureflg = true;

	CFileDialog filedlg(true,"bin", NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "BINファイル(*.bin)|*.bin||");
	if(filedlg.DoModal() != IDOK) return;
	
	a = new char[512];
	mainfile = filedlg.GetPathName();
	strcpy(a,mainfile);

	pApp->filename = mainfile;
	pApp->fileload = true;
	pApp->captureflg = false;


}

//-------------------------------------------------------------------
// func   : void OnFileClose()
// param  : 無し
// print  : メニューの"データファイルを閉じる"をクリックすると呼ばれる
//-------------------------------------------------------------------
void CtestDoc::OnFileClose()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->fileload = false;
}


//-------------------------------------------------------------------
// func   : void OnFileSave()
// param  : 無し
// print  : メニューの"上書き保存"をクリックすると呼ばれる
//-------------------------------------------------------------------
void CtestDoc::OnFileSave()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// 上書き保存
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CStdioFile			file;
	CString				mainfile;
	char*				a;

	if(!pApp->fileload){
		// 新規にファイルを作成する場合

		pApp->captureflg = true;

		CFileDialog filedlg(false,"bin", NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXTENSIONDIFFERENT, "BINファイル(*.bin)|*.bin||");
		if(filedlg.DoModal() != IDOK) return;
		
		a = new char[512];
		mainfile = filedlg.GetPathName();
		strcpy(a,mainfile);

		pApp->filename = mainfile;
		pApp->fileload = true;

		pApp->captureflg = false;

	}
	else {
		// ファイルが作成されている、もしくはすでに読み込まれている場合

		//------------ ファイル書き込み ------------------------------------

		//　書き込みファイルを開く
		a = new char[512];

		strcpy(a,pApp->filename);

		FILE* wfile = fopen(a,"wb");

		//　ファイルヘッダ
		fwrite("orz",sizeof(char),3,wfile);


		// 書き込み処理・・・・・・



		//　書き込みファイルを閉じる
		fclose(wfile);
		wfile = NULL;

	}
}


//-------------------------------------------------------------------
// func   : void OnFileSaveAs()
// param  : 無し
// print  : メニューの"名前をつけて保存"をクリックすると呼ばれる
//-------------------------------------------------------------------
void CtestDoc::OnFileSaveAs()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	CtestApp* pApp = (CtestApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CStdioFile			file;
	CString				mainfile;
	char*				a;

	// ファイルを開くダイアログを呼び出しファイル名を作成
	pApp->captureflg = true;

	CFileDialog filedlg(false,"bin", NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXTENSIONDIFFERENT, "BINファイル(*.bin)|*.bin||");
	if(filedlg.DoModal() != IDOK) return;
	
	a = new char[512];
	mainfile = filedlg.GetPathName();
	strcpy(a,mainfile);

	pApp->filename = mainfile;
	pApp->fileload = true;
	pApp->captureflg = false;

	//------------ ファイル書き込み ------------------------------------

	//　書き込みファイルを開く
	FILE* wfile = fopen(a,"wb");

	//　ファイルヘッダ
	fwrite("orz",sizeof(char),3,wfile);



	// 書き込み処理・・・・・・



	//　書き込みファイルを閉じる
	fclose(wfile);
	wfile = NULL;

}
