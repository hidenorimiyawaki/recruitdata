// AttrDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mapeditor.h"
#include "AttrDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttrDialog ダイアログ


CAttrDialog::CAttrDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAttrDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAttrDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CAttrDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttrDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttrDialog, CDialog)
	//{{AFX_MSG_MAP(CAttrDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttrDialog メッセージ ハンドラ

BOOL CAttrDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください

	//----- ここから ----- Phase 3 : シリアライズ

	// アプリケーションオブジェクトのポインタを取得
	CMapEditorApp* pApp = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// ラジオボタンの設定
	CButton* radio0 = (CButton*)GetDlgItem(IDC_RADIO_NO_HIT);
	CButton* radio1 = (CButton*)GetDlgItem(IDC_RADIO_HIT);
	// 現在のマップデータを取得
	int data = pApp->MapData.GetMapData(pApp->CurrentMapPoint.x, pApp->CurrentMapPoint.y);
	// データからボタンの状態をセット
	if(data & 0x00010000) {
		radio1->SetCheck(1);		// あたり判定あり
	} else {
		radio0->SetCheck(1);		// あたり判定なし
	}

	//----- ここまで -----

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CAttrDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	//----- ここから ----- Phase 3 : シリアライズ

	// アプリケーションオブジェクトのポインタを取得
	CMapEditorApp* pApp = (CMapEditorApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	// ラジオボタンの設定
	CButton* radio0 = (CButton*)GetDlgItem(IDC_RADIO_NO_HIT);
	CButton* radio1 = (CButton*)GetDlgItem(IDC_RADIO_HIT);
	// 現在のマップデータを取得
	int data = pApp->MapData.GetMapData(pApp->CurrentMapPoint.x, pApp->CurrentMapPoint.y);
	// ボタンの状態からデータを再設定
	if(radio0->GetCheck()) {	// 「判定なし」がチェックされている
		data &= 0xfffeffff;		// ビットを倒す
	}
	if(radio1->GetCheck()) {	// 「判定あり」がチェックされている
		data |= 0x00010000;		// ビットを立てる
	}
	pApp->MapData.SetMapData(pApp->CurrentMapPoint.x, pApp->CurrentMapPoint.y, data);

	// ビューを再描画
	POSITION posDocTpl = pApp->GetFirstDocTemplatePosition();	// 最初のテンプレートの位置を取得
	CDocTemplate* docTpl = pApp->GetNextDocTemplate(posDocTpl);	// 最初のテンプレートを取得

	POSITION posDoc = docTpl->GetFirstDocPosition();		// 最初のドキュメントの位置を取得
	CDocument* document = docTpl->GetNextDoc(posDoc);		// 最初のドキュメントを取得

	document->UpdateAllViews(NULL);							// ドキュメントからビューを更新

	//----- ここまで -----

	CDialog::OnOK();
}


