// TestDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "TestDll.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

MHC_CARDINTERFACE_API int __stdcall WriteData(char * data)
{
	data="hello world";
	return 0;
}