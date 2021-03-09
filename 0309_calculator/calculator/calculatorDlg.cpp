
// calculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include "afxdialogex.h"

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


// CcalculatorDlg dialog



CcalculatorDlg::CcalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_edit1);
}

BEGIN_MESSAGE_MAP(CcalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CcalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CcalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CcalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CcalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CcalculatorDlg::OnBnClickedButton6)
	ON_EN_CHANGE(IDC_EDIT2, &CcalculatorDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON7, &CcalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CcalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CcalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CcalculatorDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CcalculatorDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CcalculatorDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON14, &CcalculatorDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON13, &CcalculatorDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON15, &CcalculatorDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CcalculatorDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON18, &CcalculatorDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON17, &CcalculatorDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON19, &CcalculatorDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CcalculatorDlg::OnBnClickedButton20)
END_MESSAGE_MAP()


// CcalculatorDlg message handlers

BOOL CcalculatorDlg::OnInitDialog()
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
	SetWindowText(L"Calculator, designer: ching-yu");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcalculatorDlg::OnPaint()
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
HCURSOR CcalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CcalculatorDlg::Add(int a, int b) {
	return (a + b);
}

int CcalculatorDlg::Sub(int a, int b) {
	return (a - b);
}

void CcalculatorDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
void CcalculatorDlg::OnBnClickedButton14() // 0
{
	// varible/windows data exchange
	UpdateData(1);
	m_edit1 += "0";
	UpdateData(0);
}
void CcalculatorDlg::OnBnClickedButton1()
{	UpdateData(1); m_edit1 += "1"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton2()
{ 	UpdateData(1); m_edit1 += "2"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton3()
{	UpdateData(1); m_edit1 += "3"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton4()
{	UpdateData(1); m_edit1 += "4"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton5()
{	UpdateData(1); m_edit1 += "5"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton6()
{	UpdateData(1); m_edit1 += "6"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton7()
{	UpdateData(1); m_edit1 += "7"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton8()
{	UpdateData(1); m_edit1 += "8"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton9() // +
{	UpdateData(1); m_edit1 += "+"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton10() // -
{	UpdateData(1); m_edit1 += "-"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton11() // *
{	UpdateData(1); m_edit1 += "*"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton12() // /
{	UpdateData(1); m_edit1 += "/"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton15() // C
{	UpdateData(1); m_edit1 = ""; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton16() // %
{	UpdateData(1); m_edit1 += "%"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton17() // (
{	UpdateData(1); m_edit1 += "("; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton18() // )
{	UpdateData(1); m_edit1 += ")"; UpdateData(0);	}
void CcalculatorDlg::OnBnClickedButton19() // .
{	UpdateData(1); m_edit1 += "."; UpdateData(0);	}

void CcalculatorDlg::OnBnClickedButton20() // backspace
{
	UpdateData(1);
	int i = m_edit1.GetLength();
	m_edit1.SetAt(i - 1, 0x0000);
	UpdateData(0);
}

void CcalculatorDlg::OnBnClickedButton13() // =
{
	// TODO: Add your control notification handler code here
}
