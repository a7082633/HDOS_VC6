#if !defined(AFX_HD_CPUANDIDCTL_H__3F9DC6B1_DD96_4152_9221_2A75404977C8__INCLUDED_)
#define AFX_HD_CPUANDIDCTL_H__3F9DC6B1_DD96_4152_9221_2A75404977C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_CPUAndIDCtl.h : Declaration of the CHD_CPUAndIDCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl : See HD_CPUAndIDCtl.cpp for implementation.

class CHD_CPUAndIDCtrl : public COleControl
{
	DECLARE_DYNCREATE(CHD_CPUAndIDCtrl)

// Constructor
public:
	CHD_CPUAndIDCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_CPUAndIDCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	long ReaderHandle;
	~CHD_CPUAndIDCtrl();

	DECLARE_OLECREATE_EX(CHD_CPUAndIDCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHD_CPUAndIDCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHD_CPUAndIDCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHD_CPUAndIDCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CHD_CPUAndIDCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CHD_CPUAndIDCtrl)
	afx_msg BSTR ReaderOpen();
	afx_msg void ReaderClose();
	afx_msg BSTR ICCPowerOn();
	afx_msg BSTR ICCPowerOff();
	afx_msg BSTR ICCReaderApplicationHEX(LPCTSTR Command_APDU);
	afx_msg BSTR ReadIDCard(LPCTSTR PicPath);
	afx_msg BSTR GetInputPass(long ctime);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CHD_CPUAndIDCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CHD_CPUAndIDCtrl)
	dispidReaderOpen = 1L,
	dispidReaderClose = 2L,
	dispidICCPowerOn = 3L,
	dispidICCPowerOff = 4L,
	dispidICCReaderApplicationHEX = 5L,
	dispidReadIDCard = 6L,
	dispidGetInputPass = 7L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_CPUANDIDCTL_H__3F9DC6B1_DD96_4152_9221_2A75404977C8__INCLUDED)
