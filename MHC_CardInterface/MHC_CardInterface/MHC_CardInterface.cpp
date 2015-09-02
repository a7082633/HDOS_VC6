// MHC_CardInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "MHC_CardInterface.h"
#include "FileMap.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

static char _PSAMPIN[8] = {0x31,0x32,0x33,0x34,0x35,0x36,0};//


//打开设备
MHC_CARDINTERFACE_API int __stdcall iDOpenPort(void)
{
	char Reset[260];
	char apdu[100];
	char resp[256];
	char sw[5] ;
	
	int ret = rd.Open();
	rd.Beep(20);

	/*						 
	ret = rd.PSAM_Reset(SLOT_PSAM, Reset);
	if (ret != IRV_OK)
		return ret;
	
	//PSAM 
	ret = SelectFile (SLOT_PSAM  , "DF01" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	strcpy(apdu , "0020000003");
	strcat(apdu , _PSAMPIN);
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	*/

	return ret;
}
//断开设备
MHC_CARDINTERFACE_API int __stdcall iDClosePort()
{
	int ret = rd.Close();
	return ret;
}

//上电复位
// slot = SLOT_USER(0x01) 用户卡上电
// slot = SLOT_PSAM(0x11) SAM卡上电
// ATR需要分配40+1以上的字符空间
MHC_CARDINTERFACE_API int __stdcall PowerOn(HANDLE hDev,int slot, char * ATR) 
{
	int ret;
	char Reset[260];
	char apdu[100];
	char resp[256];
	char sw[5];

	if (slot == SLOT_USER) 
	{
		ret = rd.RF_Reset(Reset);
		if (ret == IRV_OK)
		{
			//非接复位成功时，重置全局卡号数据
			loadCardNo(Reset);
		}
		else
			return ret;
		//获取全局的城市代码
		ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF05");
		if (ret != IRV_OK)
			return ret;

		if(ATR[0]=='Y' && ATR[1]=='S' && ATR[2]=='D' && ATR[3]=='M')
			loadCityCode(ATR+4);
		//rd11
		else
		{
			strcpy(apdu , "00b2390005");
			ret = rd.RF_Send (apdu , resp , sw);
			if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
				return IRV_RD_RCDERR;
			else
				loadCityCode(resp + 4);
		}
		//重置工作目录
		resetWorkingADF();
/*
			iW_DF03EE_ALLInfo(hDev,1,"广东省深圳省宜昌市地方税务|222222|20120123|0212|1234566665");
			char data[3000]={0};
			iR_DF03EE_ALLInfo(hDev,1,data);

			iW_DF03ED_ALLInfo(hDev,1,"广东省深圳省宜昌市地方税务|222222|20120123");
			char data1[6000]={0};
			iR_DF03ED_ALLInfo(hDev,1,data1);*/
	}
	else if (slot == SLOT_PSAM)
	{
		ret = rd.PSAM_Reset(slot,Reset);
		ret = SelectFile (SLOT_PSAM  , "DF01" , NULL, NULL);
		if (ret != IRV_OK)
			return IRV_PSAM_ERR;
//		iVerifyPIN(0,"1234");
		/*strcpy(apdu , "0020000003");
		strcat(apdu , _PSAMPIN);
		ret = rd.PSAM_Send (apdu , resp , sw);
		if (strcmp(sw , "9000") != 0)
			return IRV_PSAM_ERR;*/
	}
	else if (slot == SLOT_CARD)
	{
		ret = rd.PSAM_Reset(slot,Reset);
		//大卡
		ret = SelectFile (SLOT_PSAM  , "DF01" , NULL, NULL);
		if (ret != IRV_OK)
			return IRV_PSAM_ERR;
		
/*
		strcpy(apdu , "0020000002");
		strcat(apdu , _PSAMPIN);
		ret = rd.PSAM_Send (apdu , resp , sw);
		if (strcmp(sw , "9000") != 0)
			return IRV_PSAM_ERR;
		*/
	}
	else
	{
		return IRV_PARA_ERR;
	}
	if (ret == IRV_OK)
		strcpy(ATR , (char *)Reset);

	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iVerifyPIN(HANDLE hDev,char * PIN)
{
	int ret;
	char Reset[260];
	char apdu[100];
	char resp[256];
	char sw[5];

	strcpy(apdu , "00200000");
	int len = strlen(PIN)/2;
	char a[3]={0};
	sprintf(a,"%02d",len);
	strcat(apdu,a);
	strcat(apdu , PIN);
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	return IRV_OK;
}

//发卡机构基本数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF05Info(HANDLE hDev,
							  char * KLB,             //卡类别代码                                                                                        
							  char * GFBB,            //规范版本                                                                                          
							  char * FKJGMC,          //发卡机构名称                                                                                      
							  char * FKJGDM,          //发卡机构代码 
							  char * FKJGZS,			//发卡机构证书
							  char * FKSJ,            //发卡时间，YYYYMMDD格式                                                                            
							  char * KH,              //卡号，与居民身份证号或者证件号码一致
							  char * AQM,             //安全码                                                                                            
							  char * XPXLH,           //芯片序列号
							  char * YYCSDM				//应用城市代码
							  )
{
	int ret ;
	char apdu[100]={0};
	char resp[400]={0};
	char sw[5]={0};
//	char KLBb[3]={0};

	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF05");
	if (ret != IRV_OK)
		return ret;
	//rd1 136 9139 8466 tianye 
	strcpy(apdu , "00b2010003");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp , KLB );
	
	//rd2
	strcpy(apdu , "00b2020006");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,GFBB );
	
	//rd3
	strcpy(apdu , "00b2030020");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,FKJGMC );
	
	//rd4
	strcpy(apdu , "00b204000D");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,FKJGDM );
	
	//rd5
	strcpy(apdu , "00b20500B6");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,FKJGZS );

	//rd6
	strcpy(apdu , "00b2060006");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,FKSJ );
	
	//rd8
	strcpy(apdu , "00b2080014");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,KH );
	
	//rd9
	strcpy(apdu , "00b2090005");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,AQM );
	
	//rd10
	strcpy(apdu , "00b20A000C");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,XPXLH );
	
	//rd11
	strcpy(apdu , "00b2390005");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,YYCSDM );

	return IRV_OK;
}

//持卡人基本信息数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF06Info(HANDLE hDev,
							  char * XM,              //姓名
							  char * XB,              //性别代码
							  char * MZ,              //民族代码
							  char * CSRQ,            //出生日期，YYYYMMDD格式
							  char * SFZH            //居民身份证号
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DDF1 , apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,XM );
	
	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,XB );
	
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,MZ );
	
	//rd4
	strcpy(apdu , "00b2040400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,CSRQ );
	
	//rd5
	strcpy(apdu , "00b2050400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,SFZH );


	return IRV_OK;
}							 

//发卡机构基本数据文件
MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF05Info(
							  HANDLE hDev,
							  char * KLB,             //卡类别代码                                                                                        
							  char * GFBB,            //规范版本                                                                                          
							  char * FKJGMC,          //发卡机构名称                                                                                      
							  char * FKJGDM,          //发卡机构代码 
							  char * FKJGZS,			//发卡机构证书
							  char * FKSJ,            //发卡时间，YYYYMMDD格式                                                                            
							  char * KH,              //卡号，与居民身份证号或者证件号码一致
							  char * AQM,             //安全码                                                                                            
							  char * XPXLH,           //芯片序列号
							  char * YYCSDM				//应用城市代码
							  )
{
	char apdu[512 + 10 + 1];
	char resp[100];
//	char apduHead[11];
	char divGene[49];
//	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DDF1 , divGene , resp);
	if (ret != IRV_OK)
		return ret;
	
	if (( KLB != NULL) &&( strlen(KLB) != 0) )          
	{
		strcpy(apdu , "01");
		strcpy(resp , "03");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_KLB, KLB );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( GFBB != NULL) &&( strlen(GFBB) != 0) )         
	{
		strcpy(apdu , "02");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_GFBB, GFBB );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( FKJGMC != NULL) &&( strlen(FKJGMC) != 0)  )           
	{
		strcpy(apdu , "03");
		strcpy(resp , "34");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_FKJGMC, FKJGMC );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( FKJGDM != NULL) &&( strlen(FKJGDM) != 0) )             
	{
		strcpy(apdu , "04");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_FKJGDM, FKJGDM );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( FKJGZS != NULL) &&( strlen(FKJGZS) != 0) )             
	{
		int len = strlen(FKJGZS);
		for(int i=0;i<(360-len);i++)
			strcat(FKJGZS,"0");
		strcpy(apdu , "05");
		strcpy(resp , "C4");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_FKJGZS, FKJGZS );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( FKSJ != NULL) &&( strlen(FKSJ) != 0)  )            
	{
		strcpy(apdu , "06");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_FKSJ, FKSJ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( KH != NULL) &&( strlen(KH) != 0)  )            
	{
		strcpy(apdu , "07");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp ,TAG_KH,KH);
		if (ret != IRV_OK) 
			return ret;
	}
	if (( AQM != NULL) &&( strlen(AQM) != 0)  )            
	{
		strcpy(apdu , "08");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_AQM , AQM);
		if (ret != IRV_OK) 
			return ret;
	}

	if (( XPXLH != NULL) &&( strlen(XPXLH) != 0)  )            
	{
		strcpy(apdu , "09");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_XPXLH, XPXLH );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( YYCSDM != NULL) &&( strlen(YYCSDM) != 0)  )            
	{
		strcpy(apdu , "0A");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_YYCSDM, YYCSDM );
		if (ret != IRV_OK) 
			return ret;
	}

	return IRV_OK;



}

MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF06Info(HANDLE hDev,
							  char * XM,              //姓名
							  char * XB,              //性别代码
							  char * MZ,              //民族代码
							  char * CSRQ,            //出生日期，YYYYMMDD格式
							  char * SFZH            //居民身份证号
							  )
{
	char apdu[512 + 10 + 1];
	char resp[100];
//	char apduHead[11];
	char divGene[49];
//	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DDF1 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	if (( XM != NULL) &&( strlen(XM) != 0) )          
	{
		strcpy(apdu , "01");
		strcpy(resp , "34");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_XM, XM );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( XB != NULL) &&( strlen(XB) != 0)     )         
	{
		strcpy(apdu , "02");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_XB, XB );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( MZ != NULL) &&( strlen(MZ) != 0)   )           
	{
		strcpy(apdu , "03");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_MZDM, MZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( CSRQ != NULL) &&( strlen(CSRQ) != 0) )             
	{
		strcpy(apdu , "04");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_CSRQ, CSRQ );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( SFZH != NULL) &&( strlen(SFZH) != 0)  )            
	{
		strcpy(apdu , "05");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_JMSFZH, SFZH );
		if (ret != IRV_OK) 
			return ret;
	}

	return IRV_OK;
}


//照片
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF07Info(HANDLE hDev,
							  BYTE * ZHAOPIAN        //照片												  												  
							  )
{
	char apdu[100];
	char resp[400];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF07");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DDF1,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//先读出长度
	strcpy(apdu , "00B0000002");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_BINERR;
	u.HexstrToBin((unsigned char *)sw  ,(unsigned char *) resp , 4);
	
	//数据后续总长度
	UINT iend = (sw[0] * 256 + sw[1]) + 2;
	if (iend > 3072) 
		return IRV_DDF1EF07_DATAERR;
	int a = (iend - iend % 0x80) / 0x80 ;
	//
	for (int i = 0 ; i < a ; i++ )
	{
		memcpy (resp, "\x00\xb0\x00\x00\x80" , 5);
		ret = i * 0x80;
		u.UINTToBin(ret , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_RD_BINERR;	
		}
		u.HexstrToBin((unsigned char *)ZHAOPIAN + i * 0x80 , (unsigned char *)resp , 0x80 * 2);
	}
	//last block
	if(iend%0x80==0)//前面循环已写
	{}
	else
	{
		memcpy (resp, "\x00\xb0\x00\x00\x80" , 5);
		ret = i * 0x80;
		u.UINTToBin(ret , resp + 2);
		resp[4] = iend % 0x80 ;
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_RD_BINERR;	
		}
		u.HexstrToBin((unsigned char *)ZHAOPIAN + i * 0x80 , (unsigned char *)resp , (iend % 0x80) * 2);
	}
	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF07Info(HANDLE hDev,
							  BYTE * ZHAOPIAN        //照片												  												  
							  )
{
	char apdu[ 510 + 1];
	char resp[512];
	char divGene[49];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF07");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DDF1 , divGene , resp);
	if (ret != IRV_OK)
		return ret;
	
	//数据总长度
	UINT ilen = ZHAOPIAN[0] * 256 + ZHAOPIAN[1]+2;
	
	int a = (ilen - ilen % 0x80) / 0x80 ;
	//
	for (int i = 0 ; i < a ; i++ )
	{
		memcpy (resp, "\x00\xD6\x00\x00\x80" , 5);
		ret = i * 0x80;
		u.UINTToBin(ret , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		u.BinToHexstr((unsigned char *)resp , (unsigned char *)ZHAOPIAN + i * 0x80 , 0x80);
		strcat(apdu , resp);
		//ret = UpdateBinEncMac(STK_DDF1 , apdu , resp);
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_WR_BINERR;	
		}
	}
	if(ilen%0x80==0)//前面循环已写
	{}
	else
	{
		//last block
		memcpy (resp, "\x00\xD6\x00\x00\x94" , 5);
		ret = i * 0x80;
		u.UINTToBin(ret , resp + 2);
	//	resp[4] = (ilen % 0x80) + 16 ;
	//	resp[4] = resp[4] - (resp[4] % 16) + 4;
		resp[4] = (ilen % 0x80);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		u.BinToHexstr((unsigned char *)resp ,(unsigned char *) ZHAOPIAN + i * 0x80 , ilen % 0x80);
		strcat(apdu , resp);
		
		//ret = UpdateBinEncMac(STK_DDF1 , apdu , resp);
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_WR_BINERR;	
		}
	}
	return ret;
}

//DDF1 EF08
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF08Info(HANDLE hDev,
							  char * KYXQ,			//卡有效期
							  char * BRDH1,           //本人电话1
							  char * BRDH2,           //本人电话2
							  char * YLFYZFFS1,		  //医疗费用支付方式1
							  char * YLFYZFFS2,		  //医疗费用支付方式2
							  char * YLFYZFFS3		  //医疗费用支付方式3		
							  )
{
	
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF08");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DDF1 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,KYXQ );
	
	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,BRDH1 );
	
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,BRDH2);
	
	//rd4
	strcpy(apdu , "00b2040400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,YLFYZFFS1 );
	
	//rd5
	strcpy(apdu , "00b2050400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,YLFYZFFS2 );
	
	//rd6
	strcpy(apdu , "00b2060400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,YLFYZFFS3 );

	return IRV_OK;
}

//EF08
MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF08Info(HANDLE hDev,
							  char * KYXQ,			//卡有效期
							  char * BRDH1,           //本人电话1
							  char * BRDH2,           //本人电话2
							  char * YLFYZFFS1,		  //医疗费用支付方式1
							  char * YLFYZFFS2,		  //医疗费用支付方式2
							  char * YLFYZFFS3		  //医疗费用支付方式3		
							  )
{
	char apdu[ 10 + 1];
	char resp[100];
	char divGene[49];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,NULL,"EF08");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DDF1 , divGene , resp);
	if (ret != IRV_OK)
		return ret;
	
	if (( KYXQ != NULL) &&( strlen(KYXQ) != 0) )          
	{
		strcpy(apdu , "01");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_KYXQ, KYXQ );
		if (ret != IRV_OK) 
			return ret;
	}

	if (( BRDH1 != NULL) &&( strlen(BRDH1) != 0)     )         
	{
		strcpy(apdu , "02");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_BRDH1, BRDH1 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( BRDH2 != NULL) &&( strlen(BRDH2) != 0)   )           
	{
		strcpy(apdu , "03");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_BRDH2, BRDH2 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( YLFYZFFS1 != NULL) &&( strlen(YLFYZFFS1) != 0) )             
	{
		strcpy(apdu , "04");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_YLFYZF1, YLFYZFFS1 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( YLFYZFFS2 != NULL) &&( strlen(YLFYZFFS2) != 0)  )            
	{
		strcpy(apdu , "05");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_YLFYZF2, YLFYZFFS2 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( YLFYZFFS3 != NULL) &&( strlen(YLFYZFFS3) != 0)  )            
	{
		strcpy(apdu , "06");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DDF1 , apdu , resp , TAG_YLFYZF3, YLFYZFFS3 );
		if (ret != IRV_OK) 
			return ret;
	}

	return IRV_OK;
}


							  
//地址信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF05Info(HANDLE hDev,
							  char * DZLB1,             //地址类别1
							  char * DZ1,				//地址1
							  char * DZLB2,             //地址类别1
							  char * DZ2				//地址1
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF01 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,DZLB1 );
	
	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,DZ1 );
	
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,DZLB2);
	
	//rd4
	strcpy(apdu , "00b2040400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,DZ2 );
	
	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF05Info(HANDLE hDev,
							  char * DZLB1,             //地址类别1
							  char * DZ1,				//地址1
							  char * DZLB2,             //地址类别1
							  char * DZ2				//地址1
							  )
{
	char apdu[ 10 + 1];
	char resp[100];
	char divGene[49];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF01 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	if (( DZLB1 != NULL) &&( strlen(DZLB1) != 0)  )            
	{
		strcpy(apdu , "01");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_DZLB1, DZLB1 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( DZ1 != NULL) &&( strlen(DZ1) != 0)  )            
	{
		strcpy(apdu , "02");
		strcpy(resp , "74");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_DZ1, DZ1 );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( DZLB2 != NULL) &&( strlen(DZLB2) != 0)  )            
	{
		strcpy(apdu , "03");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_DZLB2, DZLB2 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( DZ2 != NULL) &&( strlen(DZ2) != 0)  )            
	{
		strcpy(apdu , "04");
		strcpy(resp , "74");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_DZ2, DZ2 );
		if (ret != IRV_OK) 
			return ret;
	}

	return IRV_OK;
}

