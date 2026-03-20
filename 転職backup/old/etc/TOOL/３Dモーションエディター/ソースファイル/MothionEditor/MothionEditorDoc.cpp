// MothionEditorDoc.cpp : CMothionEditorDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "MothionEditor.h"

#include "MothionEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorDoc

IMPLEMENT_DYNCREATE(CMothionEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMothionEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CMothionEditorDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_EX, OnFileSaveEx)
	ON_COMMAND(ID_FILE_LOAD_EX, OnFileLoadEx)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorDoc クラスの構築/消滅

CMothionEditorDoc::CMothionEditorDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CMothionEditorDoc::~CMothionEditorDoc()
{
}

BOOL CMothionEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMothionEditorDoc シリアライゼーション

void CMothionEditorDoc::Serialize(CArchive& ar)
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
// CMothionEditorDoc クラスの診断

#ifdef _DEBUG
void CMothionEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMothionEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMothionEditorDoc コマンド

void CMothionEditorDoc::OnFileSaveAs() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				mainfile;
	CString				workfile;
	CFileException		openfile;
	PARTS_ROT_POINT* pt ;

	CFileDialog filedlg(false,"txt", NULL, OFN_OVERWRITEPROMPT  , "ヘッダーファイル(*.h)|*.h||");
	if(filedlg.DoModal() != IDOK) return; 

	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	
	mainfile = filedlg.GetFileName();

	workfile = filedlg.GetFileTitle();
	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
	}
	else {

		file.WriteString("//---------------------------------\n");
		file.WriteString("//  [ MotionEditor ] モーションデータ\n");
		file.WriteString("//---------------------------------\n\n");

		file.WriteString("\nMOTION_DATA ");
		workfile.Format("%s",workfile);		file.WriteString(workfile);
		file.WriteString("_motion[");
		workfile.Format("%d * ", pApp->end_check + 1);	file.WriteString(workfile);
		workfile.Format("%d",  PARTS_QTY);				file.WriteString(workfile);

		file.WriteString("] = {\n");

		for(int y = 0; y < pApp->end_check + 1; y++) {
			workfile.Format("//%dフレーム目\n", y);
			file.WriteString(workfile);

			for(int x = 0; x < PARTS_QTY; x++) {
				pt= &pApp->zintai.parts[x]->rot_point[0][y];
	
				file.WriteString("\t{");

				workfile.Format("%0.2ff,", pt->point[0]);
				file.WriteString(workfile);
				workfile.Format("%0.2ff,", pt->point[1]);
				file.WriteString(workfile);
				workfile.Format("%0.2ff,", pt->point[2]);
				file.WriteString(workfile);

				workfile.Format("%0.2ff,", pt->rot[0]);
				file.WriteString(workfile);
				workfile.Format("%0.2ff,", pt->rot[1]);
				file.WriteString(workfile);
				workfile.Format("%0.2ff,", pt->rot[2]);
				file.WriteString(workfile);

				workfile.Format("%d,", pApp->flgset[0][y].attack);
				file.WriteString(workfile);
				workfile.Format("%d,", pApp->flgset[0][y].gard);
				file.WriteString(workfile);
				workfile.Format("%d", pApp->frame_time[0][y]);
				file.WriteString(workfile);


				file.WriteString("},\n");

			}
			file.WriteString("\n");
		}
		file.WriteString("};\n\n");

		file.Close();
	}
	
}

