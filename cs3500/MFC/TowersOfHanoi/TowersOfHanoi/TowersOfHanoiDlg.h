
// TowersOfHanoiDlg.h : header file
//

#pragma once


// CTowersOfHanoiDlg dialog
class CTowersOfHanoiDlg : public CDialogEx
{
// Construction
public:
	CTowersOfHanoiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TOWERSOFHANOI_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
