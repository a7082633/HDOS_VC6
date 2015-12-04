// HD_RWHealInterface.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "PDS_RWHealInterface.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//获取dll的HMODULE
HMODULE GetCurrentModule()
{
#if _MSC_VER < 1300    // earlier than .NET compiler (VC 6.0)
	
	// Here's a trick that will get you the handle of the module
	// you're running in without any a-priori knowledge:
	// http://www.dotnet247.com/247reference/msgs/13/65259.aspx
	
	MEMORY_BASIC_INFORMATION mbi;
	static int dummy;
	VirtualQuery( &dummy, &mbi, sizeof(mbi) );
	
	return reinterpret_cast<HMODULE>(mbi.AllocationBase);
	
#else    // VC 7.0
	
	// from ATL 7.0 sources
	
	return reinterpret_cast<HMODULE>(&__ImageBase);
#endif
}
int GetConfigFullPath2(TCHAR *configFullPath)
{
	unsigned long r=GetModuleFileName(GetCurrentModule(),configFullPath,MAX_PATH);
	if(r==0)
	{
		return 120;
	}
	char *pc=strrchr(configFullPath,'\\');
	*pc=0;
	strcat(configFullPath,"\\SSSE32.dll");
	return 0;
}
//加载SSSE32
TCHAR configFullPath_dll[MAX_PATH]; // MAX_PATH
int ret=GetConfigFullPath2(configFullPath_dll);
HMODULE hModule=::LoadLibrary(configFullPath_dll);
typedef int(__stdcall *FXN)(char*);
typedef int(__stdcall *FXN2)(long);
typedef int(__stdcall *FXN3)(long,unsigned char *);
typedef int(__stdcall *FXN4)(long,unsigned char);
typedef int(__stdcall *FXN5)(unsigned char *,int,unsigned char *);
typedef int(__stdcall *FXN6)(long,char *);
typedef int(__stdcall *FXN7)(long,unsigned char,unsigned char*);
typedef int(__stdcall *FXN8)(long,unsigned char,long,unsigned char*,unsigned char*);
typedef int(__stdcall *FXN9)(long,long,unsigned char*,unsigned char*);
//
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
//MHC_CARDINTERFACE_API int __stdcall IDOpenPort(char *account,char *password)
//{
//	char addr[300]={0};
////	char des[300]={0};
////	CString sdes;
////	::GetCurrentDirectory(300,des);
////	sdes.Format("%s\\config.ini",des);
////	::MessageBox(NULL,sdes,NULL,MB_OK);
//	DWORD ConfigLen=GetPrivateProfileString("INFO","Device_Address",NULL,addr,sizeof(addr),"D:\\config.ini");
//	//DWORD ConfigLen=GetPrivateProfileString("INFO","Device_Address",NULL,addr,sizeof(addr),".\\config.ini");
//	//::MessageBox(NULL,addr,NULL,MB_OK);
//	//char *addr="http://221.176.197.13:8011/Api!DeviceIdentify.do";
//	/////////////////////////////////////////////////////////
//	long hReader=ICC_Reader_Open("USB1");
//	char cmd[100]={0};
//	unsigned char Response[50]={0};
//	if(hReader<=0)//设备打开失败返回
//	{
//		return hReader;
//	}
//	//获取sam卡序列号
//		//操作SAM卡
//	int rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam卡复位
//	if(rt<=0)
//	{
//		return rt;
//	}
//		//选SAM卡的MF
//	memset(cmd,0,100);
//	memset(Response,0,50);
//	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
//	int len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
//	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
//	{
//		return IFD_ICC_TypeError;
//	}
//		//选0015
//	memset(cmd,0,100);
//	memset(Response,0,50);
//	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
//	len = ICC_Reader_Application(hReader,0x11,7,(unsigned char *)cmd,Response);
//	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
//	{
//		return IFD_ICC_TypeError;
//	}
//		//读取sam卡的序列号
//	memset(cmd,0,100);
//	memset(Response,0,50);
//	memcpy(cmd, "\x00\xB0\x00\x00\x0A",5); 
//	len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
//	if(len<=0||Response[len-2]!=0x90)
//	{
//		return IFD_ICC_TypeError;
//	}
//	unsigned char SamNo[21]={0};
//	HexToStr((unsigned char *)Response,10,SamNo);
//	//获取机具号
//	char Dev_Ser[50]={0};
//	rt=ICC_Reader_GetDeviceCSN(hReader,Dev_Ser);
//	if(rt<=0)
//	{
//		return rt;
//	}
//	//发送http请求
//	CInternetSession m_session("Webservice32");
//	CHttpFile *pFile;
//	//char HttpResponse[500]={0};
//	CString HttpResponse="";
//	try
//	{
//		CString strData;
//		char requestUrl[500]={0};
//		//char requestUrl[500]={"http://221.176.197.13:8011/Api!DeviceIdentify.do?account=test&password=111111&macno=000011&samno=123456"};
//		sprintf(requestUrl,"%s?account=%s&password=%s&macno=%s&samno=%s",
//			addr,account,password,Dev_Ser,SamNo);
//		//::MessageBox(NULL,requestUrl,NULL,MB_OK);
//		DWORD   dwFlags   =   INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_RELOAD; 
//		pFile = (CHttpFile *) m_session.OpenURL(requestUrl,1,dwFlags);
//		DWORD Code;
//		pFile->QueryInfoStatusCode(Code);
//		if(Code!=200)
//		{
//			return CANT_FINDWEB;
//		}
//		//::MessageBox(NULL,"haha",NULL,MB_OK);
//		while(pFile->ReadString(strData))
//			HttpResponse+=strData;
//		//::MessageBox(NULL,requestUrl,NULL,MB_OK);
//	}
//	catch(CInternetException* e)  //捕获异常
//	{
//		TCHAR pszError[200];
//		e->GetErrorMessage(pszError, 200);
//		//::MessageBox(NULL,pszError,NULL,MB_OK);
//		e->Delete();
//		return HTTP_EXCEPTION;
//	}
//	//pFile->Close();
//	m_session.Close();
//	char rtstr[10]={0};
//	memcpy(rtstr,HttpResponse.GetBuffer(0),4);
//	HttpResponse.ReleaseBuffer();
//	ICC_Reader_Close(hReader);
//	if(0==strcmp(rtstr,"0000"))
//		return iDOpenPort();
//	else return atoi(rtstr);
////	return 0;
//}
MHC_CARDINTERFACE_API int __stdcall IDClosePort(void)
{
	return iDClosePort();
}
MHC_CARDINTERFACE_API int __stdcall IVerifyPIN(HANDLE hDev,char * PIN)
{
	int rt=iVerifyPIN(hDev,PIN);
	return rt;
}
//MHC_CARDINTERFACE_API int __stdcall IPowerOn(HANDLE hDev,int slot, 
//											 char * ATR,char *account,
//											 char *password,int doctype,
//											 char *para,char *userid,char *pin)
//{
//	long hReader=ICC_Reader_Open("USB1");
//	char cmd[100]={0};
//	unsigned char Response[50]={0};
//	if(hReader<=0)//设备打开失败返回
//	{
//		return hReader;
//	}
//	//取卡的芯片号
//		//请求卡片
//	int rt=0;
//	rt=PICC_Reader_Request(hReader);
//	if(rt!=0)
//	{
//		return rt;
//	}
//		//防碰撞
//	unsigned char uid[10]={0};
//	rt =PICC_Reader_anticoll(hReader,uid);
//	if(rt)
//	{
//		return rt;
//	}
//		//选卡
//	rt=PICC_Reader_Select(hReader,0x41);
//	if(rt)
//	{
//		return rt;
//	}
//		//上电
//	rt=PICC_Reader_PowerOnTypeA(hReader,Response);
//	if(rt<=0)
//	{
//		return rt;
//	}
//	unsigned char csno[17]={0};
//	HexToStr(Response+5,8,csno);
//	//获取机具号（从芯片获取）
//	char macno[50]={0};
//	rt=ICC_Reader_GetDeviceCSN(hReader,macno);
//	if(rt<=0)
//	{
//		return rt;
//	}
//	//获取sam卡序列号
////	char SamATR[50]={0};
////	rt=PowerOn(hDev,0x11,SamATR);
////	if(rt)
////	{
////		return rt;
////	}
////	char samno[300]={0};
////	rt=iReader_SAM_Public((int)hDev,samno);
////	if(rt)
////	{
////		return rt;
////	}
//		//操作SAM卡
//	memset(Response,0,50);
//	rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam卡复位
//	if(rt<=0)
//	{
//		return rt;
//	}
//		//选SAM卡的MF
//	memset(cmd,0,100);
//	memset(Response,0,50);
//	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
//	int len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
//	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
//	{
//		return len;
//	}
//	//选0015
//	memset(cmd,0,100);
//	memset(Response,0,50);
//	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
//	len = ICC_Reader_Application(hReader,0x11,7,(unsigned char *)cmd,Response);
//	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
//	{
//		return IFD_ICC_TypeError;
//	}
//		//读取sam卡的序列号
//	memset(cmd,0,100);
//	memset(Response,0,50);
//	memcpy(cmd, "\x00\xB0\x00\x00\x0A",5); 
//	len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
//	if(len<=0||Response[len-2]!=0x90)
//	{
//		return IFD_ICC_TypeError;
//	}
//	unsigned char samno[21]={0};
//	HexToStr((unsigned char *)Response,10,samno);
//	ICC_Reader_PowerOff(hReader,0x11);
//	//发送http请求
//	char addr[300]={0};
//	DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),".\\config.ini");
//	//MessageBox(NULL,addr,NULL,MB_OK);
//	CInternetSession m_session("Webservice32");
//	CString HttpResponse;
//	try
//	{
//		CString strData;
////		char requestUrl[500]={"http://221.176.197.13:8011/Api!CardIdentify.do?account=test&password=111111&csno=410425200810190216&macno=000011&samno=123456&doctype=1&funtype=0&para=0|1|0&userid=001"};
//		char requestUrl[500]={0};
//		sprintf(requestUrl,"%s?account=%s&password=%s&csno=%s&macno=%s&samno=%s&doctype=%d&funtype=1&para=%s&userid=%s",
//			addr,account,password,csno,macno,samno,doctype,para,userid);
//		//MessageBox(NULL,requestUrl,NULL,MB_OK);
//		CHttpFile *pFile;
//		//MessageBox(NULL,requestUrl,NULL,MB_OK);
//		pFile = (CHttpFile *) m_session.OpenURL(requestUrl);
//		DWORD Code;
//		pFile->QueryInfoStatusCode(Code);
//		if(Code!=200)
//		{
//			return CANT_FINDWEB;
//		}
//		while(pFile->ReadString(strData))
//			HttpResponse+=strData;
//		pFile->Close();
//	}
//	catch(CInternetException* e)  //捕获异常
//	{
//		TCHAR pszError[200];
//		e->GetErrorMessage(pszError, 200);
//		::MessageBox(NULL,pszError,NULL,MB_OK);
//		e->Delete();
//		return HTTP_EXCEPTION;
//	}
//	m_session.Close();
//	char rtstr[10]={0};
//	memcpy(rtstr,HttpResponse.GetBuffer(0),4);
//	ICC_Reader_Close(hReader);
//
//	if(0==strcmp(rtstr,"0000"))
//	{
//		rt=PowerOn(hDev,slot,ATR);
//		if(rt) return rt;
//		rt=IVerifyPIN(hDev,pin);
//		return rt;
//	}
//	else return atoi(rtstr);
//}
MHC_CARDINTERFACE_API int __stdcall IChange_Pin(int hDev,char *oldPin,char *newPin)
{
	return iChange_Pin(hDev,oldPin,newPin);
}
int GetConfigFullPath(TCHAR *configFullPath)
{
	unsigned long r=GetModuleFileName(GetCurrentModule(),configFullPath,MAX_PATH);
	if(r==0)
	{
		return 122;
	}
	char *pc=strrchr(configFullPath,'\\');
	*pc=0;
	strcat(configFullPath,"\\config.ini");
	return 0;
}
MHC_CARDINTERFACE_API int __stdcall IR_ReadCard(char *para,char *dataOut,
												char *account,char *password,
												int doctype,char *userid,
												char *pin)
{
//	::MessageBox(NULL,exeFullPath,NULL,MB_OK);
//	CString g_szOcxPath=::AfxGetApp()->m_pszHelpFilePath;
//	::MessageBox(NULL,g_szOcxPath,NULL,MB_OK);
//	CString g_szOcxName =::AfxGetApp()->m_pszExeName;
//	::MessageBox(NULL,g_szOcxName,NULL,MB_OK);
	//读之前判断进程是否存在
	if(!FindProcess())
	{
		::MessageBox(NULL,"请运行卫计委卡管程序","提示",MB_OK);
		return PROCCESS_EXIST;
	}
	//获取SSSE32函数
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN ICC_Reader_Open=(FXN)::GetProcAddress(hModule,"ICC_Reader_Open"); //打开端口
	FXN2 PICC_Reader_Request=(FXN2)::GetProcAddress(hModule,"PICC_Reader_Request"); //请求卡片
	FXN2 ICC_Reader_Close=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close"); //关闭端口
	FXN3 PICC_Reader_anticoll=(FXN3)::GetProcAddress(hModule,"PICC_Reader_anticoll"); //防碰撞
	FXN4 PICC_Reader_Select=(FXN4)::GetProcAddress(hModule,"PICC_Reader_Select"); //选卡
	FXN3 PICC_Reader_PowerOnTypeA=(FXN3)::GetProcAddress(hModule,"PICC_Reader_PowerOnTypeA"); //TYPE A上电
	FXN5 HexToStr=(FXN5)::GetProcAddress(hModule,"HexToStr"); //TYPE A上电
	FXN4 ICC_Reader_PowerOff=(FXN4)::GetProcAddress(hModule,"ICC_Reader_PowerOff"); //接触卡下电
	FXN6 ICC_Reader_GetDeviceCSN=(FXN6)::GetProcAddress(hModule,"ICC_Reader_GetDeviceCSN"); //获取芯片号
	FXN7 ICC_Reader_pre_PowerOn=(FXN7)::GetProcAddress(hModule,"ICC_Reader_pre_PowerOn"); //非接上电
	FXN8 ICC_Reader_Application=(FXN8)::GetProcAddress(hModule,"ICC_Reader_Application"); //发送指令
	//先获取配置文件路径
	TCHAR configFullPath[MAX_PATH]; // MAX_PATH
	int rt=GetConfigFullPath(configFullPath);
	if(rt!=0) return rt;
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
	unsigned char csno[50]={0};
	HexToStr(Response,rt,csno);
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
	rt=ICC_Reader_pre_PowerOn(hReader,0x11,Response); //sam卡复位
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
	//::MessageBox(NULL,"获取数据正常!",NULL,MB_OK);
	DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),configFullPath);
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
	
		//::MessageBox(NULL,requestUrl,NULL,MB_OK);

		CHttpFile *pFile;
		pFile = (CHttpFile *) m_session.OpenURL(requestUrl);
		DWORD Code;
		pFile->QueryInfoStatusCode(Code);
		if(Code!=200)
		{
			m_session.Close();
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
		m_session.Close();
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
		case 101:
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
				case 101:
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
		case 1000:
			{
				char XM[50]={0};char XB[50]={0};char MZ[50]={0};char CSRQ[50]={0};char SFZH[50]={0};
				re=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char KYXQ[2]={0};char BRDH1[21]={0};char BRDH2[21]={0};char YLFYZFFS1[21]={0};char YLFYZFFS2[21]={0};char YLFYZFFS3[21]={0};
				re=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char DZLB1[21]={0};char DZ1[120]={0};char DZLB2[21]={0};char DZ2[120]={0};		  
				re=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char LXRXM1[40]={0};char LXRGX1[2]={0};char LXRDH1[30]={0};char LXRXM2[40]={0};char LXRGX2[2]={0};       
				char LXRDH2[30]={0};char LXRXM3[40]={0};char LXRGX3[2]={0};char LXRDH3[30]={0}; 
				re=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char WHCD[10]={0};char HYZK[10]={0};char ZY[10]={0};
				re=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);
				if(re)
				{
					iDClosePort();
					return re;
				}
				int len=strlen(dataOut);
				sprintf(dataOut+len,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s|",
					XM,XB,MZ,CSRQ,SFZH,BRDH1,BRDH2,DZLB1,DZ1,DZLB2,DZ2,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,
					LXRXM3,LXRGX3,LXRDH3,WHCD,HYZK,ZY);
				break;
			}
		case 1003:
			{
				char szData[3283]={0};
				re=iR_DF03ED_ALLInfo(hDev,1,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1004:
			{
				char szData[3283]={0};
				re=iR_DF03ED_ALLInfo(hDev,2,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1005:
			{
				char szData[3283]={0};
				re=iR_DF03ED_ALLInfo(hDev,3,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1006:
			{
				char szData[3283]={0};
				re=iR_DF03ED_ALLInfo(hDev,4,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1007:
			{
				char szData[3283]={0};
				re=iR_DF03ED_ALLInfo(hDev,5,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1013:
			{
				char szData[1867]={0};
				re=iR_DF03EE_ALLInfo(hDev,1,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1014:
			{
				char szData[1867]={0};
				re=iR_DF03EE_ALLInfo(hDev,2,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1015:
			{
				char szData[1867]={0};
				re=iR_DF03EE_ALLInfo(hDev,3,szData);
				if(re)
				{
					iDClosePort();
					return re;
				}
				char *p=szData;
				while(*p!='\0')
				{
					if(*p=='|')
						*p=',';
					p++;
				}
				strcat(dataOut,szData);
				strcat(dataOut,"|");
				break;
			}
		case 1023:
			{
				char GMWZMC[30]={0};
				char GMFY[120]={0};
				for(int i=1;i<=3;i++)
				{
					re=iR_DF02EF07Info(hDev,i,GMWZMC,GMFY);
					if(re)
					{
						iDClosePort();
						return re;
					}
					strcat(dataOut,GMWZMC); strcat(dataOut,",");strcat(dataOut,GMFY); strcat(dataOut,",");
					memset(GMWZMC,0,30);memset(GMFY,0,120);
				}
				int n=strlen(dataOut);
				dataOut[n-1]='|';
				break;
			}
		case 1025:
			{
				char MYJZMC[30]={0};	
				char MYJZSJ[10]={0};
				for(int i=1;i<=10;i++)
				{
					re=iR_DF02EF08Info(hDev,i,MYJZMC,MYJZSJ);
					if(re)
					{
						iDClosePort();
						return re;
					}
					strcat(dataOut,MYJZMC); strcat(dataOut,",");strcat(dataOut,MYJZSJ); strcat(dataOut,",");
					memset(MYJZMC,0,30);memset(MYJZSJ,0,10);
				}
				int n=strlen(dataOut);
				dataOut[n-1]='|';
				break;
			}
		case 1027:
			{
				char MZJLBS1[30]={0};	
				char MZJLBS2[10]={0};
				char MZJLBS3[10]={0};
				char MZJLBS4[10]={0};
				char MZJLBS5[10]={0};
				re=iR_DF03EF06Info(hDev,MZJLBS1,MZJLBS2,MZJLBS3,MZJLBS4,MZJLBS5);
				if(re)
				{
					iDClosePort();
					return re;
				}
				if(!strcmp(MZJLBS1,"ff")||!strcmp(MZJLBS1,"FF"))
					strcpy(MZJLBS1,"F");
				else
					strcpy(MZJLBS1,"0");
				if(!strcmp(MZJLBS2,"ff")||!strcmp(MZJLBS2,"FF"))
					strcpy(MZJLBS2,"F");
				else
					strcpy(MZJLBS2,"0");
				if(!strcmp(MZJLBS3,"ff")||!strcmp(MZJLBS3,"FF"))
					strcpy(MZJLBS3,"F");
				else
					strcpy(MZJLBS3,"0");
				if(!strcmp(MZJLBS4,"ff")||!strcmp(MZJLBS4,"FF"))
					strcpy(MZJLBS4,"F");
				else
					strcpy(MZJLBS4,"0");
				if(!strcmp(MZJLBS5,"ff")||!strcmp(MZJLBS5,"FF"))
					strcpy(MZJLBS5,"F");
				else
					strcpy(MZJLBS5,"0");
				int len=strlen(dataOut);
				sprintf(dataOut+len,"%s%s%s%s%s|",MZJLBS1,MZJLBS2,MZJLBS3,MZJLBS4,MZJLBS5);
				break;
			}
		case 1028:
			{
				char ZYJLBS1[30]={0};	
				char ZYJLBS2[10]={0};
				char ZYJLBS3[10]={0};
				re=iR_DF03EF05Info(hDev,ZYJLBS1,ZYJLBS2,ZYJLBS3);
				if(re)
				{
					iDClosePort();
					return re;
				}
				if(!strcmp(ZYJLBS1,"ff")||!strcmp(ZYJLBS1,"FF"))
					strcpy(ZYJLBS1,"F");
				else
					strcpy(ZYJLBS1,"0");
				if(!strcmp(ZYJLBS2,"ff")||!strcmp(ZYJLBS2,"FF"))
					strcpy(ZYJLBS2,"F");
				else
					strcpy(ZYJLBS2,"0");
				if(!strcmp(ZYJLBS3,"ff")||!strcmp(ZYJLBS3,"FF"))
					strcpy(ZYJLBS3,"F");
				else
					strcpy(ZYJLBS3,"0");
				int len=strlen(dataOut);
				sprintf(dataOut+len,"%s%s%s|",ZYJLBS1,ZYJLBS2,ZYJLBS3);
				break;
			}
		default:
			iDClosePort();
			return 120;
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
	//获取SSSE32函数
//	TCHAR configFullPath[MAX_PATH]; // MAX_PATH
//	int rt=GetConfigFullPath(configFullPath);
//	if(rt!=0) return rt;
//	HMODULE hModule=::LoadLibrary(configFullPath);
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN ICC_Reader_Open=(FXN)::GetProcAddress(hModule,"ICC_Reader_Open"); //打开端口
	FXN2 PICC_Reader_Request=(FXN2)::GetProcAddress(hModule,"PICC_Reader_Request"); //请求卡片
	FXN2 ICC_Reader_Close=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close"); //关闭端口
	FXN3 PICC_Reader_anticoll=(FXN3)::GetProcAddress(hModule,"PICC_Reader_anticoll"); //防碰撞
	FXN4 PICC_Reader_Select=(FXN4)::GetProcAddress(hModule,"PICC_Reader_Select"); //选卡
	FXN3 PICC_Reader_PowerOnTypeA=(FXN3)::GetProcAddress(hModule,"PICC_Reader_PowerOnTypeA"); //TYPE A上电
	FXN5 HexToStr=(FXN5)::GetProcAddress(hModule,"HexToStr"); //TYPE A上电
	FXN4 ICC_Reader_PowerOff=(FXN4)::GetProcAddress(hModule,"ICC_Reader_PowerOff"); //接触卡下电
	FXN6 ICC_Reader_GetDeviceCSN=(FXN6)::GetProcAddress(hModule,"ICC_Reader_GetDeviceCSN"); //获取芯片号
	FXN7 ICC_Reader_pre_PowerOn=(FXN7)::GetProcAddress(hModule,"ICC_Reader_pre_PowerOn"); //非接上电
	FXN8 ICC_Reader_Application=(FXN8)::GetProcAddress(hModule,"ICC_Reader_Application"); //发送指令
	//先获取配置文件路径
	TCHAR configFullPath[MAX_PATH]; // MAX_PATH
	int rt=GetConfigFullPath(configFullPath);
	if(rt!=0) return rt;
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
	unsigned char csno[40]={0};
	HexToStr(Response,rt,csno);
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
	rt=ICC_Reader_pre_PowerOn(hReader,0x11,Response); //sam卡复位
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
	DWORD ConfigLen=GetPrivateProfileString("INFO","Card_Address","DefaultName",addr,sizeof(addr),configFullPath);
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
			m_session.Close();
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
		m_session.Close();
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
	char *p=dataIn;
	if(flag==1003||flag==1004||flag==1005||flag==1006||flag==1007||flag==1008||flag==1013||flag==1014||flag==1015||flag==1016||flag==1024||flag==1026)
	{
		while(*p!='\0')
		{
			if(*p==',')
			{
				*p='|';
			}
			p++;
		}
	}
	if(flag!=1003&&flag!=1004&&flag!=1005&&flag!=1006&&flag!=1007&&flag!=1008&&flag!=1013&&flag!=1014&&flag!=1015&&flag!=1016)
	{
		In = strtok (dataIn,split);
		while(In!=NULL)
		{
			vs.push_back(In);
			In = strtok (NULL,split);
		}
	}
	HANDLE hDev;
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
		if(flag>=41&&flag<=55)
		{
			switch(flag)
			{
			case 41:
				{
					int i=iW_DF02EF05Info(hDev,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 42:
				{
					int i=iW_DF02EF05Info(hDev,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 43:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 44:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 45:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 46:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 47:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 48:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 49:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 50:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 51:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 52:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 53:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL,NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 54:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str(),NULL);
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 55:
				{
					int i=iW_DF02EF05Info(hDev,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,(char *)vs[index++].c_str());
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			case 56:
				{
					int i=iW_DF02EF06Info(hDev,(char *)vs[index++].c_str());
					if(i)	
					{
						iDClosePort();
						return i;
					}
					break;
				}
			}//end switch
		}
		else if(flag<=57)
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
		}else if(flag==1024)
		{
			HANDLE hDev;
			int re=iW_DF02EF07Info(hDev,(char *)vs[index].c_str(),(char *)vs[index+1].c_str());
			if(re)
			{
				iDClosePort();
				return re;
			}
			index+=2;
		}else if(flag==1026)
		{
			int re=iW_DF02EF08Info(hDev,(char *)vs[index].c_str(),(char *)vs[index+1].c_str());
			if(re)
			{
				iDClosePort();
				return re;
			}
			index+=2;
		}else if(flag==1003)
		{
			int re=iW_DF03ED_ALLInfo(hDev,1,dataIn);
			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1004)
		{
			int re=iW_DF03ED_ALLInfo(hDev,2,dataIn);
			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1005)
		{
			int re=iW_DF03ED_ALLInfo(hDev,3,dataIn);
			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1006)
		{
			int re=iW_DF03ED_ALLInfo(hDev,4,dataIn);
			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1007)
		{
			int re=iW_DF03ED_ALLInfo(hDev,5,dataIn);
			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1013)
		{
			int re= iW_DF03EE_ALLInfo(hDev,1,dataIn);

			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1014)
		{
			int re=iW_DF03EE_ALLInfo(hDev,2,dataIn);
			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1015)
		{
			int re=iW_DF03EE_ALLInfo(hDev,3,dataIn);
			if(re)
			{
				iDClosePort();
				return re;
			}
		}else if(flag==1027)
		{
			for(int i=1;i<=5;i++)
			{
				string str=dataIn;
				str=str.substr(i-1,1);
				if(!str.compare("F")||!str.compare("f"))
				{
					int re=iErase_DF03EF06Info(hDev,i);
					if(re)
					{
						iDClosePort();
						return re;
					}
				}else if(!str.compare("0"))
				{
					int re=iW_DF03EF06Info(hDev,i);
					if(re)
					{
						iDClosePort();
						return re;
					}
				}
			}
		}else if(flag==1028)
		{
			for(int i=1;i<=3;i++)
			{
				string str=dataIn;
				str=str.substr(i-1,1);
				if(!str.compare("F")||!str.compare("f"))
				{
					int re=iErase_DF03EF05Info(hDev,i);
					if(re)
					{
						iDClosePort();
						return re;
					}
				}else if(!str.compare("0"))
				{
					int re=iW_DF03EF05Info(hDev,i);
					if(re)
					{
						iDClosePort();
						return re;
					}
				}
			}
		}else if(flag==1008)
		{
			char MZJLBS1[30]={0};	
			char MZJLBS2[10]={0};
			char MZJLBS3[10]={0};
			char MZJLBS4[10]={0};
			char MZJLBS5[10]={0};
			int re=iR_DF03EF06Info(hDev,MZJLBS1,MZJLBS2,MZJLBS3,MZJLBS4,MZJLBS5);
			if(re)
			{
				iDClosePort();
				return re;
			}
			int i=0;
			for(;i<5;i++)
			{
				switch(i)
				{
				case 0:
					{
						if(!strcmp(MZJLBS1,"ff")||!strcmp(MZJLBS1,"FF"))
						{
							re=iW_DF03ED_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF06Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				case 1:
					{
						if(!strcmp(MZJLBS2,"ff")||!strcmp(MZJLBS2,"FF"))
						{
							re=iW_DF03ED_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF06Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				case 2:
					{
						if(!strcmp(MZJLBS3,"ff")||!strcmp(MZJLBS3,"FF"))
						{
							re=iW_DF03ED_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF06Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				case 3:
					{
						if(!strcmp(MZJLBS4,"ff")||!strcmp(MZJLBS4,"FF"))
						{
							re=iW_DF03ED_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF06Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				case 4:
					{
						if(!strcmp(MZJLBS5,"ff")||!strcmp(MZJLBS5,"FF"))
						{
							re=iW_DF03ED_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF06Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				}//end switch
			}//end for
			if(i==5)
			{
				for(i=0;i<5;i++)
				{
					iErase_DF03EF06Info(hDev,i+1);
				}
				re=iW_DF03ED_ALLInfo(hDev,1,dataIn);
				if(re)
				{
					iDClosePort();
					return re;
				}
				re=iW_DF03EF06Info(hDev,1);
			}
		}else if(flag==1016)
		{
			char ZYJLBS1[30]={0};	
			char ZYJLBS2[10]={0};
			char ZYJLBS3[10]={0};
			int re=iR_DF03EF05Info(hDev,ZYJLBS1,ZYJLBS2,ZYJLBS3);
			if(re)
			{
				iDClosePort();
				return re;
			}
			int i=0;
			for(;i<3;i++)
			{
				switch(i)
				{
				case 0:
					{
						if(!strcmp(ZYJLBS1,"ff")||!strcmp(ZYJLBS1,"FF"))
						{
							re=iW_DF03EE_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF05Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				case 1:
					{
						if(!strcmp(ZYJLBS2,"ff")||!strcmp(ZYJLBS2,"FF"))
						{
							re=iW_DF03EE_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF05Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				case 2:
					{
						if(!strcmp(ZYJLBS3,"ff")||!strcmp(ZYJLBS3,"FF"))
						{
							re=iW_DF03EE_ALLInfo(hDev,i+1,dataIn);
							if(re)
							{
								iDClosePort();
								return re;
							}
							re=iW_DF03EF05Info(hDev,i+1);
							if(re)
							{
								iDClosePort();
								return re;
							}
							iDClosePort();
							return 0;
						}
						break;
					}
				}//end switch
			}//end for
			if(i==3)
			{
				for(i=0;i<3;i++)
				{
					iErase_DF03EF05Info(hDev,i+1);
				}
				re=iW_DF03EE_ALLInfo(hDev,1,dataIn);
				if(re)
				{
					iDClosePort();
					return re;
				}
				re=iW_DF03EF05Info(hDev,1);
			}
		}else
		{
			iDClosePort();
			return 120;
		}
		pa = strtok (NULL,split);
	}
	iDClosePort();
	return 0;
}
MHC_CARDINTERFACE_API long __stdcall ICC_Reader_Open(char* dev_Name)
{
	//获取SSSE32函数
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN HNICC_Reader_Open=(FXN)::GetProcAddress(hModule,"ICC_Reader_Open"); //打开端口
	long rt=HNICC_Reader_Open(dev_Name);
	return rt;
}

MHC_CARDINTERFACE_API long __stdcall ICC_Reader_Close(long ReaderHandle)
{
	//获取SSSE32函数
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN2 HNICC_Reader_Close=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close"); //打开端口
	long rt=HNICC_Reader_Close(ReaderHandle);
	return rt;
}


MHC_CARDINTERFACE_API long __stdcall PICC_Reader_FindCard(long ReaderHandle)
{
	//获取SSSE32函数
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN2 PICC_Reader_Request=(FXN2)::GetProcAddress(hModule,"PICC_Reader_Request"); //请求卡片
	FXN3 PICC_Reader_anticoll=(FXN3)::GetProcAddress(hModule,"PICC_Reader_anticoll"); //防碰撞
	FXN4 PICC_Reader_Select=(FXN4)::GetProcAddress(hModule,"PICC_Reader_Select"); //选卡
	FXN3 PICC_Reader_PowerOnTypeA=(FXN3)::GetProcAddress(hModule,"PICC_Reader_PowerOnTypeA"); //TYPE A上电
	long rt=PICC_Reader_Request(ReaderHandle);
	if(rt!=0)
	{
		return rt;
	}
	//防碰撞
	unsigned char uid[10]={0};
	rt =PICC_Reader_anticoll(ReaderHandle,uid);
	if(rt)
	{
		return rt;
	}
	//选卡
	rt=PICC_Reader_Select(ReaderHandle,0x41);
	if(rt)
	{
		return rt;
	}
	//上电
	unsigned char Response[200]={0};
	rt=PICC_Reader_PowerOnTypeA(ReaderHandle,Response);
	if(rt<=0)
	{
		return rt;
	}
	return 0;
}

MHC_CARDINTERFACE_API long __stdcall  PICC_Reader_Application(long  ReaderHandle,long Lenth_of_Command_APDU, unsigned  char*  Command_APDU, unsigned  char*  Response_APDU)
{
	//获取SSSE32函数
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN9 HNPICC_Reader_Application=(FXN9)::GetProcAddress(hModule,"PICC_Reader_Application"); //发送指令
	long rt=HNPICC_Reader_Application(ReaderHandle,Lenth_of_Command_APDU,Command_APDU,Response_APDU);
	return rt;
}

MHC_CARDINTERFACE_API long __stdcall  StrToHex(unsigned char *strIn,int inLen,unsigned char *strOut)//将字符命令流转为16进制流
{
	//获取SSSE32函数
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN5 HNStrToHex=(FXN5)::GetProcAddress(hModule,"StrToHex"); //发送指令
	long rt=HNStrToHex(strIn,inLen,strOut);
	return rt;
}
MHC_CARDINTERFACE_API long __stdcall  HexToStr(unsigned char *strIn,int inLen,unsigned char *strOut)
{
	//获取SSSE32函数
	if(hModule==NULL) 
	{
		::MessageBox(NULL,"加载SSSE32失败","提示",MB_OK);
		return 121;
	}
	FXN5 HNHexToStr=(FXN5)::GetProcAddress(hModule,"HexToStr"); //发送指令
	long rt=HNHexToStr(strIn,inLen,strOut);
	return rt;
}