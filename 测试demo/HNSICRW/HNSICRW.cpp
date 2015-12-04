// HNSICRW.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HNSICRW.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

long WINAPI Run(char* flag,char*data,char*err)
{
	::MessageBox(NULL,"≤‚ ‘≥…π¶!",NULL,MB_OK);//
	return 0;
}