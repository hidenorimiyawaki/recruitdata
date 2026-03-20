// VectorSetToolDoc.cpp : CVectorSetToolDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "VectorSetTool.h"

#include "VectorSetToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolDoc

IMPLEMENT_DYNCREATE(CVectorSetToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CVectorSetToolDoc, CDocument)
	//{{AFX_MSG_MAP(CVectorSetToolDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(AFX_ID_FILE_SAVE_EX, OnIdFileSaveEx)
	ON_COMMAND(AFX_ID_FILE_LOAD_EX, OnIdFileLoadEx)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolDoc クラスの構築/消滅

CVectorSetToolDoc::CVectorSetToolDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CVectorSetToolDoc::~CVectorSetToolDoc()
{
}

BOOL CVectorSetToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolDoc シリアライゼーション

void CVectorSetToolDoc::Serialize(CArchive& ar)
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
// CVectorSetToolDoc クラスの診断

#ifdef _DEBUG
void CVectorSetToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVectorSetToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVectorSetToolDoc コマンド

void CVectorSetToolDoc::OnFileOpen() 
{
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);


	CStdioFile			file;
	CFileException		openfile;
	CString				workfile;
	CString				filename;
	char*				a;

	CFileDialog filedlg(true,"x", NULL, OFN_HIDEREADONLY | OFN_READONLY, "Xファイル(*.x *.X)|*.x; *.X||");
	if(filedlg.DoModal() != IDOK) return;
	
	a = new char[1024];
	pApp->mainfile = filedlg.GetPathName();
	pApp->mainmodel.LoadData();

	pApp->fileload = 1;
	pApp->draw_flg = 1;

	delete a;
}

void CVectorSetToolDoc::OnIdFileSaveEx() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				workfile;
	CFileException		openfile;
	int					sign_flg;

	CFileDialog filedlg(false,"bin", NULL, OFN_OVERWRITEPROMPT  , "バイナリファイル(*.BIN *.bin)|*.bin||");
	if(filedlg.DoModal() != IDOK) return; 

	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	workfile = filedlg.GetFileName();

	if(!file.Open(workfile,CFile::modeCreate | CFile::modeWrite,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);

	}
	else {
		workfile.Format("// VectorSetFile\n");
		file.WriteString(workfile);

		for(int i = 0; i < MAX_DATA;i++){
			if(pApp->point[i].x < 0){
				sign_flg = 1;
				pApp->point[i].x *= (-1);
			}
			else{
				sign_flg = 0;
			}
			workfile.Format("%07d\n", sign_flg);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->point[i].x);
			file.WriteString(workfile);
			if(sign_flg == 1) pApp->point[i].x *= (-1);

			if(pApp->point[i].y < 0){
				sign_flg = 1;
				pApp->point[i].y *= (-1);
			}
			else{
				sign_flg = 0;
			}
			workfile.Format("%07d\n", sign_flg);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->point[i].y);
			file.WriteString(workfile);
			if(sign_flg == 1) pApp->point[i].y *= (-1);


			if(pApp->ballon_point[i].x < 0){
				sign_flg = 1;
				pApp->ballon_point[i].x *= (-1);
			}
			else{
				sign_flg = 0;
			}
			workfile.Format("%07d\n", sign_flg);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->ballon_point[i].x);
			file.WriteString(workfile);
			if(sign_flg == 1) pApp->ballon_point[i].x *= (-1);

			if(pApp->ballon_point[i].y < 0){
				sign_flg = 1;
				pApp->ballon_point[i].y *= (-1);
			}
			else{
				sign_flg = 0;
			}
			workfile.Format("%07d\n", sign_flg);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->ballon_point[i].y);
			file.WriteString(workfile);
			if(sign_flg == 1) pApp->ballon_point[i].y *= (-1);


			if(pApp->drum_point[i].x < 0){
				sign_flg = 1;
				pApp->drum_point[i].x *= (-1);
			}
			else{
				sign_flg = 0;
			}
			workfile.Format("%07d\n", sign_flg);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->drum_point[i].x);
			file.WriteString(workfile);
			if(sign_flg == 1) pApp->drum_point[i].x *= (-1);

			if(pApp->drum_point[i].y < 0){
				sign_flg = 1;
				pApp->drum_point[i].y *= (-1);
			}
			else{
				sign_flg = 0;
			}
			workfile.Format("%07d\n", sign_flg);
			file.WriteString(workfile);
			workfile.Format("%07d\n", (int)pApp->drum_point[i].y);
			file.WriteString(workfile);
			if(sign_flg == 1) pApp->drum_point[i].y *= (-1);


		}
		workfile.Format("%07d\n", pApp->point_cnt);
		file.WriteString(workfile);
		workfile.Format("%07d\n", pApp->ballon_point_cnt);
		file.WriteString(workfile);
		workfile.Format("%07d\n", pApp->drum_point_cnt);
		file.WriteString(workfile);
		file.Close();
	}

	pApp->draw_flg = 1;

}

