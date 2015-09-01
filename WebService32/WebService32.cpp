// WebService32.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include <string>
#include <iostream>
#include "WebService32.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
 
bool PostHttpPage(const std::string& hostName, const std::string& pathName, const std::string& postData)
{
	using namespace std;
	CInternetSession session("your app agent name");
	try
	{
		INTERNET_PORT nPort = 8011;
		DWORD dwRet = 0;
		CHttpConnection* pServer = session.GetHttpConnection(hostName.c_str(), nPort);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, pathName.c_str());
		CString strHeaders = "Content-Type: application/x-www-form-urlencoded"; // 请求头
		//开始发送请求
		pFile->SendRequest(strHeaders,(LPVOID)postData.c_str(),postData.size());
		pFile->QueryInfoStatusCode(dwRet);
		if (dwRet == HTTP_STATUS_OK)
		{
			CString result, newline;
			while(pFile->ReadString(newline))
			{//循环读取每行内容
				result += newline+"\r\n";
			}
		}
		else
		{
			return false;
		}
		delete pFile;
		delete pServer;
	}
	catch (CInternetException* pEx)
	{
		TCHAR pszError[200];
		pEx->GetErrorMessage(pszError, 200);
		std::cout<<pszError<<std::endl;//显示异常信息
		return false;
	}
	session.Close();
	return true;
}
 //	PostHttpPage("221.176.197.13","Api!CardIdentify.do","account=123&&password=123");
int i=9;
char *rtstr=NULL;
void __stdcall DeleteMemry()
{
	if(rtstr!=NULL)
	{
		delete []rtstr;
		rtstr=NULL;
	}
}
char * __stdcall Authentication(char *addr,char *account,char *password,int doctype,int action)
{
	if(rtstr==NULL)
		rtstr=new char[100];
	memset(rtstr,0x00,100);
	long hReader=ICC_Reader_Open("USB1");
	char cmd[100]={0};
	unsigned char Response[50]={0};
	if(hReader<=0)//设备打开失败返回
	{
		return "打开设备失败";
	}
	//取卡的芯片号
		//请求卡片
	int rt=0;
	rt=PICC_Reader_Request(hReader);
	if(rt!=0)
	{
		return "请求卡片失败";
	}
		//防碰撞
	unsigned char uid[10]={0};
	rt =PICC_Reader_anticoll(hReader,uid);
	if(rt)
	{
		return "防碰撞失败";
	}
		//选卡
	rt=PICC_Reader_Select(hReader,0x41);
	if(rt)
	{
		return "选卡失败";
	}
		//上电
	rt=PICC_Reader_PowerOnTypeA(hReader,Response);
	if(rt<=0)
	{
		return "上电失败!";
	}
	unsigned char CardChipNo[17]={0};
	HexToStr(Response+5,8,CardChipNo);
	//获取机具号（从芯片获取）
	char temp[50]={0};
	rt=ICC_Reader_GetDeviceCSN(hReader,temp);
	if(rt<=0)
	{
		return "获取机具号失败";
	}
	char dev_ser[50]={0};
	memcpy(dev_ser,temp,rt);
	//获取sam卡序列号
		//操作SAM卡
	memset(Response,0,50);
	rt=ICC_Reader_PowerOn(hReader,0x11,Response); //sam卡复位
	if(rt<=0)
	{
		return "SAM卡上电失败";
	}
		//选SAM卡的MF
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x00",5); 
	int len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		return "SAM-其他卡型-00A4000000";
	}
	//选0015
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7); 
	len = ICC_Reader_Application(hReader,0x11,7,(unsigned char *)cmd,Response);
	if( (Response[len-2]!=0x61) && (Response[len-2]!=0x90) )
	{
		return "SAM-其他卡型-00A40000020015";
	}
		//读取sam卡的序列号
	memset(cmd,0,100);
	memset(Response,0,50);
	memcpy(cmd, "\x00\xB0\x00\x00\x0A",5); 
	len = ICC_Reader_Application(hReader,0x11,5,(unsigned char *)cmd,Response);
	if(len<=0||Response[len-2]!=0x90)
	{
		return "00B095000A";
	}
	unsigned char SamNo[21]={0};
	HexToStr((unsigned char *)Response,10,SamNo);
	//发送http请求
	CInternetSession m_session("Webservice32");
	CString HttpResponse;
	try
	{
		CString strData;
		//char *requestUrl="http://221.176.197.13:8011/Api!CardIdentify.do?account=123&&password=123";
		char requestUrl[500]={0};
		sprintf(requestUrl,"%s?account=%s&password=%s&csno=%s&macno=%s&samno=%s&doctype=%d&action=%d",
			addr,account,password,CardChipNo,dev_ser,SamNo,doctype,action);
		CHttpFile *pFile;
		pFile = (CHttpFile *) m_session.OpenURL(requestUrl);
		DWORD Code;
		pFile->QueryInfoStatusCode(Code);
		if(Code!=200)
		{
			strData.Format("页面不存在,链接:%s",requestUrl);
			strcpy(rtstr,strData.GetBuffer(0));
			return rtstr;
		}
		while(pFile->ReadString(strData))
			HttpResponse+=strData;
	}
	catch(CInternetException* e)  //捕获异常
	{
		TCHAR pszError[200];
		e->GetErrorMessage(pszError, 200);
		e->Delete();
		return pszError;
	}
	m_session.Close();
	memcpy(rtstr,HttpResponse.GetBuffer(0),4);
	return rtstr;
}

char * __stdcall Test1()
{
	i=0;
	return NULL;
}
int __stdcall Test2()
{
	return i;
}