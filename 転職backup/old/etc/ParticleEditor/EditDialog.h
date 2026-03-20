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
	CSliderCtrl m_Edit_Slider_Num;
	CSliderCtrl m_Edit_Slider_Size;
	CSliderCtrl m_Edit_Slider_Time;
	CSliderCtrl m_Edit_Slider_Pos_X;
	CSliderCtrl m_Edit_Slider_Pos_Y;
	CSliderCtrl m_Edit_Slider_Pos_Z;
	CSliderCtrl m_Edit_Slider_Dir_X;
	CSliderCtrl m_Edit_Slider_Dir_Y;
	CSliderCtrl m_Edit_Slider_Dir_Z;
	CSliderCtrl m_Edit_Slider_Gravity;
	CSliderCtrl m_Edit_Slider_Range_X;
	CSliderCtrl m_Edit_Slider_Range_Y;
	CSliderCtrl m_Edit_Slider_Range_Z;
	CSliderCtrl m_Edit_Slider_Speed;
	int m_Edit_Num;
	int m_Edit_Time;
	float m_Edit_Scale;
	float m_Edit_Pos_X;
	float m_Edit_Pos_Y;
	float m_Edit_Pos_Z;
	float m_Edit_Dir_X;
	float m_Edit_Dir_Y;
	float m_Edit_Dir_Z;
	float m_Edit_Gravity;
	float m_Edit_Range_X;
	float m_Edit_Range_Y;
	float m_Edit_Range_Z;
	float m_Edit_Speed;
	CButton m_Check_Side_X;
	CButton m_Check_Side_Y;
	CButton m_Check_Side_Z;
	CButton m_Check_Add_Alpha;
	CButton m_Check_Alpha;
	CButton m_Check_Time;
	CButton m_Check_Size;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnBnClickedRadioPos();
	afx_msg void OnBnClickedRadioRot();
	afx_msg void OnBnClickedRadioScale();
	afx_msg void OnBnClickedCheckSideX();
	afx_msg void OnBnClickedCheckSideY();
	afx_msg void OnBnClickedCheckSideZ();
	afx_msg void OnBnClickedCheckTime();
	afx_msg void OnBnClickedCheckSize();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic m_Static_Dir_X;
	CStatic m_Static_Dir_Y;
	CStatic m_Static_Dir_Z;
	CStatic m_Static_Speed;
	CStatic m_Static_Gravity;
	void ReStart(void);
	CButton m_Check_Time_Alpha;
};
