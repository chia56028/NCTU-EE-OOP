
// BMPDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BMP.h"
#include "BMPDlg.h"
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


// CBMPDlg dialog



CBMPDlg::CBMPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BMP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBMPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBMPDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBMPDlg message handlers

BOOL CBMPDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBMPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBMPDlg::OnPaint()
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
HCURSOR CBMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBMPDlg::OnBnClickedButton1()
{
	// 1. open *.BMP file
	errno_t err;
	FILE *In;
	err = fopen_s(&In, "hero.bmp", "rb");
	if (err != 0) {
		SetWindowText(L"File hero.bmp not found");
		return;
	}
	else {
		SetWindowText(L"File opened successfully");
	}

	// 2. read infomation of width, height
	int Width, Height;
	// BMP header has 54 bytes (14 for file header; 40 for information header)
	unsigned char UCBuf[54];
	fread(UCBuf, 1, 54, In);
	Width = ((int)UCBuf[18] << 0)+ ((int)UCBuf[19] << 8)+ ((int)UCBuf[20] << 16)+ ((int)UCBuf[21] << 24);
	Height = ((int)UCBuf[22] << 0) + ((int)UCBuf[23] << 8) + ((int)UCBuf[24] << 16) + ((int)UCBuf[25] << 24);

	// 3. draw picture
	HDC hdc = ::GetDC(m_hWnd);
	int x, y, z;
	// width * 3 channel
	z = (4 - ((Width * 3) % 4)) % 4;
	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			fread(UCBuf, 1, 3, In);
			// change color: red(2) => green(1)
			if ((UCBuf[0] < 128) && (UCBuf[1] < 128) && (UCBuf[2] > 128)) {
				// UCBuf[3] is tmp
				UCBuf[3] = UCBuf[1];
				UCBuf[1] = UCBuf[2];
				UCBuf[2] = UCBuf[3];
			}
			// set color
			CPen P(PS_SOLID, 1, RGB(UCBuf[2], UCBuf[1], UCBuf[0]));
			SelectObject(hdc, P);
			// draw a point
			MoveToEx(hdc, x, Height - y, 0);
			LineTo(hdc, x + 1, Height - y);
		}
		fread(UCBuf, 1, z, In);
	}



}
