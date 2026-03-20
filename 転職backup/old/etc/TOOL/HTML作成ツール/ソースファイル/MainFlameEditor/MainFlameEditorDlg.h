// MainFlameEditorDlg.h : ヘッダー ファイル
//

#if !defined(AFX_MAINFLAMEEDITORDLG_H__812CDD35_8D55_4F2E_8CAF_C3EDA9F90600__INCLUDED_)
#define AFX_MAINFLAMEEDITORDLG_H__812CDD35_8D55_4F2E_8CAF_C3EDA9F90600__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct{
	CString	ImageName;
	int		ImageHabaV;
	int		ImageHabaH;
}HTMLPAGEDATA;

/////////////////////////////////////////////////////////////////////////////
// CMainFlameEditorDlg ダイアログ

class CMainFlameEditorDlg : public CDialog
{
// 構築
public:
	CMainFlameEditorDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	HTMLPAGEDATA  HomePageData[3][5];
// ダイアログ データ
	//{{AFX_DATA(CMainFlameEditorDlg)
	enum { IDD = IDD_MAINFLAMEEDITOR_DIALOG };
	CSliderCtrl	m_SliderV3;
	CSliderCtrl	m_SliderV2;
	CSliderCtrl	m_SliderV1;
	CSliderCtrl	m_SliderH5;
	CSliderCtrl	m_SliderH4;
	CSliderCtrl	m_SliderH3;
	CSliderCtrl	m_SliderH2;
	CSliderCtrl	m_SliderH1;
	CComboBox	m_ComboVNo;
	CString	m_EditFileName1;
	CString	m_EditFileName2;
	CString	m_EditFileName3;
	CString	m_EditFileName4;
	CString	m_EditFileName5;
	int		m_EditV1;
	int		m_EditV2;
	int		m_EditV3;
	int		m_EditX1;
	int		m_EditX2;
	int		m_EditX3;
	int		m_EditX4;
	int		m_EditX5;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMainFlameEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMainFlameEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonsave();
	afx_msg void OnButtonload();
	afx_msg void OnButtonbrows1();
	afx_msg void OnButtonbrows2();
	afx_msg void OnButtonbrows3();
	afx_msg void OnButtonbrows4();
	afx_msg void OnButtonbrows5();
	afx_msg void OnSelchangeComboVno();
	afx_msg void OnReleasedcaptureSliderv1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderv2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderv3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderh1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderh2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderh3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderh4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderh5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditFilename1();
	afx_msg void OnKillfocusEditFilename2();
	afx_msg void OnKillfocusEditFilename3();
	afx_msg void OnKillfocusEditFilename4();
	afx_msg void OnKillfocusEditFilename5();
	afx_msg void OnKillfocusEditv1();
	afx_msg void OnKillfocusEditv2();
	afx_msg void OnKillfocusEditv3();
	afx_msg void OnKillfocusEditx1();
	afx_msg void OnKillfocusEditx2();
	afx_msg void OnKillfocusEditx3();
	afx_msg void OnKillfocusEditx4();
	afx_msg void OnKillfocusEditx5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAINFLAMEEDITORDLG_H__812CDD35_8D55_4F2E_8CAF_C3EDA9F90600__INCLUDED_)
