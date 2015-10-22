// ID_CARDDlg.h : header file
//

#if !defined(AFX_ID_CARDDLG_H__2BA6F527_65A3_4DE7_993B_0EDB88268C11__INCLUDED_)
#define AFX_ID_CARDDLG_H__2BA6F527_65A3_4DE7_993B_0EDB88268C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WH_KEYBOARD_LL 13
#define WH_MOUSE_LL    14
#define ULONG_PTR ULONG
typedef struct {
  DWORD     vkCode;
  DWORD     scanCode;
  DWORD     flags;
  DWORD     time;
  ULONG_PTR dwExtraInfo;
} KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;
typedef struct {
  POINT     pt;
  DWORD     mouseData;
  DWORD     flags;
  DWORD     time;
  ULONG_PTR dwExtraInfo;
} MSLLHOOKSTRUCT, *PMSLLHOOKSTRUCT;
/////////////////////////////////////////////////////////////////////////////
// CID_CARDDlg dialog

class CID_CARDDlg : public CDialog
{
// Construction
private:
	void *m_pDlgQuery;
	CString sPhotoPath;
	CString sInfoPath;
public:
	_variant_t RecordsAffected;
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;
	CString GetLastPath(CString ReadMePath,CString &LastPath);
	int InitComm();
	HANDLE m_hThread;
	HANDLE m_hHookThread;
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
	afx_msg void OnBtnSelctphodir();
	afx_msg void OnBtnIdcardExcel();
	afx_msg void OnButtonTest();
	afx_msg void OnBtnClosehook();
	afx_msg void OnClose();
	afx_msg void OnBtnOpenquery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ID_CARDDLG_H__2BA6F527_65A3_4DE7_993B_0EDB88268C11__INCLUDED_)
