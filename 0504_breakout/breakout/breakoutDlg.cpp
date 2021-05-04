
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
#define N 1   // number of ball
#define W1 10 // number of bricks on the horizontal plane
#define H1 6  // number of bricks on the vertical plane

/* parameters of bricks */
// 0-1 coordinate (left, up)
// 2-3 coordinate (right, down)
// 4   RGB color of brick
// 5   state of brick 
//  - 0: not exist
//  - 1: exist, hit 1->0
//  - 2/3: fall down, 2->3->0 (color won't change)
//  - 4/5: fall down, 4->5->0 (twinkle)
//  - 6/7: stone, hit 6->7->0
int T_bricks[H1][W1][6];

HDC hdc; // 繪圖用
int px, py, pw, ph, pF; // 接球平台參數
int cx[N], cy[N], cs[N], cc[N], r[N], dx[N], dy[N];	// 球座標

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

	// 1.5. initialize parameters of bricks && draw bricks
	for (int y = 0; y < H1; y++) {
		for (int x = 0; x < W1; x++) {
			int *brick = T_bricks[y][x];
			*(brick + 0) = 5 + x*(W/W1);           // x-coordinate of top left
			*(brick + 1) = 5 + 40*y;               // y-coordinate of top left
			*(brick + 2) = 5 + (x+1)*(W/W1) - 10;  // x-coordinate of bottom right
			*(brick + 3) = 5 + 40*(y+1) - 10;      // y-coordinate of bottom right
			*(brick + 4) = rand()+ (rand()<<16);   // RGB color
			*(brick + 5) = rand()%2;               // state
		}
	}
	for (int y = 0; y < H1; y++) {
		for (int x = 0; x < W1; x++) {
			int *brick = T_bricks[y][x];
			if (*(brick + 5) != 0) {
				Rect(hdc, *(brick + 0), *(brick + 1), *(brick + 2), *(brick + 3), *(brick + 4), 1);
			}
			else {
				Rect(hdc, *(brick + 0), *(brick + 1), *(brick + 2), *(brick + 3), 0xF0F0F0, 1);
			}
		}
	}

	// 2. 繪出接球平台(隨著滑鼠移動)
	// px=平台左邊x座標, py=平台左邊y座標
	// pw=平台寬度, ph=平台厚度
	// pF=紀錄滑鼠按下狀態
	// 接球平台參數
	ph = 15;  px = W / 2 - pw / 2; py = H - ph - 5; pw = 80; pF = 0;
	Rect(hdc, px, py, px+pw, py + ph, 0xFF0000, 1);

	// 3. 繪出球(會隨時間移動)
	// param (cx, cy): 球心座標
	// param r: 球半徑
	// param (dx, dy): 球移動向量
	// param cs: status of ball (0: gameover, 1: playing)
	// param cc: color of ball
	for (int i = 0; i < N; i++) {
		cx[i] = W / 2;
		cy[i] = H / 2;
		r[i] = 10+(rand()%10);
		dx[i] = 3+(rand()%7);
		dy[i] = -7-(rand()%9);
		cs[i] = 1;
		cc[i] = rand()+(rand()<<16);
		Ball(hdc, cx[i], cy[i], r[i], cc[i]);
	}

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

// check if ith ball (cx[i], cy[i], r[i]) hits the brick
void Check(int i) {
	for (int y = 0; y < H1; y++) {
		for (int x = 0; x < W1; x++) {
			int *b = T_bricks[y][x];
			if (*(b + 5) != 0) {
				if (
					// hit bottom
					((cy[i] - r[i] < *(b + 3)) && (cy[i] - r[i] > *(b + 1)) &&
					(cx[i] + r[i] > *(b + 0)) && (cx[i] - r[i] < *(b + 2))) ||
					// hit top
					((cy[i] + r[i] > *(b + 3)) && (cy[i] + r[i] < *(b + 1)) &&
					(cx[i] + r[i] > *(b + 0)) && (cx[i] - r[i] < *(b + 2)))
					) 
				{
					// 1. brick disappear
					*(b + 5) = 0;
					Rect(hdc, *(b + 0), *(b + 1), *(b + 2), *(b + 3), 0xF0F0F0, 1);

					// 2. ball flip
					dy[i] = 0 - dy[i];
				}else if (
					// hit left
					((cy[i] - r[i] < *(b + 3)) && (cy[i] - r[i] > *(b + 1)) &&
					(cx[i] + r[i] > *(b + 0)) && (cx[i] + r[i] < *(b + 2))) ||
					// hit right
					((cy[i] - r[i] < *(b + 3)) && (cy[i] - r[i] > *(b + 1)) &&
					(cx[i] - r[i] > *(b + 0)) && (cx[i] - r[i] < *(b + 2)))
					)
				{
					// 1. brick disappear
					*(b + 5) = 0;
					Rect(hdc, *(b + 0), *(b + 1), *(b + 2), *(b + 3), 0xF0F0F0, 1);

					// 2. ball flip
					dx[i] = 0 - dx[i];
				}

			}
		}
	}
}

// handle movement of ball
// For PlaySound() we need to include:
#include "mmsystem.h"
#pragma comment (lib, "winmm.lib")
void CbreakoutDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 123) {
		for (int i = 0; i < N; i++) {
			if (cs[i]==1) {
				// 1.塗銷舊球
				Ball(hdc, cx[i], cy[i], r[i], 0xF0F0F0);

				// 2.改變球新座標，檢查邊界
				cx[i] += dx[i]; cy[i] += dy[i];
				if ((cx[i] - r[i]) < 2) {
					cx[i] = r[i] + 2;
					dx[i] *= -1;
				}
				else if ((cx[i] + r[i]) > (W - 1)) {
					cx[i] = W - 1 - r[i];
					dx[i] *= -1;
				}

				if ((cy[i] - r[i]) < 2) {
					cy[i] = r[i] + 2;
					dy[i] *= -1;
				}

				else if ((cy[i] + r[i]) > (H - 1)) {
					cy[i] = H - 1 - r[i];
					dy[i] *= -1;
				}

				// 2.2. check if ith ball hits the brick
				// param i: number of ball
				Check(i);
			

				// 2.3. auto play (send mouse events)
				if (cy[i] + r[i] >= py-80) {
					CPoint P;
					P.x = cx[i]; // send x-asix of ball to mouse and make mouse move
					pF = 1;      // click mouse
					OnMouseMove(0, P);
				}
				


				// 2.5. check (1)if ball touch the button (2)if platform couch the ball
				if ((cy[i] + r[i]) >= py) { // buttom of ball touch upper edge of platform 
					if ((cx[i] < px) || (cx[i] > (px + pw))) { // ball falls outside the platform
						KillTimer(123); // ball stops moving
						Ball(hdc, cx[i], py + ph - r[i], r[i], cc[i]);
						SetWindowText(L"Didn't catch the ball");
						PlaySound(L"abc.wav", 0, SND_ASYNC);
					}
					else { // while catch the ball
						cy[i] = cy[i] - r[i] - 1;
						dy[i] *= -1;
						PlaySound(L"cammra.wav", 0, SND_ASYNC);
					}
				}

				// 3.繪出新球
				Ball(hdc, cx[i], cy[i], r[i], cc[i]);
			}
		}
		
	}

	CDialogEx::OnTimer(nIDEvent);
}
