// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D7AA0354_AB5C_478D_A430_0DE88FE0855E__INCLUDED_)
#define AFX_STDAFX_H__D7AA0354_AB5C_478D_A430_0DE88FE0855E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include <stdio.h>
#include "MHC_CardInterface.H"
#pragma comment(lib,"WSB_RWInterface.lib")
#include "HD300_V1.H"
#pragma comment(lib,"HD300_V1.lib")
#endif // !defined(AFX_STDAFX_H__D7AA0354_AB5C_478D_A430_0DE88FE0855E__INCLUDED_)
