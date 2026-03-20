#pragma once


// CChildEdit フレーム 

class CChildEdit : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildEdit)
protected:
	CChildEdit();           // 動的生成で使用される protected コンストラクタ
	virtual ~CChildEdit();

protected:
	DECLARE_MESSAGE_MAP()
};


