// BHGX_HD.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "BHGX_HD.h"

long DevHandle;
char g_DF[20]={0};
int g_iCardType=-1; //卡片类型 0：CPU卡；1：SAM卡；2：M1卡

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
			break;		
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

BHGX_HD_API BOOL __stdcall bProbe(void)
{
	//::MessageBox(NULL,"bProbe",NULL,MB_OK);
	int re = -1;
	re = ICC_Reader_Open("USB1");
	if(re <= 0)
	{
		return FALSE;
	}
	ICC_Reader_Close(re);
	return TRUE;
}

BHGX_HD_API int __stdcall iOpen(void)
{
	HANDLE hDev=NULL;
	DevHandle = ICC_Reader_Open("USB1");
	int ret=iDOpenPort();
	if(DevHandle <= 0||ret!=0)
	{
		return WS_ERR_DEVICECONNECT;
	}
	return WS_OK;
}

BHGX_HD_API int __stdcall iClose(void)
{
	int re = -1;
	re = ICC_Reader_Close(DevHandle);
	iDClosePort();
	if(re != 0 || DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}
	return WS_OK;
}

BHGX_HD_API int __stdcall iReadBin( unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, int iSizeInBytes, int iOffsetInBytes )
{
	char Message[500]={0};
	sprintf(Message,"(iReadBin)卡类型:%d\r\n文件名:%s\r\n字节数:%d\r\n偏移:%d",iCardType,pKey,iSizeInBytes,iOffsetInBytes);
	::MessageBox(NULL,Message,NULL,MB_OK);
	///////////////////////////
	HANDLE  hDev=NULL;
	char Key[16] = {0};
	HexToStr(pKey, 6, (unsigned char*)Key);
	char Buf[255] = {0};
	char ppBuf[0x4000] = {0};
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	int re = -1;
	
	if(iCardType == 0)//是CPU卡
	{
		///////////////////////////上电以及认证
		char ATR[50]={0};
		int ret=PowerOn(hDev ,0x01,ATR);//用户卡上电
		if(ret)
		{
			return WS_ERR_NORESPONSE_CPU;
		}
		ret=PowerOn(hDev ,0x11,ATR);//psam卡上电
		if(ret)
		{
			return WS_ERR_NORESPONSE_SAM;
		}
		ret=iVerifyPIN(hDev,"123456");
		if(ret)
		{
			return WS_ERR_PINERR;
		}
		//::MessageBox(NULL,"open_s",NULL,MB_OK);
		////////////////////////////
		if(strcmp((const char *)pKey,"EF07")==0)//读照片的二进制数据
		{
			unsigned char bysZHAOPIAN[3074] = {0};
			re = iR_DDF1EF07Info(hDev,bysZHAOPIAN);
			if(re)
			{
				return WS_ERR_OTHER;
			}
			memcpy(pBuf,bysZHAOPIAN+iOffsetInBytes,iSizeInBytes);
		}
		else if(strcmp((const char *)pKey,"EE01")==0)//读门诊信息
		{
			re=iR_DF03EEInfo(hDev,1,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"EE02")==0)
		{
			re=iR_DF03EEInfo(hDev,2,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"EE03")==0)
		{
			re=iR_DF03EEInfo(hDev,3,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED01")==0)
		{
			re=iR_DF03EDInfo(hDev,1,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED02")==0)
		{
			re=iR_DF03EDInfo(hDev,2,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED03")==0)
		{
			re=iR_DF03EDInfo(hDev,3,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED04")==0)
		{
			re=iR_DF03EDInfo(hDev,4,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED05")==0)
		{
			re=iR_DF03EDInfo(hDev,5,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else
		{
			return WS_ERR_OTHER;
		}
		return WS_OK;
	}
	else if(iCardType == 1)
	{
		return WS_ERR_UNSUPPORTED;
	}
	else if(iCardType == 2)
	{
		int block, secnr;
		double addrstart, addrcount;
		int addrtemp1, addrtemp2, addrtemp3, addrtemp4;

		block = (iOffsetInBytes/8)/16;
		secnr = block/4;
		addrstart = (((iOffsetInBytes/8.0)/16.0) - block)*8.0*4.0;
		addrcount = iSizeInBytes/4.0;
		addrtemp1 = 32-addrstart;
		addrtemp2 = addrcount-addrtemp1;
		addrtemp3 = addrtemp2/32;
		addrtemp4 = addrtemp2%32;

		if(addrtemp3 > 63)
		{
			return WS_ERR_ROffSET;
		}
		unsigned char Rdata[256] = {0};

		if(addrtemp2 <= 0)
		{
			re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, secnr, pKey);
			if(re != 0)
			{
				::MessageBox(NULL,"密码错误!",NULL,MB_OK);
				return WS_ERR_OTHER;
			}

			re = PICC_Reader_Read(DevHandle, block, Rdata);
			if(re != 0)
			{
				return WS_ERR_IC;
			}

			if(iSizeInBytes%8 != 0)
			{
				memset(Buf, 0, 255);
				HexToStr(Rdata, 16, (unsigned char*)Buf);
				memcpy(ppBuf, Buf+(int)addrstart, (int)addrcount);
				StrToHex((unsigned char*)ppBuf, ((iSizeInBytes/8.0)*2+1), (unsigned char*)pBuf);
			}
			else
			{
				memset(Buf, 0, 255);
				HexToStr(Rdata, 16, (unsigned char*)Buf);
				memcpy(ppBuf, Buf+(int)addrstart, (int)addrcount);
				
				StrToHex((unsigned char*)ppBuf, (int)addrcount, (unsigned char*)pBuf);
			}

		}
		else
		{
			re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, secnr, pKey);
			if(re != 0)
			{
				return WS_ERR_OTHER;
			}
			
			re = PICC_Reader_Read(DevHandle, block, Rdata);
			if(re != 0)
			{
				return WS_ERR_IC;
			}
			memset(Buf, 0, 255);
			HexToStr(Rdata, 16, (unsigned char*)Buf);
			memcpy(ppBuf, Buf+(int)addrstart, (int)addrtemp1);
			
			for(int i = 0; i < addrtemp3; i++)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, (block+1+i)/4, pKey);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}

				re = PICC_Reader_Read(DevHandle, block+1+i, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				memset(Buf, 0, 255);
				HexToStr(Rdata, 16, (unsigned char*)Buf);
				memcpy(ppBuf+addrtemp1+i*32, Buf, 32);
				
			}
			if(addrtemp4 != 0)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, (block+addrtemp3+1)/4, pKey);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}
				
				re = PICC_Reader_Read(DevHandle, block+addrtemp3+1, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				memset(Buf, 0, 255);
				HexToStr(Rdata, 16, (unsigned char*)Buf);
				memcpy(ppBuf+addrtemp1+addrtemp3*32, Buf, (int)addrtemp4);
			}
			//memcpy(pBuf, ppppBuf, (int)addrtemp1/2+(addrtemp3)*16+(int)addrtemp4/2);
			if(iSizeInBytes%8 != 0)
			{
				StrToHex((unsigned char*)ppBuf, ((iSizeInBytes/8.0)*2+1), (unsigned char*)pBuf);
			}
			else
			{
				StrToHex((unsigned char*)ppBuf, (int)addrcount, (unsigned char*)pBuf);
			}
		}
	}
	else
	{
		return WS_ERR_CARDTYPE;
	}
	return WS_OK;
}

BHGX_HD_API int __stdcall iWriteBin( unsigned char iCardType, unsigned char *pKey, const unsigned char *pBuf, int nCtrlword, int iSizeInBytes, int iOffsetInBytes )
{
	//////////////////////////
	HANDLE hDev=NULL;
	char Key[16] = {0};
	HexToStr(pKey, 6, (unsigned char*)Key);
	unsigned char Rdata[256] = {0};
	unsigned char Wdata[256] = {0};
	char Buf[0x1000] = {0};
	char RBuf[0x1000] = {0};
	char ppBuf[0x1000] = {0};
	//strcpy(Buf, (char*)pBuf);
	
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	int re = -1;
	
	if(iCardType == 0)//CPU卡
	{
		///////////////////////////上电以及认证
		char ATR[50]={0};
		int ret=PowerOn(hDev ,0x01,ATR);//用户卡上电
		if(ret)
		{
			return WS_ERR_NORESPONSE_CPU;
		}
		ret=PowerOn(hDev ,0x11,ATR);//psam卡上电
		if(ret)
		{
			return WS_ERR_NORESPONSE_SAM;
		}
		ret=iVerifyPIN(hDev,"123456");
		if(ret)
		{
			return WS_ERR_PINERR;
		}
		//::MessageBox(NULL,"open_s",NULL,MB_OK);
		////////////////////////////
		if(strcmp((const char *)pKey,"EF07")==0)
		{
			unsigned char bysZHAOPIAN[3074] = {0};
			re = iW_DDF1EF07Info(hDev,(unsigned char *)pBuf);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"EE01")==0)
		{
			re=iW_DF03EEInfo(hDev,1,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"EE02")==0)
		{
			re=iW_DF03EEInfo(hDev,2,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"EE03")==0)
		{
			re=iW_DF03EEInfo(hDev,3,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED01")==0)
		{
			re=iW_DF03EDInfo(hDev,1,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED02")==0)
		{
			re=iW_DF03EDInfo(hDev,2,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED03")==0)
		{
			re=iW_DF03EDInfo(hDev,3,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED04")==0)
		{
			re=iW_DF03EDInfo(hDev,4,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else if(strcmp((const char *)pKey,"ED05")==0)
		{
			re=iW_DF03EDInfo(hDev,5,(char *)pBuf,iOffsetInBytes,iSizeInBytes,AN_style);
			if(re)
			{
				return WS_ERR_OTHER;
			}
		}
		else
		{
			return WS_ERR_OTHER;
		}
		return WS_OK;
	}
	else if(iCardType == 1)
	{
		return WS_ERR_UNSUPPORTED;
	}
	else if(iCardType == 2)
	{
		if(iSizeInBytes%4 != 0)
		{
			return WS_ERR_RLength;
		}

		if(iSizeInBytes%8 != 0)
		{
			HexToStr((unsigned char*)pBuf, ((iSizeInBytes/8.0)*2+1)/2, (unsigned char*)Buf);
			HexToStr((unsigned char*)pBuf, ((iSizeInBytes/8.0)*2+1)/2, (unsigned char*)ppBuf);
		}
		else
		{
			HexToStr((unsigned char*)pBuf, iSizeInBytes/8, (unsigned char*)Buf);
			HexToStr((unsigned char*)pBuf, iSizeInBytes/8, (unsigned char*)ppBuf);
			
			if(strlen((char*)Buf) != (iSizeInBytes/4))
			{
				return WS_ERR_RLength;
			}
		}
		
		int addrindex, block, secnr;
		double addrstart, addrcount;
		int addrtemp1, addrtemp2, addrtemp3, addrtemp4;

		block = (iOffsetInBytes/8)/16;
		secnr = block/4;
		addrstart = (((iOffsetInBytes/8.0)/16.0) - block)*8.0*4.0;
		addrcount = iSizeInBytes/4.0;
		addrtemp1 = 32-addrstart;
		addrtemp2 = addrcount-addrtemp1;
		addrtemp3 = addrtemp2/32;
		addrtemp4 = addrtemp2%32;

		if(addrtemp3 > 63)
		{
			return WS_ERR_ROffSET;
		}

		if(addrtemp2 <= 0)
		{
			if(nCtrlword == 0)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x61, secnr, pKey);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}
			}
			else if(nCtrlword == 1)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, secnr, pKey);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}
			}
			else
			{
				return WS_ERR_DataStyleCheckErr;
			}

			re = PICC_Reader_Read(DevHandle, block, Rdata);
			if(re != 0)
			{
				return WS_ERR_IC;
			}
			HexToStr(Rdata, 16, (unsigned char*)RBuf);
			memcpy(RBuf+(int)addrstart, Buf, (int)addrcount);

			re = PICC_Reader_WriteHEX(DevHandle, block, (unsigned char*)RBuf);
			if(re != 0)
			{
				return WS_ERR_IC;
			}
		}
		else
		{
			if(nCtrlword == 0)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x61, secnr, pKey);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}
			}
			else if(nCtrlword == 1)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, secnr, pKey);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}
			}
			else
			{
				return WS_ERR_DataStyleCheckErr;
			}
			
			re = PICC_Reader_Read(DevHandle, block, Rdata);
			if(re != 0)
			{
				return WS_ERR_IC;
			}
			HexToStr(Rdata, 16, (unsigned char*)RBuf);	
			memcpy(RBuf+(int)addrstart, Buf, addrtemp1);
		
			re = PICC_Reader_WriteHEX(DevHandle, block, (unsigned char*)RBuf);
			if(re != 0)
			{
				return WS_ERR_IC;
			}
			
			for(int i = 0; i < addrtemp3; i++)
			{
				if(nCtrlword == 0)
				{
					re = PICC_Reader_Authentication_Pass(DevHandle, 0x61, (block+1+i)/4, pKey);
					if(re != 0)
					{
						return WS_ERR_OTHER;
					}
				}
				else if(nCtrlword == 1)
				{
					re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, (block+1+i)/4, pKey);
					if(re != 0)
					{
						return WS_ERR_OTHER;
					}
				}
				else
				{
					return WS_ERR_DataStyleCheckErr;
				}

				re = PICC_Reader_Read(DevHandle, block+1+i, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				HexToStr(Rdata, 16, (unsigned char*)RBuf);	
				memcpy(RBuf, Buf+addrtemp1+i*32, 32);
							
				re = PICC_Reader_WriteHEX(DevHandle, block+1+i, (unsigned char*)RBuf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
			}
			if(addrtemp4 != 0)
			{
				if(nCtrlword == 0)
				{
					re = PICC_Reader_Authentication_Pass(DevHandle, 0x61, (block+1+addrtemp3)/4, pKey);
					if(re != 0)
					{
						return WS_ERR_OTHER;
					}
				}
				else if(nCtrlword == 1)
				{
					re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, (block+1+addrtemp3)/4, pKey);
					if(re != 0)
					{
						return WS_ERR_OTHER;
					}
				}
				else
				{
					return WS_ERR_DataStyleCheckErr;
				}
				
				re = PICC_Reader_Read(DevHandle, block+1+addrtemp3, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				HexToStr(Rdata, 16, (unsigned char*)RBuf);	
				memcpy(RBuf, Buf+addrtemp1+addrtemp3*32, (int)addrtemp4);
				
				re = PICC_Reader_WriteHEX(DevHandle, block+1+addrtemp3, (unsigned char*)RBuf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
								
			}
		}
	}
	else
	{
		return WS_ERR_CARDTYPE;
	}
	return WS_OK;
}

BHGX_HD_API int __stdcall iReadRec( unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, unsigned long buflen, int iRecNo, int iRecCount )
{
//	::MessageBox(NULL,g_DF,NULL,MB_OK);
//	char Message[500]={0};
//	sprintf(Message,"(iReadRec)卡类型:%d\r\n文件名:%s\r\n缓存长度:%d\r\n记录号:%d\r\n记录条数:%d",iCardType,pKey,buflen,iRecNo,iRecCount);
//	::MessageBox(NULL,Message,NULL,MB_OK);
	///////////////////////////
	if(buflen==0)
	{
		return WS_ERR_RLength;
	}
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}
	///////////////////////////上电以及认证
	HANDLE hDev=NULL;
	char ATR[50]={0};
	int ret=PowerOn(hDev ,0x01,ATR);//用户卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_CPU;
	}
	ret=PowerOn(hDev ,0x11,ATR);//psam卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_SAM;
	}
	ret=iVerifyPIN(hDev,"123456");
	if(ret)
	{
		return WS_ERR_PINERR;
	}
	//::MessageBox(NULL,"open_s",NULL,MB_OK);
	////////////////////////////
	unsigned char Buf[1000]={0};
	unsigned char CoverBuf[500]={0};
	int re=-1;
	if((strcmp((const char *)pKey,"EF05")==0) && (strcmp((const char *)g_DF,"DDF1")==0))
	{
		if(iRecCount>10)
			return WS_ERR_DataItemsErr;
		//264  //284
		char KLB[100]={0};
		KLB[0]=1;KLB[1]=1;
		char GFBB[100]={0};
		GFBB[0]=2;GFBB[1]=4;
		char FKJGMC[100]={0};
		FKJGMC[0]=3;FKJGMC[1]=30;
		char FKJGDM[100]={0};
		FKJGDM[0]=4;FKJGDM[1]=11;
		char FKJGZS[500]={0};
		FKJGZS[0]=5;FKJGZS[1]=180;
		char FKSJ[100]={0};
		FKSJ[0]=6;FKSJ[1]=4;
		char KH[100]={0};
		KH[0]=9;KH[1]=18;
		char AQM[100]={0}; 
		AQM[0]=9;AQM[1]=3;
		char XPXLH[100]={0}; 
		XPXLH[0]=10;XPXLH[1]=10;
		char YYCSDM[100]={0};
		YYCSDM[0]=57;YYCSDM[1]=3;
		re=iR_DDF1EF05Info(hDev,KLB+2,GFBB+2, FKJGMC+2, FKJGDM+2, FKJGZS+2, FKSJ+2, KH+2, AQM+2, XPXLH+2, YYCSDM+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		memcpy(Buf,KLB,3); 
		memcpy(Buf+3,GFBB,6);
		memcpy(Buf+9,FKJGMC,32);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)FKJGDM+2,strlen(FKJGDM+2),CoverBuf);//11
		memcpy(Buf+41,FKJGDM,2);
		memcpy(Buf+43,CoverBuf,11);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)FKJGZS+2,strlen(FKJGZS+2),CoverBuf);//180
		memcpy(Buf+54,FKJGZS,2);
		memcpy(Buf+56,CoverBuf,180);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)FKSJ+2,strlen(FKSJ+2),CoverBuf); //4
		memcpy(Buf+236,FKSJ,2);
		memcpy(Buf+238,CoverBuf,4);

		memcpy(Buf+242,KH,20);
		memcpy(Buf+262,AQM,5);
		memcpy(Buf+267,XPXLH,12);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)YYCSDM+2,strlen(YYCSDM+2),CoverBuf); //3
		memcpy(Buf+279,FKSJ,2);
		memcpy(Buf+281,CoverBuf,3);
	}
	else if((strcmp((const char *)pKey,"EF06")==0) && (strcmp((const char *)g_DF,"DDF1")==0))
	{
		if(iRecCount>5)
		{
			return WS_ERR_DataItemsErr;
		}
		//54   64
		char XM[50]={0};             //姓名
		XM[0]=11;XM[1]=30;
		char XB[50]={0};               //性别代码
		XB[0]=12;XB[1]=1;
		char MZ[50]={0};               //民族代码
		MZ[0]=13;MZ[1]=1;
		char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
		CSRQ[0]=14;CSRQ[1]=4;
		char SFZH[50]={0};            //居民身份证号
		SFZH[0]=15;SFZH[1]=18;
		re=iR_DDF1EF06Info(hDev,XM+2,XB+2,MZ+2,CSRQ+2,SFZH+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}

		memcpy(Buf,XM,32); 
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)XB+2,strlen(XB+2),CoverBuf);//1
		memcpy(Buf+32,XB,2);
		memcpy(Buf+34,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)MZ+2,strlen(MZ+2),CoverBuf);//1
		memcpy(Buf+35,MZ,2);
		memcpy(Buf+37,CoverBuf,1);
		StrToHex((unsigned char *)CSRQ+2,strlen(CSRQ+2),Buf+32);//4
		memcpy(Buf+38,CSRQ,2);
		memcpy(Buf+40,CoverBuf,4);
		memcpy(Buf+44,SFZH,20); 	
	}
	else if((strcmp((const char *)pKey,"EF08")==0) && (strcmp((const char *)g_DF,"DDF1")==0))
	{
		if(iRecCount>6)
			return WS_ERR_DataItemsErr;
		//47 59
		char KYXQ[21]={0};			//卡有效期
		KYXQ[0]=7;KYXQ[1]=4;
		char BRDH1[41]={0};         //本人电话1
		BRDH1[0]=16;BRDH1[1]=20;
		char BRDH2[41]={0};           //本人电话2
		BRDH2[0]=17;BRDH2[1]=20;
		char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
		YLFYZFFS1[0]=18;YLFYZFFS1[1]=1;
		char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
		YLFYZFFS2[0]=19;YLFYZFFS2[1]=1;
		char YLFYZFFS3[21]={0};	
		YLFYZFFS3[0]=20;YLFYZFFS3[1]=1;
		re=iR_DDF1EF08Info(hDev,KYXQ+2,BRDH1+2,BRDH2+2,YLFYZFFS1+2,YLFYZFFS2+2,YLFYZFFS3+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)KYXQ+2,strlen(KYXQ+2),CoverBuf);//4
		memcpy(Buf,KYXQ,2);
		memcpy(Buf+2,CoverBuf,4);

		memcpy(Buf+6,BRDH1,22);
		memcpy(Buf+28,BRDH1,22);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)YLFYZFFS1+2,strlen(YLFYZFFS1+2),CoverBuf);//1
		memcpy(Buf+50,YLFYZFFS1,2);
		memcpy(Buf+52,CoverBuf,1);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)YLFYZFFS2+2,strlen(YLFYZFFS2+2),CoverBuf);//1
		memcpy(Buf+53,YLFYZFFS2,2);
		memcpy(Buf+55,CoverBuf,1);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)YLFYZFFS3+2,strlen(YLFYZFFS3+2),CoverBuf);//1
		memcpy(Buf+56,YLFYZFFS3,2);
		memcpy(Buf+58,CoverBuf,1);
	}
	else if((strcmp((const char *)pKey,"EF05")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		//::MessageBox(NULL,"DF01/DF05",NULL,MB_OK);
		if(iRecCount>4)
			return WS_ERR_DataItemsErr;
		// 202   210
		char DZLB1[21]={0};	
		DZLB1[0]=21;DZLB1[1]=1;
		char DZ1[120]={0};    
		DZ1[0]=22;DZ1[1]=100;
		char DZLB2[21]={0};   
		DZLB2[0]=23;DZLB2[1]=1;
		char DZ2[120]={0};	
		DZ2[0]=24;DZ2[1]=100;
		re=iR_DF01EF05Info(hDev,DZLB1+2,DZ1+2,DZLB2+2,DZ2+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		//::MessageBox(NULL,DZLB1+2,NULL,MB_OK);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)DZLB1+2,strlen(DZLB1+2),CoverBuf);//1
		memcpy(Buf,DZLB1,2);
		memcpy(Buf+2,CoverBuf,1);

		memcpy(Buf+3,DZ1,102);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)DZLB2+2,strlen(DZLB2+2),CoverBuf);//1
		memcpy(Buf+105,DZLB2,2);
		memcpy(Buf+107,CoverBuf,1);

		memcpy(Buf+108,DZ2,102);
	}
	else if((strcmp((const char *)pKey,"EF06")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		if(iRecCount>9)
			return WS_ERR_DataItemsErr;
		// 153      171
		char LXRXM1[40]={0};	
		LXRXM1[0]=25;LXRXM1[1]=30;
		char LXRGX1[40]={0};  
		LXRGX1[0]=26;LXRGX1[1]=1;
		char LXRDH1[40]={0};
		LXRDH1[0]=27;LXRDH1[1]=20;
		char LXRXM2[40]={0};	
		LXRXM2[0]=28;LXRXM2[1]=30;
		char LXRGX2[40]={0};  
		LXRGX2[0]=29;LXRGX2[1]=1;
		char LXRDH2[40]={0}; 
		LXRDH2[0]=30;LXRDH2[1]=20;
		char LXRXM3[40]={0};
		LXRXM3[0]=31;LXRXM3[1]=30;
		char LXRGX3[40]={0};    
		LXRGX3[0]=32;LXRGX3[1]=1;
		char LXRDH3[40]={0}; 
		LXRDH3[0]=33;LXRDH3[1]=20;
		re=iR_DF01EF06Info(hDev,LXRXM1+2,LXRGX1+2,LXRDH1+2,LXRXM2+2,LXRGX2+2,LXRDH2+2,LXRXM3+2,LXRGX3+2,LXRDH3+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		memcpy(Buf,LXRXM1,32);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)LXRGX1+2,strlen(LXRGX1+2),CoverBuf);//1
		memcpy(Buf+32,LXRGX1,2);
		memcpy(Buf+34,CoverBuf,1);

		memcpy(Buf+35,LXRDH1,22);
		memcpy(Buf+57,LXRXM2,32);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)LXRGX2+2,strlen(LXRGX2+2),CoverBuf);//1
		memcpy(Buf+89,LXRGX2,2);
		memcpy(Buf+91,CoverBuf,1);

		memcpy(Buf+92,LXRDH1,22);
		memcpy(Buf+114,LXRXM3,32);

		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)LXRGX3+2,strlen(LXRGX3+2),CoverBuf);//1
		memcpy(Buf+146,LXRGX3,2);
		memcpy(Buf+148,CoverBuf,1);

		memcpy(Buf+149,LXRDH1,22);
	}
	else if((strcmp((const char *)pKey,"EF07")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		if(iRecCount>3)
			return WS_ERR_DataItemsErr;
		char WHCD[10]={0};
		WHCD[0]=34;WHCD[1]=1;
		char HYZK[10]={0};   
		HYZK[0]=35;HYZK[1]=1;
		char ZY[10]={0};	
		ZY[0]=36;ZY[1]=3;
		re=iR_DF01EF07Info(hDev,WHCD+2,HYZK+2,ZY+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)WHCD+2,strlen(WHCD+2),CoverBuf);//1
		memcpy(Buf,WHCD,2);
		memcpy(Buf+2,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)HYZK+2,strlen(HYZK+2),CoverBuf);//1
		memcpy(Buf+3,HYZK,2);
		memcpy(Buf+5,CoverBuf,1);

		memcpy(Buf+6,ZY,5);
	}
	else if((strcmp((const char *)pKey,"EF08")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		if(iRecCount>4)
			return WS_ERR_DataItemsErr;
		//       62
		char ZJLB[20]={0};	
		ZJLB[0]=37;ZJLB[1]=1;
		char ZJHM[20]={0};  
		ZJHM[0]=38;ZJHM[1]=18;
		char JKDAH[20]={0};
		JKDAH[0]=39;JKDAH[1]=17;
		char XNHZH[20]={0};
		XNHZH[0]=40;XNHZH[1]=18;
		re=iR_DF01EF08Info(hDev,ZJLB+2,ZJHM+2,JKDAH+2,XNHZH+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)ZJLB+2,strlen(ZJLB+2),CoverBuf);//1
		memcpy(Buf,ZJLB,2);
		memcpy(Buf+2,CoverBuf,1);

		memcpy(Buf+3,ZJHM,20);
		memcpy(Buf+23,JKDAH,19);
		memcpy(Buf+42,XNHZH,20);
	}
	else if((strcmp((const char *)pKey,"EF05")==0) && (strcmp((const char *)g_DF,"DF02")==0))
	{
		if(iRecCount>15)
			return WS_ERR_DataItemsErr;
		//         84
		char ABOXX[10]={0};	
		ABOXX[0]=41;ABOXX[1]=1;
		char RHXX[10]={0};   
		RHXX[0]=42;RHXX[1]=1;
		char XCBZ[10]={0};
		XCBZ[0]=43;XCBZ[1]=1;
		char XZBBZ[10]={0};
		XZBBZ[0]=44;XZBBZ[1]=1;
		char XNXGBBZ[10]={0};         //心脑血管病标志
		XNXGBBZ[0]=45;XNXGBBZ[1]=1;
		char DXBBZ[10]={0};           //癫痫病标志
		DXBBZ[0]=46;DXBBZ[1]=1;
		char NXWLBZ[10]={0};          //凝血紊乱标志
		NXWLBZ[0]=47;NXWLBZ[1]=1;
		char TNBBZ[10]={0};           //糖尿病标志
		TNBBZ[0]=48;TNBBZ[1]=1;
		char QGYBZ[10]={0};           //青光眼标志
		QGYBZ[0]=49;QGYBZ[1]=1;
		char TXBZ[10]={0};          //透析标志
		TXBZ[0]=50;TXBZ[1]=1;
		char QGYZBZ[10]={0};          //器官移植标志
		QGYZBZ[0]=51;QGYZBZ[1]=1;
		char QGQSBZ[10]={0};        //器官缺失标志
		QGQSBZ[0]=52;QGQSBZ[1]=1;
		char KZXYZBZ[10]={0};         //可装卸义肢标志
		KZXYZBZ[0]=53;KZXYZBZ[1]=1;
		char XZQBQBZ[10]={0};        //心脏起搏器标志
		XZQBQBZ[0]=54;XZQBQBZ[1]=1;
		char QTYXJSMC[50]={0};
		QTYXJSMC[0]=55;QTYXJSMC[1]=40;
		re=iR_DF02EF05Info(hDev,ABOXX+2,RHXX+2,XCBZ+2,XZBBZ+2,XNXGBBZ+2,DXBBZ+2,NXWLBZ+2,TNBBZ+2,QGYBZ+2,TXBZ+2,QGYZBZ+2,QGQSBZ+2,KZXYZBZ+2,XZQBQBZ+2,QTYXJSMC+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)ABOXX+2,strlen(ABOXX+2),CoverBuf);//1
		memcpy(Buf,ABOXX,2);
		memcpy(Buf+2,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)RHXX+2,strlen(RHXX+2),CoverBuf);//1
		memcpy(Buf+3,RHXX,2);
		memcpy(Buf+5,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)XCBZ+2,strlen(XCBZ+2),CoverBuf);//1
		memcpy(Buf+6,XCBZ,2);
		memcpy(Buf+8,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)XZBBZ+2,strlen(XZBBZ+2),CoverBuf);//1
		memcpy(Buf+9,XZBBZ,2);
		memcpy(Buf+11,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)XNXGBBZ+2,strlen(XNXGBBZ+2),CoverBuf);//1
		memcpy(Buf+12,XNXGBBZ,2);
		memcpy(Buf+14,CoverBuf,1);
		StrToHex((unsigned char *)DXBBZ+2,strlen(DXBBZ+2),CoverBuf);//1
		memcpy(Buf+15,DXBBZ,2);
		memcpy(Buf+17,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)NXWLBZ+2,strlen(NXWLBZ+2),CoverBuf);//1
		memcpy(Buf+18,NXWLBZ,2);
		memcpy(Buf+20,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)TNBBZ+2,strlen(TNBBZ+2),CoverBuf);//1
		memcpy(Buf+21,TNBBZ,2);
		memcpy(Buf+23,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)QGYBZ+2,strlen(QGYBZ+2),CoverBuf);//1
		memcpy(Buf+24,QGYBZ,2);
		memcpy(Buf+26,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)TXBZ+2,strlen(TXBZ+2),CoverBuf);//1
		memcpy(Buf+27,TXBZ,2);
		memcpy(Buf+29,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)QGYZBZ+2,strlen(QGYZBZ+2),CoverBuf);//1
		memcpy(Buf+30,QGYZBZ,2);
		memcpy(Buf+32,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)QGQSBZ+2,strlen(QGQSBZ+2),CoverBuf);//1
		memcpy(Buf+33,QGQSBZ,2);
		memcpy(Buf+35,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)KZXYZBZ+2,strlen(KZXYZBZ+2),CoverBuf);//1
		memcpy(Buf+36,KZXYZBZ,2);
		memcpy(Buf+38,CoverBuf,1);
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)XZQBQBZ+2,strlen(XZQBQBZ+2),CoverBuf);//1
		memcpy(Buf+39,XZQBQBZ,2);
		memcpy(Buf+41,CoverBuf,1);
		memcpy(Buf+42,QTYXJSMC,42);
	}
	else if((strcmp((const char *)pKey,"EF06")==0) && (strcmp((const char *)g_DF,"DF02")==0))
	{
		if(iRecCount>1)
			return WS_ERR_DataItemsErr;
		char JSBBZ[10]={0};	
		JSBBZ[0]=56;JSBBZ[1]=1;
		re=iR_DF02EF06Info(hDev,JSBBZ+2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
		memset(CoverBuf,0,500);
		StrToHex((unsigned char *)JSBBZ+2,strlen(JSBBZ+2),CoverBuf);//1
		memcpy(Buf,JSBBZ,2);
		memcpy(Buf+2,CoverBuf,1);
	}
	else
	{
		return WS_ERR_OTHER;
	}
	memcpy(pBuf,Buf,buflen);
	return 0;
}

