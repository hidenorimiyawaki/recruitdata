// GlidDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "animationtool.h"
#include "GlidDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlidDialog ダイアログ


CGlidDialog::CGlidDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGlidDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGlidDialog)
	m_Edit_Caption = _T("");
	//}}AFX_DATA_INIT
	delete_flg = OFF;

}


void CGlidDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGlidDialog)
	DDX_Control(pDX, IDC_BIT_TEST, m_Bit_Test);
	DDX_Control(pDX, IDC_LIST_CASH, m_List_Cash);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_Edit_Caption);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGlidDialog, CDialog)
	//{{AFX_MSG_MAP(CGlidDialog)
	ON_LBN_DBLCLK(IDC_LIST_CASH, OnDblclkListCash)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LIST_CASH, OnSelchangeListCash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlidDialog メッセージ ハンドラ

void CGlidDialog::OnOK() 
{
	// OKボタンないんでなんもしません
	
	CDialog::OnOK();
}

void CGlidDialog::OnCancel() 
{
	// キャンセルボタンないんでなんもしません
	
	CDialog::OnCancel();
}


BOOL CGlidDialog::PreTranslateMessage(MSG* pMsg) 
{

	// 入力キーでメッセージが発生した場合の処理
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定

	int			work_cnt;													// 設定段数の保存変数
	CString		work;														// リストの文章描画のための変数

	switch(pMsg->message) {													// 今来たメッセージは？
		case WM_KEYDOWN:													// キーダウンだったら
			switch(pMsg->wParam) {											// 何キーですか？
			case VK_RETURN:	
				if(enter_flg == OFF){									
					enter_flg = ON;									
				}
				return true;								// RETURNキーなら押されてなかった事にする
			case VK_ESCAPE:		return true;								// ESCAPEキーなら押されてなかった事にする
			case VK_DELETE:													// DELETEキーならフラグ設定しよう
				if(delete_flg == OFF){										// デリート許可無いの？
					delete_flg = ON;										// なら出しましょう
				}
				return true;
			}
			break;

		case WM_KEYUP:														// キーアップだったら
			switch(pMsg->wParam) {											// 何キーですか？
			default:
			break;
			case VK_DELETE:													// DELETEキーなら処理しましょう
				if(delete_flg == ON){										// デリート許可は下りてますか？
					if(	pApp->GlidDialog.m_List_Cash.GetCurSel() != 0){		// キャッシュのカーソルは1段目？
						work_cnt = pApp->GlidDialog.m_List_Cash.GetCurSel();// 違うなら、今のカーソル位置を取得
						
						for(int i = work_cnt - 1;i < pApp->cash_cnt;i++){	// その位置から中身を一個下にずらしていこう
							pApp->cash_data[i] = pApp->cash_data[i + 1];	// まずはデータから
							pApp->cash_string[i] = pApp->cash_string[i + 1];// 次に注釈文章ね
						}
						pApp->cash_cnt--;									// カウンタを減らしておくのも忘れずに
						pApp->GlidDialog.m_List_Cash.DeleteString(work_cnt);
/*
						for(i = work_cnt-1;i < pApp->cash_cnt;i++){
							
							if((pApp->cash_data[i].left == pApp->cash_data[i].right) || (pApp->cash_data[i].top == pApp->cash_data[i].bottom)){
								i = pApp->cash_cnt;
							}
							else{
								work.Format("%d:矩形(%d,%d,%d,%d) // %s",i,(int)pApp->cash_data[i+1].left -128,(int)pApp->cash_data[i+1].top,(int)pApp->cash_data[i+1].right -128,
											(int)pApp->cash_data[i+1].bottom,pApp->cash_string[i+1]);
																									// キャッシュ用文章再構成

								pApp->GlidDialog.m_List_Cash.InsertString(i,work);			// 消した位置に注釈つきでキャッシュ書き直し
								pApp->GlidDialog.m_List_Cash.SetCurSel(i);					// で、その位置にカーソル戻そう
							}
						}
*/
						for(i = 0;i < CASH_MAX;i++){						// その位置から中身を一個下にずらしていこう
							if(pApp->attach_kukei[i] >= work_cnt){			// 取得してあるキャッシュが今の位置より大きい？
								pApp->attach_kukei[i]--;					// じゃあ、1段減らしましょう
							}
						}

						pApp->GlidDialog.m_List_Cash.SetCurSel(0);			// 一応、1番目にカーソル戻しとこう

					}
					delete_flg = OFF;										// 全部終わったら、許可廃棄
				}
				return true;
			}
			case VK_RETURN:													// RETURNキーなら
				if(enter_flg == ON){										
					UpdateData(true);														// ダイアログの今の内容取得

					if(	pApp->GlidDialog.m_List_Cash.GetCurSel() != 0){						// カーソル位置0番目じゃない？
						work_cnt = pApp->GlidDialog.m_List_Cash.GetCurSel();				// じゃあ、カーソル位置記憶して
						pApp->cash_string[work_cnt - 1] = m_Edit_Caption;					// 文章保存用の変数に今の文章渡そう
						pApp->GlidDialog.m_List_Cash.DeleteString(work_cnt);				// で、その位置のキャッシュ消しましょう

						work_cnt -= 1;														// 消したからカウンタ一個減らす

						work.Format("%d:矩形(%d,%d,%d,%d) // %s",work_cnt+1,(int)pApp->cash_data[work_cnt].left -128,(int)pApp->cash_data[work_cnt].top,(int)pApp->cash_data[work_cnt].right -128,
									(int)pApp->cash_data[work_cnt].bottom,pApp->cash_string[work_cnt]);
																							// キャッシュ用文章再構成

						pApp->GlidDialog.m_List_Cash.InsertString(work_cnt+1,work);			// 消した位置に注釈つきでキャッシュ書き直し
						pApp->GlidDialog.m_List_Cash.SetCurSel(work_cnt+1);					// で、その位置にカーソル戻そう
					enter_flg = OFF;	
					}
				return true;
				}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CGlidDialog::OnDblclkListCash() 
{
	// グリッドキャッシュがダブルクリックされたときに注釈メッセージを加えましょう処理

	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定

	int			work_cnt;													// カーソル位置一時保管変数
	CString		work;														// 

	UpdateData(true);														// ダイアログの今の内容取得

	if(	pApp->GlidDialog.m_List_Cash.GetCurSel() != 0){						// カーソル位置0番目じゃない？
		work_cnt = pApp->GlidDialog.m_List_Cash.GetCurSel();				// じゃあ、カーソル位置記憶して
		pApp->cash_string[work_cnt - 1] = m_Edit_Caption;					// 文章保存用の変数に今の文章渡そう
		pApp->GlidDialog.m_List_Cash.DeleteString(work_cnt);				// で、その位置のキャッシュ消しましょう

		work_cnt -= 1;														// 消したからカウンタ一個減らす

		work.Format("%d:矩形(%d,%d,%d,%d) // %s",work_cnt+1,(int)pApp->cash_data[work_cnt].left -128,(int)pApp->cash_data[work_cnt].top,(int)pApp->cash_data[work_cnt].right -128,
					(int)pApp->cash_data[work_cnt].bottom,pApp->cash_string[work_cnt]);
																			// キャッシュ用文章再構成

		pApp->GlidDialog.m_List_Cash.InsertString(work_cnt+1,work);			// 消した位置に注釈つきでキャッシュ書き直し
		pApp->GlidDialog.m_List_Cash.SetCurSel(work_cnt+1);					// で、その位置にカーソル戻そう
		
	}
}


void CGlidDialog::DrawExec()
{
	Invalidate(false);
}

void CGlidDialog::OnPaint() 
{
	// 仮想ビットマップ領域を現実の描画領域に貼り付け描画

	CPaintDC dc(this);														// 描画用のデバイス コンテキスト(MFC様御用達なんで使いません)
		
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定
	CDC *pDC;																// デバイスコンテキスト用の取得用変数作成
	pDC = m_Bit_Test.GetDC();												// デバイスコンテキスト取得

	pDC->BitBlt(0, 0,180,180, &memDC, 0, 0, SRCCOPY);						// 仮想ビットマップを貼り付け描画
	
	ReleaseDC(pDC);															// デバイスコンテキスト開放

}

BOOL CGlidDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// ダイアログが起動されたときに仮想ビットマップ領域を作成
	CDC *pDC;																// デバイスコンテキスト用の取得用変数作成
	pDC = m_Bit_Test.GetDC();												// デバイスコンテキスト取得
	memDC.CreateCompatibleDC(pDC);											// 仮想画面用メンバ変数(メモリDC)に描画許可設定	
	Bitmap.CreateCompatibleBitmap(pDC,180,180);								// 仮想ビットマップ領域作成
	memDC.SelectObject(&Bitmap);											// メモリDCに仮想ビットマップ領域を関連付け
	memDC.ExtFloodFill(0,0,RGB(0,0,0),FLOODFILLSURFACE);					// メモリDCを白で初期化
	ReleaseDC(pDC);															// デバイスコンテキスト開放	

	delete_flg = enter_flg = 0;
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CGlidDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	Invalidate(false);
}

void CGlidDialog::OnSelchangeListCash() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定

	int		work;															// カーソル位置一時保存用変数

	work = pApp->GlidDialog.m_List_Cash.GetCurSel();						// カーソル位置保存
	
	if(work != 0){															// やってから、何ですが0番目じゃないよね
		pApp->start.x = pApp->cash_data[work - 1].left;						// そうじゃないなら
		pApp->start.y = pApp->cash_data[work - 1].top;						// カーソルを
		pApp->end.x = pApp->cash_data[work - 1].right;						// 表示するために
		pApp->end.y = pApp->cash_data[work - 1].bottom;						// 保存してある領域から再設定

		pApp->Dx.workbord.texRect.top = pApp->cash_data[work - 1].top;		// 絵の参照位置も再設定
		pApp->Dx.workbord.texRect.left = pApp->cash_data[work - 1].left -128;
		pApp->Dx.workbord.texRect.bottom = pApp->cash_data[work - 1].bottom;
		pApp->Dx.workbord.texRect.right = pApp->cash_data[work - 1].right -128;
	
		pApp->DrawExecEx();													// で、描画するために仮想BITMAPに描画
	}
}


