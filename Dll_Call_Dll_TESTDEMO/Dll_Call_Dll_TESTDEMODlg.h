// Dll_Call_Dll_TESTDEMODlg.h : header file
//

#if !defined(AFX_DLL_CALL_DLL_TESTDEMODLG_H__A85B9AAF_F0D0_4EC4_A1C2_3E3EF443E08E__INCLUDED_)
#define AFX_DLL_CALL_DLL_TESTDEMODLG_H__A85B9AAF_F0D0_4EC4_A1C2_3E3EF443E08E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDll_Call_Dll_TESTDEMODlg dialog

class CDll_Call_Dll_TESTDEMODlg : public CDialog
{
// Construction
public:
	CDll_Call_Dll_TESTDEMODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDll_Call_Dll_TESTDEMODlg)
	enum { IDD = IDD_DLL_CALL_DLL_TESTDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDll_Call_Dll_TESTDEMODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDll_Call_Dll_TESTDEMODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLL_CALL_DLL_TESTDEMODLG_H__A85B9AAF_F0D0_4EC4_A1C2_3E3EF443E08E__INCLUDED_)
