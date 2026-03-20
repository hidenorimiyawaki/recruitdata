// RenbanEditorDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "RenbanEditor.h"
#include "RenbanEditorDlg.h"

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
// CRenbanEditorDlg ダイアログ

CRenbanEditorDlg::CRenbanEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRenbanEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRenbanEditorDlg)
	m_EditAddles = _T("");
	m_EditNowNo = 0;
	m_EditNowTime = 0;
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenbanEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenbanEditorDlg)
	DDX_Control(pDX, IDC_SLIDEREDIT, m_SliderEdit);
	DDX_Text(pDX, IDC_EDITADDLES, m_EditAddles);
	DDX_Text(pDX, IDC_EDITNOWNO, m_EditNowNo);
	DDX_Text(pDX, IDC_EDITNOWTIME, m_EditNowTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRenbanEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CRenbanEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DATASAVE, OnButtonDatasave)
	ON_BN_CLICKED(IDC_BUTTON_DATALOAD, OnButtonDataload)
	ON_BN_CLICKED(IDC_BUTTON_BROWS, OnButtonBrows)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_EDITNOWNO, OnKillfocusEditnowno)
	ON_EN_KILLFOCUS(IDC_EDITNOWTIME, OnKillfocusEditnowtime)
	ON_EN_KILLFOCUS(IDC_EDITADDLES, OnKillfocusEditaddles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenbanEditorDlg メッセージ ハンドラ

BOOL CRenbanEditorDlg::OnInitDialog()
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
	DefSetDialog.DoModal();
	SetData = new HTMLPAGEDATA[DefSetDialog.m_MaxHtmlNum];
	for(int i = 0;i<=DefSetDialog.m_MaxHtmlNum -1;i++){
		SetData[i].ImageTime = DefSetDialog.m_EditDefTime;
	}
	m_EditNowTime = SetData[0].ImageTime;
	m_SliderEdit.SetRange(0,DefSetDialog.m_MaxHtmlNum-1,true);
	UpdateData(false);

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CRenbanEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRenbanEditorDlg::OnPaint() 
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
HCURSOR CRenbanEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRenbanEditorDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;

	CFileDialog filedlg(false,"html", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "HTMLファイル(*.html)|*.html||");
	if(filedlg.DoModal() != IDOK) return; 

	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	UpdateData(true);
		for(int i = 0;i <= DefSetDialog.m_MaxHtmlNum - 1;i++){
			workfile.Format("%s%d.html",filename,i);

			mainfile = workfile;

			if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
				MessageBox("ファイルがオープンできませんでした", "error", MB_ICONERROR | MB_OK);
			}
			else {
					workfile.Format("<html>\n<head>\n\n<meta http-equiv=\"Refresh\" content=\"%d; URL=%s%d.html\">\n</head>",SetData[i].ImageTime,filename,i+1);
					file.WriteString(workfile);

					workfile.Format("\n<body><img src=\"%s\">\n</body>\n</html>",SetData[i].ImageAddles);
					file.WriteString(workfile);
					file.Close();
			}
		}
		workfile.Format("%s%d.html",filename,DefSetDialog.m_MaxHtmlNum - 1);

		mainfile = workfile;

		if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
			MessageBox("ファイルがオープンできませんでした", "error", MB_ICONERROR | MB_OK);
		}
		else {
				workfile.Format("<html>\n<head>\n\n<meta http-equiv=\"Refresh\" content=\"%d; URL=%s%d.html\">\n</head>",SetData[DefSetDialog.m_MaxHtmlNum -1].ImageTime ,filename,0);
				file.WriteString(workfile);

				workfile.Format("\n<body><img src=\"%s\">\n</body>\n</html>",SetData[DefSetDialog.m_MaxHtmlNum -1].ImageAddles);
				file.WriteString(workfile);
				file.Close();
		}
	
}

void CRenbanEditorDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CDialog::OnCancel();
}

