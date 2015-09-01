#if !defined(AFX_PSAMDIALOG_H__B9CFE245_2787_4BD0_A770_1A4701F7CE4D__INCLUDED_)
#define AFX_PSAMDIALOG_H__B9CFE245_2787_4BD0_A770_1A4701F7CE4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSAMDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PSAMDialog dialog

class PSAMDialog : public CDialog
{
// Construction
public:
	static void SetHandle(int ihandle);
	PSAMDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PSAMDialog)
	enum { IDD = IDD_DIALOG_PSAM };
	CListBox	m_cListBox;
	CString	m_PIN;
	CString	m_OldPIN;
	CString	m_NEWPIN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PSAMDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PSAMDialog)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton5();
	afx_msg void OnButton4();
	afx_msg void OnButton7();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSAMDIALOG_H__B9CFE245_2787_4BD0_A770_1A4701F7CE4D__INCLUDED_)
