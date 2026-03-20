// ModelManager.cpp: CModelManager クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MothionEditor.h"
#include "ModelManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CModelManager::CModelManager()
{
	for(int i = 0; i < MODEL_QTY; i++) {
		model[i] = new CModel(i);
	}
}

CModelManager::~CModelManager()
{
	for(int i = 0; i < MODEL_QTY; i++) {
		delete model[i];
	}
}

bool CModelManager::SetupModels()
{
	for(int i = 0; i < MODEL_QTY; i++) {
		if(!model[i]->LoadData()) return false;
	}
	return true;
}
