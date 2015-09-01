#if !defined(AFX_DLIALOGPASS_H__EEE6D05A_B97C_46DB_989C_979539123FB5__INCLUDED_)
#define AFX_DLIALOGPASS_H__EEE6D05A_B97C_46DB_989C_979539123FB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlialogPass.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlialogPass dialog

class CDlialogPass : public CDialog
{
// Construction
public:
	CListCtrl	m_list;
	long m_nItem;
	CString m_pass;
	HWND m_ListHwnd;
	CDlialogPass(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlialogPass)
	enum { IDD = IDD_DIALOG_PASS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlialogPass)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlialogPass)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLIALOGPASS_H__EEE6D05A_B97C_46DB_989C_979539123FB5__INCLUDED_)
