#if !defined(AFX_HD_CPUANDIDPPG_H__3E7EA286_A75F_40B3_8F20_4A3B258959BB__INCLUDED_)
#define AFX_HD_CPUANDIDPPG_H__3E7EA286_A75F_40B3_8F20_4A3B258959BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_CPUAndIDPpg.h : Declaration of the CHD_CPUAndIDPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDPropPage : See HD_CPUAndIDPpg.cpp.cpp for implementation.

class CHD_CPUAndIDPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CHD_CPUAndIDPropPage)
	DECLARE_OLECREATE_EX(CHD_CPUAndIDPropPage)

// Constructor
public:
	CHD_CPUAndIDPropPage();

// Dialog Data
	//{{AFX_DATA(CHD_CPUAndIDPropPage)
	enum { IDD = IDD_PROPPAGE_HD_CPUANDID };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CHD_CPUAndIDPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_CPUANDIDPPG_H__3E7EA286_A75F_40B3_8F20_4A3B258959BB__INCLUDED)
