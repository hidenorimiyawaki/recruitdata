// Model.h: CModel クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_H__14ED5E43_CCD3_415D_B305_706465113C5C__INCLUDED_)
#define AFX_MODEL_H__14ED5E43_CCD3_415D_B305_706465113C5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModel  
{
public:
	int model_index;
	bool LoadData();
	LPDIRECT3DTEXTURE8 texture;
	LPDIRECT3DINDEXBUFFER8 index_buffer;
	LPDIRECT3DVERTEXBUFFER8 vertex_buffer;
	int index_qty;
	int vertex_qty;
	LPD3DXMESH mesh;
	CModel(int index);
	virtual ~CModel();

};

#endif // !defined(AFX_MODEL_H__14ED5E43_CCD3_415D_B305_706465113C5C__INCLUDED_)
