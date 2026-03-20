#if !defined(AFX_ATTRDATA_H__F0DC809B_CA20_4933_88CA_D3270C002B95__INCLUDED_)
#define AFX_ATTRDATA_H__F0DC809B_CA20_4933_88CA_D3270C002B95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttrData.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAttrData ウィンドウ

class CAttrData : public CWnd
{
// コンストラクション
public:
	CAttrData();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAttrData)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	UINT GetAttrDatta(int x, int y);
	void SetAttrData(int x, int y, int pat);
	UINT AttrData;
	virtual ~CAttrData();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAttrData)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ATTRDATA_H__F0DC809B_CA20_4933_88CA_D3270C002B95__INCLUDED_)
