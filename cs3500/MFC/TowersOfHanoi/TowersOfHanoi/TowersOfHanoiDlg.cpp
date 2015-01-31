// TowersOfHanoiDlg.cpp : implementation file

#include "stdafx.h"
#include "TowersOfHanoi.h"
#include "TowersOfHanoiDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTowersOfHanoiDlg dialog




CTowersOfHanoiDlg::CTowersOfHanoiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTowersOfHanoiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTowersOfHanoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTowersOfHanoiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTowersOfHanoiDlg message handlers

BOOL CTowersOfHanoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTowersOfHanoiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below to draw the icon.  
//For MFC applications using the document/view model, this is automatically done for you by the framework.
const double BASE_WIDTH = 20;
const double BASE_HEIGHT = 10;
const double BASE_SEP = 10;

void CTowersOfHanoiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting // like a canvas

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
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect); // ClientRect just deals with canvas not margin or header
		int w = rect.Width();
		int h = rect.Height();

		//draw base of tower
		for(int i=1;i<4;i++)
		{
			CBrush towerBrush(RGB(0,255,0));//pens for outline, brush for filled
			dc.SelectObject(towerBrush);
			int x1 = BASE_SEP;
			int y1 = BASE_SEP;
			int x2 = x1 + BASE_WIDTH;
			int y2 = y1 + BASE_HEIGHT;
			dc.Rectangle(x1*w/100, h-y1*h/100, x2*w/100, h-y2*h/100);
			//draw pole of tower
		}

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CTowersOfHanoiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTowersOfHanoiDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnLButtonDown(nFlags, point);
}
