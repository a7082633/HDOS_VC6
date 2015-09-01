// HD_XJDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_XJDLL.H"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int __stdcall HD_GetCardNo(char *dataOut)
{
	char UserNo[0x0A]={0};
	char SHBZHM[0x13]={0};
	char XM[0x1F]={0};
	char XB[0x02]={0};
	char MZ[0x03]={0};
	char CSD[0x07]={0};
	char CSRQ[0x09]={0};
	long hReader=ICC_Reader_Open("USB1");
	if(hReader<=0)//设备打开失败返回
	{
		char *p="打开设备失败";
		strcpy(dataOut,p);
		return hReader;
	}
	//上电
	unsigned char Response[50]={0};
	int rt=ICC_Reader_PowerOn(hReader,0x01,Response);
	if(rt<=0)
	{
		char *p="卡上电失败";
		strcpy(dataOut,p);
		ICC_Reader_Close(hReader);
		return rt;
	}
	//发送选SSSE指令
	unsigned char cmd[100]=
		{0x00,0xA4,0x04,0x00,0x0F,
		0x73,0x78,0x31,0x2E,0x73,
		0x68,0x2E,0xC9,0xE7,0xBB,
		0xE1,0xB1,0xA3,0xD5,0xCF};
	unsigned char ResponseAPDU[200]={0};
    int len=ICC_Reader_Application(hReader,0x01,20,cmd,ResponseAPDU);
	if(len<=0)
	{
		char *p="执行指令失败,00a4 3f00";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return len;
	}
	if( (ResponseAPDU[len-2]!=0x61) && (ResponseAPDU[len-2]!=0x90) )
	{
		char *p="其他卡型-00A43F00";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	//读卡面号
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xB2\x07\x2C\x0B",5);
	len = ICC_Reader_Application(hReader,0x01,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		char *p="其他卡型-00B2072C00";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	memcpy(UserNo,ResponseAPDU+2,0x09);//获个人编号
	//选SSSE/EF06
	memset(cmd, 0, 100);
	memset(ResponseAPDU, 0, 100);
	memcpy(cmd, "\x00\xA4\x02\x00\x02\xEF\x06", 7);
	rt = ICC_Reader_Application(hReader, 0x01, 7, cmd, Response);
	if(rt<0 || Response[rt-2]!=0x90)
	{
		char *p="选SSSE/EF06失败";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader,0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	//社会保障号码(身份证号码)
	memset(cmd, 0, 100);
	memset(ResponseAPDU, 0, 100);
	memcpy(cmd, "\x00\xB2\x08\x00\x14", 5);
	rt = ICC_Reader_Application(hReader, 0x01, 5, cmd, ResponseAPDU);
	if(rt<0 && Response[rt-2]!=0x90)
	{
		char *p="读社会保障号失败SSSE/EF06-00B2080014";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	memcpy(SHBZHM,ResponseAPDU+2,rt-4);
	//姓名
	memset(cmd, 0, 100);
	memset(ResponseAPDU, 0, 100);
	memcpy(cmd, "\x00\xB2\x09\x00\x20", 5);
	rt = ICC_Reader_Application(hReader, 0x01, 5, cmd, ResponseAPDU);
	if(rt<0 && Response[rt-2]!=0x90)
	{
		char *p="读姓名失败SSSE/EF06-00B2090020";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	memcpy(XM,ResponseAPDU+2,rt-4);
	//性别
	memset(cmd, 0, 100);
	memset(ResponseAPDU, 0, 100);
	memcpy(cmd, "\x00\xB2\x0A\x00\x03", 5);
	rt = ICC_Reader_Application(hReader, 0x01, 5, cmd, ResponseAPDU);
	if(rt<0 && Response[rt-2]!=0x90)
	{
		char *p="读性别失败SSSE/EF06-00B20A0003";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	memcpy(XB,ResponseAPDU+2,rt-4);
	//民族
	memset(cmd, 0, 100);
	memset(ResponseAPDU, 0, 100);
	memcpy(cmd, "\x00\xB2\x0B\x00\x03", 5);
	rt = ICC_Reader_Application(hReader, 0x01, 5, cmd, ResponseAPDU);
	if(rt<0 && Response[rt-2]!=0x90)
	{
		char *p="读民族失败SSSE/EF06-00B20B0003";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	HexToStr(ResponseAPDU+2,1,(unsigned char *)MZ);
	//memcpy(MZ,ResponseAPDU+2,rt-4);
	//出生地
	memset(cmd, 0, 100);
	memset(ResponseAPDU, 0, 100);
	memcpy(cmd, "\x00\xB2\x0C\x00\x05", 5);
	rt = ICC_Reader_Application(hReader, 0x01, 5, cmd, ResponseAPDU);
	if(rt<0 && Response[rt-2]!=0x90)
	{
		char *p="读出生地失败SSSE/EF06-00B20C0005";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	HexToStr(ResponseAPDU+2,3,(unsigned char *)CSD);
	//memcpy(CSD,ResponseAPDU+2,rt-4);
	//出生日期
	memset(cmd, 0, 100);
	memset(ResponseAPDU, 0, 100);
	memcpy(cmd, "\x00\xB2\x0D\x00\x06", 5);
	rt = ICC_Reader_Application(hReader, 0x01, 5, cmd, ResponseAPDU);
	if(rt<0 && Response[rt-2]!=0x90)
	{
		char *p="读出生日期失败SSSE/EF06-00B20D0006";
		strcpy(dataOut,p);
		ICC_Reader_PowerOff(hReader, 0x01);
		ICC_Reader_Close(hReader);
		return -4;
	}
	HexToStr(ResponseAPDU+2,4,(unsigned char *)CSRQ);
	//memcpy(CSRQ,ResponseAPDU+2,rt-4);
	sprintf(dataOut,"%s|%s|%s|%s|%s|%s|%s",UserNo,SHBZHM,XM,XB,MZ,CSD,CSRQ);
	ICC_Reader_PowerOff(hReader, 0x01);
	ICC_Reader_Close(hReader);
	return 0;
}
