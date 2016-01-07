// HD_HDRWInterfaceDemoDlg.h : header file
//

#if !defined(AFX_HD_HDRWINTERFACEDEMODLG_H__33878612_D6FC_4BAD_B7CE_E84E20870738__INCLUDED_)
#define AFX_HD_HDRWINTERFACEDEMODLG_H__33878612_D6FC_4BAD_B7CE_E84E20870738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHD_HDRWInterfaceDemoDlg dialog

class CHD_HDRWInterfaceDemoDlg : public CDialog
{
// Construction
public:
	CHD_HDRWInterfaceDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHD_HDRWInterfaceDemoDlg)
	enum { IDD = IDD_HD_HDRWINTERFACEDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_HDRWInterfaceDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHD_HDRWInterfaceDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_HDRWINTERFACEDEMODLG_H__33878612_D6FC_4BAD_B7CE_E84E20870738__INCLUDED_)
