
// UDP_chatDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "UDP_chat.h"
#include "UDP_chatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SEVENT (WM_USER+100) // Server Event
#define CEVENT (WM_USER+200) // Client Event
#include "tcpip_async.cpp"

SOCKET      SSock, CSock;    // Internet Connection Code
sockaddr_in CAddr;           // Save Remote Info (IP+Port)

char IP[100] = { "192.168.13.255" }; //x.x.x.255 for broadcast


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CUDPchatDlg 對話方塊



CUDPchatDlg::CUDPchatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UDP_CHAT_DIALOG, pParent)
	, m_Edit1(_T(""))
	, m_Edit2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPchatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit11);
}

BEGIN_MESSAGE_MAP(CUDPchatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUDPchatDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CUDPchatDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CUDPchatDlg 訊息處理常式

BOOL CUDPchatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	// Set up UDP Client (Receive Message)
	Start_UDP_Server(&SSock, 6000, SEVENT, m_hWnd);

	// Set up UDP Server (Send Message)
	Start_UDP_Client(&CSock, &CAddr, 6000, IP, CEVENT, m_hWnd);

	UpdateData(1);
	m_Edit1 = L"Successfully start UDP";
	UpdateData(0);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CUDPchatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CUDPchatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CUDPchatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Client send the string in the windows to Server
void CUDPchatDlg::OnBnClickedButton1()
{
	// 1. Declare variables
	int i, Len = sizeof(sockaddr);
	char S1[2000] = { "Hello World" };
	wchar_t *S11;

	// 2. Capture string
	UpdateData(1);
	S11 = (wchar_t *)m_Edit2.GetBuffer();
	UpdateData(0);

	// 3. Data transform
	UniCodeToBig5(S11, S1, sizeof(S1)-2); // bug here

	// 4. Client send datas to Server
	sendto(CSock, S1, strlen(S1), 0, (sockaddr *)&CAddr, Len);

	
}


void CUDPchatDlg::OnEnChangeEdit1()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
}


LRESULT CUDPchatDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	int i, len=sizeof(sockaddr);
	char S1[2000], S2[2000]; // One-Byte Character
	wchar_t S11[200];        // Two-Bytes UninCode String
	sockaddr Addr;
	sockaddr_in Addr1;

	// UDP Server: Receive Message from Client 
	if (message == SEVENT) {
		i = recvfrom(wParam, S1, sizeof(S1) - 1, 0, (sockaddr *)&Addr1, &len);
		if (i > 0) {
			// end of string
			S1[i] = 0;

			sprintf_s(S2, sizeof(S2) - 1, "(%d,%d,%d,%d) say: %s\r\n",
				(Addr1.sin_addr.s_addr >> 0) & 0xFF,
				(Addr1.sin_addr.s_addr >> 8) & 0xFF,
				(Addr1.sin_addr.s_addr >> 16) & 0xFF,
				(Addr1.sin_addr.s_addr >> 24) & 0xFF,
				S1, sizeof(S1)-1);

			// transform
			Big5ToUniCode(S2, S11, strlen(S2)+1);

			// display string
			UpdateData(1);
			m_Edit1 += S11;
			m_Edit1 += L"\r\n";
			UpdateData(0);

			// auto scroll
			m_Edit11.LineScroll(m_Edit11.GetLineCount());
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
