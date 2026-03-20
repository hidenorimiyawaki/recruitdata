// ScripteEditorDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ScripteEditor.h"
#include "ScripteEditorDlg.h"

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
// CScripteEditorDlg ダイアログ

CScripteEditorDlg::CScripteEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScripteEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScripteEditorDlg)
	m_EditBunshou = _T("サンプル");
	m_EditBrank = 0;
	m_EditSpeed = 5;
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScripteEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScripteEditorDlg)
	DDX_Control(pDX, IDC_SLIDER_COLOR_R, m_SliderColorR);
	DDX_Control(pDX, IDC_SLIDER_COLOR_G, m_SliderColorG);
	DDX_Control(pDX, IDC_SLIDER_COLOR_B, m_SliderColorB);
	DDX_Control(pDX, IDC_SAMPLE_COLOR, m_SampleColor);
	DDX_Control(pDX, IDC_COMBOFONTSIZE, m_ComboFontSize);
	DDX_Control(pDX, IDC_COMBO_MOVE_TYPE, m_ComboMoveType);
	DDX_Control(pDX, IDC_COMBO_FONT_TYPE, m_ComboFontType);
	DDX_Control(pDX, IDC_CHECK_UNDERLINE, m_CheckUnderLine);
	DDX_Control(pDX, IDC_CHECK_POWER, m_CheckPower);
	DDX_Control(pDX, IDC_CHECK_NANAME, m_CheckNaname);
	DDX_Text(pDX, IDC_EDIT_BUNSHOU, m_EditBunshou);
	DDX_Text(pDX, IDC_EDIT_BRANK, m_EditBrank);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_EditSpeed);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScripteEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CScripteEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSAVE, OnButtonsave)
	ON_BN_CLICKED(IDC_BUTTONLOAD, OnButtonload)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_EDIT_BRANK, OnKillfocusEditBrank)
	ON_EN_KILLFOCUS(IDC_EDIT_BUNSHOU, OnKillfocusEditBunshou)
	ON_EN_KILLFOCUS(IDC_EDIT_SPEED, OnKillfocusEditSpeed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScripteEditorDlg メッセージ ハンドラ

BOOL CScripteEditorDlg::OnInitDialog()
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
	SampleBrush.CreateSolidBrush(RGB(0,0,0));	// ブラシを黒で初期化
	posB = posR = posG = 0;						// ブラシにあわせてバーの位置初期化

	m_SliderColorR.SetRange(0,255,TRUE);	// カラースライダーRの範囲設定
	m_SliderColorG.SetRange(0,255,TRUE);	// カラースライダーGの範囲設定
	m_SliderColorB.SetRange(0,255,TRUE);	// カラースライダーBの範囲設定

	m_ComboMoveType.InsertString(-1,"上");
	m_ComboMoveType.InsertString(-1,"下");
	m_ComboMoveType.InsertString(-1,"左");
	m_ComboMoveType.InsertString(-1,"右");
	m_ComboMoveType.SetCurSel(2);

	m_ComboFontType.InsertString(-1,"ＭＳ 明朝");
	m_ComboFontType.InsertString(-1,"ＭＳ ゴシック");
	m_ComboFontType.InsertString(-1,"HG行書体");
	m_ComboFontType.InsertString(-1,"fantasy");
	m_ComboFontType.SetCurSel(1);

	m_ComboFontSize.InsertString(-1,"1");
	m_ComboFontSize.InsertString(-1,"2");
	m_ComboFontSize.InsertString(-1,"3");
	m_ComboFontSize.InsertString(-1,"4");
	m_ComboFontSize.InsertString(-1,"5");
	m_ComboFontSize.InsertString(-1,"6");
	m_ComboFontSize.InsertString(-1,"7");
	m_ComboFontSize.SetCurSel(3);
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CScripteEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScripteEditorDlg::OnPaint() 
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
	CDC* pDC = m_SampleColor.GetDC();	// サンプルウィンドウの描画許可取得
	
	pDC->SelectObject(SampleBrush);		// サンプルウィンドウ描画用のブラシ関連付け
	pDC->Rectangle(0,0,60,30);			// サンプルウィンドウ描画
	
	m_SampleColor.ReleaseDC(pDC);		// サンプルウィンドウの描画許可開放

}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CScripteEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScripteEditorDlg::OnOK() 
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
	
		switch(m_ComboMoveType.GetCurSel()){
			case 0:
				workfile.Format("<html><head><title></title></head><body>\n<body LEFTMARGIN=\"%d\" >\n\n",m_EditBrank);
				file.WriteString(workfile);

				workfile.Format("<MARQUEE direction=\"");
				file.WriteString(workfile);

				workfile.Format("up\" scrollamount=\"%d\">\n",m_EditSpeed);
				file.WriteString(workfile);
			break;

			case 1:
				workfile.Format("<html><head><title></title></head><body>\n<body LEFTMARGIN=\"%d\" >\n\n",m_EditBrank);
				file.WriteString(workfile);

				workfile.Format("<MARQUEE direction=\"");
				file.WriteString(workfile);

				workfile.Format("down\" scrollamount=\"%d\">\n",m_EditSpeed);
				file.WriteString(workfile);
			break;

			case 2:
				workfile.Format("<html><head><title></title></head><body>\n<body TOPMARGIN=\"%d\" >\n\n",m_EditBrank);
				file.WriteString(workfile);

				workfile.Format("<MARQUEE direction=\"");
				file.WriteString(workfile);

				workfile.Format("left\" scrollamount=\"%d\">\n",m_EditSpeed);
				file.WriteString(workfile);
			break;

			case 3:
				workfile.Format("<html><head><title></title></head><body>\n<body TOPMARGIN=\"%d\" >\n\n",m_EditBrank);
				file.WriteString(workfile);

				workfile.Format("<MARQUEE direction=\"");
				file.WriteString(workfile);

				workfile.Format("right\" scrollamount=\"%d\">\n",m_EditSpeed);
				file.WriteString(workfile);
			break;

			default:
				break;
		}

		workfile.Format("<font  color=\"#%02x%02x%02x\" size=\"%d\" face=\"",posR,posG,posB,m_ComboFontSize.GetCurSel()+1 );
		file.WriteString(workfile);

		switch(m_ComboFontType.GetCurSel()){
			case 0:
				workfile.Format("ＭＳ 明朝\"\" >\n");
				file.WriteString(workfile);
			break;

			case 1:
				workfile.Format("ＭＳ ゴシック\"\" >\n");
				file.WriteString(workfile);
			break;

			case 2:
				workfile.Format("HG行書体\"\" >\n");
				file.WriteString(workfile);
			break;

			case 3:
				workfile.Format("fantasy\"\" >\n");
				file.WriteString(workfile);
			break;

			default:
				break;
		}
		if(m_CheckPower.GetCheck()) {
				workfile.Format("<STRONG>\n");
				file.WriteString(workfile);
		}
		if(m_CheckNaname.GetCheck()) {
				workfile.Format("<i>\n");
				file.WriteString(workfile);
		}
		if(m_CheckUnderLine.GetCheck()) {
				workfile.Format("<u>\n");
				file.WriteString(workfile);
		}

		file.WriteString(m_EditBunshou);

		if(m_CheckUnderLine.GetCheck()) {
			workfile.Format("</u>\n");
			file.WriteString(workfile);
		}
		if(m_CheckNaname.GetCheck()) {
				workfile.Format("</i>\n");
				file.WriteString(workfile);
		}
		if(m_CheckPower.GetCheck()) {
				workfile.Format("</STRONG>\n");
				file.WriteString(workfile);
		}

		workfile.Format("</font></marquee>\n\n</body></html>");
		file.WriteString(workfile);

		file.Close();
	}}

void CScripteEditorDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CDialog::OnCancel();
}

void CScripteEditorDlg::OnButtonsave() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;

	UpdateData(true);

	CFileDialog filedlg(false,"SEF", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "ScriptEditor専用ファイル(*.SEF)|*.SEF||");
	if(filedlg.DoModal() != IDOK) return; 

	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {

		workfile.Format("%03d\n",posR);
		file.WriteString(workfile);
		workfile.Format("%03d\n",posG);
		file.WriteString(workfile);
		workfile.Format("%03d\n",posB);
		file.WriteString(workfile);

		workfile.Format("%05d\n",m_EditBrank);
		file.WriteString(workfile);
		workfile.Format("%05d\n",m_EditSpeed);
		file.WriteString(workfile);

		workfile.Format("%d\n",m_ComboMoveType.GetCurSel());
		file.WriteString(workfile);
		workfile.Format("%d\n",m_ComboFontType.GetCurSel());
		file.WriteString(workfile);
		workfile.Format("%d\n",m_ComboFontSize.GetCurSel());
		file.WriteString(workfile);

		workfile.Format("%d\n",m_CheckPower.GetCheck());
		file.WriteString(workfile);
		workfile.Format("%d\n",m_CheckNaname.GetCheck());
		file.WriteString(workfile);
		workfile.Format("%d\n",m_CheckUnderLine.GetCheck());
		file.WriteString(workfile);

		file.WriteString(m_EditBunshou);

		file.Close();
	}
	
}

