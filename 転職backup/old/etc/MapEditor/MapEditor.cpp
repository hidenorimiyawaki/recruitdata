// MapEditor.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "MapEditor.h"

#include "MainFrm.h"
#include "MapEditorDoc.h"
#include "MapEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp

BEGIN_MESSAGE_MAP(CMapEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CMapEditorApp)
	ON_COMMAND(AFX_ID_ATTR_DISP, OnAttrDisp)
	ON_COMMAND(AFX_ID_DATA_OUTPUT, OnDataOutput)
	ON_COMMAND(AFX_ID_MODE_EDITMAP, OnModeEditmap)
	ON_COMMAND(AFX_ID_MODESETATTR, OnModesetattr)
	ON_COMMAND(AFX_ID_MAKE_DATA, OnIdMakeData)
	ON_COMMAND(AFX_ID_LOAD_BMP, OnLoadBmp)
	ON_COMMAND(AFX_ID_CURSOL_SIZE, OnCursolSize)
	ON_COMMAND(AFX_ID_BMP_GLID, OnBmpGlid)
	ON_COMMAND(AFX_ID_MAIN_GLID, OnMainGlid)
	ON_COMMAND(AFX_ID_SET_GLID_COLOR, OnSetGlidColor)
	ON_COMMAND(AFX_ID_DAT_DATA_OUTPUT, OnDatDataOutput)
	ON_COMMAND(AFX_ID_DAT_DATA_LOAD, OnDatDataLoad)
	ON_COMMAND(AFX_ID_SET_ATTR, OnSetAttr)
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp クラスの構築

CMapEditorApp::CMapEditorApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。

	NewChipNo = 0;
	LoadBitmap = false;

	ScrollPoint.x = 0;
	ScrollPoint.y = 0;

	DispAttr = false;
	MapMode = true;
	AttrMode = false;
	BmpDlgGlid = false;
	MainGlid = false;

	MapData = new CMapData[SizeDialog.MAP_X * SizeDialog.MAP_Y];
	AttrData = new CAttrData[SizeDialog.MAP_X * SizeDialog.MAP_Y];
	GlidPointX = new CPoint[SizeDialog.MAP_X * 2];
	GlidPointY = new CPoint[SizeDialog.MAP_Y * 2];

	UINT x,y;

	for(x = 0; x < SizeDialog.MAP_X;x++){
		GlidPointX[x].x = x * 8;
		GlidPointX[x].y = 0;
		GlidPointX[x + SizeDialog.MAP_X].x = x * 8;
		GlidPointX[x + SizeDialog.MAP_X].y = SizeDialog.m_x_size;
	}

	for(y = 0;y < SizeDialog.MAP_Y ;y++){
		GlidPointY[y].x = 0;
		GlidPointY[y].y = y * 8;
		GlidPointY[y + SizeDialog.MAP_Y].x = SizeDialog.m_y_size;
		GlidPointY[y + SizeDialog.MAP_Y].y = y * 8;
	}
	
	
}

CMapEditorApp::~CMapEditorApp()
{
	delete [] MapData;
	delete [] AttrData;
	delete [] GlidPointX;
	delete [] GlidPointY;

}
/////////////////////////////////////////////////////////////////////////////
// 唯一の CMapEditorApp オブジェクト

CMapEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp クラスの初期化

BOOL CMapEditorApp::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さく
	// したければ以下の特定の初期化ルーチンの中から不必要なもの
	// を削除してください。

