
// FCMAppDlg.h : header file
//

#pragma once
#include "Memory.h"
#include "Calculate.h"

// CFCMAppDlg dialog
class CFCMAppDlg : public CDialogEx
{
// Construction
public:
	CFCMAppDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FCMAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CEdit edit_cluster;
	CButton button_;
	CStatic static_dunn;
	int m, c;
	int d = 4;
	int n = 150;
	Memory memory;
	Calculate calculate;
	float** X;
	float** U;
	float** C;
	CString Str1,Str2,Str3;
public:
	afx_msg void OnBnClickedButton();
protected:
	CListCtrl m_listCtrl;
public:
	afx_msg void OnEnChangeEditCluster();
	afx_msg void OnBnClickedButtonLoad();
	CListCtrl m_listCtrl_2;
	CStatic static_pbm;
	CComboBox combo_data;
};
