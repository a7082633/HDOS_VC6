// HD_IDAndM1_DLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_IDAndM1_DLL.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

long __stdcall Reader_Open()
{
	long Handle=ICC_Reader_Open("USB1");
	return Handle;
}
long __stdcall Reader_Close(long ReaderHandle)
{
	int i=ICC_Reader_Close(ReaderHandle);
	return i;
}
int __stdcall Find_M1Card(long ReaderHandle,unsigned char *uid)
{
	int i=PICC_Reader_Request(ReaderHandle);
	if(i!=0)
		return -1;
	unsigned char Uid[20]={0};
	i=PICC_Reader_anticoll(ReaderHandle,Uid);
	if(i!=0)
		return -2;
	i=PICC_Reader_Select(ReaderHandle,0x41);
	if(i!=0)
		return -3;
	strrev((char *)Uid);

	unsigned long t=0;
	memcpy(&t,Uid,4);
	sprintf((char *)uid,"%u",t);
	return 0;
}
long __stdcall Authentication_Pass(long ReaderHandle,unsigned char Mode, unsigned char SecNr,unsigned char *PassWord)
{
	int i=PICC_Reader_Authentication_Pass(ReaderHandle,Mode,SecNr,PassWord);
	if(i!=0)
		return -4;
	return 0;
}
long __stdcall Reader_Read(long  ReaderHandle,unsigned char Addr, unsigned  char *Data)
{
	int i=PICC_Reader_Read(ReaderHandle,Addr,Data);	//读取卡片M1
	if(i!=0)
		return -5;
	return 0;
}
long __stdcall Reader_Write(long ReaderHandle,unsigned char Addr,unsigned char *Data)
{
	int i=PICC_Reader_Write(ReaderHandle,Addr,Data);//写入数据M1
	if(i!=0)
		return -6;
	return 0;
}
int __stdcall Reader_ReadIdCard(const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire)
{
	int i=HD_InitComm(1001);
	if(i!=0)
		return i;
	i=HD_Authenticate();
	if(i!=0)
		return i;
	i=HD_Read_BaseMsg(pBmpFile,pName,pSex,pNation,pBirth,pAddress,pCertNo,pDepartment ,pEffectData,pExpire);
	if(i!=0)
		return i;
	return 0;
}