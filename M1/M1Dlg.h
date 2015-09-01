// M1Dlg.h : header file
//

#if !defined(AFX_M1DLG_H__01806DF9_D8A3_4677_9981_A8ACFB9D0057__INCLUDED_)
#define AFX_M1DLG_H__01806DF9_D8A3_4677_9981_A8ACFB9D0057__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CM1Dlg dialog

class CM1Dlg : public CDialog
{
// Construction
public:
	HMODULE hModule;
	int Authentication(int iSecNr);
	int InitialReader();
	long hReader;
	CM1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CM1Dlg)
	enum { IDD = IDD_M1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CM1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CM1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRqe();
	afx_msg void OnDestroy();
	afx_msg void OnBtnRa();
	afx_msg void OnBtnRa2();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnWritehex();
	afx_msg void OnBtnInitial();
	afx_msg void OnBtnIncrement();
	afx_msg void OnBtnDescment();
	afx_msg void OnBtnReadval();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnRastr();
	afx_msg void OnBtnWritestr();
	afx_msg void OnBtnRaall();
	afx_msg void OnBtnLoadkey();
	afx_msg void OnBtnOpenport();
	afx_msg void OnBtnCloseport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_M1DLG_H__01806DF9_D8A3_4677_9981_A8ACFB9D0057__INCLUDED_)
