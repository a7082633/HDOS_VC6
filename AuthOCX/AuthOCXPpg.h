#if !defined(AFX_AUTHOCXPPG_H__41F99641_ED61_4745_84CA_CFBC0C60DC18__INCLUDED_)
#define AFX_AUTHOCXPPG_H__41F99641_ED61_4745_84CA_CFBC0C60DC18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// AuthOCXPpg.h : Declaration of the CAuthOCXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CAuthOCXPropPage : See AuthOCXPpg.cpp.cpp for implementation.

class CAuthOCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CAuthOCXPropPage)
	DECLARE_OLECREATE_EX(CAuthOCXPropPage)

// Constructor
public:
	CAuthOCXPropPage();

// Dialog Data
	//{{AFX_DATA(CAuthOCXPropPage)
	enum { IDD = IDD_PROPPAGE_AUTHOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CAuthOCXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHOCXPPG_H__41F99641_ED61_4745_84CA_CFBC0C60DC18__INCLUDED)
