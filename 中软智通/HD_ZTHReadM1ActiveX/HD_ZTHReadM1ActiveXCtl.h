#if !defined(AFX_HD_ZTHREADM1ACTIVEXCTL_H__2E2CE73F_E091_4DC8_B545_5F1F8B698A0A__INCLUDED_)
#define AFX_HD_ZTHREADM1ACTIVEXCTL_H__2E2CE73F_E091_4DC8_B545_5F1F8B698A0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHReadM1ActiveXCtl.h : Declaration of the CHD_ZTHReadM1ActiveXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl : See HD_ZTHReadM1ActiveXCtl.cpp for implementation.

class CHD_ZTHReadM1ActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CHD_ZTHReadM1ActiveXCtrl)

// Constructor
public:
	CHD_ZTHReadM1ActiveXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ZTHReadM1ActiveXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CHD_ZTHReadM1ActiveXCtrl();

	DECLARE_OLECREATE_EX(CHD_ZTHReadM1ActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHD_ZTHReadM1ActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHD_ZTHReadM1ActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHD_ZTHReadM1ActiveXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CHD_ZTHReadM1ActiveXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CHD_ZTHReadM1ActiveXCtrl)
	afx_msg BSTR HDReadM1(LPCTSTR Key, LPCTSTR Addr);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CHD_ZTHReadM1ActiveXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CHD_ZTHReadM1ActiveXCtrl)
	dispidHDReadM1 = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHREADM1ACTIVEXCTL_H__2E2CE73F_E091_4DC8_B545_5F1F8B698A0A__INCLUDED)
