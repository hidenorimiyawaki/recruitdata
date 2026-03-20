// Zintai.h: CZintai クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZINTAI_H__2515C1FF_83E3_48A3_B481_219FB2AC317B__INCLUDED_)
#define AFX_ZINTAI_H__2515C1FF_83E3_48A3_B481_219FB2AC317B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CZintai  
{
public:
	void ResetData();
	FRAME2 frame[BANK_QTY][FRAME_QTY];
	CParts* parts[PARTS_QTY];
	UINT cur_frame;
	void Draw();
	int cur_parts;
	CZintai();
	virtual ~CZintai();

};

#endif // !defined(AFX_ZINTAI_H__2515C1FF_83E3_48A3_B481_219FB2AC317B__INCLUDED_)
