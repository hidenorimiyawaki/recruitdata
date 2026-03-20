// testView.h : CtestView クラスのインターフェイス
//


#pragma once


class CtestView : public CView
{
protected: // シリアル化からのみ作成します。
	CtestView();
	DECLARE_DYNCREATE(CtestView)

// 属性
public:
	CtestDoc* GetDocument() const;

// 操作
public:

// オーバーライド
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CtestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // testView.cpp のデバッグ バージョン
inline CtestDoc* CtestView::GetDocument() const
   { return reinterpret_cast<CtestDoc*>(m_pDocument); }
#endif

