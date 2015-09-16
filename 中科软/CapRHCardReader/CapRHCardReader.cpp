// CapRHCardReader.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "CapRHCardReader.h"

HMODULE hModuleD=NULL;
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
int GetConfigFullPath(TCHAR *configFullPath)
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
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	TCHAR configFullPath[MAX_PATH];
	int rt=GetConfigFullPath(configFullPath);
	//::MessageBox(NULL,cofigFullPath,NULL,MB_OK);
	if(hModuleD==NULL)
	{
		hModuleD=::LoadLibrary(configFullPath);
	}
	if(hModuleD==NULL)
		MessageBox(NULL,"加载失败-HDOS",NULL,MB_OK);
//	if(hModuleD!=NULL)
//	{
//		::MessageBox(NULL,"加载成功",NULL,MB_OK);
//	}else
//	{
//		::MessageBox(NULL,"加载失败",NULL,MB_OK);
//	}
    return TRUE;
}
typedef int(__stdcall *FXN)(char *);
typedef int(__stdcall *FXN2)(long);
typedef int(__stdcall *FXN3)(long,unsigned char *);
typedef int(__stdcall *FXN4)(long,unsigned char);
typedef int(__stdcall *FXN5)(long,unsigned char,unsigned char *);
typedef int(__stdcall *FXN6)(long,unsigned char,long,unsigned char*,unsigned char*);
typedef int(__stdcall *FXN7)(long,long,unsigned char*,unsigned char*);
typedef int(__stdcall *FXN8)(long,unsigned char,long,unsigned char*,unsigned char*);
typedef int(__stdcall *FXN9)(long,char *,char *,char *,char *);
typedef int(__stdcall *FXNA)(long,char *);
RHCARDREADERAPI int ICC_Reader_Open()
{
	FXN Reader_Open=(FXN)::GetProcAddress(hModuleD,"ICC_Reader_Open");
	return Reader_Open("USB1");
}
RHCARDREADERAPI int ICC_Reader_Close(int ReaderHandle)
{
	FXN2 Reader_Close=(FXN2)::GetProcAddress(hModuleD,"ICC_Reader_Close");
	return Reader_Close(ReaderHandle);
}
RHCARDREADERAPI int ICC_Reader_Reset(int ReaderHandle, int ICC_Slot_No, unsigned char *Response, int *RespLen)
{
	int re=0;
	unsigned char uid[5]={0};
	FXN2 PICC_Reader_SetTypeA=(FXN2)::GetProcAddress(hModuleD,"PICC_Reader_SetTypeA");
	FXN2 PICC_Reader_Request=(FXN2)::GetProcAddress(hModuleD,"PICC_Reader_Request");
	FXN3 PICC_Reader_anticoll=(FXN3)::GetProcAddress(hModuleD,"PICC_Reader_anticoll");
	FXN4 PICC_Reader_Select=(FXN4)::GetProcAddress(hModuleD,"PICC_Reader_Select");
	FXN3 PICC_Reader_PowerOnTypeA=(FXN3)::GetProcAddress(hModuleD,"PICC_Reader_PowerOnTypeA");
	FXN5 ICC_Reader_pre_PowerOn=(FXN5)::GetProcAddress(hModuleD,"ICC_Reader_pre_PowerOn");
	switch(ICC_Slot_No)
	{
	case 0:
		{
			re = PICC_Reader_SetTypeA(ReaderHandle);
			if(re!=0)
			{
				return re;
			}
			re=PICC_Reader_Request(ReaderHandle);
			if(re!=0)
			{
				return re;
			}
			re = PICC_Reader_anticoll(ReaderHandle,uid);
			if(re!=0)
			{
				return re;
			}
			re = PICC_Reader_Select(ReaderHandle,0x41);
			if(re!=0)
			{
				return re ;
			}
			re = PICC_Reader_PowerOnTypeA(ReaderHandle,Response);
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
		}
		break;
	case 1:
		{
			re=ICC_Reader_pre_PowerOn(ReaderHandle,0x01,Response);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
		}
		break;
	case 2:
		{
			re=ICC_Reader_pre_PowerOn(ReaderHandle,0x11,Response);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
		}
		break;
	case 3:
		{
			re=ICC_Reader_pre_PowerOn(ReaderHandle,0x12,Response);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
		}
		break;
	case 4:
		{
			re=ICC_Reader_pre_PowerOn(ReaderHandle,0x13,Response);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
		}
		break;
	case 5:
		{
			re=ICC_Reader_pre_PowerOn(ReaderHandle,0x14,Response);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
		}
		break;
	}
	return 0;
}
RHCARDREADERAPI int ICC_Reader_PowerOff(int ReaderHandle, int ICC_Slot_No)
{
	int re=0;
	FXN4 ICC_Reader_PowerOff2=(FXN4)::GetProcAddress(hModuleD,"ICC_Reader_PowerOff");
	switch(ICC_Slot_No)
	{
	case 0:
		break;
	case 1:
		{
			re=ICC_Reader_PowerOff2(ReaderHandle,0x01);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
		}
		break;
	case 2:
		{
			re=ICC_Reader_PowerOff2(ReaderHandle,0x11);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
		}
		break;
	case 3:
		{
			re=ICC_Reader_PowerOff2(ReaderHandle,0x12);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
		}
		break;
	case 4:
		{
			re=ICC_Reader_PowerOff2(ReaderHandle,0x13);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
		}
		break;
	case 5:
		{
			re=ICC_Reader_PowerOff2(ReaderHandle,0x14);//上电 冷 返回数据长度
			if(re<0)
			{
				return re;
			}
		}
		break;
	}
	return 0;
}

