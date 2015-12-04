// SSSE32.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SSSE32.h"
#include <Winuser.h> 
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string>
using namespace std;
#include <mbstring.h>
#include "WAPP.H"
extern "C" {
#include <setupapi.h>
#include "hidsdi.h"
}



#define VID    0x072F
#define PID    0x90D5

//#define VID    0x0471
//#define PID    0xa112

unsigned char _FLAG=0;
//unsigned char cardtype=0;

typedef struct _PATH {
    char   DevicePath[255];
}PATH, *PPATH;


/******************extern def**********/
#define CardCommandT1 0x02
#define CardCommandT2 0x06
#define CardCommandT3 0x08




#define hd_Beep        0x00
#define CPURESET       0x7e
#define CPUSETCPU      0x83
#define CPUOVERFLOWTITLE1     0x82
#define CPUAPDU        0x7D
#define USBCPUDOWN     0xE8
#define halt  0x45

#define ID_REQUEST	  0xB0//寻卡
#define ID_SELECT	  0xB1//选卡
#define ID_READ		  0xB3//读卡




/****************************/

extern bool SubKey[2][16][48];// 16圈子密钥
extern char Tmp[256], deskey[16];
unsigned char G_len =0;
int cntInit=0;

unsigned char flagAUTO=0;
unsigned char longtimedata[3]={0};
unsigned char flagLong=0;
long autoRead=0;
long hdevs[100];

bool _bpps=true;

//extern int Indev;
extern unsigned char devType[4];
extern  COMSTAT ComStat;
DCB dcb;
unsigned char  _cardtype=0;//保存当前的卡型

struct COM
{
	long ReaderHandle;
	int stat;
};

COM m_sCOM[10];


#define DEV_NUM  10
int                                DevCount;
PSP_DEVICE_INTERFACE_DETAIL_DATA   DevDetailData[DEV_NUM];//保存寻找到的设备

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

long WINAPI ICC_SetCpuETU(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char cpupro,unsigned char cpuetu)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		unsigned char temp[255]={0};
		unsigned char OutReport[255];
//		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x04;
		temp[5]=0x00;
		temp[6]=0x7a;
		
		if(ICC_Slot_No==0x01)
			temp[7]=0x0C;
		else if(ICC_Slot_No==0x11)
			temp[7]=0x0D;
		else if(ICC_Slot_No==0x12)
			temp[7]=0x0E;
		else if(ICC_Slot_No==0x13)
			temp[7]=0x0F;
		else if(ICC_Slot_No==0x14)
			temp[7]=0x10;
		//data
//		temp[7]=cputype;//time parameter 

		temp[8]=cpupro;
		temp[9]=cpuetu;
		//get and set xorbuffer
		unsigned xorbuffer=0x00;
		for(int i=2;i<10;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature((HANDLE)ReaderHandle,temp,0x21);
		return IFD_OK;//sucess
}

long WINAPI ICC_Reader_Open(char* dev_Name)
{
	if(strcmp(dev_Name,"AUTO")==0)
	{
		flagAUTO=1;
	}
	else
	{
		if(dev_Name[0]!='U'||dev_Name[1]!='S'||dev_Name[2]!='B')
			return IFD_ParameterError;
	}

    for (int i = 0; i < DEV_NUM; i++)
	{
		if (DevDetailData[i]) free(DevDetailData[i]);
	}
	DevCount = 0;

	HANDLE                             DevHandle;
	GUID                             HidGuid;
	HDEVINFO                         DevInfo;
	SP_DEVICE_INTERFACE_DATA         DevData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DevDetail;
	PHIDP_PREPARSED_DATA	           PreparsedData;
	HIDP_CAPS	                       Capabilities;
	HIDD_ATTRIBUTES                    Attributes;
	ULONG                            Length;
	int                              Index;
	BOOL                             ok;

  /* Get GUID for all System HIDs */
	 HidD_GetHidGuid(&HidGuid);
	 DevInfo = SetupDiGetClassDevs(&HidGuid, 
                                NULL, 
                                NULL, 
                                (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE)
                                );

  DevData.cbSize = sizeof(DevData);

  DevDetail = NULL;

  Index = -1;

  /* Scan all Devices */
  do {

    Index++;

    /* Device Interface Element of a Device Information set */
    ok = SetupDiEnumDeviceInterfaces(DevInfo, 
                                     0, 
                                     &HidGuid, 
                                     Index, 
                                     &DevData
                                     );
    if (!ok) break;

    /* Get Device Interface Details - Get Length */
    ok = SetupDiGetDeviceInterfaceDetail(DevInfo, 
                                         &DevData, 
                                         NULL, 
                                         0, 
                                         &Length, 
                                         NULL
                                         );

    /* Allocate memory for Device Detailed Data */
    if (DevDetail) free(DevDetail);
    DevDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(Length);
      
    /* Set cbSize in the DevDetail structure */
    DevDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    /* Get Device Interface Details */
    ok = SetupDiGetDeviceInterfaceDetail(DevInfo, 
                                         &DevData, 
                                         DevDetail, 
                                         Length, 
                                         NULL, 
                                         NULL
                                         );
    if (!ok) continue;

    /* Create File for Device Read/Write */
    DevHandle = CreateFile(DevDetail->DevicePath, 
                           GENERIC_READ | GENERIC_WRITE, 
                           FILE_SHARE_READ | FILE_SHARE_WRITE, 
                           (LPSECURITY_ATTRIBUTES)NULL,
                           OPEN_EXISTING, 
                           0, 
                           NULL
                           );

    if (DevHandle == INVALID_HANDLE_VALUE) 
		continue;
	else
	{
		Attributes.Size = sizeof(Attributes);
        BOOLEAN bSuccess = HidD_GetAttributes(DevHandle, &Attributes);
		if (bSuccess)
		{
			if ((Attributes.VendorID == VID) &&
				(Attributes.ProductID == PID))
			{
				DevDetailData[DevCount++] = DevDetail;
				DevDetail = NULL;
			//	break;
			}
//	13488794130	
		}
		else
		{
			continue;	
		}
	}
    CloseHandle(DevHandle);

  }while (DevCount < DEV_NUM);

	if (DevDetail) free(DevDetail);

	SetupDiDestroyDeviceInfoList (DevInfo);

	if(flagAUTO==0)
	{
		  char name[2]={0};
		  name[0] = dev_Name[3];
		  int ncom = atoi(name);
		  if(ncom>(DevCount)||(ncom<-1)||(ncom>9))
			  return IFD_ParameterError;
		  else
		  {
			  if (DevDetailData[ncom-1] == NULL) return IFD_ConnectError;

			  /* Create File for Device Read/Write */
			  DevHandle = CreateFile(DevDetailData[ncom-1]->DevicePath, 
									 GENERIC_READ | GENERIC_WRITE, 
									 FILE_SHARE_READ | FILE_SHARE_WRITE, 
									 (LPSECURITY_ATTRIBUTES)NULL,
									 OPEN_EXISTING, 
									 0, 
									 NULL
									 );

			  if (DevHandle == INVALID_HANDLE_VALUE) return IFD_ConnectError;
			  else
			  {

				  m_sCOM[ncom].ReaderHandle = (long)DevHandle;
				  m_sCOM[ncom].stat = 1;
				  return (long)DevHandle;
			  }

		  }
	}
	else
	  {
		  if (DevDetailData[0] == NULL) return IFD_ConnectError;

		  /* Create File for Device Read/Write */
		  DevHandle = CreateFile(DevDetailData[0]->DevicePath, 
								 GENERIC_READ | GENERIC_WRITE, 
								 FILE_SHARE_READ | FILE_SHARE_WRITE, 
								 (LPSECURITY_ATTRIBUTES)NULL,
								 OPEN_EXISTING, 
								 0, 
								 NULL
								 );

		  if (DevHandle == INVALID_HANDLE_VALUE) return IFD_ConnectError;
		  else
		  {
			  autoRead = (long)DevHandle;
			  return (long)DevHandle;
		  }

	  }



}

long WINAPI ICC_Reader_Close(long ReaderHandle)
{
	int flag;
	if(ReaderHandle<=0)
		return IFD_UnConnected;
	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
	

	flag=CloseHandle((HANDLE)ReaderHandle);
	
	if(!flag)
	{
		return flag;
	}

	
	if(flagAUTO==1)
	{
		flagAUTO=0;
		autoRead=0;
		return IFD_OK;
	}
		

	for( int x=1;x<10;x++)
	{
		if(m_sCOM[x].ReaderHandle == ReaderHandle)
		{
			m_sCOM[x].stat = 0;
		}	
	}

	return IFD_OK;
}

long WINAPI ICC_Reader_GetDeviceCSN(long ReaderHandle,char* dev_Ser)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}


	HANDLE hDev=(HANDLE)ReaderHandle;
	unsigned char temp[255]={0};
	unsigned char OutReport[255]={0};

	OutReport[0]=0;
	temp[1]=CardCommandT1;
	temp[2]=CardCommandT3;
	temp[3]=0x00;
	temp[4]=0x01;
	temp[5]=0x00;
	temp[6]=0x11;
	temp[7]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6];

	//set and get feature data
	HidD_SetFeature(hDev,temp,0x21);
	HidD_GetFeature(hDev,OutReport,0x21);
	if(OutReport[3])
		return IFD_ICC_NoResponse;//call failed卡片类型不对
	if(OutReport[1]!=0x02||OutReport[2]!=0x02)
		return IFD_ICC_NoResponse;

	long returnlen=(long)OutReport[4];
//	*rlen=(unsigned char)(returnlen);

	for(int k=0;k<returnlen;k++)
	{
		*(dev_Ser++)=OutReport[6+k];
	}

	return returnlen;
//	return IFD_OK;
}

long WINAPI ICC_Reader_pre_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response)//冷复位
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

	HANDLE hDev=(HANDLE)ReaderHandle;
	unsigned char temp[255]={0};
	unsigned char OutReport[255]={0};

	OutReport[0]=0;
	temp[1]=CardCommandT1;
	temp[2]=CardCommandT3;
	temp[3]=0x00;
	temp[4]=0x03;
	temp[5]=0x00;
	temp[6]=0x74;
//		temp[7]= cardtype;
    if(ICC_Slot_No==0x01)
		temp[7]=0x0C;
	else if(ICC_Slot_No==0x11)
		temp[7]=0x0D;
	else if(ICC_Slot_No==0x12)
		temp[7]=0x0E;
	else if(ICC_Slot_No==0x13)
		temp[7]=0x0F;
	temp[8]=0x40;
	temp[9]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6]^temp[7]^temp[8];
	//set and get feature data
	HidD_SetFeature(hDev,temp,0x21);
	HidD_GetFeature(hDev,OutReport,0x21);

	if(OutReport[3])
		return IFD_ICC_NoResponse;//call failed卡片类型不对

	long returnlen=(long)OutReport[4];

	for(int k=0;k<returnlen;k++)
	{
		*(Response++)=OutReport[5+k];
	}

	if(_bpps)
	{
		unsigned char his=(OutReport[6]&0x0f);
		if(his<=0)
			return returnlen;

		unsigned char ta1,td1;
		unsigned char m,n; 
		int t=0;
		n = OutReport[6];//t0
		m = n&0x10;   //判断ta1 tb1 tc1 td1
		if(m==0x10)//ta1存在，进行特定或协商判断
		{	
			unsigned char PPScom1[4] = {0xff,0x10,0x12,0xfd};
			//unsigned char PPScom2[4] = {0xff,0x10,0x13,0xfc};
			//unsigned char PPScom3[4] = {0xff,0x10,0x14,0xfb};
			//unsigned char PPScom4[4] = {0xff,0x10,0x18,0xf7};
			unsigned char res[20]={0};
			ta1=OutReport[7];
			int s_ta1 = ta1>>4;
			//if(s_ta1!=0x01)
			//	return returnlen;
			if(ta1==0x95)
				ta1=0x94;
			PPScom1[2]=ta1;
			PPScom1[3]=PPScom1[0]^PPScom1[1]^PPScom1[2];
			m=n&0x80;
			if(m==0x80)//Td1存在  进一步判断ta2
			{
				int f=0;
				if(n&0x40==0x40)//tc1存在
					f++;
				if(n&0x20==0x20)//tb1存在
					f++;
				td1=OutReport[8+f];	
					f++;
				if((td1&0x10)==0x10)//ta2存在 特定模式
				{
					unsigned char ta2 = OutReport[8+f];
					if((ta2&0x10)!=0x10)//判断b5是否为0，是的话，则使用新的ETU
					{
						if((ta1&0xf0) == 0x10 ||(ta1&0xf0) == 0x90)//判断F是否为1
						{
							ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);
							/*
							switch(ta1&0x0f)
							{
								case 1:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
								case 2:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
								case 3:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
								case 8:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
							default:break;
							}*/
						}
					}
	//				ICC_SetCpuETU
				}
				else //ta2 不存在  协商模式
				{
					ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom1,res);
					/*switch(ta1&0x0f)
					{
						case 0x02:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom1,res); break;
						case 0x03:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom1,res);break;
						case 0x04:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom1,res);break;
						case 0x08:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom1,res);break;
					}*/
					
					if(ta1&0x0f==0x02)
					{
						if(res[0]!=PPScom1[0])
						{
							if(res[1]&0x0f!=PPScom1[1]&0x0f)
								return IFD_ICC_TypeError;
						}
					}
					if(ta1&0x0f==0x03)
					{
						if(res[0]!=PPScom1[0])
						{
							if(res[1]&0x0f!=PPScom1[1]&0x0f)
								return IFD_ICC_TypeError;
						}
					}
					if(ta1&0x0f==0x04)
					{
						if(res[0]!=PPScom1[0])
						{
							if(res[1]&0x0f!=PPScom1[1]&0x0f)
								return IFD_ICC_TypeError;
						}
					}
					if(ta1&0x0f==0x08)
					{
						if(res[0]!=PPScom1[0])
						{
							if(res[1]&0x0f!=PPScom1[1]&0x0f)
								return IFD_ICC_TypeError;
						}
					}
					ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);
					/*
					switch(ta1&0x0f)
					{
						case 1:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
						case 2:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
						case 3:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
						case 8:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
					default:break;
					}*/

				}

			}
			else//协商模式 td1不存在
			{
				ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom1,res);
				/*
				switch(ta1&0x0f)
				{
					case 0x02:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom1,res);break;
					case 0x03:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom2,res);break;
					case 0x04:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom3,res);break;
					case 0x08:ICC_Reader_Application(ReaderHandle,ICC_Slot_No,4,PPScom4,res);break;
				}
			*/
				if((ta1&0x0f)==0x02)
				{
					if(res[0]!=PPScom1[0])
					{
						if(res[1]&0x0f!=PPScom1[1]&0x0f)
							return IFD_ICC_TypeError;
					}
				}
				if((ta1&0x0f)==0x03)
				{
					if(res[0]!=PPScom1[0])
					{
						if(res[1]&0x0f!=PPScom1[1]&0x0f)
							return IFD_ICC_TypeError;
					}
				}
				if((ta1&0x0f)==0x04)
				{
					if(res[0]!=PPScom1[0])
					{
						if(res[1]&0x0f!=PPScom1[1]&0x0f)
							return IFD_ICC_TypeError;
					}
				}
				if((ta1&0x0f)==0x08)
				{
					if(res[0]!=PPScom1[0])
					{
						if(res[1]&0x0f!=PPScom1[1]&0x0f)
							return IFD_ICC_TypeError;
					}
				}
				ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);
				/*
				switch(ta1&0x0f)
				{
					case 1:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
					case 2:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
					case 3:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
					case 8:ICC_SetCpuETU(ReaderHandle,ICC_Slot_No,0,ta1);break;
				default:break;
				}*/
			}
		}
		else//缺省模式
		{
			
		}
	}
	return returnlen;	
}
long WINAPI ICC_Reader_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}


		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[255]={0};
		unsigned char OutReport[255]={0};

		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;
		temp[5]=0x00;
		temp[6]=0x75;
