#if !defined(AFX_DIALOGWRITEALLERGYRECORD_H__BEDE15DF_D43B_4C44_8980_9172B15E0517__INCLUDED_)
#define AFX_DIALOGWRITEALLERGYRECORD_H__BEDE15DF_D43B_4C44_8980_9172B15E0517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogWriteAllergyRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteAllergyRecord dialog

class CDialogWriteAllergyRecord : public CDialog
{
// Construction
public:
	void * pDlg;
	HANDLE hDev;
	CDialogWriteAllergyRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogWriteAllergyRecord)
	enum { IDD = IDD_DIALOG_WRITE_ALLERGY_RECORD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWriteAllergyRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogWriteAllergyRecord)
	virtual void OnOK();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGWRITEALLERGYRECORD_H__BEDE15DF_D43B_4C44_8980_9172B15E0517__INCLUDED_)
