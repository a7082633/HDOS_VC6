#if !defined(AFX_HD_HNOCXCTL_H__EB128509_28A2_4087_B3AC_2A40B22360F6__INCLUDED_)
#define AFX_HD_HNOCXCTL_H__EB128509_28A2_4087_B3AC_2A40B22360F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_HNOCXCtl.h : Declaration of the CHD_HNOCXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl : See HD_HNOCXCtl.cpp for implementation.

class CHD_HNOCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CHD_HNOCXCtrl)

// Constructor
public:
	CHD_HNOCXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_HNOCXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CHD_HNOCXCtrl();

	DECLARE_OLECREATE_EX(CHD_HNOCXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHD_HNOCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHD_HNOCXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHD_HNOCXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CHD_HNOCXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CHD_HNOCXCtrl)
	CString m_zp;
	afx_msg void OnZpChanged();
	afx_msg BSTR ReadCard(LPCTSTR para, LPCTSTR account, LPCTSTR password, LPCTSTR doctype, LPCTSTR userid, LPCTSTR pin);
	afx_msg long WriteCard(LPCTSTR para, LPCTSTR dataIn, LPCTSTR account, LPCTSTR password, LPCTSTR doctype, LPCTSTR userid, LPCTSTR pin);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CHD_HNOCXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	char pDest[10000];
	enum {
	//{{AFX_DISP_ID(CHD_HNOCXCtrl)
	dispidZp = 1L,
	dispidReadCard = 2L,
	dispidWriteCard = 3L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_HNOCXCTL_H__EB128509_28A2_4087_B3AC_2A40B22360F6__INCLUDED)
