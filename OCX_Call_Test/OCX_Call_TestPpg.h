#if !defined(AFX_OCX_CALL_TESTPPG_H__60D75A3C_985D_4E22_BE91_8B993211CB41__INCLUDED_)
#define AFX_OCX_CALL_TESTPPG_H__60D75A3C_985D_4E22_BE91_8B993211CB41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCX_Call_TestPpg.h : Declaration of the COCX_Call_TestPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestPropPage : See OCX_Call_TestPpg.cpp.cpp for implementation.

class COCX_Call_TestPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(COCX_Call_TestPropPage)
	DECLARE_OLECREATE_EX(COCX_Call_TestPropPage)

// Constructor
public:
	COCX_Call_TestPropPage();

// Dialog Data
	//{{AFX_DATA(COCX_Call_TestPropPage)
	enum { IDD = IDD_PROPPAGE_OCX_CALL_TEST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(COCX_Call_TestPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCX_CALL_TESTPPG_H__60D75A3C_985D_4E22_BE91_8B993211CB41__INCLUDED)
