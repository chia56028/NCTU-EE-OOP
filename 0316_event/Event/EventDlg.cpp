
// EventDlg.cpp: 實作檔案
//事件(Event) practice: Timer, Mouse, (keyboard, Networks, sound recording, windows...)
#include "pch.h"
#include "framework.h"
#include "Event.h"
#include "EventDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CEventDlg 對話方塊



CEventDlg::CEventDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EVENT_DIALOG, pParent)
	, m_Edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
}

BEGIN_MESSAGE_MAP(CEventDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEventDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, &CEventDlg::OnEnChangeEdit1)
	ON_WM_MOUSEMOVE()
//	ON_WM_MOUSELEAVE()
ON_WM_MENUSELECT()
//ON_WM_LBUTTONDOWN()
//ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CEventDlg 訊息處理常式

BOOL CEventDlg::OnInitDialog()
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

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CEventDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEventDlg::OnPaint()
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
HCURSOR CEventDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEventDlg::OnBnClickedButton1()
{
	//Start Timer, show the newest time per second
	SetTimer(123, 1000, 0);  //Timer representing code = 123, generate one event per second (1000ms)
	SetTimer(1234, 500, 0);
	
}

int Cur = 0;
void CEventDlg::OnTimer(UINT_PTR nIDEvent)  //處理timer副程式
{
	// 0. Declare Variables
	CTime t;   //MFC中處理時間之類別(class)
	char S1[100];  //1 byte char
	wchar_t S2[100]; //2 bytes char
	int y, m1, d, h, m, s;

	// 1. Display the time per second
	if (nIDEvent == 123) {
		t = CTime::GetCurrentTime(); //取得目前時間
		h = t.GetHour();		     //取得時
		m = t.GetMinute();			 //取得分
		s = t.GetSecond();           //取得秒
		sprintf_s(S1, "%2d:%2d:%2d", h, m, s); //製造時間字串
		//for (int i = 0; i <= strlen(S1); i++) S2[i] = (wchar_t)S1[i];
		//SetWindowText(S2);        //顯示
		UpdateData(1);
		m_Edit1 = S1;
		UpdateData(0);

	}

	// 2. 跑馬燈
	if (nIDEvent == 1234) {
		strcpy_s(S1, sizeof(S1), "NCTU");
		for (int i = 0; i <= strlen(S1); i++) S2[i] = (wchar_t)S1[i];
		SetWindowText(&S2[Cur]);
		Cur++;
		if (Cur >= strlen(S1)) Cur = 0;
	}
	

	CDialogEx::OnTimer(nIDEvent);
}


void CEventDlg::OnEnChangeEdit1()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
}


void CEventDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	char S1[100];
	wchar_t S2[100];

	sprintf_s(S1, "Mouse Move: (%d, %d)", point.x, point.y);
	for (int i = 0; i <= strlen(S1); i++) S2[i] = (wchar_t)S1[i];
	SetWindowText(S2);
	

	CDialogEx::OnMouseMove(nFlags, point);
}

void CEventDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	CDialogEx::OnMenuSelect(nItemID, nFlags, hSysMenu);

	// TODO: 在此加入您的訊息處理常式程式碼
}

void CEventDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	SetWindowText(L"Click mouse");
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CEventDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	SetWindowText(L"Leave mouse");
	CDialogEx::OnLButtonUp(nFlags, point);
}


//void CEventDlg::OnMouseLeave()
//{
//	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
//
//	CDialogEx::OnMouseLeave();
//}



//void CEventDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}


//void CEventDlg::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
//
//	CDialogEx::OnLButtonUp(nFlags, point);
//}