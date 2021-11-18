
// FCMAppDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FCMApp.h"
#include "FCMAppDlg.h"
#include "afxdialogex.h"
#include <iostream> 
#include <math.h>
#include <fstream>
#include "Memory.h"
#include "Calculate.h"
#include "stdlib.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFCMAppDlg dialog



CFCMAppDlg::CFCMAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FCMAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFCMAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CLUSTER, edit_cluster);
	DDX_Control(pDX, IDC_BUTTON, button_);
	DDX_Control(pDX, IDC_STATIC_DUNN, static_dunn);
	DDX_Control(pDX, IDC_LIST_CONTROL, m_listCtrl);
	DDX_Control(pDX, IDC_LIST_CONTROL_2, m_listCtrl_2);
	DDX_Control(pDX, IDC_STATIC_PBM, static_pbm);
	DDX_Control(pDX, IDC_COMBO_DATA, combo_data);
}

BEGIN_MESSAGE_MAP(CFCMAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, &CFCMAppDlg::OnBnClickedButton)
	ON_EN_CHANGE(IDC_EDIT_CLUSTER, &CFCMAppDlg::OnEnChangeEditCluster)
//	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CFCMAppDlg::OnBnClickedButtonLoad)
ON_BN_CLICKED(IDC_BUTTON_LOAD, &CFCMAppDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CFCMAppDlg message handlers

BOOL CFCMAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	combo_data.AddString(_T("Iris"));
	combo_data.AddString(_T("abalone"));
	combo_data.SetCurSel(0);

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
	for (int i = 0; i < d; i++) {
		m_listCtrl.InsertColumn(i, _T(""), LVCFMT_CENTER, 100);
		m_listCtrl_2.InsertColumn(i, _T(""), LVCFMT_CENTER, 100);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFCMAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFCMAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFCMAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFCMAppDlg::OnBnClickedButton()
{
	// d la so chieu
	// n la so diem cua X
	// m la trong so mu
	// c la so cum
	m = 2;
	edit_cluster.GetWindowTextW(Str1);
	c = _ttoi(Str1);


	//	cout << "nhap tham so m";
	//	cin >>m;

	//	cout << "nhap so cum";
	//	cin >>c;

	// tap cac ma tran x
	memory.allocate(X, n + 1, d + 1);
	memory.read(X, n, d);

	// ma tran U
	memory.allocate(U, n + 1, c + 1);

	// tap cac vector cum C  
	memory.allocate(C, c + 1, d + 1);


	//khoi tao ma tran U
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= c; j++)
			U[i][j] = (float)1 / (i + j);

	//khoi tao cac tam C
	for (int i = 1; i <= c; i++)
		for (int j = 1; j <= d; j++)
			C[i][j] = 1;

	// thuat toan fcm
	float JUC = 0;
	float JUCnew = 0;
	do {
		JUC = JUCnew;
		for (int k = 1; k <= c; k++)
			calculate.update_CK(U, X, C, d, m, n, k);

		for (int i = 1; i <= n; i++)
			for (int k = 1; k <= c; k++)
				calculate.update_UIK(U, X, C, d, m, c, i, k);

		JUCnew = calculate.update_JUC(U, X, C, n, c, d, m);

	} while (abs(JUC - JUCnew) > 0);

	float delta_min = 999;
	float delta_max = 0;
	float E1 = 0, EK = 0, DK = 0;

	//ban kinh cac tam cum(thuat toan dunn)
	float* radius;
	radius = new float[c + 1];
	for (int i = 1; i <= c; i++)
		radius[i] = 0;

	//tong khoang cach cac phan tu cua cum do den cum do
	float* E;
	E = new float[c + 1];
	for (int i = 1; i <= c; i++)
		E[i] = 0;

	//tinh ban kinh cac tam cum
	for (int i = 1; i <= n; i++) {
		float clus = 0;
		int ter = 0;
		for (int j = 1; j <= c; j++) {
			if (U[i][j] > clus) {
				clus = U[i][j];
				ter = j;
			}
		}
		// thuat toan dunn
		float radius_ter = calculate.D(X, C, i, ter, d);
		if (radius_ter > radius[ter])
			radius[ter] = radius_ter;

		// thuat toan PBM
		E[ter] += radius_ter;
	}

	//tinh EK
	for (int i = 1; i <= c; i++) {
		EK += E[i];
	}

	//tinh E1
	E1 = E[1];

	//tim ban kinh lon nhat
	for (int i = 1; i <= c; i++) {
		if (delta_max < radius[i])
			delta_max = radius[i];
	}

	//tim khoang cach nho nhat giua 2 tam cum
	for (int i = 1; i < c; i++)
		for (int j = i + 1; j <= c; j++) {
			if (delta_min > calculate.Dcluster(X, C, i, j, d))
				delta_min = calculate.Dcluster(X, C, i, j, d);
			if (DK < calculate.Dcluster(X, C, i, j, d))
				DK = calculate.Dcluster(X, C, i, j, d);
		}
	float dunn = delta_min / delta_max;
	float PBM = (float)(E1 * DK) / EK;
	PBM = (float)PBM / c;
	PBM = pow((float)PBM, 2.0);

	Str2.Format(_T(" %f"), dunn);
	static_dunn.SetWindowTextW(Str2);
	Str3.Format(_T(" %f"), PBM);
	static_pbm.SetWindowTextW(Str3);

	m_listCtrl.DeleteAllItems();
	for(int i=0;i<c;i++)
		for (int j = 0; j < d; j++) {
			CString Str=NULL;
			Str.Format(_T("%f"), C[i + 1][j + 1]);
			if ((j==0))
				m_listCtrl.InsertItem(i, Str);
			else
				m_listCtrl.SetItemText(i, j, Str);
		}
			

	//giai phong bo nho cua cac ma tran
	memory.free(X, n, d);
	memory.free(U, n, c);
	memory.free(C, c, d);

}


void CFCMAppDlg::OnEnChangeEditCluster()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



void CFCMAppDlg::OnBnClickedButtonLoad()
{
	memory.allocate(X, n + 1, d + 1);
	memory.read(X, n, d);
	m_listCtrl_2.DeleteAllItems();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++) {
			CString Str = NULL;
			Str.Format(_T("%f"), X[i + 1][j + 1]);
			if ((j == 0))
				m_listCtrl_2.InsertItem(i, Str);
			else
				m_listCtrl_2.SetItemText(i, j, Str);
		}
	// TODO: Add your control notification handler code here
}
