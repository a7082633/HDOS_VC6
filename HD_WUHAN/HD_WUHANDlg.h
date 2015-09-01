// HD_WUHANDlg.h : header file
//

#if !defined(AFX_HD_WUHANDLG_H__D9B1C820_1D23_48B7_BF68_D687FE233DED__INCLUDED_)
#define AFX_HD_WUHANDLG_H__D9B1C820_1D23_48B7_BF68_D687FE233DED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHD_WUHANDlg dialog

class CHD_WUHANDlg : public CDialog
{
// Construction
public:
	static DWORD WINAPI ReaderThread(LPVOID lpParameter);
	HANDLE m_hThread;
	long ReaderHandle;
	CHD_WUHANDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CHD_WUHANDlg)
	enum { IDD = IDD_HD_WUHAN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_WUHANDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHD_WUHANDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnClose();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnOpenthread();
	afx_msg void OnBtnClosethread();
	virtual void OnOK();
	afx_msg void OnBtnReadother();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_WUHANDLG_H__D9B1C820_1D23_48B7_BF68_D687FE233DED__INCLUDED_)
