// ReaderTestDlg.h : header file
//

#if !defined(AFX_READERTESTDLG_H__9117FC2F_1329_4F60_9058_A154BAFB9222__INCLUDED_)
#define AFX_READERTESTDLG_H__9117FC2F_1329_4F60_9058_A154BAFB9222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReaderTestDlg dialog

class CReaderTestDlg : public CDialog
{
// Construction
public:
	long hReader;
	CReaderTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReaderTestDlg)
	enum { IDD = IDD_READERTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReaderTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReaderTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnBtnReadsbk();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERTESTDLG_H__9117FC2F_1329_4F60_9058_A154BAFB9222__INCLUDED_)