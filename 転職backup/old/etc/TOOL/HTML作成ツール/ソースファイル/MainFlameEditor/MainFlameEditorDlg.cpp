// MainFlameEditorDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MainFlameEditor.h"
#include "MainFlameEditorDlg.h"

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
// CMainFlameEditorDlg ダイアログ

CMainFlameEditorDlg::CMainFlameEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainFlameEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainFlameEditorDlg)
	m_EditFileName1 = _T("");
	m_EditFileName2 = _T("");
	m_EditFileName3 = _T("");
	m_EditFileName4 = _T("");
	m_EditFileName5 = _T("");
	m_EditV1 = 0;
	m_EditV2 = 0;
	m_EditV3 = 0;
	m_EditX1 = 0;
	m_EditX2 = 0;
	m_EditX3 = 0;
	m_EditX4 = 0;
	m_EditX5 = 0;
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainFlameEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainFlameEditorDlg)
	DDX_Control(pDX, IDC_SLIDERV3, m_SliderV3);
	DDX_Control(pDX, IDC_SLIDERV2, m_SliderV2);
	DDX_Control(pDX, IDC_SLIDERV1, m_SliderV1);
	DDX_Control(pDX, IDC_SLIDERH5, m_SliderH5);
	DDX_Control(pDX, IDC_SLIDERH4, m_SliderH4);
	DDX_Control(pDX, IDC_SLIDERH3, m_SliderH3);
	DDX_Control(pDX, IDC_SLIDERH2, m_SliderH2);
	DDX_Control(pDX, IDC_SLIDERH1, m_SliderH1);
	DDX_Control(pDX, IDC_COMBO_VNO, m_ComboVNo);
	DDX_Text(pDX, IDC_EDIT_FILENAME1, m_EditFileName1);
	DDX_Text(pDX, IDC_EDIT_FILENAME2, m_EditFileName2);
	DDX_Text(pDX, IDC_EDIT_FILENAME3, m_EditFileName3);
	DDX_Text(pDX, IDC_EDIT_FILENAME4, m_EditFileName4);
	DDX_Text(pDX, IDC_EDIT_FILENAME5, m_EditFileName5);
	DDX_Text(pDX, IDC_EDITV1, m_EditV1);
	DDV_MinMaxInt(pDX, m_EditV1, 1, 100);
	DDX_Text(pDX, IDC_EDITV2, m_EditV2);
	DDV_MinMaxInt(pDX, m_EditV2, 0, 99);
	DDX_Text(pDX, IDC_EDITV3, m_EditV3);
	DDV_MinMaxInt(pDX, m_EditV3, 0, 98);
	DDX_Text(pDX, IDC_EDITX1, m_EditX1);
	DDV_MinMaxInt(pDX, m_EditX1, 1, 100);
	DDX_Text(pDX, IDC_EDITX2, m_EditX2);
	DDV_MinMaxInt(pDX, m_EditX2, 0, 99);
	DDX_Text(pDX, IDC_EDITX3, m_EditX3);
	DDV_MinMaxInt(pDX, m_EditX3, 0, 98);
	DDX_Text(pDX, IDC_EDITX4, m_EditX4);
	DDV_MinMaxInt(pDX, m_EditX4, 0, 97);
	DDX_Text(pDX, IDC_EDITX5, m_EditX5);
	DDV_MinMaxInt(pDX, m_EditX5, 0, 96);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainFlameEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CMainFlameEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSAVE, OnButtonsave)
	ON_BN_CLICKED(IDC_BUTTONLOAD, OnButtonload)
	ON_BN_CLICKED(IDC_BUTTONBROWS1, OnButtonbrows1)
	ON_BN_CLICKED(IDC_BUTTONBROWS2, OnButtonbrows2)
	ON_BN_CLICKED(IDC_BUTTONBROWS3, OnButtonbrows3)
	ON_BN_CLICKED(IDC_BUTTONBROWS4, OnButtonbrows4)
	ON_BN_CLICKED(IDC_BUTTONBROWS5, OnButtonbrows5)
	ON_CBN_SELCHANGE(IDC_COMBO_VNO, OnSelchangeComboVno)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERV1, OnReleasedcaptureSliderv1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERV2, OnReleasedcaptureSliderv2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERV3, OnReleasedcaptureSliderv3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERH1, OnReleasedcaptureSliderh1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERH2, OnReleasedcaptureSliderh2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERH3, OnReleasedcaptureSliderh3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERH4, OnReleasedcaptureSliderh4)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERH5, OnReleasedcaptureSliderh5)
	ON_EN_KILLFOCUS(IDC_EDIT_FILENAME1, OnKillfocusEditFilename1)
	ON_EN_KILLFOCUS(IDC_EDIT_FILENAME2, OnKillfocusEditFilename2)
	ON_EN_KILLFOCUS(IDC_EDIT_FILENAME3, OnKillfocusEditFilename3)
	ON_EN_KILLFOCUS(IDC_EDIT_FILENAME4, OnKillfocusEditFilename4)
	ON_EN_KILLFOCUS(IDC_EDIT_FILENAME5, OnKillfocusEditFilename5)
	ON_EN_KILLFOCUS(IDC_EDITV1, OnKillfocusEditv1)
	ON_EN_KILLFOCUS(IDC_EDITV2, OnKillfocusEditv2)
	ON_EN_KILLFOCUS(IDC_EDITV3, OnKillfocusEditv3)
	ON_EN_KILLFOCUS(IDC_EDITX1, OnKillfocusEditx1)
	ON_EN_KILLFOCUS(IDC_EDITX2, OnKillfocusEditx2)
	ON_EN_KILLFOCUS(IDC_EDITX3, OnKillfocusEditx3)
	ON_EN_KILLFOCUS(IDC_EDITX4, OnKillfocusEditx4)
	ON_EN_KILLFOCUS(IDC_EDITX5, OnKillfocusEditx5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFlameEditorDlg メッセージ ハンドラ

BOOL CMainFlameEditorDlg::OnInitDialog()
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
	m_SliderV1.SetRange(1,100,true);
	m_SliderV2.SetRange(0,99,true);
	m_SliderV3.SetRange(0,98,true);

	m_SliderV1.SetPos(100);
	m_SliderV2.SetPos(0);
	m_SliderV3.SetPos(0);

	m_SliderH1.SetRange(1,100,true);
	m_SliderH2.SetRange(0,99,true);
	m_SliderH3.SetRange(0,98,true);
	m_SliderH4.SetRange(0,97,true);
	m_SliderH5.SetRange(0,96,true);

	m_SliderH1.SetPos(100);
	m_SliderH2.SetPos(0);
	m_SliderH3.SetPos(0);
	m_SliderH4.SetPos(0);
	m_SliderH5.SetPos(0);

	m_ComboVNo.InsertString(-1,"1");
	m_ComboVNo.InsertString(-1,"2");
	m_ComboVNo.InsertString(-1,"3");
	m_ComboVNo.SetCurSel(0);

	for(int i = 0;i <= 2 ;i++){
		for(int j = 0;j <= 4 ;j++){
			HomePageData[i][j].ImageName.Format("");
			HomePageData[i][j].ImageHabaV = 0;
			HomePageData[i][j].ImageHabaH = 0;
		}
	}
	HomePageData[0][0].ImageHabaV = 100;
	HomePageData[0][0].ImageHabaH = 100;
	HomePageData[1][0].ImageHabaH = 100;
	HomePageData[2][0].ImageHabaH = 100;
	m_EditV1 = 100;
	m_EditX1 = 100;

	UpdateData(false);
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CMainFlameEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMainFlameEditorDlg::OnPaint() 
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
HCURSOR CMainFlameEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMainFlameEditorDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	CStdioFile			file;
	CString				mainfile;
	CString				workfile;
	CFileException		openfile;

	UpdateData(true);

	CFileDialog filedlg(false,"html", NULL, OFN_OVERWRITEPROMPT  , "HTMLファイル(*.html)|*.html||");
	if(filedlg.DoModal() != IDOK) return; 

	
	mainfile = filedlg.GetFileName();

	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {

		workfile.Format("<Html>\n<Head>\n<Title></Title>\n</Head>\n<Frameset Frameborder=\"no\" rows=\"");
		file.WriteString(workfile);
	
		workfile.Format("%d%%",HomePageData[0][0].ImageHabaV);
		file.WriteString(workfile);

		for(int i = 1;i <= 2 ;i++){
			if(HomePageData[0][i].ImageHabaV > 0){ 
				workfile.Format(",%d%%",HomePageData[0][i].ImageHabaV);
				file.WriteString(workfile);
			}
		}
		workfile.Format("\">");
		file.WriteString(workfile);
	
		for(i = 0;i <= 2 ;i++){
			if(HomePageData[0][i].ImageHabaV > 0){
				workfile.Format("\n<Frameset cols=\"%d%%",HomePageData[i][0].ImageHabaH);
				file.WriteString(workfile);
				for(int j = 1;j <= 4 ;j++){
					if(HomePageData[i][j].ImageHabaH > 0){
						workfile.Format(",%d%%",HomePageData[i][j].ImageHabaH);
						file.WriteString(workfile);
					}
				}
				workfile.Format("\">");
				file.WriteString(workfile);

				for(j = 0;j <= 4 ;j++){
					if(HomePageData[i][j].ImageHabaH > 0){
						workfile.Format("<Frame src=\"%s\">\n",HomePageData[i][j].ImageName);
						file.WriteString(workfile);
					}
				}

				workfile.Format("</Frameset>\n");
				file.WriteString(workfile);
			}
		}
		workfile.Format("</Frameset>\n</Html>");
		file.WriteString(workfile);

		file.Close();
	}
}

