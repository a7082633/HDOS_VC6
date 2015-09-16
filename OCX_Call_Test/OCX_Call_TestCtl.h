#if !defined(AFX_OCX_CALL_TESTCTL_H__BF6DDCEE_CF6C_4CC8_8987_ABDA035B8E48__INCLUDED_)
#define AFX_OCX_CALL_TESTCTL_H__BF6DDCEE_CF6C_4CC8_8987_ABDA035B8E48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCX_Call_TestCtl.h : Declaration of the COCX_Call_TestCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl : See OCX_Call_TestCtl.cpp for implementation.

class COCX_Call_TestCtrl : public COleControl
{
	DECLARE_DYNCREATE(COCX_Call_TestCtrl)

// Constructor
public:
	COCX_Call_TestCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCX_Call_TestCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~COCX_Call_TestCtrl();

	DECLARE_OLECREATE_EX(COCX_Call_TestCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(COCX_Call_TestCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(COCX_Call_TestCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(COCX_Call_TestCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(COCX_Call_TestCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(COCX_Call_TestCtrl)
	afx_msg BSTR ReadSam();
	afx_msg BSTR ReadID();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(COCX_Call_TestCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(COCX_Call_TestCtrl)
	dispidReadSam = 1L,
	dispidReadID = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCX_CALL_TESTCTL_H__BF6DDCEE_CF6C_4CC8_8987_ABDA035B8E48__INCLUDED)
