// SpriteToolDoc.cpp : CSpriteToolDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "SpriteTool.h"

#include "SpriteToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolDoc

IMPLEMENT_DYNCREATE(CSpriteToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpriteToolDoc, CDocument)
	//{{AFX_MSG_MAP(CSpriteToolDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_LOAD_EX, OnFileLoadEx)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_EX, OnFileSaveEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolDoc クラスの構築/消滅

CSpriteToolDoc::CSpriteToolDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CSpriteToolDoc::~CSpriteToolDoc()
{
}

BOOL CSpriteToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSpriteToolDoc シリアライゼーション

void CSpriteToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolDoc クラスの診断

#ifdef _DEBUG
void CSpriteToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpriteToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpriteToolDoc コマンド

void CSpriteToolDoc::OnFileOpen() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CStdioFile			file;
	CFileException		openfile;
	CString				workfile;
	CString				filename;
	char*				a;

	CFileDialog filedlg(true,"jpg", NULL, OFN_HIDEREADONLY | OFN_READONLY, "画像ファイル(*.jpg *.tga *.bmp)|*.jpg; *.tga; *.bmp||");
	if(filedlg.DoModal() != IDOK) return;
	
	a = new char[512];
	mainfile = filedlg.GetPathName();
	strcpy(a,mainfile);

	pApp->Dx.mainbord.Initialize(pApp->Dx.D3DDevice8,a);

	pApp->Dx.workbord.Initialize(pApp->Dx.D3DDevice8,a);
	pApp->Dx.workbord.x = 0;
	pApp->Dx.workbord.y = 0;
	pApp->Dx.workbord.pRect.top = 0;
	pApp->Dx.workbord.pRect.left = 0;
	pApp->Dx.workbord.pRect.bottom = 180;
	pApp->Dx.workbord.pRect.right = 180;

	pApp->Dx.exbord.Initialize(pApp->Dx.D3DDevice8,a);
	pApp->Dx.exbord.x = 0;
	pApp->Dx.exbord.y = 0;
	pApp->Dx.exbord.pRect.top = 0;
	pApp->Dx.exbord.pRect.left = 0;
	pApp->Dx.exbord.pRect.bottom = 256;
	pApp->Dx.exbord.pRect.right = 256;

	pApp->Dx.mainbord.pRect.bottom -= 13;
	pApp->Dx.mainbord.x = (float)SCREEN_WIDTH - (float)pApp->Dx.mainbord.ita.Width - (float)136;
	pApp->Dx.mainbord.y = (float)SCREEN_HEIGHT - (float)pApp->Dx.mainbord.ita.Height - (float)16;


	pApp->fileload = 1;
	pApp->draw_flg = 1;

	delete a;
	
}

