// test.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "test.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "testDoc.h"
#include "testView.h"
#include ".\test.h"

#ifdef _cDEBUG
#define new DEBUG_NEW
#endif


// CtestApp

BEGIN_MESSAGE_MAP(CtestApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_SET_COLOR_A, OnSetColorA)
	ON_COMMAND(ID_SET_COLOR_B, OnSetColorB)
END_MESSAGE_MAP()


// CtestApp コンストラクション

CtestApp::CtestApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CtestApp オブジェクトです。

CtestApp theApp;

// CtestApp 初期化

BOOL CtestApp::InitInstance()
{
	// アプリケーション　マニフェストが　visual スタイルを有効にするために、
	// ComCtl32.dll バージョン 6　以降の使用を指定する場合は、
	// Windows XP に　InitCommonControls() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	InitCommonControls();

	CWinApp::InitInstance();

	// OLE ライブラリを初期化します。
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 標準初期化
	// これらの機能を使わずに、最終的な実行可能ファイルのサイズを縮小したい場合は、
	// 以下から、不要な初期化ルーチンを
	// 削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: この文字列を、会社名または組織名などの、
	// 適切な文字列に変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	LoadStdProfileSettings(0);  // 標準の INI ファイルのオプションをロードします (MRU を含む)
	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_testTYPE,
		RUNTIME_CLASS(CtestDoc),
		RUNTIME_CLASS(CChildFrame), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CtestView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// メイン MDI フレーム ウィンドウを作成します。
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出します。
	//  MDI アプリケーションでは、この呼び出しは、m_pMainWnd を設定した直後に発生しなければなりません。
	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、 False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();


	//-------------------------- 各種初期化 ----------------------------------

	// 仮テクスチャファイル列挙
	char* file_name_bg_mesh[] = {
		".\\texture\\shadow.tga",
		".\\texture\\Effect1.tga",
		".\\texture\\smoke.bmp",
		"NULL",
	};

	// パラメータ保存用変数初期化
	pos.x = pos.y = pos.z = 0;
	posflg.x = posflg.y = posflg.z = posflg.w = false;
	rot.x = rot.y = rot.z = 0;
	rotflg.x = rotflg.y = rotflg.z = rotflg.w = false;
	scale.x = scale.y = scale.z = 1;
	scaleflg.x = scaleflg.y = scaleflg.z = scaleflg.w = false;
	pos.w = scale.w = 100;
	rot.w = 1;
	gravity = 0;
	dir = 0;

	// ステータス設定ダイアログ構築
	EditDialog.Create(IDD_EDIT_DIALOG, m_pMainWnd);

	// テクスチャ初期化および読み込み
	direct_x.mainbord = new CBillbord;
	direct_x.mainbord->Initialize(direct_x.D3DDevice,file_name_bg_mesh[0]);

	// パーティクル初期化
	particle = new CParticle[PARTICLE_MAX];
	POSITION3 work;
	work.x = work.y = work.z = 0;
	for(int i = 0;i< 100;i++){
		particle[i].EffectSet(&work);
	}

	// メニュー項目の設定
	CMenu* menu = m_pMainWnd->GetMenu();			// メニュー領域のポインタ取得
	menu->CheckMenuItem(ID_SET_STATUS_A , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(ID_SET_STATUS_B , MF_BYCOMMAND | MF_CHECKED);

	// モード判別フラグ初期化
	fileload = false;
	drawflg = false;
	captureflg = false;

	return TRUE;
}

// CtestApp メッセージ ハンドラ


int CtestApp::ExitInstance()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	direct_x.Cleanup();

	return CWinApp::ExitInstance();
}

void CtestApp::OnSetColorA()
{
	// カラーダイアログが開いた場合に子ウィンドウの強制マウスキャプチャを解除する
	captureflg = true;
	ColorDialog.DoModal();
	captureflg = false;
}

void CtestApp::OnSetColorB()
{
	// カラーダイアログが開いた場合に子ウィンドウの強制マウスキャプチャを解除する
	captureflg = true;
	ColorDialog.DoModal();
	captureflg = false;
}


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CtestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


