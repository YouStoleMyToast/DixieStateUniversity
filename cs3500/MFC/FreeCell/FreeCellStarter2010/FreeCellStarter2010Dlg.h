// FreeCellStarter2010Dlg.h : header file
#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

#include "Cell.h"

// CFreeCellStarter2010Dlg dialog
class CFreeCellStarter2010Dlg : public CDialogEx
{
// Construction
public:
	CFreeCellStarter2010Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FREECELLSTARTER2010_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	Cell *mCells[16];//16 pointers to cells
	int mSelectedCell;
	bool mWinner;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	std::vector<int> mCardvec;

public:
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileNew();
};