void CSpriteToolDoc::OnFileLoadEx() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				workfile;
	CFileException		openfile;
	CString				filename;
	char*				a;
	int					error;
	int					i;

	CFileDialog filedlg(true,"bin", NULL, OFN_HIDEREADONLY | OFN_READONLY, "バイナリファイル(*.bin)|*.bin||");
	if(filedlg.DoModal() != IDOK) return;
	
	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	filename = filedlg.GetFileName();
	error = 0;

	if(!file.Open(filename,CFile::modeRead,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {

		file.ReadString(workfile);
		if(workfile != "// AnimationEditFile"){
			workfile.Format("これはAnimationTool用ファイルではありません");
			MessageBox(NULL,workfile,NULL,MB_OK);
			error = 1;
		}

		if(error == 0){ 
			a = new char[8];

			for(i = 0; i < MAX_DATA;i++){
				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->data[i][TOP] =  (float)(a[0]-48) * 1000000;
				pApp->data[i][TOP] += (a[1]-48) * 100000;
				pApp->data[i][TOP] += (a[2]-48) * 10000;
				pApp->data[i][TOP] += (a[3]-48) * 1000;
				pApp->data[i][TOP] += (a[4]-48) * 100;
				pApp->data[i][TOP] += (a[5]-48) * 10;
				pApp->data[i][TOP] += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->data[i][LEFT] =  (float)(a[0]-48) * 1000000;
				pApp->data[i][LEFT] += (a[1]-48) * 100000;
				pApp->data[i][LEFT] += (a[2]-48) * 10000;
				pApp->data[i][LEFT] += (a[3]-48) * 1000;
				pApp->data[i][LEFT] += (a[4]-48) * 100;
				pApp->data[i][LEFT] += (a[5]-48) * 10;
				pApp->data[i][LEFT] += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->data[i][DOWN] =  (float)(a[0]-48) * 1000000;
				pApp->data[i][DOWN] += (a[1]-48) * 100000;
				pApp->data[i][DOWN] += (a[2]-48) * 10000;
				pApp->data[i][DOWN] += (a[3]-48) * 1000;
				pApp->data[i][DOWN] += (a[4]-48) * 100;
				pApp->data[i][DOWN] += (a[5]-48) * 10;
				pApp->data[i][DOWN] += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->data[i][RIGHT] =  (float)(a[0]-48) * 1000000;
				pApp->data[i][RIGHT] += (a[1]-48) * 100000;
				pApp->data[i][RIGHT] += (a[2]-48) * 10000;
				pApp->data[i][RIGHT] += (a[3]-48) * 1000;
				pApp->data[i][RIGHT] += (a[4]-48) * 100;
				pApp->data[i][RIGHT] += (a[5]-48) * 10;
				pApp->data[i][RIGHT] += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->frame_data[i] =  (a[0]-48) * 1000000;
				pApp->frame_data[i] += (a[1]-48) * 100000;
				pApp->frame_data[i] += (a[2]-48) * 10000;
				pApp->frame_data[i] += (a[3]-48) * 1000;
				pApp->frame_data[i] += (a[4]-48) * 100;
				pApp->frame_data[i] += (a[5]-48) * 10;
				pApp->frame_data[i] += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->next_frame[i] =  (a[0]-48) * 1000000;
				pApp->next_frame[i] += (a[1]-48) * 100000;
				pApp->next_frame[i] += (a[2]-48) * 10000;
				pApp->next_frame[i] += (a[3]-48) * 1000;
				pApp->next_frame[i] += (a[4]-48) * 100;
				pApp->next_frame[i] += (a[5]-48) * 10;
				pApp->next_frame[i] += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->attach_kukei[i] =  (a[0]-48) * 1000000;
				pApp->attach_kukei[i] += (a[1]-48) * 100000;
				pApp->attach_kukei[i] += (a[2]-48) * 10000;
				pApp->attach_kukei[i] += (a[3]-48) * 1000;
				pApp->attach_kukei[i] += (a[4]-48) * 100;
				pApp->attach_kukei[i] += (a[5]-48) * 10;
				pApp->attach_kukei[i] += (a[6]-48) * 1;
				
			}
			for(int i = 0; i < CASH_MAX;i++){
				file.ReadString(pApp->cash_string[i]);

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->cash_data[i].top =  (a[0]-48) * 1000000;
				pApp->cash_data[i].top += (a[1]-48) * 100000;
				pApp->cash_data[i].top += (a[2]-48) * 10000;
				pApp->cash_data[i].top += (a[3]-48) * 1000;
				pApp->cash_data[i].top += (a[4]-48) * 100;
				pApp->cash_data[i].top += (a[5]-48) * 10;
				pApp->cash_data[i].top += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->cash_data[i].left =  (a[0]-48) * 1000000;
				pApp->cash_data[i].left += (a[1]-48) * 100000;
				pApp->cash_data[i].left += (a[2]-48) * 10000;
				pApp->cash_data[i].left += (a[3]-48) * 1000;
				pApp->cash_data[i].left += (a[4]-48) * 100;
				pApp->cash_data[i].left += (a[5]-48) * 10;
				pApp->cash_data[i].left += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->cash_data[i].bottom =  (a[0]-48) * 1000000;
				pApp->cash_data[i].bottom += (a[1]-48) * 100000;
				pApp->cash_data[i].bottom += (a[2]-48) * 10000;
				pApp->cash_data[i].bottom += (a[3]-48) * 1000;
				pApp->cash_data[i].bottom += (a[4]-48) * 100;
				pApp->cash_data[i].bottom += (a[5]-48) * 10;
				pApp->cash_data[i].bottom += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->cash_data[i].right =  (a[0]-48) * 1000000;
				pApp->cash_data[i].right += (a[1]-48) * 100000;
				pApp->cash_data[i].right += (a[2]-48) * 10000;
				pApp->cash_data[i].right += (a[3]-48) * 1000;
				pApp->cash_data[i].right += (a[4]-48) * 100;
				pApp->cash_data[i].right += (a[5]-48) * 10;
				pApp->cash_data[i].right += (a[6]-48) * 1;
			}

			delete a;
		}
		file.Close();
	}

	pApp->start.y = (long)pApp->data[0][TOP];
	pApp->start.x = (long)pApp->data[0][LEFT] + 128;
	pApp->end.y = (long)pApp->data[0][DOWN];
	pApp->end.x = (long)pApp->data[0][RIGHT] + 128;

	pApp->Dx.workbord.texRect.top = pApp->start.y;
	pApp->Dx.workbord.texRect.left = pApp->start.x -128;
	pApp->Dx.workbord.texRect.bottom = pApp->end.y;
	pApp->Dx.workbord.texRect.right = pApp->end.x -128;

	CString		work;
	pApp->CashDialog.m_List_Cash.ResetContent();
	pApp->cash_cnt = 0;

	work.Format("Blank(left,top,right,bottom）// コメント");	// 初期データの文字列設定
	pApp->CashDialog.m_List_Cash.InsertString(0,work);			// そして初期文字列配置
	pApp->CashDialog.m_List_Cash.SetCurSel(0);					// ついでにカーソルを初期位置にあわせる

	for(i = 0;i < CASH_MAX;i++){
		if((pApp->cash_data[i].top != pApp->cash_data[i].bottom) && (pApp->cash_data[i].left != pApp->cash_data[i].right)){
			work.Format("%d:矩形(%d,%d,%d,%d) // %s",i+1,(int)pApp->cash_data[pApp->cash_cnt].left -128,(int)pApp->cash_data[pApp->cash_cnt].top,(int)pApp->cash_data[pApp->cash_cnt].right -128,
						(int)pApp->cash_data[pApp->cash_cnt].bottom,pApp->cash_string[pApp->cash_cnt]);
			pApp->CashDialog.m_List_Cash.InsertString(pApp->cash_cnt + 1,work);
			pApp->cash_cnt++;
		}
		else{
			i = CASH_MAX;
		}
	}

	pApp->draw_flg = 1;	
}

void CSpriteToolDoc::OnFileSave() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				mainfile;
	CString				workfile;
	CFileException		openfile;
	CString				filename;
	int					cnt;

	CFileDialog filedlg(false,"c", NULL, OFN_OVERWRITEPROMPT  , "ソースファイル(*.c)|*.c||");
	if(filedlg.DoModal() != IDOK) return; 

	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	
	filename = filedlg.GetFileName();
	workfile = filedlg.GetFileTitle();

	if(!file.Open(filename,CFile::modeCreate | CFile::modeWrite,&openfile)){
	}
	else {
		cnt = 0;

		file.WriteString("//---------------------------------\n");
		file.WriteString("//  [ SpriteRectData ] \n");
		file.WriteString("//---------------------------------\n\n");

		file.WriteString("\nextern const rect ");
		workfile.Format("%s",workfile);		file.WriteString(workfile);
		file.WriteString("[");
		
		workfile.Format("%d", pApp->cash_cnt);	file.WriteString(workfile);

		file.WriteString("] = {\n");

		for(int i = 0;i < pApp->cash_cnt;i++){
			workfile.Format("{%d,", pApp->cash_data[i].top);
			file.WriteString(workfile);
			workfile.Format("%d,", pApp->cash_data[i].bottom);
			file.WriteString(workfile);

			workfile.Format("%d,", pApp->cash_data[i].left);
			file.WriteString(workfile);

			workfile.Format("%d},", pApp->cash_data[i].right);
			file.WriteString(workfile);


			if(pApp->cash_string[i] != ""){
				workfile.Format("	// %s \n", pApp->cash_string[i]);
				file.WriteString(workfile);
			}
			else{
				workfile.Format("\n");
				file.WriteString(workfile);
			}
		}

		file.WriteString("};\n\n");

		file.Close();
	}
	pApp->draw_flg = 1;	
}

