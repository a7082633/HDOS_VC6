// OCX_CallerDlg.h : header file
//

#if !defined(AFX_OCX_CALLERDLG_H__0A752743_3D16_467E_924B_ED551A5C84DD__INCLUDED_)
#define AFX_OCX_CALLERDLG_H__0A752743_3D16_467E_924B_ED551A5C84DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COCX_CallerDlg dialog

class COCX_CallerDlg : public CDialog
{
// Construction
public:
	COCX_CallerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COCX_CallerDlg)
	enum { IDD = IDD_OCX_CALLER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCX_CallerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COCX_CallerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCX_CALLERDLG_H__0A752743_3D16_467E_924B_ED551A5C84DD__INCLUDED_)
