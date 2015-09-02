// HealthCardReaderDlg.h : header file
//

#if !defined(AFX_HEALTHCARDREADERDLG_H__C76EAB98_7FDC_4CE1_AE95_8E44B9B1E51F__INCLUDED_)
#define AFX_HEALTHCARDREADERDLG_H__C76EAB98_7FDC_4CE1_AE95_8E44B9B1E51F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHealthCardReaderDlg dialog

class CHealthCardReaderDlg : public CDialog
{
// Construction
public:
	HANDLE hDev;
	CHealthCardReaderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHealthCardReaderDlg)
	enum { IDD = IDD_HEALTHCARDREADER_DIALOG };
	CComboBox	m_comboOutpatientInfo;
	CComboBox	m_comboInhospitalInfo;
	CComboBox	m_comboOutpatient;
	CComboBox	m_comboInHospital;
	CComboBox	m_comboImmune;
	CComboBox	m_comboAllergy;
	CString	m_sData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHealthCardReaderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHealthCardReaderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConnectDev();
	afx_msg void OnBtnCloseDev();
	afx_msg void OnBtnPsamOn();
	afx_msg void OnBtnVerifyPin();
	afx_msg void OnBtnHealthOn();
	afx_msg void OnBtnReadPublishinfo();
	afx_msg void OnBtnWritePublishinfo();
	afx_msg void OnBtnReadPersoninfo();
	afx_msg void OnBtnWritePersoninfo();
	afx_msg void OnBtnReadPic();
	afx_msg void OnBtnWritePic();
	afx_msg void OnBtnReadOwnerinfo();
	afx_msg void OnBtnWriteOwnerinfo();
	afx_msg void OnBtnReadAddrinfo();
	afx_msg void OnBtnWriteAddrinfo();
	afx_msg void OnBtnReadRelativeinfo();
	afx_msg void OnBtnWriteRelativeinfo();
	afx_msg void OnBtnReadJobmarryinfo();
	afx_msg void OnBtnWriteJobmarryinfo();
	afx_msg void OnBtnReadLicenceinfo();
	afx_msg void OnBtnWriteLicenceinfo();
	afx_msg void OnBtnReadClinicalinfo();
	afx_msg void OnBtnWriteClinicalinfo();
	afx_msg void OnBtnReadSpecialinfo();
	afx_msg void OnBtnWriteSpecialinfo();
	afx_msg void OnBtnReadAllergyRecord();
	afx_msg void OnBtnAddAllergyRecord();
	afx_msg void OnBtnReadImmuneRecord();
	afx_msg void OnBtnAddImmuneRecord();
	afx_msg void OnBtnReadInhospitalRecord();
	afx_msg void OnBtnWriteInhospitalRecord();
	afx_msg void OnBtnClearInhospitalRecord();
	afx_msg void OnBtnReadOutpatientRecord();
	afx_msg void OnBtnWriteOutpatientRecord();
	afx_msg void OnBtnClearOutpatientRecord();
	afx_msg void OnBtnReadInhospitalinfo();
	afx_msg void OnBtnWriteInhospitalinfo();
	afx_msg void OnBtnReadAllinhospitalinfo();
	afx_msg void OnBtnWriteAllinhospitalinfo();
	afx_msg void OnBtnReadOutpatientinfo();
	afx_msg void OnBtnReadAlloutpatientinfo();
	afx_msg void OnBtnWriteOutpatientinfo();
	afx_msg void OnBtnWriteAlloutpatientinfo();
	afx_msg void OnBtnPsamOrgCer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEALTHCARDREADERDLG_H__C76EAB98_7FDC_4CE1_AE95_8E44B9B1E51F__INCLUDED_)
