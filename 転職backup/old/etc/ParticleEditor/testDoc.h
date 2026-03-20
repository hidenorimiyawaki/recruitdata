// testDoc.h : CtestDoc クラスのインターフェイス
//


#pragma once

class CtestDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CtestDoc();
	DECLARE_DYNCREATE(CtestDoc)

// 属性
public:

// 操作
public:

// オーバーライド
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 実装
public:
	virtual ~CtestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTexOpen2();
	afx_msg void OnTexOpen1();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileClose();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};


