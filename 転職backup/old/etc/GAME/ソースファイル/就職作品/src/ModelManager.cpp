#include "main.h"

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

bool CModelManager::SetupModels(LPDIRECT3DDEVICE8 p_Device,XFILEINFO* xfileinfo)
{
	for(int i = 0; i < MODEL_QTY; i++) {
		if(!model[i]->LoadData(p_Device,xfileinfo)) return false;
	}
	return true;
}