void CVectorSetToolDoc::OnIdFileLoadEx() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				workfile;
	CFileException		openfile;
	CString				filename;
	char*				a;
	int					error;
	int					i;
	int					sign_flg;

	CFileDialog filedlg(true,"bin", NULL, OFN_HIDEREADONLY | OFN_READONLY, "バイナリファイル(*.bin)|*.bin||");
	if(filedlg.DoModal() != IDOK) return;
	
	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	filename = filedlg.GetFileName();
	error = 0;

	if(!file.Open(filename,CFile::modeRead,&openfile)){
		MessageBox(NULL, "ファイルがオープンできませんでした", "error", MB_OK | MB_ICONWARNING);
	}
	else {

		file.ReadString(workfile);
		if(workfile != "// VectorSetFile"){
			workfile.Format("これはVectorSetTool用ファイルではありません");
			MessageBox(NULL,workfile,NULL,MB_OK);
			error = 1;
		}

		if(error == 0){ 
			a = new char[9];

			for(i = 0; i < MAX_DATA;i++){

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg =  (a[0]-48) * 1000000;
				sign_flg += (a[1]-48) * 100000;
				sign_flg += (a[2]-48) * 10000;
				sign_flg += (a[3]-48) * 1000;
				sign_flg += (a[4]-48) * 100;
				sign_flg += (a[5]-48) * 10;
				sign_flg += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->point[i].x =  (a[0]-48) * 1000000;
				pApp->point[i].x += (a[1]-48) * 100000;
				pApp->point[i].x += (a[2]-48) * 10000;
				pApp->point[i].x += (a[3]-48) * 1000;
				pApp->point[i].x += (a[4]-48) * 100;
				pApp->point[i].x += (a[5]-48) * 10;
				pApp->point[i].x += (a[6]-48) * 1;
				if(sign_flg == 1) pApp->point[i].x *= (-1);

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg =  (a[0]-48) * 1000000;
				sign_flg += (a[1]-48) * 100000;
				sign_flg += (a[2]-48) * 10000;
				sign_flg += (a[3]-48) * 1000;
				sign_flg += (a[4]-48) * 100;
				sign_flg += (a[5]-48) * 10;
				sign_flg += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->point[i].y =  (a[0]-48) * 1000000;
				pApp->point[i].y += (a[1]-48) * 100000;
				pApp->point[i].y += (a[2]-48) * 10000;
				pApp->point[i].y += (a[3]-48) * 1000;
				pApp->point[i].y += (a[4]-48) * 100;
				pApp->point[i].y += (a[5]-48) * 10;
				pApp->point[i].y += (a[6]-48) * 1;	
				if(sign_flg == 1) pApp->point[i].y *= (-1);



				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg =  (a[0]-48) * 1000000;
				sign_flg += (a[1]-48) * 100000;
				sign_flg += (a[2]-48) * 10000;
				sign_flg += (a[3]-48) * 1000;
				sign_flg += (a[4]-48) * 100;
				sign_flg += (a[5]-48) * 10;
				sign_flg += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->ballon_point[i].x =  (a[0]-48) * 1000000;
				pApp->ballon_point[i].x += (a[1]-48) * 100000;
				pApp->ballon_point[i].x += (a[2]-48) * 10000;
				pApp->ballon_point[i].x += (a[3]-48) * 1000;
				pApp->ballon_point[i].x += (a[4]-48) * 100;
				pApp->ballon_point[i].x += (a[5]-48) * 10;
				pApp->ballon_point[i].x += (a[6]-48) * 1;
				if(sign_flg == 1) pApp->ballon_point[i].x *= (-1);

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg =  (a[0]-48) * 1000000;
				sign_flg += (a[1]-48) * 100000;
				sign_flg += (a[2]-48) * 10000;
				sign_flg += (a[3]-48) * 1000;
				sign_flg += (a[4]-48) * 100;
				sign_flg += (a[5]-48) * 10;
				sign_flg += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->ballon_point[i].y =  (a[0]-48) * 1000000;
				pApp->ballon_point[i].y += (a[1]-48) * 100000;
				pApp->ballon_point[i].y += (a[2]-48) * 10000;
				pApp->ballon_point[i].y += (a[3]-48) * 1000;
				pApp->ballon_point[i].y += (a[4]-48) * 100;
				pApp->ballon_point[i].y += (a[5]-48) * 10;
				pApp->ballon_point[i].y += (a[6]-48) * 1;	
				if(sign_flg == 1) pApp->ballon_point[i].y *= (-1);


				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg =  (a[0]-48) * 1000000;
				sign_flg += (a[1]-48) * 100000;
				sign_flg += (a[2]-48) * 10000;
				sign_flg += (a[3]-48) * 1000;
				sign_flg += (a[4]-48) * 100;
				sign_flg += (a[5]-48) * 10;
				sign_flg += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->drum_point[i].x =  (a[0]-48) * 1000000;
				pApp->drum_point[i].x += (a[1]-48) * 100000;
				pApp->drum_point[i].x += (a[2]-48) * 10000;
				pApp->drum_point[i].x += (a[3]-48) * 1000;
				pApp->drum_point[i].x += (a[4]-48) * 100;
				pApp->drum_point[i].x += (a[5]-48) * 10;
				pApp->drum_point[i].x += (a[6]-48) * 1;
				if(sign_flg == 1) pApp->drum_point[i].x *= (-1);

				file.ReadString(workfile);
				strcpy(a,workfile);	
				sign_flg =  (a[0]-48) * 1000000;
				sign_flg += (a[1]-48) * 100000;
				sign_flg += (a[2]-48) * 10000;
				sign_flg += (a[3]-48) * 1000;
				sign_flg += (a[4]-48) * 100;
				sign_flg += (a[5]-48) * 10;
				sign_flg += (a[6]-48) * 1;

				file.ReadString(workfile);
				strcpy(a,workfile);	
				pApp->drum_point[i].y =  (a[0]-48) * 1000000;
				pApp->drum_point[i].y += (a[1]-48) * 100000;
				pApp->drum_point[i].y += (a[2]-48) * 10000;
				pApp->drum_point[i].y += (a[3]-48) * 1000;
				pApp->drum_point[i].y += (a[4]-48) * 100;
				pApp->drum_point[i].y += (a[5]-48) * 10;
				pApp->drum_point[i].y += (a[6]-48) * 1;	
				if(sign_flg == 1) pApp->drum_point[i].y *= (-1);
			}
			file.ReadString(workfile);
			strcpy(a,workfile);	
			pApp->point_cnt =  (a[0]-48) * 1000000;
			pApp->point_cnt += (a[1]-48) * 100000;
			pApp->point_cnt += (a[2]-48) * 10000;
			pApp->point_cnt += (a[3]-48) * 1000;
			pApp->point_cnt += (a[4]-48) * 100;
			pApp->point_cnt += (a[5]-48) * 10;
			pApp->point_cnt += (a[6]-48) * 1;

			file.ReadString(workfile);
			strcpy(a,workfile);	
			pApp->ballon_point_cnt =  (a[0]-48) * 1000000;
			pApp->ballon_point_cnt += (a[1]-48) * 100000;
			pApp->ballon_point_cnt += (a[2]-48) * 10000;
			pApp->ballon_point_cnt += (a[3]-48) * 1000;
			pApp->ballon_point_cnt += (a[4]-48) * 100;
			pApp->ballon_point_cnt += (a[5]-48) * 10;
			pApp->ballon_point_cnt += (a[6]-48) * 1;

			file.ReadString(workfile);
			strcpy(a,workfile);	
			pApp->drum_point_cnt =  (a[0]-48) * 1000000;
			pApp->drum_point_cnt += (a[1]-48) * 100000;
			pApp->drum_point_cnt += (a[2]-48) * 10000;
			pApp->drum_point_cnt += (a[3]-48) * 1000;
			pApp->drum_point_cnt += (a[4]-48) * 100;
			pApp->drum_point_cnt += (a[5]-48) * 10;
			pApp->drum_point_cnt += (a[6]-48) * 1;


			delete a;
		}
		file.Close();
	}


	pApp->draw_flg = 1;
}

