// FreeCellStarter2010Dlg.cpp : implementation file

#include "stdafx.h"
#include "FreeCellStarter2010.h"
#include "FreeCellStarter2010Dlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const int COL_COUNT = 8;

const int MARGIN = 20;
const int PADDING = 2;

const int CARD_OFFSET = 25;

const int CELL_WIDTH = 75;
const int CELL_HEIGHT = 100;

const int COL_WIDTH = CELL_WIDTH;
const int COL_HEIGHT = CELL_HEIGHT+(17*MARGIN);

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

// CFreeCellStarter2010Dlg dialog

CFreeCellStarter2010Dlg::CFreeCellStarter2010Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFreeCellStarter2010Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CFreeCellStarter2010Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFreeCellStarter2010Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_NEW, &CFreeCellStarter2010Dlg::OnFileNew)
END_MESSAGE_MAP()


// CFreeCellStarter2010Dlg message handlers

BOOL CFreeCellStarter2010Dlg::OnInitDialog()
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

	/*
	//CWnd* pImage = GetDlgItem(IDR_MAINFRAME);
	CWnd *pImage = (CWnd*) GetDlgItem(IDR_MAINFRAME);


    CRect rect;
    pImage->GetWindowRect(rect);
    HRGN hRgn = CreateRoundRectRgn(0, 0, rect.Width(), rect.Height(), 40, 40);
    HINSTANCE hIns = AfxGetInstanceHandle();
    HBITMAP hBmp = LoadBitmap(hIns, MAKEINTRESOURCE(IDR_MAINFRAME));
    HBRUSH hBr = CreatePatternBrush(hBmp); 
    DeleteObject(hIns);
    DeleteObject(hBmp);
    FillRgn(pImage->GetDC()->GetSafeHdc(), hRgn, hBr);

	*/


		/*
	CString pngPath=L"U:\\Pictures\tron.jpg";
	CImage pngImage;
	CBitmap pngBmp; 
	CDC bmDC;
	CBitmap *pOldbmp;
	BITMAP  bi;
	//UINT xPos=450,yPos=300;
	UINT xPos=10,yPos=10;
	CClientDC dc(this);

	pngImage.Load(pngPath);
	// new code

	pngBmp.Attach(pngImage.Detach());

	bmDC.CreateCompatibleDC(&dc);

	pOldbmp= bmDC.SelectObject(&pngBmp);
	pngBmp.GetBitmap(&bi);
	dc.BitBlt(xPos,yPos,bi.bmWidth,bi.bmHeight,&bmDC,0,0,SRCCOPY);  
	bmDC.SelectObject(pOldbmp);*/

	//CString imgpath=L"U:\\Pictures\tron.jpg";
	//CImage cimage;
	//CBitmap bitmapimg;
	//cimage.Load(imgpath);
	//bitmapimg.Attach(cimage.Detach());

	/*
	//works
	CRect rect;
	GetClientRect(&rect);
	CBrush blueBrush(RGB(0,0,255));
	COLORREF backgroundColor = RGB(200,200,255);
	CBrush backgroundBrush(backgroundColor);
	//dc.SetBkMode(TRANSPARENT);//for text
	dc.SelectObject(backgroundBrush);
	dc.Rectangle(rect);*/
	/*
	CRect rect;
	rect.SetRect(100,100,200,200);
	CBitmap bmp;
	bmp
	CDialogEx::SetBackgroundImage(bitmapimg);*/

	//HINSTANCE hIns = AfxGetInstanceHandle();
	//HBITMAP hbitmap = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDR_MAINFRAME));
	//CDialogEx::SetBackgroundImage(bitmapimg);

	this->mSelectedCell = -1;
	this->mWinner = false;

	for(unsigned int i=0; i<52; i++)
	{
		mCardvec.push_back(i);
	}
	int time = std::time(0);
	std::srand(time);
	std::random_shuffle(mCardvec.begin(), mCardvec.end());

	char titlestr[100];
	_itoa(time ,titlestr, 10);
	CString titlestart = L"Free Cell Game Number: ";
	CString titlenumber = (CString)titlestr;
	CString titlefull = titlestart + titlenumber;
	this->SetWindowText(titlefull);

	// Setup the cards
	bool ok = InitializeCards();
	if(!ok)
	{
		MessageBox(L"cards.dll failed to initialize", L"Error");
		return true;
	}
	//init cells
	int l,t,r,b,index;
	for(int tc=0; tc<4; tc++)
	{
		l = MARGIN+(MARGIN*tc)+(CELL_WIDTH*tc);
		t = MARGIN;
		r = l + CELL_WIDTH;
		b = t + CELL_HEIGHT;
		index = tc;
		mCells[index] = new TempCell(l,t,r,b);
	}
	for(int ec=0; ec<4; ec++)
	{
		l = MARGIN+(MARGIN*ec)+(CELL_WIDTH*ec)+(MARGIN*4)+(CELL_WIDTH*4);
		t = MARGIN;
		r = l + CELL_WIDTH;
		b = t + CELL_HEIGHT;
		index = ec + 4;
		mCells[index] = new EndCell(l,t,r,b);
	}
	for(int sc=0; sc<8; sc++)
	{
		l = MARGIN+(MARGIN*sc)+(CELL_WIDTH*sc);
		t = MARGIN + CELL_HEIGHT + (MARGIN*2);
		r = l + CELL_WIDTH;
		b = t + COL_HEIGHT;
		index = sc+8;
		mCells[index] = new StartCell(l,t,r,b);
		if(sc < 4)
		{
			for(int c=0; c<7; c++)
			{
				mCells[index]->AddCard(mCardvec.back());
				mCardvec.pop_back();
			}
		}
		else if((sc >=4) && (sc < 8))
		{
			for(int c=0; c<6; c++)
			{
				mCells[index]->AddCard(mCardvec.back());
				mCardvec.pop_back();
			}
		}
		mCells[index]->SetInit(false);
	}

	return TRUE; // return TRUE unless you set the focus to a control
}