BHGX_HD_API int __stdcall iWriteRec( unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, unsigned long buflen, int iRecNo, int iRecCount )
{
	char Message[500]={0};
	sprintf(Message,"(iWriteRec)卡类型:%d\r\n文件名:%s\r\n缓存长度:%d\r\n记录号:%d\r\n记录条数:%d",iCardType,pKey,buflen,iRecNo,iRecCount);
	::MessageBox(NULL,Message,NULL,MB_OK);
	unsigned char Message2[500]={0};
	HexToStr(pBuf,buflen,Message2);
	::MessageBox(NULL,(const char *)Message2,NULL,MB_OK);
	if(buflen==0)
	{
		return WS_ERR_RLength;
	}
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}
	HANDLE hDev=NULL;
	///////////////////////////上电以及认证
	char ATR[50]={0};
	int ret=PowerOn(hDev ,0x01,ATR);//用户卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_CPU;
	}
	ret=PowerOn(hDev ,0x11,ATR);//psam卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_SAM;
	}
	ret=iVerifyPIN(hDev,"123456");
	if(ret)
	{
		return WS_ERR_PINERR;
	}
	//::MessageBox(NULL,"open_s",NULL,MB_OK);
	////////////////////////////
	unsigned char Buf[1000]={0};
	unsigned char CoverBuf[500]={0};
	int re=-1;
	if((strcmp((const char *)pKey,"EF05")==0) && (strcmp((const char *)g_DF,"DDF1")==0))
	{
		if(iRecCount>10)
			return WS_ERR_DataItemsErr;
		//264  //284
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
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					memcpy(KLB,pBuf+2,1);
				}
				break;
			case 1:
				{
					memcpy(GFBB,pBuf+5,4);
				}
				break;
			case 2:
				{
					memcpy(FKJGMC,pBuf+11,30);
				}
				break;
			case 3:
				{
					HexToStr(pBuf+43,11,CoverBuf);
					memcpy(FKJGDM,CoverBuf,22);
				}
				break;
			case 4:
				{
					HexToStr(pBuf+56,180,CoverBuf);
					memcpy(FKJGZS,CoverBuf,360);
				}
				break;
			case 5:
				{
					HexToStr(pBuf+238,4,CoverBuf);
					memcpy(FKSJ,CoverBuf,8);
				}
				break;
			case 6:
				{
					memcpy(KH,pBuf+244,18);
				}
				break;
			case 7:
				{
					memcpy(AQM,pBuf+264,3);
				}
				break;
			case 8:
				{
					memcpy(XPXLH,pBuf+269,10);
				}
				break;
			case 9:
				{
					HexToStr(pBuf+281,3,CoverBuf);
					memcpy(YYCSDM,CoverBuf,6);
				}
				break;
			}
		}//end for
		re=iW_DDF1EF05Info(hDev,KLB,GFBB,FKJGMC,FKJGDM,FKJGZS,FKSJ,KH,AQM,XPXLH,YYCSDM);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)pKey,"EF06")==0) && (strcmp((const char *)g_DF,"DDF1")==0))
	{
		if(iRecCount>5)
			return WS_ERR_DataItemsErr;
		//54   64
		char XM[50]={0};             //姓名
		char XB[50]={0};               //性别代码
		char MZ[50]={0};               //民族代码
		char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
		char SFZH[50]={0};            //居民身份证号
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					memcpy(XM,pBuf+2,30);
				}
				break;
			case 1:
				{
					HexToStr(pBuf+34,1,CoverBuf);
					memcpy(XB,CoverBuf,2);
				}
				break;
			case 2:
				{
					HexToStr(pBuf+37,1,CoverBuf);
					memcpy(MZ,CoverBuf,2);
				}
				break;
			case 3:
				{
					HexToStr(pBuf+40,4,CoverBuf);
					memcpy(CSRQ,CoverBuf,8);
				}
				break;
			case 4:
				{
					memcpy(SFZH,pBuf+46,18);
				}
				break;
			}
		}//end for
		re=iW_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
		if(re)
		{
			return WS_ERR_OTHER;
		}	
	}
	else if((strcmp((const char *)pKey,"EF08")==0) && (strcmp((const char *)g_DF,"DDF1")==0))
	{
		if(iRecCount>6)
			return WS_ERR_DataItemsErr;
		//47 59
		char KYXQ[21]={0};			//卡有效期
		char BRDH1[41]={0};         //本人电话1
		char BRDH2[41]={0};           //本人电话2
		char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
		char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
		char YLFYZFFS3[21]={0};	
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					HexToStr(pBuf+2,4,CoverBuf);
					memcpy(KYXQ,CoverBuf,8);
				}
				break;
			case 1:
				{
					memcpy(BRDH1,pBuf+8,20);
				}
				break;
			case 2:
				{
					memcpy(BRDH1,pBuf+30,20);
				}
				break;
			case 3:
				{
					HexToStr(pBuf+52,1,CoverBuf);
					memcpy(YLFYZFFS1,CoverBuf,2);
				}
				break;
			case 4:
				{
					HexToStr(pBuf+55,1,CoverBuf);
					memcpy(YLFYZFFS2,CoverBuf,2);
				}
			case 5:
				{
					HexToStr(pBuf+58,1,CoverBuf);
					memcpy(YLFYZFFS3,CoverBuf,2);
				}
				break;
			}
		}//end for
		re=iW_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)pKey,"EF05")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		if(iRecCount>4)
			return WS_ERR_DataItemsErr;
		// 202   210
		char DZLB1[21]={0};	
		char DZ1[120]={0};    
		char DZLB2[21]={0};   
		char DZ2[120]={0};	
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					HexToStr(pBuf+2,1,CoverBuf);
					memcpy(DZLB1,CoverBuf,2);
				}
				break;
			case 1:
				{
					memcpy(DZ1,pBuf+5,100);
				}
				break;
			case 2:
				{
					HexToStr(pBuf+107,1,CoverBuf);
					memcpy(DZLB2,CoverBuf,2);
				}
				break;
			case 3:
				{
					memcpy(DZ2,pBuf+110,100);
				}
				break;
			}
		}//end for
		re=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)pKey,"EF06")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		if(iRecCount>9)
			return WS_ERR_DataItemsErr;
		// 153      171
		char LXRXM1[40]={0};	
		char LXRGX1[40]={0};  
		char LXRDH1[40]={0};
		char LXRXM2[40]={0};	
		char LXRGX2[40]={0};  
		char LXRDH2[40]={0}; 
		char LXRXM3[40]={0};
		char LXRGX3[40]={0};    
		char LXRDH3[40]={0}; 
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					memcpy(LXRXM1,pBuf+2,30);
				}
				break;
			case 1:
				{
					HexToStr(pBuf+34,1,CoverBuf);
					memcpy(LXRGX1,CoverBuf,2);
				}
				break;
			case 2:
				{
					memcpy(LXRDH1,pBuf+37,20);
				}
				break;
			case 3:
				{
					memcpy(LXRXM2,pBuf+59,30);
				}
				break;
			case 4:
				{
					HexToStr(pBuf+91,1,CoverBuf);
					memcpy(LXRGX2,CoverBuf,2);
				}
			case 5:
				{
					memcpy(LXRDH2,pBuf+94,20);
				}
				break;
			case 6:
				{
					memcpy(LXRXM3,pBuf+116,30);
				}
				break;
			case 7:
				{
					HexToStr(pBuf+158,1,CoverBuf);
					memcpy(LXRGX3,CoverBuf,2);
				}
			case 8:
				{
					memcpy(LXRDH3,pBuf+151,20);
				}
				break;
			}
		}//end for
		re=iW_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)pKey,"EF07")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		if(iRecCount>3)
			return WS_ERR_DataItemsErr;
		//       11
		char WHCD[10]={0};
		char HYZK[10]={0};   
		char ZY[10]={0};	
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					HexToStr(pBuf+2,1,CoverBuf);
					memcpy(WHCD,CoverBuf,2);
				}
				break;
			case 1:
				{
					HexToStr(pBuf+5,1,CoverBuf);
					memcpy(HYZK,CoverBuf,2);
				}
				break;
			case 2:
				{
					memcpy(ZY,pBuf+8,3);
				}
				break;
			}
		}//end for
		re=iW_DF01EF07Info(hDev,WHCD,HYZK,ZY);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)pKey,"EF08")==0) && (strcmp((const char *)g_DF,"DF01")==0))
	{
		if(iRecCount>4)
			return WS_ERR_DataItemsErr;
		//       62
		char ZJLB[20]={0};	
		char ZJHM[20]={0};  
		char JKDAH[20]={0};
		char XNHZH[20]={0};
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					HexToStr(pBuf+2,1,CoverBuf);
					memcpy(ZJLB,CoverBuf,2);
				}
				break;
			case 1:
				{
					memcpy(ZJHM,pBuf+5,18);
				}
				break;
			case 2:
				{
					memcpy(JKDAH,pBuf+25,17);
				}
			case 3:
				{
					memcpy(XNHZH,pBuf+44,18);
				}
				break;
			}
		}//end for
		re=iW_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)pKey,"EF05")==0) && (strcmp((const char *)g_DF,"DF02")==0))
	{
		if(iRecCount>15)
			return WS_ERR_DataItemsErr;
		//         84
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
		for(int i=0;i<iRecCount;i++)
		{
			switch(i)
			{
			case 0:
				{
					HexToStr(pBuf+2,1,CoverBuf);
					memcpy(ABOXX,CoverBuf,2);
				}
				break;
			case 1:
				{
					HexToStr(pBuf+5,1,CoverBuf);
					memcpy(RHXX,CoverBuf,2);
				}
				break;
			case 2:
				{
					HexToStr(pBuf+8,1,CoverBuf);
					memcpy(XCBZ,CoverBuf,2);
				}
			case 3:
				{
					HexToStr(pBuf+11,1,CoverBuf);
					memcpy(XZBBZ,CoverBuf,2);
				}
			case 4:
				{
					HexToStr(pBuf+14,1,CoverBuf);
					memcpy(XNXGBBZ,CoverBuf,2);
				}
				break;
			case 5:
				{
					HexToStr(pBuf+17,1,CoverBuf);
					memcpy(DXBBZ,CoverBuf,2);
				}
				break;
			case 6:
				{
					HexToStr(pBuf+20,1,CoverBuf);
					memcpy(NXWLBZ,CoverBuf,2);
				}
				break;
			case 7:
				{
					HexToStr(pBuf+23,1,CoverBuf);
					memcpy(TNBBZ,CoverBuf,2);
				}
				break;
			case 8:
				{
					HexToStr(pBuf+26,1,CoverBuf);
					memcpy(QGYBZ,CoverBuf,2);
				}
				break;
			case 9:
				{
					HexToStr(pBuf+29,1,CoverBuf);
					memcpy(TXBZ,CoverBuf,2);
				}
				break;
			case 10:
				{
					HexToStr(pBuf+32,1,CoverBuf);
					memcpy(QGYZBZ,CoverBuf,2);
				}
				break;
			case 11:
				{
					HexToStr(pBuf+35,1,CoverBuf);
					memcpy(QGQSBZ,CoverBuf,2);
				}
				break;
			case 12:
				{
					HexToStr(pBuf+38,1,CoverBuf);
					memcpy(KZXYZBZ,CoverBuf,2);
				}
				break;
			case 13:
				{
					HexToStr(pBuf+41,1,CoverBuf);
					memcpy(XZQBQBZ,CoverBuf,2);
				}
				break;
			case 14:
				{
					memcpy(QTYXJSMC,pBuf+44,40);
				}
				break;
			}
		}//end for
		re=iW_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)pKey,"EF06")==0) && (strcmp((const char *)g_DF,"DF02")==0))
	{
		if(iRecCount>1)
			return WS_ERR_DataItemsErr;
		char JSBBZ[10]={0};	
		HexToStr(pBuf+2,1,CoverBuf);
		memcpy(JSBBZ,CoverBuf,2);
		re=iW_DF02EF06Info(hDev,JSBBZ);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else
	{
		return WS_ERR_OTHER;
	}
	return 0;
}

