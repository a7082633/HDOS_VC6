#if !defined(AFX_OCXTEST2CTL_H__AAF0717A_5B01_4F6E_A56D_1DA66A9593B2__INCLUDED_)
#define AFX_OCXTEST2CTL_H__AAF0717A_5B01_4F6E_A56D_1DA66A9593B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCXTest2Ctl.h : Declaration of the COCXTest2Ctrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl : See OCXTest2Ctl.cpp for implementation.

class COCXTest2Ctrl : public COleControl
{
	DECLARE_DYNCREATE(COCXTest2Ctrl)

// Constructor
public:
	COCXTest2Ctrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCXTest2Ctrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~COCXTest2Ctrl();

	BEGIN_OLEFACTORY(COCXTest2Ctrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(COCXTest2Ctrl)

	DECLARE_OLETYPELIB(COCXTest2Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(COCXTest2Ctrl)     // Property page IDs
	DECLARE_OLECTLTYPE(COCXTest2Ctrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(COCXTest2Ctrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(COCXTest2Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(COCXTest2Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(COCXTest2Ctrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXTEST2CTL_H__AAF0717A_5B01_4F6E_A56D_1DA66A9593B2__INCLUDED)
