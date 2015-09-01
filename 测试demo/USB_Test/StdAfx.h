// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7B96E36C_45A0_4B3C_8EB9_092659F14DD4__INCLUDED_)
#define AFX_STDAFX_H__7B96E36C_45A0_4B3C_8EB9_092659F14DD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

extern "C" {
// Declare the C libraries used
#include "setupapi.h"  // Must link in setupapi.lib
#include "hidsdi.h"   // Must link in hid.lib
}
#pragma comment(lib,"setupapi.lib")
#pragma comment(lib,"hid.lib")
#define V_ID    0x072F
#define P_ID    0x90D5
#define CardCommandT1 0x02
#define CardCommandT2 0x06
#define CardCommandT3 0x08
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7B96E36C_45A0_4B3C_8EB9_092659F14DD4__INCLUDED_)
