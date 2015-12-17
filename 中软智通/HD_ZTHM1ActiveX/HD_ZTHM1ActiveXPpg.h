#if !defined(AFX_HD_ZTHM1ACTIVEXPPG_H__8540F245_1A06_4012_80DE_163965C3F8E9__INCLUDED_)
#define AFX_HD_ZTHM1ACTIVEXPPG_H__8540F245_1A06_4012_80DE_163965C3F8E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHM1ActiveXPpg.h : Declaration of the CHD_ZTHM1ActiveXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXPropPage : See HD_ZTHM1ActiveXPpg.cpp.cpp for implementation.

class CHD_ZTHM1ActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CHD_ZTHM1ActiveXPropPage)
	DECLARE_OLECREATE_EX(CHD_ZTHM1ActiveXPropPage)

// Constructor
public:
	CHD_ZTHM1ActiveXPropPage();

// Dialog Data
	//{{AFX_DATA(CHD_ZTHM1ActiveXPropPage)
	enum { IDD = IDD_PROPPAGE_HD_ZTHM1ACTIVEX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CHD_ZTHM1ActiveXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHM1ACTIVEXPPG_H__8540F245_1A06_4012_80DE_163965C3F8E9__INCLUDED)
