#if !defined(AFX_DIALOGWRITESPECIALINFO_H__687FDD03_D80E_4E85_9859_A05917796AC9__INCLUDED_)
#define AFX_DIALOGWRITESPECIALINFO_H__687FDD03_D80E_4E85_9859_A05917796AC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWriteSpecialInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteSpecialInfo dialog

class CDialogWriteSpecialInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWriteSpecialInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWriteSpecialInfo)
	enum { IDD = IDD_DIALOG_WRITE_SPECIALINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWriteSpecialInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWriteSpecialInfo)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITESPECIALINFO_H__687FDD03_D80E_4E85_9859_A05917796AC9__INCLUDED_)
