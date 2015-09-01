// ID_CARDDlg.h : header file
//

#if !defined(AFX_ID_CARDDLG_H__2BA6F527_65A3_4DE7_993B_0EDB88268C11__INCLUDED_)
#define AFX_ID_CARDDLG_H__2BA6F527_65A3_4DE7_993B_0EDB88268C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CID_CARDDlg dialog

class CID_CARDDlg : public CDialog
{
// Construction
public:
	int InitComm();
	HANDLE m_hThread;
	static DWORD WINAPI ReaderThread(LPVOID lpParameter);
	int iPort;
	CID_CARDDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CID_CARDDlg)
	enum { IDD = IDD_ID_CARD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CID_CARDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CID_CARDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpendev();
	afx_msg void OnBtnClosedev();
	afx_msg void OnBtnClaContent();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ID_CARDDLG_H__2BA6F527_65A3_4DE7_993B_0EDB88268C11__INCLUDED_)