void CVectorSetToolDoc::OnFileSave() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CStdioFile			file;
	CString				mainfile;
	CString				workfile;
	CString				titlefile;
	CFileException		openfile;
	CString				filename;
	int					work;
	CFileDialog filedlg(false,"c", NULL, OFN_OVERWRITEPROMPT  , "ソースファイル(*.c)|*.c||");
	if(filedlg.DoModal() != IDOK) return; 

	CVectorSetToolApp* pApp = (CVectorSetToolApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	filename = filedlg.GetFileName();
	titlefile = filedlg.GetFileTitle();

	if(!file.Open(filename,CFile::modeCreate | CFile::modeWrite,&openfile)){
	}
	else {

		file.WriteString("//---------------------------------\n");
		file.WriteString("//  [ VectorData ] \n");
		file.WriteString("//---------------------------------\n\n");

		work = 0 - pApp->point[0].y ;
		file.WriteString("\nextern const CGroundHitVertex c_");
		workfile.Format("%s",titlefile);		file.WriteString(workfile);
		workfile.Format("[%d] = {\n", pApp->point_cnt);
		file.WriteString(workfile);
		for(int i = 0; i < pApp->point_cnt-1;i++){
			workfile.Format("CGVtx(D3DXVECTOR2(%d,%d)",pApp->point[i].x - (SCREEN_WIDTH /2),pApp->point[i].y+work);
			file.WriteString(workfile); 
			if(pApp->point[i].y == pApp->point[i+1].y){ 
				file.WriteString(",GH_GROUND),\n");
			}
			else{
				file.WriteString(",GH_SLOOP),\n");
			}
		}
		workfile.Format("CGVtx(D3DXVECTOR2(30000.0f,0.0f),GH_END)};\n\n");
		file.WriteString(workfile);


		if(pApp->drum_point_cnt > 0){
			file.WriteString("//---------------------------------\n");
			file.WriteString("//  [ DrumData ] \n");
			file.WriteString("//---------------------------------\n\n");

			file.WriteString("const int c_n");
			workfile.Format("%s",titlefile);		file.WriteString(workfile);
			workfile.Format("DrumNum = %d;", pApp->drum_point_cnt);
			file.WriteString(workfile);

			file.WriteString("\nconst D3DXVECTOR2	c_av");
			workfile.Format("%s",titlefile);		file.WriteString(workfile);

			file.WriteString("DrumPos[] = {\n");
			for(int i = 0; i < pApp->drum_point_cnt;i++){
				workfile.Format("D3DXVECTOR2(%d,%d),\n",pApp->drum_point[i].x - (SCREEN_WIDTH /2),pApp->drum_point[i].y -SET_OFFSET);
				file.WriteString(workfile); 
			}
			workfile.Format("};\n\n");
			file.WriteString(workfile);
		}

		if(pApp->ballon_point_cnt > 0){		
			file.WriteString("//---------------------------------\n");
			file.WriteString("//  [ BallonData ] \n");
			file.WriteString("//---------------------------------\n\n");

			file.WriteString("const int c_n");
			workfile.Format("%s",titlefile);		file.WriteString(workfile);
			workfile.Format("BallonNum = %d;", pApp->ballon_point_cnt);
			file.WriteString(workfile);

			file.WriteString("\nconst D3DXVECTOR2	c_av");
			workfile.Format("%s",titlefile);		file.WriteString(workfile);

			file.WriteString("BallonPos[] = {\n");
			for(int i = 0; i < pApp->ballon_point_cnt;i++){
				workfile.Format("D3DXVECTOR2(%d,%d),\n",pApp->ballon_point[i].x - (SCREEN_WIDTH /2),pApp->ballon_point[i].y -SET_OFFSET);
				file.WriteString(workfile); 
			}
			workfile.Format("};");
			file.WriteString(workfile);
		}

		file.Close();
	
	}
	pApp->draw_flg = 1;
}
