// particleediterDoc.h : CparticleediterDoc クラスのインターフェイス
//


#pragma once

class CparticleediterDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CparticleediterDoc();
	DECLARE_DYNCREATE(CparticleediterDoc)

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
	virtual ~CparticleediterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};


