// PCSC DemoDlg.h : header file
//

#if !defined(AFX_PCSCDEMODLG_H__85663F32_7F50_4D82_98D9_89E5A1E5BA81__INCLUDED_)
#define AFX_PCSCDEMODLG_H__85663F32_7F50_4D82_98D9_89E5A1E5BA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPCSCDemoDlg dialog

class CPCSCDemoDlg : public CDialog
{
private:
	SCARDCONTEXT hSC;
	LONG lReturn;
	char mszReaders[1024];
	LPTSTR pReader,pReaderName[2];
	DWORD dwLen;
	int nReaders,nCurrentReader;
	SCARDHANDLE hCardHandle[2];
	DWORD dwAP;
// Construction
public:
	CPCSCDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPCSCDemoDlg)
	enum { IDD = IDD_PCSCDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCSCDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPCSCDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnTest();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnOpendev();
	afx_msg void OnBtnClosedev();
	afx_msg void OnBtnExcapdu();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCSCDEMODLG_H__85663F32_7F50_4D82_98D9_89E5A1E5BA81__INCLUDED_)
