#if !defined(AFX_DIALOGWRITEPERSONINFO_H__F2197221_D51A_4C69_86EE_F665D17485B2__INCLUDED_)
#define AFX_DIALOGWRITEPERSONINFO_H__F2197221_D51A_4C69_86EE_F665D17485B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWritePersonInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWritePersonInfo dialog

class CDialogWritePersonInfo : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWritePersonInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWritePersonInfo)
	enum { IDD = IDD_DIALOG_WRITE_PERSONINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWritePersonInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWritePersonInfo)
	afx_msg void OnBtnWrite();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITEPERSONINFO_H__F2197221_D51A_4C69_86EE_F665D17485B2__INCLUDED_)