//联系人信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF06Info(HANDLE hDev,
							  char * LXRXM1,          //联系人姓名1                                                                                       
							  char * LXRGX1,          //联系人关系代码1                                                                                   
							  char * LXRDH1,          //联系人电话1                                                                                       
							  char * LXRXM2,          //联系人姓名2                                                                                       
							  char * LXRGX2,          //联系人关系代码2                                                                                   
							  char * LXRDH2,          //联系人电话2                                                                                       
							  char * LXRXM3,          //联系人姓名3                                                                                       
							  char * LXRGX3,          //联系人关系代码3                                                                                   
							  char * LXRDH3			  //联系人电话3
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF01 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,LXRXM1 );
	
	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,LXRGX1 );
	
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,LXRDH1);
	
	//rd4
	strcpy(apdu , "00b2040400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,LXRXM2 );
	
	//rd5
	strcpy(apdu , "00b2050400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,LXRGX2 );
	
	//rd6
	strcpy(apdu , "00b2060400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,LXRDH2);
	
	//rd7
	strcpy(apdu , "00b2070400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,LXRXM3);
	
	//rd8
	strcpy(apdu , "00b2080400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,LXRGX3 );
	
	//rd9
	strcpy(apdu , "00b2090400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,LXRDH3);

	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF06Info(HANDLE hDev,
							  char * LXRXM1,          //联系人姓名1                                                                                       
							  char * LXRGX1,          //联系人关系代码1                                                                                   
							  char * LXRDH1,          //联系人电话1                                                                                       
							  char * LXRXM2,          //联系人姓名2                                                                                       
							  char * LXRGX2,          //联系人关系代码2                                                                                   
							  char * LXRDH2,          //联系人电话2                                                                                       
							  char * LXRXM3,          //联系人姓名3                                                                                       
							  char * LXRGX3,          //联系人关系代码3                                                                                   
							  char * LXRDH3			  //联系人电话3
							  )
{
	char apdu[ 10 + 1];
	char resp[100];
	char divGene[49];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF01 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	if (( LXRXM1 != NULL) &&( strlen(LXRXM1) != 0)  )            
	{
		strcpy(apdu , "01");
		strcpy(resp , "34");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRXM1, LXRXM1 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( LXRGX1 != NULL) &&( strlen(LXRGX1) != 0)  )            
	{
		strcpy(apdu , "02");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRGX1, LXRGX1 );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( LXRDH1 != NULL) &&( strlen(LXRDH1) != 0)  )            
	{
		strcpy(apdu , "03");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRDH1, LXRDH1 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( LXRXM2 != NULL) &&( strlen(LXRXM2) != 0)  )            
	{
		strcpy(apdu , "04");
		strcpy(resp , "34");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRXM2, LXRXM2 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( LXRGX2 != NULL) &&( strlen(LXRGX2) != 0)  )            
	{
		strcpy(apdu , "05");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRGX2, LXRGX2 );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( LXRDH2 != NULL) &&( strlen(LXRDH2) != 0)  )            
	{
		strcpy(apdu , "06");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRDH2, LXRDH2 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( LXRXM3 != NULL) &&( strlen(LXRXM3) != 0)  )            
	{
		strcpy(apdu , "07");
		strcpy(resp , "34");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRXM3, LXRXM3 );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( LXRGX3 != NULL) &&( strlen(LXRGX3) != 0)  )            
	{
		strcpy(apdu , "08");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRGX3, LXRGX3 );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( LXRDH3 != NULL) &&( strlen(LXRDH3) != 0)  )            
	{
		strcpy(apdu , "09");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_LXRDH3, LXRDH3 );
		if (ret != IRV_OK) 
			return ret;
	}

	return IRV_OK;
}

//职业婚姻信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF07Info(HANDLE hDev,
							  char * WHCD,          //文化程度代码
							  char * HYZK,			//婚姻状况代码
							  char * ZY             //职业代码
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF07");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF01 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,WHCD );
	
	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,HYZK );
	
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,ZY);
	
	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF07Info(HANDLE hDev,
							  char * WHCD,          //文化程度代码
							  char * HYZK,			//婚姻状况代码
							  char * ZY             //职业代码
							  )
{
	char apdu[ 10 + 1];
	char resp[100];
	char divGene[49];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF07");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF01 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	if (( WHCD != NULL) &&( strlen(WHCD) != 0)  )            
	{
		strcpy(apdu , "01");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_WHCD, WHCD );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( HYZK != NULL) &&( strlen(HYZK) != 0)  )            
	{
		strcpy(apdu , "02");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_HYZK, HYZK );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( ZY != NULL) &&( strlen(ZY) != 0)  )            
	{
		strcpy(apdu , "03");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_ZYDM, ZY );
		if (ret != IRV_OK) 
			return ret;
	}
	return IRV_OK;
}

//证件记录信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF08Info(HANDLE hDev,
							  char * ZJLB,            //证件类别代码，决定身份证号和证件号码哪一项必填
							  char * ZJHM,            //证件号码
							  char * JKDAH,           //健康档案号
							  char * XNHZH            //新农合证号
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF08");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF01 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(CN_style,  resp ,ZJLB );
	
	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,ZJHM );
	
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,JKDAH);
	
	//rd4
	strcpy(apdu , "00b2040400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,XNHZH);

	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF08Info(HANDLE hDev,
							  char * ZJLB,            //证件类别代码，决定身份证号和证件号码哪一项必填
							  char * ZJHM,            //证件号码
							  char * JKDAH,           //健康档案号
							  char * XNHZH            //新农合证号
							  )
{
	char apdu[ 10 + 1];
	char resp[100];
	char divGene[49];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF01","EF08");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF01 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	if (( ZJLB != NULL) &&( strlen(ZJLB) != 0)  )            
	{
		strcpy(apdu , "01");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_ZJLB, ZJLB );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( ZJHM != NULL) &&( strlen(ZJHM) != 0)  )            
	{
		strcpy(apdu , "02");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_ZJHM, ZJHM );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( JKDAH != NULL) &&( strlen(JKDAH) != 0)  )            
	{
		strcpy(apdu , "03");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_JKDABH, JKDAH);
		if (ret != IRV_OK) 
			return ret;
	}
	if (( XNHZH != NULL) &&( strlen(XNHZH) != 0)  )            
	{
		strcpy(apdu , "04");
		strcpy(resp , "24");
		ret = UpdateRecEncMac(STK_DF01 , apdu , resp , TAG_XNHZH, XNHZH );
		if (ret != IRV_OK) 
			return ret;
	}
	return IRV_OK;
}

