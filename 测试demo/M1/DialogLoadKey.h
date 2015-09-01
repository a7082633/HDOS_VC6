#if !defined(AFX_DIALOGLOADKEY_H__F253D140_48AB_43D5_8E97_8467084D674C__INCLUDED_)
#define AFX_DIALOGLOADKEY_H__F253D140_48AB_43D5_8E97_8467084D674C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogLoadKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogLoadKey dialog

class CDialogLoadKey : public CDialog
{
// Construction
public:
	HMODULE hModule;
	long hReader;
	CDialogLoadKey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogLoadKey)
	enum { IDD = IDD_DIALOG_LOADKEY };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogLoadKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogLoadKey)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioS50();
	afx_msg void OnRadioS70();
	afx_msg void OnBtnDownload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGLOADKEY_H__F253D140_48AB_43D5_8E97_8467084D674C__INCLUDED_)
