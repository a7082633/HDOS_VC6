#if !defined(AFX_INPUTDIALOG_H__16A01913_7EC2_470B_81C2_460A7D32BC90__INCLUDED_)
#define AFX_INPUTDIALOG_H__16A01913_7EC2_470B_81C2_460A7D32BC90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDialog.h : header file
//
#define FILE_DDF1EF08	1
#define FILE_DF01EF05	2
#define FILE_DF01EF06	3
#define FILE_DF01EF07	4	//职业信息
#define FILE_DF01EF08	5
#define FILE_DF02EF05	6
#define FILE_DF02EF06	7
#define FILE_DF02EF07	8
#define FILE_DF02EF08	9

#define FILE_DDF1EF05	10
#define FILE_DDF1EF06	11



/////////////////////////////////////////////////////////////////////////////
// InputDialog dialog

class InputDialog : public CDialog
{
// Construction
public:
	bool _CancelPressed;
	void Setview(int type);
	InputDialog(CWnd* pParent = NULL );   // standard constructor

// Dialog Data
	//{{AFX_DATA(InputDialog)
	enum { IDD = IDD_DIALOG_input };
	CEdit	m_cedit1;
	CString	m_static1;
	CString	m_static2;
	CString	m_static3;
	CString	m_static4;
	CString	m_static5;
	CString	m_static6;
	CString	m_static7;
	CString	m_static8;
	CString	m_static9;
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit4;
	CString	m_edit5;
	CString	m_edit6;
	CString	m_edit7;
	CString	m_edit8;
	CString	m_edit9;
	CString	m_static10;
	CString	m_edit10;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InputDialog)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDIALOG_H__16A01913_7EC2_470B_81C2_460A7D32BC90__INCLUDED_)