BHGX_HD_API int __stdcall iAppendRec( unsigned char *pKey, const unsigned char *pBuf, unsigned long buflen )
{
	char Message[500]={0};
	sprintf(Message,"(iAppendRec)文件名:%s\r\n缓存区长度:%d",pKey,buflen);
	::MessageBox(NULL,Message,NULL,MB_OK);
	////////////////////////////////////////////
	if(buflen==0)
	{
		return WS_ERR_RLength;
	}
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}
	HANDLE hDev=NULL;
	///////////////////////////上电以及认证
	char ATR[50]={0};
	int ret=PowerOn(hDev ,0x01,ATR);//用户卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_CPU;
	}
	ret=PowerOn(hDev ,0x11,ATR);//psam卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_SAM;
	}
	ret=iVerifyPIN(hDev,"123456");
	if(ret)
	{
		return WS_ERR_PINERR;
	}
	//::MessageBox(NULL,"open_s",NULL,MB_OK);
	////////////////////////////
	int re=-1;
	if((strcmp((const char *)g_DF,"DF02")==0) && (strcmp((const char *)pKey,"EF07")==0))
	{
		char GMWZMC[40]={0};
		char GMFY[200]={0};
		memcpy(GMWZMC,pBuf,20);
		memcpy(GMFY,pBuf+20,100);
		re=iW_DF02EF07Info(hDev,GMWZMC,GMFY);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)g_DF,"DF02")==0) && (strcmp((const char *)pKey,"EF08")==0))
	{
		char MYJZMC[40]={0};
		char MYJZSJ[200]={0};
		unsigned char temp[40]={0};
		memcpy(temp,pBuf,24);
		memcpy(MYJZMC,temp,20);
		HexToStr(temp+20,4,(unsigned char *)MYJZSJ);
		re=iW_DF02EF08Info(hDev,MYJZMC,MYJZSJ);
		if(re)
		{
			return WS_ERR_OTHER;
		}
	}
	else
	{
		return WS_ERR_OTHER;
	}
	return 0;
}