//临床基本数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF05Info(HANDLE hDev,
							  char * ABOXX,           //ABO血型代码
							  char * RHXX,            //RH血型代码
							  char * XCBZ,            //哮喘标志
							  char * XZBBZ,           //心脏病标志
							  char * XNXGBBZ,         //心脑血管病标志
							  char * DXBBZ,           //癫痫病标志
							  char * NXWLBZ,          //凝血紊乱标志
							  char * TNBBZ,           //糖尿病标志
							  char * QGYBZ,           //青光眼标志
							  char * TXBZ,            //透析标志
							  char * QGYZBZ,          //器官移植标志
							  char * QGQSBZ,          //器官缺失标志
							  char * KZXYZBZ,         //可装卸义肢标志
							  char * XZQBQBZ,         //心脏起搏器标志
							  char * QTYXJSMC         //其他医学警示名称
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF02 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,ABOXX );
	
	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,RHXX );
	
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,XCBZ);
	
	//rd4
	strcpy(apdu , "00b2040400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,XZBBZ);
	
	//rd5
	strcpy(apdu , "00b2050400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,XNXGBBZ );
	
	//rd6
	strcpy(apdu , "00b2060400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,DXBBZ );
	
	//rd7
	strcpy(apdu , "00b2070400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,NXWLBZ);
	
	//rd8
	strcpy(apdu , "00b2080400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,TNBBZ);

	//rd9
	strcpy(apdu , "00b2090400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,QGYBZ );
	
	//rd10
	strcpy(apdu , "00b20A0400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,TXBZ );
	
	//rd11
	strcpy(apdu , "00b20B0400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,QGYZBZ);
	
	//rd12
	strcpy(apdu , "00b20C0400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,QGQSBZ);

	//rd13
	strcpy(apdu , "00b20D0400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,KZXYZBZ );
	
	//rd14
	strcpy(apdu , "00b20E0400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,XZQBQBZ );
	
	//rd15
	strcpy(apdu , "00b20F0400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(AN_style,  resp ,QTYXJSMC);
	
	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF02EF05Info(HANDLE hDev,
							  char * ABOXX,           //ABO血型代码
							  char * RHXX,            //RH血型代码
							  char * XCBZ,            //哮喘标志
							  char * XZBBZ,           //心脏病标志
							  char * XNXGBBZ,         //心脑血管病标志
							  char * DXBBZ,           //癫痫病标志
							  char * NXWLBZ,          //凝血紊乱标志
							  char * TNBBZ,           //糖尿病标志
							  char * QGYBZ,           //青光眼标志
							  char * TXBZ,            //透析标志
							  char * QGYZBZ,          //器官移植标志
							  char * QGQSBZ,          //器官缺失标志
							  char * KZXYZBZ,         //可装卸义肢标志
							  char * XZQBQBZ,         //心脏起搏器标志
							  char * QTYXJSMC        //其他医学警示名称
							  )
{
	char apdu[ 10 + 1];
	char resp[100];
	char divGene[49];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF02_1 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	if (( ABOXX != NULL) &&( strlen(ABOXX) != 0)  )            
	{
		strcpy(apdu , "01");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_ABOXX, ABOXX );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( RHXX != NULL) &&( strlen(RHXX) != 0)  )            
	{
		strcpy(apdu , "02");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_RHXX, RHXX );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( XCBZ != NULL) &&( strlen(XCBZ) != 0)  )            
	{
		strcpy(apdu , "03");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_XCBZ, XCBZ);
		if (ret != IRV_OK) 
			return ret;
	}
	if (( XZBBZ != NULL) &&( strlen(XZBBZ) != 0)  )            
	{
		strcpy(apdu , "04");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_XZBBZ, XZBBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( XNXGBBZ != NULL) &&( strlen(XNXGBBZ) != 0)  )            
	{
		strcpy(apdu , "05");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_XNXGBBZ, XNXGBBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	
	if (( DXBBZ != NULL) &&( strlen(DXBBZ) != 0)  )            
	{
		strcpy(apdu , "06");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_DXBBZ, DXBBZ);
		if (ret != IRV_OK) 
			return ret;
	}
	if (( NXWLBZ != NULL) &&( strlen(NXWLBZ) != 0)  )            
	{
		strcpy(apdu , "07");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_NXWLBZ, NXWLBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( TNBBZ != NULL) &&( strlen(TNBBZ) != 0)  )            
	{
		strcpy(apdu , "08");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_TNBBZ, TNBBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( QGYBZ != NULL) &&( strlen(QGYBZ) != 0)  )            
	{
		strcpy(apdu , "09");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_QGYBZ, QGYBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( TXBZ != NULL) &&( strlen(TXBZ) != 0)  )            
	{
		strcpy(apdu , "0A");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_TXBZ, TXBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( QGYZBZ != NULL) &&( strlen(QGYZBZ) != 0)  )            
	{
		strcpy(apdu , "0B");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_QGYZBZ, QGYZBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( QGQSBZ != NULL) &&( strlen(QGQSBZ) != 0)  )            
	{
		strcpy(apdu , "0C");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_QGQSBZ, QGQSBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( KZXYZBZ != NULL) &&( strlen(KZXYZBZ) != 0)  )            
	{
		strcpy(apdu , "0D");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_KZXYZBZ, KZXYZBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( XZQBQBZ != NULL) &&( strlen(XZQBQBZ) != 0)  )            
	{
		strcpy(apdu , "0E");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_XZQBQBZ, XZQBQBZ );
		if (ret != IRV_OK) 
			return ret;
	}
	if (( QTYXJSMC != NULL) &&( strlen(QTYXJSMC) != 0)  )            
	{
		strcpy(apdu , "0F");
		strcpy(resp , "34");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_QTYXJS, QTYXJSMC );
		if (ret != IRV_OK) 
			return ret;
	}
	return IRV_OK;
}


//特殊信息数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF06Info(HANDLE hDev,
							  char * JSBBZ           //精神病标志
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF02 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
		tlvRespToOutput(B_style,  resp ,JSBBZ );

	return IRV_OK;
}


MHC_CARDINTERFACE_API int __stdcall iW_DF02EF06Info(HANDLE hDev,
							  char * JSBBZ           //精神病标志
							  )
{
	char apdu[ 10 + 1];
	char resp[100];
	char divGene[49];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF02_2 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	if (( JSBBZ != NULL) &&( strlen(JSBBZ) != 0)  )            
	{
		strcpy(apdu , "01");
		strcpy(resp , "14");
		ret = UpdateRecEncMac(STK_DF02 , apdu , resp , TAG_JSBBZ, JSBBZ );
		if (ret != IRV_OK) 
			return ret;
	}

	return IRV_OK;
}


//过敏基本数据文件
//nRecorderNo 记录号
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF07Info(HANDLE hDev, int nRecorderNo, 
													char* GMWZMC, 
													char* GMFY)
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF07");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF02 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	switch (nRecorderNo)
	{
	case 1:
		strcpy(apdu , "00b2010400");
		break;
	case 2:
		strcpy(apdu , "00b2020400");
		break;
	case 3:
		strcpy(apdu , "00b2030400");
		break;
	default:
		return IRV_PARA_ERR;
	}

	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
//		return IRV_RD_RCDERR;
	}
	else
	{
		memcpy(apdu , resp , 40);
		apdu[40] = 0;
		u.HexstrToBin((unsigned char*)GMWZMC , (unsigned char*)apdu , 40);
		u.HexstrToBin((unsigned char*)GMFY , (unsigned char*)resp + 40 , 200);
	}

	return IRV_OK;
}


//由于是循环记录，新写入的数据永远是第一条数据
MHC_CARDINTERFACE_API int __stdcall iW_DF02EF07Info(HANDLE hDev,
							  char * GMWZMC,        //过敏物质名称
							  char * GMFY			//过敏物质反应
							  )
{
	char apdu[ 512 + 4];
	char resp[255];
	char divGene[125];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF07");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF02_3 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	memset(divGene , 0 , sizeof(divGene));
	strcpy(divGene , GMWZMC);
	strcpy(divGene + 20 , GMFY);
	//转成字符串
	u.BinToHexstr( (unsigned char *)resp ,(unsigned char *) divGene , 120);
	
	//组织数据写入
	strcpy(apdu , "00DC000378");
	strcat(apdu,resp);

//	char apdu[100];
//	char resp[256];
	char sw[5];
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_WR_RCDERR;
	}

//	ret = UpdateBinEncMac(STK_DF02 , apdu , resp);
	
	return IRV_OK;
}

//免疫基本数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF08Info(HANDLE hDev, int nRecorderNo, 
													char* MYJZMC, 
													char* MYJZSJ)
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF08");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF02 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	switch (nRecorderNo)
	{
	case 1:
		strcpy(apdu , "00b2010400");
		break;
	case 2:
		strcpy(apdu , "00b2020400");
		break;
	case 3:
		strcpy(apdu , "00b2030400");
		break;
	case 4:
		strcpy(apdu , "00b2040400");
		break;
	case 5:
		strcpy(apdu , "00b2050400");
		break;
	case 6:
		strcpy(apdu , "00b2060400");
		break;
	case 7:
		strcpy(apdu , "00b2070400");
		break;
	case 8:
		strcpy(apdu , "00b2080400");
		break;
	case 9:
		strcpy(apdu , "00b2090400");
		break;
	case 10:
		strcpy(apdu , "00b20A0400");
		break;

	default:
		return IRV_PARA_ERR;
	}

	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
	//	return IRV_RD_RCDERR;
	}
	else
	{
		memcpy(apdu , resp , 40);
		apdu[40] = 0;
		u.HexstrToBin((unsigned char*)MYJZMC , (unsigned char*)apdu , 40);
		strcpy(MYJZSJ , resp + 40);
	}

	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF02EF08Info(HANDLE hDev,
							  char* MYJZMC,//免疫接种名称 
							  char* MYJZSJ //免疫接种时间
							  )
{
	char apdu[ 510 + 1];
	char resp[255];
	char divGene[125];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF02","EF08");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF02_3 , divGene , resp);
	if (ret != IRV_OK)
		return ret;

	memset(divGene , 0 , sizeof(divGene));
	strcpy(divGene , MYJZMC);
	u.HexstrToBin((unsigned char *)divGene + 20 , (unsigned char *)MYJZSJ , strlen(MYJZSJ));
	//转成字符串
	u.BinToHexstr((unsigned char *)resp , (unsigned char *)divGene , 24);
	
	//组织数据写入
//	strcpy(apdu , "04DC000324");
//	ret = UpdateBinEncMac(STK_DF02 , apdu , resp);

	strcpy(apdu , "00DC000318");
	strcat(apdu,resp);

	char sw[5];
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_WR_RCDERR;
	}
	return IRV_OK;

}

//住院信息索引文件
MHC_CARDINTERFACE_API int __stdcall iR_DF03EF05Info(HANDLE hDev,
							  char * ZYJLBS1,             //住院记录有效标志
							  char * ZYJLBS2,
							  char * ZYJLBS3
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF03 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( ZYJLBS1 ,resp  );

	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( ZYJLBS2 ,resp  );
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( ZYJLBS3 ,resp  );

	return IRV_OK;
}


