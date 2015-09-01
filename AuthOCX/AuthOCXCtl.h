#if !defined(AFX_AUTHOCXCTL_H__E82C8E09_98EC_4715_A2A4_EED2D9ADAEE6__INCLUDED_)
#define AFX_AUTHOCXCTL_H__E82C8E09_98EC_4715_A2A4_EED2D9ADAEE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// AuthOCXCtl.h : Declaration of the CAuthOCXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl : See AuthOCXCtl.cpp for implementation.

class CAuthOCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CAuthOCXCtrl)

// Constructor
public:
	CAuthOCXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuthOCXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CAuthOCXCtrl();

	DECLARE_OLECREATE_EX(CAuthOCXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CAuthOCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CAuthOCXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CAuthOCXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CAuthOCXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CAuthOCXCtrl)
	afx_msg BSTR TestAu(LPCTSTR addr, LPCTSTR account, LPCTSTR password, short doctype, short action);
	afx_msg BSTR TestAu2(LPCTSTR addr, LPCTSTR account, LPCTSTR password);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CAuthOCXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CAuthOCXCtrl)
	dispidTestAu = 1L,
	dispidTestAu2 = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHOCXCTL_H__E82C8E09_98EC_4715_A2A4_EED2D9ADAEE6__INCLUDED)
