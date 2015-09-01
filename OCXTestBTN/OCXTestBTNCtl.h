#if !defined(AFX_OCXTESTBTNCTL_H__A0C3A098_53EA_4434_9BF6_0333EBA22278__INCLUDED_)
#define AFX_OCXTESTBTNCTL_H__A0C3A098_53EA_4434_9BF6_0333EBA22278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCXTestBTNCtl.h : Declaration of the COCXTestBTNCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl : See OCXTestBTNCtl.cpp for implementation.

class COCXTestBTNCtrl : public COleControl
{
	DECLARE_DYNCREATE(COCXTestBTNCtrl)

// Constructor
public:
	COCXTestBTNCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCXTestBTNCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~COCXTestBTNCtrl();

	DECLARE_OLECREATE_EX(COCXTestBTNCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(COCXTestBTNCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(COCXTestBTNCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(COCXTestBTNCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(COCXTestBTNCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(COCXTestBTNCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(COCXTestBTNCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(COCXTestBTNCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXTESTBTNCTL_H__A0C3A098_53EA_4434_9BF6_0333EBA22278__INCLUDED)
