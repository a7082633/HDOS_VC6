#if !defined(AFX_DIALOGQUERYDATA_H__9569051E_511D_4BCF_9337_367DFE6DFACC__INCLUDED_)
#define AFX_DIALOGQUERYDATA_H__9569051E_511D_4BCF_9337_367DFE6DFACC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogQueryData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryData dialog

class CDialogQueryData : public CDialog
{
// Construction
public:
	bool isOpenBackup;
	_variant_t RecordsAffected;
	_ConnectionPtr m_pConnection;
	_ConnectionPtr m_pConnection_backup;
	_RecordsetPtr m_pRecordset_backup;
	_RecordsetPtr m_pRecordset;
	CDialogQueryData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogQueryData)
	enum { IDD = IDD_DIALOG_QUERYDATA };
	CComboBox	m_combo_exp;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogQueryData)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogQueryData)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnShowall();
	afx_msg void OnBtnQuery();
	afx_msg void OnBtnExport();
	afx_msg void OnBtnBackup();
	afx_msg void OnBtnOpenbackup();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGQUERYDATA_H__9569051E_511D_4BCF_9337_367DFE6DFACC__INCLUDED_)
