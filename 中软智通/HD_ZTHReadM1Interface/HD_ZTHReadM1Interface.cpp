// HD_ZTHReadM1Interface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include  "HD_ZTHReadM1Interface.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int __stdcall HD_ReadM1(char *Key,char *Addr,char *DataOut,char *pErr)
{
	//¡Ÿ ±ø®
	long ReaderHandle=ICC_Reader_Open("USB1");
	if(ReaderHandle<=0)
	{
		sprintf(pErr,"(¡Ÿ ±ø®)¥Úø™∂Àø⁄ ß∞‹,¥ÌŒÛ¥˙¬Î:%d",ReaderHandle);
		return 1;
	}
	int ret=PICC_Reader_Request(ReaderHandle);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(¡Ÿ ±ø®)«Î«Ûø®∆¨ ß∞‹,¥ÌŒÛ¥˙¬Î:%d",ret);
		return 1;
	}
	unsigned char uid[50]={0};
	ret=PICC_Reader_anticoll(ReaderHandle,uid);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(¡Ÿ ±ø®)∑¿≈ˆ◊≤ ß∞‹,¥ÌŒÛ¥˙¬Î:%d",ret);
		return 1;
	}
	ret=PICC_Reader_Select(ReaderHandle,0x41);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(¡Ÿ ±ø®)—°ø® ß∞‹,¥ÌŒÛ¥˙¬Î:%d",ret);
		return 1;
	}
	unsigned char key[10]={0};
	StrToHex((unsigned char*)Key,12,key);//Ω´◊÷∑˚√¸¡Ó¡˜◊™Œ™16Ω¯÷∆¡˜
	int iAddr=atoi(Addr);
	int sq=iAddr/4;
	ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,sq,key);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(¡Ÿ ±ø®)»œ÷§…»«¯%d√‹¬Î ß∞‹,¥ÌŒÛ¥˙¬Î:%d",sq,ret);
		return 1;
	}
	unsigned char DataHex[100]={0};
	ret=PICC_Reader_ReadHEX(ReaderHandle,iAddr,DataHex);
	if(ret!=0)
	{
		ICC_Reader_Close(ReaderHandle);
		sprintf(pErr,"(¡Ÿ ±ø®)∂¡%døÈ ß∞‹,¥ÌŒÛ¥˙¬Î:%d",iAddr,ret);
		return 1;
	}
	strcpy(DataOut,(char *)DataHex);
	ICC_Reader_Close(ReaderHandle);
	return 0;
}