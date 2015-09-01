#if !defined(AFX_HD_HNOCXPPG_H__C442CA8B_036F_4C1E_B0F5_DE8FFF9D1CB4__INCLUDED_)
#define AFX_HD_HNOCXPPG_H__C442CA8B_036F_4C1E_B0F5_DE8FFF9D1CB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_HNOCXPpg.h : Declaration of the CHD_HNOCXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXPropPage : See HD_HNOCXPpg.cpp.cpp for implementation.

class CHD_HNOCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CHD_HNOCXPropPage)
	DECLARE_OLECREATE_EX(CHD_HNOCXPropPage)

// Constructor
public:
	CHD_HNOCXPropPage();

// Dialog Data
	//{{AFX_DATA(CHD_HNOCXPropPage)
	enum { IDD = IDD_PROPPAGE_HD_HNOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CHD_HNOCXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_HNOCXPPG_H__C442CA8B_036F_4C1E_B0F5_DE8FFF9D1CB4__INCLUDED)
