#if !defined(AFX_STDAFX_H__B84DDAC7_3311_4F74_B990_5051429CD709__INCLUDED_)
#define AFX_STDAFX_H__B84DDAC7_3311_4F74_B990_5051429CD709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Comon Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#include <afxdb.h>			// MFC database classes
#include <afxdao.h>			// MFC DAO database classes

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include "MHC_CardInterface.h"
#pragma comment(lib,"WSB_RWInterface.lib")
#include "HD300_V1.H"
#pragma comment(lib,"HD300_V1.lib")
#include "Utils.h"
#include "ConvertUtil.h"
#include "StringUtil.h"
#endif // !defined(AFX_STDAFX_H__B84DDAC7_3311_4F74_B990_5051429CD709__INCLUDED_)
