// VectorSetTool.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "VectorSetTool.h"

#include "MainFrm.h"
#include "VectorSetToolDoc.h"
#include "VectorSetToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolApp

BEGIN_MESSAGE_MAP(CVectorSetToolApp, CWinApp)
	//{{AFX_MSG_MAP(CVectorSetToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(AFX_ID_CHANGE_POINT, OnIdChangePoint)
	ON_COMMAND(AFX_ID_EDIT_POINT, OnIdEditPoint)
	ON_COMMAND(AFX_ID_DELETE_POINT, OnIdDeletePoint)
	ON_COMMAND(AFX_ID_SNAP_ON, OnIdSnapOn)
	ON_COMMAND(AFX_ID_SNAP_OFF, OnIdSnapOff)
	ON_COMMAND(AFX_ID_CHANGE_OBJECT_POINT, OnIdChangeObjectPoint)
	ON_COMMAND(AFX_ID_DELETE_OBJECT_POINT, OnIdDeleteObjectPoint)
	ON_COMMAND(AFX_ID_OBJECT_1, OnIdObject1)
	ON_COMMAND(AFX_ID_OBJECT_2, OnIdObject2)
	ON_COMMAND(AFX_ID_SET_OBJECT_POINT, OnIdSetObjectPoint)
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolApp クラスの構築

CVectorSetToolApp::CVectorSetToolApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CVectorSetToolApp オブジェクト

CVectorSetToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolApp クラスの初期化

BOOL CVectorSetToolApp::InitInstance()
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
		RUNTIME_CLASS(CVectorSetToolDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CVectorSetToolView));
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
	work_dir = Dx.camera.Direction;

	GlidPen.CreatePen(PS_SOLID,2,RGB(255,255,0));				// グリッド(大枠)としてのペンを作成(デフォルトで白、色の変更可能)
	CheckPen.CreatePen(PS_SOLID,2,RGB(0,255,0));				// グリッド(大枠)としてのペンを作成(デフォルトで白、色の変更可能)

	PointPen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CursolBrush.CreateStockObject(BLACK_BRUSH);				// グリッド・カーソル用の中抜きブラシ
	SelectPen.CreatePen(PS_SOLID,2,RGB(120,120,120));

	DrumPen.CreatePen(PS_SOLID,2,RGB(0,255,255));
	BallonPen.CreatePen(PS_SOLID,2,RGB(0,0,255));

	// 一発目の描画
	DrawExec();													// 描画

	// アイドル時間に使用するタイマー初期化
	time = bftime = anime_time = frame_count = 0;				// 各時間管理変数初期化

	// フラグ初期化
	animation_flg = draw_flg = OFF;								// 描画系のフラグをOFFで初期化
	lbutton = fileload = OFF;									// システム系のフラグをOFFで初期化

	for(int i = 0;i < MAX_DATA;i++){
		point[i].x = point[i].y = 0;
		ballon_point[i].x = ballon_point[i].y = 0;
		drum_point[i].x = drum_point[i].y = 0;
	}

	point_cnt = 0;
	ballon_point_cnt = 0;
	drum_point_cnt = 0;

	Point_Cheker = 0;
	drum_Point_Cheker = 0;
	ballon_Point_Cheker = 0;

	point_offset_x = point_offset_y = 0;
	camera_offset_x = camera_offset_y = 0;

	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_CHANGE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_EDIT_POINT , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_SET_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_CHANGE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);

	menu->CheckMenuItem(AFX_ID_SNAP_OFF , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_OBJECT_1 , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_OBJECT_2 , MF_BYCOMMAND | MF_UNCHECKED);

	object_flg = 0;
	SnapFlg = OFF;												// ついでにスナップもONで
	NowPoint.x = NowPoint.y = 0;
	Point_flg = 0;
	shift_flg = cnt_flg = 0;
	CameraDialog.Create(IDD_CAMERA_DIALOG, m_pMainWnd);
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
void CVectorSetToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolApp メッセージ ハンドラ

