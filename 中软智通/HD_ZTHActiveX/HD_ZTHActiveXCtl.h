#if !defined(AFX_HD_ZTHACTIVEXCTL_H__904EEAA5_BEF2_4236_8743_7DCFB0B3A0D9__INCLUDED_)
#define AFX_HD_ZTHACTIVEXCTL_H__904EEAA5_BEF2_4236_8743_7DCFB0B3A0D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHActiveXCtl.h : Declaration of the CHD_ZTHActiveXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl : See HD_ZTHActiveXCtl.cpp for implementation.

class CHD_ZTHActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CHD_ZTHActiveXCtrl)

// Constructor
public:
	CHD_ZTHActiveXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ZTHActiveXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CHD_ZTHActiveXCtrl();

	DECLARE_OLECREATE_EX(CHD_ZTHActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHD_ZTHActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHD_ZTHActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHD_ZTHActiveXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CHD_ZTHActiveXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CHD_ZTHActiveXCtrl)
	afx_msg BSTR HDCloseDevice();
	afx_msg BSTR HDReadCardInfo(LPCTSTR Key);
	afx_msg BSTR HDOpenDevice(LPCTSTR PIN);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CHD_ZTHActiveXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CHD_ZTHActiveXCtrl)
	dispidHDCloseDevice = 1L,
	dispidHDReadCardInfo = 2L,
	dispidHDOpenDevice = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHACTIVEXCTL_H__904EEAA5_BEF2_4236_8743_7DCFB0B3A0D9__INCLUDED)