BHGX_HD_API int __stdcall iSignRec( unsigned char *pKey, int iRecNo, int sign )
{
	char Message[500]={0};
	sprintf(Message,"(iSignRec)文件名:%s\r\n记录号:%d\r\n标志:%d",pKey,iRecNo,sign);
	::MessageBox(NULL,Message,NULL,MB_OK);
	////////////////////////////////////////////
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}
	HANDLE hDev=NULL;
	///////////////////////////上电以及认证
	char ATR[50]={0};
	int ret=PowerOn(hDev ,0x01,ATR);//用户卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_CPU;
	}
	ret=PowerOn(hDev ,0x11,ATR);//psam卡上电
	if(ret)
	{
		return WS_ERR_NORESPONSE_SAM;
	}
	ret=iVerifyPIN(hDev,"123456");
	if(ret)
	{
		return WS_ERR_PINERR;
	}
	//::MessageBox(NULL,"open_s",NULL,MB_OK);
	////////////////////////////
	int re=-1;
	if((strcmp((const char *)g_DF,"DF03")==0) && (strcmp((const char *)pKey,"EF05")==0))
	{
		if(iRecNo>3)
		{
			return WS_ERR_DataItemsErr;
		}
		if(sign==1)
		{
			re=iW_DF03EF05Info(hDev,iRecNo);
			if(re)
				return WS_ERR_IC;
		}
		else if(sign==0)
		{
			re=iErase_DF03EF05Info(hDev,iRecNo);
			if(re)
				return WS_ERR_IC;
		}
		else
		{
			return WS_ERR_OTHER;
		}
	}
	else if((strcmp((const char *)g_DF,"DF03")==0) && (strcmp((const char *)pKey,"EF06")==0))
	{
		if(iRecNo>5)
		{
			return WS_ERR_DataItemsErr;
		}
		if(sign==1)
		{
			re=iW_DF03EF06Info(hDev,iRecNo);
			if(re)
				return WS_ERR_IC;
		}
		else if(sign==0)
		{
			re=iErase_DF03EF06Info(hDev,iRecNo);
			if(re)
				return WS_ERR_IC;
		}
		else
		{
			return WS_ERR_OTHER;
		}
	}
	else
	{
		return WS_ERR_OTHER;
	}
	return 0;
}

