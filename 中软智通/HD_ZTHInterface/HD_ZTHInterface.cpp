// HD_ZTHInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_ZTHInterface.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int __stdcall HD_OpenDevice(char *PIN,char *pErr)
{
	HANDLE hDev=NULL;
	int ret=iDOpenPort();
	if(ret!=0)
	{
		sprintf(pErr,"打开设备失败,错误代码:%d",ret);
		return 1;
	}
	char ATR[50]={0};
	ret=PowerOn(hDev ,0x11,ATR);
	if(ret!=0)
	{
		sprintf(pErr,"SAM卡上电失败,错误代码:%d",ret);
		return 1;
	}
	ret=iVerifyPIN(hDev,PIN);
	if(ret!=0)
	{
		sprintf(pErr,"SAM认证PIN失败,错误代码:%d",ret);
		return 1;
	}
	return 0;
}
int __stdcall HD_CloseDevice()
{
	iDClosePort();
	return 0;
}
int __stdcall HD_ReadCardInfo(char *Key,char *CardType,char *CardNo,char *Name,char *Sex,char *Born,char *IDNo,char *MakeCDT,char *EffectD,char *Nation,char *pErr)
{
	HANDLE hDev=NULL;
	char ATR[50]={0};
	char XM[40]={0};
	char XB[10]={0};
	char MZ[10]={0};
	char CSRQ[10]={0};
	char SFZH[20]={0};
	char FKSJ[20]={0};
	char KYXQ[20]={0};
	char KH[40]={0};
	int  ret=PowerOn(hDev ,0x01,ATR);
	if(ret==0)
	{
		//健康卡
		//读卡号
		char TermType[3]={0};
		char PortType[3]={0};
		char PortNO[5]={0}; 
		char TransPortNO[3]={0};
		char ICFlag[3]={0};
		char Taglist[30]={0};
		char AIDList[30]={0};
		char DataBuf[80]={0};
		strcpy(Taglist,"AI");
		strcpy(ICFlag,"3");//+	DataBuf	0x0018efc8 "A0196217902000011197079I006250831"
		//strcpy(ICFlag,"6");//+	DataBuf	0x0018efc8 "A0196217902000011197079I006250831"

		char ATR[60] = {0};
		int ire = HD_ICC_GetInfo(TermType,PortType,PortNO,TransPortNO,ICFlag,Taglist,AIDList,DataBuf);
		if(ire!=0 || strlen(DataBuf)<10)
		{
			strcpy(pErr,"1|获取卡号/有效期失败|");
			return 1;
		}
		char len[10]={0};
		memcpy(len,DataBuf+2,2);
		int LenOfCardNo=atoi(len);
		memcpy(KH,DataBuf+4,LenOfCardNo);
		char *p=strstr(DataBuf,"I");
		memset(len,0,sizeof(len));
		memcpy(len,p+2,2);
		int LenOfDate=atoi(len);
		strcpy(KYXQ,"20");
		strcat(KYXQ,p+4);
		//memcpy(KYXQ,p+4,LenOfDate);
		//读姓名、性别、出生日期、身份证号码
		ret=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
		if(ret!=0)
		{
			sprintf(pErr,"读DDF1EF06失败,错误代码:%d",ret);
			return 1;
		}
		//读发卡日期
		char Temp[500]={0};
		ret=iR_DDF1EF05Info(hDev,Temp,Temp,Temp,Temp,Temp,FKSJ,Temp,Temp,Temp,Temp);
		if(ret!=0)
		{
			sprintf(pErr,"读DDF1EF05失败,错误代码:%d",ret);
			return 1;
		}
		//开始填数据
		strcpy(CardType,"1");  //卡类型
		strcpy(CardNo,KH);  //卡号
		strcpy(Name,XM);       //姓名
		strcpy(Sex,XB);		   //性别
		strcpy(Born,CSRQ);     //出生日期
		strcpy(IDNo,SFZH);     //身份证号
		strcpy(Nation,MZ);     //民族代码
		strcpy(MakeCDT,FKSJ);     //发卡日期
		strcpy(EffectD,KYXQ);     //有效期
	}else
	{
		//临时卡
		long ReaderHandle=ICC_Reader_Open("USB1");
		if(ReaderHandle<=0)
		{
			sprintf(pErr,"(临时卡)打开端口失败,错误代码:%d",ReaderHandle);
			return 1;
		}
		int ret=PICC_Reader_Request(ReaderHandle);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)请求卡片失败,错误代码:%d",ret);
			return 1;
		}
		unsigned char uid[50]={0};
		ret=PICC_Reader_anticoll(ReaderHandle,uid);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)防碰撞失败,错误代码:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Select(ReaderHandle,0x41);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)选卡失败,错误代码:%d",ret);
			return 1;
		}
		unsigned char key[10]={0};
		StrToHex((unsigned char*)Key,12,key);//将字符命令流转为16进制流
		//读临时卡号、发卡日期
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,3,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)认证s3密码失败,错误代码:%d",ret);
			return 1;
		}
		unsigned char DataHex[40]={0};
		ret=PICC_Reader_ReadHEX(ReaderHandle,12,DataHex);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读卡号失败,错误代码:%d",ret);
			return 1;
		}
		memcpy(KH,DataHex+13,19);
		memset(DataHex,0,40);
		ret=PICC_Reader_ReadHEX(ReaderHandle,13,DataHex);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读发卡日期失败,错误代码:%d",ret);
			return 1;
		}
		memcpy(FKSJ,DataHex,8);
		memset(DataHex,0,40);
		//读姓名、性别
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,1,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)认证s1密码失败,错误代码:%d",ret);
			return 1;
		}
		unsigned char Data[40]={0};
		ret=PICC_Reader_Read(ReaderHandle,4,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读姓名1失败,错误代码:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,5,Data+16);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读姓名2失败,错误代码:%d",ret);
			return 1;
		}
		memcpy(XM,Data,32);
		memset(Data,0,40);
		ret=PICC_Reader_Read(ReaderHandle,6,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读性别失败,错误代码:%d",ret);
			return 1;
		}
		XB[0]='0';
		memcpy(XB+1,Data,1);
		memset(DataHex,0,40);
		//读身份证号、出生日期
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,2,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)认证s2密码失败,错误代码:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,8,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读身份证号1失败,错误代码:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,9,Data+16);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读身份证号2失败,错误代码:%d",ret);
			return 1;
		}
		memcpy(SFZH,Data,18);
		memset(Data,0,40);
		ret=PICC_Reader_ReadHEX(ReaderHandle,10,DataHex);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"(临时卡)读出生日期失败,错误代码:%d",ret);
			return 1;
		}
		memcpy(CSRQ,DataHex,8);
		//开始填数据
		strcpy(CardType,"2");
		strcpy(CardNo,KH);
		strcpy(Name,XM);
		strcpy(Sex,XB);
		strcpy(Born,CSRQ);
		strcpy(IDNo,SFZH);
		strcpy(MakeCDT,FKSJ);
	}
	return 0;
}