//将住院有效标识更改为0x00
MHC_CARDINTERFACE_API int __stdcall iW_DF03EF05Info(HANDLE hDev,
							  int nRecorderNo
							  )
{
	char apdu[100 + 1];
	char cmpApdu[100 + 1];
	char resp[255];
	char divGene[125];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF03_1, divGene , resp);
	if (ret != IRV_OK)
		return ret;



	strcpy(cmpApdu , "84D2000400" );
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);
	ret  = rd.RF_Send(cmpApdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_W_DF03EF05ERR;	
	return IRV_OK;


	
	//组织数据
	strcpy(cmpApdu , "84D2000404");
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);

	ret = GetCNandCityCode(divGene , divGene + 16 );
	if (ret != IRV_OK)
		return ret;
	
	strcpy(apdu , "0084000008");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;
	strcat(divGene , resp ); //cardno + citycode + rand

	//PSAM 算MAC

	strcpy(apdu , "80DE480518");
	strcat(apdu , divGene);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "80FA050000");
	strcat(apdu , "00000000000000000000000000000000" ); // mac init
	strcpy( apdu + 10 + 32 , cmpApdu ) ;
	Padding(apdu + 10);
	ret = strlen(apdu + 10) / 2;
	u.UINTToBin(ret , sw);
	u.BinToHexstr((unsigned char *)resp ,(unsigned char *) sw + 1, 1 );
	memcpy(apdu + 8 , resp , 2);

	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (memcmp(sw , "\x36\x31" , 2) != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C00000");
	strcat(apdu , sw + 2);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcat(cmpApdu , resp );
	ret  = rd.RF_Send(cmpApdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_W_DF03EF05ERR;	

	return IRV_OK;

}

//将住院有效标识更改为0xff
MHC_CARDINTERFACE_API int __stdcall iErase_DF03EF05Info(HANDLE hDev,
								  int nRecorderNo
								  )
{
	char apdu[100 + 1];
	char cmpApdu[100 + 1];
	char resp[255];
	char divGene[125];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF03_2, divGene , resp);
	if (ret != IRV_OK)
		return ret;

	strcpy(cmpApdu , "840C000400" );
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);
	ret  = rd.RF_Send(cmpApdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_ER_DF03EF05ERR;	
	return IRV_OK;

	//组织数据
	strcpy(cmpApdu , "840C000404");
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);
	
	ret = GetCNandCityCode(divGene , divGene + 16 );
	if (ret != IRV_OK)
		return ret;
	
	strcpy(apdu , "0084000008");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;
	strcat(divGene , resp ); //cardno + citycode + rand

	//PSAM 算MAC
	strcpy(apdu , "80DE480518");
	strcat(apdu , divGene);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "80FA050000");
	strcat(apdu , "00000000000000000000000000000000" ); // mac init
	strcpy( apdu + 10 + 32 , cmpApdu ) ;
	Padding(apdu + 10);
	ret = strlen(apdu + 10) / 2;
	u.UINTToBin(ret , sw);
	u.BinToHexstr((unsigned char *)resp ,(unsigned char *) sw + 1, 1 );
	memcpy(apdu + 8 , resp , 2);

	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (memcmp(sw , "\x36\x31" , 2) != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C00000");
	strcat(apdu , sw + 2);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcat(cmpApdu , resp );
	ret  = rd.RF_Send(cmpApdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_ER_DF03EF05ERR;	

	return IRV_OK;
}


//门诊信息索引文件
MHC_CARDINTERFACE_API int __stdcall iR_DF03EF06Info(HANDLE hDev,
							  char * MZJLBS1, //门诊记录有效标识
							  char * MZJLBS2,
							  char * MZJLBS3,
							  char * MZJLBS4,
							  char * MZJLBS5
							  )
{
	char apdu[100];
	char resp[256];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF03 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//rd1
	strcpy(apdu , "00b2010400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( MZJLBS1 ,resp  );

	//rd2
	strcpy(apdu , "00b2020400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( MZJLBS2 ,resp  );
	//rd3
	strcpy(apdu , "00b2030400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( MZJLBS3 ,resp  );
	//rd4
	strcpy(apdu , "00b2040400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( MZJLBS4 ,resp  );
	//rd5
	strcpy(apdu , "00b2050400");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_RCDERR;
	}
	else
		strcpy( MZJLBS5 ,resp  );
	return IRV_OK;
}

//写0x00
MHC_CARDINTERFACE_API int __stdcall iW_DF03EF06Info(HANDLE hDev,
							  int nRecorderNo
							  )
{
	char apdu[100 + 1];
	char cmpApdu[100 + 1];
	char resp[255];
	char divGene[125];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF03_1, divGene , resp);
	if (ret != IRV_OK)
		return ret;

	strcpy(cmpApdu , "84D2000400" );
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);
	ret  = rd.RF_Send(cmpApdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_W_DF03EF05ERR;	

	return IRV_OK;
	
	//组织数据
	strcpy(cmpApdu , "84D2000404");
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);

	ret = GetCNandCityCode(divGene , divGene + 16 );
	if (ret != IRV_OK)
		return ret;
	
	strcpy(apdu , "0084000008");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;
	strcat(divGene , resp ); //cardno + citycode + rand

	//PSAM 算MAC
	strcpy(apdu , "80DE480518");
	strcat(apdu , divGene);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "80FA050000");
	strcat(apdu + 10 , "00000000000000000000000000000000" ); // mac init
	strcpy( apdu + 10 + 32 , cmpApdu ) ;
	Padding(apdu + 10);
	ret = strlen(apdu + 10) / 2;
	u.UINTToBin(ret , sw);
	u.BinToHexstr((unsigned char *)resp ,(unsigned char *) sw + 1, 1 );
	memcpy(apdu + 8 , resp , 2);

	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (memcmp(sw , "\x36\x31" , 2) != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C00000");
	strcat(apdu , sw + 2);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcat(cmpApdu , resp );
	ret  = rd.RF_Send(cmpApdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_W_DF03EF05ERR;	

	return IRV_OK;
}

//写0xff
MHC_CARDINTERFACE_API int __stdcall iErase_DF03EF06Info(HANDLE hDev,
								  int nRecorderNo
								  )
{
	char apdu[100 + 1];
	char cmpApdu[100 + 1];
	char resp[255];
	char divGene[125];
	char sw[5];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(divGene , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 UK
	ret = AuthUK(UK_DF03_2, divGene , resp);
	if (ret != IRV_OK)
		return ret;

	strcpy(cmpApdu , "840C000400" );
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);
	ret  = rd.RF_Send(cmpApdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_ER_DF03EF05ERR;	
	return IRV_OK;
	
	//组织数据
	strcpy(cmpApdu , "840C000404");
	u.intTo1ByteHex(nRecorderNo , cmpApdu + 4);

	ret = GetCNandCityCode(divGene , divGene + 16 );
	if (ret != IRV_OK)
		return ret;
	
	strcpy(apdu , "0084000008");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;
	strcat(divGene , resp ); //cardno + citycode + rand

	//PSAM 算MAC
	strcpy(apdu , "80DE480518");
	strcat(apdu , divGene);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "80FA050000");
	strcat(apdu , "00000000000000000000000000000000" ); // mac init
	strcpy( apdu + 10 + 32 , cmpApdu ) ;
	Padding(apdu + 10);
	ret = strlen(apdu + 10) / 2;
	u.UINTToBin(ret , sw);
	u.BinToHexstr((unsigned char *)resp ,(unsigned char *) sw + 1, 1 );
	memcpy(apdu + 8 , resp , 2);

	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (memcmp(sw , "\x36\x31" , 2) != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C00000");
	strcat(apdu , sw + 2);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcat(cmpApdu , resp );
	ret  = rd.RF_Send(cmpApdu , resp, sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_ER_DF03EF05ERR;	

	return IRV_OK;
}

//住院信息文件
//1. nStyle可以取以下4个值。
// #define NO_style			0x00
// #define AN_style			0x01
// #define CN_style			0x0F
// #define B_style			0xFF
//2.如果全读全写，比如读写整个EE01的数据，那么 nStyle=NO_style, pos=0, Len=1639(不需要操作EEXX文件的最后2项)
//	文件最后2项为“签名”操作时才写入的数据。
//3.如果读写具体数据项，pos\len\style的取值请参考相关文档。
//4.pos\len取值的单位是卡内部存储空间的字节的大小
//5.如果卡内存储数据的类型是CN_style和B_style， szData的size需要大于(卡内存储空间的2倍+1)

MHC_CARDINTERFACE_API int __stdcall iR_DF03EEInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  )
{
	char apdu[300];
	char resp[300];
	char sw[5];
	
	if ((nPos + nLen) > 1639)
		return IRV_PARA_ERR;
	if (nRecorderNo > 3)
		return IRV_PARA_ERR;

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF03 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//判断记录标记是否可用
/*	strcpy(apdu , "00b2010400");
	u.intTo1ByteHex (nRecorderNo , apdu + 4);
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;
	*/
//	if (strcmp( resp , "FF") == 0 )
//		return IRV_RCINVALID;
	
	//select bin file
	strcpy(apdu , "00A4000002EE00");
	u.intTo1ByteHex (nRecorderNo , apdu + 12);
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;

	//临时数据
	char * pdata = (char *)malloc((nLen * 2 + 2)*sizeof(char));
	memset(pdata , 0 , sizeof(pdata));
	//数据后续总长度
	int iend = nPos + nLen;
	
	int a = (nLen - nLen % 0x80) / 0x80 ;
	//
	for (int i = 0 ; i < a ; i++ )
	{
		memcpy (resp, "\x00\xb0\x00\x00\x80" , 5);
		ret = nPos + i * 0x80; //偏移地址
		u.UINTToBin(ret , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_RD_BINERR;	
		}
		strcat(pdata , resp);
	}
	//last block
	memcpy (resp, "\x00\xb0\x00\x00\x80" , 5);
	ret = nPos + i * 0x80;
	u.UINTToBin(ret , resp + 2);
	resp[4] = (nLen  % 0x80) ;
	u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
	apdu[10] = 0;
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_BINERR;	
	}
	strcat(pdata , resp);;
	
	//数据输出
	switch (nStyle)
	{
	case NO_style:
	case B_style:
		strcpy(szData , pdata);
		break;
	case AN_style:
		u.HexstrToBin ((unsigned char*)szData , (unsigned char*)pdata , strlen(pdata));
		break;
	case CN_style:			
		for ( i = 0 ; i < strlen(pdata) ;i++)
		{
			if (pdata[i] == 'F')
			{
				pdata[i] = 0;break;
			}
		}
		strcpy(szData , pdata);
		break;
	}
	free(pdata);
	return IRV_OK;
}

//写入 EE00 文件
MHC_CARDINTERFACE_API int __stdcall iW_DF03EEInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  )
{
	char apdu[300];
	char resp[300];
	char sw[5];
	
	if ((nPos + nLen) > 1639)
		return IRV_PARA_ERR;
	if (nRecorderNo > 3)
		return IRV_PARA_ERR;

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF05");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthUK(UK_DF03_1 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//判断记录标记是否可用
//	strcpy(apdu , "00b2010400");
//	u.intTo1ByteHex (nRecorderNo , apdu + 4);
//	ret = rd.RF_Send (apdu , resp , sw);
//	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
//		return IRV_RD_RCDERR;
//	
//	if (strcmp( resp , "FF") == 0 )
//		return IRV_RCINVALID;
	
	//select bin file
	strcpy(apdu , "00A4000002EE00");
	u.intTo1ByteHex (nRecorderNo , apdu + 12);
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;

	//临时数据
	char * pdata = (char *)malloc((nLen * 2 + 2)*sizeof(char));
	memset(pdata , 0 , sizeof(pdata));
	
	//准备数据
	switch (nStyle)
	{
	case NO_style:
	case CN_style:
	case B_style:
		strcpy( pdata , szData );
		break;
	case AN_style:
		u.BinToHexstr((unsigned char*)pdata ,  (unsigned char*)szData ,  nLen);
		break;
	}

	BinDataPadding(nStyle , pdata , nLen);
	//数据后续总长度
	int iend = nPos + nLen;
	
	int a = (nLen - nLen % 0x80) / 0x80 ;
	//
	for (int i = 0 ; i < a ; i++ )
	{
		//apdu head
		memcpy (resp, "\x00\xd6\x00\x00\x80" , 5);
		ret = nPos + i * 0x80; //偏移地址
		u.UINTToBin(ret , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		//data
		memset(resp , 0 , sizeof(resp));
		memcpy(resp , pdata + (i * 0x80) * 2 , 0x80 * 2 );
		
		strcat(apdu , resp);
		ret = rd.RF_Send(apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_WR_BINERR;	
		}
	}
	//last block
	memcpy (resp, "\x00\xd6\x00\x00\x80" , 5);
	ret = nPos + i * 0x80;
	u.UINTToBin(ret , resp + 2);
	resp[4] = (nLen  % 0x80) ;
	u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
	apdu[10] = 0;
	memset(resp , 0 , sizeof(resp));
	memcpy(resp , pdata + (i * 0x80) * 2 , 0x80 * 2 );
	strcat(apdu , resp);
	ret = rd.RF_Send(apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_WR_BINERR;	
	}

	free(pdata);
	return IRV_OK;
}


//门诊信息文件 len = 3013
MHC_CARDINTERFACE_API int __stdcall iR_DF03EDInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  )
{
	char apdu[300];
	char resp[300];
	char sw[5];
	
	if ((nPos + nLen) > 3113)
		return IRV_PARA_ERR;
	if (nRecorderNo > 5)
		return IRV_PARA_ERR;

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthIRK(RK_DF03 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//判断记录标记是否可用
/*	strcpy(apdu , "00b2010400");
	u.intTo1ByteHex (nRecorderNo , apdu + 4);
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;*/
	
//	if (strcmp( resp , "FF") == 0 )
//		return IRV_RCINVALID;
	
	//select bin file
	strcpy(apdu , "00A4000002ED00");
	u.intTo1ByteHex (nRecorderNo , apdu + 12);
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;

	//临时数据
	char * pdata = (char *)malloc((nLen * 2 + 2)*sizeof(char));
	memset(pdata , 0 , sizeof(pdata));
	//数据后续总长度
	int iend = nPos + nLen;
	
	int a = (nLen - nLen % 0x80) / 0x80 ;
	//
	for (int i = 0 ; i < a ; i++ )
	{
		memcpy (resp, "\x00\xb0\x00\x00\x80" , 5);
		ret = nPos + i * 0x80; //偏移地址
		u.UINTToBin(ret , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_RD_BINERR;	
		}
		strcat(pdata , resp);
	}
	//last block
	memcpy (resp, "\x00\xb0\x00\x00\x80" , 5);
	ret = nPos + i * 0x80;
	u.UINTToBin(ret , resp + 2);
	resp[4] = (nLen % 0x80) ;
	u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
	apdu[10] = 0;
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_RD_BINERR;	
	}
	strcat(pdata , resp);;
	
	//数据输出
	switch (nStyle)
	{
	case NO_style:
	case B_style:
		strcpy(szData , pdata);
		break;
	case AN_style:
		u.HexstrToBin ((unsigned char*)szData , (unsigned char*)pdata , strlen(pdata));
		break;
	case CN_style:			
		for ( i = 0 ; i < strlen(pdata) ;i++)
		{
			if (pdata[i] == 'F')
			{
				pdata[i] = 0;break;
			}
		}
		strcpy(szData , pdata);
		break;
	}
	free(pdata);
	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF03EDInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  )
{
	char apdu[300];
	char resp[300];
	char sw[5];
	
	if ((nPos + nLen) > 3013)
		return IRV_PARA_ERR;
	if (nRecorderNo > 5)
		return IRV_PARA_ERR;

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(apdu , resp );
	if (ret != IRV_OK)
		return ret;
	
	ret = SelectFile(SLOT_USER , "DDF1" ,"DF03","EF06");
	if (ret != IRV_OK)
		return ret;
	
	//认证用户卡 IRK
	ret = AuthUK(UK_DF03_1 ,apdu , resp);
	if (ret != IRV_OK)
		return ret;
	
	//判断记录标记是否可用
//	strcpy(apdu , "00b2010400");
//	u.intTo1ByteHex (nRecorderNo , apdu + 4);
//	ret = rd.RF_Send (apdu , resp , sw);
//	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
//		return IRV_RD_RCDERR;
//	
//	if (strcmp( resp , "FF") == 0 )
	//	return IRV_RCINVALID;
	
	//select bin file
	strcpy(apdu , "00A4000002ED00");
	u.intTo1ByteHex (nRecorderNo , apdu + 12);
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;

	//临时数据
	char * pdata = (char *)malloc((nLen * 2 + 2)*sizeof(char));
	memset(pdata , 0 , sizeof(pdata));
	
	//准备数据
	switch (nStyle)
	{
	case NO_style:
	case CN_style:
	case B_style:
		strcpy( pdata , szData );
		break;
	case AN_style:
		u.BinToHexstr((unsigned char*)pdata ,  (unsigned char*)szData ,  nLen);
		break;
	}
	BinDataPadding(nStyle , pdata , nLen);
	//数据后续总长度
	int iend = nPos + nLen;
	
	int a = (nLen - nLen % 0x80) / 0x80 ;
	//
	for (int i = 0 ; i < a ; i++ )
	{
		//apdu head
		memcpy (resp, "\x00\xd6\x00\x00\x80" , 5);
		ret = nPos + i * 0x80; //偏移地址
		u.UINTToBin(ret , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		apdu[10] = 0;
		//data
		memset(resp , 0 , sizeof(resp));
		memcpy(resp , pdata + (i * 0x80) * 2 , 0x80 * 2 );
		strcat(apdu , resp);

		ret = rd.RF_Send(apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			return IRV_WR_BINERR;	
		}
	}
	//last block
	memcpy (resp, "\x00\xd6\x00\x00\x80" , 5);
	ret = nPos + i * 0x80;
	u.UINTToBin(ret , resp + 2);
	resp[4] = ( nLen % 0x80) ;
	u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
	apdu[10] = 0;
	memset(resp , 0 , sizeof(resp));
	memcpy(resp , pdata + (i * 0x80) * 2 , 0x80 * 2 );

	strcat(apdu , resp);
	ret = rd.RF_Send(apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
	{
		return IRV_WR_BINERR;	
	}

	free(pdata);
	return IRV_OK;
}

int findChar(int StartAddr,char * data,char c)
{
	int len = strlen(data);
	for(int i=StartAddr;i<len;i++)
	{
		if(data[i]==c)
		{
			return i;
		}
		else
			continue;
	}
	if(i==len)
		return -1;
}

/*
		int dataid ;		//数据项ID
	char FileID[3];		//所在文件ID
	char ADFID[3];		//所在应用目录ID
	int iDataLen;		//数据项总长度
	BYTE cCoding;		//数据项编码方式 AN/CN/B
	BYTE cFiletype;		//文件类型		BIN/REC
	BYTE cUpdateAcc;	//文件的更新权限	UK
*/

MHC_CARDINTERFACE_API int __stdcall iW_DF03EE_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData											  
							  )//全写
{
	unsigned char tempdata[1800]={0};
	int len = strlen(szData);
	int start =0;//传入数据偏移量
	int post=0;//待写入数据量的偏移量
	unsigned char temp[400]={0};
	for(int i=0;i<len;i++)
	{
		if(i==0x94)
		{
			int n;
		}
		int s = findChar(start,szData,'|');// 1111|23456
		if(s<0)//最后一段/唯一的一段
		{
			memset(temp,0,400);
			memcpy(temp,szData+start,len-start);
			if(_stDataFileMAP[i+64].cCoding==CN_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+64].iDataLen*2);
			}
			else if(_stDataFileMAP[i+64].cCoding==AN_style)
			{
				memcpy(tempdata+post,temp,_stDataFileMAP[i+64].iDataLen);
			}
			else if(_stDataFileMAP[i+64].cCoding==B_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+64].iDataLen*2);
			}
			post+=_stDataFileMAP[i+64].iDataLen;
			break;
		}
		else
		{
			memset(temp,0,400);
			memcpy(temp,szData+start,s-start);
			if(_stDataFileMAP[i+64].cCoding==CN_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+64].iDataLen*2);
			}
			else if(_stDataFileMAP[i+64].cCoding==AN_style)
			{
				memcpy(tempdata+post,temp,_stDataFileMAP[i+64].iDataLen);
			}
			else if(_stDataFileMAP[i+64].cCoding==B_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+64].iDataLen*2);
			}
			start=s;
			start+=1;
			post+=_stDataFileMAP[i+64].iDataLen;
		}
		if(i==0x92)
				break;
	}
	return  iW_DF03EEInfo(hDev, nRecorderNo, (char*)tempdata,0, 1639, AN_style );
	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iR_DF03EE_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData											  
							  )
{
	unsigned char tempdata[1800]={0};
//	int len = strlen(szData);
	int start =0;//传出数据偏移量
	int post=0;//读出的数据量的偏移量
	char temp[400]={0};

	int re = iR_DF03EEInfo(hDev, nRecorderNo,(char*)tempdata,0, 1639, AN_style);
	if(re!=0)
		return re;
	for(int i=0;i<147;i++)
	{
		if(i!=0)
			strcat(szData,"|");
		memset(temp,0,400);
		if(_stDataFileMAP[i+64].cCoding==CN_style)
		{
			u.BinToHexstr((unsigned char*)temp , tempdata+post , _stDataFileMAP[i+64].iDataLen);
			strcat(szData,temp);
		}
		else if(_stDataFileMAP[i+64].cCoding==AN_style)
		{
			memcpy(temp,tempdata+post,_stDataFileMAP[i+64].iDataLen);
			strcat(szData,temp);
		}
		else if(_stDataFileMAP[i+64].cCoding==B_style)
		{
			u.BinToHexstr((unsigned char*)temp , tempdata+post , _stDataFileMAP[i+64].iDataLen);
			strcat(szData,temp);
		}
		post+=_stDataFileMAP[i+64].iDataLen;
	}

	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iW_DF03ED_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData											  
							  )//全写
{
	unsigned char tempdata[6000]={0};
	int len = strlen(szData);
	int start =0;//传入数据偏移量
	int post=0;//待写入数据量的偏移量
	unsigned char temp[400]={0};
	for(int i=0;i<len;i++)
	{
		int s = findChar(start,szData,'|');// 1111|23456
		if(s<0)//最后一段/唯一的一段
		{
			memset(temp,0,400);
			memcpy(temp,szData+start,len-start);
			if(_stDataFileMAP[i+213].cCoding==CN_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+213].iDataLen*2);
			}
			else if(_stDataFileMAP[i+213].cCoding==AN_style)
			{
				memcpy(tempdata+post,temp,_stDataFileMAP[i+213].iDataLen);
			}
			else if(_stDataFileMAP[i+213].cCoding==B_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+213].iDataLen*2);
			}
			post+=_stDataFileMAP[i+213].iDataLen;
			break;
		}
		else
		{
			memset(temp,0,400);
			memcpy(temp,szData+start,s-start);
			if(_stDataFileMAP[i+213].cCoding==CN_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+213].iDataLen*2);
			}
			else if(_stDataFileMAP[i+213].cCoding==AN_style)
			{
				memcpy(tempdata+post,temp,_stDataFileMAP[i+213].iDataLen);
			}
			else if(_stDataFileMAP[i+213].cCoding==B_style)
			{
				u.HexstrToBin(tempdata+post , temp , _stDataFileMAP[i+213].iDataLen*2);
			}
			start=s;
			start+=1;
			post+=_stDataFileMAP[i+213].iDataLen;
		}
		if(i==0xa9)
				break;
	}
	return  iW_DF03EDInfo(hDev, nRecorderNo, (char*)tempdata,0, 3013, AN_style );

	return IRV_OK;
}

