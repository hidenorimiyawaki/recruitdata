// VectorSetToolDoc.h : CVectorSetToolDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORSETTOOLDOC_H__A1173D3F_BE80_4EDF_AE85_E0BC8D6194E5__INCLUDED_)
#define AFX_VECTORSETTOOLDOC_H__A1173D3F_BE80_4EDF_AE85_E0BC8D6194E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVectorSetToolDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CVectorSetToolDoc();
	DECLARE_DYNCREATE(CVectorSetToolDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CVectorSetToolDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CVectorSetToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CVectorSetToolDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnIdFileSaveEx();
	afx_msg void OnIdFileLoadEx();
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VECTORSETTOOLDOC_H__A1173D3F_BE80_4EDF_AE85_E0BC8D6194E5__INCLUDED_)
