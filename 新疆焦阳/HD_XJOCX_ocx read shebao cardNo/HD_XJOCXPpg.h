#if !defined(AFX_HD_XJOCXPPG_H__ED89EC44_ABEE_4D92_B934_FC60051F1B99__INCLUDED_)
#define AFX_HD_XJOCXPPG_H__ED89EC44_ABEE_4D92_B934_FC60051F1B99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_XJOCXPpg.h : Declaration of the CHD_XJOCXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXPropPage : See HD_XJOCXPpg.cpp.cpp for implementation.

class CHD_XJOCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CHD_XJOCXPropPage)
	DECLARE_OLECREATE_EX(CHD_XJOCXPropPage)

// Constructor
public:
	CHD_XJOCXPropPage();

// Dialog Data
	//{{AFX_DATA(CHD_XJOCXPropPage)
	enum { IDD = IDD_PROPPAGE_HD_XJOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CHD_XJOCXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_XJOCXPPG_H__ED89EC44_ABEE_4D92_B934_FC60051F1B99__INCLUDED)
