// AnimationTool.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "AnimationTool.h"

#include "MainFrm.h"
#include "AnimationToolDoc.h"
#include "AnimationToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimationToolApp

BEGIN_MESSAGE_MAP(CAnimationToolApp, CWinApp)
	//{{AFX_MSG_MAP(CAnimationToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(AFX_ID_GLID_ON, OnIdGlidOn)
	ON_COMMAND(AFX_ID_GLID_OFF, OnIdGlidOff)
	ON_COMMAND(AFX_ID_SNAP_ON, OnIdSnapOn)
	ON_COMMAND(AFX_ID_SNAP_OFF, OnIdSnapOff)
	ON_COMMAND(ID_ANIME_TEST, OnAnimeTest)
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimationToolApp クラスの構築

CAnimationToolApp::CAnimationToolApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
	fileload = 0;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CAnimationToolApp オブジェクト

CAnimationToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAnimationToolApp クラスの初期化

BOOL CAnimationToolApp::InitInstance()
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

	LoadStdProfileSettings(5);  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAnimationToolDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CAnimationToolView));
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
	DataDialog.Create(IDD_DATADIALOG, m_pMainWnd);				// データ設定(時間、参照対象)ダイアログ作成
	GlidDialog.Create(IDD_GLID_DIALOG, m_pMainWnd);				// グリッドキャッシュ設定ダイアログ作成

	// グリッドキャッシュの初期化設定
	CString		work;											// グリッドキャッシュの初期データ設定用ワーク変数
	work.Format("Blank(left,top,right,bottom）// コメント");	// 初期データの文字列設定
	GlidDialog.m_List_Cash.InitStorage(50,32767);				// グリッドとして設定できるデータの最大数設定
	GlidDialog.m_List_Cash.InsertString(0,work);				// そして初期文字列配置
	GlidDialog.m_List_Cash.SetCurSel(0);						// ついでにカーソルを初期位置にあわせる

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
void CAnimationToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAnimationToolApp メッセージ ハンドラ

BOOL CAnimationToolApp::OnIdle(LONG lCount) 
{
	// 描画フラグがONであるならば描画(基本的にダイアログを出したときにシステム描画として呼び出される)
	int work;

	if(draw_flg == 1){												// 再描画要請？
		DrawExec();													// 描画関数呼び出し
		draw_flg = 0;												// 描画フラグをOFF
	}
	time = timeGetTime();											// 時間取得
	if(time - bftime > FRAME_RATE) {								// 今の時間から、さっきの時間引いたらフレームレート以下？
		bftime = time;												// 今の時間を保存
		if(AnimeDialog.playflg == 1){								// アニメーション確認ダイアログがアニメ中？
			work = AnimeDialog.m_Flame_Slider.GetPos();
			anime_time++;											// じゃ、カウンタ＋＋ね。
			Dx.exbord.texRect.top = (long)data[AnimeDialog.anime_frame][TOP];		// とりあえず、4すみのデータ設定
			Dx.exbord.texRect.left = (long)data[AnimeDialog.anime_frame][LEFT];	// で、絵の参照位置更新しましょう
			Dx.exbord.texRect.bottom = (long)data[AnimeDialog.anime_frame][DOWN];	
			Dx.exbord.texRect.right = (long)data[AnimeDialog.anime_frame][RIGHT]; 

			if(frame_data[AnimeDialog.anime_frame] <= anime_time){	// で、カウンタって今の設定上限と一緒？
				AnimeDialog.anime_frame = next_frame[AnimeDialog.anime_frame];	// じゃ、それにあわせましょう
													
				if(work >= 0) anime_time = work;				// それからカウンタの初期化を忘れずに
				else {
					anime_time = 0;
				}
			}

			DrawAnimeTest();										// プレイ中ならば常に
			AnimeDialog.DrawExec();									// 描画しましょうけ
		}
		else {
			anime_time = 0;											// アニメーションカウンタは初期化されててね
		}
	}	
	if(AnimeDialog.end == 1){										// ダイアログの終了要請はでてる？
		AnimeDialog.DestroyWindow();								// なら専用関数で終了
		AnimeDialog.end = 0;										// で、終了要請開放ね
	}
	return true;
}