void CFreeCellStarter2010Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
// For MFC applications using the document/view model, this is automatically done for you by the framework.
void CFreeCellStarter2010Dlg::OnPaint()
{
	/*
	CString pngPath=L"U:\\Pictures\tron.jpg";
	CImage pngImage;
	CBitmap pngBmp; 
	CDC bmDC;
	CBitmap *pOldbmp;
	BITMAP  bi;
	//UINT xPos=450,yPos=300;
	UINT xPos=10,yPos=10;
	CClientDC dc(this);

	pngImage.Load(pngPath);
	// new code

	pngBmp.Attach(pngImage.Detach());

	bmDC.CreateCompatibleDC(&dc);

	pOldbmp= bmDC.SelectObject(&pngBmp);
	pngBmp.GetBitmap(&bi);
	dc.BitBlt(xPos,yPos,bi.bmWidth,bi.bmHeight,&bmDC,0,0,SRCCOPY);  
	bmDC.SelectObject(pOldbmp);*/

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
		/*
		CImage image;
		image.Load(_T("U:\\Pictures\tron.jpg"));
		CBitmap bitmap;
		bitmap.Attach(image.Detach());*/

		/*
		//CWnd* pImage = GetDlgItem(IDC_PICTURE_CONTROL);
		CWnd *pImage = (CWnd*) GetDlgItem(IDC_BATCH);

        CRect rc;
        pImage->GetWindowRect(rc);
        HRGN hRgn = CreateRoundRectRgn(0, 0, rc.Width(), rc.Height(), 40, 40);
        HINSTANCE hIns = AfxGetInstanceHandle();
        HBITMAP hBmp = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP1));
        HBRUSH hBr = CreatePatternBrush(hBmp); 
        DeleteObject(hIns);
        DeleteObject(hBmp);
        FillRgn(pImage->GetDC()->GetSafeHdc(), hRgn, hBr);
		*/



		CPaintDC dc(this); // device context for painting
		//paint background

		/*
		//CWnd* pImage = GetDlgItem(IDR_MAINFRAME);
		CWnd *pImage = (CWnd*) GetDlgItem(IDR_MAINFRAME);


        CRect rect;
        pImage->GetWindowRect(rect);
        HRGN hRgn = CreateRoundRectRgn(0, 0, rect.Width(), rect.Height(), 40, 40);
        HINSTANCE hIns = AfxGetInstanceHandle();
        HBITMAP hBmp = LoadBitmap(hIns, MAKEINTRESOURCE(IDR_MAINFRAME));
        HBRUSH hBr = CreatePatternBrush(hBmp); 
        DeleteObject(hIns);
        DeleteObject(hBmp);
        FillRgn(pImage->GetDC()->GetSafeHdc(), hRgn, hBr);
		*/

		//works
		CRect rect;
		GetClientRect(&rect);
		CBrush blueBrush(RGB(0,0,255));
		COLORREF backgroundColor = RGB(200,200,255);
		CBrush backgroundBrush(backgroundColor);
		//dc.SetBkMode(TRANSPARENT);//for text
		dc.SelectObject(backgroundBrush);
		dc.Rectangle(rect);

		//paint cells and cards
		for(int i=0; i<16;i++)
		{
			mCells[i]->Draw(dc);
		}
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CFreeCellStarter2010Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFreeCellStarter2010Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	UninstallCards();
	CDialogEx::OnClose();
}