//		temp[7]= cardtype;
        if(ICC_Slot_No==0x01)
			temp[7]=0x0C;
		else if(ICC_Slot_No==0x11)
			temp[7]=0x0D;
		else if(ICC_Slot_No==0x12)
			temp[7]=0x0E;
		else if(ICC_Slot_No==0x13)
			temp[7]=0x0F;
		else if(ICC_Slot_No==0x14)
			temp[7]=0x10;
		temp[8]=0x40;
		temp[9]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6]^temp[7]^temp[8];

		//set and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		HidD_GetFeature(hDev,OutReport,0x21);
		if(OutReport[3])
			return IFD_ICC_NoResponse;//call failed卡片类型不对
		if(OutReport[1]!=0x02||OutReport[2]!=0x02)
			return IFD_ICC_NoResponse;
		//c6
		long returnlen=(long)OutReport[4];
//		*rlen=(unsigned char)(returnlen);


		for(int k=0;k<returnlen;k++)
		{
			*(Response++)=OutReport[5+k];
		}

		return returnlen;
}

long WINAPI ICC_Reader_PowerOff(long ReaderHandle,unsigned char ICC_Slot_No)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;

		temp[4]=0x01;

		temp[5]=0x00;
		temp[6]=0x73;
//		temp[7]=0xb8;


		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature((HANDLE)ReaderHandle,temp,0x21);
		HidD_GetFeature((HANDLE)ReaderHandle,OutReport,0x21);
		if(OutReport[3])
			return(OutReport[3]);//call failed 

		return IFD_OK;
}

long WINAPI ICC_Reader_GetStatus(long ReaderHandle,unsigned char ICC_Slot_No)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[255]={0};
		unsigned char OutReport[255]={0};

		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;
		temp[5]=0x00;
		temp[6]=0x77;
//		temp[9]=ICC_Slot_No;

		//set and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		HidD_GetFeature(hDev,OutReport,0x21);
		if(OutReport[3]==1)
			return IFD_ICC_NoPower;//call failed
		else if(OutReport[3]==2)
			return IFD_ICC_NoExist;
		else return IFD_OK;

}
//(发给动态库的)命令参数错  01
//卡片无应答  c2
//(动态库)不支持该命令 82
long WINAPI ICC_Reader_Application(long ReaderHandle,unsigned char ICC_Slot_No,
							 long Lenth_of_Command_APDU,unsigned char* Command_APDU,
							 unsigned char* Response_APDU)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[300];
		unsigned char OutReport[300];
		unsigned char *psbuf;
		long len;
		
		memset(temp,0,300);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;//0x7d
		temp[4]=(Lenth_of_Command_APDU+3)%0x100;  //低字节
		
		//data
		temp[5]=(Lenth_of_Command_APDU+3)/0x100; //高字节
		temp[6]=0x72;
		if(ICC_Slot_No==0x01)
			temp[7]=0x0C;
		else if(ICC_Slot_No==0x11)
			temp[7]=0x0D;
		else if(ICC_Slot_No==0x12)
			temp[7]=0x0E;
		else if(ICC_Slot_No==0x13)
			temp[7]=0x0F;
		else if(ICC_Slot_No==0x14)
			temp[7]=0x10;
		temp[8]=0x00;

		psbuf=Command_APDU;
		
		for(int j=9;j<9+Lenth_of_Command_APDU;j++)
		{
			temp[j]=Command_APDU[j-9];
		}
		
		//get and set xorbuffer
		unsigned xorbuffer=0x00;
		for(int i=2;i<j;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[j]=xorbuffer;

		if(Lenth_of_Command_APDU<24)
		{
				//send and get feature data
				HidD_SetFeature(hDev,temp,0x21);					
				HidD_GetFeature(hDev,OutReport,0x21);
	
				if(OutReport[3])
				{
					return -20;
				}
				//	return(OutReport[3]);//call failed 
				
				//get return data
				long returnlen=(int)OutReport[4];
				len=(long)(returnlen);
				
				if(CardCommandT1==OutReport[1])
				{
					
					for(int l=0;l<returnlen;l++)
					{
						*(Response_APDU++)=OutReport[6+l];
					}
				}
				else if(CPUOVERFLOWTITLE1==OutReport[1])
				{
					int getTime=0;
					int iData=0;//the current count of out feature data
					long total = (int)OutReport[5]<<8;
					returnlen = returnlen+ total;
					len=(long)(returnlen);
					//the first time get feature
					for(int l=0;l<27;l++)
					{
						*(Response_APDU++)=OutReport[6+l];
					}

					returnlen-=27;//返回字节数先减去27个
					if(returnlen==0)
						getTime=0;
					else
						getTime=(returnlen-1)/31+1;//如果为31的倍数时，应该是要减一

					//loop to get Feature data
					while(getTime>=1)
					{
						if(getTime!=1)
						{
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<31;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
								++iData;
							}
							
							getTime--;
						}
						else//the last time to get feature data
						{
							int ltimelen=returnlen-iData;
							
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<ltimelen;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
							}
							getTime--;
						}
					}//while(getTime>=1)
				}//else if(CPUOVERFLOWTITLE1==OutReport[1])
		}
		else
		{
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(Lenth_of_Command_APDU+3)%0x100;
				
				//data
				singletemp[5]=temp[3]=(Lenth_of_Command_APDU+3)/0x100;
				singletemp[6]=temp[4]=0x72;

				if(ICC_Slot_No==0x01)
					singletemp[7]=temp[5]=0x0C;
				else if(ICC_Slot_No==0x11)
					singletemp[7]=temp[5]=0x0D;
				else if(ICC_Slot_No==0x12)
					singletemp[7]=temp[5]=0x0E;
				else if(ICC_Slot_No==0x13)
					singletemp[7]=temp[5]=0x0F;
			//	singletemp[7]=temp[5]=0x0c;
				singletemp[8]=temp[6]=0x00;
				
				
				
				for(int k=0;k<24;k++)
				{
					singletemp[9+k]=temp[++itemp]=*(Command_APDU++);
				}
				
				Lenth_of_Command_APDU-=24;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);
				
				if(Lenth_of_Command_APDU<=0)
					sentTime=1;
				else
					sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一
				
				//loop to sent feature
				while(sentTime)
				{	
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;

						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						Lenth_of_Command_APDU-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						lasttemp[1]=CardCommandT1;
						int remainlen=strlen((char *)Command_APDU);
			
						for(int k=0;k<Lenth_of_Command_APDU+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);

						if(OutReport[3])
						{
							return -20;
						}
						
						int returnlen=(int)OutReport[4];
						len=(long)(returnlen);
						
						//get the return buffer data
						for(int l=0;l<returnlen;l++)
						{
							*(Response_APDU++)=OutReport[6+l];
						}
					}
				}//while(sentTime)
		}

	return len;
}

long WINAPI ICC_Reader_Libinfo(char* info)
{
	strcpy(info,"HD-OS           HD100-C1-HN-P302");
	return IFD_OK;
}

long WINAPI ICC_PosBeep(long ReaderHandle, unsigned char time)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
/**/
		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[255]={0};
		unsigned char OutReport[255]={0};
		
		temp[0]=0x00;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=hd_Beep;
		temp[4]=0x02;
		temp[5]=0x00;
		temp[6]=0xb2;
		temp[7]=time;

		temp[8]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6]^temp[7];//0x3c
		//temp[8]=0x00;
		
	   BOOL flag=FALSE;
		flag=HidD_SetFeature(hDev,temp,0x21);
		flag=HidD_GetFeature(hDev,OutReport,0x21);
	//	if(OutReport[3])
		return IFD_OK;
}

long WINAPI ICC_SetCpupara(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char cpupro,unsigned char cpuetu)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		unsigned char temp[255]={0};
		unsigned char OutReport[255];
//		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x04;
		temp[5]=0x00;
		temp[6]=0x76;
		
		if(ICC_Slot_No==0x01)
			temp[7]=0x0C;
		else if(ICC_Slot_No==0x11)
			temp[7]=0x0D;
		else if(ICC_Slot_No==0x12)
			temp[7]=0x0E;
		else if(ICC_Slot_No==0x13)
			temp[7]=0x0F;
		else if(ICC_Slot_No==0x14)
			temp[7]=0x10;
		//data
//		temp[7]=cputype;//time parameter 

		temp[8]=cpupro;
		temp[9]=cpuetu;
		//get and set xorbuffer
		unsigned xorbuffer=0x00;
		for(int i=2;i<10;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature((HANDLE)ReaderHandle,temp,0x21);
		return IFD_OK;//sucess
}
/*
long WINAPI ICC_GetFirmware(long ReaderHandle)
{     //02 08 00 01 - 00 b0 0a

	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;
		temp[5]=0x00;
		temp[6]=0xb0;
		temp[7]=0x0a;


		
		
		//send and get feature data
		HidD_SetFeature((HANDLE)ReaderHandle,temp,0x21);
		HidD_GetFeature((HANDLE)ReaderHandle,OutReport,0x21);
		if(OutReport[3])
			return(OutReport[3]);//call failed 

		cardtype=OutReport[5];

		return IFD_OK;//sucess
}
*/

long WINAPI Rcard1(long ReaderHandle,unsigned char ctime,int track,unsigned char *rlen,char *getdata)
{

	if(ReaderHandle<=0)
		return -5;

	if(track<1||track>3)
			return -4;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return -5;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return -5;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}


		HANDLE hDev = (HANDLE)ReaderHandle;
	//	int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;
		temp[5]=0x00;
		temp[6]=0x30;
		temp[7]=track;
		temp[8]=ctime;
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<9;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);


		if(OutReport[3])
		{
			 if(OutReport[3] == 0x16)
				return -4;
			return -1;
		}
		
		long returnlen=(int)OutReport[4];
		*rlen=(long)(returnlen);
		
		if(CardCommandT1==OutReport[1])
		{
			
			for(int l=0;l<returnlen;l++)
			{
				*(getdata++)=OutReport[6+l];
			}
		}
		else if(CPUOVERFLOWTITLE1==OutReport[1])
		{
			int getTime=0;
			int iData=0;//the current count of out feature data
			long total = (int)OutReport[5]<<8;
			returnlen = returnlen+ total;
			*rlen=(long)(returnlen);
			//the first time get feature
			for(int l=0;l<27;l++)
			{
				*(getdata++)=OutReport[6+l];
			}

			returnlen-=27;//返回字节数先减去27个

			getTime=returnlen/31+1;

			//loop to get Feature data
			while(getTime>=1)
			{
				if(getTime!=1)
				{
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<31;i++)
					{
						*(getdata++)=OutReport[2+i];
						++iData;
					}
					
					getTime--;
				}
				else//the last time to get feature data
				{
					int ltimelen=returnlen-iData;
					
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<ltimelen;i++)
					{
						*(getdata++)=OutReport[2+i];
					}
					getTime--;
				}
			}//while(getTime>=1)
		}//else if(CPUOVERFLOWTITLE1==OutReport[1])