void CAnimationToolApp::DrawExec()
{
	// メインウィンドウに最終目的としての画面を描画

	CRect	clrect;													// クライアント領域のサイズ用変数
	HDC		hdc;													// デバイスコンテキスト変数
	CPoint	work;													// 座標用変数(ワーク)
	UINT	i;														// カウンタ用変数

	hdc = GetDC(m_pMainWnd->m_hWnd);								// デバイスコンテキスト取得
	SelectObject(hdc,GlidPen);										// グリッド用のペン選択
	SelectObject(hdc,CursolBrush);									// 中抜きブラシ選択

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

	// カーソル描画
	SelectObject(hdc,CursolPen);									// グリッドが引き終わったら、カーソル枠用ペン設定
	Rectangle(hdc,start.x,start.y,end.x,end.y);						// 今の分のカーソルを引く
	if(end.x < start.x){
		MoveToEx(hdc,(end.x - start.x) / 2+ start.x,start.y,NULL);	// で、引き始めの位置に移動
		LineTo(hdc,(end.x - start.x) / 2+ start.x,end.y);			// 線を引く
	}else{
		MoveToEx(hdc,(start.x - end.x) / 2+ end.x,start.y,NULL);	// で、引き始めの位置に移動
		LineTo(hdc,(start.x - end.x) / 2+ end.x,end.y);			// 線を引く
	}
	
	ReleaseDC(m_pMainWnd->m_hWnd,hdc);								// 用済みなのでデバイスコンテキスト開放

}
void CAnimationToolApp::DrawExecEx()
{
	// メインウィンドウにワークとしての画面(グリッドキャッシュ用)を描画してからグリッドキャッシュに渡す

	HDC		hdc;													// デバイスコンテキスト変数
	CDC		pDC;													// デバイスコンテキストの受け取り用変数

	hdc = GetDC(m_pMainWnd->m_hWnd);								// デバイスコンテキスト取得

	pDC.Attach(hdc);												// デバイスコンテキストをCDCクラスに手渡す
	Dx.WorkRender();												// DirectXでメインウィンドウに描画する
	GlidDialog.memDC.BitBlt(0,0,180,180,&pDC,466,330,SRCCOPY);		// 描画したものをグリッドダイアログの仮想Bitmapに渡す
	GlidDialog.DrawExec();											// 仮想Bitmapを実際の領域に貼り付け描画
	DrawExec();														// メインウィンドウがえらいことになってるから正式描画

	hdc = pDC.Detach();												// CDCが受け取ったデバイスコンテキストを返す

	ReleaseDC(m_pMainWnd->m_hWnd,hdc);								// デバイスコンテキスト開放
	
}

void CAnimationToolApp::OnIdGlidOn() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();
	
	menu->CheckMenuItem(AFX_ID_GLID_OFF , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_GLID_ON , MF_BYCOMMAND | MF_CHECKED);

	GlidFlg = ON;
	draw_flg = 1;
}

void CAnimationToolApp::OnIdGlidOff() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_GLID_ON , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_GLID_OFF , MF_BYCOMMAND | MF_CHECKED);

	GlidFlg = OFF;
	draw_flg = 1;
}

void CAnimationToolApp::OnIdSnapOn() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();
	
	menu->CheckMenuItem(AFX_ID_SNAP_OFF , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SNAP_ON , MF_BYCOMMAND | MF_CHECKED);

	SnapFlg = ON;
	draw_flg = 1;

}

void CAnimationToolApp::OnIdSnapOff() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CMenu* menu = m_pMainWnd->GetMenu();

	menu->CheckMenuItem(AFX_ID_SNAP_ON , MF_BYCOMMAND | MF_UNCHECKED);
	menu->CheckMenuItem(AFX_ID_SNAP_OFF , MF_BYCOMMAND | MF_CHECKED);

	SnapFlg = OFF;
	draw_flg = 1;
}

void CAnimationToolApp::DrawAnimeTest()
{
	HDC		hdc;													// デバイスコンテキスト変数
	CDC		pDC;													// デバイスコンテキストの受け取り用変数

	hdc = GetDC(m_pMainWnd->m_hWnd);								// デバイスコンテキスト取得

	pDC.Attach(hdc);												// デバイスコンテキストをCDCクラスに手渡す
	Dx.WorkRenderEx();												// DirectXでメインウィンドウに描画する
	AnimeDialog.memDC.BitBlt(0,0,256,256,&pDC,391,257,SRCCOPY);		// 描画したものをグリッドダイアログの仮想Bitmapに渡す
	AnimeDialog.DrawExec();											// 仮想Bitmapを実際の領域に貼り付け描画
	DrawExec();														// メインウィンドウがえらいことになってるから正式描画

	hdc = pDC.Detach();												// CDCが受け取ったデバイスコンテキストを返す

	ReleaseDC(m_pMainWnd->m_hWnd,hdc);								// デバイスコンテキスト開放

}



void CAnimationToolApp::OnAnimeTest() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	AnimeDialog.Create(IDD_ANIME_DIALOG, m_pMainWnd);
	
	draw_flg = 1;

}