void CSpriteToolDoc::OnFileSaveEx() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				workfile;
	CFileException		openfile;

	CFileDialog filedlg(false,"bin", NULL, OFN_OVERWRITEPROMPT  , "バイナリファイル(*.BIN *.bin)|*.bin||");
	if(filedlg.DoModal() != IDOK) return; 

	CSpriteToolApp* pApp = (CSpriteToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	workfile = filedlg.GetFileName();

	if(!file.Open(workfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);

	}
	else {
		workfile.Format("// AnimationEditFile\n");
		file.WriteString(workfile);

		for(int i = 0; i < MAX_DATA;i++){
			workfile.Format("%07d\n", (int)pApp->data[i][TOP]);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->data[i][LEFT]);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->data[i][DOWN]);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->data[i][RIGHT]);
			file.WriteString(workfile);
			workfile.Format("%07d\n", pApp->frame_data[i]);
			file.WriteString(workfile);
			workfile.Format("%07d\n", pApp->next_frame[i]);
			file.WriteString(workfile);
			workfile.Format("%07d\n", pApp->attach_kukei[i]);
			file.WriteString(workfile);
		}
		for(i = 0; i < CASH_MAX;i++){
			file.WriteString(pApp->cash_string[i]);
			workfile.Format("\n");
			file.WriteString(workfile);
			workfile.Format("%07d\n", pApp->cash_data[i].top);
			file.WriteString(workfile);
			workfile.Format("%07d\n", pApp->cash_data[i].left);
			file.WriteString(workfile);
			workfile.Format("%07d\n", pApp->cash_data[i].bottom);
			file.WriteString(workfile);
			workfile.Format("%07d\n", pApp->cash_data[i].right);
			file.WriteString(workfile);
		}

		file.Close();
	}

	pApp->draw_flg = 1;
	
}