void CMainFlameEditorDlg::OnCancel() 
{
	// TODO: この位置に特別な後処理を追加してください。
	
	CDialog::OnCancel();
}

void CMainFlameEditorDlg::OnButtonsave() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;

	CFileDialog filedlg(false,"MFE", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "MainFlameEditor専用ファイル(*.MFE)|*.MFE||");
	if(filedlg.DoModal() != IDOK) return; 

	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {

		for(int i = 0;i <= 2 ;i++){
			workfile.Format("%03d\n",HomePageData[0][i].ImageHabaV);
			file.WriteString(workfile);
		}

		for(i = 0;i <= 2 ;i++){
			for(int j = 0;j <= 4 ;j++){
				workfile.Format("%03d\n",HomePageData[i][j].ImageHabaH);
				file.WriteString(workfile);
			}
		}
		for(i = 0;i <= 2 ;i++){
			for(int j = 0;j <= 4 ;j++){
				workfile.Format("%s\n",HomePageData[i][j].ImageName);
				file.WriteString(workfile);
			}
		}

		file.Close();
	}
		
}

void CMainFlameEditorDlg::OnButtonload() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;
	char*				a;
	int					work;

	CFileDialog filedlg(true,"MFE", NULL, OFN_HIDEREADONLY | OFN_READONLY, "MainFlameEditor専用ファイル(*.MFE)|*.MFE||");
	if(filedlg.DoModal() != IDOK) return;
	
	mainfile = filedlg.GetFileName();
	filename = filedlg.GetFileTitle();

	if(!file.Open(mainfile,CFile::modeRead,&openfile)){
		MessageBox("ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {
		a = new char[4];
		
		for(int i = 0;i <= 2 ;i++){
			file.ReadString(workfile);
			strcpy(a,workfile);
			work = (a[0]-48) * 100;
			work += (a[1]-48) * 10;
			work += (a[2]-48) * 1;
			HomePageData[0][i].ImageHabaV = work;
		}

		for(i = 0;i <= 2 ;i++){
			for(int j = 0;j <= 4 ;j++){
				file.ReadString(workfile);
				strcpy(a,workfile);
				work = (a[0]-48) * 100;
				work += (a[1]-48) * 10;
				work += (a[2]-48) * 1;
				HomePageData[i][j].ImageHabaH = work;
			}
		}

		for(i = 0;i <= 2 ;i++){
			for(int j = 0;j <= 4 ;j++){
				file.ReadString(workfile);
				HomePageData[i][j].ImageName = workfile;
			}
		}

		file.Close();
	}
	m_EditFileName1 = HomePageData[m_ComboVNo.GetCurSel()][0].ImageName;
	m_EditFileName2 = HomePageData[m_ComboVNo.GetCurSel()][1].ImageName;
	m_EditFileName3 = HomePageData[m_ComboVNo.GetCurSel()][2].ImageName;
	m_EditFileName4 = HomePageData[m_ComboVNo.GetCurSel()][3].ImageName;
	m_EditFileName5 = HomePageData[m_ComboVNo.GetCurSel()][4].ImageName;

	m_SliderH1.SetPos(HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH);
	m_SliderH2.SetPos(HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH);
	m_SliderH3.SetPos(HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH);
	m_SliderH4.SetPos(HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH);
	m_SliderH5.SetPos(HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH);

	m_EditX1 = HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH;
	m_EditX2 = HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH;
	m_EditX3 = HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH;
	m_EditX4 = HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH;
	m_EditX5 = HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH;

	m_EditV1 = HomePageData[0][0].ImageHabaV;
	m_EditV2 = HomePageData[0][1].ImageHabaV;
	m_EditV3 = HomePageData[0][2].ImageHabaV;

	m_SliderV1.SetPos(m_EditV1);
	m_SliderV2.SetPos(m_EditV2);
	m_SliderV3.SetPos(m_EditV3);

	UpdateData(false);
	
}