void CScripteEditorDlg::OnButtonload() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;
	char*				a;
	int					work;

	CFileDialog filedlg(true,"SEF", NULL, OFN_HIDEREADONLY | OFN_READONLY, "ScriptEditor専用ファイル(*.SEF)|*.SEF||");
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
		work = (a[0]-48) * 100;
		work += (a[1]-48) * 10;
		work += (a[2]-48) * 1;
		posR = work;

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = (a[0]-48) * 100;
		work += (a[1]-48) * 10;
		work += (a[2]-48) * 1;
		posG = work;

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = (a[0]-48) * 100;
		work += (a[1]-48) * 10;
		work += (a[2]-48) * 1;
		posB = work;

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = (a[0]-48) * 10000;
		work += (a[1]-48) * 1000;
		work += (a[2]-48) * 100;
		work += (a[3]-48) * 10;
		work += (a[4]-48) * 1;
		m_EditBrank = work;

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = (a[0]-48) * 10000;
		work += (a[1]-48) * 1000;
		work += (a[2]-48) * 100;
		work += (a[3]-48) * 10;
		work += (a[4]-48) * 1;
		m_EditSpeed = work;

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = a[0]-48;
		m_ComboMoveType.SetCurSel(work);

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = a[0]-48;
		m_ComboFontType.SetCurSel(work);

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = a[0]-48;
		m_ComboFontSize.SetCurSel(work);

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = a[0]-48;
		m_CheckPower.SetCheck(work);

		file.ReadString(workfile);
		strcpy(a,workfile);
		work = a[0]-48;
		m_CheckNaname.SetCheck(work);


		file.ReadString(workfile);
		strcpy(a,workfile);
		work = a[0]-48;
		m_CheckUnderLine.SetCheck(work);

		file.ReadString(m_EditBunshou);

		file.Close();
	}


	SampleBrush.DeleteObject();

	SampleBrush.CreateSolidBrush(RGB(posR,posG,posB));

	m_SliderColorR.SetPos(posR);
	m_SliderColorG.SetPos(posG);
	m_SliderColorB.SetPos(posB);

	CDC* pDC = m_SampleColor.GetDC();
	
	pDC->SelectObject(SampleBrush);
	pDC->Rectangle(0,0,60,30);
	
	m_SampleColor.ReleaseDC(pDC);
	UpdateData(false);
	
}

void CScripteEditorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	SampleBrush.DeleteObject();			// 前回作成したブラシを削除

	SampleBrush.CreateSolidBrush(RGB(m_SliderColorR.GetPos(),m_SliderColorG.GetPos(),m_SliderColorB.GetPos()));
	//↑サンプルウィンドウ用ブラシを現在のバーの位置、すなわち設定された色で作成

	posR = (int)m_SliderColorR.GetPos();	// 現在のRバーの位置を保存
	posG = (int)m_SliderColorG.GetPos();	// 現在のGバーの位置を保存
	posB = (int)m_SliderColorB.GetPos();	// 現在のBバーの位置を保存

	CDC* pDC = m_SampleColor.GetDC();	// サンプルウィンドウの描画許可取得
	
	pDC->SelectObject(SampleBrush);		// サンプルウィンドウ描画用のブラシ関連付け
	pDC->Rectangle(0,0,60,30);			// サンプルウィンドウ描画
	
	m_SampleColor.ReleaseDC(pDC);		// サンプルウィンドウの描画許可開放

	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CScripteEditorDlg::OnKillfocusEditBrank() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	
}

void CScripteEditorDlg::OnKillfocusEditBunshou() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	
}

void CScripteEditorDlg::OnKillfocusEditSpeed() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	
}
