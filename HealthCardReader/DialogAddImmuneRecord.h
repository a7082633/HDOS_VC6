#if !defined(AFX_DIALOGADDIMMUNERECORD_H__093E4468_4481_4A7F_A225_FBBC0AD5FDF0__INCLUDED_)
#define AFX_DIALOGADDIMMUNERECORD_H__093E4468_4481_4A7F_A225_FBBC0AD5FDF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAddImmuneRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAddImmuneRecord dialog

class CDialogAddImmuneRecord : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogAddImmuneRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAddImmuneRecord)
	enum { IDD = IDD_DIALOG_WRITE_IMMUNE_RECORD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAddImmuneRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAddImmuneRecord)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGADDIMMUNERECORD_H__093E4468_4481_4A7F_A225_FBBC0AD5FDF0__INCLUDED_)