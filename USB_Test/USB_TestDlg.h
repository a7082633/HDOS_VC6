// USB_TestDlg.h : header file
//

#if !defined(AFX_USB_TESTDLG_H__9066C15E_5B70_4D60_8C06_9FDC19CB9341__INCLUDED_)
#define AFX_USB_TESTDLG_H__9066C15E_5B70_4D60_8C06_9FDC19CB9341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUSB_TestDlg dialog

class CUSB_TestDlg : public CDialog
{
// Construction
public:
	HANDLE DevHandle;
	CUSB_TestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUSB_TestDlg)
	enum { IDD = IDD_USB_TEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSB_TestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUSB_TestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnFinddev();
	afx_msg void OnBtnClosedev();
	afx_msg void OnBtnBeep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USB_TESTDLG_H__9066C15E_5B70_4D60_8C06_9FDC19CB9341__INCLUDED_)