BHGX_HD_API int __stdcall iIOCtl( int cmd, void *data, int datasize )
{
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	int re = -1;
	if(cmd == 1)
	{
		re = ICC_PosBeep(DevHandle, 16);
		if(re != 0)
		{
			return WS_ERR_UNSUPPORTED;
		}
	}
	else
	{
		return WS_ERR_UNSUPPORTED;
	}
	return 0;
}

BHGX_HD_API int __stdcall ICCSet( unsigned int iCardSet, unsigned char *pCardType, unsigned char *pRet )
{
//	char Message[500]={0};
//	sprintf(Message,"(ICCSet)卡座:%d\r\n",iCardSet);
//	::MessageBox(NULL,Message,NULL,MB_OK);
	///////////////////////////
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	unsigned char cmd[256] = {0};
	unsigned char resp[1000] = {0};
	unsigned char uid[5] = {0};
	int re = -1;

	if(iCardSet == 0)
	{
		re = PICC_Reader_SetTypeA(DevHandle);
		if(re != 0)
		{
			return -38;
		}
		re = PICC_Reader_Request(DevHandle);
		if(re != 0)
		{
			return -38;
		}
		re = PICC_Reader_anticoll(DevHandle, uid);
		if(re != 0)
		{
			return -38;
		}
		
		re = PICC_Reader_Select(DevHandle, 0x41);
		if(re != 0)
		{
			return -38;
		}

		memset(resp,0,1000);
		re = PICC_Reader_PowerOnTypeA(DevHandle, resp);
		if(re < 0)
		{
			re = PICC_Reader_Request(DevHandle);
			if(re != 0)
			{
				return -38;
			}
			re = PICC_Reader_anticoll(DevHandle, uid);
			if(re != 0)
			{
				return -38;
			}
			
			re = PICC_Reader_Select(DevHandle, 0x41);
			if(re != 0)
			{
				return -38;
			}
			g_iCardType=2;
			//strcpy((char*)pCardType, "0");
			*pCardType=0;
			HexToStr(uid, 4, pRet);
			//::MessageBox(NULL,"M1",NULL,MB_OK);
			return 0;
		}
		g_iCardType=0;
		//strcpy((char*)pCardType, "1");
		*pCardType=1;
		HexToStr(resp, re, (unsigned char*)pRet);
		//::MessageBox(NULL,"CPU",NULL,MB_OK);
	}
	else if(iCardSet == 1)
	{
		memset(resp, 0, 1000);
		re = ICC_Reader_pre_PowerOn(DevHandle, 0x11, resp);
		if(re <=0)
		{
			return WS_ERR_RESET_SAM;
		}
		g_iCardType=1;
		//strcpy((char*)pCardType, "2");
		*pCardType=2;
		HexToStr(resp, re, pRet);
	}
	else
	{
		//卡座参数错误
		return WS_ERR_SETSLOTID;
	}
	return 0;
}