#ifdef _AFXDLL
	Enable3dControls();		// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif

	// 設定が保存される下のレジストリ キーを変更します。
	// TODO: この文字列を、会社名または所属など適切なものに
	// 変更してください。
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMapEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CMapEditorView));
	AddDocTemplate(pDocTemplate);

	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// コマンドラインでディスパッチ コマンドを指定します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	BmpDialog.Create(IDD_BMP_DIALOG,m_pMainWnd);

	CMenu* menu = m_pMainWnd->GetMenu();
	menu->CheckMenuItem(AFX_ID_MODE_EDITMAP , MF_BYCOMMAND | MF_CHECKED);

	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard 仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMapEditorApp::OnAttrDisp() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	//-----------メニュー項目のチェックマーク設定------------------S
	CMenu* menu = m_pMainWnd->GetMenu();

	if(DispAttr){
		menu->CheckMenuItem(AFX_ID_ATTR_DISP , MF_BYCOMMAND | MF_UNCHECKED);
		DispAttr = false;
	}
	else{
		menu->CheckMenuItem(AFX_ID_ATTR_DISP , MF_BYCOMMAND | MF_CHECKED);
		DispAttr = true;
	}
	//-----------メニュー項目のチェックマーク設定------------------E


	//-----------ビューの再描画処理処理のための準備----------------S
	POSITION pos = GetFirstDocTemplatePosition();

	CDocTemplate* DocTemp = GetNextDocTemplate(pos);

	POSITION Defpos = DocTemp->GetFirstDocPosition();

	CDocument* doc = DocTemp->GetNextDoc(Defpos);

	doc->UpdateAllViews(NULL);
}

void CMapEditorApp::OnDataOutput() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				subfile;
	CString				workfile;
	CString				filename;

	CFileDialog filedlg(false,"c", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT  , "Cファイル(*.c)|*.c||");
	if(filedlg.DoModal() != IDOK) return; 

	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {
		UINT x,y;
		int wk_x,wk_y;
		// Ｃ言語の配列の形で出力
		file.WriteString("//---------------------------------\n");
		file.WriteString("//  [ MapEditor ] マップデータ\n");
		file.WriteString("//---------------------------------\n\n");

		file.WriteString("\nu16 ");
		workfile.Format("%s",filename);		file.WriteString(workfile);
		file.WriteString("_map[");
		workfile.Format("%d*", SizeDialog.MAP_Y);		file.WriteString(workfile);
		workfile.Format("%d",  SizeDialog.MAP_X);		file.WriteString(workfile);
		
		file.WriteString("] = {\n");

		for(y = 0; y < SizeDialog.MAP_Y; y++) {
			file.WriteString("\t{");
			for(x = 0; x < SizeDialog.MAP_X; x++) {

				wk_y = y * SizeDialog.MAP_X;
				wk_x = x + wk_y;

				workfile.Format("0x%x", MapData[wk_x].Palette);
				file.WriteString(workfile);

				workfile.Format("%03x,", MapData[wk_x].MapData);
				file.WriteString(workfile);
			}
			file.WriteString("},\n");
		}
		file.WriteString("};\n\n");

		file.WriteString("//---------------------------------\n");
		file.WriteString("//  [ MapEditor ] 属性データ\n");
		file.WriteString("//---------------------------------\n\n");

		file.WriteString("\nu8 ");
		workfile.Format("%s",filename);		file.WriteString(workfile);
		file.WriteString("_data[");
		workfile.Format("%d*", SizeDialog.MAP_Y);		file.WriteString(workfile);
		workfile.Format("%d",  SizeDialog.MAP_X);		file.WriteString(workfile);
		
		file.WriteString("] = {\n");

		for(y = 0; y < SizeDialog.MAP_Y; y++) {
			file.WriteString("\t{");
			for(x = 0; x < SizeDialog.MAP_X; x++) {
				wk_y = y * SizeDialog.MAP_X;
				wk_x = x + wk_y;
				workfile.Format("0x%02x,", AttrData[wk_x].AttrData);
				file.WriteString(workfile);
			}
			file.WriteString("},\n");
		}
		file.WriteString("};\n\n");

		file.WriteString("//---------------------------------\n");
		file.WriteString("//  End Of File\n");
		file.WriteString("//---------------------------------\n");

		file.Close();
	}

}

