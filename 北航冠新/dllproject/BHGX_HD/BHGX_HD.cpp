// BHGX_HD.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "BHGX_HD.h"

long DevHandle;

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
		if(strcmp(pKey,"EE01")==0)
		{
			re=iR_DF03EEInfo(hDev,1,pBuf,iOffsetInBytes,iSizeInBytes,0x01);

		}else if(strcmp(pKey,"EE02")==0)
		{
			re=iR_DF03EEInfo(hDev,2,pBuf,iOffsetInBytes,iSizeInBytes,0x01);
		}else if(strcmp(pKey,"EE03")==0)
		{
			re=iR_DF03EEInfo(hDev,3,pBuf,iOffsetInBytes,iSizeInBytes,0x01);
		}else if(strcmp(pKey,"ED01")==0)
		{
			re=iR_DF03EDInfo(hDev,1,pBuf,iOffsetInBytes,iSizeInBytes,0x01);
		}else if(strcmp(pKey,"ED02")==0)
		{
			re=iR_DF03EDInfo(hDev,2,pBuf,iOffsetInBytes,iSizeInBytes,0x01);
		}else if(strcmp(pKey,"ED03")==0)
		{
			re=iR_DF03EDInfo(hDev,3,pBuf,iOffsetInBytes,iSizeInBytes,0x01);
		}else if(strcmp(pKey,"ED04")==0)
		{
			re=iR_DF03EDInfo(hDev,4,pBuf,iOffsetInBytes,iSizeInBytes,0x01);
		}else if(strcmp(pKey,"ED05")==0)
		{
			re=iR_DF03EDInfo(hDev,5,pBuf,iOffsetInBytes,iSizeInBytes,0x01);
		}else
			return WS_ERR_FileNoErr;
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
	
	if(iCardType == 0)
	{
		return WS_ERR_UNSUPPORTED;
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
	
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	return 0;
}

BHGX_HD_API int __stdcall iWriteRec( unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, unsigned long buflen, int iRecNo, int iRecCount )
{
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	return 0;
}

BHGX_HD_API int __stdcall iAppendRec( unsigned char *pKey, const unsigned char *pBuf, unsigned long buflen )
{
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
	}

	return 0;
}

BHGX_HD_API int __stdcall iSignRec( unsigned char *pKey, int iRecNo, int sign )
{
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
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
			
			strcpy((char*)pCardType, "0");
			HexToStr(uid, 4, pRet);
			return 0;
		}
		strcpy((char*)pCardType, "1");
		HexToStr(resp, re, (unsigned char*)pRet);
	}
	else if(iCardSet == 1)
	{
		memset(resp, 0, 1000);
		re = ICC_Reader_pre_PowerOn(DevHandle, 0x11, resp);
		if(re <=0)
		{
			return WS_ERR_RESET_SAM;
		}
		strcpy((char*)pCardType, "2");
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
	if(DevHandle <= 0)
	{
		return WS_ERR_DEVICECONNECT;
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
