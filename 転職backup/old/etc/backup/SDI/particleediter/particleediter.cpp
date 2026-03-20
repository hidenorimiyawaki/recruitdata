// particleediter.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "particleediter.h"
#include "MainFrm.h"

#include "particleediterDoc.h"
#include "particleediterView.h"
#include ".\particleediter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CparticleediterApp

BEGIN_MESSAGE_MAP(CparticleediterApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CparticleediterApp コンストラクション

CparticleediterApp::CparticleediterApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CparticleediterApp オブジェクトです。

CparticleediterApp theApp;

// CparticleediterApp 初期化

BOOL CparticleediterApp::InitInstance()
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
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CparticleediterDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CparticleediterView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、 False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出してください。
	//  SDI アプリケーションでは、ProcessShellCommand の直後にこの呼び出しが発生しなければなりません。

	m_pMainWnd->SetTimer(1,FRAME_RATE,NULL);
	if(direct_x.Initialize(m_pMainWnd->m_hWnd) != S_OK) return false;
	EditDialog.Create(IDD_EDIT_DIALOG, m_pMainWnd);


	POSITION3 work;

	// アイドル時間に使用するタイマー初期化
	time = bftime = frame_count = 0;				// 各時間管理変数初期化
	end_check = 99;

	char* file_name_bg_mesh[] = {
		".\\texture\\shadow.tga",
		".\\texture\\Effect1.tga",
	};

	direct_x.mainbord = new CBillbord;
	direct_x.mainbord->Initialize(direct_x.D3DDevice,file_name_bg_mesh[0]);

	particle = new CParticle[PARTICLE_MAX];

	work.x = EditDialog.m_Edit_Pos_X;
	work.y = EditDialog.m_Edit_Pos_Y;
	work.z = EditDialog.m_Edit_Pos_Z;
	for(int i = 0;i< PARTICLE_MAX;i++){
		particle[i].EffectSet(&work);
	}
	return TRUE;
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
void CparticleediterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CparticleediterApp メッセージ ハンドラ


BOOL CparticleediterApp::OnIdle(LONG lCount)
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	return CWinApp::OnIdle(lCount);
}

int CparticleediterApp::ExitInstance()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	direct_x.Cleanup();
	delete[] particle; 

	return CWinApp::ExitInstance();
}
