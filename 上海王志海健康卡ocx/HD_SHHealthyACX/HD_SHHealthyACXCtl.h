#if !defined(AFX_HD_SHHEALTHYACXCTL_H__F06EE2D0_140F_466F_BAD0_D3BEA234F529__INCLUDED_)
#define AFX_HD_SHHEALTHYACXCTL_H__F06EE2D0_140F_466F_BAD0_D3BEA234F529__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_SHHealthyACXCtl.h : Declaration of the CHD_SHHealthyACXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl : See HD_SHHealthyACXCtl.cpp for implementation.

class CHD_SHHealthyACXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CHD_SHHealthyACXCtrl)

// Constructor
public:
	CHD_SHHealthyACXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_SHHealthyACXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CHD_SHHealthyACXCtrl();

	DECLARE_OLECREATE_EX(CHD_SHHealthyACXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHD_SHHealthyACXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHD_SHHealthyACXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHD_SHHealthyACXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CHD_SHHealthyACXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CHD_SHHealthyACXCtrl)
	afx_msg BSTR ReadCard();
	afx_msg BSTR ReadInfoOutPatient();
	afx_msg BSTR ReadInfoHospitalization();
	afx_msg BSTR WriteInfoOutPatient(LPCTSTR DataIn);
	afx_msg BSTR WriteInfoHospitalization(LPCTSTR DataIn);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CHD_SHHealthyACXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CHD_SHHealthyACXCtrl)
	dispidReadCard = 1L,
	dispidReadInfoOutPatient = 2L,
	dispidReadInfoHospitalization = 3L,
	dispidWriteInfoOutPatient = 4L,
	dispidWriteInfoHospitalization = 5L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_SHHEALTHYACXCTL_H__F06EE2D0_140F_466F_BAD0_D3BEA234F529__INCLUDED)
