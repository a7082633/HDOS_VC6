#if !defined(AFX_TESTOCXPPG_H__8B92FEAE_0125_4757_8FA3_322DC80E039A__INCLUDED_)
#define AFX_TESTOCXPPG_H__8B92FEAE_0125_4757_8FA3_322DC80E039A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TestOcxPpg.h : Declaration of the CTestOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CTestOcxPropPage : See TestOcxPpg.cpp.cpp for implementation.

class CTestOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTestOcxPropPage)
	DECLARE_OLECREATE_EX(CTestOcxPropPage)

// Constructor
public:
	CTestOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CTestOcxPropPage)
	enum { IDD = IDD_PROPPAGE_TESTOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CTestOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTOCXPPG_H__8B92FEAE_0125_4757_8FA3_322DC80E039A__INCLUDED)
