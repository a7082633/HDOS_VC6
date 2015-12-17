// HD_ZTHM1DemoDlg.h : header file
//

#if !defined(AFX_HD_ZTHM1DEMODLG_H__4D051D06_0F54_40B8_A512_B3524609C71F__INCLUDED_)
#define AFX_HD_ZTHM1DEMODLG_H__4D051D06_0F54_40B8_A512_B3524609C71F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1DemoDlg dialog

class CHD_ZTHM1DemoDlg : public CDialog
{
// Construction
public:
	CHD_ZTHM1DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHD_ZTHM1DemoDlg)
	enum { IDD = IDD_HD_ZTHM1DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ZTHM1DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHD_ZTHM1DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	afx_msg void OnBtnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHM1DEMODLG_H__4D051D06_0F54_40B8_A512_B3524609C71F__INCLUDED_)