//		

		return IFD_OK;//sucess
}

//02 08 00 01 00 60 01（track1）
long WINAPI Rcard(long ReaderHandle,unsigned char ctime,int track,unsigned char *rlen,char *getdata)
{
	if(ReaderHandle<=0)
		return -5;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return -5;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return -5;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
	int re = Rcard1(ReaderHandle,ctime,track,rlen,getdata);
//	int re = ICC_PassGetID(ReaderHandle, rlen,,start,stop,cardID, cpass);
	if (re != 0) 
	{	int i=0;
		i=ctime*1000;
		while(i>0)
		{	Sleep(200);
			re = ICC_PassCheck(ReaderHandle, rlen, (unsigned char*)getdata);
			if(re==0)
			{
			//	ICC_PassCancel(ReaderHandle);
			//	strcpy(getdata,getdata+1);
			//	*rlen=*rlen-1;
			
				
				return 0;
			}
			if(re==-1)
			{
			//	ICC_PassCancel(ReaderHandle);
				return -1;
			}

			if(re==-2)
			{
				i=i-200;
				continue;				
			}
		}
		ICC_GetTimeOut(ReaderHandle,2);
		return re;
	}
	return IFD_OK;//sucess
}
/*
long WINAPI WCard(long ReaderHandle,char *getdata,int track)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x11;//低位
		temp[5]=0x00;//高位
		temp[6]=0x61;
		temp[7]=track;
		for(int i=0;i<16;i++)
		{
			temp[8+i]=getdata[i];
		}

	
		unsigned xorbuffer=0x00;
		for( i=2;i<24;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[24]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);


		if(OutReport[3])
		{
			return -5;
		}
	return IFD_OK;
}*/
/*
long WINAPI ICC_DispLcd(long ReaderHandle,unsigned char type)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x62;
		temp[7]=type;
	
		
		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);


		if(OutReport[3])
		{
			return -5;
		}
	return IFD_OK;
}
*/
long WINAPI ICC_DispInfo(long ReaderHandle,unsigned char row,unsigned char list,char *data)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		len=strlen(data);
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=len+3;//低位
		temp[5]=0x00;//高位
		temp[6]=0x69;
		temp[7]=row;
		temp[8]=list;

		for(int i=0;i<len;i++)
		{
			temp[9+i]=data[i]&0xff;
		}

		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(i=2;i<(9+len);i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9+len]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);


		if(OutReport[3])
		{
			return OutReport[3];
		}
	return IFD_OK;
} 

long WINAPI ICC_CtlLight(long ReaderHandle)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		//int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6a;

	
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);


		if(OutReport[3])
		{
			return OutReport[3];
		}
	return IFD_OK;
}

long WINAPI ICC_ChangeLight(long ReaderHandle,unsigned char mode)
{
		if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		if(mode==0)
			temp[6]=0x6e;
		else 
			temp[6]=0x6d;

	
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		
	return IFD_OK;
}
/*
long WINAPI ICC_Clear(long ReaderHandle, unsigned char cLine)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x65;
		temp[7]=cLine;
	
	
		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);


		if(OutReport[3])
		{
			return OutReport[3];
		}
	return IFD_OK;
}
*/
long WINAPI ICC_GetInputPass(long ReaderHandle, unsigned char ctime, unsigned char *rlen,unsigned char start,unsigned char stop, unsigned char * cpass)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

	int re = ICC_PassGet(ReaderHandle, rlen,ctime,start,stop, cpass);

	if (re != 0) 
	{	
//		ICC_PassGet(ReaderHandle, rlen,ctime,start,stop, cpass);
		int i=0;
		i=ctime*1000;
		while(i>0)
		{	
			Sleep(200);
	//		ICC_PassGet(ReaderHandle, rlen,ctime,start,stop, cpass);

			re = ICC_PassCheck(ReaderHandle, rlen, cpass);
			if(re==0)
			{
			//	ICC_PassCancel(ReaderHandle);
				return 0;
			}
			if(re==-1)
			{
			//	ICC_PassCancel(ReaderHandle);  109 793 475 709
				return -1;
			}
			if(re==-2)
			{
				i=i-200;
				continue;				
			}
		}
		ICC_GetTimeOut(ReaderHandle,1);
		return re;
	}

	return IFD_OK;
}

long WINAPI ICC_GetInputPassID(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start,unsigned char stop,unsigned char * cardID,unsigned char * cpass)//获取密码，带超时,带ID
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

	int re = ICC_PassGetID(ReaderHandle, rlen,ctime,start,stop,cardID, cpass);
	if (re != 0) 
	{	int i=0;
		i=ctime*1000;
		while(i>0)
		{	Sleep(200);
			re = ICC_PassCheck(ReaderHandle, rlen, cpass);
			if(re==0)
			{
			//	ICC_PassCancel(ReaderHandle);
				return 0;
			}
			if(re==-1)
			{
			//	ICC_PassCancel(ReaderHandle);
				return -1;
			}
			if(re==-2)
			{
			//	ICC_PassCancel(ReaderHandle);
				return -2;
			}
			if(re==-4)
			{
				i=i-200;
				continue;				
			}
		}
	}

	return IFD_OK;	
}
/*
long WINAPI ICC_PassIn(long ReaderHandle,unsigned char ctime)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x67;
		temp[7]=ctime;
	
	
		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);


		if(OutReport[3])
		{
			return OutReport[3];
		}
	return IFD_OK;
}*/

long WINAPI ICC_GetTimeOut(long ReaderHandle,unsigned char flag)//获取密码、读磁条超时
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0xb3;
		temp[7] = flag;
		
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
		
			return -2;

		}

	return IFD_OK;
}

long WINAPI ICC_PassGet(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char start,unsigned char stop,unsigned char * cpass)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6c;
		temp[7] = time;
		temp[8]=start;
		temp[9]=stop;
		
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<10;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			*rlen=0;
			cpass=NULL;
			return -2;

		}
		*rlen=OutReport[4]+OutReport[5]*16;
		for(i=6;i<(6+OutReport[4]);i++)
		{
			cpass[i-6]=OutReport[i];
		}

	return IFD_OK;
}

long WINAPI ICC_PassGetID(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char start,unsigned char stop,unsigned char * cardID,unsigned char * cpass)//获取密码，带卡号
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x0f;//低位
		temp[5]=0x00;//高位
		temp[6]=0x68; //1B  46  x  y  0D  0A
		temp[7]=time;
		temp[8]=start;
		temp[9]=stop;
		for(int i=0;i<12;i++)
			temp[10+i]=cardID[i];
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(i=2;i<22;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[22]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			*rlen=0;
			cpass=NULL;
			if(OutReport[3]==0xa1)
				return -1;
			else if(OutReport[3]==0xa2)
				return -2;
			else if(OutReport[3]==0xa3)
				return -3;
			else if(OutReport[3]==0xa4)
				return -4;
			else
				return -1;
		}
		*rlen=OutReport[4];
		for(i=5;i<(5+OutReport[4]);i++)
		{
			cpass[i-5]=OutReport[i];
		}

	return IFD_OK;	
}
/*
long WINAPI ICC_PassCancel(long ReaderHandle)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x69;
	
		
		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];
		}

	return IFD_OK;
}*/

long WINAPI ICC_PassCheck(long ReaderHandle,unsigned char *rlen,unsigned char * cpass)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
	//	int len;
//		unsigned char temp[255];
		unsigned char OutReport[255];
//		memset(temp,0,255);
		OutReport[0]=0;
/*		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6a; //1B  46  x  y  0D  0A

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
*/		
		BOOLEAN i = HidD_GetFeature(hDev,OutReport,0x21);
		if(!i)
			return -1;
		if(OutReport[3]||OutReport[3]==0xcc)
		{
			*rlen=0;
			cpass=NULL;
			return -2;
		}
		if(OutReport[1]!=0x02&&OutReport[1]!=0x82)
			return -2;
//		if(OutReport[2]!=0x02)
//			return -2;
		int len;
		*rlen=OutReport[4]+OutReport[5]*16;
			len = *rlen;	
				if(CardCommandT1==OutReport[1])
				{
					
					for(int l=0;l<*rlen;l++)
					{
						*(cpass++)=OutReport[6+l];
					}
				}
				else if(CPUOVERFLOWTITLE1==OutReport[1])
				{
					int getTime=0;
					int iData=0;//the current count of out feature data
					//long total = (int)OutReport[5]<<8;
					//returnlen = returnlen+ total;
					//len=(long)(returnlen);
					//the first time get feature
					for(int l=0;l<28;l++)
					{
						*(cpass++)=OutReport[6+l];
					}

					len-=27;//返回字节数先减去27个

					getTime=(len)/31+1;

					//loop to get Feature data
					while(getTime>=1)
					{
						if(getTime!=1)
						{
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<31;i++)
							{
								*(cpass++)=OutReport[2+i];
								++iData;
							}
							
							getTime--;
						}
						else//the last time to get feature data
						{
							int ltimelen=len-iData;
							
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<ltimelen;i++)
							{
								*(cpass++)=OutReport[2+i];
							}
							getTime--;
						}
					}//while(getTime>=1)
				}//else if(CPUOVERFLOWTITLE1==OutReport[1])
//		
		

	return IFD_OK;
}

long WINAPI ICC_PassSetDES(long ReaderHandle,unsigned char DES) //设置加密是des还是3des
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x66; //1B  46  x  y  0D  0A
		temp[7]=DES;
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];
			
		}

	return IFD_OK;
}

long WINAPI ICC_PassSetDevID(long ReaderHandle,unsigned char *devID)//设置键盘设备ID
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x05;//低位
		temp[5]=0x00;//高位
		temp[6]=0x65; //1B  46  x  y  0D  0A
		for(int i=0;i<4;i++)
			temp[7+i]=devID[i];
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(i=2;i<11;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[11]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];
			
		}

	return IFD_OK;
}

long WINAPI ICC_PassGetDevID(long ReaderHandle,unsigned char *devID)//获取键盘设备ID
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x64; //1B  46  x  y  0D  0A
		
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];	
		}
		for(i=5;i<(5+OutReport[4]);i++)
			devID[i-5]=OutReport[i];

	return IFD_OK;	
}

long WINAPI ICC_PassSetKeyLen(long ReaderHandle,unsigned char len)//设置密码长度
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x63; //1B  46  x  y  0D  0A
		temp[7]=len;
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];	
		}

	return IFD_OK;
}

long WINAPI ICC_PassDes(long ReaderHandle,unsigned char flag,unsigned char *InData,unsigned char *OutData)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02+8;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6b; //1B  46  x  y  0D  0A
		if(flag==1)
			temp[7]=0x31;
		else if(flag==0)
			temp[7]=0x30;
		else
			return -1;

		for(int i=0;i<8;i++)
			temp[8+i]=InData[i];
		
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for( i=2;i<7+8+1;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[16]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
//		Sleep(100);
		HidD_GetFeature(hDev,OutReport,0x21);
		
		unsigned char rlen;
		if(OutReport[3])
		{
			int i=0;
			i=1000;
			while(i>0)
			{	Sleep(100);
				int re = ICC_PassCheck(ReaderHandle, &rlen, OutData);
				if(re==0)
				{
				//	ICC_PassCancel(ReaderHandle);
					return 0;
				}
				if(re==-1)
				{
				//	ICC_PassCancel(ReaderHandle);
					return -1;
				}
				if(re==-2)
				{
				//	ICC_PassCancel(ReaderHandle);
					return -2;
				}
				if(re==-4)
				{
					i=i-100;
					continue;				
				}
			}
			return -20;
		}

		for(i=0;i<OutReport[4];i++)
			OutData[i]=OutReport[5+i];

	return IFD_OK;	
}

long WINAPI ICC_PassSetFD(long ReaderHandle,unsigned char fd)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6d; //1B  46  x  y  0D  0A
		if(fd==1)
			temp[7]=0x31;
		else if(fd==0)
			temp[7]=0x30;
		else
			return -1;		
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];	
		}

	return IFD_OK;		
}

long WINAPI ICC_GetInputPassACOUNT(long ReaderHandle, unsigned char ctime, unsigned char *rlen,unsigned char * cardID,unsigned char * cpass)//获取密码，带超时,带ID
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

	int re = ICC_PassGetACOUNT(ReaderHandle, rlen,ctime,cardID, cpass);
	if (re != 0) 
	{	int i=0;
		i=ctime*1000;
		while(i>0)
		{	Sleep(200);
			re = ICC_PassCheck(ReaderHandle, rlen, cpass);
			if(re==0)
			{
			//	ICC_PassCancel(ReaderHandle);
				return 0;
			}
			if(re==-1)
			{
			//	ICC_PassCancel(ReaderHandle);
				return -1;
			}
			if(re==-2)
			{
			//	ICC_PassCancel(ReaderHandle);
				return -2;
			}
			if(re==-4)
			{
				i=i-200;
				continue;				
			}
		}
	}

	return IFD_OK;	
}

long WINAPI ICC_PassGetACOUNT(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char * cardID,unsigned char * cpass)//获取密码，带卡号
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
//		int len;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x11;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6e; //1B  46  x  y  0D  0A
		temp[7]=time;
		for(int i=0;i<16;i++)
			temp[8+i]=cardID[i];
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(i=2;i<24;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[24]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];
		}
		*rlen=OutReport[4];
		for(i=5;i<(5+OutReport[4]);i++)
		{
			cpass[i-5]=OutReport[i];
		}

	return IFD_OK;	
}

