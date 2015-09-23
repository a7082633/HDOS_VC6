
// ExcelTestDlg.h : header file
//

#if !defined(AFX_EXCELTESTDLG_H__B7ABD403_A261_4D17_A8F4_D2DBCD97E8E6__INCLUDED_)
#define AFX_EXCELTESTDLG_H__B7ABD403_A261_4D17_A8F4_D2DBCD97E8E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExcelTestDlg dialog

class CExcelTestDlg : public CDialog
{
// Construction
public:
	CString sInfoPath;
	CExcelTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExcelTestDlg)
	enum { IDD = IDD_EXCELTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExcelTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExceltest();
	afx_msg void OnOpenAdd();
	afx_msg void OnOpenRead();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTESTDLG_H__B7ABD403_A261_4D17_A8F4_D2DBCD97E8E6__INCLUDED_)
