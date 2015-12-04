#if !defined(AFX_HD_SHHEALTHYACXPPG_H__3AAD9F25_72AF_4C52_A3C0_1FC1F18EF9E8__INCLUDED_)
#define AFX_HD_SHHEALTHYACXPPG_H__3AAD9F25_72AF_4C52_A3C0_1FC1F18EF9E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_SHHealthyACXPpg.h : Declaration of the CHD_SHHealthyACXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXPropPage : See HD_SHHealthyACXPpg.cpp.cpp for implementation.

class CHD_SHHealthyACXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CHD_SHHealthyACXPropPage)
	DECLARE_OLECREATE_EX(CHD_SHHealthyACXPropPage)

// Constructor
public:
	CHD_SHHealthyACXPropPage();

// Dialog Data
	//{{AFX_DATA(CHD_SHHealthyACXPropPage)
	enum { IDD = IDD_PROPPAGE_HD_SHHEALTHYACX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CHD_SHHealthyACXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_SHHEALTHYACXPPG_H__3AAD9F25_72AF_4C52_A3C0_1FC1F18EF9E8__INCLUDED)