void CMainFlameEditorDlg::OnButtonbrows1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	CFileDialog filedlg(TRUE,"html", NULL, OFN_HIDEREADONLY  , "HTMLファイル(*.html)|*.html|画像ファイル(*.jpg *.gif *.png *.bmp)|*.jpg;*.gif;*.png;*.bmp||");
	if(filedlg.DoModal() != IDOK) return; 

	
	HomePageData[m_ComboVNo.GetCurSel()][0].ImageName = filedlg.GetPathName();
	m_EditFileName1 = HomePageData[m_ComboVNo.GetCurSel()][0].ImageName;
	UpdateData(false);
	
}

void CMainFlameEditorDlg::OnButtonbrows2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	CFileDialog filedlg(TRUE,"html", NULL, OFN_HIDEREADONLY  , "HTMLファイル(*.html)|*.html|画像ファイル(*.jpg *.gif *.png *.bmp)|*.jpg;*.gif;*.png;*.bmp||");
	if(filedlg.DoModal() != IDOK) return; 

	
	HomePageData[m_ComboVNo.GetCurSel()][1].ImageName = filedlg.GetPathName();
	m_EditFileName2 = HomePageData[m_ComboVNo.GetCurSel()][1].ImageName;
	UpdateData(false);
	
}

void CMainFlameEditorDlg::OnButtonbrows3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	CFileDialog filedlg(TRUE,"html", NULL, OFN_HIDEREADONLY  , "HTMLファイル(*.html)|*.html|画像ファイル(*.jpg *.gif *.png *.bmp)|*.jpg;*.gif;*.png;*.bmp||");
	if(filedlg.DoModal() != IDOK) return; 

	
	HomePageData[m_ComboVNo.GetCurSel()][2].ImageName = filedlg.GetPathName();
	m_EditFileName3 = HomePageData[m_ComboVNo.GetCurSel()][2].ImageName;
	UpdateData(false);
	
}

