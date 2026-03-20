// DougaEditorDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DougaEditor.h"
#include "DougaEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
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
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDougaEditorDlg ダイアログ

CDougaEditorDlg::CDougaEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDougaEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDougaEditorDlg)
	m_EditAddles = _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDougaEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDougaEditorDlg)
	DDX_Control(pDX, IDC_CHECK_AUTO, m_CheckAuto);
	DDX_Control(pDX, IDC_CHECK_HIDDEN, m_CheckHidden);
	DDX_Control(pDX, IDC_CHECK_ROOP, m_CheckRoop);
	DDX_Control(pDX, IDC_COMBO_POS, m_ComboPos);
	DDX_Text(pDX, IDC_EDIT_ADDLES, m_EditAddles);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDougaEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CDougaEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWS, OnButtonBrows)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDougaEditorDlg メッセージ ハンドラ

BOOL CDougaEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	m_ComboPos.InsertString(-1,"左");
	m_ComboPos.InsertString(-1,"中央");
	m_ComboPos.InsertString(-1,"右");
	m_ComboPos.SetCurSel(0);
	m_CheckAuto.SetCheck(1);
	m_CheckRoop.SetCheck(1);

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CDougaEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CDougaEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CDougaEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDougaEditorDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;

	UpdateData(true);

	CFileDialog filedlg(false,"html", NULL, OFN_OVERWRITEPROMPT  , "HTMLファイル(*.html)|*.html||");
	if(filedlg.DoModal() != IDOK) return; 

	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {
	
				workfile.Format("<HTML><TOP></TOP>\n<BODY>\n");
				file.WriteString(workfile);

				if(m_ComboPos.GetCurSel() == 1){
					workfile.Format("<DIV align=\"center\">\n");
					file.WriteString(workfile);
				}
				else {
				}

				workfile.Format("<embed src=\"");
				file.WriteString(workfile);

				file.WriteString(m_EditAddles);

				workfile.Format("\" loop=\"");
				file.WriteString(workfile);

				if(m_CheckRoop.GetCheck() != 0){
					workfile.Format("true\" autostart=\"");
					file.WriteString(workfile);
				}
				else {
					workfile.Format("false\" autostart=\"");
					file.WriteString(workfile);
				}

				if(m_CheckAuto.GetCheck() != 0){
					workfile.Format("true\" hidden=\"");
					file.WriteString(workfile);
				}
				else {
					workfile.Format("false\" hidden=\"");
					file.WriteString(workfile);
				}

				if(m_CheckHidden.GetCheck() != 0){
					workfile.Format("true\" align=\"");
					file.WriteString(workfile);
				}
				else {
					workfile.Format("false\" align=\"");
					file.WriteString(workfile);
				}

				switch(m_ComboPos.GetCurSel()){
					case 0:
						workfile.Format("left\" >\n");
						file.WriteString(workfile);
					break;

					case 1:
						workfile.Format("center\" >\n");
						file.WriteString(workfile);
					break;

					case 2:
						workfile.Format("right\" >\n");
						file.WriteString(workfile);
					break;
				}
				if(m_ComboPos.GetCurSel() == 1){
					workfile.Format("</DIV>\n");
					file.WriteString(workfile);
				}
				else {
				}


				workfile.Format("\n</BODY>\n</HTMl>");
				file.WriteString(workfile);



		file.Close();
	}

}

void CDougaEditorDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CDialog::OnCancel();
}

void CDougaEditorDlg::OnButtonBrows() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;

	CFileDialog filedlg(true,"avi", NULL, OFN_HIDEREADONLY | OFN_READONLY, "動画ファイル(*.avi *.mpg *.mpeg)|*.avi; *.mpg; *.mpeg|サウンドファイル(*.wav *.mp3 *.mid)|*.wav; *.mp3; *.mid||");
	if(filedlg.DoModal() != IDOK) return;
	
	m_EditAddles = filedlg.GetPathName();

	UpdateData(false);
	
}
