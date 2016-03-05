// SSSE32IDCard_ReadDlg.h : header file
//

#if !defined(AFX_SSSE32IDCARD_READDLG_H__C3C213D3_8EE6_484C_9721_48A36AAE1D83__INCLUDED_)
#define AFX_SSSE32IDCARD_READDLG_H__C3C213D3_8EE6_484C_9721_48A36AAE1D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSSSE32IDCard_ReadDlg dialog

class CSSSE32IDCard_ReadDlg : public CDialog
{
// Construction
public:
	long handler;
	CSSSE32IDCard_ReadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSSSE32IDCard_ReadDlg)
	enum { IDD = IDD_SSSE32IDCARD_READ_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSSE32IDCard_ReadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSSSE32IDCard_ReadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnClose();
	afx_msg void OnBtnFindcard();
	afx_msg void OnBtnSelectc();
	afx_msg void OnBtnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSSE32IDCARD_READDLG_H__C3C213D3_8EE6_484C_9721_48A36AAE1D83__INCLUDED_)