long WINAPI ICC_PassMAC(long ReaderHandle,unsigned char *InData,unsigned char *OutData)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		unsigned char temp[255];
		unsigned char OutReport[255];
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char xtemp[255];

		int len = strlen((char*)InData);
		int pos=0;

		if(len<27)
		{
			memset(temp,0,255);
			OutReport[0]=0;
			temp[1]=CardCommandT1;
			temp[2]=CardCommandT3;
			temp[3]=0x00;
			temp[4]=len+1;//低位
			temp[5]=0x00;//高位
			temp[6]=0x6f; //1B  46  x  y  0D  0A

			for(int i=0;i<len;i++)
				temp[7+i]=InData[i];
			
			unsigned xorbuffer=0x00;
			for(i=2;i<len+7;i++)
			{
				xorbuffer^=temp[i];
			}
			temp[len+7]=xorbuffer;
		
				//sent feature time:1
			HidD_SetFeature(hDev,temp,0x21);
			HidD_GetFeature(hDev,OutReport,0x21);

			unsigned char rlen;
			if(OutReport[3])
			{
				int i=0;
				i=1000;
				while(i>0)
				{	Sleep(100);
					int re = ICC_PassCheck(ReaderHandle, &rlen, OutData);
					if(re==0)
					{
					//	ICC_PassCancel(ReaderHandle);
						return 0;
					}
					if(re==-1)
					{
					//	ICC_PassCancel(ReaderHandle);
						return -1;
					}
					if(re==-2)
					{
					//	ICC_PassCancel(ReaderHandle);
						return -2;
					}
					if(re==-4)
					{
						i=i-100;
						continue;				
					}
				}
				return -20;
			}
			
			for(i=5;i<(5+OutReport[4]);i++)
			{
				OutData[i-5]=OutReport[i];
			}

			return IFD_OK;
		}
			memset(temp,0,255);
			OutReport[0]=0;
			temp[1]=CPUOVERFLOWTITLE1;
			temp[2]=xtemp[0]=CardCommandT3;
			temp[3]=xtemp[1]=0x00;
			temp[4]=xtemp[2]=(len+1)%0x100;//低位
			temp[5]=xtemp[3]=(len+1)/0x100;//高位
			temp[6]=xtemp[4]=0x6f; //1B  46  x  y  0D  0A

			for(int i=0;i<26;i++)
				temp[7+i]=xtemp[5+i]=InData[pos++];	
		
			len-=26;
				//sent feature time:1
			HidD_SetFeature(hDev,temp,0x21);

			int	sentTime=(len/31)+1;
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
				
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=xtemp[5+pos++]=InData[pos++];
						}
						
						len-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						
						
						
						for(int k=0;k<len;k++)
						{
							lasttemp[2+k]=xtemp[5+pos++]=InData[pos++];
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<pos+1;i++)
						{
							xorbuffer^=xtemp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);

						HidD_GetFeature(hDev,OutReport,0x21);


						unsigned char rlen;
						if(OutReport[3])
						{
							int i=0;
							i=2000;
							while(i>0)
							{	Sleep(100);
								int re = ICC_PassCheck(ReaderHandle, &rlen, OutData);
								if(re==0)
								{
								//	ICC_PassCancel(ReaderHandle);
									return 0;
								}
								if(re==-1)
								{
								//	ICC_PassCancel(ReaderHandle);
									return -1;
								}
								if(re==-2)
								{
								//	ICC_PassCancel(ReaderHandle);
									return -2;
								}
								if(re==-4)
								{
									i=i-100;
									continue;				
								}
							}
							return -20;
						}
						
						int returnlen=(int)OutReport[4];
					//	len=(long)(returnlen);
						
						//get the return buffer data
						for(int l=0;l<returnlen;l++)
						{
							*(OutData++)=OutReport[5+l];
						}
						
					}

				}//while(sentTime)

	return IFD_OK;	
	
}

long WINAPI ICC_PassECB(long ReaderHandle,unsigned char *rlen,unsigned char *InData,unsigned char *OutData)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[300];
		unsigned char OutReport[300];
		long len = strlen((char*)InData);
		
		memset(temp,0,300);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;//0x7d
		temp[4]=len%0x100;  //低字节
		temp[5]=len/0x100; //高字节
		temp[6]=0x73;
		
//		psbuf=Command_APDU;
		
		for(int j=7;j<7+len;j++)
		{
			temp[j]=InData[j-7];
		}
		
		//get and set xorbuffer
		unsigned xorbuffer=0x00;
		for(int i=2;i<j;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[j]=xorbuffer;

		if(len<27)
		{
				//send and get feature data
				HidD_SetFeature(hDev,temp,0x21);
				HidD_GetFeature(hDev,OutReport,0x21);


				unsigned char rlen;
				if(OutReport[3])
				{
					int i=0;
					i=2000;
					while(i>0)
					{	Sleep(100);
						int re = ICC_PassCheck(ReaderHandle, &rlen, OutData);
						if(re==0)
						{
						//	ICC_PassCancel(ReaderHandle);
							return 0;
						}
						if(re==-1)
						{
						//	ICC_PassCancel(ReaderHandle);
							return -1;
						}
						if(re==-2)
						{
						//	ICC_PassCancel(ReaderHandle);
							return -2;
						}
						if(re==-4)
						{
							i=i-100;
							continue;				
						}
					}
					return -20;
				}
				//	return(OutReport[3]);//call failed 
				
				//get return data
				long returnlen=(int)OutReport[4];
//				len=(long)(returnlen);
				
				if(CardCommandT1==OutReport[1])
				{
					
					for(int l=0;l<returnlen;l++)
					{
						*(OutData++)=OutReport[5+l];
					}
				}
				else if(CPUOVERFLOWTITLE1==OutReport[1])
				{					
					for(int l=0;l<28;l++)
					{
						*(OutData++)=OutReport[5+l];
					}

					returnlen-=28;//返回字节数先减去27个
					
					int ltimelen=returnlen-28;
					
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<ltimelen;i++)
					{
						*(OutData++)=OutReport[2+i];
					}									
				}

		}
		else
		{
				
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=4;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=len%0x100+1;
				
				singletemp[5]=temp[3]=len/0x100;
				singletemp[6]=temp[4]=0x73;
						
				for(int k=0;k<26;k++)
				{
					singletemp[7+k]=temp[++itemp]=*(InData++);
				}
				
				len-=26;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);

				sentTime=(len/31)+1;
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(InData++);
						}
						
						len-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						int remainlen=strlen((char *)OutData);
						
						
						for(int k=0;k<len;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(InData++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);


						unsigned char rlen;
						if(OutReport[3])
						{
							int i=0;
							i=2000;
							while(i>0)
							{	Sleep(100);
								int re = ICC_PassCheck(ReaderHandle, &rlen, OutData);
								if(re==0)
								{
								//	ICC_PassCancel(ReaderHandle);
									return 0;
								}
								if(re==-1)
								{
								//	ICC_PassCancel(ReaderHandle);
									return -1;
								}
								if(re==-2)
								{
								//	ICC_PassCancel(ReaderHandle);
									return -2;
								}
								if(re==-4)
								{
									i=i-100;
									continue;				
								}
							}
							return -20;
						}
						
						int returnlen=(int)OutReport[4];

						if(CardCommandT1==OutReport[1])
						{		
							for(int l=0;l<returnlen;l++)
							{
								*(OutData++)=OutReport[5+l];
							}
						}
						else if(CPUOVERFLOWTITLE1==OutReport[1])
						{					
							for(int l=0;l<28;l++)
							{
								*(OutData++)=OutReport[5+l];
							}

							returnlen-=28;//返回字节数先减去27个
							
							int ltimelen=returnlen-28;
							
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<ltimelen;i++)
							{
								*(OutData++)=OutReport[2+i];
							}									
						}
						
					}

				}//while(sentTime)
	
		}

	return 0;	
}

long WINAPI ICC_PassChangeMkey(long ReaderHandle,unsigned char MkeyId ,unsigned char *Newmkey)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len = strlen((char*)Newmkey);
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=len+2;//低位
		temp[5]=0x00;//高位
		temp[6]=0x70; //1B  46  x  y  0D  0A
		temp[7]=MkeyId;

		for(int i=0;i<len;i++)
			temp[8+i]=Newmkey[i];
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(i=2;i<len+8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[len+8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];
		}


	return IFD_OK;	
}

long WINAPI ICC_PassChangeWkey(long ReaderHandle,unsigned char MkeyId ,unsigned char Wkeyid,unsigned char *Newmkey)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		int len = strlen((char*)Newmkey);
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=len+3;//低位
		temp[5]=0x00;//高位
		temp[6]=0x71; //1B  46  x  y  0D  0A
		temp[7]=MkeyId;
		temp[8]=Wkeyid;

		for(int i=0;i<len;i++)
			temp[9+i]=Newmkey[i];
		/*get and set xorbuffer*/
		unsigned xorbuffer=0x00;
		for(i=2;i<len+9;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[len+9]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];
		}


	return IFD_OK;	
}

long WINAPI ICC_PassActiveWkey(long ReaderHandle,unsigned char MkeyId ,unsigned char Wkeyid) //激活工作密钥 
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x72; //1B  46  x  y  0D  0A
		temp[7]=MkeyId;
		temp[8]=Wkeyid;


		unsigned xorbuffer=0x00;
		for(int i=2;i<9;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return OutReport[3];
		}


	return IFD_OK;	
}



long WINAPI ICC_Reader_4442_PowerOn(long ReaderHandle,unsigned char *data) //4442卡上电
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x50;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}


		int len=OutReport[4];

		for(i=0;i<len;i++)
			data[i]=OutReport[5+i];

	return IFD_OK;
}
long WINAPI ICC_Reader_4442_PowerOff(long ReaderHandle) //4442卡下电
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x51;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}
	

	return IFD_OK;
}

long WINAPI ICC_Reader_4442_Read(long ReaderHandle,int offset,int len,unsigned char *data) //4442卡读数据
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(offset<0||offset>255)
			return IFD_ParameterError;
		if(len<0||len>256)
			return IFD_ParameterError;
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[300];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x04;//低位
		temp[5]=0x00;//高位
		temp[6]=0x52;
		temp[7]=offset;
		temp[8]=len%0x100;
		temp[9]=len/0x100;

		unsigned xorbuffer=0x00;
		for(int i=2;i<10;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

		long returnlen=(int)OutReport[4];
//		returnlen+=(int)OutReport[5]<<8;
		
		if(CardCommandT1==OutReport[1])
		{
			
			for(int l=0;l<returnlen;l++)
			{
				*(data++)=OutReport[6+l];
			}
		}
		else if(CPUOVERFLOWTITLE1==OutReport[1])
		{
			int getTime=0;
			int iData=0;//the current count of out feature data
			long total = (int)OutReport[5]<<8;
			returnlen = returnlen+ total;
	//		len=(long)(returnlen);
			//the first time get feature
			for(int l=0;l<27;l++)
			{
				*(data++)=OutReport[6+l];
			}

			returnlen-=27;//返回字节数先减去27个
			if(returnlen==0)
				getTime=0;
			else
				getTime=(returnlen-1)/31+1;//如果为31的倍数时，应该是要减一

			//loop to get Feature data
			while(getTime>=1)
			{
				if(getTime!=1)
				{
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<31;i++)
					{
						*(data++)=OutReport[2+i];
						++iData;
					}
					
					getTime--;
				}
				else//the last time to get feature data
				{
					int ltimelen=returnlen-iData;
					
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<ltimelen;i++)
					{
						*(data++)=OutReport[2+i];
					}
					getTime--;
				}
			}//while(getTime>=1)
		}//else if(CPUOVERFLOWTITLE1==OutReport[1])

	return IFD_OK;	
}

