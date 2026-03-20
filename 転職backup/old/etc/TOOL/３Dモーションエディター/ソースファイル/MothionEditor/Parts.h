// Parts.h: CParts クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTS_H__DC7CA262_4259_45A6_9E21_883E8B0C06F4__INCLUDED_)
#define AFX_PARTS_H__DC7CA262_4259_45A6_9E21_883E8B0C06F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParts  
{
public:
	void SetInitialData(int index);
	PARTS_ROT_POINT rot_point[BANK_QTY][FRAME_QTY];
	void Exec();
	void SetMatrix();
	void Draw(bool current);
	D3DXMATRIX matrix;
	int parent;
	int model;
	CParts(int index);
	virtual ~CParts();

};

#endif // !defined(AFX_PARTS_H__DC7CA262_4259_45A6_9E21_883E8B0C06F4__INCLUDED_)
