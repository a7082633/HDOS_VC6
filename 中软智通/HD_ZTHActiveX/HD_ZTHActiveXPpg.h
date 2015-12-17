#if !defined(AFX_HD_ZTHACTIVEXPPG_H__A93F924D_DFEC_4717_86F1_9B1CE7776D64__INCLUDED_)
#define AFX_HD_ZTHACTIVEXPPG_H__A93F924D_DFEC_4717_86F1_9B1CE7776D64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHActiveXPpg.h : Declaration of the CHD_ZTHActiveXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXPropPage : See HD_ZTHActiveXPpg.cpp.cpp for implementation.

class CHD_ZTHActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CHD_ZTHActiveXPropPage)
	DECLARE_OLECREATE_EX(CHD_ZTHActiveXPropPage)

// Constructor
public:
	CHD_ZTHActiveXPropPage();

// Dialog Data
	//{{AFX_DATA(CHD_ZTHActiveXPropPage)
	enum { IDD = IDD_PROPPAGE_HD_ZTHACTIVEX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CHD_ZTHActiveXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHACTIVEXPPG_H__A93F924D_DFEC_4717_86F1_9B1CE7776D64__INCLUDED)
