#if !defined(AFX_HD_XJOCXCTL_H__91EC715E_D612_4A17_8C1A_4E036ED0E5A4__INCLUDED_)
#define AFX_HD_XJOCXCTL_H__91EC715E_D612_4A17_8C1A_4E036ED0E5A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_XJOCXCtl.h : Declaration of the CHD_XJOCXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl : See HD_XJOCXCtl.cpp for implementation.

class CHD_XJOCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CHD_XJOCXCtrl)

// Constructor
public:
	CHD_XJOCXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_XJOCXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CHD_XJOCXCtrl();

	DECLARE_OLECREATE_EX(CHD_XJOCXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CHD_XJOCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CHD_XJOCXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CHD_XJOCXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CHD_XJOCXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CHD_XJOCXCtrl)
	afx_msg BSTR HDGetCardNo();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CHD_XJOCXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CHD_XJOCXCtrl)
	dispidHDGetCardNo = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_XJOCXCTL_H__91EC715E_D612_4A17_8C1A_4E036ED0E5A4__INCLUDED)
