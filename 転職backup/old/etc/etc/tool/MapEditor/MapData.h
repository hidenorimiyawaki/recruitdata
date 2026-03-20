#if !defined(AFX_MAPDATA_H__C217DB84_86E2_455B_B505_905B275B3F1D__INCLUDED_)
#define AFX_MAPDATA_H__C217DB84_86E2_455B_B505_905B275B3F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapData.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMapData ウィンドウ

class CMapData : public CWnd
{
// コンストラクション
public:
	CMapData();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CMapData)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	UINT Palette;
	UINT	GetMapData(int x,int y);
	BOOL	MapData;
	void	SetMapData(int x , int y , int pat);
	virtual ~CMapData();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMapData)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAPDATA_H__C217DB84_86E2_455B_B505_905B275B3F1D__INCLUDED_)