BHGX_HD_API int __stdcall iUCardAuthSys( int iKeyID )
{
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	return 0;
}

BHGX_HD_API int __stdcall iSelectFile( unsigned char iCardType, unsigned char *pInFID )
{
	char Message[500]={0};
	sprintf(Message,"(iSelectFile)卡类型:%d\r\n文件名:%s\r\n",iCardType,pInFID);
	::MessageBox(NULL,Message,NULL,MB_OK);
	/////////////////////////////
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}
	if(strcmp("DDF1",(const char *)pInFID)==0)
	{
		strcpy(g_DF,"DDF1");
	}
	else if(strcmp("DF01",(const char *)pInFID)==0)
	{
		strcpy(g_DF,"DF01");
	}
	else if(strcmp("DF02",(const char *)pInFID)==0)
	{
		strcpy(g_DF,"DF02");
	}
	else if(strcmp("DF03",(const char *)pInFID)==0)
	{
		strcpy(g_DF,"DF03");
	}
	return 0;
}

BHGX_HD_API int __stdcall iGetRandom( unsigned char iCardType, unsigned char iRndLen, unsigned char * pOutRnd )
{
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	if(iCardType != 0 && iCardType != 1)
	{
		return WS_ERR_UNSLOTID;
	}

	unsigned char cmd[256] = {0};
	unsigned char resp[1000] = {0};
	int re = -1;

	if(iCardType == 0)
	{
		memset(cmd, 0, 256);
		memset(resp,0,1000);
		memcpy(cmd, "\x00\x84\x00\x00\x08", 5); //0084000008
		cmd[4] = iRndLen;
		re = PICC_Reader_Application(DevHandle, 5, cmd, resp);
		if(re <= 0 || resp[re-2] != 0x90) 
		{
			return WS_ERR_IC;
		}
		HexToStr(resp, re, pOutRnd);
	}
	else if(iCardType == 1)
	{
		memset(cmd,0,200);
		memset(resp,0,1000);
		memcpy(cmd, "\x00\x84\x00\x00\x08", 5); //0084000008
		cmd[4] = iRndLen;
		re = ICC_Reader_Application(DevHandle, 0x11, 5, cmd, resp);
		if(re <= 0 || resp[re-2] != 0x90) 
		{
			return WS_ERR_IC;
		}
		HexToStr(resp, re, pOutRnd);
	}
	else
	{
		return WS_ERR_UNSLOTID;
	}
	return 0;
}