RHCARDREADERAPI int ICC_Reader_Application(int ReaderHandle, int ICC_Slot_No, int Length_of_Command_APDU, char *Command_APDU, char *Response_APDU, int *RespLen)
{
	int re=0;
	FXN8 ICC_Reader_Application2=(FXN8)::GetProcAddress(hModuleD,"ICC_Reader_Application");
	FXN7 PICC_Reader_Application=(FXN7)::GetProcAddress(hModuleD,"PICC_Reader_Application");
	switch(ICC_Slot_No)
	{
	case 0:
		{
			re=PICC_Reader_Application(ReaderHandle,Length_of_Command_APDU,
				(unsigned char *)Command_APDU,(unsigned char *)Response_APDU);
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
			return re;
		}
		break;
	case 1:
		{
			re=ICC_Reader_Application2(ReaderHandle,0x01,Length_of_Command_APDU,
				(unsigned char *)Command_APDU,(unsigned char *)Response_APDU);
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
			return re;
		}
		break;
	case 2:
		{
			re=ICC_Reader_Application2(ReaderHandle,0x11,Length_of_Command_APDU,
				(unsigned char *)Command_APDU,(unsigned char *)Response_APDU);
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
			return re;
		}
		break;
	case 3:
		{
			re=ICC_Reader_Application2(ReaderHandle,0x12,Length_of_Command_APDU,
				(unsigned char *)Command_APDU,(unsigned char *)Response_APDU);
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
			return re;
		}
		break;
	case 4:
		{
			re=ICC_Reader_Application2(ReaderHandle,0x13,Length_of_Command_APDU,
				(unsigned char *)Command_APDU,(unsigned char *)Response_APDU);
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
			return re;
		}
		break;
	case 5:
		{
			re=ICC_Reader_Application2(ReaderHandle,0x14,Length_of_Command_APDU,
				(unsigned char *)Command_APDU,(unsigned char *)Response_APDU);
			if(re<0)
			{
				return re;
			}
			*RespLen=re;
			return re;
		}
		break;
	}
	return 0;
}

RHCARDREADERAPI int ICC_Reader_Version(char *info)
{
	FXN Reader_Open=(FXN)::GetProcAddress(hModuleD,"ICC_Reader_Open");
	FXN2 Reader_Close=(FXN2)::GetProcAddress(hModuleD,"ICC_Reader_Close");
	FXN9 ICC_Reader_GetDeviceVersion=(FXN9)::GetProcAddress(hModuleD,"ICC_Reader_GetDeviceVersion");
	FXNA ICC_Reader_GetDeviceCSN=(FXNA)::GetProcAddress(hModuleD,"ICC_Reader_GetDeviceCSN");
	long ReaderHandle=Reader_Open("USB1");
	if(ReaderHandle<0)
		return ReaderHandle;
	char VSoftware[100]={0};
	char VHardware[100]={0};
	char VBoot[100]={0};
	char VDate[100]={0};
	char dev_Ser[100]={0};
	int re=ICC_Reader_GetDeviceVersion(ReaderHandle,VSoftware,VHardware,VBoot,VDate);
	if(re)
		return re;
	re=ICC_Reader_GetDeviceCSN(ReaderHandle,dev_Ser);
	if(re)
		return re;
	sprintf(info,"%s|%s|%s|%s|%s",dev_Ser,VSoftware,VHardware,VBoot,VDate);
	re=Reader_Close(ReaderHandle);
	return 0;
}