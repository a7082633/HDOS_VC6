// HD_RWHealInterface.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "PDS_RWHealInterface.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL FindProcess()
{
	int i=0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32); 
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		i+=0;
	}
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while(bMore)
	{
		//printf(" 进程名称：%s \n", pe32.szExeFile);
		if(stricmp("HCenter.exe",pe32.szExeFile)==0)
		{
			//printf("进程运行中");
			i+=1;
		}
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	if(i>0){           //大于1，排除自身
		return true;
	}else{
		return false;
	}
}
MHC_CARDINTERFACE_API int __stdcall IDOpenPort(char *account,char *password)
{
	char addr[300]={0};
//	char des[300]={0};
//	CString sdes;
//	::GetCurrentDirectory(300,des);
//	sdes.Format("%s\\config.ini",des);
//	::MessageBox(NULL,sdes,NULL,MB_OK);
	DWORD ConfigLen=GetPrivateProfileString("INFO","Device_Address",NULL,addr,sizeof(addr),"D:\\config.ini");
	//DWORD ConfigLen=GetPrivateProfileString("INFO","Device_Address",NULL,addr,sizeof(addr),".\\config.ini");
	//::MessageBox(NULL,addr,NULL,MB_OK);
	//char *addr="http://221.176.197.13:8011/Api!DeviceIdentify.do";
	/////////////////////////////////////////////////////////
	long hReader=ICC_Reader_Open("USB1");
	char cmd[100]={0};
	unsigned char Response[50]={0};
	if(hReader<=0)//设备打开失败返回
	{
		return hReader;
	}
	//获取sam卡序列号
		//操作SAM卡
	int rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam卡复位
	if(rt<=0)
	{
		return rt;
	}
		//选SAM卡的MF
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
	int len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		return IFD_ICC_TypeError;
	}
		//选0015
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
	len = ICC_Reader_Application(hReader,0x11,7,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		return IFD_ICC_TypeError;
	}
		//读取sam卡的序列号
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xB0\x00\x00\x0A",5); 
	len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if(len<=0||Response[len-2]!=0x90)
	{
		return IFD_ICC_TypeError;
	}
	unsigned char SamNo[21]={0};
	HexToStr((unsigned char *)Response,10,SamNo);
	//获取机具号
	char Dev_Ser[50]={0};
	rt=ICC_Reader_GetDeviceCSN(hReader,Dev_Ser);
	if(rt<=0)
	{
		return rt;
	}
	//发送http请求
	CInternetSession m_session("Webservice32");
	CHttpFile *pFile;
	//char HttpResponse[500]={0};
	CString HttpResponse="";
	try
	{
		CString strData;
		char requestUrl[500]={0};
		//char requestUrl[500]={"http://221.176.197.13:8011/Api!DeviceIdentify.do?account=test&password=111111&macno=000011&samno=123456"};
		sprintf(requestUrl,"%s?account=%s&password=%s&macno=%s&samno=%s",
			addr,account,password,Dev_Ser,SamNo);
		//::MessageBox(NULL,requestUrl,NULL,MB_OK);
		DWORD   dwFlags   =   INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_RELOAD; 
		pFile = (CHttpFile *) m_session.OpenURL(requestUrl,1,dwFlags);
		DWORD Code;
		pFile->QueryInfoStatusCode(Code);
		if(Code!=200)
		{
			return CANT_FINDWEB;
		}
		//::MessageBox(NULL,"haha",NULL,MB_OK);
		while(pFile->ReadString(strData))
			HttpResponse+=strData;
		//::MessageBox(NULL,requestUrl,NULL,MB_OK);
	}
	catch(CInternetException* e)  //捕获异常
	{
		TCHAR pszError[200];
		e->GetErrorMessage(pszError, 200);
		//::MessageBox(NULL,pszError,NULL,MB_OK);
		e->Delete();
		return HTTP_EXCEPTION;
	}
	//pFile->Close();
	m_session.Close();
	char rtstr[10]={0};
	memcpy(rtstr,HttpResponse.GetBuffer(0),4);
	HttpResponse.ReleaseBuffer();
	ICC_Reader_Close(hReader);
	if(0==strcmp(rtstr,"0000"))
		return iDOpenPort();
	else return atoi(rtstr);