void CMapEditorApp::OnModeEditmap() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
		//-----------メニュー項目のチェックマーク設定------------------S
	CMenu* menu = m_pMainWnd->GetMenu();


	menu->CheckMenuItem(AFX_ID_MODE_EDITMAP , MF_BYCOMMAND | MF_CHECKED);	
	menu->CheckMenuItem(AFX_ID_MODE_SETATTR , MF_BYCOMMAND | MF_UNCHECKED);
	AttrMode = false;
	MapMode = true;

	//-----------メニュー項目のチェックマーク設定------------------E


	//-----------ビューの再描画処理処理のための準備----------------S
	POSITION pos = GetFirstDocTemplatePosition();

	CDocTemplate* DocTemp = GetNextDocTemplate(pos);

	POSITION Defpos = DocTemp->GetFirstDocPosition();

	CDocument* doc = DocTemp->GetNextDoc(Defpos);

	doc->UpdateAllViews(NULL);
}

void CMapEditorApp::OnModesetattr() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
		//-----------メニュー項目のチェックマーク設定------------------S
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_MODE_EDITMAP , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_MODE_SETATTR , MF_BYCOMMAND | MF_CHECKED);
	MapMode = false;
	AttrMode = true;
	
	//-----------メニュー項目のチェックマーク設定------------------E

	//-----------ビューの再描画処理処理のための準備----------------S
	POSITION pos = GetFirstDocTemplatePosition();

	CDocTemplate* DocTemp = GetNextDocTemplate(pos);

	POSITION Defpos = DocTemp->GetFirstDocPosition();

	CDocument* doc = DocTemp->GetNextDoc(Defpos);

	doc->UpdateAllViews(NULL);
}

void CMapEditorApp::OnIdMakeData() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if(SizeDialog.DoModal() != IDOK) return;
	
}

void CMapEditorApp::OnLoadBmp() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CString filename;		// ＢＭＰファイル名が入る変数

	// ファイルのコモンダイアログを開いてＢＭＰファイル名を取得
	CFileDialog myDLG(true, "bmp", NULL, OFN_HIDEREADONLY, "BMPﾌｧｲﾙ(*.bmp)|*.bmp||");
	if(myDLG.DoModal() != IDOK) return;

	// ＢＭＰファイル名をパス込みで取得
	filename = myDLG.GetPathName();

	if(LoadBitmap) {
		// 一度読み込まれていたら以前のビットマップを廃棄
		Bitmap.Detach();
		DC.DeleteDC();
	}
	// ファイルからビットマップを読み込む
	hBitmap = (HBITMAP)LoadImage(0, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	Bitmap.Attach(hBitmap);		// CBitmap にビットマップを割り当てる
	DC.CreateCompatibleDC(0);	// メモリに互換ＤＣを作成
	LoadBitmap = true;			// ＢＭＰロードフラグをセット

	// ダイアログを再描画
	BmpDialog.Invalidate(true);

	// ビューを再描画
	POSITION posDocTpl = GetFirstDocTemplatePosition();		// 最初のテンプレートの位置を取得
	CDocTemplate* docTpl = GetNextDocTemplate(posDocTpl);	// 最初のテンプレートを取得

	POSITION posDoc = docTpl->GetFirstDocPosition();		// 最初のドキュメントの位置を取得
	CDocument* document = docTpl->GetNextDoc(posDoc);		// 最初のドキュメントを取得

	document->UpdateAllViews(NULL);							// ドキュメントからビューを更新
    
	//----- ここまで -----
	
}

void CMapEditorApp::OnCursolSize() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CSDialog.work_x = CSDialog.m_cursol_x;
	CSDialog.work_y = CSDialog.m_cursol_y;
	if(CSDialog.DoModal() != IDOK) return;
	
}

