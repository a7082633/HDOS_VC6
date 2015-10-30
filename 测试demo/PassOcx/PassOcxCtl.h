#if !defined(AFX_PASSOCXCTL_H__D4A35550_E592_4366_AC05_D71F3B6300D4__INCLUDED_)
#define AFX_PASSOCXCTL_H__D4A35550_E592_4366_AC05_D71F3B6300D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PassOcxCtl.h : Declaration of the CPassOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl : See PassOcxCtl.cpp for implementation.

class CPassOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPassOcxCtrl)

// Constructor
public:
	CPassOcxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CPassOcxCtrl();

	DECLARE_OLECREATE_EX(CPassOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPassOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPassOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPassOcxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CPassOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPassOcxCtrl)
	afx_msg BSTR GetInputPass();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CPassOcxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CPassOcxCtrl)
	dispidGetInputPass = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSOCXCTL_H__D4A35550_E592_4366_AC05_D71F3B6300D4__INCLUDED)
