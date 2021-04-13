
// BMPDlg.h : header file
//

#pragma once

// Header File & Library for painting
#include "vfw.h"
#pragma comment(lib, "vfw32.lib")


// CBMPDlg dialog
class CBMPDlg : public CDialogEx
{
// Construction
public:
	CBMPDlg(CWnd* pParent = nullptr);	// standard constructor
	int Draw_BitMap(int x, int y, int PX, int PY, unsigned char * Data);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BMP_DIALOG };
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
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
