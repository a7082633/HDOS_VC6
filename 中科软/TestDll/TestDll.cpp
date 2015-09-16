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

RHCARDREADERAPI int Test()
{
	int i=iDOpenPort();
	int hDev=0;
	char info[1024]={0};
	i=iReader_SAM_Public(hDev,info);//该函数取得SAM卡片公共信息文件
	i=iDClosePort();
	return i;
}