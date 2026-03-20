// SpriteTool.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "SpriteTool.h"

#include "MainFrm.h"
#include "SpriteToolDoc.h"
#include "SpriteToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolApp

BEGIN_MESSAGE_MAP(CSpriteToolApp, CWinApp)
	//{{AFX_MSG_MAP(CSpriteToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(AFX_ID_SNAP_ON, OnIdSnapOn)
	ON_COMMAND(AFX_ID_SNAP_OFF, OnIdSnapOff)
	ON_COMMAND(AFX_ID_GLID_ON, OnIdGlidOn)
	ON_COMMAND(AFX_ID_GLID_OFF, OnIdGlidOff)
	ON_COMMAND(ID_GLID_TYPE_OPEN, OnGlidTypeOpen)
	ON_COMMAND(AFX_ID_ALPHA_ON, OnIdAlphaOn)
	ON_COMMAND(AFX_ID_ALPHA_OFF, OnIdAlphaOff)
	ON_COMMAND(AFX_ID_MODE_DIVIDE, OnIdModeDivide)
	ON_COMMAND(AFX_ID_MODE_SET, OnIdModeSet)
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolApp クラスの構築

CSpriteToolApp::CSpriteToolApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CSpriteToolApp オブジェクト

CSpriteToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolApp クラスの初期化

BOOL CSpriteToolApp::InitInstance()
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

	LoadStdProfileSettings(0);  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSpriteToolDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CSpriteToolView));
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

	//------------------自己初期化------------------------------S

	// DirectX初期化
	Dx.Initialize(m_pMainWnd->m_hWnd);							// DirectX初期化呼び出し

	// ダイアログ作成
	CashDialog.Create(IDD_CASH_DIALOG, m_pMainWnd);				// グリッドキャッシュ設定ダイアログ作成

	// グリッドキャッシュの初期化設定
	CString		work;											// グリッドキャッシュの初期データ設定用ワーク変数
	work.Format("Blank(left,top,right,bottom）// コメント");	// 初期データの文字列設定
	CashDialog.m_List_Cash.InitStorage(50,32767);				// グリッドとして設定できるデータの最大数設定
	CashDialog.m_List_Cash.InsertString(0,work);				// そして初期文字列配置
	CashDialog.m_List_Cash.SetCurSel(0);						// ついでにカーソルを初期位置にあわせる

	// グリッドキャッシュのカウンタ初期化
	cash_cnt = 0;												// カウントを0に設定

	// アイドル時間に使用するタイマー初期化
	time = bftime = anime_time = frame_count = 0;				// 各時間管理変数初期化

	// グリッドのための各種ブラシ・ペン初期化
	CursolBrush.CreateStockObject(HOLLOW_BRUSH);				// グリッド・カーソル用の中抜きブラシ
	CursolPen.CreatePen(PS_SOLID,2,RGB(255,255,0));				// カーソルを描画するためのペン(デフォルトで黄色)
	GlidPen.CreatePen(PS_SOLID,2,RGB(255,255,255));				// グリッド(大枠)としてのペンを作成(デフォルトで白、色の変更可能)
	HollowGlidPen.CreatePen(PS_SOLID,1,RGB(80,80,80));			// グリッド(間の線)としてのペンを作成(デフォルトで灰色、色の変更不可能)

	// 各種保存用データを一気に初期化
	for(int i = 0; i < MAX_DATA;i++){							// データの最大数だけ
		data[i][TOP] = 0;										// 保存用のデータ(TOP)を初期化
		data[i][LEFT] = 0;										// 保存用のデータ(LEFT)を初期化
		data[i][DOWN] = 0;										// 保存用のデータ(DOWN)を初期化
		data[i][RIGHT] = 0;										// 保存用のデータ(RIGHT)を初期化
		frame_data[i] = 0;										// 保存用の表示する時間を初期化
		next_frame[i] = 0;										// 保存用の次に参照するデータを初期化
		attach_kukei[i] = 0;									// 保存用の参照する矩形の番号用データを初期化
	}
	for(i = 0; i < CASH_MAX;i++){								// キャッシュの最大数だけ
		cash_string[i].Format("");								// 文字列初期化
		cash_data[i].top = 0;									// 頂点初期化
		cash_data[i].left = 0;									// 頂点初期化
		cash_data[i].bottom = 0;								// 頂点初期化
		cash_data[i].right = 0;									// 頂点初期化

	}

	// アニメーション用のフラグ＋描画フラグ初期化
	animation_flg = draw_flg = OFF;								// 描画系のフラグをOFFで初期化

	// グリッドの初期幅設定
	GLID_WIDTH = GLID_HEIGHT = 16;								// グリッドの幅を16×16で初期化

	// 一発目の描画
	DrawExec();													// 描画

	// メニューバー設定
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_GLID_ON , MF_BYCOMMAND | MF_CHECKED);
	GlidFlg = ON;												// 初期状態はグリッドONで
	menu->CheckMenuItem(AFX_ID_SNAP_ON , MF_BYCOMMAND | MF_CHECKED);
	SnapFlg = ON;												// ついでにスナップもONで
	menu->CheckMenuItem(AFX_ID_ALPHA_ON , MF_BYCOMMAND | MF_CHECKED);
	AlphaFlg = ON;												// ついでにスナップもONで

	menu->CheckMenuItem(AFX_ID_MODE_DIVIDE , MF_BYCOMMAND | MF_CHECKED);
	mode = MODE_DIVIDE;
	//------------------自己初期化------------------------------E

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