void CMainFlameEditorDlg::OnButtonbrows4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	CFileDialog filedlg(TRUE,"html", NULL, OFN_HIDEREADONLY  , "HTMLファイル(*.html)|*.html|画像ファイル(*.jpg *.gif *.png *.bmp)|*.jpg;*.gif;*.png;*.bmp||");
	if(filedlg.DoModal() != IDOK) return; 

	
	HomePageData[m_ComboVNo.GetCurSel()][3].ImageName = filedlg.GetPathName();
	m_EditFileName4 = HomePageData[m_ComboVNo.GetCurSel()][3].ImageName;
	UpdateData(false);
	
}

void CMainFlameEditorDlg::OnButtonbrows5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	CFileDialog filedlg(TRUE,"html", NULL, OFN_HIDEREADONLY  , "HTMLファイル(*.html)|*.html|画像ファイル(*.jpg *.gif *.png *.bmp)|*.jpg;*.gif;*.png;*.bmp||");
	if(filedlg.DoModal() != IDOK) return; 

	
	HomePageData[m_ComboVNo.GetCurSel()][4].ImageName = filedlg.GetPathName();
	m_EditFileName5 = HomePageData[m_ComboVNo.GetCurSel()][4].ImageName;
	UpdateData(false);
	
}

void CMainFlameEditorDlg::OnSelchangeComboVno() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_EditFileName1 = HomePageData[m_ComboVNo.GetCurSel()][0].ImageName;
	m_EditFileName2 = HomePageData[m_ComboVNo.GetCurSel()][1].ImageName;
	m_EditFileName3 = HomePageData[m_ComboVNo.GetCurSel()][2].ImageName;
	m_EditFileName4 = HomePageData[m_ComboVNo.GetCurSel()][3].ImageName;
	m_EditFileName5 = HomePageData[m_ComboVNo.GetCurSel()][4].ImageName;

	m_SliderH1.SetPos(HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH);
	m_SliderH2.SetPos(HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH);
	m_SliderH3.SetPos(HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH);
	m_SliderH4.SetPos(HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH);
	m_SliderH5.SetPos(HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH);

	m_EditX1 = HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH;
	m_EditX2 = HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH;
	m_EditX3 = HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH;
	m_EditX4 = HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH;
	m_EditX5 = HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH;
	
	UpdateData(false);

}