long WINAPI ICC_Reader_4442_Write(long ReaderHandle,int offset,int len,unsigned char *data) //4442卡写数据 
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[300];
		unsigned char OutReport[300];
		memset(temp,0,300);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=(0x04+len)%0x100;//低位
		temp[5]=(0x04+len)/0x100;//高位
		temp[6]=0x53;
		temp[7]=offset;
		temp[8]=len%0x100;
		temp[9]=len/0x100;

		for(int i=0;i<len;i++)
		{
			temp[10+i]=data[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<(10+len);i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10+len]=xorbuffer;
		
		//send and get feature data

		if(len<23)
		{
				//send and get feature data
			HidD_SetFeature(hDev,temp,0x21);
			HidD_GetFeature(hDev,OutReport,0x21);

			if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
				return -100;

			if(OutReport[3])
			{
				return -20;
			}
			return IFD_OK;
				
		}
		else
		{
				
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(len+4)%0x100;
				
				//data
				singletemp[5]=temp[3]=(len+4)/0x100;

				singletemp[6]=temp[4]=0x53;
				singletemp[7]=temp[5]=offset;
				singletemp[8]=temp[6]=len%0x100;
				singletemp[9]=temp[7]=len/0x100;
				
				
				
				for(int k=0;k<23;k++)
				{
					singletemp[10+k]=temp[++itemp]=*(data++);
				}
				
				len-=23;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);
				
				if(len<=0)
					sentTime=1;
				else
				//	sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一
			    	sentTime=((len-1)/31)+1;//如果为31的倍数时，应该是要减一
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(data++);
						}
						
						len-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						//int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<len+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(data++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);

						if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
							return -100;
						if(OutReport[3])
						{
							return -20;

						}
												
						
					}
				//	return IFD_OK;
				}
			return IFD_OK;
		}

	return IFD_OK;	
}
long WINAPI ICC_Reader_4442_Verify(long ReaderHandle,unsigned char *key) //4442卡认证密钥
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x04;//低位
		temp[5]=0x00;//高位
		temp[6]=0x54;

		for(int i=0;i<3;i++)
		{
			temp[7+i]=key[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<10;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

	return IFD_OK;	
}

long WINAPI ICC_Reader_4442_Change(long ReaderHandle,unsigned char *newkey) //4442卡修改密钥
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x55;

		for(int i=0;i<3;i++)
		{
			temp[7+i]=newkey[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<10;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

	return IFD_OK;	
}
long WINAPI ICC_Reader_4442_ReadProtect(long ReaderHandle,int offset,int len,unsigned char *data) //4442卡读保护数据
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(offset<0||offset>255)
			return IFD_ParameterError;
		if(len<0||len>256)
			return IFD_ParameterError;
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
//		unsigned char m_data[256];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x56;
		temp[7]=offset;
		temp[8]=len;

//		unsigned char temp[255];
		unsigned char datatemp[4];
		unsigned char m_data[40];

		unsigned xorbuffer=0x00;
		for(int i=2;i<9;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

//		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
//			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

		long returnlen=(int)OutReport[4];
		
		if(CardCommandT1==OutReport[1])
		{
			
			for(int l=0;l<returnlen;l++)
			{
				datatemp[l]=OutReport[6+l];
			}
		}
		
		for(int j=0;j<4;j++)
		{
			unsigned char x = (datatemp[j]<<7);
			unsigned char y = x/0x80;
			m_data[0+8*j]=y;

			x = (datatemp[j]<<6);
			y = x/0x80;
			m_data[1+8*j]=y;

			x = (datatemp[j]<<5);
			y = x/0x80;
			m_data[2+8*j]=y;
			
			x = (datatemp[j]<<4);
			y = x/0x80;
			m_data[3+8*j]=y;

			x = (datatemp[j]<<3);
			y = x/0x80;
			m_data[4+8*j]=y;

			x = (datatemp[j]<<2);
			y = x/0x80;
			m_data[5+8*j]=y;

			x = (datatemp[j]<<1);
			y = x/0x80;
			m_data[6+8*j]=y;

			x = (datatemp[j]<<0);
			y = x/0x80;
			m_data[7+8*j]=y;
		}
		for(j=offset;j<(len+offset);j++)
			data[j-offset]=m_data[j];
		
	return IFD_OK;	
}
long WINAPI ICC_Reader_4442_WriteProtect(long ReaderHandle,int offset,int len,unsigned char *data) //4442卡写保护数据
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03+len;//低位
		temp[5]=0x00;//高位
		temp[6]=0x57;
		temp[7]=offset;
		temp[8]=len;

		for(int i=0;i<len;i++)
		{
			temp[9+i]=data[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<(9+len);i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9+len]=xorbuffer;
		
		//send and get feature data

		if(len<24)
		{
				//send and get feature data
			HidD_SetFeature(hDev,temp,0x21);
			HidD_GetFeature(hDev,OutReport,0x21);

			if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
				return -100;

			if(OutReport[3])
			{
				return -20;
			}
			return IFD_OK;
				
		}
		else
		{
				
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(len+3)%0x100;
				
				//data
				singletemp[5]=temp[3]=(len+3)/0x100;

				singletemp[6]=temp[4]=0x57;
				singletemp[7]=temp[5]=offset;
				singletemp[8]=temp[6]=len;
				
				
				
				for(int k=0;k<24;k++)
				{
					singletemp[9+k]=temp[++itemp]=*(data++);
				}
				
				len-=24;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);

				if(len<=0)
					sentTime=1;
				else
					//sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一
					sentTime=((len-1)/31)+1;//如果为31的倍数时，应该是要减一
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(data++);
						}
						
						len-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						//int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<len+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(data++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);

						if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
							return -1;
						if(OutReport[3])
						{
							return -20;

						}	
					}
				//	return IFD_OK;
				}
			return IFD_OK;
		}

	return IFD_OK;	
}
long WINAPI ICC_Reader_4442_ReadCount(long ReaderHandle) //读取4442卡密钥剩余认证次数
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x58;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return -1;
		}
		int len=OutReport[4];

		

	return OutReport[5];
}
/*############ 4428 基本操作函数#################*/

long WINAPI ICC_Reader_4428_PowerOn(long ReaderHandle,unsigned char *data) //4428卡上电
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x60;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}
		
		int len=OutReport[4];

		for(i=0;i<len;i++)
			data[i]=OutReport[5+i];

	return IFD_OK;
}
long WINAPI ICC_Reader_4428_PowerOff(long ReaderHandle) //4428卡下电
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x61;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);
		
		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}
	

	return IFD_OK;
}

long WINAPI ICC_Reader_4428_Read(long ReaderHandle,int offset,int len,unsigned char *data) //4428卡读数据
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(offset<0||offset>1024)
			return IFD_ParameterError;
		if(len<0||len>1025)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[1050];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x05;//低位
		temp[5]=0x00;//高位
		temp[6]=0x62;
		temp[7]=offset%0x100;
		temp[8]=offset/0x100;
		temp[9]=len%0x100;
		temp[10]=len/0x100;

		unsigned xorbuffer=0x00;
		for(int i=2;i<11;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[11]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

		long returnlen=(int)OutReport[4];
		
		if(CardCommandT1==OutReport[1])
		{
			
			for(int l=0;l<returnlen;l++)
			{
				*(data++)=OutReport[6+l];
			}
		}
		else if(CPUOVERFLOWTITLE1==OutReport[1])
		{
			int getTime=0;
			int iData=0;//the current count of out feature data
			long total = (int)OutReport[5]<<8;
			returnlen = returnlen+ total;
	//		len=(long)(returnlen);
			//the first time get feature
			for(int l=0;l<27;l++)
			{
				*(data++)=OutReport[6+l];
			}

			returnlen-=27;//返回字节数先减去27个
			if(returnlen==0)
				getTime=0;
			else
				getTime=(returnlen-1)/31+1;//如果为31的倍数时，应该是要减一

			//loop to get Feature data
			while(getTime>=1)
			{
				if(getTime!=1)
				{
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<31;i++)
					{
						*(data++)=OutReport[2+i];
						++iData;
					}
					
					getTime--;
				}
				else//the last time to get feature data
				{
					int ltimelen=returnlen-iData;
					
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<ltimelen;i++)
					{
						*(data++)=OutReport[2+i];
					}
					getTime--;
				}
			}//while(getTime>=1)
		}//else if(CPUOVERFLOWTITLE1==OutReport[1])

	return IFD_OK;	
}

long WINAPI ICC_Reader_4428_Write(long ReaderHandle,int offset,int len,unsigned char *data) //4428卡写数据 
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[1050];
		unsigned char OutReport[1050];
		memset(temp,0,1050);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=(0x05+len)%0x100;//低位
		temp[5]=(0x05+len)/0x100;//高位
		temp[6]=0x63;
		temp[7]=offset%0x100;
		temp[8]=offset/0x100;
		temp[9]=len%0x100;
		temp[10]=len/0x100;

	//	temp[7]=offset;
	//	temp[8]=len;

		for(int i=0;i<len;i++)
		{
			temp[11+i]=data[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<(11+len);i++)
		{
			xorbuffer^=temp[i];
		}
		temp[11+len]=xorbuffer;
		
		//send and get feature data

		if(len<22)
		{
				//send and get feature data
			HidD_SetFeature(hDev,temp,0x21);
			HidD_GetFeature(hDev,OutReport,0x21);

			if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
				return -100;

			if(OutReport[3])
			{
				return -20;
			}
			return IFD_OK;
				
		}
		else
		{
				
				memset(temp,0,1050);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(len+5)%0x100;
				
				//data
				singletemp[5]=temp[3]=(len+5)/0x100;

				singletemp[6]=temp[4]=0x63;
				singletemp[7]=temp[5]=offset%0x100;
				singletemp[8]=temp[6]=offset/0x100;
				singletemp[9]=temp[7]=len%0x100;
				singletemp[10]=temp[8]=len/0x100;
				
				
				
				for(int k=0;k<22;k++)
				{
					singletemp[11+k]=temp[++itemp]=*(data++);
				}
				
				len-=22;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);

				if(len<=0)
					sentTime=1;
				else
				//	sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一
					sentTime=((len-1)/31)+1;//如果为31的倍数时，应该是要减一
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(data++);
						}
						
						len-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[1050];
						memset(lasttemp,0,1050);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						//int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<len+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(data++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);

						if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
							return -100;

						if(OutReport[3])
						{
							return -20;

						}
						
						
						
					}
				//	return IFD_OK;
				}
			return IFD_OK;
		}

	return IFD_OK;	
}
long WINAPI ICC_Reader_4428_Verify(long ReaderHandle,unsigned char *key) //4428卡认证密钥
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x64;

		for(int i=0;i<2;i++)
		{
			temp[7+i]=key[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<9;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

	return IFD_OK;	
}

long WINAPI ICC_Reader_4428_Change(long ReaderHandle,unsigned char *newkey) //4428卡修改密钥
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x65;

		for(int i=0;i<3;i++)
		{
			temp[7+i]=newkey[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<10;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[10]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

	return IFD_OK;	
}
long WINAPI ICC_Reader_4428_ReadProtect(long ReaderHandle,int offset,int len,unsigned char *data) //4428卡读保护数据
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(offset<0||offset>1023)
			return IFD_ParameterError;
		if(len<0||len>1024)
			return IFD_ParameterError;
		HANDLE hDev = (HANDLE)ReaderHandle;

		unsigned char temp[255];
		unsigned char datatemp[256];
		unsigned char m_data[1024];

		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x66;
		temp[7]=offset;
		temp[8]=len;

		unsigned xorbuffer=0x00;
		for(int i=2;i<9;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

//		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
//			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

		long returnlen=(int)OutReport[4];
		
		if(CardCommandT1==OutReport[1])
		{
			
			for(int l=0;l<returnlen;l++)
			{
				datatemp[l]=OutReport[6+l];
			}
		}
		else if(CPUOVERFLOWTITLE1==OutReport[1])
		{
			int getTime=0;
			int iData=0;//the current count of out feature data
			long total = (int)OutReport[5]<<8;
			returnlen = returnlen+ total;
	//		len=(long)(returnlen);
			//the first time get feature
			for(int l=0;l<27;l++)
			{
				datatemp[l]=OutReport[6+l];
			}

			returnlen-=27;//返回字节数先减去27个
			if(returnlen==0)
				getTime=0;
			else
				getTime=(returnlen-1)/31+1;//如果为31的倍数时，应该是要减一

			//loop to get Feature data
			while(getTime>=1)
			{
				if(getTime!=1)
				{
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<31;i++)
					{
						datatemp[27+iData]=OutReport[2+i];
						++iData;
					}
					
					getTime--;
				}
				else//the last time to get feature data
				{
					int ltimelen=returnlen-iData;
					
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<ltimelen;i++)
					{
						datatemp[27+iData]=OutReport[2+i];
						++iData;
					}
					getTime--;
				}
			}//while(getTime>=1)
		}//else if(CPUOVERFLOWTITLE1==OutReport[1])
//		for(int j=0;j<128;j++)
//			datatemp[j]=data[j];
//		strcpy((char*)datatemp,(const char*)data);
		for(int j=0;j<128;j++)
		{
			unsigned char x = (datatemp[j]<<7);
			unsigned char y = x/0x80;
			m_data[0+8*j]=y;

			x = (datatemp[j]<<6);
			y = x/0x80;
			m_data[1+8*j]=y;

			x = (datatemp[j]<<5);
			y = x/0x80;
			m_data[2+8*j]=y;
			
			x = (datatemp[j]<<4);
			y = x/0x80;
			m_data[3+8*j]=y;

			x = (datatemp[j]<<3);
			y = x/0x80;
			m_data[4+8*j]=y;

			x = (datatemp[j]<<2);
			y = x/0x80;
			m_data[5+8*j]=y;

			x = (datatemp[j]<<1);
			y = x/0x80;
			m_data[6+8*j]=y;

			x = (datatemp[j]<<0);
			y = x/0x80;
			m_data[7+8*j]=y;
		}
		for(j=offset;j<(len+offset);j++)
			data[j-offset]=m_data[j];
	return IFD_OK;	
}
long WINAPI ICC_Reader_4428_WriteProtect(long ReaderHandle,int offset,int len,unsigned char *data) //4428卡写保护数据
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
//		unsigned char datatemp[256];
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
//		temp[4]=(0x03+len)%0x100;//低位
//		temp[5]=(0x03+len)/0x100;//高位
//		temp[6]=0x67;
//		temp[7]=offset;
//		temp[8]=len;
		temp[4]=(0x05+len)%0x100;//低位
		temp[5]=(0x05+len)/0x100;//高位
		temp[6]=0x67;
		temp[7]=offset%0x100;
		temp[8]=offset/0x100;
		temp[9]=len%0x100;
		temp[10]=len/0x100;

		for(int i=0;i<len;i++)
		{
			temp[11+i]=data[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<(11+len);i++)
		{
			xorbuffer^=temp[i];
		}
		temp[11+len]=xorbuffer;
		
		//send and get feature data

		if(len<22)
		{
				//send and get feature data
			HidD_SetFeature(hDev,temp,0x21);
			HidD_GetFeature(hDev,OutReport,0x21);

			if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

			if(OutReport[3])
			{
				return -20;
			}
			return IFD_OK;
				
		}
		else
		{
				
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
//				singletemp[4]=temp[2]=(len+3)%0x100;
				
//				//data
//				singletemp[5]=temp[3]=(len+3)/0x100;

//				singletemp[6]=temp[4]=0x53;
//				singletemp[7]=temp[5]=offset;
//				singletemp[8]=temp[6]=len;

				singletemp[4]=temp[2]=(len+5)%0x100;
				
				//data
				singletemp[5]=temp[3]=(len+5)/0x100;

				singletemp[6]=temp[4]=0x67;
				singletemp[7]=temp[5]=offset%0x100;
				singletemp[8]=temp[6]=offset/0x100;
				singletemp[9]=temp[7]=len%0x100;
				singletemp[10]=temp[8]=len/0x100;
				
				
				
				for(int k=0;k<22;k++)
				{
					singletemp[11+k]=temp[++itemp]=*(data++);
				}
				
				len-=22;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);
				
				if(len<=0)
					sentTime=1;
				else
				//	sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一
					sentTime=((len-1)/31)+1;//如果为31的倍数时，应该是要减一
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(data++);
						}
						
						len-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						//int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<len+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(data++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);

						if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
							return -100;

						if(OutReport[3])
						{
							return -20;

						}
						
												
					}
				//	return IFD_OK;
				}
			return IFD_OK;
		}


	return IFD_OK;	
}
long WINAPI ICC_Reader_4428_ReadCount(long ReaderHandle) //读取4428卡密钥剩余认证次数
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x68;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);
		
		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return -1;
		}
		int len=OutReport[4];