// ダイアログを実行するためのアプリケーション コマンド
void CSpriteToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolApp メッセージ ハンドラ
void CSpriteToolApp::DrawExec()
{
	// メインウィンドウに最終目的としての画面を描画

	CRect	clrect;													// クライアント領域のサイズ用変数
	HDC		hdc;													// デバイスコンテキスト変数
	CPoint	work;													// 座標用変数(ワーク)
	UINT	i;														// カウンタ用変数

	hdc = GetDC(m_pMainWnd->m_hWnd);								// デバイスコンテキスト取得
	SelectObject(hdc,GlidPen);										// グリッド用のペン選択
	SelectObject(hdc,CursolBrush);									// 中抜きブラシ選択

	if(mode == MODE_DIVIDE){
		Dx.Render();													// DirectXの描画を呼び出し

		if(GlidFlg == ON){
			// 横幅用グリッドの描画										// グリッドは表示するのか？ならば
			for(i = 0;i < (Dx.mainbord.ita.Width / GLID_WIDTH) +1 ;i++){// グリッドとして引かねばならない分ループ
				work.x = GLID_WIDTH * i + 128;							// グリッドの引くべき位置を設定(X座標)
				work.y = 0;												// グリッドの引くべき位置を設定(Y座標)
				if((i % 4) == 0){										// グリッドが太枠として引かねばならないならば
					SelectObject(hdc,GlidPen);							// グリッド用のペンを設定
				}
				else{													// そうでないならば
					SelectObject(hdc,HollowGlidPen);					// 灰色ペンを設定
				}
				MoveToEx(hdc,work.x,work.y,NULL);						// で、引き始めの位置に移動
				work.y = Dx.mainbord.ita.Height;						// 引き終わりの位置を設定し
				LineTo(hdc,work.x,work.y);								// 線を引く
			}

			// 縦幅用グリッドの描画
			for(i = 0;i < (Dx.mainbord.ita.Height / GLID_HEIGHT) +1 ;i++){// グリッドとして引かねばならない分ループ
				work.x = 128;											// グリッドの引くべき位置を設定(X座標)
				work.y = GLID_HEIGHT * i;								// グリッドの引くべき位置を設定(Y座標)
				if((i % 4) == 0){										// グリッドが太枠として引かねばならないならば
					SelectObject(hdc,GlidPen);							// グリッド用のペンを設定
				}
				else{													// そうでないならば
					SelectObject(hdc,HollowGlidPen);					// 灰色ペンを設定
				}
				MoveToEx(hdc,work.x,work.y,NULL);						// で、引き始めの位置に移動
				work.x = Dx.mainbord.ita.Width + 128;					// 引き終わりの位置を設定し
				LineTo(hdc,work.x,work.y);								// 線を引く
			}
		}

	}
	// カーソル描画
	SelectObject(hdc,CursolPen);									// グリッドが引き終わったら、カーソル枠用ペン設定
	Rectangle(hdc,start.x,start.y,end.x,end.y);						// 今の分のカーソルを引く
	
	ReleaseDC(m_pMainWnd->m_hWnd,hdc);								// 用済みなのでデバイスコンテキスト開放

}

