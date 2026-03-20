// MothionEditorDoc.h : CMothionEditorDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOTHIONEDITORDOC_H__1A902FA1_3C01_4AD2_97D5_95EF7A87B7DF__INCLUDED_)
#define AFX_MOTHIONEDITORDOC_H__1A902FA1_3C01_4AD2_97D5_95EF7A87B7DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMothionEditorDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CMothionEditorDoc();
	DECLARE_DYNCREATE(CMothionEditorDoc)

// アトリビュート
public:
	PARTS_ROT_POINT rot_point[PARTS_QTY];
// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMothionEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CMothionEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMothionEditorDoc)
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSaveEx();
	afx_msg void OnFileLoadEx();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MOTHIONEDITORDOC_H__1A902FA1_3C01_4AD2_97D5_95EF7A87B7DF__INCLUDED_)
