// HD_HDRWInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_HDRWInterface.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

HD_HDRWINTERFACE_API int __stdcall test(void)
{
	::MessageBox(NULL,"HAHA",NULL,MB_OK);
	return 0;
}