void CMapEditorApp::OnBmpGlid() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	//-----------メニュー項目のチェックマーク設定------------------S
	CMenu* menu = m_pMainWnd->GetMenu();

	if(BmpDlgGlid){
		menu->CheckMenuItem(AFX_ID_BMP_GLID , MF_BYCOMMAND | MF_UNCHECKED);
		BmpDlgGlid = false;
	}
	else{
		menu->CheckMenuItem(AFX_ID_BMP_GLID , MF_BYCOMMAND | MF_CHECKED);
		BmpDlgGlid = true;
	}
	//-----------メニュー項目のチェックマーク設定------------------E


	//-----------ビューの再描画処理処理のための準備----------------S
	POSITION pos = GetFirstDocTemplatePosition();

	CDocTemplate* DocTemp = GetNextDocTemplate(pos);

	POSITION Defpos = DocTemp->GetFirstDocPosition();

	CDocument* doc = DocTemp->GetNextDoc(Defpos);

	doc->UpdateAllViews(NULL);

}

void CMapEditorApp::OnMainGlid() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	//-----------メニュー項目のチェックマーク設定------------------S
	CMenu* menu = m_pMainWnd->GetMenu();

	if(MainGlid){
		menu->CheckMenuItem(AFX_ID_MAIN_GLID , MF_BYCOMMAND | MF_UNCHECKED);
		MainGlid = false;
	}
	else{
		menu->CheckMenuItem(AFX_ID_MAIN_GLID , MF_BYCOMMAND | MF_CHECKED);
		MainGlid = true;
	}
	//-----------メニュー項目のチェックマーク設定------------------E


	//-----------ビューの再描画処理処理のための準備----------------S
	POSITION pos = GetFirstDocTemplatePosition();

	CDocTemplate* DocTemp = GetNextDocTemplate(pos);

	POSITION Defpos = DocTemp->GetFirstDocPosition();

	CDocument* doc = DocTemp->GetNextDoc(Defpos);

	doc->UpdateAllViews(NULL);
	
}

void CMapEditorApp::OnSetGlidColor() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	if(GlidColorDialog.DoModal() != IDOK) return;
	
}

void CMapEditorApp::OnDatDataOutput() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;
	UINT				x,y;
	int					wk_x,wk_y;

	CFileDialog filedlg(false,"MEF", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "MapEditor専用ファイル(*.MEF)|*.MEF||");
	if(filedlg.DoModal() != IDOK) return; 

	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {
		workfile.Format("%04d\n",SizeDialog.m_x_size);
		file.WriteString(workfile);
		workfile.Format("%04d\n",SizeDialog.m_y_size);
		file.WriteString(workfile);

		for(y = 0; y < SizeDialog.MAP_Y; y++) {
			for(x = 0; x < SizeDialog.MAP_X; x++) {
				wk_y = y * SizeDialog.MAP_X;
				wk_x = x + wk_y;

				workfile.Format("%04d\n", MapData[wk_x].MapData);
				file.WriteString(workfile);
			}
		}
		
		for(y = 0; y < SizeDialog.MAP_Y; y++) {
			for(x = 0; x < SizeDialog.MAP_X; x++) {
				wk_y = y * SizeDialog.MAP_X;
				wk_x = x + wk_y;

				workfile.Format("%04d\n", MapData[wk_x].Palette);
				file.WriteString(workfile);
			}
		}

		for(y = 0; y < SizeDialog.MAP_Y; y++) {
			for(x = 0; x < SizeDialog.MAP_X; x++) {
				wk_y = y * SizeDialog.MAP_X;
				wk_x = x + wk_y;
				workfile.Format("%04d\n", AttrData[wk_x].AttrData);
				file.WriteString(workfile);
			}
		}

		file.Close();
	}
	
}