void CMothionEditorDoc::OnFileSaveEx() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
		// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				mainfile;
	CString				workfile;
	CFileException		openfile;
	PARTS_ROT_POINT* pt ;
	int					sign_flg;

	CFileDialog filedlg(false,"DDT", NULL, OFN_OVERWRITEPROMPT  , "3DTOOL専用ファイル(*.DDT)|*.DDT||");
	if(filedlg.DoModal() != IDOK) return; 

	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	mainfile = filedlg.GetFileName();
	
	if(!file.Open(mainfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);

	}
	else {
	
		workfile.Format("%05d\n",pApp->end_check);
		file.WriteString(workfile);

		for(int y = 0; y < pApp->end_check + 1; y++) {

			for(int x = 0; x < PARTS_QTY; x++) {
				pt= &pApp->zintai.parts[x]->rot_point[0][y];

				if(pt->point[0] < 0){
					sign_flg = 1;
					pt->point[0] *= (-1);
				}
				else{
					sign_flg = 0;
				}
				workfile.Format("%05d\n", sign_flg);
				file.WriteString(workfile);
				workfile.Format("%05d\n", (int)(pt->point[0] * 100));
				file.WriteString(workfile);
				if(sign_flg == 1) pt->point[0] *= (-1);

				if(pt->point[1] < 0){
					sign_flg = 1;
					pt->point[1] *= (-1);
				}
				else{
					sign_flg = 0;
				}
				workfile.Format("%05d\n", sign_flg);
				file.WriteString(workfile);
				workfile.Format("%05d\n", (int)(pt->point[1] * 100));
				file.WriteString(workfile);
				if(sign_flg == 1) pt->point[1] *= (-1);

				if(pt->point[2] < 0){
					sign_flg = 1;
					pt->point[2] *= (-1);
				}
				else{
					sign_flg = 0;
				}
				workfile.Format("%05d\n", sign_flg);
				file.WriteString(workfile);
				workfile.Format("%05d\n", (int)(pt->point[2] * 100));
				file.WriteString(workfile);
				if(sign_flg == 1) pt->point[2] *= (-1);


				if(pt->rot[0] < 0){
					sign_flg = 1;
					pt->rot[0] *= (-1);
				}
				else{
					sign_flg = 0;
				}
				workfile.Format("%05d\n", sign_flg);
				file.WriteString(workfile);
				workfile.Format("%05d\n", (int)(pt->rot[0] * 100));
				file.WriteString(workfile);
				if(sign_flg == 1) pt->rot[0] *= (-1);

				if(pt->rot[1] < 0){
					sign_flg = 1;
					pt->rot[1] *= (-1);
				}
				else{
					sign_flg = 0;
				}
				workfile.Format("%05d\n", sign_flg);
				file.WriteString(workfile);
				workfile.Format("%05d\n", (int)(pt->rot[1] * 100));
				file.WriteString(workfile);
				if(sign_flg == 1) pt->rot[1] *= (-1);

				if(pt->rot[2] < 0){
					sign_flg = 1;
					pt->rot[2] *= (-1);
				}
				else{
					sign_flg = 0;
				}
				workfile.Format("%05d\n", sign_flg);
				file.WriteString(workfile);
				workfile.Format("%05d\n", (int)(pt->rot[2] * 100));
				file.WriteString(workfile);
				if(sign_flg == 1) pt->rot[2] *= (-1);


			}
			workfile.Format("%05d\n", pApp->flgset[0][y].attack);
			file.WriteString(workfile);
			workfile.Format("%05d\n", pApp->flgset[0][y].gard);
			file.WriteString(workfile);
			workfile.Format("%05d\n", pApp->frame_time[0][y]);
			file.WriteString(workfile);

		}

		file.Close();
	}
	

}