MHC_CARDINTERFACE_API int __stdcall iR_DF03ED_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData											  
							  )
{
	unsigned char tempdata[3100]={0};
//	int len = strlen(szData);
	int start =0;//传出数据偏移量
	int post=0;//读出的数据量的偏移量
	char temp[400]={0};

	int re = iR_DF03EDInfo(hDev, nRecorderNo,(char*)tempdata,0, 3013, AN_style);
	if(re!=0)
		return re;
	for(int i=0;i<170;i++)
	{
		if(i!=0)
			strcat(szData,"|");
		memset(temp,0,400);
		if(_stDataFileMAP[i+213].cCoding==CN_style)
		{
			u.BinToHexstr((unsigned char*)temp , tempdata+post , _stDataFileMAP[i+213].iDataLen);
			strcat(szData,temp);
		}
		else if(_stDataFileMAP[i+213].cCoding==AN_style)
		{
			memcpy(temp,tempdata+post,_stDataFileMAP[i+213].iDataLen);
			strcat(szData,temp);
		}
		else if(_stDataFileMAP[i+213].cCoding==B_style)
		{
			u.BinToHexstr((unsigned char*)temp , tempdata+post , _stDataFileMAP[i+213].iDataLen);
			strcat(szData,temp);
		}
		post+=_stDataFileMAP[i+213].iDataLen;
	}

	return IRV_OK;
}