BHGX_HD_API int __stdcall iChangePwdEx( const unsigned char * pNewKeyA, const unsigned char * ctrlword, const unsigned char * pNewKeyB, const unsigned char * poldPin, unsigned char nsector, unsigned char keyA1B0, unsigned char changeflag )
{
	unsigned char KeyA[16] = {0};
	unsigned char pctrlword[16] = {0};
	unsigned char KeyB[16] = {0};
	unsigned char OldKey[16] = {0};
	HexToStr((unsigned char*)pNewKeyA, 6, KeyA);
	HexToStr((unsigned char*)ctrlword, 4, pctrlword);
	HexToStr((unsigned char*)pNewKeyB, 6, KeyB);
	HexToStr((unsigned char*)poldPin, 6, OldKey);

	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	int re = -1;
	unsigned char uid[5] = {0};
	unsigned char Rdata[256] = {0};
	unsigned char Wdata[256] = {0};
	unsigned char Tempdata[256] = {0};
	char Buf[36] = {0};

	re = PICC_Reader_SetTypeA(DevHandle);
	if(re != 0)
	{
		return -38;
	}
	
	re = PICC_Reader_Request(DevHandle);
	if(re != 0)
	{
		return -38;
	}
	
	re = PICC_Reader_anticoll(DevHandle, uid);
	if(re != 0)
	{
		return -38;
	}
	re = PICC_Reader_Select(DevHandle, 0x41);
	if(re != 0)
	{
		return -38;
	}

	switch(changeflag)
	{
	case 0://值为0表示只改A密码
		{
			if(keyA1B0 == 0)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x61, nsector, (unsigned char*)poldPin);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}

				memset(Rdata, 0, 256);
				memset(Wdata, 0, 256);
				memset(Tempdata, 0, 256);
				memset(Buf, 0, 36);

				re = PICC_Reader_Read(DevHandle, (nsector+1)*4-1, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}				
				//000000000000 ff078069 ffffffffffff
				//111111111111 ff078069 ffffffffffff
				memcpy(Rdata, pNewKeyA, 6);
				memcpy(Rdata+10, poldPin, 6);
				memcpy(Buf, Rdata, 16);
				HexToStr(Rdata, 16, Tempdata);
				re = PICC_Reader_Write(DevHandle, (nsector+1)*4-1, (unsigned char*)Buf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
			} 
			else
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, nsector, (unsigned char*)poldPin);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}

				memset(Rdata, 0, 256);
				memset(Wdata, 0, 256);
				memset(Tempdata, 0, 256);
				memset(Buf, 0, 36);
				
				re = PICC_Reader_Read(DevHandle, (nsector+1)*4-1, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}				
				//000000000000 ff078069 ffffffffffff
				//111111111111 ff078069 ffffffffffff
				memcpy(Rdata, pNewKeyA, 6);
				//memcpy(Rdata+12, poldPin, 6 );
				memcpy(Buf, Rdata, 16);
				HexToStr(Rdata, 16, Tempdata);
				re = PICC_Reader_Write(DevHandle, (nsector+1)*4-1, (unsigned char*)Buf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				
			}
		}
		break;
	case 2://值为2表示密码权限访问字不更改，只改A、B密码
		{
			if(keyA1B0 == 0)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x61, nsector, (unsigned char*)poldPin);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}

				memset(Rdata, 0, 256);
				memset(Wdata, 0, 256);
				memset(Tempdata, 0, 256);
				memset(Buf, 0, 36);

				re = PICC_Reader_Read(DevHandle, (nsector+1)*4-1, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}				
				//000000000000 ff078069 ffffffffffff
				//111111111111 ff078069 ffffffffffff
				memcpy(Rdata, pNewKeyA, 6);
				memcpy(Rdata+10, pNewKeyB, 6);
				memcpy(Buf, Rdata, 16);
				HexToStr(Rdata, 16, Tempdata);
				re = PICC_Reader_Write(DevHandle, (nsector+1)*4-1, (unsigned char*)Buf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				
			} 
			else
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, nsector, (unsigned char*)poldPin);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}

				memset(Rdata, 0, 256);
				memset(Wdata, 0, 256);
				memset(Tempdata, 0, 256);
				memset(Buf, 0, 36);
				
				re = PICC_Reader_Read(DevHandle, (nsector+1)*4-1, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}				
				//000000000000 ff078069 ffffffffffff
				//111111111111 ff078069 ffffffffffff
				memcpy(Rdata, pNewKeyA, 6);
				memcpy(Rdata+10, pNewKeyB, 6);
				memcpy(Buf, Rdata, 16);
				HexToStr(Rdata, 16, Tempdata);
				re = PICC_Reader_Write(DevHandle, (nsector+1)*4-1, (unsigned char*)Buf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
			}
		}
		break;
	case 3://值为3表示同时更改A、B、 密码权限访问字
		if(keyA1B0 == 0)
			{
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x61, nsector, (unsigned char*)poldPin);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}

				memset(Rdata, 0, 256);
				memset(Wdata, 0, 256);
				memset(Tempdata, 0, 256);
				memset(Buf, 0, 36);

				re = PICC_Reader_Read(DevHandle, (nsector+1)*4-1, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}				
				//000000000000 ff078069 ffffffffffff
				//111111111111 ff078069 ffffffffffff
				memcpy(Rdata, pNewKeyA, 6);
				memcpy(Rdata+6, ctrlword, 4);
				memcpy(Rdata+10, pNewKeyB, 6);
				memcpy(Buf, Rdata, 16);
				HexToStr(Rdata, 16, Tempdata);
				re = PICC_Reader_Write(DevHandle, (nsector+1)*4-1, (unsigned char*)Buf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				
			} 
			else
			{				
				re = PICC_Reader_Authentication_Pass(DevHandle, 0x60, nsector, (unsigned char*)poldPin);
				if(re != 0)
				{
					return WS_ERR_OTHER;
				}

				memset(Rdata, 0, 256);
				memset(Wdata, 0, 256);
				memset(Tempdata, 0, 256);
				memset(Buf, 0, 36);
				
				re = PICC_Reader_Read(DevHandle, (nsector+1)*4-1, Rdata);
				if(re != 0)
				{
					return WS_ERR_IC;
				}				
				//000000000000 ff078069 ffffffffffff
				//111111111111 ff078069 ffffffffffff
				memcpy(Rdata, pNewKeyA, 6);
				memcpy(Rdata+6, ctrlword, 4);
				memcpy(Rdata+10, pNewKeyB, 6);
				memcpy(Buf, Rdata, 16);
				HexToStr(Rdata, 16, Tempdata);
				re = PICC_Reader_Write(DevHandle, (nsector+1)*4-1, (unsigned char*)Buf);
				if(re != 0)
				{
					return WS_ERR_IC;
				}
				
			}
		break;
	default:
		return WS_ERR_DataStyleCheckErr;
	}	
	return WS_OK;
}
