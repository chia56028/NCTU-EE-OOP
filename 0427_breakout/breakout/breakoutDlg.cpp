
// breakoutDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "breakout.h"
#include "breakoutDlg.h"
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


// CbreakoutDlg 對話方塊



CbreakoutDlg::CbreakoutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BREAKOUT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbreakoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CbreakoutDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CbreakoutDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CbreakoutDlg 訊息處理常式

BOOL CbreakoutDlg::OnInitDialog()
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

void CbreakoutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CbreakoutDlg::OnPaint()
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
HCURSOR CbreakoutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 遊戲平台規格
#define W 630
#define H 700

HDC hdc; // 繪圖用
int px, py, pw, ph, pF; // 接球平台參數
int cx, cy, r, dx, dy;	// 球座標

// 繪出球
void Ball(HDC hdc, int cx, int cy, int r, int C) {
	
	// 1. 設定顏色
	CPen P1(PS_SOLID, 1, RGB((C >> 16) & 0xFF, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P1);

	// 2. 繪球
	int x, y;
	// MoveToEx(hdc, cx + r, cy, 0);
	for (int i = 0; i <= 360; i++) {
		x = cx + (int)((double)r * cos(6.28318*i / 360));
		y = cy + (int)((double)r * sin(6.28318*i / 360));
		MoveToEx(hdc, cx, cy, 0);
		LineTo(hdc, x, y);
	}
}


// 矩形繪圖副程式
// hdc: 繪圖用
//  (x1, y1) 矩形左上座標
//  (x2, y2) 矩形右上座標
// C: RGB color
// F: 空心或實心

void Rect(HDC hdc, int x1, int y1, int x2, int y2, int C, int F) {
	int y, z;
	// 1. color setting
	CPen P1(PS_SOLID, 1, RGB((C >> 16) & 0xFF, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P1);
	// 2. check y1, y2 順序
	if (y1 > y2) {
		// 交換座標
		z = y1;  y1 = y2;  y2 = z;
		z = x1;  x1 = x2;  x2 = z;
	}
	// 3.1 繪矩形框
	if (!F) {
		MoveToEx(hdc, x1, y1, 0);
		LineTo(hdc, x2, y1);
		LineTo(hdc, x2, y2);
		LineTo(hdc, x1, y2);
		LineTo(hdc, x1, y1);
	}
	// 3.2 繪矩形磚
	else {
		for (y = y1; y <= y2; y++) {
			MoveToEx(hdc, x1, y, 0);
			LineTo(hdc, x2, y);
		}
	}
}

void CbreakoutDlg::OnBnClickedButton1()  //啟動遊戲
{
	hdc = ::GetDC(m_hWnd);
	
	// 1.繪出遊戲框
	Rect(hdc, 0, 0, W, H, 0xFF, 0);//藍色實心矩形

	// 2. 繪出接球平台(隨著滑鼠移動)
	// px=平台左邊x座標, py=平台左邊y座標
	// pw=平台寬度, ph=平台厚度
	// pF=紀錄滑鼠按下狀態
	//接球平台參數
	ph = 15;  px = W / 2 - pw / 2; py = H - ph - 5; pw = 80; pF = 0;
	Rect(hdc, px, py, px+pw, py + ph, 0xFF0000, 1);

	// 3. 繪出球(會隨時間移動)
	// (cx, cy): 球心座標
	// r: 球半徑
	// (dx, dy): 球移動向量
	cx = W / 2; cy = H / 2; r = 10; dx = 5; dy = -11;
	Ball(hdc, cx, cy, r, 0xFF00FF);
	SetTimer(123, 20, 0); // 每100ms呼叫Timer移動球
	
}


void CbreakoutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{	pF = 1; // 滑鼠左鍵按下
	CDialogEx::OnLButtonDown(nFlags, point); }

void CbreakoutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{   pF = 0; // 滑鼠左鍵放開
	CDialogEx::OnLButtonUp(nFlags, point); }

void CbreakoutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((pF) )//&& (point.y>=py) && (point.y<=(py+ph)))
	{	
		// 在滑鼠按下的情況下處理
		// 1. 塗銷舊接球平台
		Rect(hdc, px, py, px + pw, py + ph, 0xF0F0F0, 1);
		// 2. 設定新的接球平台座標，並檢查邊界
		px = point.x - pw / 2;
		if (px < 2)
			px = 2;
		else if ((px + pw) > (W - 2))
			px = W - 2 - pw;

		// 3. 繪出新的接球平台
		Rect(hdc, px, py, px + pw, py + ph, 0xFF0000, 1);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CbreakoutDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 123) {
		// 1.塗銷舊球
		Ball(hdc, cx, cy, r, 0xF0F0F0);
		// 2.改變球新座標，檢查邊界
		cx += dx; cy += dy;
		if ((cx - r) < 2) {
			cx = r + 2;
			dx *= -1;
		}
		else if ((cx + r) > (W - 1)) {
			cx = W - 1 - r;
			dx *= -1;
		}
			
		if ((cy - r) < 2) {
			cy = r + 2;
			dy *= -1;
		}
			
		else if ((cy + r) > (H - 1)) {
			cy = H - 1 - r;
			dy *= -1;
		}
			
		// 3.繪出新球
		Ball(hdc, cx, cy, r, 0xFF00FF);
	}

	CDialogEx::OnTimer(nIDEvent);
}