void CMainFlameEditorDlg::OnReleasedcaptureSliderv1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
		UpdateData(true);

	*pResult = 0;
	int	work;

	m_EditV1 = m_SliderV1.GetPos();
	m_EditV2 = m_SliderV2.GetPos();
	m_EditV3 = m_SliderV3.GetPos();

	work = 100 - m_EditV1 - m_EditV2 - m_EditV3;

	m_EditV2 += work;
	if(m_EditV2 < 1){
		m_EditV3 -= 100 - m_EditV2 - m_EditV1;
		if(m_EditV3 <= 0) m_EditV3 = 0;
	}

	m_SliderV1.SetPos(m_EditV1);
	m_SliderV2.SetPos(m_EditV2);
	m_SliderV3.SetPos(m_EditV3);

	HomePageData[0][0].ImageHabaV = m_EditV1;
	HomePageData[0][1].ImageHabaV = m_EditV2;
	HomePageData[0][2].ImageHabaV = m_EditV3;

	UpdateData(false);
}

void CMainFlameEditorDlg::OnReleasedcaptureSliderv2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	*pResult = 0;
	int	work;

	m_EditV1 = m_SliderV1.GetPos();
	m_EditV2 = m_SliderV2.GetPos();
	m_EditV3 = m_SliderV3.GetPos();

	work = 100 - m_EditV1 - m_EditV2 - m_EditV3;

	if(m_EditV3 != 0){
		m_EditV3 += work;
		if(m_EditV3 <= 0){
			work = m_EditV3;
			m_EditV3 = 0;
			m_EditV1 += work - 1;
		}
	}
	else {
		m_EditV1 += work;
	}
	if(m_EditV1 <= 1){
		m_EditV1 = 1;
		m_EditV2 = 99;
	}

	m_SliderV1.SetPos(m_EditV1);
	m_SliderV2.SetPos(m_EditV2);
	m_SliderV3.SetPos(m_EditV3);

	HomePageData[0][0].ImageHabaV = m_EditV1;
	HomePageData[0][1].ImageHabaV = m_EditV2;
	HomePageData[0][2].ImageHabaV = m_EditV3;

	UpdateData(false);
}

void CMainFlameEditorDlg::OnReleasedcaptureSliderv3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	*pResult = 0;
	int	work;

	m_EditV1 = m_SliderV1.GetPos();
	m_EditV2 = m_SliderV2.GetPos();
	m_EditV3 = m_SliderV3.GetPos();

	work = 100 - m_EditV1 - m_EditV2 - m_EditV3;

	if(m_EditV2 >= 1){
		m_EditV2 += work;
		if(m_EditV2 <= 1){
			work = m_EditV2;
			m_EditV2 = 1;
			m_EditV1 += work - 1;
		}
	}
	else {
		m_EditV1 += work - 1;
	}


	m_SliderV1.SetPos(m_EditV1);
	m_SliderV2.SetPos(m_EditV2);
	m_SliderV3.SetPos(m_EditV3);

	HomePageData[0][0].ImageHabaV = m_EditV1;
	HomePageData[0][1].ImageHabaV = m_EditV2;
	HomePageData[0][2].ImageHabaV = m_EditV3;

	UpdateData(false);

}

