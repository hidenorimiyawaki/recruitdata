/************************************************************
*						MACRO.H								*
*															*
*		このファイルでは、マクロの定義をします。			*
*															**															*
************************************************************/
#ifndef	___MACRO_H___
#define	___MACRO_H___

//-------- マクロ
#define SAFE_RELEASE(x)	if(x){ x->Release(); x=NULL; }
#define SAFE_DELETE_ARRAY(x) if( (x) != NULL ){ delete [] (x); (x) = NULL; }
#endif