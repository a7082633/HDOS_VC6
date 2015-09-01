#if !defined(AFX_DIALOGWRITERELATIVEINFO_H__7D834056_098B_4675_8A03_07B4909A79A8__INCLUDED_)
#define AFX_DIALOGWRITERELATIVEINFO_H__7D834056_098B_4675_8A03_07B4909A79A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWriteRelativeInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteRelativeInfo dialog

class CDialogWriteRelativeInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWriteRelativeInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWriteRelativeInfo)
	enum { IDD = IDD_DIALOG_WRITE_RELATIVEINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWriteRelativeInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWriteRelativeInfo)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITERELATIVEINFO_H__7D834056_098B_4675_8A03_07B4909A79A8__INCLUDED_)
