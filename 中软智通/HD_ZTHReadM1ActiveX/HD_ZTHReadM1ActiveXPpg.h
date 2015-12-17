#if !defined(AFX_HD_ZTHREADM1ACTIVEXPPG_H__3F2631BD_B413_4310_BB77_A5D6F955347D__INCLUDED_)
#define AFX_HD_ZTHREADM1ACTIVEXPPG_H__3F2631BD_B413_4310_BB77_A5D6F955347D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHReadM1ActiveXPpg.h : Declaration of the CHD_ZTHReadM1ActiveXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXPropPage : See HD_ZTHReadM1ActiveXPpg.cpp.cpp for implementation.

class CHD_ZTHReadM1ActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CHD_ZTHReadM1ActiveXPropPage)
	DECLARE_OLECREATE_EX(CHD_ZTHReadM1ActiveXPropPage)

// Constructor
public:
	CHD_ZTHReadM1ActiveXPropPage();

// Dialog Data
	//{{AFX_DATA(CHD_ZTHReadM1ActiveXPropPage)
	enum { IDD = IDD_PROPPAGE_HD_ZTHREADM1ACTIVEX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CHD_ZTHReadM1ActiveXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHREADM1ACTIVEXPPG_H__3F2631BD_B413_4310_BB77_A5D6F955347D__INCLUDED)
