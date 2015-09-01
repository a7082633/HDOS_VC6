#if !defined(AFX_DIALOGWRITEOWNERINFO_H__DF94F74C_2508_4400_B7C2_6C807437A5F0__INCLUDED_)
#define AFX_DIALOGWRITEOWNERINFO_H__DF94F74C_2508_4400_B7C2_6C807437A5F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWriteOwnerInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteOwnerInfo dialog

class CDialogWriteOwnerInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWriteOwnerInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWriteOwnerInfo)
	enum { IDD = IDD_DIALOG_WRITE_OWNERINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWriteOwnerInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWriteOwnerInfo)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITEOWNERINFO_H__DF94F74C_2508_4400_B7C2_6C807437A5F0__INCLUDED_)
