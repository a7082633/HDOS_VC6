#if !defined(AFX_TESTOCXCTL_H__A6DB2F99_BB50_42D5_BE5A_F9F1A17AE23F__INCLUDED_)
#define AFX_TESTOCXCTL_H__A6DB2F99_BB50_42D5_BE5A_F9F1A17AE23F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TestOcxCtl.h : Declaration of the CTestOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl : See TestOcxCtl.cpp for implementation.

class CTestOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTestOcxCtrl)

// Constructor
public:
	CTestOcxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CTestOcxCtrl();

	DECLARE_OLECREATE_EX(CTestOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CTestOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTestOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CTestOcxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CTestOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CTestOcxCtrl)
	afx_msg BSTR ReadID();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CTestOcxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CTestOcxCtrl)
	dispidReadID = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTOCXCTL_H__A6DB2F99_BB50_42D5_BE5A_F9F1A17AE23F__INCLUDED)