void CMothionEditorDoc::OnFileLoadEx() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CFileException		openfile;
	CString				mainfile;
	CString				workfile;
	CString				filename;
	char*				a;
	PARTS_ROT_POINT* pt ;
	int					sign_flg;

	CFileDialog filedlg(true,"DDT", NULL, OFN_HIDEREADONLY | OFN_READONLY, "3DTOOL専用ファイル(*.DDT)|*.DDT||");
	if(filedlg.DoModal() != IDOK) return;
	
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	mainfile = filedlg.GetFileName();

	if(!file.Open(mainfile,CFile::modeRead,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {
		a = new char[5];

		file.ReadString(workfile);
		strcpy(a,workfile);	
		pApp->end_check = (a[0]-48) * 10000;
		pApp->end_check += (a[1]-48) * 1000;
		pApp->end_check += (a[2]-48) * 100;
		pApp->end_check += (a[3]-48) * 10;
		pApp->end_check += (a[4]-48) * 1;

		for(int y = 0; y < pApp->end_check + 1; y++) {

			for(int x = 0; x < PARTS_QTY; x++) {

				pt= &pApp->zintai.parts[x]->rot_point[0][y];

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg = (a[0]-48) * 10000;
				sign_flg += (a[1]-48) * 1000;
				sign_flg += (a[2]-48) * 100;
				sign_flg += (a[3]-48) * 10;
				sign_flg += (a[4]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pt->point[0] = (a[0]-48) * 10000;
				pt->point[0] += (a[1]-48) * 1000;
				pt->point[0] += (a[2]-48) * 100;
				pt->point[0] += (a[3]-48) * 10;
				pt->point[0] += (a[4]-48) * 1;
				if(pt->point[0] != 0) pt->point[0] = (float)(pt->point[0] / 100);
				if(sign_flg == 1) pt->point[0] *= -1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg = (a[0]-48) * 10000;
				sign_flg += (a[1]-48) * 1000;
				sign_flg += (a[2]-48) * 100;
				sign_flg += (a[3]-48) * 10;
				sign_flg += (a[4]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pt->point[1] = (a[0]-48) * 10000;
				pt->point[1] += (a[1]-48) * 1000;
				pt->point[1] += (a[2]-48) * 100;
				pt->point[1] += (a[3]-48) * 10;
				pt->point[1] += (a[4]-48) * 1;
				if(pt->point[1] != 0) pt->point[1] = (float)(pt->point[1] / 100);
				if(sign_flg == 1) pt->point[1] *= -1;


				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg = (a[0]-48) * 10000;
				sign_flg += (a[1]-48) * 1000;
				sign_flg += (a[2]-48) * 100;
				sign_flg += (a[3]-48) * 10;
				sign_flg += (a[4]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pt->point[2] = (a[0]-48) * 10000;
				pt->point[2] += (a[1]-48) * 1000;
				pt->point[2] += (a[2]-48) * 100;
				pt->point[2] += (a[3]-48) * 10;
				pt->point[2] += (a[4]-48) * 1;
				if(pt->point[2] != 0) pt->point[2] = (float)(pt->point[2] / 100);
				if(sign_flg == 1) pt->point[2] *= -1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg = (a[0]-48) * 10000;
				sign_flg += (a[1]-48) * 1000;
				sign_flg += (a[2]-48) * 100;
				sign_flg += (a[3]-48) * 10;
				sign_flg += (a[4]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pt->rot[0] = (a[0]-48) * 10000;
				pt->rot[0] += (a[1]-48) * 1000;
				pt->rot[0] += (a[2]-48) * 100;
				pt->rot[0] += (a[3]-48) * 10;
				pt->rot[0] += (a[4]-48) * 1;
				if(pt->rot[0] != 0) pt->rot[0] = (float)(pt->rot[0] / 100);
				if(sign_flg == 1) pt->rot[0] *= -1;


				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg = (a[0]-48) * 10000;
				sign_flg += (a[1]-48) * 1000;
				sign_flg += (a[2]-48) * 100;
				sign_flg += (a[3]-48) * 10;
				sign_flg += (a[4]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pt->rot[1] = (a[0]-48) * 10000;
				pt->rot[1] += (a[1]-48) * 1000;
				pt->rot[1] += (a[2]-48) * 100;
				pt->rot[1] += (a[3]-48) * 10;
				pt->rot[1] += (a[4]-48) * 1;
				if(pt->rot[1] != 0) pt->rot[1] = (float)(pt->rot[1] / 100);
				if(sign_flg == 1) pt->rot[1] *= -1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg = (a[0]-48) * 10000;
				sign_flg += (a[1]-48) * 1000;
				sign_flg += (a[2]-48) * 100;
				sign_flg += (a[3]-48) * 10;
				sign_flg += (a[4]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pt->rot[2] = (a[0]-48) * 10000;
				pt->rot[2] += (a[1]-48) * 1000;
				pt->rot[2] += (a[2]-48) * 100;
				pt->rot[2] += (a[3]-48) * 10;
				pt->rot[2] += (a[4]-48) * 1;
				if(pt->rot[2] != 0) pt->rot[2] = (float)(pt->rot[2] / 100);
				if(sign_flg == 1) pt->rot[2] *= -1;


			}
			file.ReadString(workfile);
			strcpy(a,workfile);	
			pApp->flgset[0][y].attack = (a[0]-48) * 10000;
			pApp->flgset[0][y].attack += (a[1]-48) * 1000;
			pApp->flgset[0][y].attack += (a[2]-48) * 100;
			pApp->flgset[0][y].attack += (a[3]-48) * 10;
			pApp->flgset[0][y].attack += (a[4]-48) * 1;

			file.ReadString(workfile);
			strcpy(a,workfile);	
			pApp->flgset[0][y].gard = (a[0]-48) * 10000;
			pApp->flgset[0][y].gard += (a[1]-48) * 1000;
			pApp->flgset[0][y].gard += (a[2]-48) * 100;
			pApp->flgset[0][y].gard += (a[3]-48) * 10;
			pApp->flgset[0][y].gard += (a[4]-48) * 1;

			file.ReadString(workfile);
			strcpy(a,workfile);	
			pApp->frame_time[0][y] = (a[0]-48) * 10000;
			pApp->frame_time[0][y] += (a[1]-48) * 1000;
			pApp->frame_time[0][y] += (a[2]-48) * 100;
			pApp->frame_time[0][y] += (a[3]-48) * 10;
			pApp->frame_time[0][y] += (a[4]-48) * 1;

		}

		
		file.Close();
	}
	
	pApp->zintai.cur_frame = 0;
	pApp->EditDialog.SetData();

	for(int i = 0; i < PARTS_QTY; i++) {
		pApp->zintai.parts[i]->SetMatrix();			// マトリックスを更新	
	}

}

void CMothionEditorDoc::OnEditCopy() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	for(int i = 0; i < PARTS_QTY; i++) {
		rot_point[i].point[0] = pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].point[0];	
		rot_point[i].point[1] = pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].point[1];	
		rot_point[i].point[2] = pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].point[2];	

		rot_point[i].rot[0] = pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].rot[0];	
		rot_point[i].rot[1] = pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].rot[1];	
		rot_point[i].rot[2] = pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].rot[2];	
	}

}

void CMothionEditorDoc::OnEditPaste() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
	CMothionEditorApp* pApp = (CMothionEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	for(int i = 0; i < PARTS_QTY; i++) {
		pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].point[0] = rot_point[i].point[0];	
		pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].point[1] = rot_point[i].point[1];	
		pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].point[2] = rot_point[i].point[2];	

		pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].rot[0] = rot_point[i].rot[0];	
		pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].rot[1] = rot_point[i].rot[1];	
		pApp->zintai.parts[i]->rot_point[0][pApp->zintai.cur_frame].rot[2] = rot_point[i].rot[2];	
	}

	for(i = 0; i < PARTS_QTY; i++) {
		pApp->zintai.parts[i]->SetMatrix();			// マトリックスを更新	
	}
	
}
