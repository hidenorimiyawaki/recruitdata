// AnimationToolDoc.h : CAnimationToolDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMATIONTOOLDOC_H__6F6BD4DB_B3A8_4B9D_9DA9_59957EFFC5DA__INCLUDED_)
#define AFX_ANIMATIONTOOLDOC_H__6F6BD4DB_B3A8_4B9D_9DA9_59957EFFC5DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAnimationToolDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CAnimationToolDoc();
	DECLARE_DYNCREATE(CAnimationToolDoc)

// アトリビュート
public:
	CString				mainfile;

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAnimationToolDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CAnimationToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CAnimationToolDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveEx();
	afx_msg void OnFileLoadEx();
	afx_msg void OnGlidTypeOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ANIMATIONTOOLDOC_H__6F6BD4DB_B3A8_4B9D_9DA9_59957EFFC5DA__INCLUDED_)
