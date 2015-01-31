
// notepodView.cpp : implementation of the CnotepodView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "notepod.h"
#endif

#include "notepodDoc.h"
#include "notepodView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnotepodView

IMPLEMENT_DYNCREATE(CnotepodView, CEditView)

BEGIN_MESSAGE_MAP(CnotepodView, CEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CnotepodView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CnotepodView construction/destruction

CnotepodView::CnotepodView()
{
	// TODO: add construction code here

}

CnotepodView::~CnotepodView()
{
}

BOOL CnotepodView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}


// CnotepodView printing


void CnotepodView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CnotepodView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CnotepodView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CnotepodView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CnotepodView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CnotepodView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CnotepodView diagnostics

#ifdef _DEBUG
void CnotepodView::AssertValid() const
{
	CEditView::AssertValid();
}

void CnotepodView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CnotepodDoc* CnotepodView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CnotepodDoc)));
	return (CnotepodDoc*)m_pDocument;
}
#endif //_DEBUG


// CnotepodView message handlers
