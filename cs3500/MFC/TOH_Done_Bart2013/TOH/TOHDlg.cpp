
// TOHDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TOH.h"
#include "TOHDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int MARGIN=6;
const int BASE_WIDTH = 26;
const int BASE_HEIGHT = 10;
const int TOWER_WIDTH = 4;
const int TOWER_HEIGHT = 45;
const int SPACE_BETWEEN_DISKS = 5;
const int NUM_DISKS = 4; // don't use more than 7
const int DISK_HEIGHT = 5;
const int DISK_GAP = 1;
const double DISK_DECREASE = 2.5;

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


// CTOHDlg dialog




CTOHDlg::CTOHDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTOHDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTOHDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTOHDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTOHDlg message handlers

BOOL CTOHDlg::OnInitDialog()
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
	double diskWidth = BASE_WIDTH - DISK_DECREASE;
	for(int d=0; d<NUM_DISKS; d++)
	{
		mTower[0].push_back((int)diskWidth);
		diskWidth -= DISK_DECREASE;
	}

	mSelectedTower = -1;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTOHDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if((nID & 0xFFF0) == IDM_ABOUTBOX)
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
// For MFC applications using the document/view model, this is automatically done for you by the framework.

void CTOHDlg::OnPaint()
{
	if(IsIconic())
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
		// Do our drawing here.
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		int w = rect.Width();
		int h = rect.Height();
		int x1,x2,y1,y2;
		CBrush blueBrush( RGB(0,0,255) );
		CBrush redBrush( RGB(255,0,0) );
		CBrush whiteBrush( RGB(255,255,255) );
		CBrush towerBrush( RGB(100, 20, 80) );

		COLORREF backgroundColor = RGB(200,200,255);
		CBrush backgroundBrush( backgroundColor );

		dc.SetBkMode(TRANSPARENT); // for Text //TRANSPARENT for no text background
		//dc.SetBkColor(backgroundColor); // for text

		// Paint the background:
		dc.SelectObject(backgroundBrush);
		dc.Rectangle(rect);

		// Draw all 3 towers:
		for(int t=0; t<3; t++)
		{
			if(t == mSelectedTower)
			{
				dc.SelectObject(redBrush);
			}
			else
			{
				dc.SelectObject(towerBrush);
			}
			// Draw the base of a tower
			x1 = MARGIN + t*(BASE_WIDTH+SPACE_BETWEEN_DISKS);
			x2 = x1 + BASE_WIDTH;
			y1 = MARGIN;
			y2 = y1 + BASE_HEIGHT;
			dc.Rectangle(x1*w/100, h-y1*h/100, x2*w/100, h-y2*h/100);

			// Draw the pole of a tower
			int midBase = (x1+x2)/2;
			x1 = midBase - TOWER_WIDTH/2;
			x2 = midBase + TOWER_WIDTH/2;
			y1 = MARGIN + BASE_HEIGHT;
			y2 = y1 + TOWER_HEIGHT;
			dc.Rectangle(x1*w/100, h-y1*h/100, x2*w/100, h-y2*h/100);

			// Draw the disks of a tower
			y1 = y1 + DISK_GAP;
			y2 = y1 + DISK_HEIGHT;
			dc.SelectObject(blueBrush);
			for(unsigned int d=0; d<mTower[t].size(); d++)
			{
				x1 = midBase - mTower[t][d]/2;
				x2 = midBase + mTower[t][d]/2;
				dc.Rectangle(x1*w/100, h-y1*h/100, x2*w/100, h-y2*h/100);
				y1 = y2 + DISK_GAP;
				y2 = y1 + DISK_HEIGHT;
			}
		}

		if(mTower[1].size() == NUM_DISKS) // Draw if the user won
		{
			dc.TextOutW(MARGIN*w/100, (int)(.8*MARGIN*h)/100, L"You Won!");
		}
		else // or draw the instructions:
		{
			dc.TextOutW(MARGIN*w/100, (int)(0.8*MARGIN*h)/100, L"To win this game, move all the disks from the first tower to the second.");
			dc.TextOutW(MARGIN*w/100, (int)(1.5*MARGIN*h)/100, L"You may only move one disk at a time, and you can't put a bigger disk on a smaller disk.");
			if(mSelectedTower == -1)
			{
				dc.TextOutW(MARGIN*w/100, (int)(3.0*MARGIN*h)/100, L"Click on a tower to move a disk from:");
			}
			else
			{
				dc.TextOutW(w/2, (int)(3.0*MARGIN*h)/100, L"Now click on a tower to move the disk to:");
			}
		}

		// Call the parent method
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTOHDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTOHDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Check all three towers to see if <point> is inside of them, and set <picked> accordingly
	CRect rect;
	GetClientRect(&rect);
	int w = rect.Width();
	int h = rect.Height();
	int x1, x2, y1, y2;
	int picked = -1;
	for(int t=0; t<3; t++)
	{
		// Check the base of a tower
		x1 = MARGIN + t*(BASE_WIDTH+SPACE_BETWEEN_DISKS);
		x2 = x1 + BASE_WIDTH;
		y1 = MARGIN;
		y2 = y1 + BASE_HEIGHT;
		if( point.x >= x1*w/100 && point.y <= h-y1*h/100 && point.x <= x2*w/100 && point.y >= h-y2*h/100)
		{
			picked = t;
		}
			
		// Check the pole of a tower
		int midBase = (x1+x2)/2;
		x1 = midBase - TOWER_WIDTH/2;
		x2 = midBase + TOWER_WIDTH/2;
		y1 = MARGIN + BASE_HEIGHT;
		y2 = y1+TOWER_HEIGHT;
		if( point.x >= x1*w/100 && point.y <= h-y1*h/100 && point.x <= x2*w/100 && point.y >= h-y2*h/100)
		{
			picked = t;
		}

		// Check the disks of a tower
		y1 = y1 + DISK_GAP;
		y2 = y1 + DISK_HEIGHT;
		for(unsigned int d=0; d<mTower[t].size(); d++)
		{
			x1 = midBase - mTower[t][d]/2;
			x2 = midBase + mTower[t][d]/2;
			if( point.x >= x1*w/100 && point.y <= h-y1*h/100 && point.x <= x2*w/100 && point.y >= h-y2*h/100)
			{
				picked = t;
			}
			y1 = y2 + DISK_GAP;
			y2 = y1 + DISK_HEIGHT;
		}
	}
	if(picked == -1) // if the user didn't click on any tower, do nothing.
	{
		return;
	}

	if(mSelectedTower == -1) // A first click. The picked tower is the source of the move
	{
		if(mTower[picked].size() > 0) // can't pick a tower with nothing in it.
		{
			mSelectedTower = picked;
		}
	}
	else // A second click. The picked tower is the destination of the move (mSelectedTower is the source).
	{
		if (mTower[picked].size() == 0 || mTower[mSelectedTower].back() < mTower[picked].back() ) // a legal move
		{
			// make the move!
			mTower[picked].push_back( mTower[mSelectedTower].back() );
			mTower[mSelectedTower].pop_back();
		}
		mSelectedTower = -1;
	}

	Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}