void CVectorSetToolApp::DrawExec()
{
	Dx.Render();													// DirectXの描画を呼び出し
	CRect	clrect;													// クライアント領域のサイズ用変数
	HDC		hdc;													// デバイスコンテキスト変数
	CPoint	work;													// 座標用変数(ワーク)
	int	i;														// カウンタ用変数

	hdc = GetDC(m_pMainWnd->m_hWnd);								// デバイスコンテキスト取得

	Dx.Render();													// DirectXの描画を呼び出し
	SelectObject(hdc,SelectPen);										// グリッド用のペン選択

	MoveToEx(hdc,0,SET_OFFSET,NULL);				// で、引き始めの位置に移動
	LineTo(hdc,SCREEN_WIDTH,SET_OFFSET);
	MoveToEx(hdc,SCREEN_WIDTH/2,0,NULL);				// で、引き始めの位置に移動
	LineTo(hdc,SCREEN_WIDTH/2,SCREEN_HEIGHT);	

	SelectObject(hdc,GlidPen);										// グリッド用のペン選択
/*	
	for(i = 0;i < point_cnt -1;i++){
		MoveToEx(hdc,point[i].x - camera_offset_x,point[i].y - camera_offset_y,NULL);				// で、引き始めの位置に移動
		LineTo(hdc,point[i+1].x - camera_offset_x,point[i+1].y - camera_offset_y);					// 線を引く
	}
*/
	SelectObject(hdc,CursolBrush);									// 中抜きブラシ選択
	SelectObject(hdc,PointPen);										// グリッド用のペン選択
	for(i = 0;i < point_cnt;i++){
		if(!((point[i].x == 0)&&(point[i].y == 0))){
			if(i == Point_Cheker && Point_flg == 1 && Point_flg == 2){
				SelectObject(hdc,CheckPen);										// グリッド用のペン選択
				Rectangle(hdc,point[i].x-2 - camera_offset_x,point[i].y-2 - camera_offset_y,
					point[i].x+2 - camera_offset_x,point[i].y+2 - camera_offset_y);
				SelectObject(hdc,PointPen);		
			}
			else{
				Rectangle(hdc,point[i].x-2 - camera_offset_x,point[i].y-2 - camera_offset_y,
				point[i].x+2 - camera_offset_x,point[i].y+2 - camera_offset_y);
			}
		}
		else{
			i = MAX_DATA;
		}
	}
	SelectObject(hdc,CursolBrush);									// 中抜きブラシ選択
	SelectObject(hdc,DrumPen);										// グリッド用のペン選択
	for(i = 0;i < drum_point_cnt;i++){
		if(!((drum_point[i].x == 0)&&(drum_point[i].y == 0))){
			if(i == drum_Point_Cheker && Point_flg == 4 && Point_flg == 5){
				SelectObject(hdc,CheckPen);										// グリッド用のペン選択
				Rectangle(hdc,drum_point[i].x-2 - camera_offset_x,drum_point[i].y-2 - camera_offset_y,
					drum_point[i].x+2 - camera_offset_x,drum_point[i].y+2 - camera_offset_y);
				SelectObject(hdc,DrumPen);		
			}
			else{
				Rectangle(hdc,drum_point[i].x-2 - camera_offset_x,drum_point[i].y-2 - camera_offset_y,
				drum_point[i].x+2 - camera_offset_x,drum_point[i].y+2 - camera_offset_y);
			}
		}
		else{
			i = MAX_DATA;
		}
	}
	SelectObject(hdc,CursolBrush);									// 中抜きブラシ選択
	SelectObject(hdc,BallonPen);										// グリッド用のペン選択
	for(i = 0;i < ballon_point_cnt;i++){
		if(!((ballon_point[i].x == 0)&&(ballon_point[i].y == 0))){
			if(i == ballon_Point_Cheker && Point_flg == 4 && Point_flg == 5){
				SelectObject(hdc,CheckPen);										// グリッド用のペン選択
				Rectangle(hdc,ballon_point[i].x-2 - camera_offset_x,ballon_point[i].y-2 - camera_offset_y,
					ballon_point[i].x+2 - camera_offset_x,ballon_point[i].y+2 - camera_offset_y);
				SelectObject(hdc,BallonPen);		
			}
			else{
				Rectangle(hdc,ballon_point[i].x-2 - camera_offset_x,ballon_point[i].y-2 - camera_offset_y,
				ballon_point[i].x+2 - camera_offset_x,ballon_point[i].y+2 - camera_offset_y);
			}
		}
		else{
			i = MAX_DATA;
		}
	}

	ReleaseDC(m_pMainWnd->m_hWnd,hdc);								// 用済みなのでデバイスコンテキスト開放

}