BOOL CSpriteToolApp::OnIdle(LONG lCount) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	if(draw_flg == 1){												// 再描画要請？
		DrawExec();													// 描画関数呼び出し
		draw_flg = 0;												// 描画フラグをOFF
	}
	return CWinApp::OnIdle(lCount);
}
void CSpriteToolApp::DrawExecEx()
{
	// メインウィンドウにワークとしての画面(グリッドキャッシュ用)を描画してからグリッドキャッシュに渡す

	HDC		hdc;													// デバイスコンテキスト変数
	CDC		pDC;													// デバイスコンテキストの受け取り用変数

	hdc = GetDC(m_pMainWnd->m_hWnd);								// デバイスコンテキスト取得

	pDC.Attach(hdc);												// デバイスコンテキストをCDCクラスに手渡す
	Dx.WorkRender();												// DirectXでメインウィンドウに描画する
	CashDialog.memDC.BitBlt(0,0,180,180,&pDC,466,330,SRCCOPY);		// 描画したものをグリッドダイアログの仮想Bitmapに渡す
	CashDialog.DrawExec();											// 仮想Bitmapを実際の領域に貼り付け描画
	DrawExec();														// メインウィンドウがえらいことになってるから正式描画

	hdc = pDC.Detach();												// CDCが受け取ったデバイスコンテキストを返す

	ReleaseDC(m_pMainWnd->m_hWnd,hdc);								// デバイスコンテキスト開放
	
}


void CSpriteToolApp::OnIdSnapOn() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();
	
	menu->CheckMenuItem(AFX_ID_SNAP_OFF , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SNAP_ON , MF_BYCOMMAND | MF_CHECKED);

	SnapFlg = ON;
	draw_flg = 1;
	
}

void CSpriteToolApp::OnIdSnapOff() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_SNAP_ON , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SNAP_OFF , MF_BYCOMMAND | MF_CHECKED);

	SnapFlg = OFF;
	draw_flg = 1;
	
}

void CSpriteToolApp::OnIdGlidOn() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();
	
	menu->CheckMenuItem(AFX_ID_GLID_OFF , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_GLID_ON , MF_BYCOMMAND | MF_CHECKED);

	GlidFlg = ON;
	draw_flg = 1;
	
}

void CSpriteToolApp::OnIdGlidOff() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_GLID_ON , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_GLID_OFF , MF_BYCOMMAND | MF_CHECKED);

	GlidFlg = OFF;
	draw_flg = 1;
	
}

void CSpriteToolApp::OnGlidTypeOpen() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	GlidTypeDialog.DoModal();
	draw_flg = 1;	
}

void CSpriteToolApp::OnIdAlphaOn() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_ALPHA_ON , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_ALPHA_OFF , MF_BYCOMMAND | MF_UNCHECKED);

	AlphaFlg = ON;
	draw_flg = 1;
	
}

void CSpriteToolApp::OnIdAlphaOff() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_ALPHA_ON , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_ALPHA_OFF , MF_BYCOMMAND | MF_CHECKED);

	AlphaFlg = OFF;
	draw_flg = 1;
	
}

void CSpriteToolApp::OnIdModeDivide() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_MODE_SET , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_MODE_DIVIDE , MF_BYCOMMAND | MF_CHECKED);

	mode = MODE_DIVIDE;
	draw_flg = 1;
	
}

void CSpriteToolApp::OnIdModeSet() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_MODE_SET , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_MODE_DIVIDE , MF_BYCOMMAND | MF_UNCHECKED);

	mode = MODE_SET;
	draw_flg = 1;
	
}
