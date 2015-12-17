#if !defined(AFX_HD_ZTHM1ACTIVEXCTL_H__DA2B9A4D_48E1_465E_AB1C_A7288E1A1CDE__INCLUDED_)
#define AFX_HD_ZTHM1ACTIVEXCTL_H__DA2B9A4D_48E1_465E_AB1C_A7288E1A1CDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHM1ActiveXCtl.h : Declaration of the CHD_ZTHM1ActiveXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl : See HD_ZTHM1ActiveXCtl.cpp for implementation.

class CHD_ZTHM1ActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CHD_ZTHM1ActiveXCtrl)

// Constructor
public:
	CHD_ZTHM1ActiveXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ZTHM1ActiveXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CHD_ZTHM1ActiveXCtrl();

	DECLARE_OLECREATE_EX(CHD_ZTHM1ActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHD_ZTHM1ActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHD_ZTHM1ActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHD_ZTHM1ActiveXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CHD_ZTHM1ActiveXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CHD_ZTHM1ActiveXCtrl)
	afx_msg BSTR HDWriteM1(LPCTSTR Key, LPCTSTR Name, LPCTSTR Sex, LPCTSTR IDNo, LPCTSTR Born, LPCTSTR CardNo, LPCTSTR MakeCDT);
	afx_msg BSTR HDReadM1(LPCTSTR Key, LPCTSTR Addr);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CHD_ZTHM1ActiveXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CHD_ZTHM1ActiveXCtrl)
	dispidHDWriteM1 = 1L,
	dispidHDReadM1 = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHM1ACTIVEXCTL_H__DA2B9A4D_48E1_465E_AB1C_A7288E1A1CDE__INCLUDED)
