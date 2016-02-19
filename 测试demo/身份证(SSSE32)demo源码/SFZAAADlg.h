// SFZAAADlg.h : header file
//

#if !defined(AFX_SFZAAADLG_H__364CE997_48C4_434C_B90F_5763A0FD24C7__INCLUDED_)
#define AFX_SFZAAADLG_H__364CE997_48C4_434C_B90F_5763A0FD24C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSFZAAADlg dialog

class CSFZAAADlg : public CDialog
{
// Construction
public:
	long hReader;
	HANDLE m_hThread;
	static DWORD WINAPI ReaderThread(LPVOID lpParameter);
	CSFZAAADlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSFZAAADlg)
	enum { IDD = IDD_SFZAAA_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFZAAADlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSFZAAADlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnopen();
	afx_msg void OnBtnclen();
	afx_msg void OnBtnread();
	afx_msg void OnClosethread();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFZAAADLG_H__364CE997_48C4_434C_B90F_5763A0FD24C7__INCLUDED_)
