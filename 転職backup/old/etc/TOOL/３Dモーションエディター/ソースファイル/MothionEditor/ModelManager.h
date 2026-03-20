// ModelManager.h: CModelManager クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELMANAGER_H__8A82E9B8_EFE2_48B1_B505_403D7F4AA060__INCLUDED_)
#define AFX_MODELMANAGER_H__8A82E9B8_EFE2_48B1_B505_403D7F4AA060__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModelManager  
{
public:
	CModel* model[MODEL_QTY];
	bool SetupModels();
	CModelManager();
	virtual ~CModelManager();

};

#endif // !defined(AFX_MODELMANAGER_H__8A82E9B8_EFE2_48B1_B505_403D7F4AA060__INCLUDED_)
