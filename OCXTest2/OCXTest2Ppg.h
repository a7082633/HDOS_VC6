#if !defined(AFX_OCXTEST2PPG_H__5ED262A8_125B_4088_B613_A7DC0A1AA187__INCLUDED_)
#define AFX_OCXTEST2PPG_H__5ED262A8_125B_4088_B613_A7DC0A1AA187__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCXTest2Ppg.h : Declaration of the COCXTest2PropPage property page class.

////////////////////////////////////////////////////////////////////////////
// COCXTest2PropPage : See OCXTest2Ppg.cpp.cpp for implementation.

class COCXTest2PropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(COCXTest2PropPage)
	DECLARE_OLECREATE_EX(COCXTest2PropPage)

// Constructor
public:
	COCXTest2PropPage();

// Dialog Data
	//{{AFX_DATA(COCXTest2PropPage)
	enum { IDD = IDD_PROPPAGE_OCXTEST2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(COCXTest2PropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXTEST2PPG_H__5ED262A8_125B_4088_B613_A7DC0A1AA187__INCLUDED)
