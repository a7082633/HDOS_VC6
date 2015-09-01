#if !defined(AFX_DIALOGWRITEPUBLISHINFO_H__95CBE8B9_2E68_41F1_8658_2FE27B9C45A6__INCLUDED_)
#define AFX_DIALOGWRITEPUBLISHINFO_H__95CBE8B9_2E68_41F1_8658_2FE27B9C45A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWritePublishInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWritePublishInfo dialog

class CDialogWritePublishInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWritePublishInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWritePublishInfo)
	enum { IDD = IDD_DIALOG_WRITE_PUBLISHINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWritePublishInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWritePublishInfo)
	afx_msg void OnBtnWrite();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITEPUBLISHINFO_H__95CBE8B9_2E68_41F1_8658_2FE27B9C45A6__INCLUDED_)
