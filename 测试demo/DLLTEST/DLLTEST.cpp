// DLLTEST.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "DLLTEST.H"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch(ul_reason_for_call) 
	{
	case DLL_PROCESS_ATTACH:
		::MessageBox(NULL,"start",NULL,MB_OK);
		//The DLL is being mapped into the process's address space.
		break;
		
	case DLL_THREAD_ATTACH:
		//A thread is being created.
		break;
		
	case DLL_THREAD_DETACH:
		//A thread is exiting cleanly.
		break;
		
	case DLL_PROCESS_DETACH:
		//The DLL is being unmapped from the process's address space.
		::MessageBox(NULL,"exit",NULL,MB_OK);
		break;
	}
    return TRUE;
}
int __stdcall justtest()
{
	::MessageBox(NULL,"fun_call",NULL,MB_OK);
	return 0;
}