void CGlidDialog::DrawExecEx()
{
	CAnimationToolApp* pApp = (CAnimationToolApp*)AfxGetApp();				// アプリケーションポインタを取得
	ASSERT_VALID(pApp);														// エラーがないか判定

	int		work;															// カーソル位置一時保存用変数

	work = pApp->GlidDialog.m_List_Cash.GetCurSel();						// カーソル位置保存
	
	if(work != 0){															// やってから、何ですが0番目じゃないよね
		pApp->start.x = pApp->cash_data[work - 1].left;						// そうじゃないなら
		pApp->start.y = pApp->cash_data[work - 1].top;						// カーソルを
		pApp->end.x = pApp->cash_data[work - 1].right;						// 表示するために
		pApp->end.y = pApp->cash_data[work - 1].bottom;						// 保存してある領域から再設定

		pApp->Dx.workbord.texRect.top = pApp->cash_data[work - 1].top;		// 絵の参照位置も再設定
		pApp->Dx.workbord.texRect.left = pApp->cash_data[work - 1].left -128;
		pApp->Dx.workbord.texRect.bottom = pApp->cash_data[work - 1].bottom;
		pApp->Dx.workbord.texRect.right = pApp->cash_data[work - 1].right -128;
		pApp->DrawExecEx();													// で、描画するために仮想BITMAPに描画
	}
	Invalidate(false);
}