//按数据项序号读数据
MHC_CARDINTERFACE_API DWORD __stdcall wsc_GetCardInfo(HANDLE hCard,void *pvSelect,int nItem)
{	
	P_ITEMSELECT pItems = (P_ITEMSELECT) pvSelect;
	ITEMSELECT item;
	P_ITEMSELECT pitem = &item;
	
	char apdu[100];
	char resp[256];
	char cardNo[17];
	char cityCode[17];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(cardNo , cityCode );

	for (int i = 0 ;i < nItem ; i++) 
	{
		memcpy(pitem , &pItems[i] , sizeof(ITEMSELECT));
		
		if (!(getDFEFfromFILEMAP(pitem , apdu , resp)))
		{
			//*(pItems[i].pdwErrCode) = IRV_PARA_ERR;
			return IRV_PARA_ERR;
			continue;
		}
		
		//判断当前DF是否匹配
		if (isWorkingDFID(apdu)) 
		{
			if (isWorkingEFID(resp))
			{/*nothing to do*/	}
			else
			{//选择EF文件
				ret = SelectFile(SLOT_USER , NULL ,NULL,resp);
				if (ret != IRV_OK)
					//{*(pItems[i].pdwErrCode) = ret;}
					return ret;
			}
		}
		else
		{
			//选择DF + EF
			ret = SelectFile(SLOT_USER , NULL ,apdu,resp);
			if (ret != IRV_OK)
				//{*(pItems[i].pdwErrCode) = ret;}
				return ret;

			//获取读权限			
			ret = getReadACCbyADF(apdu , cardNo , cityCode);
			if (ret != IRV_OK)
				//{*(pItems[i].pdwErrCode) = ret;}			
				return ret;
		}
		
		//依据文件类型 等参数 读取内容 // 依据编码输出 或 返回错误值都在函数中处理
		ret = RdFileByItemStruct(pitem);
		if (ret != IRV_OK)
			return ret;
	}

	return IRV_OK;
}

//按数据项序号写数据
MHC_CARDINTERFACE_API DWORD __stdcall wsc_PutCardInfo(HANDLE hCard,void *pvSelect,int nItem)
{
	P_ITEMSELECT pItems = (P_ITEMSELECT) pvSelect;
	ITEMSELECT item;
	P_ITEMSELECT pitem = &item;
	
	char apdu[100];
	char resp[256];
	char cardNo[17];
	char cityCode[17];

	//获取用户卡卡号，城市代码
	int ret = GetCNandCityCode(cardNo , cityCode );

	for (int i = 0 ;i < nItem ; i++) 
	{
		memcpy(pitem , &pItems[i] , sizeof(ITEMSELECT));
		
		if (!(getDFEFfromFILEMAP(pitem , apdu , resp)))
		{
			//*(pItems[i].pdwErrCode) = IRV_PARA_ERR;
			return IRV_PARA_ERR;
			continue;
		}
		
		//判断当前DF是否匹配
		if (isWorkingDFID(apdu)) 
		{
			if (isWorkingEFID(resp))
			{/*nothing to do*/	}
			else
			{//选择EF文件
				ret = SelectFile(SLOT_USER , NULL ,NULL,resp);
				if (ret != IRV_OK)
					//{*(pItems[i].pdwErrCode) = ret;}
					return ret;
				//获取文件更新权限			
				ret = getUpdateACCbyADF(pitem->wItemFlag , cardNo , cityCode);
				if (ret != IRV_OK)
					//{*(pItems[i].pdwErrCode) = ret;continue;}	
					return ret;
			}
		}
		else
		{
			//选择DF + EF
			ret = SelectFile(SLOT_USER , NULL ,apdu,resp);
			if (ret != IRV_OK)
				//{*(pItems[i].pdwErrCode) = ret;continue;}
				return ret;

			//获取文件更新权限			
			ret = getUpdateACCbyADF(pitem->wItemFlag , cardNo , cityCode);
			if (ret != IRV_OK)
				//{*(pItems[i].pdwErrCode) = ret;continue;}			
				return ret;
		}
		
		//依据文件类型 等参数 读取内容 // 依据编码输出 或 返回错误值都在函数中处理
		UdFileByItemStruct(pitem);
	}

	return IRV_OK;
}