void CMainFlameEditorDlg::OnReleasedcaptureSliderh1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	*pResult = 0;
	int	work;

	m_EditX1 = m_SliderH1.GetPos();
	m_EditX2 = m_SliderH2.GetPos();
	m_EditX3 = m_SliderH3.GetPos();
	m_EditX4 = m_SliderH4.GetPos();
	m_EditX5 = m_SliderH5.GetPos();

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;

	m_EditX2 += work;
	if(m_EditX2 <= 1 && m_EditX5 > 0){
		work = m_EditX2;
		m_EditX2 = 1;
		m_EditX5 += work;
		if(m_EditX5 < 0){
			work = m_EditX5;
			m_EditX5 = 0;
			m_EditX4 += work;
			if(m_EditX4 < 0){
				work = m_EditX4;
				m_EditX4 = 0;
				m_EditX3 += work;
			}
		}
	}
	if(m_EditX2 <= 1 && m_EditX4 > 0){
		work = m_EditX2;
		m_EditX2 = 1;
		m_EditX4 += work;
		if(m_EditX4 < 0){
			work = m_EditX4;
			m_EditX4 = 0;
			m_EditX3 += work;
		}
	}
	if(m_EditX2 <= 1 && m_EditX3 > 0){
		work = m_EditX2;
		m_EditX2 = 1;
		m_EditX3 += work;
	}

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;
	
	if(work != 0)m_EditX1 += work;

	m_SliderH1.SetPos(m_EditX1);
	m_SliderH2.SetPos(m_EditX2);
	m_SliderH3.SetPos(m_EditX3);
	m_SliderH4.SetPos(m_EditX4);
	m_SliderH5.SetPos(m_EditX5);

	HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH = m_EditX1;
	HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH = m_EditX2;
	HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH = m_EditX3;
	HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH = m_EditX4;
	HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH = m_EditX5;

	UpdateData(false);

}

void CMainFlameEditorDlg::OnReleasedcaptureSliderh2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	*pResult = 0;
	int	work;

	m_EditX1 = m_SliderH1.GetPos();
	m_EditX2 = m_SliderH2.GetPos();
	m_EditX3 = m_SliderH3.GetPos();
	m_EditX4 = m_SliderH4.GetPos();
	m_EditX5 = m_SliderH5.GetPos();

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;

	m_EditX1 += work;
	if(m_EditX1 < 1 && m_EditX5 >= 0){
		work = m_EditX1;
		m_EditX1 = 0;
		m_EditX5 += work;
		if(m_EditX5 <= 0){
			work = m_EditX5;
			m_EditX5 = 0;
			m_EditX4 += work;
			if(m_EditX4 <= 0){
				work = m_EditX4;
				m_EditX4 = 0;
				m_EditX3 += work;
			}
		}
	}
	if(m_EditX1 < 1 && m_EditX4 >= 0){
		work = m_EditX1;
		m_EditX1 = 0;
		m_EditX4 += work;
		if(m_EditX4 <= 0){
			work = m_EditX4;
			m_EditX4 = 0;
			m_EditX3 += work;
		}
	}
	if(m_EditX1 < 1 && m_EditX3 >= 0){
		work = m_EditX1;
		m_EditX1 = 0;
		m_EditX3 += work;
	}

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;
	
	if(work != 0)m_EditX2 += work;

	m_SliderH1.SetPos(m_EditX1);
	m_SliderH2.SetPos(m_EditX2);
	m_SliderH3.SetPos(m_EditX3);
	m_SliderH4.SetPos(m_EditX4);
	m_SliderH5.SetPos(m_EditX5);

	HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH = m_EditX1;
	HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH = m_EditX2;
	HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH = m_EditX3;
	HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH = m_EditX4;
	HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH = m_EditX5;

	UpdateData(false);

}

void CMainFlameEditorDlg::OnReleasedcaptureSliderh3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	*pResult = 0;
		int	work;

	m_EditX1 = m_SliderH1.GetPos();
	m_EditX2 = m_SliderH2.GetPos();
	m_EditX3 = m_SliderH3.GetPos();
	m_EditX4 = m_SliderH4.GetPos();
	m_EditX5 = m_SliderH5.GetPos();

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;

	m_EditX2 += work;
	if(m_EditX2 < 1 && m_EditX5 >= 0){
		work = m_EditX2;
		m_EditX2 = 1;
		m_EditX5 += work;
		if(m_EditX5 <= 0){
			work = m_EditX5;
			m_EditX5 = 0;
			m_EditX4 += work;
			if(m_EditX4 <= 0){
				work = m_EditX4;
				m_EditX4 = 0;
				m_EditX1 += work;
			}
		}
	}
	if(m_EditX2 < 1 && m_EditX4 >= 0){
		work = m_EditX2;
		m_EditX2 = 1;
		m_EditX4 += work;
		if(m_EditX4 <= 0){
			work = m_EditX4;
			m_EditX4 = 0;
			m_EditX1 += work;
		}
	}
	if(m_EditX2 < 1 && m_EditX1 >= 1){
		work = m_EditX2;
		m_EditX2 = 1;
		m_EditX1 += work;
	}

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;
	
	if(work != 0)m_EditX3 += work;


	m_SliderH1.SetPos(m_EditX1);
	m_SliderH2.SetPos(m_EditX2);
	m_SliderH3.SetPos(m_EditX3);
	m_SliderH4.SetPos(m_EditX4);
	m_SliderH5.SetPos(m_EditX5);

	HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH = m_EditX1;
	HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH = m_EditX2;
	HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH = m_EditX3;
	HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH = m_EditX4;
	HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH = m_EditX5;

	UpdateData(false);

}

