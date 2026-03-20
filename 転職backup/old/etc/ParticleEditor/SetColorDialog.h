#include "afxcmn.h"
#pragma once


// CSetColorDialog ダイアログ

class CSetColorDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetColorDialog)

public:
	CSetColorDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSetColorDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Slider_Color_R;
	CSliderCtrl m_Slider_Color_G;
	CSliderCtrl m_Slider_Color_B;
	int color_r;
	int color_g;
	int color_b;
	afx_msg void OnBnClickedButtonDefault();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};