BOOL CVectorSetToolApp::OnIdle(LONG lCount) 
{
	// 描画フラグがONであるならば描画(基本的にダイアログを出したときにシステム描画として呼び出される)
	if(draw_flg == 1){												// 再描画要請？
		DrawExec();													// 描画関数呼び出し
		draw_flg = 0;												// 描画フラグをOFF
	}
	
//	return CWinApp::OnIdle(lCount);
	return true;
}

void CVectorSetToolApp::OnIdEditPoint() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_CHANGE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_EDIT_POINT , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_SET_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_CHANGE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);

	Point_flg = 0;

	draw_flg = 1;	
}

void CVectorSetToolApp::OnIdChangePoint() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_CHANGE_POINT , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_EDIT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SET_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_CHANGE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);

	Point_flg = 1;

	draw_flg = 1;
}


void CVectorSetToolApp::OnIdDeletePoint() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_CHANGE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_POINT , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_EDIT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SET_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_CHANGE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);

	Point_flg = 2;

	draw_flg = 1;	
}

void CVectorSetToolApp::OnIdSetObjectPoint() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_CHANGE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_EDIT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SET_OBJECT_POINT , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_CHANGE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);

	Point_flg = 3;

	draw_flg = 1;	
	
}

void CVectorSetToolApp::OnIdChangeObjectPoint() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_CHANGE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_EDIT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SET_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_CHANGE_OBJECT_POINT , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);

	Point_flg = 4;

	draw_flg = 1;	
	
}

void CVectorSetToolApp::OnIdDeleteObjectPoint() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_CHANGE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_EDIT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SET_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_CHANGE_OBJECT_POINT , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_DELETE_OBJECT_POINT , MF_BYCOMMAND | MF_CHECKED);

	Point_flg = 5;

	draw_flg = 1;	
	
}

void CVectorSetToolApp::OnIdSnapOn() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_SNAP_ON , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_SNAP_OFF , MF_BYCOMMAND | MF_UNCHECKED);

	SnapFlg = ON;												// ついでにスナップもONで
	draw_flg = 1;	

}

void CVectorSetToolApp::OnIdSnapOff() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_SNAP_ON , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SNAP_OFF , MF_BYCOMMAND | MF_CHECKED);

	SnapFlg = OFF;												// ついでにスナップもONで
	draw_flg = 1;	

}

void CVectorSetToolApp::OnIdObject1() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_OBJECT_1 , MF_BYCOMMAND | MF_CHECKED);
	menu->CheckMenuItem(AFX_ID_OBJECT_2 , MF_BYCOMMAND | MF_UNCHECKED);
	
	object_flg = 0;
	draw_flg = 1;
}

void CVectorSetToolApp::OnIdObject2() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();						// メニュー領域のポインタ取得
	menu->CheckMenuItem(AFX_ID_OBJECT_1 , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_OBJECT_2 , MF_BYCOMMAND | MF_CHECKED);
	
	object_flg = 1;
	draw_flg = 1;
	
}
