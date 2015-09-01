// HD_XJIDCARDInter.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_XJIDCARDInter.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int __stdcall Reader_ReadIDMsg(const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire,char * pErrMsg)
{
	long ReaderHandle=ICC_Reader_Open("USB1");
	if(ReaderHandle<0) return ReaderHandle;
	int rt = PICC_Reader_ID_Request(ReaderHandle);//身份证寻卡
	if(rt)
	{
		ICC_Reader_Close(ReaderHandle);
		return rt;
	}
	rt = PICC_Reader_ID_Select(ReaderHandle);//身份证选卡
	if(rt)
	{
		ICC_Reader_Close(ReaderHandle);
		return rt;
	}
	rt=PICC_Reader_ReadIDMsg(ReaderHandle,pBmpFile,pName,pSex,pNation,pBirth,pAddress,pCertNo,pDepartment,pEffectData,pExpire,pErrMsg);
	if(rt)
	{
		ICC_Reader_Close(ReaderHandle);
		return rt;
	}
	ICC_Reader_Close(ReaderHandle);
	return 0;
}