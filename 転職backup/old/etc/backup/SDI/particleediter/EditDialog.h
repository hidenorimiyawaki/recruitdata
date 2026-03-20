#include "afxcmn.h"
#include "afxwin.h"
#pragma once


// CEditDialog ダイアログ

class CEditDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditDialog)

public:
	CEditDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CEditDialog();

// ダイアログ データ
	enum { IDD = IDD_EDIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CSliderCtrl m_Edit_Slider_Num;
	virtual BOOL OnInitDialog();
	int m_Edit_Num;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_Edit_Scale;
	CSliderCtrl m_Edit_Slider_Size;
	int m_Edit_Pos_X;
	int m_Edit_Pos_Y;
	int m_Edit_Pos_Z;
	CSliderCtrl m_Edit_Slider_Pos_X;
	CSliderCtrl m_Edit_Slider_Pos_Y;
	CSliderCtrl m_Edit_Slider_Pos_Z;
	int m_Edit_Time;
	CSliderCtrl m_Edit_Slider_Time;
	int m_Edit_Dir_X;
	int m_Edit_Dir_Y;
	int m_Edit_Dir_Z;
	int m_Edit_Gravity;
	CSliderCtrl m_Edit_Slider_Dir_X;
	CSliderCtrl m_Edit_Slider_Dir_Y;
	CSliderCtrl m_Edit_Slider_Dir_Z;
	CSliderCtrl m_Edit_Slider_Gravity;
};