void CMainFlameEditorDlg::OnReleasedcaptureSliderh4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	*pResult = 0;
	int	work;

	m_EditX1 = m_SliderH1.GetPos();
	m_EditX2 = m_SliderH2.GetPos();
	m_EditX3 = m_SliderH3.GetPos();
	m_EditX4 = m_SliderH4.GetPos();
	m_EditX5 = m_SliderH5.GetPos();

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;

	m_EditX3 += work;
	if(m_EditX3 < 1 && m_EditX5 >= 0){
		work = m_EditX3;
		m_EditX3 = 1;
		m_EditX5 += work;
		if(m_EditX5 <= 0){
			work = m_EditX5;
			m_EditX5 = 0;
			m_EditX2 += work;
			if(m_EditX2 <= 1){
				work = m_EditX2;
				m_EditX2 = 1;
				m_EditX1 += work;
			}
		}
	}
	if(m_EditX3 < 1 && m_EditX2 >= 1){
		work = m_EditX3;
		m_EditX3 = 1;
		m_EditX2 += work;
		if(m_EditX2 <= 0){
			work = m_EditX2;
			m_EditX2 = 0;
			m_EditX1 += work;
		}
	}
	if(m_EditX3 < 1 && m_EditX1 >= 1){
		work = m_EditX3;
		m_EditX3 = 1;
		m_EditX1 += work;
	}

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;
	
	if(work != 0)m_EditX4 += work;

	m_SliderH1.SetPos(m_EditX1);
	m_SliderH2.SetPos(m_EditX2);
	m_SliderH3.SetPos(m_EditX3);
	m_SliderH4.SetPos(m_EditX4);
	m_SliderH5.SetPos(m_EditX5);

	HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH = m_EditX1;
	HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH = m_EditX2;
	HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH = m_EditX3;
	HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH = m_EditX4;
	HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH = m_EditX5;

	UpdateData(false);

}

void CMainFlameEditorDlg::OnReleasedcaptureSliderh5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);

	*pResult = 0;
	int	work;

	m_EditX1 = m_SliderH1.GetPos();
	m_EditX2 = m_SliderH2.GetPos();
	m_EditX3 = m_SliderH3.GetPos();
	m_EditX4 = m_SliderH4.GetPos();
	m_EditX5 = m_SliderH5.GetPos();

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;

	m_EditX4 += work;
	if(m_EditX4 < 1 && m_EditX3 >= 1){
		work = m_EditX4;
		m_EditX4 = 1;
		m_EditX3 += work;
		if(m_EditX3 <= 1){
			work = m_EditX3;
			m_EditX3 = 1;
			m_EditX2 += work;
			if(m_EditX2 <= 1){
				work = m_EditX2;
				m_EditX2 = 1;
				m_EditX1 += work;
			}
		}
	}
	if(m_EditX4 < 1 && m_EditX2 >= 1){
		work = m_EditX4;
		m_EditX4 = 1;
		m_EditX2 += work;
		if(m_EditX2 <= 0){
			work = m_EditX2;
			m_EditX2 = 0;
			m_EditX1 += work;
		}
	}
	if(m_EditX4 < 1 && m_EditX1 >= 1){
		work = m_EditX4;
		m_EditX4 = 1;
		m_EditX1 += work;
	}

	work = 100 - m_EditX1 - m_EditX2 - m_EditX3 - m_EditX4 - m_EditX5;
	
	if(work != 0)m_EditX5 += work;


	m_SliderH1.SetPos(m_EditX1);
	m_SliderH2.SetPos(m_EditX2);
	m_SliderH3.SetPos(m_EditX3);
	m_SliderH4.SetPos(m_EditX4);
	m_SliderH5.SetPos(m_EditX5);

	HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH = m_EditX1;
	HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH = m_EditX2;
	HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH = m_EditX3;
	HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH = m_EditX4;
	HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH = m_EditX5;

	UpdateData(false);
}