//		*count=OutReport[5];

	return OutReport[5];
}

long WINAPI ICC_Reader_24c_PowerOn(long ReaderHandle,unsigned char *data,unsigned char flag) //24cxx卡上电
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6d;
		temp[7]=flag;

		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

		int len=OutReport[4];

		for(i=0;i<len;i++)
			data[i]=OutReport[5+i];

	return IFD_OK;
}
long WINAPI ICC_Reader_24c_PowerOff(long ReaderHandle,unsigned char flag) //24cxx卡下电
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6a;
		temp[7]=flag;

		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}
	

	return IFD_OK;
}
long WINAPI ICC_Reader_24c_Read(long ReaderHandle,int offset,int len,unsigned char *data,unsigned char flag) //24cxx卡读数据
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(offset<0)
			return IFD_ParameterError;
		if(len<0)
			return IFD_ParameterError;
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[1050];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x06;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6b;
		temp[7]=flag;
		temp[8]=offset%0x100;
		temp[9]=offset/0x100;
		temp[10]=len%0x100;
		temp[11]=len/0x100;

		unsigned xorbuffer=0x00;
		for(int i=2;i<12;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[12]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

		long returnlen=(int)OutReport[4];
		
		if(CardCommandT1==OutReport[1])
		{
			
			for(int l=0;l<returnlen;l++)
			{
				*(data++)=OutReport[6+l];
			}
		}
		else if(CPUOVERFLOWTITLE1==OutReport[1])
		{
			int getTime=0;
			int iData=0;//the current count of out feature data
			long total = (int)OutReport[5]<<8;
			returnlen = returnlen+ total;
	//		len=(long)(returnlen);
			//the first time get feature
			for(int l=0;l<27;l++)
			{
				*(data++)=OutReport[6+l];
			}

			returnlen-=27;//返回字节数先减去27个
			if(returnlen==0)
				getTime=0;
			else
				getTime=(returnlen-1)/31+1;//如果为31的倍数时，应该是要减一

			//loop to get Feature data
			while(getTime>=1)
			{
				if(getTime!=1)
				{
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<31;i++)
					{
						*(data++)=OutReport[2+i];
						++iData;
					}
					
					getTime--;
				}
				else//the last time to get feature data
				{
					int ltimelen=returnlen-iData;
					
					HidD_GetFeature(hDev,OutReport,0x21);
					for(int i=0;i<ltimelen;i++)
					{
						*(data++)=OutReport[2+i];
					}
					getTime--;
				}
			}//while(getTime>=1)
		}//else if(CPUOVERFLOWTITLE1==OutReport[1])

	return IFD_OK;	
}
long WINAPI ICC_Reader_24c_Write(long ReaderHandle,int offset,int len,unsigned char *data,unsigned char flag) //24cxx卡写数据 
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[1050];
		unsigned char OutReport[1050];
		memset(temp,0,1050);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=(0x06+len)%0x100;//低位
		temp[5]=(0x06+len)/0x100;//高位
		temp[6]=0x6c;
		temp[7]=flag;
		temp[8]=offset%0x100;
		temp[9]=offset/0x100;
		temp[10]=len%0x100;
		temp[11]=len/0x100;

	//	temp[7]=offset;
	//	temp[8]=len;

		for(int i=0;i<len;i++)
		{
			temp[12+i]=data[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<(12+len);i++)
		{
			xorbuffer^=temp[i];
		}
		temp[12+len]=xorbuffer;
		
		//send and get feature data

		if(len<22)
		{
				//send and get feature data
			HidD_SetFeature(hDev,temp,0x21);
			HidD_GetFeature(hDev,OutReport,0x21);

			if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

			if(OutReport[3])
			{
				return -20;
			}
			return IFD_OK;
				
		}
		else
		{
				
				memset(temp,0,1050);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(len+6)%0x100;
				
				//data
				singletemp[5]=temp[3]=(len+6)/0x100;

				singletemp[6]=temp[4]=0x6c;
				singletemp[7]=temp[5]=flag;
				singletemp[8]=temp[6]=offset%0x100;
				singletemp[9]=temp[7]=offset/0x100;
				singletemp[10]=temp[8]=len%0x100;
				singletemp[11]=temp[9]=len/0x100;
				
				
				
				for(int k=0;k<21;k++)
				{
					singletemp[12+k]=temp[++itemp]=*(data++);
				}
				
				len-=21;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);

				if(len<=0)
					sentTime=1;
				else
				//	sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一
					sentTime=((len-1)/31)+1;//如果为31的倍数时，应该是要减一
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(data++);
						}
						
						len-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[1050];
						memset(lasttemp,0,1050);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						//int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<len+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(data++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);

						if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
							return -100;
						if(OutReport[3])
						{
							return -20;

						}
						
						
						
					}
				//	return IFD_OK;
				}
			return IFD_OK;
		}

	return IFD_OK;	
}
long WINAPI PICC_Reader_SetTypeA(long ReaderHandle)//设置读typeA
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x87;
		temp[7]=0x41;

		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);
		
		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return OutReport[3];
		}


	return IFD_OK;		
}

long WINAPI PICC_Reader_SetTypeB(long ReaderHandle)//设置读typeB
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x87;
		temp[7]=0x42;

		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return OutReport[3];
		}

	return IFD_OK;	
}

long WINAPI PICC_Reader_Select(long ReaderHandle,unsigned char cardtype)//选择卡片，41为typea 42为typeb
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;
/**/
	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		if(cardtype==0x41)
		{
			temp[6]=0x43;
			_cardtype=1;
		}
		else
		{
			temp[6]=0x8a;
			_cardtype=2;
		}

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}


	return IFD_OK;		
}

long WINAPI PICC_Reader_Request(long ReaderHandle)//typea请求卡片
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
/**/
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x41;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}



	return IFD_OK;
}

long WINAPI PICC_Reader_anticoll(long ReaderHandle,unsigned char *uid)//防碰撞 typea卡片
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
/**/
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x42;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}
		int len=OutReport[4];

		for(i=0;i<len;i++)
			uid[i]=OutReport[5+i];
	return IFD_OK;
}

long WINAPI PICC_Reader_PowerOnTypeA(long ReaderHandle,unsigned char* Response)//上电
{

	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x85;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);
		_FLAG=0;

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return -20;
		}
		
		int len=OutReport[4];

		for(i=0;i<len;i++)
			Response[i]=OutReport[5+i];

	return len;
}

long WINAPI PICC_Reader_PowerOnTypeB(long ReaderHandle,unsigned char* Response)//上电
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x01;//低位
		temp[5]=0x00;//高位
		temp[6]=0x88;

		unsigned xorbuffer=0x00;
		for(int i=2;i<7;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[7]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);
		
		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return -20;
		}
		int len=OutReport[4];

		for(i=0;i<len;i++)
			Response[i]=OutReport[5+i];

	return len;
}



long WINAPI PICC_Reader_Application1(long ReaderHandle,long Lenth_of_Command_APDU,
									unsigned char* Command_APDU,unsigned char* Response_APDU)  //type a/b执行apdu命令
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[300];
		unsigned char OutReport[300];
		unsigned char *psbuf;
		long len;
		
		memset(temp,0,300);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;//0x7d
		temp[4]=(Lenth_of_Command_APDU+3)%0x100;  //低字节
		
		//data
		temp[5]=(Lenth_of_Command_APDU+3)/0x100; //高字节
		temp[6]=0x86;
		
		_FLAG=_FLAG^1;
		if(_FLAG==1)
		{	
		//	if((Lenth_of_Command_APDU+2)>52)
				temp[7]=0x1a;
		//	else
		//		temp[7]=0x0a;
		}	
		else if(_FLAG==0)
		{
		//	if((Lenth_of_Command_APDU+2)>52)
				temp[7]=0x1b;
		//	else
		//		temp[7]=0x0b;
		}
			
		temp[8]=0x00;

		psbuf=Command_APDU;
		
		for(int j=9;j<9+Lenth_of_Command_APDU;j++)
		{
			temp[j]=Command_APDU[j-9];
		}
		
		//get and set xorbuffer
		unsigned xorbuffer=0x00;
		for(int i=2;i<j;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[j]=xorbuffer;

		if(Lenth_of_Command_APDU<24)
		{
				//send and get feature data
				HidD_SetFeature(hDev,temp,0x21);
				HidD_GetFeature(hDev,OutReport,0x21);


				if(OutReport[3])
				{
					return -20;

				}
				//	return(OutReport[3]);//call failed 
				
				//get return data
				long returnlen=(int)OutReport[4]-2;
				len=(long)(returnlen);
				
				if(CardCommandT1==OutReport[1])
				{
					
					for(int l=0;l<returnlen;l++)
					{
						*(Response_APDU++)=OutReport[8+l];
					}
				}
				else if(CPUOVERFLOWTITLE1==OutReport[1])
				{
					int getTime=0;
					int iData=0;//the current count of out feature data
					long total = (int)OutReport[5]<<8;
					returnlen = returnlen+ total;
					len=(long)(returnlen);
					//the first time get feature
					for(int l=0;l<25;l++)
					{
						*(Response_APDU++)=OutReport[8+l];
					}

					returnlen-=25;//返回字节数先减去27个
					if(returnlen==0)
						getTime=0;
					else
						getTime=(returnlen-1)/31+1;

					//loop to get Feature data
					while(getTime>=1)
					{
						if(getTime!=1)
						{
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<31;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
								++iData;
							}
							
							getTime--;
						}
						else//the last time to get feature data
						{
							int ltimelen=returnlen-iData;
							
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<ltimelen;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
							}
							getTime--;
						}
					}//while(getTime>=1)
				}//else if(CPUOVERFLOWTITLE1==OutReport[1])
//			return (0);//sucess
		}
		else
		{
				
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(Lenth_of_Command_APDU+3)%0x100;
				
				//data
				singletemp[5]=temp[3]=(Lenth_of_Command_APDU+3)/0x100;
				singletemp[6]=temp[4]=0x86;

			//	_FLAG=_FLAG^1;
				if(_FLAG==1)
				{	
				//	if((Lenth_of_Command_APDU+2)>52)
						singletemp[7]=temp[5]=0x1a;
				//	else
				//		singletemp[7]=temp[5]=0x0a;
				}	
				else if(_FLAG==0)
				{
				//	if((Lenth_of_Command_APDU+2)>52)
						singletemp[7]=temp[5]=0x1b;
				//	else
				//		singletemp[7]=temp[5]=0x0b;
				}
			//	singletemp[7]=temp[5]=0x0c;
				singletemp[8]=temp[6]=0x00;
				
				
				
				for(int k=0;k<24;k++)
				{
					singletemp[9+k]=temp[++itemp]=*(Command_APDU++);
				}
				
				Lenth_of_Command_APDU-=24;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);

				if(Lenth_of_Command_APDU<=0)
					sentTime=1;
				else
					sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一

		//		sentTime=((Lenth_of_Command_APDU-1)/31)+1;
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						Lenth_of_Command_APDU-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<Lenth_of_Command_APDU+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);


						if(OutReport[3])
						{
							return -20;

						}
						
						int returnlen=(int)OutReport[4]-2;
						len=(long)(returnlen);
						
						//get the return buffer data
						for(int l=0;l<returnlen;l++)
						{
							*(Response_APDU++)=OutReport[8+l];
						}
						
				//		return (0);//sucess
						
					}

				}//while(sentTime)
	
		}

	return len;	
}

