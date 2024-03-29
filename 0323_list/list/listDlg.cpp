﻿
// listDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "list.h"
#include "listDlg.h"
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


// ClistDlg 對話方塊



ClistDlg::ClistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST_DIALOG, pParent)
	, m_Edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_LIST1, m_List1);
}

BEGIN_MESSAGE_MAP(ClistDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &ClistDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ClistDlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &ClistDlg::OnLvnItemchangedList1)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &ClistDlg::OnItemclickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &ClistDlg::OnColumnclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &ClistDlg::OnClickList1)
END_MESSAGE_MAP()


// ClistDlg 訊息處理常式
CToolTipCtrl m_TP;
BOOL ClistDlg::OnInitDialog()
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
	m_TP.Create(this);
	m_TP.Activate(TRUE);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void ClistDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void ClistDlg::OnPaint()
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
HCURSOR ClistDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void ClistDlg::OnBnClickedButton1()
{
	// 0. initialization
	int S[100][4];  // 4 subjects score
	char N[100][10]; // names
	char S1[100];
	errno_t err;
	FILE *f;
	int no = 0;

	// 1. open the file
	err = fopen_s(&f, "Book1.txt", "rb");
	if (err != 0) {
		SetWindowText(L"Book1 not found");
		return;
	}

	// 2. read the file
	while (!(feof(f))) {
		fscanf_s(f, "%s %d %d %d %d\n", &N[no], 10, &S[no][0], &S[no][1], &S[no][2], &S[no][3]);  //read the content of Book1 to the arrays
		sprintf_s(S1, "%s %d %d %d %d\r\n", N[no], S[no][0], S[no][1], S[no][2], S[no][3]);
		UpdateData(1);
		m_Edit1 += S1;
		UpdateData(0);
		no++;
	}
}

void Big5toUnicode(char *Big5, wchar_t *Unicode, int len) {
	MultiByteToWideChar(950, 0, Big5, -1, Unicode, len + 1);
}

int S[100][4];  //4 subjects score
char N[100][10]; //names
int no = 0; // number of people
void ClistDlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_List1.InsertColumn(0, L"Name");		m_List1.SetColumnWidth(0, 60);
	m_List1.InsertColumn(1, L"Chinese");	m_List1.SetColumnWidth(1, 60);
	m_List1.InsertColumn(2, L"English");	m_List1.SetColumnWidth(2, 60);
	m_List1.InsertColumn(3, L"Math");		m_List1.SetColumnWidth(3, 60);
	m_List1.InsertColumn(4, L"Society");	m_List1.SetColumnWidth(4, 60);

	//0. initialization
	char S1[100];
	errno_t err;
	FILE *f;
	
	//1. open the file
	err = fopen_s(&f, "Book1.txt", "rb");
	if (err != 0) {
		SetWindowText(L"Book1 not found");
		return;
	}
	//2. read the file
	wchar_t temp[10];
	while (!(feof(f))) {
		fscanf_s(f, "%s %d %d %d %d\n", &N[no], 10, &S[no][0], &S[no][1], &S[no][2], &S[no][3]);  //read the content of Book1 to the arrays
		Big5toUnicode(&N[no][0], temp, strlen(&N[no][0]));
		m_List1.InsertItem(no, temp);
		for (int i = 0; i < 4; i++) {
			sprintf_s(S1, "%d", S[no][i]);
			Big5toUnicode(S1, temp, strlen(S1));
			m_List1.SetItemText(no, i+1, temp);
		}
		no++;
	}
}

void Swap(char Name[][10], int Score[][4], int a, int b){
	// exchange names
	char T[10];
	strcpy_s(T, &Name[a][0]);
	strcpy_s(&Name[a][0], 10, &Name[b][0]);
	strcpy_s(&Name[b][0], 10, T);

	// exchange scores
	for (int i = 0; i < 4; i++) {
		Score[a][i] += Score[b][i];
		Score[b][i] = Score[a][i] - Score[b][i];
		Score[a][i] -= Score[b][i];
	}
}

// Name[][10]: record names
// Score[][4]: record 4 subjects scores
// N: record number of people
// I: record the column (item) which is going to sort (0: Name, 1: Chinese, 2: English, 3: Math, 4: Social Science)
// F: sorting Direction (0: decreasing, 1: increasing)
void Sorting(char Name[][10], int Score[][4], int N, int I, int F) {
	int i, j, k;

	if (F > 0) {
		// use bubble sort to sort 4 subjects
		if (I >= 1 && I <= 4) {
			for (i = 0; i < N; i++) {
				for (j = i + 1; j < N; j++) {
					if (Score[i][I - 1] > Score[j][I - 1]) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
		// sort name
		else {
			for (i = 0; i < N; i++) {
				for (j = 0; j < N - 1; j++) {
					if (strcmp(&Name[i][0], &Name[j][0]) > 0) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
	}
	else {
		// use bubble sort to sort 4 subjects
		if (I >= 1 && I <= 4) {
			for (i = 0; i < N; i++) {
				for (j = i + 1; j < N; j++) {
					if (Score[i][I - 1] < Score[j][I - 1]) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
		// sort name
		else {
			for (i = 0; i < N; i++) {
				for (j = 0; j < N - 1; j++) {
					if (strcmp(&Name[i][0], &Name[j][0]) < 0) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
	}
	
}



void ClistDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}


int dir = 0;
void ClistDlg::OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	// 1. get item number which you click
	NMLISTVIEW *pLV = (NMLISTVIEW *)pNMHDR;
	int I = pLV->iItem;

	// 2. sort the column
	dir = (dir + 1) % 2;
	Sorting(N, S, no, I, dir);

	// 3. redisplay
	m_List1.DeleteAllItems();

	wchar_t temp[10];
	char S1[100];

	for (int n = 0; n < no; n++) {
		Big5toUnicode(&N[n][0], temp, strlen(&N[n][0]));
		m_List1.InsertItem(n, temp);
		for (int i = 0; i < 4; i++) {
			sprintf_s(S1, "%d", S[n][i]);
			Big5toUnicode(S1, temp, strlen(S1));
			m_List1.SetItemText(n, i + 1, temp);
		}
	}

	*pResult = 0;
}


void ClistDlg::OnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	

	*pResult = 0;
}


void ClistDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	// 1. get column number
	NMLISTVIEW *pLV = (NMLISTVIEW *)pNMHDR;
	int I = pLV->iItem, J = pLV->iSubItem;

	// 2. calculate total score of column
	if (J == 0 && I >= 0) {
		int sum = 0;
		for (int i = 0; i < 4; i++) sum += S[I][i];
		char S1[100];
		wchar_t temp[100];
		sprintf_s(S1, "%s-total score=%d", &N[I-1][10], sum);
		Big5toUnicode(S1, temp, strlen(S1));

		// 3. display on title
		SetWindowText(temp);

		// 4. display ToolTip
		m_TP.AddTool(GetDlgItem(IDC_LIST1), temp, 0, 0);

	}
	

	*pResult = 0;
}


BOOL ClistDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	if (m_TP.m_hWnd != NULL) m_TP.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}
