// HD_WHInterface.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "HD_WHInterface.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
    return TRUE;
}

unsigned long ChangeNum(char* str,int length)   //十六进制字符串转十进制数值   
{      
    char  revstr[16]={0};  //根据十六进制字符串的长度，这里注意数组不要越界   
    int   num[16]={0};      
    int   count=1;      
    unsigned long  result=0;      
    strcpy(revstr,str);      
    for   (int i=length-1;i>=0;i--)      
    {      
        if ((revstr[i]>='0') && (revstr[i]<='9'))      
            num[i]=revstr[i]-48;//字符0的ASCII值为48   
        else if ((revstr[i]>='a') && (revstr[i]<='f'))      
            num[i]=revstr[i]-'a'+10;      
        else if ((revstr[i]>='A') && (revstr[i]<='F'))      
            num[i]=revstr[i]-'A'+10;      
        else      
            num[i]=0;    
        result=result+num[i]*count;      
        count=count*16;//十六进制(如果是八进制就在这里乘以8)       
    }      
    return result;      
} 
int __stdcall IC_GetData(char *dataOut,char *pErr,int TimeOut)
{
	int i=0;
	int count=TimeOut*10/3;
	long ReaderHandle=ICC_Reader_Open("USB1");
	//i=ICC_DispSound(ReaderHandle,2,1);
	CString temp;
	//处理磁条卡
	//	unsigned char rlen=0;
	//	char DataBuffer[400]={0};
	//	i=Rcard(ReaderHandle,TimeOut,2,&rlen,DataBuffer);
	//	if(DataBuffer[0]!=NULL)
	//	{
	//		temp.Format("磁条卡:%s",DataBuffer);
	//		memcpy(dataOut,temp.GetBuffer(0),temp.GetLength());
	//		temp.ReleaseBuffer();
	//		ICC_Reader_Close(ReaderHandle);
	//		return 0;
	//	}
	/////////////////////////////////////////////
	i=ICC_Reader_DisCardType(ReaderHandle);
	if(i>0)
	{
		//this->SetDlgItemText(IDC_EDIT_DATA,"接触CPU卡");
		unsigned char cmd[100]={0};
		unsigned char Response[100]={0};
		///////////////////////////////////
		char KH[100]={0};
		unsigned char FKRQ[10]={0};
		unsigned char KYXQ[10]={0};
		unsigned char SHBZHM[50]={0};
		///////////////////////////////////
		i=ICC_Reader_PowerOn(ReaderHandle,0x01,Response);
		if(i <= 0)
		{
			temp.Format("社保卡上电失败,错误代码:%d",i);
			ICC_Reader_Close(ReaderHandle);
			strcpy(pErr,temp.GetBuffer(0));
			temp.ReleaseBuffer();
			return i;
		}
		//选SSSE
		memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF", 20);
		i= ICC_Reader_Application(ReaderHandle,0x01, 20, cmd, Response);
		if(Response[i-2]!=0x61 && Response[i-2]!=0x90)
		{
			temp.Format("社保卡选SSSE失败,错误代码:%d",i);
			strcpy(pErr,temp.GetBuffer(0));
			ICC_Reader_PowerOff(ReaderHandle,0x01);
			ICC_Reader_Close(ReaderHandle);
			return i;
		}
		//选SSSE/EF05
		memset(cmd, 0, 20);
		memcpy(cmd, "\x00\xA4\x02\x00\x02\xEF\x05", 7);
		i = ICC_Reader_Application(ReaderHandle, 0x01, 7, cmd, Response);
		if(i<0 || Response[i-2]!=0x90)
		{
			temp.Format("社保卡选SSSE-EF05失败,错误代码:%d",i);
			strcpy(pErr,temp.GetBuffer(0));
			ICC_Reader_PowerOff(ReaderHandle,0x01);
			ICC_Reader_Close(ReaderHandle);
			return i;
		}
		//卡号
		memset(cmd, 0, 7);
		memset(Response, 0, 100);
		memcpy(cmd, "\x00\xB2\x07\x04\x0B", 5);
		i = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
		if(i<0 && Response[i-2]!=0x90)
		{
			temp.Format("社保卡读取卡号失败,错误代码:%d",i);
			strcpy(pErr,temp.GetBuffer(0));
			ICC_Reader_PowerOff(ReaderHandle,0x01);
			ICC_Reader_Close(ReaderHandle);
			return i;
		}
		memcpy(KH, Response+2,i-4);
		//发卡日期
		memset(cmd, 0, 7);
		memset(Response, 0, 100);
		memcpy(cmd, "\x00\xB2\x05\x04\x06", 5);
		i = ICC_Reader_Application(ReaderHandle,0x01, 5, cmd, Response);
		if(i<0 && Response[i-2]!=0x90)
		{
			temp.Format("社保卡读取发卡日期失败,错误代码:%d",i);
			strcpy(pErr,temp.GetBuffer(0));
			ICC_Reader_PowerOff(ReaderHandle,0x01);
			ICC_Reader_Close(ReaderHandle);
			return i;
		}
		HexToStr(Response+2,4,FKRQ);
		//卡有效期
		memset(cmd, 0, 7);
		memset(Response, 0, 100);
		memcpy(cmd, "\x00\xB2\x06\x04\x06", 5);
		i = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
		if(i<0 && Response[i-2]!=0x90)
		{
			temp.Format("社保卡读取有效期失败,错误代码:%d",i);
			strcpy(pErr,temp.GetBuffer(0));
			ICC_Reader_PowerOff(ReaderHandle, 0x01);
			ICC_Reader_Close(ReaderHandle);
			return i;
		}
		HexToStr(Response+2,4,KYXQ);
		//选SSSE/EF06
		memset(cmd, 0, 20);
		memset(Response, 0, 100);
		memcpy(cmd, "\x00\xA4\x02\x00\x02\xEF\x06", 7);
		i = ICC_Reader_Application(ReaderHandle, 0x01, 7, cmd, Response);
		if(i<0 || Response[i-2]!=0x90)
		{
			temp.Format("选SSSE/EF06失败,错误代码:%d",i);
			strcpy(pErr,temp.GetBuffer(0));
			ICC_Reader_PowerOff(ReaderHandle, 0x01);
			ICC_Reader_Close(ReaderHandle);
			return i;
		}
		//社会保障号码
		memset(cmd, 0, 7);
		memset(Response, 0, 100);
		memcpy(cmd, "\x00\xB2\x08\x00\x14", 5);
		i = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
		if(i<0 && Response[i-2]!=0x90)
		{
			temp.Format("社保卡读取身份证(社保号)失败,错误代码:%d",i);
			strcpy(pErr,temp.GetBuffer(0));
			ICC_Reader_PowerOff(ReaderHandle, 0x01);
			ICC_Reader_Close(ReaderHandle);
			return i;
		}
		memcpy(SHBZHM, Response+2,i-4);
		temp.Format("社保卡:%s|%s|%s|%s",KH,FKRQ,KYXQ,SHBZHM);
		strcpy(dataOut,temp.GetBuffer(0));
		ICC_Reader_PowerOff(ReaderHandle, 0x01);
		ICC_Reader_Close(ReaderHandle);
		return 0;
	}
	else
	{
		//非接触卡
		//身份证
		i=PICC_Reader_ID_Request(ReaderHandle);//身份证寻卡
		if(i==0)
		{
			i=PICC_Reader_ID_Select(ReaderHandle);//身份证选卡
			if(i)
			{
				temp.Format("身份证选卡失败,错误代码:%d",i);
				strcpy(pErr,temp.GetBuffer(0));
				ICC_Reader_Close(ReaderHandle);
				return i;
			}
			char pName[50]={0};
			char pSex[10]={0};
			char pNation[10]={0};
			char pBirth[50]={0};
			char pAddress[100]={0};
			char pCertNo[50]={0};
			char pDepartment[100]={0};
			char pEffectData[50]={0};
			char pExpire[20]={0};
			char pErrMsg[50]={0};
			
			char pic[77726]={0};
			i=PICC_Reader_ReadIDInfo(ReaderHandle,pic,pName,pSex,pNation,pBirth,pAddress,pCertNo, 
				pDepartment ,pEffectData,pExpire,pErrMsg);
			//			i=PICC_Reader_ReadIDMsg(ReaderHandle,"zp.bmp",pName,pSex,pNation,pBirth,pAddress,pCertNo, 
			//				pDepartment ,pEffectData,pExpire,pErrMsg);
			if(i) 
			{
				temp.Format("读取身份证信息失败,错误代码:%d",i);
				strcpy(pErr,temp.GetBuffer(0));
				ICC_Reader_Close(ReaderHandle);
				return i;
			}
			temp.Format("身份证信息:%s|%s|%s|%s|%s|%s|%s|%s|%s",pName,pSex,pNation,pBirth,pAddress,pCertNo, 
				pDepartment ,pEffectData,pExpire);
			strcpy(dataOut,temp.GetBuffer(0));
			ICC_Reader_Close(ReaderHandle);
			return 0;
		}else
		{
			////////////////////////////////////////
			unsigned char uid[20]={0};
			unsigned char Response[100]={0};
			i=PICC_Reader_SetTypeA(ReaderHandle);
			i=PICC_Reader_Request(ReaderHandle);
			if(i)
			{
				temp.Format("请求卡片失败,错误代码:%d",i);
				strcpy(pErr,temp.GetBuffer(0));
				//ICC_Reader_Close(ReaderHandle);
				//return i;
			}
			i=PICC_Reader_anticoll(ReaderHandle,uid);
			if(i)
			{
				temp.Format("防碰撞失败,错误代码:%d",i);
				strcpy(pErr,temp.GetBuffer(0));
				ICC_Reader_Close(ReaderHandle);
				return i;
			}
			i=PICC_Reader_Select(ReaderHandle,0x41);
			if(i)
			{
				temp.Format("选卡失败,错误代码:%d",i);
				strcpy(pErr,temp.GetBuffer(0));
				ICC_Reader_Close(ReaderHandle);
				return i;
			}
			i=PICC_Reader_PowerOnTypeA(ReaderHandle,Response);
			if(i>=0)
			{
				//非接触/CPU卡(健康卡)
				i=iDOpenPort();
				if(i) 
				{
					temp.Format("打开端口失败(健康卡),错误代码:%d",i);
					strcpy(pErr,temp.GetBuffer(0));
					iDClosePort();
					return i;
				}
				HANDLE hDev;
				char ATR[50]={0};
				i=PowerOn(hDev,0x01,ATR);
				if(i) 
				{
					temp.Format("健康卡上电失败,错误代码:%d",i);
					strcpy(pErr,temp.GetBuffer(0));
					iDClosePort();
					return i;
				}
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
				i=iR_DDF1EF05Info(hDev,KLB,GFBB, FKJGMC, FKJGDM, FKJGZS, FKSJ, KH, AQM, XPXLH,YYCSDM);
				if(i)
				{
					temp.Format("读取健康卡信息失败,错误代码:%d",i);
					strcpy(pErr,temp.GetBuffer(0));
					iDClosePort();
					return i;
				}
				temp.Format("健康卡:%s|%s",KH,FKSJ);
				strcpy(dataOut,temp.GetBuffer(0));
				iDClosePort();
				ICC_Reader_Close(ReaderHandle);
				return 0;
			}else
			{
				i=PICC_Reader_PowerOnTypeA(ReaderHandle,Response);
				if(i>0)
				{
					ICC_Reader_Close(ReaderHandle);
					return 114;
				}
				unsigned char cmd[100]={0};
				unsigned char Response_APDU[100]={0};
				memcpy(cmd, "\x00\xA4\x00\x00\x00",5);
				i=PICC_Reader_Application(ReaderHandle,5,cmd,Response_APDU);
				if(i>0) 
				{
					ICC_Reader_Close(ReaderHandle);
					return 114;
				}
				//非接触/M1卡
				memset(uid,0x00,20);
				int i=PICC_Reader_Request(ReaderHandle);
				if(i) 
				{
					temp.Format("M1卡请求卡片失败,错误代码:%d",i);
					strcpy(pErr,temp.GetBuffer(0));
					ICC_Reader_Close(ReaderHandle);
					return i;
				}
				i=PICC_Reader_anticoll(ReaderHandle,uid);
				if(i) 
				{
					temp.Format("M1卡请求防碰撞失败,错误代码:%d",i);
					strcpy(pErr,temp.GetBuffer(0));
					ICC_Reader_Close(ReaderHandle);
					return i;
				}
				//strrev((char *)uid);	
				unsigned char temp1 = 0x00;
				temp1 = uid[3];
				uid[3] = uid[0];
				uid[0] = temp1;
				temp1 = uid[1];
				uid[1] = uid[2];
				uid[2] = temp1;
				char UIDstr[40]={0};
				HexToStr(uid, 4, (unsigned char*)UIDstr);
				unsigned long num = ChangeNum(UIDstr, 8);
				sprintf((char *)uid,"%u", num);
				////////////////////////////////////////////////////////////
				temp.Format("M1卡:%s",uid);
				strcpy(dataOut,temp.GetBuffer(0));
				ICC_Reader_Close(ReaderHandle);
				return 0;
			}//end else
		}//end else
	}//end else
	//ICC_Reader_Close(ReaderHandle);
	//return 115;
		
}