long WINAPI PICC_Reader_Application2(long ReaderHandle,long Lenth_of_Command_APDU,
									unsigned char* Command_APDU,unsigned char* Response_APDU)  //type a/b执行apdu命令
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[300];
		unsigned char OutReport[300];
		unsigned char *psbuf;
		long len;
		
		memset(temp,0,300);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;//0x7d
		temp[4]=(Lenth_of_Command_APDU+3)%0x100;  //低字节
		
		//data
		temp[5]=(Lenth_of_Command_APDU+3)/0x100; //高字节
		temp[6]=0x86;
		
		_FLAG=_FLAG^1;
		if(_FLAG==1)
		{	
			temp[7]=0x0a;
		}	
		else if(_FLAG==0)
		{
			temp[7]=0x0b;
		}
			
		temp[8]=0x00;

		psbuf=Command_APDU;
		
		for(int j=9;j<9+Lenth_of_Command_APDU;j++)
		{
			temp[j]=Command_APDU[j-9];
		}
		
		//get and set xorbuffer
		unsigned xorbuffer=0x00;
		for(int i=2;i<j;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[j]=xorbuffer;

		if(Lenth_of_Command_APDU<24)
		{
				//send and get feature data
				HidD_SetFeature(hDev,temp,0x21);
				HidD_GetFeature(hDev,OutReport,0x21);


				if(OutReport[3])
				{
					return -20;

				}
				//	return(OutReport[3]);//call failed 
				
				//get return data
				long returnlen=(int)OutReport[4]-2;
				len=(long)(returnlen);
				
				if(CardCommandT1==OutReport[1])
				{
					
					for(int l=0;l<returnlen;l++)
					{
						*(Response_APDU++)=OutReport[8+l];
					}
				}
				else if(CPUOVERFLOWTITLE1==OutReport[1])
				{
					int getTime=0;
					int iData=0;//the current count of out feature data
					long total = (int)OutReport[5]<<8;
					returnlen = returnlen+ total;
					len=(long)(returnlen);
					//the first time get feature
					for(int l=0;l<25;l++)
					{
						*(Response_APDU++)=OutReport[8+l];
					}

					returnlen-=25;//返回字节数先减去27个
					if(returnlen==0)
						getTime=0;
					else
						getTime=(returnlen-1)/31+1;

					//loop to get Feature data
					while(getTime>=1)
					{
						if(getTime!=1)
						{
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<31;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
								++iData;
							}
							
							getTime--;
						}
						else//the last time to get feature data
						{
							int ltimelen=returnlen-iData;
							
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<ltimelen;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
							}
							getTime--;
						}
					}//while(getTime>=1)
				}//else if(CPUOVERFLOWTITLE1==OutReport[1])
//			return (0);//sucess
		}
		else
		{
				
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(Lenth_of_Command_APDU+3)%0x100;
				
				//data
				singletemp[5]=temp[3]=(Lenth_of_Command_APDU+3)/0x100;
				singletemp[6]=temp[4]=0x86;

			//	_FLAG=_FLAG^1;
				if(_FLAG==1)
				{	
					singletemp[7]=temp[5]=0x0a;
				}	
				else if(_FLAG==0)
				{
					singletemp[7]=temp[5]=0x0b;
				}
			//	singletemp[7]=temp[5]=0x0c;
				singletemp[8]=temp[6]=0x00;
				
				
				
				for(int k=0;k<24;k++)
				{
					singletemp[9+k]=temp[++itemp]=*(Command_APDU++);
				}
				
				Lenth_of_Command_APDU-=24;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);

				if(Lenth_of_Command_APDU<=0)
					sentTime=1;
				else
					sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一

			//	sentTime=((Lenth_of_Command_APDU-1)/31)+1;
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						Lenth_of_Command_APDU-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<Lenth_of_Command_APDU+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);


						if(OutReport[3])
						{
							return -20;

						}
						
						int returnlen=(int)OutReport[4]-2;
						len=(long)(returnlen);
						
						//get the return buffer data
						for(int l=0;l<returnlen;l++)
						{
							*(Response_APDU++)=OutReport[8+l];
						}
						
				//		return (0);//sucess
						
					}

				}//while(sentTime)
	
		}

	return len;	
}

long WINAPI PICC_Reader_Application(long ReaderHandle,long Lenth_of_Command_APDU,
									unsigned char* Command_APDU,unsigned char* Response_APDU)  //type a/b执行apdu命令
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}

		HANDLE hDev=(HANDLE)ReaderHandle;
		unsigned char temp[300];
		unsigned char OutReport[300];
		unsigned char *psbuf;
		long len;
		
		memset(temp,0,300);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;//0x7d
		temp[4]=(Lenth_of_Command_APDU+3)%0x100;  //低字节
		
		//data
		temp[5]=(Lenth_of_Command_APDU+3)/0x100; //高字节
		temp[6]=0x86;
		
		_FLAG=_FLAG^1;
		if(_FLAG==1)
		{	
			temp[7]=0x00;
		}	
		else if(_FLAG==0)
		{
			temp[7]=0x00;
		}
		if(flagLong==1)
		{
			temp[8]=longtimedata[0];	
			temp[9]=longtimedata[1];
			unsigned xorbuffer=0x00;
			for(int i=2;i<10;i++)
			{
				xorbuffer^=temp[i];
			}
			temp[10]=xorbuffer;

			flagLong=0;
		}
		else
		{
			temp[8]=0x00;
			psbuf=Command_APDU;
			
			for(int j=9;j<9+Lenth_of_Command_APDU;j++)
			{
				temp[j]=Command_APDU[j-9];
			}		
			unsigned xorbuffer=0x00;
			for(int i=2;i<j;i++)
			{
				xorbuffer^=temp[i];
			}
			temp[j]=xorbuffer;
		}

		if(Lenth_of_Command_APDU<24)
		{
				//send and get feature data
				HidD_SetFeature(hDev,temp,0x21);
				HidD_GetFeature(hDev,OutReport,0x21);

				if(OutReport[2]!=0x02)
					return -1;

				if(OutReport[3])
				{
					return -20;
				}

				if(OutReport[7]>>4==0x0f)
				{
					flagLong=1;
					longtimedata[0]=OutReport[7];
					longtimedata[1]=OutReport[8];
					int re =PICC_Reader_Application(ReaderHandle,1,NULL,Response_APDU);
					return re;
				}
				//	return(OutReport[3]);//call failed 
				
				//get return data
				long returnlen=(int)OutReport[4]-2;
				len=(long)(returnlen);
				
				if(CardCommandT1==OutReport[1])
				{
					
					for(int l=0;l<returnlen;l++)
					{
						*(Response_APDU++)=OutReport[8+l];
					}
				}
				else if(CPUOVERFLOWTITLE1==OutReport[1])
				{
					int getTime=0;
					int iData=0;//the current count of out feature data
					long total = (int)OutReport[5]<<8;
					returnlen = returnlen+ total;
					len=(long)(returnlen);
					//the first time get feature
					for(int l=0;l<25;l++)
					{
						*(Response_APDU++)=OutReport[8+l];
					}

					returnlen-=25;//返回字节数先减去25个
					if(returnlen==0)
						getTime=0;
					else
						getTime=(returnlen-1)/31+1;

					//loop to get Feature data
					while(getTime>=1)
					{
						if(getTime!=1)
						{
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<31;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
								++iData;
							}
							
							getTime--;
						}
						else//the last time to get feature data
						{
							int ltimelen=returnlen-iData;
							
							HidD_GetFeature(hDev,OutReport,0x21);
							for(int i=0;i<ltimelen;i++)
							{
								*(Response_APDU++)=OutReport[2+i];
							}
							getTime--;
						}
					}//while(getTime>=1)
				}//else if(CPUOVERFLOWTITLE1==OutReport[1])
//			return (0);//sucess
		}
		else
		{
				
				memset(temp,0,300);
				OutReport[0]=0;

				int sentTime=0;
				int itemp=6;//count of xorbuffer
				
				
				//the first time sent feature
				unsigned char singletemp[300];
				memset(singletemp,0,300);
				
				singletemp[1]=CPUOVERFLOWTITLE1;
				singletemp[2]=temp[0]=CardCommandT3;
				singletemp[3]=temp[1]=0x00;//0x7d
				singletemp[4]=temp[2]=(Lenth_of_Command_APDU+3)%0x100;
				
				//data
				singletemp[5]=temp[3]=(Lenth_of_Command_APDU+3)/0x100;
				singletemp[6]=temp[4]=0x86;

			//	_FLAG=_FLAG^1;
				if(_FLAG==1)
				{	
				//	if((Lenth_of_Command_APDU+2)>52)
						singletemp[7]=temp[5]=0x00;
				//	else
				//		singletemp[7]=temp[5]=0x0a;
				}	
				else if(_FLAG==0)
				{
				//	if((Lenth_of_Command_APDU+2)>52)
						singletemp[7]=temp[5]=0x00;
				//	else
				//		singletemp[7]=temp[5]=0x0b;
				}
			//	singletemp[7]=temp[5]=0x0c;
				singletemp[8]=temp[6]=0x00;
				
				
				
				for(int k=0;k<24;k++)
				{
					singletemp[9+k]=temp[++itemp]=*(Command_APDU++);
				}
				
				Lenth_of_Command_APDU-=24;
				//sent feature time:1
				HidD_SetFeature(hDev,singletemp,0x21);
				
				if(Lenth_of_Command_APDU<=0)
					sentTime=1;
				else
					sentTime=((Lenth_of_Command_APDU-1)/31)+1;//如果为31的倍数时，应该是要减一
	//			sentTime=((Lenth_of_Command_APDU-1)/31)+1;
				
				//loop to sent feature
				while(sentTime)
				{
					
					
					if(sentTime!=1)
					{
						unsigned char stemp[255];
						memset(stemp,0,255);
						
						stemp[1]=CPUOVERFLOWTITLE1;
						//	stemp[1]=temp[++itemp]=CPUOVERFLOWTITLE1;
						
						//data
						
						
						for(int k=0;k<31;k++)
						{
							stemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						Lenth_of_Command_APDU-=31;
						//sent feature time:1
						HidD_SetFeature(hDev,stemp,0x21);
						
						sentTime--;
					}
					else//sentTime=1
					{
						unsigned char lasttemp[300];
						memset(lasttemp,0,300);
						
						//	lasttemp[1]=temp[++itemp]=CPUSENTTITLE1;
						lasttemp[1]=CardCommandT1;
						
						//data
						
						int remainlen=strlen((char *)Command_APDU);
						
						
						for(int k=0;k<Lenth_of_Command_APDU+1;k++)
						{
							lasttemp[2+k]=temp[++itemp]=*(Command_APDU++);
						}
						
						//get and set xorbuffer
						unsigned xorbuffer=0x00;
						for(int i=0;i<itemp+1;i++)
						{
							xorbuffer^=temp[i];
						}
						lasttemp[2+k]=xorbuffer;
						//sent feature time:1
						sentTime--;
						
						HidD_SetFeature(hDev,lasttemp,0x21);
						HidD_GetFeature(hDev,OutReport,0x21);


						if(OutReport[3])
						{
							return -20;

						}
						
						int returnlen=(int)OutReport[4]-2;
						len=(long)(returnlen);
						
						//get the return buffer data
						for(int l=0;l<returnlen;l++)
						{
							*(Response_APDU++)=OutReport[8+l];
						}
						
				//		return (0);//sucess
						
					}

				}//while(sentTime)
	
		}

	return len;	
}


long WINAPI ICC_DispSound(long ReaderHandle,unsigned char type) //声音提示信息
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		
		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x6b;
		temp[7]=type;

		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[3])
		{
			return -20;
		}

	return 0;	
}


long WINAPI PICC_Reader_Authentication(long ReaderHandle,unsigned char Mode, unsigned char SecNr)
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}/**/
		if(SecNr<0||SecNr>39)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x03;//低位
		temp[5]=0x00;//高位
		temp[6]=0x44;
		temp[7]=Mode;
		temp[8]=SecNr;

		unsigned xorbuffer=0x00;
		for(int i=2;i<9;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[9]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return OutReport[3];
		}
		
	return IFD_OK;

}

long WINAPI PICC_Reader_Authentication_Pass(long ReaderHandle,unsigned char Mode, unsigned char SecNr,unsigned char *PassWord)//认证密钥 M1
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}/**/
		if(SecNr<0||SecNr>39)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x09;//低位
		temp[5]=0x00;//高位
		temp[6]=0x44;
		temp[7]=Mode;
		temp[8]=SecNr;

		for(int i=0;i<6;i++)
		{
			temp[9+i]=PassWord[i];
		}


		unsigned xorbuffer=0x00;
		for(i=2;i<15;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[15]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return OutReport[3];
		}
		
	return IFD_OK;	
}

