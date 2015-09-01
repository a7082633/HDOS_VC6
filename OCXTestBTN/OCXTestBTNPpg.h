#if !defined(AFX_OCXTESTBTNPPG_H__A04F1CA7_3543_49A8_AA6F_3A25A3B0D2CB__INCLUDED_)
#define AFX_OCXTESTBTNPPG_H__A04F1CA7_3543_49A8_AA6F_3A25A3B0D2CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCXTestBTNPpg.h : Declaration of the COCXTestBTNPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// COCXTestBTNPropPage : See OCXTestBTNPpg.cpp.cpp for implementation.

class COCXTestBTNPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(COCXTestBTNPropPage)
	DECLARE_OLECREATE_EX(COCXTestBTNPropPage)

// Constructor
public:
	COCXTestBTNPropPage();

// Dialog Data
	//{{AFX_DATA(COCXTestBTNPropPage)
	enum { IDD = IDD_PROPPAGE_OCXTESTBTN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(COCXTestBTNPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXTESTBTNPPG_H__A04F1CA7_3543_49A8_AA6F_3A25A3B0D2CB__INCLUDED)
