#if !defined(AFX_DIALOGWRITECLINICALINFO_H__0A5E4DB3_E180_4A29_8D36_03129A0D5ADB__INCLUDED_)
#define AFX_DIALOGWRITECLINICALINFO_H__0A5E4DB3_E180_4A29_8D36_03129A0D5ADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWriteClinicalInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteClinicalInfo dialog

class CDialogWriteClinicalInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWriteClinicalInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWriteClinicalInfo)
	enum { IDD = IDD_DIALOG_WRITE_CLINICALINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWriteClinicalInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWriteClinicalInfo)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITECLINICALINFO_H__0A5E4DB3_E180_4A29_8D36_03129A0D5ADB__INCLUDED_)