MHC_CARDINTERFACE_API HANDLE __stdcall OpenDevice(int port)
{
	int ret = iDOpenPort();
	if (ret != IRV_OK)
		return 0;
	
	char atr[255];
	ret = PowerOn((HANDLE)(Reader::m_hReader),SLOT_USER , atr);
	if (ret != IRV_OK)
		return 0;
	//重置工作目录
	resetWorkingADF();

	return (HANDLE)rd.m_hReader;
}

MHC_CARDINTERFACE_API DWORD __stdcall	CloseDevice(HANDLE hCard)
{
	iDClosePort();
	return IRV_OK;
}

MHC_CARDINTERFACE_API DWORD  __stdcall SendAPDU (
				HANDLE hDev,
				unsigned char bySlot,
				unsigned char * pbyC_Command,
				unsigned long byLen,
				unsigned char * pbyR_Command,
				int * pnRes )
{

	char cmd[300]={0};
	char resp[300]={0};
	char sw[30]={0};

	u.BinToHexstr((unsigned char*)cmd , pbyC_Command , byLen) ;

	int ret=0;
	if(bySlot == SLOT_USER)
		ret = rd.RF_Send (cmd , resp , sw);
	else
		ret = rd.PSAM_Send (cmd , resp , sw);

	int len = strlen((char *)resp);
	unsigned char res[8]={0};
//	if(resp==NULL)
	u.HexstrToBin((unsigned char*)pbyR_Command , (unsigned char*)resp , strlen((char *)resp));
	
	u.HexstrToBin((unsigned char*)res , (unsigned char*)sw , strlen((char *)sw));

	memcpy(pbyR_Command+len/2,res,2);
//	else
	*pnRes = len/2;
	if(ret!=0 )
		return -1;

	

/*
	u.HexstrToBin(send , (unsigned char*)_APDU_CMD , strlen((char *)_APDU_CMD));
	
	retval = ICC_Reader_Application(Reader::m_hReader,_SLOT,len , send  ,resp);
	if (retval<2)
		return RD_IC_NO_RESP;

	u.BinToHexstr((unsigned char*)_APDU_Responce , resp , retval - 2) ;
	u.BinToHexstr((unsigned char*)_SW , resp + retval - 2 , 2);


	int re =0;

	if(bySlot == SLOT_USER)
		re = PICC_Reader_Application(Reader::m_hReader,byLen,pbyC_Command,pbyR_Command);
	else
		re = ICC_Reader_Application(Reader::m_hReader,bySlot,byLen,pbyC_Command,pbyR_Command);
	if(re<2)
		return re;
	else
		*pnRes = re;*/
	return 0;
	
							 
}

/*
函数：wsc_SM3Digest
功能：对输入数据进行SM3哈希运算
	参数说明：
	hCard		: [in] 设备句柄
	pbData		: [in] 待哈希数据
	nDataLen	: [in] 待哈希数据长度
	pbHash		: [out]哈希结果
	pbHashLen	: [out]指向哈希结果长度的指针
	返回值：如果成功，返回0，失败返回相应的错误码。
*/

MHC_CARDINTERFACE_API DWORD __stdcall SM3Digest(HANDLE hCard, BYTE *pbData, unsigned int nDataLen,  BYTE *pbHash, BYTE *pbHashLen)
{
	return 0;
}

/*
函数:wsc_SM2SignHash
功能：对输入数据进行SM2签名运算
	参数说明：
	hCard		: [in] 设备句柄
	pbData		: [in] 待签名数据，原始数据的哈希结果
	bLen		: [in] 待签名哈希数据长度
	pbSignedData: [out]签名结果
	pbLength	: [out]指向哈希结果长度的指针
	返回值：如果成功，返回0，失败返回相应的错误码。

说明：在执行签名前，需要wsc_VerifyPin验证PIN获取相应的权限
*/
DWORD __stdcall SM2SignHash(HANDLE hCard,
								BYTE *pbData,
								BYTE bLen,
								BYTE *pbSignedData,
								BYTE *pbLength)
{
	return 0;
}


//该函数用于修改SAM卡PIN码
//oldPin：SAM卡的现在pin码
//newPin：SAM卡的新pin码
MHC_CARDINTERFACE_API int __stdcall iChange_Pin(int hDev,
												  char *oldPin, 
												  char *newPin)
{
	char apdu[100];
	char resp[50];
	char sw[5] ;
	
	if ((strlen(oldPin) % 2) != 0)
		return IRV_PARA_ERR;
	if ((strlen(newPin) % 2) != 0)
		return IRV_PARA_ERR;

	int ret = rd.PSAM_Reset(SLOT_PSAM,resp);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;
	
	//PSAM 
	ret = SelectFile (SLOT_PSAM  , "DF01" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	strcpy(apdu , "805E010000");
	ret = (strlen(oldPin) / 2 + strlen(newPin) / 2) + 1;
	u.intTo1ByteHex(ret , apdu + 8);
	strcat(apdu , oldPin);
	strcat(apdu , "FF");
	strcat(apdu , newPin);

	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	return IRV_OK;
}

//该函数取得SAM卡片公共信息文件
//info：指向存放公共信息的存储区的指针
//存储格式如下：
	//1~10 SAM卡序列号
	//11 SAM卡版本号
	//12密钥卡类型
	//13指令集版本
	//14发卡方自定义FCI数据
MHC_CARDINTERFACE_API int __stdcall iReader_SAM_Public(int hDev,
														 char* info)
{
	char apdu[100];
	char resp[250];
	char sw[5] ;
	
	int ret = rd.PSAM_Reset(SLOT_PSAM,resp);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;
	
	//PSAM 
	ret = SelectFile (SLOT_PSAM  , "3F00" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	ret = SelectFile (SLOT_PSAM  , "0015" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	strcpy(apdu  , "00B000000E");
	ret = rd.PSAM_Send(apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy(info , resp);

	return IRV_OK;
}

//该函数取得SAM卡片的终端信息文件
//info：指向存放终端信息的存储区的指针
//存储格式如下：
//1~6	终端机编号（1字节省编码+1字节市编码+1字节发卡机构编码+3字节序列号）
MHC_CARDINTERFACE_API int __stdcall iReader_SAM_Terminal(int hDev,
														   char* info)
{
	char apdu[100];
	char resp[250];
	char sw[5] ;
	
	int ret = rd.PSAM_Reset(SLOT_PSAM,resp);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;
	//PSAM 
	ret = SelectFile (SLOT_PSAM  , "3F00" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	ret = SelectFile (SLOT_PSAM  , "0016" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	strcpy(apdu  , "00B0000006");
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy(info , resp);

	return IRV_OK;	
}

//该函数取得SAM卡片的居民健康卡应用的公共信息文件
//info：指向存放终端信息的存储区的指针
//存储格式如下：
	//1	全国居民健康卡应用密钥索引号
	//2~9	应用发行者标识
	//10~17	应用接收者标识
	//18~21	应用启用日期
	//22~25	应用有效日期
MHC_CARDINTERFACE_API int __stdcall  iReader_SAM_PublicApp(int hDev,
															 char* info)
{
	char apdu[100];
	char resp[250];
	char sw[5] ;
	
	int ret = rd.PSAM_Reset(SLOT_PSAM,resp);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;
	
	//PSAM 
	ret = SelectFile (SLOT_PSAM  , "DF01" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	ret = SelectFile (SLOT_PSAM  , "001A" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	strcpy(apdu  , "00B0000019");

	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy(info , resp);
	return IRV_OK;	
}

//该函数取得SAM卡片的居民健康卡发卡机构证书文件
//info：指向存放终端信息的存储区的指针
//存储格式如下：
//1~180	发卡机构证书
MHC_CARDINTERFACE_API int __stdcall  iReader_SAM_OrgCertificate(int hDev,
															 char* info)
{
	char apdu[100];
	char resp[400];
	char sw[5] ;
	
	int ret = rd.PSAM_Reset(SLOT_PSAM,resp);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;
	
	//PSAM 
	ret = SelectFile (SLOT_PSAM  , "DF01" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	ret = SelectFile (SLOT_PSAM  , "001B" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	strcpy(apdu  , "00B00000B4");
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	u.HexstrToBin((unsigned char*)info , (unsigned char*)resp , strlen(resp));
	return IRV_OK;	
}

//该函数取得SAM卡片的SAM卡机构证书
//info：指向存放终端信息的存储区的指针
//存储格式如下：
//1~190	SAM卡机构证书
MHC_CARDINTERFACE_API int __stdcall  iReader_SAM_Certificate(int hDev,
															 char* info)
{
	char apdu[100];
	char resp[400];
	char sw[5] ;

	int ret = rd.PSAM_Reset(SLOT_PSAM,resp);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;
	
	//PSAM 
	ret = SelectFile (SLOT_PSAM  , "DF01" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	ret = SelectFile (SLOT_PSAM  , "001C" , NULL, NULL);
	if (ret != IRV_OK)
		return IRV_PSAM_ERR;

	strcpy(apdu  , "00B00000BE");
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	u.HexstrToBin((unsigned char*)info , (unsigned char*)resp , strlen(resp));

	return IRV_OK;	
}