void CMapEditorApp::OnDatDataLoad() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;
	char*				a;
	UINT*				x;
	int					work_x , work_y,work;
	int					i;


	CFileDialog filedlg(true,"MEF", NULL, OFN_HIDEREADONLY | OFN_READONLY, "MapEditor専用ファイル(*.MEF)|*.MEF||");
	if(filedlg.DoModal() != IDOK) return;
	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeRead,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {
		a = new char[4];
		file.ReadString(workfile);
		strcpy(a,workfile);
		work_x = (a[0]-48) * 1000;
		work_x += (a[1]-48) * 100;
		work_x += (a[2]-48) * 10;
		work_x += (a[3]-48) * 1;
		SizeDialog.m_x_size = work_x;
		SizeDialog.MAP_X = SizeDialog.m_x_size / 8;

		file.ReadString(workfile);
		strcpy(a,workfile);
		work_y = (a[0]-48) * 1000;
		work_y += (a[1]-48) * 100;
		work_y += (a[2]-48) * 10;
		work_y += (a[3]-48) * 1;
		SizeDialog.m_y_size = work_y;
		SizeDialog.MAP_Y = SizeDialog.m_y_size / 8;

		
	if(MapData != 0){
		delete [] MapData;
	}
	if(AttrData != 0){
		delete [] AttrData;
	}
	if(GlidPointX != 0){
		delete [] GlidPointX;
	}
	if(GlidPointY != 0){
		delete [] GlidPointY;
	}

	MapData = new CMapData[SizeDialog.MAP_X * SizeDialog.MAP_Y];
	AttrData = new CAttrData[SizeDialog.MAP_X * SizeDialog.MAP_Y];
	GlidPointX = new CPoint[SizeDialog.MAP_X * 2];
	GlidPointY = new CPoint[SizeDialog.MAP_Y * 2];


	UINT x,y;
	int wk_x,wk_y;

	for(x = 0; x < SizeDialog.MAP_X;x++){
		GlidPointX[x].x = x * 8;
		GlidPointX[x].y = 0;
		GlidPointX[x + SizeDialog.MAP_X].x = x * 8;
		GlidPointX[x + SizeDialog.MAP_X].y = SizeDialog.m_x_size;
	}

	for(y = 0;y < SizeDialog.MAP_Y ;y++){
		GlidPointY[y].x = 0;
		GlidPointY[y].y = y * 8;
		GlidPointY[y + SizeDialog.MAP_Y].x = SizeDialog.m_y_size;
		GlidPointY[y + SizeDialog.MAP_Y].y = y * 8;
	}
	for(y = 0; y < SizeDialog.MAP_Y; y++) {
		for(x = 0; x < SizeDialog.MAP_X; x++) {
			wk_y = y * SizeDialog.MAP_X;
			wk_x = x + wk_y;
			file.ReadString(workfile);
			strcpy(a,workfile);
			work = (a[0]-48) * 1000;
			work += (a[1]-48) * 100;
			work += (a[2]-48) * 10;
			work += (a[3]-48) * 1;

			MapData[wk_x].MapData = work;

		}
	}

	for(y = 0; y < SizeDialog.MAP_Y; y++) {
		for(x = 0; x < SizeDialog.MAP_X; x++) {
			wk_y = y * SizeDialog.MAP_X;
			wk_x = x + wk_y;
			file.ReadString(workfile);
			strcpy(a,workfile);
			work = (a[0]-48) * 1000;
			work += (a[1]-48) * 100;
			work += (a[2]-48) * 10;
			work += (a[3]-48) * 1;

			MapData[wk_x].Palette = work;

		}
	}

	for(y = 0; y < SizeDialog.MAP_Y; y++) {
		for(x = 0; x < SizeDialog.MAP_X; x++) {
			wk_y = y * SizeDialog.MAP_X;
			wk_x = x + wk_y;
			file.ReadString(workfile);
			strcpy(a,workfile);
			work = (a[0]-48) * 1000;
			work += (a[1]-48) * 100;
			work += (a[2]-48) * 10;
			work += (a[3]-48) * 1;

			AttrData[wk_x].AttrData = work;

		}
	}

		file.Close();

	}
}


void CMapEditorApp::OnSetAttr() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
		if(DataDialog.DoModal() != IDOK) return;

	
}
