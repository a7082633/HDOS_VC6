#if !defined(AFX_PASSOCXPPG_H__A0AFCEA3_A758_4CCB_B37D_AE4DF59AD022__INCLUDED_)
#define AFX_PASSOCXPPG_H__A0AFCEA3_A758_4CCB_B37D_AE4DF59AD022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PassOcxPpg.h : Declaration of the CPassOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPassOcxPropPage : See PassOcxPpg.cpp.cpp for implementation.

class CPassOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPassOcxPropPage)
	DECLARE_OLECREATE_EX(CPassOcxPropPage)

// Constructor
public:
	CPassOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CPassOcxPropPage)
	enum { IDD = IDD_PROPPAGE_PASSOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPassOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSOCXPPG_H__A0AFCEA3_A758_4CCB_B37D_AE4DF59AD022__INCLUDED)
