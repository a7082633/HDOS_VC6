#if !defined(AFX_DIALOGINPUT2_H__C39C055C_AAB1_4AA6_8FD7_A53A1546575D__INCLUDED_)
#define AFX_DIALOGINPUT2_H__C39C055C_AAB1_4AA6_8FD7_A53A1546575D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogInput2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dialogInput2 dialog

class dialogInput2 : public CDialog
{
// Construction
public:
	bool _CancelPressed;
	dialogInput2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dialogInput2)
	enum { IDD = IDD_DIALOG_input2 };
	CString	m_edit1;
	CString	m_edit10;
	CString	m_edit11;
	CString	m_edit12;
	CString	m_edit13;
	CString	m_edit14;
	CString	m_edit15;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit4;
	CString	m_edit5;
	CString	m_edit6;
	CString	m_edit7;
	CString	m_edit8;
	CString	m_edit9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dialogInput2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dialogInput2)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGINPUT2_H__C39C055C_AAB1_4AA6_8FD7_A53A1546575D__INCLUDED_)