void CMainFlameEditorDlg::OnKillfocusEditFilename1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	HomePageData[m_ComboVNo.GetCurSel()][0].ImageName = m_EditFileName1;	
}

void CMainFlameEditorDlg::OnKillfocusEditFilename2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	HomePageData[m_ComboVNo.GetCurSel()][1].ImageName = m_EditFileName2;	
}

void CMainFlameEditorDlg::OnKillfocusEditFilename3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	HomePageData[m_ComboVNo.GetCurSel()][2].ImageName = m_EditFileName3;	
}

void CMainFlameEditorDlg::OnKillfocusEditFilename4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	HomePageData[m_ComboVNo.GetCurSel()][3].ImageName = m_EditFileName4;	
}

void CMainFlameEditorDlg::OnKillfocusEditFilename5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(true);
	HomePageData[m_ComboVNo.GetCurSel()][4].ImageName = m_EditFileName5;	
}

void CMainFlameEditorDlg::OnKillfocusEditv1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderV1.SetPos(HomePageData[0][0].ImageHabaV);
	m_SliderV2.SetPos(HomePageData[0][1].ImageHabaV);
	m_SliderV3.SetPos(HomePageData[0][2].ImageHabaV);
	UpdateData(false);
}

void CMainFlameEditorDlg::OnKillfocusEditv2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderV1.SetPos(HomePageData[0][0].ImageHabaV);
	m_SliderV2.SetPos(HomePageData[0][1].ImageHabaV);
	m_SliderV3.SetPos(HomePageData[0][2].ImageHabaV);
	UpdateData(false);
}

void CMainFlameEditorDlg::OnKillfocusEditv3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderV1.SetPos(HomePageData[0][0].ImageHabaV);
	m_SliderV2.SetPos(HomePageData[0][1].ImageHabaV);
	m_SliderV3.SetPos(HomePageData[0][2].ImageHabaV);
	UpdateData(false);	
}

void CMainFlameEditorDlg::OnKillfocusEditx1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderH1.SetPos(HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH);
	m_SliderH2.SetPos(HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH);
	m_SliderH3.SetPos(HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH);
	m_SliderH4.SetPos(HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH);
	m_SliderH5.SetPos(HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH);
	UpdateData(false);
}

void CMainFlameEditorDlg::OnKillfocusEditx2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderH1.SetPos(HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH);
	m_SliderH2.SetPos(HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH);
	m_SliderH3.SetPos(HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH);
	m_SliderH4.SetPos(HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH);
	m_SliderH5.SetPos(HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH);
	UpdateData(false);
}

void CMainFlameEditorDlg::OnKillfocusEditx3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderH1.SetPos(HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH);
	m_SliderH2.SetPos(HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH);
	m_SliderH3.SetPos(HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH);
	m_SliderH4.SetPos(HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH);
	m_SliderH5.SetPos(HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH);
	UpdateData(false);
}

void CMainFlameEditorDlg::OnKillfocusEditx4() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderH1.SetPos(HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH);
	m_SliderH2.SetPos(HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH);
	m_SliderH3.SetPos(HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH);
	m_SliderH4.SetPos(HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH);
	m_SliderH5.SetPos(HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH);
	UpdateData(false);
}

void CMainFlameEditorDlg::OnKillfocusEditx5() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_SliderH1.SetPos(HomePageData[m_ComboVNo.GetCurSel()][0].ImageHabaH);
	m_SliderH2.SetPos(HomePageData[m_ComboVNo.GetCurSel()][1].ImageHabaH);
	m_SliderH3.SetPos(HomePageData[m_ComboVNo.GetCurSel()][2].ImageHabaH);
	m_SliderH4.SetPos(HomePageData[m_ComboVNo.GetCurSel()][3].ImageHabaH);
	m_SliderH5.SetPos(HomePageData[m_ComboVNo.GetCurSel()][4].ImageHabaH);
	UpdateData(false);
}
