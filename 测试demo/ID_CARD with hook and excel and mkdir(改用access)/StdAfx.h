// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2B588349_1275_4666_8682_8E9B843F5E68__INCLUDED_)
#define AFX_STDAFX_H__2B588349_1275_4666_8682_8E9B843F5E68__INCLUDED_

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
#include "HDstdapi.h"
#pragma comment(lib, "HDstdapi.lib")
#include <winable.h>
#include <atlconv.h>
#include "Shlwapi.h"
#pragma comment(lib,"Shlwapi.lib") /*需要加上此行才可以正确link，VC6.0*/
#include "COMUTIL.H"
#pragma comment(lib, "comsupp.lib")
#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace rename("EOF","adoEOF"),rename("Parameters","adoParameters"),rename("Errors","adoErrors"),rename("Error","adoError")
//#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll"  no_namespace rename("EOF","adoEOF")
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2B588349_1275_4666_8682_8E9B843F5E68__INCLUDED_)