void CRenbanEditorDlg::OnButtonDatasave() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;

	CFileDialog filedlg(false,"ROF", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "RenbanEditor専用ファイル(*.ROF)|*.ROF||");
	if(filedlg.DoModal() != IDOK) return; 

	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {

		workfile.Format("%05d\n",DefSetDialog.m_MaxHtmlNum);
		file.WriteString(workfile);

		for(int i = 0;i <= DefSetDialog.m_MaxHtmlNum -1 ;i++){

			file.WriteString(SetData[i].ImageAddles);
			workfile.Format("\n");
			file.WriteString(workfile);

			workfile.Format("%05d\n",SetData[i].ImageTime);
			file.WriteString(workfile);

		}
		file.Close();
	}
	
}

void CRenbanEditorDlg::OnButtonDataload() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;
	char*				a;
	int					work;

	CFileDialog filedlg(true,"ROF", NULL, OFN_HIDEREADONLY | OFN_READONLY, "RenbanEditor専用ファイル(*.ROF)|*.ROF||");
	if(filedlg.DoModal() != IDOK) return;
	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeRead,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {
		a = new char[5];
		
		file.ReadString(workfile);
		strcpy(a,workfile);
		work = (a[0]-48) * 10000;
		work += (a[1]-48) * 1000;
		work += (a[2]-48) * 100;
		work += (a[3]-48) * 10;
		work += (a[4]-48) * 1;
		DefSetDialog.m_MaxHtmlNum = work;

		SetData = new HTMLPAGEDATA[DefSetDialog.m_MaxHtmlNum];

		for(int i = 0;i <= DefSetDialog.m_MaxHtmlNum -1 ;i++){

			file.ReadString(SetData[i].ImageAddles);

			file.ReadString(workfile);
			strcpy(a,workfile);
			work = (a[0]-48) * 10000;
			work += (a[1]-48) * 1000;
			work += (a[2]-48) * 100;
			work += (a[3]-48) * 10;
			work += (a[4]-48) * 1;
			SetData[i].ImageTime = work;

		}
		m_EditAddles = SetData[m_EditNowNo].ImageAddles;
		m_EditNowTime = SetData[m_EditNowNo].ImageTime;

		m_SliderEdit.SetRange(0,DefSetDialog.m_MaxHtmlNum - 1,true);

		file.Close();
	}

	UpdateData(false);

	
}

void CRenbanEditorDlg::OnButtonBrows() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;

	CFileDialog filedlg(true,"jpg", NULL, OFN_HIDEREADONLY | OFN_READONLY, "画像ファイル(*.jpg *.gif *.png)|*.jpg; *.gif; *.png||");
	if(filedlg.DoModal() != IDOK) return;
	
	mainfile = filedlg.GetFileName();
	m_EditAddles = filedlg.GetPathName();

	SetData[m_EditNowNo].ImageAddles = m_EditAddles;

	if(!file.Open(mainfile,CFile::modeRead,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}

	UpdateData(false);
}



void CRenbanEditorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	UpdateData(true);

	if( m_EditNowNo != m_SliderEdit.GetPos()){
		SetData[m_EditNowNo].ImageAddles = m_EditAddles;
		SetData[m_EditNowNo].ImageTime = m_EditNowTime;
		m_EditNowNo = m_SliderEdit.GetPos();
		m_EditAddles = SetData[m_EditNowNo].ImageAddles;
		m_EditNowTime = SetData[m_EditNowNo].ImageTime;
	}
	UpdateData(false);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CRenbanEditorDlg::OnKillfocusEditnowno() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	SetData[m_EditNowNo].ImageAddles = m_EditAddles;
	SetData[m_EditNowNo].ImageTime = m_EditNowTime;
	m_EditNowNo = m_SliderEdit.GetPos();

}

void CRenbanEditorDlg::OnKillfocusEditnowtime() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	SetData[m_EditNowNo].ImageAddles = m_EditAddles;
	SetData[m_EditNowNo].ImageTime = m_EditNowTime;
	m_EditNowNo = m_SliderEdit.GetPos();
	
}

void CRenbanEditorDlg::OnKillfocusEditaddles() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	SetData[m_EditNowNo].ImageAddles = m_EditAddles;
	SetData[m_EditNowNo].ImageTime = m_EditNowTime;
	m_EditNowNo = m_SliderEdit.GetPos();
	
}