//	return 0;
}
MHC_CARDINTERFACE_API int __stdcall IDClosePort(void)
{
	return iDClosePort();
}
MHC_CARDINTERFACE_API int __stdcall IVerifyPIN(HANDLE hDev,char * PIN)
{
	int rt=iVerifyPIN(hDev,PIN);
	return rt;
}
MHC_CARDINTERFACE_API int __stdcall IPowerOn(HANDLE hDev,int slot, 
											 char * ATR,char *account,
											 char *password,int doctype,
											 char *para,char *userid,char *pin)
{
	long hReader=ICC_Reader_Open("USB1");
	char cmd[100]={0};
	unsigned char Response[50]={0};
	if(hReader<=0)//设备打开失败返回
	{
		return hReader;
	}
	//取卡的芯片号
		//请求卡片
	int rt=0;
	rt=PICC_Reader_Request(hReader);
	if(rt!=0)
	{
		return rt;
	}
		//防碰撞
	unsigned char uid[10]={0};
	rt =PICC_Reader_anticoll(hReader,uid);
	if(rt)
	{
		return rt;
	}
		//选卡
	rt=PICC_Reader_Select(hReader,0x41);
	if(rt)
	{
		return rt;
	}
		//上电
	rt=PICC_Reader_PowerOnTypeA(hReader,Response);
	if(rt<=0)
	{
		return rt;
	}
	unsigned char csno[17]={0};
	HexToStr(Response+5,8,csno);
	//获取机具号（从芯片获取）
	char macno[50]={0};
	rt=ICC_Reader_GetDeviceCSN(hReader,macno);
	if(rt<=0)
	{
		return rt;
	}
	//获取sam卡序列号
//	char SamATR[50]={0};
//	rt=PowerOn(hDev,0x11,SamATR);
//	if(rt)
//	{
//		return rt;
//	}
//	char samno[300]={0};
//	rt=iReader_SAM_Public((int)hDev,samno);
//	if(rt)
//	{
//		return rt;
//	}
		//操作SAM卡
	memset(Response,0,50);
	rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam卡复位
	if(rt<=0)
	{
		return rt;
	}
		//选SAM卡的MF
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
	int len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		return len;
	}
	//选0015
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
	len = ICC_Reader_Application(hReader,0x11,7,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		return IFD_ICC_TypeError;
	}
		//读取sam卡的序列号
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xB0\x00\x00\x0A",5); 
	len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if(len<=0||Response[len-2]!=0x90)
	{
		return IFD_ICC_TypeError;
	}
	unsigned char samno[21]={0};
	HexToStr((unsigned char *)Response,10,samno);
	ICC_Reader_PowerOff(hReader,0x11);
	//发送http请求
	char addr[300]={0};
	DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),".\\config.ini");
	MessageBox(NULL,addr,NULL,MB_OK);
	CInternetSession m_session("Webservice32");
	CString HttpResponse;
	try
	{
		CString strData;
//		char requestUrl[500]={"http://221.176.197.13:8011/Api!CardIdentify.do?account=test&password=111111&csno=410425200810190216&macno=000011&samno=123456&doctype=1&funtype=0&para=0|1|0&userid=001"};
		char requestUrl[500]={0};
		sprintf(requestUrl,"%s?account=%s&password=%s&csno=%s&macno=%s&samno=%s&doctype=%d&funtype=1&para=%s&userid=%s",
			addr,account,password,csno,macno,samno,doctype,para,userid);
		//MessageBox(NULL,requestUrl,NULL,MB_OK);
		CHttpFile *pFile;
		//MessageBox(NULL,requestUrl,NULL,MB_OK);
		pFile = (CHttpFile *) m_session.OpenURL(requestUrl);
		DWORD Code;
		pFile->QueryInfoStatusCode(Code);
		if(Code!=200)
		{
			return CANT_FINDWEB;
		}
		while(pFile->ReadString(strData))
			HttpResponse+=strData;
		pFile->Close();
	}
	catch(CInternetException* e)  //捕获异常
	{
		TCHAR pszError[200];
		e->GetErrorMessage(pszError, 200);
		::MessageBox(NULL,pszError,NULL,MB_OK);
		e->Delete();
		return HTTP_EXCEPTION;
	}
	m_session.Close();
	char rtstr[10]={0};
	memcpy(rtstr,HttpResponse.GetBuffer(0),4);
	ICC_Reader_Close(hReader);

	if(0==strcmp(rtstr,"0000"))
	{
		rt=PowerOn(hDev,slot,ATR);
		if(rt) return rt;
		rt=IVerifyPIN(hDev,pin);
		return rt;
	}
	else return atoi(rtstr);
}
MHC_CARDINTERFACE_API int __stdcall IChange_Pin(int hDev,char *oldPin,char *newPin)
{
	return iChange_Pin(hDev,oldPin,newPin);
}
MHC_CARDINTERFACE_API int __stdcall IR_ReadCard(char *para,char *dataOut,
												char *account,char *password,
												int doctype,char *userid,
												char *pin)
{
	//读之前判断进程是否存在
	if(!FindProcess())
	{
		::MessageBox(NULL,"请运行卫计委卡管程序","提示",MB_OK);
		return PROCCESS_EXIST;
	}
	//读之前需要验证
	long hReader=ICC_Reader_Open("USB1");
	char cmd[100]={0};
	unsigned char Response[50]={0};
	if(hReader<=0)//设备打开失败返回
	{
		return hReader;
	}
	//取卡的芯片号
		//请求卡片
	int rt=0;
	rt=PICC_Reader_Request(hReader);
	if(rt!=0)
	{
		//::MessageBox(NULL,"取卡芯片号时请求卡片失败!",NULL,MB_OK);
		ICC_Reader_Close(hReader);
		return rt;
	}
		//防碰撞
	unsigned char uid[10]={0};
	rt =PICC_Reader_anticoll(hReader,uid);
	if(rt)
	{
		//::MessageBox(NULL,"取卡芯片号时防碰撞失败!",NULL,MB_OK);
		ICC_Reader_Close(hReader);
		return rt;
	}
		//选卡
	rt=PICC_Reader_Select(hReader,0x41);
	if(rt)
	{
		//::MessageBox(NULL,"取卡芯片号时选卡失败!",NULL,MB_OK);
		ICC_Reader_Close(hReader);
		return rt;
	}
		//上电
	rt=PICC_Reader_PowerOnTypeA(hReader,Response);
	if(rt<=0)
	{
		//::MessageBox(NULL,"取卡芯片号时上电失败!",NULL,MB_OK);
		ICC_Reader_Close(hReader);
		return rt;
	}
	unsigned char csno[17]={0};
	HexToStr(Response+5,8,csno);
	ICC_Reader_PowerOff(hReader,0x01);
	//获取机具号（从芯片获取）
	char macno[50]={0};
	rt=ICC_Reader_GetDeviceCSN(hReader,macno);
	if(rt<=0)
	{
		//::MessageBox(NULL,"取机具号失败!",NULL,MB_OK);
		ICC_Reader_Close(hReader);
		return rt;
	}
	//获取sam卡序列号
		//操作SAM卡
	memset(Response,0,50);
	rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam卡复位
	if(rt<=0)
	{
		//::MessageBox(NULL,"SAM上电失败!",NULL,MB_OK);
		ICC_Reader_Close(hReader);
		return rt;
	}
		//选SAM卡的MF
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
	int len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		//::MessageBox(NULL,"选MF失败!",NULL,MB_OK);
		ICC_Reader_Close(hReader);
		return len;
	}
	//选0015
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
	len = ICC_Reader_Application(hReader,0x11,7,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		//::MessageBox(NULL,"选SAM-MF-0015失败!",NULL,MB_OK);
		ICC_Reader_PowerOff(hReader,0x11);
		ICC_Reader_Close(hReader);
		return IFD_ICC_TypeError;
	}
		//读取sam卡的序列号
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xB0\x00\x00\x0A",5); 
	len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if(len<=0||Response[len-2]!=0x90)
	{
		//::MessageBox(NULL,"读SAM序列号失败!",NULL,MB_OK);
		ICC_Reader_PowerOff(hReader,0x11);
		ICC_Reader_Close(hReader);
		return IFD_ICC_TypeError;
	}
	unsigned char samno[21]={0};
	HexToStr((unsigned char *)Response,10,samno);
	ICC_Reader_PowerOff(hReader,0x11);
	ICC_Reader_Close(hReader);
	//发送http请求
	char addr[300]={0};
	/*C:\Program Files (x86)\PDS_HNKG\*/
	DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),"C:\\Program Files (x86)\\PDS_HNKG\\config.ini");
	//DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),"D:\\config.ini");
	CInternetSession m_session("Webservice32");
	CString HttpResponse;
	try
	{
		CString strData;
//		char requestUrl[500]={"http://221.176.197.13:8011/Api!CardIdentify.do?account=test&password=111111&csno=410425200810190216&macno=000011&samno=123456&doctype=1&funtype=0&para=0|1|0&userid=001"};
		char requestUrl[500]={0};
		sprintf(requestUrl,"%s?account=%s&password=%s&csno=%s&macno=%s&samno=%s&doctype=%d&funtype=0&para=%s&userid=%s",
			addr,account,password,csno,macno,samno,doctype,para,userid);
	
		::MessageBox(NULL,requestUrl,NULL,MB_OK);

		CHttpFile *pFile;
		pFile = (CHttpFile *) m_session.OpenURL(requestUrl);
		DWORD Code;
		pFile->QueryInfoStatusCode(Code);
		if(Code!=200)
		{
			return CANT_FINDWEB;
		}
		while(pFile->ReadString(strData))
			HttpResponse+=strData;
		pFile->Close();
	}
	catch(CInternetException* e)  //捕获异常
	{
		TCHAR pszError[200];
		e->GetErrorMessage(pszError, 200);
		::MessageBox(NULL,pszError,NULL,MB_OK);
		e->Delete();
		return HTTP_EXCEPTION;
	}
	m_session.Close();
	char rtstr[10]={0};
	memcpy(rtstr,HttpResponse.GetBuffer(0),4);

	if(0==strcmp(rtstr,"0000"))
	{
		HANDLE hDev;
		rt=iDOpenPort();
		if(rt)
		{
			//MessageBox(NULL,"打开端口失败",NULL,MB_OK);
			return rt;
		}
		char ATR[50]={0};
		rt=PowerOn(hDev,0x01,ATR);
		if(rt) 
		{
			//MessageBox(NULL,"健康卡上电失败",NULL,MB_OK);
			return rt;
		}
		rt=PowerOn(hDev,0x11,ATR);
		if(rt)
		{
			//MessageBox(NULL,"SAM上电失败",NULL,MB_OK);
			return rt;
		}
		rt=IVerifyPIN(hDev,pin);
		if(rt)
		{
			//MessageBox(NULL,"SAM认证失败",NULL,MB_OK);
			return rt;
		}
	}
	else
	{
		return atoi(rtstr);
	}
	const char * split = "|"; 
	char * p; 
	p = strtok (para,split);
	int re=0;
	while(p!=NULL) 
	{ 
		int flag=atoi(p);
		if(flag==0) return 114;
		char data[4000]={0};
		HANDLE hDev;
		switch(flag)
		{
		case 1:case 2:case 3:case 4:case 5:case 6:case 8:case 9:case 10:
		case 57:
			{
				char KLB[100]={0};
				char GFBB[100]={0};
				char FKJGMC[100]={0};
				char FKJGDM[100]={0};
				char FKJGZS[500]={0};
				char FKSJ[100]={0};
				char KH[100]={0};
				char AQM[100]={0}; 
				char XPXLH[100]={0}; 
				char YYCSDM[100]={0};
				re=iR_DDF1EF05Info(hDev,KLB,GFBB, FKJGMC, FKJGDM, FKJGZS, FKSJ, KH, AQM, XPXLH, YYCSDM);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 1:
					{strcat(dataOut,KLB);  strcat(dataOut,"|"); break;}
				case 2:
					{strcat(dataOut,GFBB);strcat(dataOut,"|");break;}
				case 3:
					{strcat(dataOut,FKJGMC);strcat(dataOut,"|");break;}
				case 4:
					{strcat(dataOut,FKJGDM);strcat(dataOut,"|");break;}
				case 5:
					{strcat(dataOut,FKJGZS);strcat(dataOut,"|");break;}
				case 6:
					{strcat(dataOut,FKSJ);strcat(dataOut,"|");break;}
				case 8:
					{strcat(dataOut,KH);strcat(dataOut,"|");break;}
				case 9:
					{strcat(dataOut,AQM);strcat(dataOut,"|");break;}
				case 10:
					{strcat(dataOut,XPXLH);strcat(dataOut,"|");break;}
				case 57:
					{strcat(dataOut,YYCSDM);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 11:case 12:case 13:case 14:
		case 15:
			{
				char XM[50]={0};             //姓名
				char XB[50]={0};               //性别代码
				char MZ[50]={0};               //民族代码
				char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
				char SFZH[50]={0};            //居民身份证号
				re=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 11:
					{strcat(dataOut,XM);  strcat(dataOut,"|"); break;}
				case 12:
					{strcat(dataOut,XB);strcat(dataOut,"|");break;}
				case 13:
					{strcat(dataOut,MZ);strcat(dataOut,"|");break;}
				case 14:
					{strcat(dataOut,CSRQ);strcat(dataOut,"|");break;}
				case 15:
					{strcat(dataOut,SFZH);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 7:case 16:case 17:case 18:case 19:
		case 20:
			{
				char KYXQ[21]={0};			//卡有效期
				char BRDH1[21]={0};         //本人电话1
				char BRDH2[21]={0};           //本人电话2
				char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
				char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
				char YLFYZFFS3[21]={0};	
				re=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 7:
					{strcat(dataOut,KYXQ);  strcat(dataOut,"|"); break;}
				case 16:
					{strcat(dataOut,BRDH1);strcat(dataOut,"|");break;}
				case 17:
					{strcat(dataOut,BRDH2);strcat(dataOut,"|");break;}
				case 18:
					{strcat(dataOut,YLFYZFFS1);strcat(dataOut,"|");break;}
				case 19:
					{strcat(dataOut,YLFYZFFS2);strcat(dataOut,"|");break;}
				case 20:
					{strcat(dataOut,YLFYZFFS3);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 21:case 22:case 23:
		case 24:
			{
				char DZLB1[21]={0};		
				char DZ1[120]={0};       
				char DZLB2[21]={0};     
				char DZ2[120]={0};	
				re=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 21:
					{strcat(dataOut,DZLB1);  strcat(dataOut,"|"); break;}
				case 22:
					{strcat(dataOut,DZ1);strcat(dataOut,"|");break;}
				case 23:
					{strcat(dataOut,DZLB2);strcat(dataOut,"|");break;}
				case 24:
					{strcat(dataOut,DZ2);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 25:case 26:case 27:case 28:case 29:case 30:case 31:case 32:
		case 33:
			{
				char LXRXM1[40]={0};		
				char LXRGX1[2]={0};       
				char LXRDH1[30]={0};
				char LXRXM2[40]={0};		
				char LXRGX2[2]={0};       
				char LXRDH2[30]={0}; 
				char LXRXM3[40]={0};		
				char LXRGX3[2]={0};       
				char LXRDH3[30]={0}; 
				re=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 25:
					{strcat(dataOut,LXRXM1);  strcat(dataOut,"|"); break;}
				case 26:
					{strcat(dataOut,LXRGX1);strcat(dataOut,"|");break;}
				case 27:
					{strcat(dataOut,LXRDH1);strcat(dataOut,"|");break;}
				case 28:
					{strcat(dataOut,LXRXM2);strcat(dataOut,"|");break;}
				case 29:
					{strcat(dataOut,LXRGX2);  strcat(dataOut,"|"); break;}
				case 30:
					{strcat(dataOut,LXRDH2);strcat(dataOut,"|");break;}
				case 31:
					{strcat(dataOut,LXRXM3);strcat(dataOut,"|");break;}
				case 32:
					{strcat(dataOut,LXRGX3);strcat(dataOut,"|");break;}
				case 33:
					{strcat(dataOut,LXRDH3);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 34:case 35:
		case 36:
			{
				char WHCD[10]={0};		
				char HYZK[10]={0};       
				char ZY[10]={0};			
				re=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 34:
					{strcat(dataOut,WHCD);  strcat(dataOut,"|"); break;}
				case 35:
					{strcat(dataOut,HYZK);strcat(dataOut,"|");break;}
				case 36:
					{strcat(dataOut,ZY);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 37:case 38:case 39:
		case 40:
			{
				char ZJLB[20]={0};		
				char ZJHM[20]={0};       
				char JKDAH[20]={0};
				char XNHZH[20]={0};
				re=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 37:
					{strcat(dataOut,ZJLB);  strcat(dataOut,"|"); break;}
				case 38:
					{strcat(dataOut,ZJHM);strcat(dataOut,"|");break;}
				case 39:
					{strcat(dataOut,JKDAH);strcat(dataOut,"|");break;}
				case 40:
					{strcat(dataOut,XNHZH);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 41:case 42:case 43:case 44:case 45:case 46:case 47:case 48:case 49:case 50:case 51:case 52:case 53:case 54:
		case 55:
			{
				char ABOXX[10]={0};		
				char RHXX[10]={0};       
				char XCBZ[10]={0};
				char XZBBZ[10]={0};
				char XNXGBBZ[10]={0};         //心脑血管病标志
				char DXBBZ[10]={0};           //癫痫病标志
				char NXWLBZ[10]={0};          //凝血紊乱标志
				char TNBBZ[10]={0};           //糖尿病标志
				char QGYBZ[10]={0};           //青光眼标志
				char TXBZ[10]={0};          //透析标志
				char QGYZBZ[10]={0};          //器官移植标志
				char QGQSBZ[10]={0};        //器官缺失标志
				char KZXYZBZ[10]={0};         //可装卸义肢标志
				char XZQBQBZ[10]={0};        //心脏起搏器标志
				char QTYXJSMC[50]={0};
				re=iR_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
				if(re)
				{
					iDClosePort();
					return re;
				}
				switch(flag)
				{
				case 41:
					{strcat(dataOut,ABOXX);  strcat(dataOut,"|"); break;}
				case 42:
					{strcat(dataOut,RHXX);strcat(dataOut,"|");break;}
				case 43:
					{strcat(dataOut,XCBZ);strcat(dataOut,"|");break;}
				case 44:
					{strcat(dataOut,XZBBZ);strcat(dataOut,"|");break;}
				case 45:
					{strcat(dataOut,XNXGBBZ);  strcat(dataOut,"|"); break;}
				case 46:
					{strcat(dataOut,DXBBZ);strcat(dataOut,"|");break;}
				case 47:
					{strcat(dataOut,NXWLBZ);strcat(dataOut,"|");break;}
				case 48:
					{strcat(dataOut,TNBBZ);strcat(dataOut,"|");break;}
				case 49:
					{strcat(dataOut,QGYBZ);  strcat(dataOut,"|"); break;}
				case 50:
					{strcat(dataOut,TXBZ);strcat(dataOut,"|");break;}
				case 51:
					{strcat(dataOut,QGYZBZ);strcat(dataOut,"|");break;}
				case 52:
					{strcat(dataOut,QGQSBZ);strcat(dataOut,"|");break;}
				case 53:
					{strcat(dataOut,KZXYZBZ);strcat(dataOut,"|");break;}
				case 54:
					{strcat(dataOut,XZQBQBZ);strcat(dataOut,"|");break;}
				case 55:
					{strcat(dataOut,QTYXJSMC);strcat(dataOut,"|");break;}
				}
				break;
			}
		case 56:
			{
				char JSBBZ[10]={0};		
				re=iR_DF02EF06Info(hDev,JSBBZ);
				if(re)
				{
					iDClosePort();
					return re;
				}
				strcat(dataOut,JSBBZ);strcat(dataOut,"|");
				break;
			}
		case 102:
			{
			//照片
				unsigned char picData[3075]={0};
				re=iR_DDF1EF07Info(hDev,(unsigned char *)picData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char temp[10]={0};
				sprintf(temp,"%02x%02x",picData[0],picData[1]);
				long len=strtol(temp,NULL,16);
				unsigned char picTemp[7000]={0};
				HexToStr(picData,len+2,picTemp);
				strcat(dataOut,(const char *)picTemp);
				strcat(dataOut,"|");
//				if(i==0) 
//				{
//					char temp[10]={0};
//					sprintf(temp,"%02x%02x",data[0],data[1]);
//					long len=strtol(temp,NULL,16);
//					ofstream file("zp.jpg",ios::out|ios::binary);
//					if(file==NULL)
//					{
//						iDClosePort();
//						return 116;
//					}
//					file.write(data+2,len);
//					file.close();
//				}
				break;
			}

		}
		p = strtok(NULL,split);
	}
	len=strlen(dataOut);
	dataOut[len-1]='\0';
	iDClosePort();
	return 0;
}
MHC_CARDINTERFACE_API int __stdcall IR_WriteCard(char *para,char *dataIn,
												char *account,char *password,
												int doctype,char *userid,
												char *pin)
{
	//读之前判断进程是否存在
	if(!FindProcess())
	{
		::MessageBox(NULL,"请运行卫计委卡管程序","提示",MB_OK);
		return PROCCESS_EXIST;
	}
	//写之前需要验证
	long hReader=ICC_Reader_Open("USB1");
	char cmd[100]={0};
	unsigned char Response[50]={0};
	if(hReader<=0)//设备打开失败返回
	{
		return hReader;
	}
	//取卡的芯片号
		//请求卡片
	int rt=0;
	rt=PICC_Reader_Request(hReader);
	if(rt!=0)
	{
		ICC_Reader_Close(hReader);
		return rt;
	}
		//防碰撞
	unsigned char uid[10]={0};
	rt =PICC_Reader_anticoll(hReader,uid);
	if(rt)
	{
		ICC_Reader_Close(hReader);
		return rt;
	}
		//选卡
	rt=PICC_Reader_Select(hReader,0x41);
	if(rt)
	{
		ICC_Reader_Close(hReader);
		return rt;
	}
		//上电
	rt=PICC_Reader_PowerOnTypeA(hReader,Response);
	if(rt<=0)
	{
		ICC_Reader_Close(hReader);
		return rt;
	}
	unsigned char csno[17]={0};
	HexToStr(Response+5,8,csno);
	ICC_Reader_PowerOff(hReader,0x01);
	//获取机具号（从芯片获取）
	char macno[50]={0};
	rt=ICC_Reader_GetDeviceCSN(hReader,macno);
	if(rt<=0)
	{
		ICC_Reader_Close(hReader);
		return rt;
	}
	//获取sam卡序列号
		//操作SAM卡
	memset(Response,0,50);
	rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam卡复位
	if(rt<=0)
	{
		ICC_Reader_Close(hReader);
		return rt;
	}
		//选SAM卡的MF
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
	int len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		ICC_Reader_Close(hReader);
		return len;
	}
	//选0015
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
	len = ICC_Reader_Application(hReader,0x11,7,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		ICC_Reader_PowerOff(hReader,0x11);
		ICC_Reader_Close(hReader);
		return IFD_ICC_TypeError;
	}
		//读取sam卡的序列号
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xB0\x00\x00\x0A",5); 
	len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if(len<=0||Response[len-2]!=0x90)
	{
		ICC_Reader_PowerOff(hReader,0x11);
		ICC_Reader_Close(hReader);
		return IFD_ICC_TypeError;
	}
	unsigned char samno[21]={0};
	HexToStr((unsigned char *)Response,10,samno);
	ICC_Reader_PowerOff(hReader,0x11);
	ICC_Reader_Close(hReader);
	//发送http请求
	char addr[300]={0};
	DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),"C:\\Program Files (x86)\\PDS_HNKG\\config.ini");
	//DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),"D:\\config.ini");	

	CInternetSession m_session("Webservice32");
	CString HttpResponse;
	try
	{
		CString strData;
//		char requestUrl[500]={"http://221.176.197.13:8011/Api!CardIdentify.do?account=test&password=111111&csno=410425200810190216&macno=000011&samno=123456&doctype=1&funtype=0&para=0|1|0&userid=001"};
		char requestUrl[500]={0};
		sprintf(requestUrl,"%s?account=%s&password=%s&csno=%s&macno=%s&samno=%s&doctype=%d&funtype=1&para=%s&userid=%s",
			addr,account,password,csno,macno,samno,doctype,para,userid);
		CHttpFile *pFile;
		pFile = (CHttpFile *) m_session.OpenURL(requestUrl);
		DWORD Code;
		pFile->QueryInfoStatusCode(Code);
		if(Code!=200)
		{
			return CANT_FINDWEB;
		}
		while(pFile->ReadString(strData))
			HttpResponse+=strData;
		pFile->Close();
	}
	catch(CInternetException* e)  //捕获异常
	{
		TCHAR pszError[200];
		e->GetErrorMessage(pszError, 200);
		//::MessageBox(NULL,pszError,NULL,MB_OK);
		e->Delete();
		return HTTP_EXCEPTION;
	}
	m_session.Close();
	char rtstr[10]={0};
	memcpy(rtstr,HttpResponse.GetBuffer(0),4);

	if(0==strcmp(rtstr,"0000"))
	{
		HANDLE hDev;
		char ATR[50]={0};
		rt=iDOpenPort();
		if(rt) return rt;
		rt=PowerOn(hDev,0x01,ATR);
		if(rt) return rt;
		rt=PowerOn(hDev,0x11,ATR);
		if(rt) return rt;
		rt=IVerifyPIN(hDev,pin);
		if(rt) return rt;
	}
	else
	{
		return atoi(rtstr);
	}
	/////////////////////////////////////////////////////////////
	HANDLE hCard;
	int flag=atoi(para);
	if(flag == 102)
	{
		//照片
		int i=iW_DDF1EF07Info(hCard,(unsigned char *)dataIn);
		return i;
	}
	const char * split = "|"; 
	vector<string> vs;
	char * In=NULL; 
	In = strtok (dataIn,split);
	while(In!=NULL)
	{
		vs.push_back(In);
		In = strtok (NULL,split);
	}
	char * pa=NULL; 
	pa = strtok (para,split);
	int index=0;
	while(pa!=NULL)
	{
		int flag=atoi(pa);
		if(flag==0) 
		{
			iDClosePort();
			return 114;
		}
		if(flag<=57)
		{
			//开始写
			ITEMSELECT pvSelect={0};
			//DWORD pdwErrCode;
			pvSelect.wItemFlag=flag;
			pvSelect.pValue=(void *)vs[index++].c_str();
			pvSelect.wValueLen=4000;
			//pvSelect.pdwErrCode=&pdwErrCode;
			int i=wsc_PutCardInfo(hCard,&pvSelect,1);
			if(i)	
			{
				iDClosePort();
				return 115;
			}
			//结束写
		}
		pa = strtok (NULL,split);
	}
	iDClosePort();
	return 0;
}
