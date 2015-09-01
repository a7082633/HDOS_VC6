#if !defined(AFX_DIALOGWRITELICENCEINFO_H__52DEFB2F_85BB_4478_9D35_6D74993E5243__INCLUDED_)
#define AFX_DIALOGWRITELICENCEINFO_H__52DEFB2F_85BB_4478_9D35_6D74993E5243__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWriteLicenceInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteLicenceInfo dialog

class CDialogWriteLicenceInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWriteLicenceInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWriteLicenceInfo)
	enum { IDD = IDD_DIALOG_WRITE_LICENCEINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWriteLicenceInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWriteLicenceInfo)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITELICENCEINFO_H__52DEFB2F_85BB_4478_9D35_6D74993E5243__INCLUDED_)