void CFreeCellStarter2010Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!mWinner)
	{
		if(this->mSelectedCell == -1)
		{
			for(int i=0; i<16;i++)
			{
				if(mCells[i]->IsPointWithinCell(point))
				{
					if(mCells[i]->CanRemoveCard())
					{
						mCells[i]->SetSelected(true);
						this->mSelectedCell = i;
						Invalidate();
						return;
					}
				}
			}
			return;
		}
		else if(this->mSelectedCell > -1)
		{
			for(int i=0; i<16; i++)
			{
				if(mCells[i]->IsPointWithinCell(point))
				{
					if(i == this->mSelectedCell) 
					{ 
						mCells[this->mSelectedCell]->SetSelected(false);
						this->mSelectedCell = -1;
						Invalidate();
						return; 
					}
					else if(mCells[i]->CanAcceptCard(mCells[this->mSelectedCell]->GetCardOnTop()))
					{
						mCells[i]->AddCard(mCells[this->mSelectedCell]->GetCardOnTop());
						mCells[this->mSelectedCell]->RemoveCard();

						int ec1 = mCells[4]->GetCardOnTop();
						int ec2 = mCells[5]->GetCardOnTop();
						int ec3 = mCells[6]->GetCardOnTop();
						int ec4 = mCells[7]->GetCardOnTop();
						if((ec1 + ec2 +ec3 + ec4) == 198)
						{
							this->mWinner=true;
						}

						mCells[this->mSelectedCell]->SetSelected(false);
						this->mSelectedCell = -1;
						Invalidate();
						return;
					}
				}
				else if(!(mCells[i]->IsPointWithinCell(point)) && (i==15))
				{ 
					mCells[this->mSelectedCell]->SetSelected(false);
					this->mSelectedCell = -1;
					Invalidate();
					return;
				}
			}
		}
	}
	else
	{
		Invalidate();
		CDialogEx::OnLButtonDown(nFlags, point);
		return;
	}
	Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
	return;
}
/*
//outline from teacher
void CFreeCellStarter2010Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Determine which cell <point> is inside of. Store in <picked>.
	// If picked==NULL, do nothing and return.
	// If no cell is yet selected, 
		// If a card can be removed from the picked cell.  
			// Mark the cell selected, and store it in mSelectedCell. Invalidate()
		// Return.
	// else a cell is already selected, 
		// If picked is the same cell as mSelectedCell (a no-op)
			// Mark the cell not selected, clear the mSelectedCell, Invalidate and return
		// If the card in mSelectedCell can be added to the picked cell.
			// Remove the card from the selected cell and add it to the picked cell.
			// Check for winner
		// Else
			// Handle illegal move.
		// Mark the cell not selected, clear the mSelectedCell, Invalidate and return


	// Determine which cell got clicked:
	Cell * picked = NULL;
	for(int i=0; i<16; i++)
	{
		if(cells[i]->IsClicked(point.x, point.y))
		{
			picked = cells[i];
			break;
		}
	}

	if(picked==NULL) // the click missed any cells.
		return;

	...
}
*/

void CFreeCellStarter2010Dlg::OnFileNew()
{
	// TODO: Add your command handler code here
}
