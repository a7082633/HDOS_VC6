#if !defined(AFX_DIALOGWRITEADDRINFO_H__D8F9D7AF_0C3F_447D_BDB3_78E2A6BEDA8A__INCLUDED_)
#define AFX_DIALOGWRITEADDRINFO_H__D8F9D7AF_0C3F_447D_BDB3_78E2A6BEDA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWriteAddrInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteAddrInfo dialog

class CDialogWriteAddrInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWriteAddrInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWriteAddrInfo)
	enum { IDD = IDD_DIALOG_WRITE_ADDRINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWriteAddrInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWriteAddrInfo)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITEADDRINFO_H__D8F9D7AF_0C3F_447D_BDB3_78E2A6BEDA8A__INCLUDED_)