long WINAPI PICC_Reader_Read(long ReaderHandle,unsigned char Addr,unsigned char *Data)	//读取卡片M1
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}/**/
		if(Addr<0||Addr>255)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x46;
		temp[7]=Addr;

		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);
		
		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}

	/*	unsigned char uctmp[20]={0};
		short uclen = 0;

		

		unsigned char conver[17];
		int flag =0;
		memset(conver,0x00,16);
		if(Addr<0x80)
		{
			if(Addr==0 || Addr%4==3 )
			{
				for(i=0;i<16;i++)
				{
					*(Data++)=OutReport[i+5];
				}
				return IFD_OK;
			}
			
		}
		else
		{
			if((Addr-0x80)%16==0x0f )
			{
				for(i=0;i<16;i++)
				{
					*(Data++)=OutReport[i+5];
				}
				return IFD_OK;
			}
		
		}

		for(i=0;i<16;i++)
		{
			if(OutReport[i+5]!=conver[i])
			{
				flag =1;
				break;
			}
		}
		if(flag==1)
		{
			memset(conver,0xff,16);
			for(i=0;i<16;i++)
			{
				if(OutReport[i+5]!=conver[i])
				{
					flag =2;
					break;
				}	
			}
		}

		if(flag == 2)//如果为0代表是全o 如果为1 代表是全f
		{
			HD_3DES_DecryptByte(OutReport+5,16,uctmp,&uclen);
			for(i=0;i<16;i++)
			{
				*(Data++)=uctmp[i];
			}
			
		}
		else
		{
			for(i=0;i<16;i++)
			{
				*(Data++)=OutReport[i+5];
			}
		}

	*/
		for(i=0;i<16;i++)
		{
			*(Data++)=OutReport[5+i];
		}
		
	return IFD_OK;

}

long WINAPI PICC_Reader_Write(long ReaderHandle,unsigned char Addr,unsigned char *Data)//写入数据M1
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
/**/		if(Addr<0||Addr>255)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02+0x10;//低位
		temp[5]=0x00;//高位
		temp[6]=0x47;
		temp[7]=Addr;
		
/*		unsigned char uctmp[20]={0};
		short uclen = 0;

		unsigned char conver[17];
		int flag =0;
		memset(conver,0x00,16);

		for(int i=0;i<16;i++)
		{
			if(Data[i]!=conver[i])
			{
				flag =1;
				break;
			}
		}
		if(flag==1)
		{
			memset(conver,0xff,16);
			for(i=0;i<16;i++)
			{
				if(Data[i]!=conver[i])
				{
					flag =2;
					break;
				}
			}
		}


		if(Addr<0x80)
		{
			if(Addr==0 || Addr%4==3 )
			{
				flag=0;
			}
		}
		else
		{
			if((Addr-0x80)%16==0x0f )
			{
				flag=0;
			}
		}

		if(flag ==2)
		{
			HD_3DES_EncryptByte(Data,16,uctmp,&uclen);
			
			for(i=0;i<16;i++)
			{
				temp[8+i]=uctmp[i];
			}
		}
		else
		{
			for(i=0;i<16;i++)
			{
				temp[8+i]=Data[i];
			}
		}
*/		
		
		for(int i=0;i<16;i++)
		{
			temp[8+i]=Data[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<24;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[24]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -100;

		if(OutReport[3])
		{
			return OutReport[3];
		}
		
	return IFD_OK;

}

long WINAPI PICC_Reader_LoadKey(long ReaderHandle,unsigned char Mode,unsigned char SecNr,unsigned char *Key)//装载密钥
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;
/**/
	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(SecNr<0||SecNr>39)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x09;//低位
		temp[5]=0x00;//高位
		temp[6]=0x4c;
		temp[7]=Mode;
		temp[8]=SecNr;


		for(int i=0;i<6;i++)
		{
			temp[9+i]=Key[i];
		}

		unsigned xorbuffer=0x00;
		for(i=2;i<15;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[15]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return OutReport[3];
		}
		
	return IFD_OK;
}

long WINAPI PICC_Reader_Readval(long ReaderHandle,unsigned char Addr,unsigned long *value)	//读值
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(Addr<0||Addr>255)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;//低位
		temp[5]=0x00;//高位
		temp[6]=0x46;
		temp[7]=Addr;

		unsigned xorbuffer=0x00;
		for(int i=2;i<8;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[8]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return -14;
		}
		unsigned char Data[16]={0};
		for(i=0;i<16;i++)
		{
			Data[i]=OutReport[5+i];
		}
		for(i=0;i<4;i++)
		{
			if(Data[i]!=Data[i+8])
				return -14;
			if((Data[i]^0xff)!=Data[i+4])
				return -14;
		}
		if(Data[12]!=Data[14])
			return -14;
		if(Data[13]!=Data[15])
			return -14;
		if((Data[12]^0xff)!=Data[13])
			return -14;
		*value=Data[0]+Data[1]*256+Data[2]*65536+Data[3]*16777216;

		return IFD_OK;
}

long WINAPI PICC_Reader_Initval(long ReaderHandle,unsigned char Addr,unsigned long value)//初始化值
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(Addr<0||Addr>255)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x12;//低位
		temp[5]=0x00;//高位
		temp[6]=0x47;
		temp[7]=Addr;

		if(value<0||value>0xffffffff)
			return IFD_ParameterError;
		temp[8]=value%256;
		temp[9]=(value%65536)/256;
		temp[10]=(value%16777216)/65536;
		temp[11]=value/16777216;
		temp[12]=temp[8]^0xff;
		temp[13]=temp[9]^0xff;
		temp[14]=temp[10]^0xff;
		temp[15]=temp[11]^0xff;
		temp[16]=temp[8];
		temp[17]=temp[9];
		temp[18]=temp[10];
		temp[19]=temp[11];
		temp[20]=Addr;
		temp[21]=Addr^0xff;
		temp[22]=Addr;
		temp[23]=Addr^0xff;


		unsigned xorbuffer=0x00;
		for(int i=2;i<24;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[24]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return IFD_ParameterError;
		}
		
	return IFD_OK;
}

long WINAPI PICC_Reader_Increment(long ReaderHandle,unsigned char Addr,unsigned long value)	//增值
{
		if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(Addr<0||Addr>255)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x06;//低位
		temp[5]=0x00;//高位
		temp[6]=0x48;
		temp[7]=Addr;
		if(value<0||value>0xffffffff)
			return IFD_ParameterError;
		temp[8]=value%256;
		temp[9]=(value%65536)/256;
		temp[10]=(value%16777216)/65536;
		temp[11]=value/16777216;

		unsigned xorbuffer=0x00;
		for(int i=2;i<12;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[12]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return -14;
		}

		return IFD_OK;

}

long WINAPI PICC_Reader_Decrement(long ReaderHandle,unsigned char Addr,unsigned long value)//减值
{
		if(ReaderHandle<=0)
		return IFD_UnConnected;

	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
				return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}
		if(Addr<0||Addr>255)
			return IFD_ParameterError;

		HANDLE hDev = (HANDLE)ReaderHandle;
		unsigned char temp[255];
		unsigned char OutReport[255];
		memset(temp,0,255);
		OutReport[0]=0;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x06;//低位
		temp[5]=0x00;//高位
		temp[6]=0x49;
		temp[7]=Addr;
		if(value<0||value>0xffffffff)
			return IFD_ParameterError;
		temp[8]=value%256;
		temp[9]=(value%65536)/256;
		temp[10]=(value%16777216)/65536;
		temp[11]=value/16777216;

		unsigned xorbuffer=0x00;
		for(int i=2;i<12;i++)
		{
			xorbuffer^=temp[i];
		}
		temp[12]=xorbuffer;
		
		//send and get feature data
		HidD_SetFeature(hDev,temp,0x21);
		
		HidD_GetFeature(hDev,OutReport,0x21);

		if(OutReport[1]!=0x02 || OutReport[2]!=0x02)
			return -1;

		if(OutReport[3])
		{
			return -14;
		}

		return IFD_OK;
}

long WINAPI PICC_Reader_ID_Request(long ReaderHandle)//身份证寻卡
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;
	
	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
			return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}	
	HANDLE hDev=(HANDLE)ReaderHandle;
	unsigned char temp[255]={0};
	unsigned char OutReport[255]={0};
	
	OutReport[0]=0;
	temp[1]=CardCommandT1;
	temp[2]=CardCommandT3;
	temp[3]=0x00;
	temp[4]=0x01;
	temp[5]=0x00;
	temp[6]=ID_REQUEST;
	temp[7]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6];
	
	//set and get feature data
	HidD_SetFeature(hDev,temp,0x21);
	HidD_GetFeature(hDev,OutReport,0x21);
	if(OutReport[3])
		return IFD_ICC_NoExist;//call failed卡片类型不对

	return IFD_OK;

}

long WINAPI PICC_Reader_ID_Select(long ReaderHandle)//身份证选卡
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;
	
	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
			return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}	
	HANDLE hDev=(HANDLE)ReaderHandle;
	unsigned char temp[255]={0};
	unsigned char OutReport[255]={0};
	
	OutReport[0]=0;
	temp[1]=CardCommandT1;
	temp[2]=CardCommandT3;
	temp[3]=0x00;
	temp[4]=0x01;
	temp[5]=0x00;
	temp[6]=ID_SELECT;
	temp[7]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6];
	
	//set and get feature data
	HidD_SetFeature(hDev,temp,0x21);
	HidD_GetFeature(hDev,OutReport,0x21);
	if(OutReport[3]==1)
		return IFD_ICC_NoExist;//call failed无卡
	
	return IFD_OK;

}

long WINAPI PICC_Reader_ID_Read(long ReaderHandle,unsigned char* Response)//身份证读卡
{
	if(ReaderHandle<=0)
		return IFD_UnConnected;
	
	if(flagAUTO==0)
	{
		for(int x=1;x<10;)
		{
			if(m_sCOM[x].ReaderHandle == ReaderHandle)
			{
				if(m_sCOM[x].stat != 1)
					return IFD_UnConnected;
				else
					break;
			}	
			x++;
		}
		if(x==10)
			return IFD_UnConnected;
	}
	else 
	{
		if(ReaderHandle!=autoRead)
			return IFD_UnConnected;
	}	
	HANDLE hDev=(HANDLE)ReaderHandle;
	unsigned char temp[255]={0};
	unsigned char OutReport[2048]={0};
	long len;
	
	OutReport[0]=0;
	temp[1]=CardCommandT1;
	temp[2]=CardCommandT3;
	temp[3]=0x00;
	temp[4]=0x01;
	temp[5]=0x00;
	temp[6]=ID_READ;
	temp[7]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6];
	
	//set and get feature data
	HidD_SetFeature(hDev,temp,0x21);
	Sleep(1000);
	HidD_GetFeature(hDev,OutReport,0x21);	
	if(OutReport[3])
	{
	return -20;
	}
	//	return(OutReport[3]);//call failed 
	
	//get return data
	long returnlen=(int)OutReport[4];
	len=(long)(returnlen);
	
	if(CardCommandT1==OutReport[1])
	{
		
		for(int l=0;l<returnlen;l++)
		{
			*(Response++)=OutReport[6+l];
		}
	}
	else if(CPUOVERFLOWTITLE1==OutReport[1])
	{
		int getTime=0;
		int iData=0;//the current count of out feature data
		long total = (int)OutReport[5]<<8;
		returnlen = returnlen+ total;
		len=(long)(returnlen);
		//the first time get feature
		for(int l=0;l<27;l++)
		{
			*(Response++)=OutReport[6+l];
		}
		
		returnlen-=27;//返回字节数先减去27个
		if(returnlen==0)
			getTime=0;
		else
			getTime=(returnlen-1)/31+1;//如果为31的倍数时，应该是要减一
		
		//loop to get Feature data
		while(getTime>=1)
		{
			if(getTime!=1)
			{
				HidD_GetFeature(hDev,OutReport,0x21);
				for(int i=0;i<31;i++)
				{
					*(Response++)=OutReport[2+i];
					++iData;
				}
				
				getTime--;
			}
			else//the last time to get feature data
			{
				int ltimelen=returnlen-iData;
				
				HidD_GetFeature(hDev,OutReport,0x21);
				for(int i=0;i<ltimelen;i++)
				{
					*(Response++)=OutReport[2+i];
				}
				getTime--;
			}
		}//while(getTime>=1)
	}
	return len;
}

long WINAPI Run(char* flag,char*data,char*err)
{
	int st;
	switch(atoi(flag))
	{
	case 1000://用户卡复位(包含打开串口和卡上电
		st = SelectFile1(data,err);
		break;
	case 1001://打开串口
		st = SelectFile2(data,err);
		break;
	case 1002://关闭串口
		st = SelectFile3(data,err);
		break;
	case 1003://卡上电
		st = SelectFile4(data,err);
		break;
	case 1004://卡下电
		st = SelectFile5(data,err);
		break;
	case 1005://检查是否是社保卡
		st = SelectFile6(data,err);
		break;
	case 2000://读取PSAM卡信息
		st = SelectFile7(data,err);
		break;
	case 2001://读取卡号
		st = SelectFile8(data,err);
		break;
	case 2002://读取社会保障号码
		st = SelectFile9(data,err);
		break;
	case 2003://读取终端信息
		st = SelectFile10(data,err);
		break;
	case 2004://读取发卡基本数据文件
		st = SelectFile11(data,err);
		break;
	case 2005://读取持卡人基本信息文件
		st = SelectFile12(data,err);
		break;
	case 2006://读取指定信息
		st = SelectFile13(data,err);
		break;
	case 2007://读取指定数据文件
		st = SelectFile14(data,err);
		break;
	case 3001://更新指定信息
		st = SelectFile15(data,err);
		break;
	case 4001://个人密码校验
		st = PerPINVerify(data,err);
		break;
	case 4002://个人密码修改
		st = PerPINChange(data,err);
		break;
	case 4003://个人密码解锁
		st = PerPINUnLock(data,err);
		break;
	case 4004://获取加密键盘密码
		st = GetPassWord(data,err);
		break;
	case 4005://密码重置
		st = ResetPassWord(data,err);
		break;
	}
	return st;	
			
}