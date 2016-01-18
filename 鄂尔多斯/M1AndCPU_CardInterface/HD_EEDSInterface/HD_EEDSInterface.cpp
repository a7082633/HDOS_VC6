// HD_EEDSInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_EEDSInterface.h"
#include "Utils.h"
#include "ConvertUtil.h"
#include "StringUtil.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}
char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}
int CleanName(char *name)
{
	int i;
	int len = (int)strlen(name);

	for(i=0; i < len; i++) {
		if(name[i] == 'F' && (!(i%5))) {
			name[i] = 0;
			break;
		}
	}

	return 0;
}
EEDS_HD_API int __stdcall ReadInfo(unsigned char *pKey, 
								   unsigned char *GECHH, 
								   unsigned char *XM, 
								   unsigned char *SFZH, 
								   unsigned char *CSRQ, 
								   unsigned char *XB, 
								   unsigned char *MZ,
								   char *pErr)
{
	HANDLE hDev=NULL;
	char sGECHH[50]={0};
	char sXM[40]={0};
	char sSFZH[20]={0};
	char sCSRQ[10]={0};
	char sXB[10]={0};
	char sMZ[10]={0};
	char ATR[50]={0};
	int ret=iDOpenPort();
//	if(ret!=0)
//	{
//		sprintf(pErr,"´ò¿ªÉè±¸Ê§°Ü,´íÎó´úÂë(WSB):%d",ret);
//		return 1;
//	}
	ret=PowerOn(hDev ,0x01,ATR);
	if(ret==0)
	{
		ret=PowerOn(hDev ,0x11,ATR);
		if(ret!=0)
		{
			iDClosePort();
			sprintf(pErr,"SAM¿¨ÉÏµçÊ§°Ü,´íÎó´úÂë(WSB):%d",ret);
			return 1;
		}
		ret=iVerifyPIN(hDev,"123456");
		if(ret!=0)
		{
			iDClosePort();
			sprintf(pErr,"SAMÈÏÖ¤PINÊ§°Ü,´íÎó´úÂë(WSB):%d",ret);
			return 1;
		}
		ret=iR_DDF1EF06Info(hDev,sXM,sXB,sMZ,sCSRQ,sSFZH);
		if(ret)
		{
			iDClosePort();
			sprintf(pErr,"¶ÁDDF1EF06Ê§°Ü,´íÎó´úÂë(WSB):%d",ret);
			return 1;
		}
		char Temp[50]={0};
		ret=iR_DF01EF08Info(hDev,Temp,Temp,Temp,sGECHH);
		if(ret)
		{
			iDClosePort();
			sprintf(pErr,"¶ÁDDF1EF08Ê§°Ü,´íÎó´úÂë(WSB):%d",ret);
			return 1;
		}
		iDClosePort();
		strcpy((char *)GECHH,sGECHH);
		strcpy((char *)XM,sXM);
		strcpy((char *)SFZH,sSFZH);
		strcpy((char *)CSRQ,sCSRQ);
		strcpy((char *)XB,sXB);
		strcpy((char *)MZ,sMZ);
	}
	else
	{
//		char Test[100]="ÕÔÁÁ";//641945115841655fffffffffffffffff
//		char szName[100] ={0} ;
//		string strName=CConvertUtil::uf_gbk_int_covers(Test,"toint");
//		char Test2[100]="5448549601";
//		strName=CConvertUtil::uf_gbk_int_covers(Test2,"togbk");
		//memcpy(Test2,"\x64\x19\x45\x11\x58\x41\x65\x50",8);\x54\x48\x54\x96\x01
		//memcpy(Test2,"\x54\x48\x54\x96\x01\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff",16);
			////////////////////
		iDClosePort();
		long ReaderHandle=ICC_Reader_Open("USB1");
		if(ReaderHandle<=0)
		{
			sprintf(pErr,"SSSE32´ò¿ª¶Ë¿ÚÊ§°Ü,´íÎó´úÂë:%d",ReaderHandle);
			return 1;
		}
		int ret=PICC_Reader_Request(ReaderHandle);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32ÇëÇó¿¨Æ¬Ê§°Ü,´íÎó´úÂë(ÎÞ¿¨):%d",ret);
			return 1;
		}
		unsigned char uid[50]={0};
		ret=PICC_Reader_anticoll(ReaderHandle,uid);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32·ÀÅö×²Ê§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Select(ReaderHandle,0x41);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32Ñ¡¿¨Ê§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		unsigned char Data[40]={0};
		unsigned char DataStr[40]={0};
		unsigned char key[10]={0};
		Utils::HexstrToBin(key,pKey,12);
		//¶ÁÅ©ºÏ¿¨ºÅ
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,1,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32ÈÏÖ¤s1ÃÜÂëÊ§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,6,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32¶Á¿é6Ê§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sGECHH,DataStr+6,18);
		//¶Á¸öÈËÐÅÏ¢
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,2,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32ÈÏÖ¤s2ÃÜÂëÊ§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		//ÐÕÃû
		ret=PICC_Reader_Read(ReaderHandle,8,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32¶Á¿é8Ê§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,9,Data+16);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32¶Á¿é9Ê§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		unsigned char stemp[100]={0};
		Utils::BinToHexstr(stemp,Data,32);
		CleanName((char *)stemp);
		string szName;
		if(Is_IntName((char *)stemp))
		{
			szName = CConvertUtil::uf_gbk_int_covers((char *)stemp,"togbk");
			strcpy(sXM,(const char *)szName.c_str());
		}else
		{
			strcpy(sXM,(const char *)Data);
		}
		//Éí·ÝÖ¤ºÅ£¬³öÉúÈÕÆÚ£¬ÐÔ±ð
		ret=PICC_Reader_Read(ReaderHandle,10,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32¶Á¿é10Ê§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sSFZH,DataStr,18);
		memcpy(sCSRQ,DataStr+18,8);
		memcpy(sXB,DataStr+26,1);
		//¶ÁÃñ×å
		ret=PICC_Reader_Authentication_Pass(ReaderHandle,0x60,3,key);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32ÈÏÖ¤s3ÃÜÂëÊ§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		ret=PICC_Reader_Read(ReaderHandle,12,Data);
		if(ret!=0)
		{
			ICC_Reader_Close(ReaderHandle);
			sprintf(pErr,"SSSE32¶Á¿é12Ê§°Ü,´íÎó´úÂë:%d",ret);
			return 1;
		}
		ICC_Reader_Close(ReaderHandle);
		Utils::BinToHexstr(DataStr,Data,16);
		memcpy(sMZ,DataStr,2);

		strcpy((char *)GECHH,sGECHH);
		strcpy((char *)XM,sXM);
		strcpy((char *)SFZH,sSFZH);
		strcpy((char *)CSRQ,sCSRQ);
		strcpy((char *)XB,sXB);
		strcpy((char *)MZ,sMZ);
	}
	return 0;
}