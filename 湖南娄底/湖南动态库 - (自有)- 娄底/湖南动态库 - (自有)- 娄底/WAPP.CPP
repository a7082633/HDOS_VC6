#include "stdafx.h"

#include "WAPP.H"
#include "math.h"
#include <string>
using namespace std;
#include <mbstring.h>

string strdata1,strdata,sDisp;
char data1[2];
char sAccm;
long Rhand;
int cardtype=0;//1：新卡，2：新一批老卡，3：老一批老卡 4:4428卡 5:4442卡 6:1604卡
int generation = 0; //1:1代卡(老卡、湘潭县)；2:2代卡(湘潭市)  3:2代卡(湘乡) 4:3代卡(创智)  5:4代卡(新卡) 
unsigned char ucATR[20]={0};

unsigned char _CityCode[33]={0};//城市代码
unsigned char _ATR[20]={0};//ATR分散因子
unsigned char _Random[10]={0};

int AN_style = 0x01;
int CN_style = 0x0F;
int B_style	=  0xFF;

#pragma data_seg("_CSP_SHARED")
HANDLE g_hEvent = NULL;
#pragma data_seg()
#pragma comment(linker,"/section:_CSP_SHARED,RWS")


int chartoint(char c)
{
	switch (c)
	{
	case '0':
		return 0;break;
	case '1':
		return 1;break;
	case '2':
		return 2;break;
	case '3':
		return 3;break;
	case '4':
		return 4;break;
	case '5':
		return 5;break;
	case '6':
		return 6;break;
	case '7':
		return 7;break;
	case '8':
		return 8;break;
	case '9':
		return 9;break;
	case 'A':
	case 'a':
		return 10;break;
	case 'B':
	case 'b':
		return 11;break;
	case 'C':
	case 'c':
		return 12;break;
	case 'D':
	case 'd':
		return 13;break;
	case 'E':
	case 'e':
		return 14;break;
	case 'F':
	case 'f':
		return 15;break;
	default:
		break;

	}
	return 0;
}

void password_setup(unsigned char *instr,unsigned char *outstr,int len)
{
	int i; 
	memcpy(outstr,instr,len);

	for(i=len-1; i >= 0; i--)
	{
		outstr[i] = char(outstr[i]-693-'m'-'t');
	}
}

long SelectFile1(char*data,char*err)
{
	int st;
	strdata="";
	strdata = "<DATA>";
	unsigned char response[255]={0};
	Rhand=ICC_Reader_Open("USB1");
	if (Rhand<0)
	{
		strdata=strdata+"99</DATA>";
		strcpy(data,strdata.c_str());
		sprintf(err,"%d",Rhand);
		return 1;
	}
	st = ICC_Reader_pre_PowerOn(Rhand,0x01,response);
	if (st<0)
	{
		strdata=strdata+"99</DATA>";
		strcpy(data,strdata.c_str());
		sprintf(err,"%d",st);
		return 1;
	}
	strdata=strdata+"00</DATA>";
	strcpy(data,strdata.c_str());
	return 0;
}

long SelectFile2(char*data,char*err)
{
/*	char instr[20]={0};
	strcpy(instr,"1111111111");
	char outstr[20]={0};
	strcpy(outstr,"2222222222");
	password_setup((unsigned char*)instr,(unsigned char*)outstr, 10);
*/
	strdata="";
	strdata = "<DATA>";
	
	Rhand=ICC_Reader_Open("USB1");
	if (Rhand<0)
	{
		strdata=strdata+"99</DATA>";
		strcpy(data,strdata.c_str());
		sprintf(err,"%d",Rhand);
		return 1;
	}

	if(!g_hEvent)
	{
		g_hEvent = CreateEvent(NULL, FALSE, TRUE, "HD100HN");
		if(g_hEvent==NULL)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			sprintf(err,"%d",Rhand);
			return 1;
		}
	}
	
	
	strdata=strdata+"100</DATA>";
	strcpy(data,strdata.c_str());
	return 0;

}

long SelectFile3(char*data,char*err)//
{
	int st;
	strdata="";
	strdata = "<DATA>";
	st=ICC_Reader_Close(Rhand);
	if (st<0)
	{
		strdata=strdata+"99</DATA>";
		strcpy(data,strdata.c_str());
		sprintf(err,"%d",st);
		return 1;

	}
	strdata=strdata+"00</DATA>";
	strcpy(data,strdata.c_str());
	return 0;
}

long SelectFile4(char*data,char*err)
{
	int st;
	strdata="";
	strdata = "<DATA>";
	unsigned char response[255]={0};
	st = ICC_Reader_pre_PowerOn(Rhand,0x01,response);//冷上电
	
	if (st<0)//进一步判断是否为4428卡
	{
		memset(response,0,255);
		st = ICC_Reader_4428_PowerOn(Rhand,response);

		if(st<0 || (response[0]==0xFF) || (response[0]==0xA2))//进一步判断是否为4442卡
		{
			memset(response,0,255);
			st = ICC_Reader_4442_PowerOn(Rhand,response);
			if(st<0 || (response[0]==0xFF))
			{
				strdata=strdata+"99</DATA>";
				strcpy(data,strdata.c_str());
				sprintf(err,"%d",st);
				return 1;
			}
			strdata=strdata+"00</DATA>";
			strcpy(data,strdata.c_str());
			return 0;	
		}
		else
		{
			strdata=strdata+"00</DATA>";
			strcpy(data,strdata.c_str());
			return 0;
		}
		
	}
	for(int n=st-8;n<st;n++)
	{	
		_ATR[n-9] =  response[n] ;
	}

	strdata=strdata+"00</DATA>";
	strcpy(data,strdata.c_str());
	return 0;
}

long SelectFile5(char*data,char*err)
{
	int st;
	strdata="";
	strdata = "<DATA>";
	st = ICC_Reader_PowerOff(Rhand,0x01);
	if (st<0)
	{
		strdata=strdata+"99</DATA>";
		strcpy(data,strdata.c_str());
		sprintf(err,"%d",st);
		return 1;
	}
	strdata=strdata+"00</DATA>";
	strcpy(data,strdata.c_str());
	return 0;
}


long SelectFile6(char*data,char*err)
{
	int st;	
	unsigned char resp[100];
	unsigned char cmd[260];
	strdata="";
	strdata = "<DATA>";
	unsigned char response[255]={0};
	st = ICC_Reader_pre_PowerOn(Rhand,0x01,response);
	if (st<0)//可能为4428
	{
		memset(resp,0,100);
		st = ICC_Reader_4428_PowerOn(Rhand,resp);
	//	if(st<0 || (resp[0]==0xFF) || (resp[0]==0xA2) || (resp[4]==0 && resp[5]==0))
		if(st == 0)//4428上电成功
		{
			
			memset(resp,0,100);
			unsigned char Data1[1025]={0};
			st = ICC_Reader_4428_Read(Rhand,0,1024,Data1);
			if(Data1[1022] == 0)
			{
				strdata=strdata+"99</DATA>";
				strcpy(data,strdata.c_str());
				cardtype =4;
//				ICC_Reader_4428_PowerOff(Rhand);
				return 0;
			}
			else if(Data1[1022] == 0xFF)
			{
				strdata=strdata+"99</DATA>";
				strcpy(data,strdata.c_str());
				cardtype =5;  //为4442卡
//				ICC_Reader_4428_PowerOff(Rhand);
				return 0;
			}
		
				
		}
		else
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			cardtype =0;  //未知
			return 1;
		}

		strdata=strdata+"99</DATA>";
		strcpy(data,strdata.c_str());
		sprintf(err,"%d",st);
		cardtype =0;
		return 1;
	}
	memset(cmd,0,260);
	memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF",20);
	//00A404000F7378312E73682EC9E7BBE1B1A3D5CF
	st = ICC_Reader_Application(Rhand,0x01,20,cmd,resp);//X选择MF文件
	if(resp[0]!=0x61)//判断是否为老一批老卡
	{
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x03",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
		if (st<0 ||resp[0]!=0x90)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			sprintf(err,"%d",st);
			cardtype =0;
			return 1;
		}
		strdata=strdata+"99</DATA>";
		strcpy(data,strdata.c_str());
		sprintf(err,"%d",st);
		cardtype =3;//老一批老卡标志
	}
	else//判断是新卡还是新一批老卡
	{
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x7f\x01",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
		if (st<0 ||(resp[0]!=0x90 && resp[0]!=0x61))//新卡
		{
			strdata=strdata+"00</DATA>";
			strcpy(data,strdata.c_str());
			cardtype =1;

			memset(cmd,0,50);
			memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF",20);
			//00A404000F7378312E73682EC9E7BBE1B1A3D5CF
			int ret = ICC_Reader_Application(Rhand,0x01,20,cmd,resp);//X选择MF文件
			if(resp[0]!=0x61)
				return 1;
			memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
			ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
			memcpy(cmd, "\x00\xB2\x01\x04\x12",5);
			ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);

			if(ret<0 || resp[ret-2]!=0x90)
			{
				strcpy(err,"卡片为空卡");
				return 1;
			}
			char sdisp[3]={0};
			char saccm[40]={0};
			for(int n=0;n<ret;n++)
			{
				sprintf(sdisp,"%02x",resp[n]);
				strcat(saccm,sdisp);
			}
			//char str[33]={0}; 
			memcpy(_CityCode,saccm+4,32);
		}
		else 
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			sprintf(err,"%d",st);
			cardtype =2;//新一批老卡标志
		}
	}

	return 0;
}

long SelectFile7(char*data,char*err)
{
	//预留
	int st;	
	unsigned char resp[100];
	unsigned char cmd[260];
	char random[3]={0};
	strdata="";
	sDisp="";
	strdata = "<DATA>";
	memset(cmd,0,260);

		unsigned char response[100]={0};
		st = ICC_Reader_pre_PowerOn(Rhand,0x11,response);
		if (st<0)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			strcpy(err,"请在SAM1卡槽插入PSAM卡");
			return 1;
		}

		memset(cmd,0,50);
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7);
		int ret = ICC_Reader_Application(Rhand,0x11,7,cmd,resp);
		memset(resp,0,100);
		memcpy(cmd, "\x00\xb0\x00\x00\x0f",5);
		ret = ICC_Reader_Application(Rhand,0x11,5,cmd,resp);

		if(ret<0 || resp[ret-2]!=0x90)
		{
			strcpy(err,"PSAM卡片为空卡");
			return 1;
		}
		for(int i=0;i<(ret-2);i++)
		{
			sprintf(random,"%02x",resp[i]);
			strdata+=random;
		}
		strdata+="</DATA>";
		strcpy(data,strdata.c_str());

	return 0 ;
}

int old_card_altervalue(int len,  char *data_buffer,char*out)
{
	int j;
	char in[100]={0};
	strcpy(in,data_buffer);
	for (int i=0 ;i< len;i++)
	{ 
		j=*(in+i);
		j +=128 ;
		if (j>255)
		{ 
			j -=256;
		}
		*(out+i)=j;
	}
//	delete in;
	return 0;
}

void procPassWord(unsigned char *instr, unsigned char *outstr, int len)
{
	int i;
	//1：十六进制进行换位运算
	for(i = 0; i < len; i++)
	{
		outstr[i] = ~((instr[i] & 0xf0)/0x10 + (instr[i] & 0x0f)*0x10) ;
	}
}


long SelectFile8(char*data,char*err)
{
	int st;	
	unsigned char resp[100];
	unsigned char cmd[260];
	unsigned char Random[10]={0};
	unsigned char index[10];
	unsigned char windex[]={"powerhy"};
	unsigned char wdata[1024];
	string comdata;
	string strddata;
	string writedata;
	strddata += "powerhy";
	strdata="";
	sDisp="";
	strdata = "<DATA>";
	memset(cmd,0,260);
	if(cardtype ==1)//新卡
	{
		unsigned char response[100]={0};
		st = ICC_Reader_pre_PowerOn(Rhand,0x11,response);
		if (st<0)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			strcpy(err,"请在SAM1卡槽插入PSAM卡");
			return 1;
		}

		int ret = ICC_Reader_PowerOn(Rhand,0x01,resp);
		for(int n=ret-8;n<ret;n++)
		{	
			ucATR[n-9] =  resp[n] ;
		}
		memset(cmd,0,50);
		memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF",20);
		//00A404000F7378312E73682EC9E7BBE1B1A3D5CF
		ret = ICC_Reader_Application(Rhand,0x01,20,cmd,resp);//X选择MF文件
		if(resp[0]!=0x61)
			return 1;
		memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
		ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
		memcpy(cmd, "\x00\xB2\x01\x04\x12",5);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);

		if(ret<0 || resp[ret-2]!=0x90)
		{
			strcpy(err,"卡片为空卡");
			return 1;
		}
		char sdisp[3]={0};
		char saccm[40]={0};
		for(n=0;n<ret;n++)
		{
			sprintf(sdisp,"%02x",resp[n]);
			strcat(saccm,sdisp);
		}
		char str[33]={0}; 
		memcpy(str,saccm+4,32);

		memset(cmd,0,50);
		memcpy(cmd, "\x00\xA4\x00\x00\x02\xdd\xf1",7);
		ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择ddf1文件
		if(resp[0]!=0x61)
		{
			strcpy(err,"用户卡类型不对");
			return 1;
		}
		
		memset(cmd,0,50);
		memcpy(cmd, "\x00\x84\x00\x00\x08",5);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		for(n=0;n<ret-2;n++)
		{	
			Random[n] =  resp[n] ;
		}
		

		memset(cmd,0,50);
		memcpy(cmd, "\x00\xA4\x00\x00\x02\xDF\x01",7);
		ret = ICC_Reader_Application(Rhand,0x11,7,cmd,resp);
		memcpy(cmd, "\xBF\xDE\x67\x08\x20",5); //一级分散

		cmd[5]=ucATR[0];
		cmd[6]=ucATR[1];
		cmd[7]=ucATR[2];
		cmd[8]=ucATR[3];
		cmd[9]=ucATR[4];
		cmd[10]=ucATR[5];
		cmd[11]=ucATR[6];
		cmd[12]=ucATR[7];

		cmd[13]=str[0];
		cmd[14]=str[1];
		cmd[15]=str[2];
		cmd[16]=str[3];
		cmd[17]=str[4];
		cmd[18]=str[5];
		cmd[19]=0x73;
		cmd[20]=0x78;

		cmd[21]=str[0];
		cmd[22]=str[1];
		cmd[23]=0x30;
		cmd[24]=0x30;
		cmd[25]=0x30;
		cmd[26]=0x30;
		cmd[27]=0x73;
		cmd[28]=0x68;
		
		cmd[29]=Random[0];
		cmd[30]=Random[1];
		cmd[31]=Random[2];
		cmd[32]=Random[3];
		cmd[33]=Random[4];
		cmd[34]=Random[5];
		cmd[35]=Random[6];
		cmd[36]=Random[7];

		ret = ICC_Reader_Application(Rhand,0x11,37,cmd,resp);
		memset(cmd,0,50);
		memcpy(cmd, "\x80\xFA\x00\x00\x08\x01\x02\x03\x04\x05\x06\x07\x08",13);//对鉴别因子加密
		ret = ICC_Reader_Application(Rhand,0x11,13,cmd,resp);
		//80FA0000080102030405060708
		memset(cmd,0,50);
		memcpy(cmd, "\x00\xc0\x00\x00\x08",5);
		ret = ICC_Reader_Application(Rhand,0x11,5,cmd,resp);
		
		unsigned char result[10]={0};
		memcpy(result,resp,8);

		memset(cmd,0,50);
		memcpy(cmd,"\x00\x88\x00\x00\x10",5);
		memcpy(cmd+5,Random,8);
		memcpy(cmd+13,"\x01\x02\x03\x04\x05\x06\x07\x08",8);

		ret = ICC_Reader_Application(Rhand,0x01,21,cmd,resp);
		//80FA0000080102030405060708
		memset(cmd,0,50);
		memcpy(cmd, "\x00\xc0\x00\x00\x08",5);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);

		for(int i=0;i<8;i++)
		{
			if(result[i]!=resp[i])
			{
				strcpy(err,"内部认证出错");
				return 1;
			}
		}
		memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
		memcpy(cmd, "\x00\xB2\x07\x04\x0B",5);
		memset(resp,0,100);
		st = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (st<0)
		{
			sprintf(err,"%d",st);
			return 1;
		}
		for( n=0;n<st;n++)
		{
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		} 
		strdata += sDisp.substr(2,9);
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
	}
	else if(cardtype==2)//新一批老卡 PSAM3
	{
		unsigned char response[100]={0};
		st = ICC_Reader_pre_PowerOn(Rhand,0x13,response);
		if (st<0)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			//sprintf(err,"%d",st);
			strcpy(err,"请在SAM3卡槽插入PSAM卡");
			return 1;
		}
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x3f\x00",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x7f\x01",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x15",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
		memcpy(cmd, "\x00\xB0\x00\x22\x14",5);
		memset(resp,0,100);
		st = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (st<0)
		{
			sprintf(err,"%d",st);
			return 1;
		}
		for( int n=0;n<0x14;n++)
		{
			if(resp[n]==0x20)
				break;
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		} 
		strdata += sDisp.substr(0,n);
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
	}
	else if(cardtype==3)//老一批老卡 PSAM2
	{
		unsigned char response[100]={0};
		st = ICC_Reader_pre_PowerOn(Rhand,0x12,response);
		if (st<0)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			//sprintf(err,"%d",st);
			strcpy(err,"请在SAM2卡槽插入PSAM卡");
			return 1;
		}
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x3f\x00",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
		memcpy(cmd, "\x00\xA4\x00\x00\x02\x00\x03",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
		memcpy(cmd, "\x00\xB0\x00\x00\x14",5);
		memset(resp,0,100);
		st = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (st<0)
		{
			sprintf(err,"%d",st);
			return 1;
		}
		for(  int n=0;n<0x14;n++)
		{
			if(resp[n]==0x20)
				break;
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		} 
		strdata += sDisp.substr(0,n);
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
	}
	else if(cardtype==4)//4428卡
	{
		unsigned char card_buff[100]={0};
		unsigned char chack_buff[100]={0};
		char cbuff[100]={0};
		char a[3]={0};
	
		memset(card_buff,0,100);
		st = ICC_Reader_4428_Read(Rhand,50,20,card_buff);
		if(st<0)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			strcpy(err,"读取卡号失败!");
			ICC_Reader_4428_PowerOff(Rhand);
			return 1;
		}
		for (int i =0; i < 20;i++)
		{
			sprintf(a,"%02X",card_buff[i]);
			strcat(cbuff,a);
		}
		bool fflag=true;;
		for(i=0;i<8;i++)//如果前8为有效数字，则为卡号
		{
			if(cbuff[i]<0x30 || cbuff[i]>0x39)
			{
				fflag=false;//不是卡号
				break;
			}
		}
		if(!fflag)//不是卡号
		{
			memset(card_buff,0,100);
			st = ICC_Reader_4428_Read(Rhand,100,14,card_buff);
			if(st<0)
			{
				strdata=strdata+"99</DATA>";
				strcpy(data,strdata.c_str());
				strcpy(err,"读取卡号失败!");
				ICC_Reader_4428_PowerOff(Rhand);
				return 1;
			}
			bool ffflag=true;;
			for(i=0;i<4;i++)//如果前4为有效数字，则为卡号
			{
				if(card_buff[i]<0x30 || card_buff[i]>0x39)
				{
					ffflag=false;//不是卡号
					break;
				}
			}
			if(!ffflag)//不是卡号
			{
				memset(card_buff,0,100);
				st = ICC_Reader_4428_Read(Rhand,27,14,card_buff);
				if(st<0)
				{
					strdata=strdata+"99</DATA>";
					strcpy(data,strdata.c_str());
					strcpy(err,"读取卡号失败!");
					ICC_Reader_4428_PowerOff(Rhand);
					return 1;
				}

				bool feflag=true;;
				for(i=0;i<8;i++)//如果前4为有效数字，则为卡号
				{
					if(card_buff[i]<0x30 || card_buff[i]>0x39)
					{
						feflag=false;//不是卡号
						break;
					}
				}
				if(!feflag)//需要解密
				{
					memset(card_buff,0,100);
					st = ICC_Reader_4428_Read(Rhand,37,20,card_buff);
					if(st<0)
					{
						strdata=strdata+"99</DATA>";
						strcpy(data,strdata.c_str());
						strcpy(err,"读取卡号失败!");
						ICC_Reader_4428_PowerOff(Rhand);
						return 1;
					}

					memset(cbuff,0,100);
					procPassWord(card_buff, (unsigned char*)cbuff, 20);
					/*strdata += "431382";*/
					for(i=0;i<20;i++)
					{
						if(cbuff[i]==' ')
						{
							cbuff[i]=0;
							break;
						}
					}
				}
				else
				{
					memset(cbuff,0,100);
					memcpy(cbuff,card_buff,14);
					for(i=0;i<14;i++)//
					{
						if(cbuff[i]<0x30 || cbuff[i]>0x39)
						{
							cbuff[i]=0;//
							break;
						}
					}
				}


			}
			else
			{
				memset(cbuff,0,100);
				memcpy(cbuff,card_buff,14);
				for(i=0;i<14;i++)//
				{
					if(cbuff[i]<0x30 || cbuff[i]>0x39)
					{
						cbuff[i]=0;//
						break;
					}
				}
			}
		}
		else
		{
			//memset(cbuff,0,100);
			//memcpy(cbuff,card_buff,20);
			for(i=0;i<40;i++)//
			{
				if(cbuff[i]<0x30 || cbuff[i]>0x39)
				{
					cbuff[i]=0;//
					break;
				}
			}
			cbuff[20]=0;
		}

		strdata += cbuff;
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		ICC_Reader_4428_PowerOff(Rhand);

	}
	else if(cardtype ==5)//4442
	{
		unsigned  char test3[10]={0};
		int test4 = ICC_Reader_4442_PowerOn(Rhand,test3);
		char card_buff[100]={0};
		char cbuff[30]={0};

		int st = ICC_Reader_4442_Read(Rhand,100,14,(unsigned char*)card_buff);
		if(st<0)
		{
			strdata=strdata+"99</DATA>";
			strcpy(data,strdata.c_str());
			strcpy(err,"读取卡号失败!");
			ICC_Reader_4442_PowerOff(Rhand);
			return 1;
		}

		for(int i=0;i<14;i++)
		{
			if(card_buff[i]<0x30 || card_buff[i]>0x39)
			{
				card_buff[i]=0;
				break;
			}
		}
		strdata += card_buff;
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		ICC_Reader_4442_PowerOff(Rhand);
		
	}
	else
	{
		strcpy(data,"Data =<DATA></DATA>");
	}
	return 0;
}

long SelectFile9(char*data,char*err)
{
	int st;	
	unsigned char resp[100];
	unsigned char cmd[260];
	strdata="";
	sDisp="";
	strdata = "<DATA>";
	unsigned char card_buff[100]={0};
	char cbuff[100]={0};
	int datalen=0;
	{
		memset(cmd,0,260);
		memcpy(cmd, "\x00\xA4\x00\x00\x02\xDD\xF1",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
		memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x06",7);
		st = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
		memcpy(cmd, "\x00\xB2\x01\x04\x14",5);
		st = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (st<0)
		{
			sprintf(err,"%d",st);
			return 1;
		}
		sDisp = (char*)resp;
		strdata += sDisp.substr(2,18);
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
	}
	return 0;
}

long SelectFile10(char*data,char*err)
{
	strdata="";
	sDisp="";
	strdata = "<DATA>";
	{
		unsigned char cardsn[30]={0};
		int re = ICC_Reader_GetDeviceCSN(Rhand,(char*)cardsn);
		if(re<0)
		{
			strdata+="获取失败";
			strdata=strdata+"</DATA>";
			strcpy(data,strdata.c_str());
			return 1;
		}
		char data1[3]={0};
		for(int i=0;i<re;i++)
		{
			sprintf(data1,"%02X",cardsn[i]);
			sDisp += data1; 
		}
		strdata += sDisp;
//		strdata = strdata+"HDH3120506000006";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
	}
	return 0;
}

long SelectFile11(char*data,char*err)
{

	unsigned char resp[100];
	unsigned char cmd[260];
	strdata="";
	sDisp="";
	strdata = "<DATA>";
	memset(resp,0,100);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDD\xF1",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd, "\x00\xB2\x01\x04\x12",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	if (ret<0)
	{
		sprintf(err,"%d",ret);
		return 1;
	}
	
	for(  int n=0;n<ret;n++)
	{
		sprintf(data1,"%02x",resp[n]);
		sDisp += data1;  
	}
	
	strdata += "<C01>"; 
	strdata += sDisp.substr(4, 32);
	strdata += "</C01>";

	memcpy(cmd, "\x00\xB2\x02\x04\x03",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	for( n=0;n<ret;n++)
	{
		sAccm=(char)resp[n];		
		sDisp+=sAccm;
	}	
	strdata += "<C02>"; 
	strdata += sDisp.substr(2, 1);
	strdata += "</C02>";
	
	memcpy(cmd, "\x00\xB2\x03\x04\x06",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	char temp[100]={0};
	for(  n=0;n<(ret-2);n++)
	{
		temp[n]=resp[n];		
	}
	sDisp = (char*)temp;
	int len = sDisp.length();
	strdata += "<C03>"; 			
	strdata += sDisp.substr(2, sDisp.length()-2);					
	strdata += "</C03>"; 
	
	memcpy(cmd, "\x00\xB2\x04\x04\x0E",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	for(n=0;n<ret;n++)
	{	
	sprintf(data1,"%02x",resp[n]);
	sDisp += data1;  
	}
	strdata += "<C04>"; 
	strdata += sDisp.substr(4, 24);
	strdata += "</C04>";
	
	memcpy(cmd, "\x00\xB2\x05\x04\x06",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	for(n=0;n<ret;n++)
	{	
	sprintf(data1,"%02x",resp[n]);
	sDisp += data1;  
	}
	strdata += "<C05>"; 
	strdata += sDisp.substr(4, 8);
	strdata += "</C05>";

	memcpy(cmd, "\x00\xB2\x06\x04\x06",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	for(n=0;n<ret;n++)
	{	
	sprintf(data1,"%02x",resp[n]);
	sDisp += data1;  
	}
	strdata += "<C06>"; 
	strdata += sDisp.substr(4, 8);
	strdata += "</C06>";

	memcpy(cmd, "\x00\xB2\x07\x04\x0B",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	memset(temp,0,100);
	for(  n=0;n<(ret-2);n++)
	{
		temp[n]=resp[n];		
	}
	sDisp = (char*)temp;

	strdata += "<C07>"; 
	strdata += sDisp.substr(2,sDisp.length()-2);
	strdata += "</C07>";
	strdata=strdata+"</DATA>";
	strcpy(data,strdata.c_str());
	return 0;
}


long SelectFile12(char*data,char*err)
{

	unsigned char resp[100];
	unsigned char cmd[260];
	strdata="";
	sDisp="";
	strdata = "<DATA>";
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDD\xF1",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x06",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd, "\x00\xB2\x01\x04\x14",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	if (ret<0)
	{
		sprintf(err,"%d",ret);
		return 1;
	}
	char temp[100]={0};
	for(  int n=0;n<ret-2;n++)
	{
		temp[n]=(char)resp[n];		
	}

	sDisp = (char*)temp;
	strdata += "<C01>"; 
	strdata += sDisp.substr(2,sDisp.length()-2);
	strdata += "</C01>";

	memcpy(cmd, "\x00\xB2\x02\x04\x20",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	memset(temp,0,100);
	for(  n=0;n<(ret-2);n++)
	{
		temp[n]=resp[n];		
	}
	sDisp = (char*)temp;
	int len = sDisp.length();
	strdata += "<C02>"; 
	strdata += sDisp.substr(2, sDisp.length()-2);
	strdata += "</C02>";
	
	memcpy(cmd, "\x00\xB2\x03\x04\x16",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	memset(temp,0,100);
	for(  n=0;n<(ret-2);n++)
	{
		temp[n]=resp[n];		
	}
	sDisp = (char*)temp;
	strdata += "<C03>"; 			
	strdata += sDisp.substr(2, sDisp.length()-2);					
	strdata += "</C03>"; 
	
	memcpy(cmd, "\x00\xB2\x04\x04\x03",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	memset(temp,0,100);
	for(  n=0;n<(ret-2);n++)
	{
		temp[n]=resp[n];		
	}
	sDisp = (char*)temp;
	strdata += "<C04>"; 
	strdata += sDisp.substr(2,1);
	strdata += "</C04>";
	
	memcpy(cmd, "\x00\xB2\x05\x04\x03",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	for(n=0;n<ret;n++)
	{	
		sprintf(data1,"%02x",resp[n]);
		sDisp += data1;  
	}
	strdata += "<C05>"; 
	strdata += sDisp.substr(4,2);
	strdata += "</C05>";

	memcpy(cmd, "\x00\xB2\x06\x04\x05",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	for(n=0;n<ret;n++)
	{	
		sprintf(data1,"%02x",resp[n]);
		sDisp += data1;  
	}
	strdata += "<C06>"; 
	strdata += sDisp.substr(4, 6);
	strdata += "</C06>";

	memcpy(cmd, "\x00\xB2\x07\x04\x06",5);
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	sDisp = "" ;
	for(n=0;n<ret;n++)
	{	
		sprintf(data1,"%02x",resp[n]);
		sDisp += data1;  
	}
	strdata += "<C07>"; 
	strdata += sDisp.substr(4, 8);
	strdata += "</C07>";

	strdata=strdata+"</DATA>";
	strcpy(data,strdata.c_str());
	return 0;
}

long ReadFileMFEF05(char*data,char*err,int len)
{
	unsigned char resp[100];
	unsigned char cmd[260];
	strdata = "<DATA>";
	strdata1="";
	sDisp="";
	strdata1=data;
	int n;
	long EndLen2 = strdata1.find(">",len);
	sDisp = strdata1.substr(len+3,EndLen2-len-4);
	int st = atoi(sDisp.c_str());
	memset(resp,0,100);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDD\xF1",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	switch(st)
	{
	case 1:
		memcpy(cmd, "\x00\xB2\x01\x04\x12",5);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(  n=0;n<ret;n++)
		{
			sprintf(data1,"%02x",resp[n]);
			sDisp += data1;  
		}
		strdata += "<C01>"; 
		strdata += sDisp.substr(4, 32);
		strdata += "</c01>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 2:
		memcpy(cmd, "\x00\xB2\x02\x04\x03",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n];		
				sDisp+=sAccm;
		}	
		strdata += "<C02>"; 
		strdata += sDisp.substr(2, 1);
		strdata += "</C02>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 3:
		memcpy(cmd, "\x00\xB2\x03\x04\x06",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n];		
				sDisp+=sAccm;
		}
		strdata += "<c03>"; 			
		strdata += sDisp.substr(2, 4);					
		strdata += "</c03>"; 
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 4:
		memcpy(cmd, "\x00\xB2\x04\x04\x0E",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{	
			sprintf(data1,"%02x",resp[n]);
			sDisp += data1;  
		}
		strdata += "<c04>"; 
		strdata += sDisp.substr(4, 24);
		strdata += "</c04>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 5:
		memcpy(cmd, "\x00\xB2\x05\x04\x06",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{	
			sprintf(data1,"%02x",resp[n]);
			sDisp += data1;  
		}
		strdata += "<c05>"; 
		strdata += sDisp.substr(4, 8);
		strdata += "</c05>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
	
	case  6:
		memcpy(cmd, "\x00\xB2\x06\x04\x06",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{	
			sprintf(data1,"%02x",resp[n]);
			sDisp += data1;  
		}
		strdata += "<c06>"; 
		strdata += sDisp.substr(4, 8);
		strdata += "</c06>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
		
	case 7:
		memcpy(cmd, "\x00\xB2\x07\x04\x0B",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n];		
				sDisp+=sAccm;
		}
		strdata += "<c07>"; 
		strdata += sDisp.substr(2,9);
		strdata += "</c07>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
	}
	
	return 0;	

}

long ReadFileMFEF06(char*data,char*err,int len)
{
	
	unsigned char resp[100];
	unsigned char cmd[260];
	strdata = "<DATA>";
	strdata1="";
	sDisp="";
	strdata1=data;
	int n;
	long EndLen2 = strdata1.find(">",len);
	sDisp = strdata1.substr(len+3,EndLen2-len-4);
	int st = atoi(sDisp.c_str());
	memset(resp,0,100);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDD\xF1",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x06",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	switch(st)
	{
	case 1:
		memcpy(cmd, "\x00\xB2\x01\x04\x14",5);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{
		sAccm=(char)resp[n];		
		sDisp+=sAccm; 
		}
		strdata += "<C01>"; 
		strdata += sDisp.substr(2,18);
		strdata += "</C01>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 2:
		memcpy(cmd, "\x00\xB2\x02\x04\x20",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
		sAccm=(char)resp[n]	;	
		sDisp+=sAccm;
		}	
		strdata += "<C02>"; 
		strdata += sDisp.substr(2, 30);
		strdata += "</C02>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 3:
		memcpy(cmd, "\x00\xB2\x03\x04\x03",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		}
		strdata += "<C03>"; 			
		strdata += sDisp.substr(2, 1);					
		strdata += "</C03>"; 
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 4:
		memcpy(cmd, "\x00\xB2\x04\x04\x03",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{	
			sprintf(data1,"%02x",resp[n]);
			sDisp += data1;  
		}
		strdata += "<C04>"; 
		strdata += sDisp.substr(4,2);
		strdata += "</C04>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 5:
		memcpy(cmd, "\x00\xB2\x05\x04\x05",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{	
		sprintf(data1,"%02x",resp[n]);
		sDisp += data1;  
		}
		strdata += "<C05>"; 
		strdata += sDisp.substr(4,6);
		strdata += "</C05>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
	
	case  6:
		memcpy(cmd, "\x00\xB2\x06\x04\x06",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{	
			sprintf(data1,"%02x",resp[n]);
			sDisp += data1;  
		}
		strdata += "<C06>"; 
		strdata += sDisp.substr(4, 8);
		strdata += "</C06>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
		
	}
	
	return 0;
}

long ReadFileDF01EF05(char *data,char *err,int len)
{
	unsigned char resp[100];
	unsigned char cmd[260];
	strdata = "<DATA>";
	strdata1="";
	sDisp="";
	strdata1=data;
	int n;
	long EndLen2 = strdata1.find(">",len);
	sDisp = strdata1.substr(len+3,EndLen2-len-4);
	int st = atoi(sDisp.c_str());
	memset(resp,0,100);
	long ret;
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDF\x01",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd,"\x00\x20\x00\x00\x03\x88\x88\x88",8); 
	ret = ICC_Reader_Application(Rhand,0x01,8,cmd,resp);
	switch(st)
	{
	case 1:
		memcpy(cmd, "\x00\xB2\x01\x04\x03",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{
		sAccm=(char)resp[n];		
		sDisp+=sAccm; 
		}
		strdata += "<C01>"; 
		strdata += sDisp.substr(2,1);
		strdata += "</C01>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 2:
		memcpy(cmd, "\x00\xB2\x02\x04\x40",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
		sAccm=(char)resp[n]	;	
		sDisp+=sAccm;
		}	
		strdata += "<C02>"; 
		strdata += sDisp.substr(2, 62);
		strdata += "</C02>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 3:
		memcpy(cmd, "\x00\xB2\x03\x04\x14",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		}
		strdata += "<C03>"; 			
		strdata += sDisp.substr(2, 18);					
		strdata += "</C03>"; 
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
		
	}
	
	return 0;
	
}

long ReadFileDF01EF06(char *data,char *err,int len)
{
	unsigned char resp[100];
	unsigned char cmd[260];
	strdata = "<DATA>";
	strdata1="";
	sDisp="";
	strdata1=data;
	int n;
	long EndLen2 = strdata1.find(">",len);
	sDisp = strdata1.substr(len+3,EndLen2-len-4);
	int st = atoi(sDisp.c_str());
	memset(resp,0,100);
	long ret;
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDF\x01",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x06",7);
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd,"\x00\x20\x00\x00\x03\x88\x88\x88",8); 
	ret = ICC_Reader_Application(Rhand,0x01,8,cmd,resp);
	switch(st)
	{
	case 1:
		memcpy(cmd, "\x00\xB2\x01\x04\x40",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for(n=0;n<ret;n++)
		{
			sAccm=(char)resp[n];		
			sDisp+=sAccm; 
		}
		strdata += "<C01>"; 
		strdata += sDisp.substr(2,62);
		strdata += "</C01>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
		
	case 2:
		memcpy(cmd, "\x00\xB2\x02\x04\x14",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		}	
		strdata += "<C02>"; 
		strdata += sDisp.substr(2, 18);
		strdata += "</C02>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
		
	case 3:
		memcpy(cmd, "\x00\xB2\x03\x04\x05",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sprintf(data1,"%02x",resp[n]);
			sDisp += data1;  
		}
		strdata += "<C03>"; 			
		strdata += sDisp.substr(4, 6);					
		strdata += "</C03>"; 
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;
		
	case 4:
		memcpy(cmd, "\x00\xB2\x04\x04\x11",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		}	
		strdata += "<C04>"; 
		strdata += sDisp.substr(2, 15);
		strdata += "</C04>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 5:
		memcpy(cmd, "\x00\xB2\x05\x04\x1a",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		}	
		strdata += "<C05>"; 
		strdata += sDisp.substr(2, 24);
		strdata += "</C05>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	case 6:
		memcpy(cmd, "\x00\xB2\x06\x04\x22",5);
		memset(resp,0,100);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0)
		{
			sprintf(err,"%d",ret);
			return 1;
		}
		sDisp = "" ;
		for( n=0;n<ret;n++)
		{
			sAccm=(char)resp[n]	;	
			sDisp+=sAccm;
		}	
		strdata += "<C06>"; 
		strdata += sDisp.substr(2, 0x20);
		strdata += "</C06>";
		strdata=strdata+"</DATA>";
		strcpy(data,strdata.c_str());
		break;

	}
	
	return 0;
	
}

long ReadFileDF01EF07(char *data,char *err,int len)
{
	return 0;
}

long ReadFileDF01EF08(char *data,char *err,int len)
{
	return 0;
}


long WriteFile(char*data,char*err)
{
	return 0 ;
}

long SelectFile13(char*data,char*err)
{
	int st ;
	int ret =0;
	char result[256]={0};
	strdata="";
	sDisp="";
	strdata1 = data;
	long StartLen = strdata1.find("<",0); //DF
	long EndLen = strdata1.find(">",StartLen); 
	long StartLen1 = strdata1.find("<",EndLen); //EF
	long EndLen1 = strdata1.find(">",StartLen1); 
	long StartLen2 = strdata1.find("<",EndLen1); //C
	long EndLen2 = strdata1.find(">",StartLen2);
	sDisp = strdata1.substr(StartLen+1,EndLen-StartLen-1);
	if (sDisp=="MF" || sDisp=="DDF1")
	{
		SelectFile("DDF1");
		
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			case 1:ret = iReadRecord("EF05",recno,0x10,CN_style,result);break;
			case 2:ret = iReadRecord("EF05",recno,0x01,AN_style,result);break;
			case 3:ret = iReadRecord("EF05",recno,0x04,AN_style,result);break;
			case 4:ret = iReadRecord("EF05",recno,0x0C,CN_style,result);break;
			case 5:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
			case 6:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
			case 7:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
			}
		} 
		if (sDisp=="EF06")
		{
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			//char result[40]={0};
			switch(recno)
			{
			case 1:ret = iReadRecord("EF06",recno,0x12,AN_style,result);break;
			case 2:ret = iReadRecord("EF06",recno,0x1E,AN_style,result);break;
			case 3:ret = iReadRecord("EF06",recno,0x14,AN_style,result);break;
			case 4:ret = iReadRecord("EF06",recno,0x01,AN_style,result);break;
			case 5:ret = iReadRecord("EF06",recno,0x01,CN_style,result);break;
			case 6:ret = iReadRecord("EF06",recno,0x03,CN_style,result);break;
			case 7:ret = iReadRecord("EF06",recno,0x04,CN_style,result);break;
			}
	//		st =ReadFileMFEF06(data,err,StartLen2);
		}
	}
	if (sDisp=="DF01") //RK1 DF01
	{
		SelectFile("DDF1");
		SelectFile("DF01");
		unsigned char wordkey[4]={0x67,0x2E,0x88};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF01认证失败!");
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			case 1:ret = iReadRecord("EF05",recno,0x02,AN_style,result);break;
			case 2:ret = iReadRecord("EF05",recno,0x50,AN_style,result);break;
			case 3:ret = iReadRecord("EF05",recno,0x03,CN_style,result);break;
			}
		} 	
		if (sDisp=="EF06")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			case 1:ret = iReadRecord("EF06",recno,0x50,AN_style,result);break;
			case 2:ret = iReadRecord("EF06",recno,0x03,CN_style,result);break;
			case 3:ret = iReadRecord("EF06",recno,0x0F,AN_style,result);break;
			case 4:ret = iReadRecord("EF06",recno,0x32,AN_style,result);break;
			case 5:ret = iReadRecord("EF06",recno,0x0F,AN_style,result);break;
			}
		} 	
		if (sDisp=="EF07")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			case 1:ret = iReadRecord("EF07",recno,0x01,AN_style,result);break;
			}
		} 
		if (sDisp=="EF08")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			case 1:ret = iReadRecord("EF08",recno,0x01,AN_style,result);break;
			}
		}
		if (sDisp=="EF09")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			case 1:ret = iReadRecord("EF09",recno,0x46,AN_style,result);break;
			case 2:ret = iReadRecord("EF09",recno,0x09,AN_style,result);break;
			case 3:ret = iReadRecord("EF09",recno,0x02,AN_style,result);break;
			}
		}
		if (sDisp=="EF0A")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			case 1:ret = iReadRecord("EF0A",recno,0x03,AN_style,result);break;
			case 2:ret = iReadRecord("EF0A",recno,0x02,AN_style,result);break;
			case 3:ret = iReadRecord("EF0A",recno,0x04,CN_style,result);break;
			}
		}
		if (sDisp=="EF15")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			if(recno==1)
			{
				ret = iReadRecord("EF15",1,0x01,CN_style,result);			
			}
			else
			{
				TLV tlv[3]={{"57",0x03,AN_style},{"58",0x03,CN_style},{"59",0x28,AN_style}};
				ret = iReadBTLV("EF15",recno,0x34,tlv,3,result);	
			}		
		}
	}
	if (sDisp=="DF02") //RK1 DF02
	{
		SelectFile("DDF1");
		SelectFile("DF02");
		unsigned char wordkey[4]={0x67,0x35,0x88};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF02认证失败!");
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
		/*	sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
			//	case 1:ret = iReadRecord("EF05",recno,0x02,AN_style,result);break;
				case 2:ret = iReadRecord("EF05",recno,0x07,AN_style,result);break;
				case 3:ret = iReadRecord("EF05",recno,0x01,AN_style,result);break;
				case 4:ret = iReadRecord("EF05",recno,0x46,AN_style,result);break;
				case 5:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
				case 6:ret = iReadRecord("EF05",recno,0x10,AN_style,result);break;
				//case 7:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
				case 8:ret = iReadRecord("EF05",recno,0x03,AN_style,result);break;
				case 9:ret = iReadRecord("EF05",recno,0x46,AN_style,result);break;
				case 10:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
				case 11:ret = iReadRecord("EF05",recno,0x10,AN_style,result);break;
			}*/
		}

		if (sDisp=="EF06")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF06",recno,0x04,CN_style,result);break;
				case 2:ret = iReadRecord("EF06",recno,0x05,AN_style,result);break;
				case 3:ret = iReadRecord("EF06",recno,0x03,CN_style,result);break;
				case 4:ret = iReadRecord("EF06",recno,0x04,CN_style,result);break;
				case 5:ret = iReadRecord("EF06",recno,0x06,AN_style,result);break;
				case 6:ret = iReadRecord("EF06",recno,0x03,CN_style,result);break;
				case 7:ret = iReadRecord("EF06",recno,0x07,AN_style,result);break;
			}
		}
		if (sDisp=="EF07")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			CYC cy[4]={{0x07,AN_style},{0x04,CN_style},{0x04,CN_style},{0x46,AN_style}};
			iReadXHFile("EF07",recno,0x55,cy,4,result);
			/*switch(recno)
			{
				case 1:ret = iReadRecord("EF06",recno,0x04,CN_style,result);break;
				case 2:ret = iReadRecord("EF06",recno,0x05,AN_style,result);break;
				case 3:ret = iReadRecord("EF06",recno,0x03,CN_style,result);break;
				case 4:ret = iReadRecord("EF06",recno,0x04,CN_style,result);break;
				case 5:ret = iReadRecord("EF06",recno,0x06,AN_style,result);break;
				case 6:ret = iReadRecord("EF06",recno,0x03,CN_style,result);break;
				case 7:ret = iReadRecord("EF06",recno,0x07,AN_style,result);break;
			}*/
		}
		if (sDisp=="EF09")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF09",recno,0x10,AN_style,result);break;
				case 2:ret = iReadRecord("EF09",recno,0x46,AN_style,result);break;
				case 3:ret = iReadRecord("EF09",recno,0x04,CN_style,result);break;
				case 4:ret = iReadRecord("EF09",recno,0x03,CN_style,result);break;
			}
		}
		if (sDisp=="EF15")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			TLV tlv[3]={{"10",0x03,AN_style},{"11",0x04,CN_style},{"12",0x03,CN_style}};
			if(recno<5)
				ret = iReadBTLV("EF15",recno,0x10,tlv,3,result);
			else
			{
				switch(recno)
				{
				//	case 1:ret = iReadRecord("EF15",recno,0x10,AN_style,result);break;
					case 5:ret = iReadRecord("EF15",recno,0x04,CN_style,result);break;
					case 6:ret = iReadRecord("EF15",recno,0x03,CN_style,result);break;
				}
			}
		}
		if (sDisp=="EF16")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());

			CYC cy[5]={{0x03,AN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style},{0x03,CN_style}};
			ret = iReadXHFile("EF16",recno,0x12,cy,5,result);
		}
	}
	if (sDisp=="DF03") //RK1 DF02
	{
		SelectFile("DDF1");
		SelectFile("DF03");
		unsigned char wordkey[4]={0x67,0x2B,0x84};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF03认证失败!");
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			unsigned char wordkey[4]={0x67,0x2C,0x85};
			if(ExterAuthen(wordkey,1))
			{
				strcpy(err,"RK1DF03认证失败!");
				return 1;
			}
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF05",recno,0x03,CN_style,result);break;
				case 2:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
				case 3:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
				case 4:ret = iReadRecord("EF05",recno,0x03,AN_style,result);break;
				case 5:ret = iReadRecord("EF05",recno,0x03,AN_style,result);break;
				case 6:ret = iReadRecord("EF05",recno,0x03,AN_style,result);break;
				case 7:ret = iReadRecord("EF05",recno,0x03,AN_style,result);break;
			}
		}
		if (sDisp=="EF06")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			if(recno<8)
			{
				switch(recno)
				{
					case 1:ret = iReadRecord("EF06",recno,0x14,AN_style,result);break;
					case 2:ret = iReadRecord("EF06",recno,0x02,AN_style,result);break;
					case 3:ret = iReadRecord("EF06",recno,0x02,AN_style,result);break;
					case 4:ret = iReadRecord("EF06",recno,0x01,AN_style,result);break;
					case 5:ret = iReadRecord("EF06",recno,0x01,AN_style,result);break;
					case 6:ret = iReadRecord("EF06",recno,0x04,CN_style,result);break;
					case 7:ret = iReadRecord("EF06",recno,0x3C,AN_style,result);break;
				}
			}
			else
			{
				TLV tlv[5]={{"13",0x02,AN_style},{"14",0x01,AN_style},{"15",0x14,AN_style},{"16",0x04,CN_style},{"17",0x3C,AN_style}};
				ret = iReadBTLV("EF06",recno,0x61,tlv,5,result);
			}
		}
		if (sDisp=="EF07")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF07",recno,0x03,AN_style,result);break;
				case 2:ret = iReadRecord("EF07",recno,0x03,CN_style,result);break;
				case 3:ret = iReadRecord("EF07",recno,0x04,CN_style,result);break;
				case 4:ret = iReadRecord("EF07",recno,0x04,CN_style,result);break;
				case 5:ret = iReadRecord("EF07",recno,0x04,CN_style,result);break;
				case 6:ret = iReadRecord("EF07",recno,0x04,CN_style,result);break;
			}
		}
		if (sDisp=="EF15")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF15",recno,0x03,CN_style,result);break;
				case 2:ret = iReadRecord("EF15",recno,0x04,CN_style,result);break;
				case 3:ret = iReadRecord("EF15",recno,0x04,CN_style,result);break;
			}
		}
		if (sDisp=="EF16")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF16",recno,0x03,CN_style,result);break;
				case 2:ret = iReadRecord("EF16",recno,0x01,AN_style,result);break;
			}
		}
		if (sDisp=="EF17")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF17",recno,0x14,AN_style,result);break;
				case 2:ret = iReadRecord("EF17",recno,0x46,AN_style,result);break;
				case 3:ret = iReadRecord("EF17",recno,0x01,AN_style,result);break;
				case 4:ret = iReadRecord("EF17",recno,0x04,CN_style,result);break;
				case 5:ret = iReadRecord("EF17",recno,0x3C,AN_style,result);break;
			}
		}
		if (sDisp=="EF18")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF18",recno,0x03,AN_style,result);break;
				case 2:ret = iReadRecord("EF18",recno,0x03,CN_style,result);break;
				case 3:ret = iReadRecord("EF18",recno,0x01,CN_style,result);break;
				case 4:ret = iReadRecord("EF18",recno,0x04,CN_style,result);break;
				case 5:ret = iReadRecord("EF18",recno,0x04,CN_style,result);break;
			}
		}
		if (sDisp=="EF19")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			TLV tlv[7]={{"18",0x03,AN_style},{"19",0x03,CN_style},{"1A",0x04,CN_style},{"1B",0x04,CN_style},{"1C",0x04,CN_style},{"1D",0x03,AN_style},{"1E",0x04,CN_style}};
			ret = iReadBTLV("EF19",recno,0x27,tlv,7,result);
		}
	}
	if (sDisp=="DF04") //RK1 DF02
	{
		SelectFile("DDF1");
		SelectFile("DF04");
		unsigned char wordkey[4]={0x67,0x2D,0x84};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF04认证失败!");
			return 1;
		}
		unsigned char cmd[20]={0};
		unsigned char resp[10]={0};
		memcpy(cmd,"\x00\x20\x00\x00\x03\x66\x66\x66",8);
		ret = ICC_Reader_Application(Rhand,0x01,8,cmd,resp);//X选择MF文件
		if(ret<2 || resp[0]!=0x90)
		{
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF05",recno,0x08,AN_style,result);break;
				case 2:ret = iReadRecord("EF05",recno,0x03,CN_style,result);break;
				case 3:ret = iReadRecord("EF05",recno,0x11,AN_style,result);break;
				case 4:ret = iReadRecord("EF05",recno,0x01,CN_style,result);break;
				case 5:ret = iReadRecord("EF05",recno,0x04,CN_style,result);break;
				case 6:ret = iReadRecord("EF05",recno,0x1D,AN_style,result);break;
				case 7:ret = iReadRecord("EF05",recno,0x0F,AN_style,result);break;
				case 8:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 9:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 10:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 11:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 12:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 13:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 14:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 15:ret = iReadRecord("EF05",recno,0x09,AN_style,result);break;
				case 16:ret = iReadRecord("EF05",recno,0x01,AN_style,result);break;
			}
		}
		if (sDisp=="EF06")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			switch(recno)
			{
				case 1:ret = iReadRecord("EF06",recno,0x01,AN_style,result);break;
				case 2:ret = iReadRecord("EF06",recno,0x04,CN_style,result);break;
				case 3:ret = iReadRecord("EF06",recno,0x02,AN_style,result);break;
			}
		}
		if (sDisp=="EF08")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			CYC cy[7]={{0x02,CN_style},{0x01,AN_style},{0x06,CN_style},{0x07,CN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style}};
			ret = iReadXHFile("EF08",recno,0x1C,cy,7,result);
		}
		if (sDisp=="EF15")
		{	
			sDisp=strdata1.substr(StartLen2+2,EndLen2-StartLen2-1);//去掉字符C
			int recno = atoi(sDisp.c_str());
			
			CYC cy[2]={{0x02,CN_style},{0x01,AN_style}};
			ret = iReadXHFile("EF15",recno,0x03,cy,2,result);
		}
	}
	
	strdata1 = "<DATA>"+strdata1+"</DATA>";
	long posit = strdata1.find("<C",0);
	strdata1.insert(posit+5,result);
	strcpy(data,strdata1.c_str());
	return 0 ;
}

long SelectFile14(char*data,char*err)
{
	int st ;
	int ret =0;
	char result[256]={0};
	strdata="";
	sDisp="";
	strdata1 = data;
	long StartLen = strdata1.find("<",0);
	long EndLen = strdata1.find(">",StartLen); 
	long StartLen1 = strdata1.find("<",EndLen);
	long EndLen1 = strdata1.find(">",StartLen1); 
//	long StartLen2 = strdata1.find("<",EndLen1);
//	long EndLen2 = strdata1.find(">",StartLen2);
	sDisp = strdata1.substr(StartLen+1,EndLen-StartLen-1);
	if (sDisp=="MF" || sDisp=="DDF1")
	{
		SelectFile("DDF1");
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			strdata+="<DATA><MF><EF05>";
			memset(result,0,256);
			if(iReadRecord("EF05",1,0x10,CN_style,result))
			{
				strdata+="</EF05></MF></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF05",2,0x01,AN_style,result))
			{
				strdata+="</EF05></MF></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF05",3,0x04,AN_style,result))
			{
				strdata+="</EF05></MF></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF05",4,0x0C,CN_style,result))
			{
				strdata+="</EF05></MF></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF05",5,0x04,CN_style,result))
			{
				strdata+="</EF05></MF></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF05",6,0x04,CN_style,result))
			{
				strdata+="</EF05></MF></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			memset(result,0,256);
			if(iReadRecord("EF05",7,0x09,AN_style,result))
			{
				strdata+="</EF05></MF></DATA>";
				goto END;
			}
			strdata+="<C07>";
			strdata+=result;
			strdata+="</C07>";
			strdata+="</EF05></MF></DATA>";

		} 
		if (sDisp=="EF06")
		{
			strdata+="<DATA><MF><EF06>";
			memset(result,0,256);
			if(iReadRecord("EF06",1,0x12,AN_style,result))
			{
				strdata+="</EF06></MF></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF06",2,0x1E,AN_style,result))
			{
				strdata+="</EF06></MF></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF06",3,0x14,AN_style,result))
			{
				strdata+="</EF06></MF></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF06",4,0x01,AN_style,result))
			{
				strdata+="</EF06></MF></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF06",5,0x01,CN_style,result))
			{
				strdata+="</EF06></MF></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF06",6,0x03,CN_style,result))
			{
				strdata+="</EF06></MF></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			memset(result,0,256);
			if(iReadRecord("EF06",7,0x04,CN_style,result))
			{
				strdata+="</EF06></MF></DATA>";
				goto END;
			}
			strdata+="<C07>";
			strdata+=result;
			strdata+="</C07>";
			strdata+="</EF06></MF></DATA>";
		}
	}
	if (sDisp=="DF01") //RK1 DF01
	{
		SelectFile("DDF1");
		SelectFile("DF01");
		unsigned char wordkey[4]={0x67,0x2E,0x88};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF01认证失败!");
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			strdata+="<DATA><DF01><EF05>";
			memset(result,0,256);
			if(iReadRecord("EF05",1,0x02,AN_style,result))
			{
				strdata+="</EF05></DF01></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF05",2,0x50,AN_style,result))
			{
				strdata+="</EF05></DF01></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF05",3,0x03,CN_style,result))
			{
				strdata+="</EF05></DF01></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";
			
			strdata+="</EF05></DF01></DATA>";
			
		} 	
		if (sDisp=="EF06")
		{	
			strdata+="<DATA><DF01><EF06>";
			memset(result,0,256);
			if(iReadRecord("EF06",1,0x50,AN_style,result))
			{
				strdata+="</EF06></DF01></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF06",2,0x03,CN_style,result))
			{
				strdata+="</EF06></DF01></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF06",3,0x0F,AN_style,result))
			{
				strdata+="</EF06></DF01></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF06",4,0x32,AN_style,result))
			{
				strdata+="</EF06></DF01></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF06",5,0x0F,AN_style,result))
			{
				strdata+="</EF06></DF01></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			strdata+="</EF06></DF01></DATA>";
		} 	
		if (sDisp=="EF07")
		{	
			strdata+="<DATA><DF01><EF07>";
			memset(result,0,256);
			if(iReadRecord("EF07",1,0x01,AN_style,result))
			{
				strdata+="</EF07></DF01></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			strdata+="</EF07></DF01></DATA>";

		} 
		if (sDisp=="EF08")
		{	
			strdata+="<DATA><DF01><EF08>";
			memset(result,0,256);
			if(iReadRecord("EF08",1,0x01,AN_style,result))
			{
				strdata+="</EF08></DF01></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			strdata+="</EF08></DF01></DATA>";
		}
		if (sDisp=="EF09")
		{	
			strdata+="<DATA><DF01><EF09>";
			memset(result,0,256);
			if(iReadRecord("EF09",1,0x46,AN_style,result))
			{
				strdata+="</EF09></DF01></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF09",2,0x09,AN_style,result))
			{
				strdata+="</EF09></DF01></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF09",3,0x02,AN_style,result))
			{
				strdata+="</EF09></DF01></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";
	
			strdata+="</EF09></DF01></DATA>";

		}
		if (sDisp=="EF0A")
		{	
			strdata+="<DATA><DF01><EF0A>";
			memset(result,0,256);
			if(iReadRecord("EF0A",1,0x03,AN_style,result))
			{
				strdata+="</EF0A></DF01></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF0A",2,0x02,AN_style,result))
			{
				strdata+="</EF0A></DF01></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF0A",3,0x04,CN_style,result))
			{
				strdata+="</EF0A></DF01></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";
	
			strdata+="</EF0A></DF01></DATA>";		
		}
		if (sDisp=="EF15")
		{	
			strdata+="<DATA><DF01><EF15>";
			memset(result,0,256);

			TLV tlv[3]={{"57",0x03,AN_style},{"58",0x03,CN_style},{"59",0x28,AN_style}};
			
			if(iReadRecord("EF15",1,0x01,CN_style,result))
			{
				strdata+="</EF15></DF01></DATA>";
				goto END;
			}

			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			char head[10]={0};
			char tail[10]={0};

			for(int i=2;i<5;i++)
			{
				memset(result,0,256);
				if(iReadBTLV("EF15",i,0x34,tlv,3,result))
				{
					strdata+="</EF15></DF01></DATA>";
					goto END;
				}
				sprintf(head,"<C%02d>",i);
				sprintf(tail,"</C%02d>",i);
				strdata+=head;
				strdata+=result;
				strdata+=tail;	
			}			
			strdata+="</EF15></DF01></DATA>";
		}
	}

	if (sDisp=="DF02") //RK1 DF02
	{
		SelectFile("DDF1");
		SelectFile("DF02");
		unsigned char wordkey[4]={0x67,0x35,0x88};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF02认证失败!");
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
		
		}

		if (sDisp=="EF06")
		{	
			strdata+="<DATA><DF02><EF06>";
			memset(result,0,256);
			if(iReadRecord("EF06",1,0x04,CN_style,result))
			{
				strdata+="</EF06></DF02></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF06",2,0x05,AN_style,result))
			{
				strdata+="</EF06></DF02></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF06",3,0x03,CN_style,result))
			{
				strdata+="</EF06></DF02></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF06",4,0x04,CN_style,result))
			{
				strdata+="</EF06></DF02></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF06",5,0x06,AN_style,result))
			{
				strdata+="</EF06></DF02></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF06",6,0x03,CN_style,result))
			{
				strdata+="</EF06></DF02></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			memset(result,0,256);
			if(iReadRecord("EF06",7,0x07,AN_style,result))
			{
				strdata+="</EF06></DF02></DATA>";
				goto END;
			}
			strdata+="<C07>";
			strdata+=result;
			strdata+="</C07>";

			strdata+="</EF06></DF02></DATA>";
		}
		if (sDisp=="EF07")
		{	
			CYC cy[4]={{0x07,AN_style},{0x04,CN_style},{0x04,CN_style},{0x46,AN_style}};
			strdata+="<DATA><DF02><EF07>";
		//	char head[10]={0};
		//	char tail[10]={0};
			for(int i=1;i<5;i++)
			{
				memset(result,0,256);
				if(iReadXHFile("EF07",i,0x55,cy,4,result))
				{
					strdata+="</EF07></DF02></DATA>";
					goto END;
				}
			//	sprintf(head,"<C%02d>",i);
			//	sprintf(tail,"</C%02d>",i);
			//	strdata+=head;
				strdata+=result;
			//	strdata+=tail;	
			}			
			strdata+="</EF07></DF02></DATA>";

		}
		if (sDisp=="EF09")
		{	
			strdata+="<DATA><DF02><EF09>";
			memset(result,0,256);
			if(iReadRecord("EF09",1,0x10,AN_style,result))
			{
				strdata+="</EF09></DF02></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF09",2,0x46,AN_style,result))
			{
				strdata+="</EF09></DF02></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF09",3,0x04,CN_style,result))
			{
				strdata+="</EF09></DF02></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF09",4,0x03,CN_style,result))
			{
				strdata+="</EF09></DF02></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			strdata+="</EF09></DF02></DATA>";
			
		}
		if (sDisp=="EF15")
		{	
			strdata+="<DATA><DF02><EF15>";
			TLV tlv[3]={{"10",0x03,AN_style},{"11",0x04,CN_style},{"12",0x03,CN_style}};

			char head[10]={0};
			char tail[10]={0};
			for(int i=1;i<5;i++)
			{
				memset(result,0,256);
				if(iReadBTLV("EF15",i,0x10,tlv,3,result))
				{
					strdata+="</EF15></DF02></DATA>";
					goto END;
				}
				sprintf(head,"<C%02d>",i);
				sprintf(tail,"</C%02d>",i);
				strdata+=head;
				strdata+=result;
				strdata+=tail;	
			}
			
			memset(result,0,256);
			if(iReadRecord("EF15",5,0x04,CN_style,result))
			{
				strdata+="</EF15></DF02></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF15",6,0x03,CN_style,result))
			{
				strdata+="</EF15></DF02></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			strdata+="</EF15></DF02></DATA>";
			
		}
		if (sDisp=="EF16")
		{	
			CYC cy[5]={{0x03,AN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style},{0x03,CN_style}};
			strdata+="<DATA><DF02><EF16>";
		//	char head[10]={0};
		//	char tail[10]={0};
			for(int i=1;i<5;i++)
			{
				memset(result,0,256);
				if(iReadXHFile("EF16",i,0x12,cy,5,result))
				{
					strdata+="</EF16></DF02></DATA>";
					goto END;
				}
			//	sprintf(head,"<C%02d>",i);
			//	sprintf(tail,"</C%02d>",i);
			//	strdata+=head;
				strdata+=result;
			//	strdata+=tail;	
			}			
			strdata+="</EF16></DF02></DATA>";
		}
	}
	if (sDisp=="DF03") //RK1 DF03
	{
		SelectFile("DDF1");
		SelectFile("DF03");

		unsigned char wordkey[4]={0x67,0x2B,0x84};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF03认证失败!");
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			unsigned char wordkey[4]={0x67,0x2C,0x85};
			if(ExterAuthen(wordkey,1))
			{
				strcpy(err,"RK2DF03认证失败!");
				return 1;
			}
			strdata+="<DATA><DF03><EF05>";
			
			memset(result,0,256);
			if(iReadRecord("EF05",1,0x03,CN_style,result))
			{
				strdata+="</EF05></DF03></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF05",2,0x04,CN_style,result))
			{
				strdata+="</EF05></DF03></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF05",3,0x04,CN_style,result))
			{
				strdata+="</EF05></DF03></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF05",4,0x03,AN_style,result))
			{
				strdata+="</EF05></DF03></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF05",5,0x03,AN_style,result))
			{
				strdata+="</EF05></DF03></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF05",6,0x03,AN_style,result))
			{
				strdata+="</EF05></DF03></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			memset(result,0,256);
			if(iReadRecord("EF05",7,0x03,AN_style,result))
			{
				strdata+="</EF05></DF03></DATA>";
				goto END;
			}
			strdata+="<C07>";
			strdata+=result;
			strdata+="</C07>";

			strdata+="</EF05></DF03></DATA>";
			
		}
		if (sDisp=="EF06")
		{	
			strdata+="<DATA><DF03><EF06>";
			
			memset(result,0,256);
			if(iReadRecord("EF06",1,0x14,AN_style,result))
			{
				strdata+="</EF06></DF03></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF06",2,0x02,AN_style,result))
			{
				strdata+="</EF06></DF03></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF06",3,0x02,AN_style,result))
			{
				strdata+="</EF06></DF03></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF06",4,0x01,AN_style,result))
			{
				strdata+="</EF06></DF03></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF06",5,0x01,AN_style,result))
			{
				strdata+="</EF06></DF03></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF06",6,0x04,CN_style,result))
			{
				strdata+="</EF06></DF03></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			memset(result,0,256);
			if(iReadRecord("EF06",7,0x3C,AN_style,result))
			{
				strdata+="</EF06></DF03></DATA>";
				goto END;
			}
			strdata+="<C07>";
			strdata+=result;
			strdata+="</C07>";
		
			TLV tlv[5]={{"13",0x02,AN_style},{"14",0x01,AN_style},{"15",0x14,AN_style},{"16",0x04,CN_style},{"17",0x3C,AN_style}};
//			ret = iReadBTLV("EF06",recno,0x61,tlv,5,result);
	
			char head[10]={0};
			char tail[10]={0};
			for(int i=8;i<11;i++)
			{
				memset(result,0,256);
				if(iReadBTLV("EF06",i,0x61,tlv,5,result))
				{
					strdata+="</EF06></DF03></DATA>";
					goto END;
				}
				sprintf(head,"<C%02d>",i);
				sprintf(tail,"</C%02d>",i);
				strdata+=head;
				strdata+=result;
				strdata+=tail;	
			}
			strdata+="</EF06></DF03></DATA>";

		}
		if (sDisp=="EF07")
		{	
			strdata+="<DATA><DF03><EF07>";
			
			memset(result,0,256);
			if(iReadRecord("EF07",1,0x03,AN_style,result))
			{
				strdata+="</EF07></DF03></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF07",2,0x03,CN_style,result))
			{
				strdata+="</EF07></DF03></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF07",3,0x04,CN_style,result))
			{
				strdata+="</EF07></DF03></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF07",4,0x04,CN_style,result))
			{
				strdata+="</EF07></DF03></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF07",5,0x04,CN_style,result))
			{
				strdata+="</EF07></DF03></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF07",6,0x04,CN_style,result))
			{
				strdata+="</EF07></DF03></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			strdata+="</EF07></DF03></DATA>";
			
		}
		if (sDisp=="EF15")
		{	
			strdata+="<DATA><DF03><EF15>";
			
			memset(result,0,256);
			if(iReadRecord("EF15",1,0x03,CN_style,result))
			{
				strdata+="</EF15></DF03></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF15",2,0x04,CN_style,result))
			{
				strdata+="</EF15></DF03></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF15",3,0x04,CN_style,result))
			{
				strdata+="</EF15></DF03></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			strdata+="</EF15></DF03></DATA>";
			
		}
		if (sDisp=="EF16")
		{	
			strdata+="<DATA><DF03><EF16>";
			
			memset(result,0,256);
			if(iReadRecord("EF16",1,0x03,CN_style,result))
			{
				strdata+="</EF16></DF03></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF16",2,0x01,AN_style,result))
			{
				strdata+="</EF16></DF03></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			strdata+="</EF16></DF03></DATA>";
			
		}
		if (sDisp=="EF17")
		{	
			strdata+="<DATA><DF03><EF17>";
			
			memset(result,0,256);
			if(iReadRecord("EF17",1,0x14,AN_style,result))
			{
				strdata+="</EF17></DF03></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF17",2,0x46,AN_style,result))
			{
				strdata+="</EF17></DF03></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF17",3,0x01,AN_style,result))
			{
				strdata+="</EF17></DF03></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF17",4,0x04,CN_style,result))
			{
				strdata+="</EF17></DF03></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF17",5,0x3C,AN_style,result))
			{
				strdata+="</EF17></DF03></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			strdata+="</EF17></DF03></DATA>";
		}
		if (sDisp=="EF18")
		{	
			strdata+="<DATA><DF03><EF18>";
			
			memset(result,0,256);
			if(iReadRecord("EF18",1,0x03,AN_style,result))
			{
				strdata+="</EF18></DF03></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF18",2,0x03,CN_style,result))
			{
				strdata+="</EF18></DF03></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF18",3,0x01,CN_style,result))
			{
				strdata+="</EF18></DF03></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF18",4,0x04,CN_style,result))
			{
				strdata+="</EF18></DF03></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF18",5,0x04,CN_style,result))
			{
				strdata+="</EF18></DF03></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			strdata+="</EF18></DF03></DATA>";

		}
		if (sDisp=="EF19")
		{	
			strdata+="<DATA><DF03><EF19>";
			TLV tlv[7]={{"18",0x03,AN_style},{"19",0x03,CN_style},{"1A",0x04,CN_style},{"1B",0x04,CN_style},{"1C",0x04,CN_style},{"1D",0x03,AN_style},{"1E",0x04,CN_style}};
			
			char head[10]={0};
			char tail[10]={0};
			for(int i=1;i<5;i++)
			{
				memset(result,0,256);
				if(iReadBTLV("EF19",i,0x27,tlv,7,result))
				{
					strdata+="</EF19></DF03></DATA>";
					goto END;
				}
				sprintf(head,"<C%02d>",i);
				sprintf(tail,"</C%02d>",i);
				strdata+=head;
				strdata+=result;
				strdata+=tail;	
			}
			strdata+="</EF19></DF03></DATA>";			
//			TLV tlv[7]={{"18",0x03,AN_style},{"19",0x03,CN_style},{"1A",0x04,CN_style},{"1B",0x04,CN_style},{"1C",0x04,CN_style},{"1D",0x03,AN_style},{"1E",0x04,CN_style}};
//			ret = iReadBTLV("EF19",recno,0x27,tlv,7,result);
		}
	}
	if (sDisp=="DF04") //RK1 DF02
	{
		SelectFile("DDF1");
		SelectFile("DF04");
		unsigned char wordkey[4]={0x67,0x2D,0x84};
		if(ExterAuthen(wordkey,1))
		{
			strcpy(err,"RK1DF04认证失败!");
			return 1;
		}
		unsigned char cmd[20]={0};
		unsigned char resp[10]={0};
		memcpy(cmd,"\x00\x20\x00\x00\x03\x66\x66\x66",8);
		ret = ICC_Reader_Application(Rhand,0x01,8,cmd,resp);//X选择MF文件
		if(ret<2 || resp[0]!=0x90)
		{
			return 1;
		}
		sDisp=strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
		if (sDisp=="EF05")
		{	
			strdata+="<DATA><DF04><EF05>";
			
			memset(result,0,256);
			if(iReadRecord("EF05",1,0x08,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF05",2,0x03,CN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF05",3,0x11,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			memset(result,0,256);
			if(iReadRecord("EF05",4,0x01,CN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C04>";
			strdata+=result;
			strdata+="</C04>";

			memset(result,0,256);
			if(iReadRecord("EF05",5,0x04,CN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C05>";
			strdata+=result;
			strdata+="</C05>";

			memset(result,0,256);
			if(iReadRecord("EF05",6,0x1D,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C06>";
			strdata+=result;
			strdata+="</C06>";

			memset(result,0,256);
			if(iReadRecord("EF05",7,0x0F,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C07>";
			strdata+=result;
			strdata+="</C07>";

			memset(result,0,256);
			if(iReadRecord("EF05",8,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C08>";
			strdata+=result;
			strdata+="</C08>";

			memset(result,0,256);
			if(iReadRecord("EF05",9,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C09>";
			strdata+=result;
			strdata+="</C09>";

			memset(result,0,256);
			if(iReadRecord("EF05",10,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C10>";
			strdata+=result;
			strdata+="</C10>";

			memset(result,0,256);
			if(iReadRecord("EF05",11,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C11>";
			strdata+=result;
			strdata+="</C11>";

			memset(result,0,256);
			if(iReadRecord("EF05",12,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C12>";
			strdata+=result;
			strdata+="</C12>";

			memset(result,0,256);
			if(iReadRecord("EF05",13,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C13>";
			strdata+=result;
			strdata+="</C13>";

			memset(result,0,256);
			if(iReadRecord("EF05",14,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C14>";
			strdata+=result;
			strdata+="</C14>";

			memset(result,0,256);
			if(iReadRecord("EF05",15,0x09,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C15>";
			strdata+=result;
			strdata+="</C15>";

			memset(result,0,256);
			if(iReadRecord("EF05",16,0x01,AN_style,result))
			{
				strdata+="</EF05></DF04></DATA>";
				goto END;
			}
			strdata+="<C16>";
			strdata+=result;
			strdata+="</C16>";

			strdata+="</EF05></DF04></DATA>";

		}
		if (sDisp=="EF06")
		{	
			strdata+="<DATA><DF04><EF06>";
			unsigned char cmd[20]={0};
			unsigned char resp[10]={0};
			memcpy(cmd,"\x00\x20\x00\x00\x03\x66\x66\x66",8);
			ret = ICC_Reader_Application(Rhand,0x01,8,cmd,resp);//X选择MF文件
			if(ret<2 || resp[0]!=0x90)
			{
				return 1;
			}
			memset(result,0,256);
			if(iReadRecord("EF06",1,0x01,AN_style,result))
			{
				strdata+="</EF06></DF04></DATA>";
				goto END;
			}
			strdata+="<C01>";
			strdata+=result;
			strdata+="</C01>";

			memset(result,0,256);
			if(iReadRecord("EF06",2,0x04,CN_style,result))
			{
				strdata+="</EF06></DF04></DATA>";
				goto END;
			}
			strdata+="<C02>";
			strdata+=result;
			strdata+="</C02>";

			memset(result,0,256);
			if(iReadRecord("EF06",3,0x02,AN_style,result))
			{
				strdata+="</EF06></DF04></DATA>";
				goto END;
			}
			strdata+="<C03>";
			strdata+=result;
			strdata+="</C03>";

			strdata+="</EF06></DF04></DATA>";
			

		}
		if (sDisp=="EF08")
		{	
			CYC cy[7]={{0x02,CN_style},{0x01,AN_style},{0x06,CN_style},{0x07,CN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style}};
	
			strdata+="<DATA><DF04><EF08>";
		//	char head[10]={0};
		//	char tail[10]={0};
			unsigned char cmd[20]={0};
			unsigned char resp[10]={0};
			memcpy(cmd,"\x00\x20\x00\x00\x03\x66\x66\x66",8);
			ret = ICC_Reader_Application(Rhand,0x01,8,cmd,resp);//X选择MF文件
			if(ret<2 || resp[0]!=0x90)
			{
				return 1;
			}

			for(int i=1;i<11;i++)
			{
				memset(result,0,256);
				if(iReadXHFile("EF08",i,0x1C,cy,7,result))
				{
					strdata+="</EF08></DF04></DATA>";
					goto END;
				}
			//	sprintf(head,"<C%02d>",i);
			//	sprintf(tail,"</C%02d>",i);
			//	strdata+=head;
				strdata+=result;
			//	strdata+=tail;	
			}			
			strdata+="</EF08></DF04></DATA>";
			
//			CYC cy[7]={{0x02,CN_style},{0x01,AN_style},{0x06,CN_style},{0x07,CN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style}};
		//	ret = iReadXHFile("EF08",recno,0x1C,cy,7,result);
		}
		if (sDisp=="EF15")
		{//	CYC cy[7]={{0x02,CN_style},{0x01,AN_style},{0x06,CN_style},{0x07,CN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style}};

			CYC cy[2]={{0x02,CN_style},{0x01,AN_style}};
			strdata+="<DATA><DF04><EF15>";
		//	char head[10]={0};
		//	char tail[10]={0};
			unsigned char cmd[20]={0};
			unsigned char resp[10]={0};
			memcpy(cmd,"\x00\x20\x00\x00\x03\x66\x66\x66",8);
			ret = ICC_Reader_Application(Rhand,0x01,8,cmd,resp);//X选择MF文件
			if(ret<2 || resp[0]!=0x90)
			{
				return 1;
			}

			for(int i=1;i<9;i++)
			{
				memset(result,0,256);
				if(iReadXHFile("EF15",i,0x03,cy,2,result))
				{
					strdata+="</EF15></DF04></DATA>";
					goto END;
				}
			//	sprintf(head,"<C%02d>",i);
			//	sprintf(tail,"</C%02d>",i);
			//	strdata+=head;
				strdata+=result;
			//	strdata+=tail;	
			}			
			strdata+="</EF15></DF04></DATA>";

		}
	}


END:	strcpy(data,strdata.c_str());
	return 0 ;
}

long SelectFile15(char*data,char*err)//<DF01><EF15><C02><C0257>123</C0257><C0258>123456</C0258><C0259>江西</C0259></C02><C01>12</C01></EF15></DF01>
{
	int st ;
	int ret =0;
	char result[256]={0};
	strdata="";
	sDisp="";
	strdata1 = data;
	long StartLen = strdata1.find("<",0); //DF
	long EndLen = strdata1.find(">",StartLen); 
	long StartLen1 = 0;
	long EndLen1 = 0;
	unsigned char Tag[20]={0};
	unsigned char datalength[20]={0};
	unsigned char style[20]={0};
//	long StartLen1 = strdata1.find("<",EndLen); //EF
//	long EndLen1 = strdata1.find(">",StartLen1); 
//	long StartLen2 = strdata1.find("<",EndLen1); //C
//	long EndLen2 = strdata1.find(">",StartLen2);
	sDisp = strdata1.substr(StartLen+1,EndLen-StartLen-1);
	if (sDisp=="MF" || sDisp=="DDF1")
	{
		SelectFile("DDF1");	
		unsigned char wordkey[4]={0x48,0x12,0x04};
		if(ExterAuthen(wordkey,2))
		{
			strcpy(err,"UKSSSE认证失败!");
			return 1;
		}
		while(true)
		{
			memset(Tag,0,20);
			memset(datalength,0,20);
			memset(style,0,20);
			StartLen1 = strdata1.find("<",EndLen); //EF
			int posit =0;
			posit = strdata1.find("<C",EndLen); //EF
			if(posit<0)
				break;
			EndLen1 = strdata1.find(">",StartLen1);
			sDisp = strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
			if(sDisp == "EF05")
			{
				memcpy(Tag,"\x01\x02\x03\x04\x05\x06\x07",7);
				memcpy(datalength,"\x10\x01\x04\x0C\x04\x04\x09",7);
				memcpy(style,"\x0F\x01\x01\x0F\x0F\x0F\x01",7);
			}
			else if(sDisp == "EF06")
			{
				memcpy(Tag,"\x08\x09\x4E\x0A\x0B\x0C\x0D",7);
				memcpy(datalength,"\x12\x1E\x14\x01\x01\x03\x04",7);
				memcpy(style,"\x01\x01\x01\x01\x0F\x0F\x0F",7);
			}
			else
			{
				strcpy(err,"该EF文件不存在");
				strcpy(data,"<DATA>99</DATA>");
				return 1;
			}
			char Fid[5]={0};
			strcpy(Fid,sDisp.c_str());

			StartLen = strdata1.find("</EF",EndLen1);// </C
			EndLen = strdata1.find(">",StartLen);

			sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);
			char datatemp[256]={0};
			strcpy(datatemp,sDisp.c_str());
			if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
			{
				strcpy(err,"写入");
				strcat(err,Fid);
				strcat(err,"失败");
				strcpy(data,"<DATA>99</DATA>");
				return 1;
			}
		}
	}
	else if(sDisp == "DF01")
	{
		SelectFile("DF01");	
		while(true)
		{
			strdata1 = data;
			memset(Tag,0,20);
			memset(datalength,0,20);
			memset(style,0,20);
			StartLen1 = strdata1.find("<",EndLen); //EF
			int posit =0;
			posit = strdata1.find("<C",EndLen); //EF
			if(posit<0)
				break;
			EndLen1 = strdata1.find(">",StartLen1);

			sDisp = strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
			if(sDisp == "EF05")
			{	
				unsigned char wordkey[4]={0x48,0x42,0x83};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK1DF01认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x20\x21\x0E",3);
				memcpy(datalength,"\x02\x50\x03",3);
				memcpy(style,"\x01\x01\x0F",3);
			}
			else if(sDisp == "EF06")
			{
				unsigned char wordkey[4]={0x47,0x25,0x86};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK4DF01认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x23\x24\x28\x2C\x2D",5);
				memcpy(datalength,"\x50\x03\x0F\x32\x0F",5);
				memcpy(style,"\x01\x0F\x01\x01\x01",5);
			}
			else if(sDisp == "EF07")
			{
				unsigned char wordkey[4]={0x48,0x43,0x84};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK2DF01认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x29",1);
				memcpy(datalength,"\x01",1);
				memcpy(style,"\x01",1);
			}
			else if(sDisp == "EF08")
			{
				unsigned char wordkey[4]={0x47,0x24,0x85};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK3DF01认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x2B",1);
				memcpy(datalength,"\x01",1);
				memcpy(style,"\x01",1);
			}
			else if(sDisp == "EF09")
			{
				unsigned char wordkey[4]={0x48,0x43,0x84};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK2DF01认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x2E\x30\x32",3);
				memcpy(datalength,"\x46\x09\x02",3);
				memcpy(style,"\x01\x01\x01",3);
			}
			else if(sDisp == "EF0A")
			{
				unsigned char wordkey[4]={0x48,0x44,0x87};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK5DF01认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x37\x38\x39",3);
				memcpy(datalength,"\x03\x02\x04",3);
				memcpy(style,"\x01\x01\x0F",3);
			}
			else if(sDisp == "EF15")//如果是记录文件<C0X>..</C0X> TLV <C0XYY>..<COXYY>
			{
				unsigned char wordkey[4]={0x47,0x2F,0x89};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK6DF01认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}	
				TLV tlv[3]={{"57",0x03,AN_style},{"58",0x03,CN_style},{"59",0x28,AN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());
				while(true)
				{
					strdata1 = data;
					StartLen = strdata1.find("<",EndLen1);// <C01
					int posit =0;
					posit = strdata1.find("<C",EndLen1); //EF
					if(posit<0)
					{
						StartLen = strdata1.find("</EF",EndLen1);// </EF
						EndLen = strdata1.find(">",StartLen);
						break;
					}
					EndLen = strdata1.find(">",StartLen);
				
					sDisp = strdata1.substr(StartLen+2,EndLen-StartLen-1);//
					int recNo = atoi(sDisp.c_str());
					if(recNo==1)
					{
						memcpy(Tag,"\x2A",1);
						memcpy(datalength,"\x01",1);
						memcpy(style,"\x0F",1);

						StartLen1 = strdata1.find("<",EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(StartLen,EndLen1-StartLen+1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());
						if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							strcpy(data,"<DATA>99</DATA>");
							return 1;
						}
					}
					else if(recNo >1 && recNo <5)
					{
						sDisp = strdata1.substr(StartLen,EndLen-StartLen+1);
						sDisp.insert(1,"/");
						StartLen1 = strdata1.find(sDisp.c_str(),EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(EndLen+1,StartLen1-EndLen-1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());

						if(iWriteBTLV(Fid,recNo,0x34,tlv,3,datatemp,0x40))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							strcpy(data,"<DATA>99</DATA>");
							return 1;
						}
					}
					else
					{
						strcpy(err,"传入参数有误");
						strcpy(data,"<DATA>99</DATA>");
						return 1;
					}
				}
				
			}
			else
			{
				strcpy(err,"该EF文件不存在");
				strcpy(data,"<DATA>99</DATA>");
				return 1;
			}

			if(sDisp != "EF15")
			{
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// </EF
				EndLen = strdata1.find(">",StartLen);

				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());
				if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}	
			}		
		}
	}
	else if(sDisp == "DF02")
	{
		SelectFile("DF02");
		while(true)
		{
			strdata1 = data;
			memset(Tag,0,20);
			memset(datalength,0,20);
			memset(style,0,20);
			StartLen1 = strdata1.find("<",EndLen); //EF
			int posit =0;
			posit = strdata1.find("<C",EndLen); //EF
			if(posit<0)
				break;
			EndLen1 = strdata1.find(">",StartLen1);

			sDisp = strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
			if(sDisp == "EF05")
			{
				strcpy(err,"该文件不支持");
				strcpy(data,"<DATA>99</DATA>");
				return 1;
			}
			else if(sDisp == "EF06")
			{
				unsigned char wordkey[4]={0x48,0x45,0x84};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK2DF02认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x4C\x4B\x4D\x60\x4F\x50\x3A",7);
				memcpy(datalength,"\x04\x05\x03\x04\x06\x03\x07",7);
				memcpy(style,"\x0F\x01\x0F\x0F\x01\x0F\x01",7);
			}
			else if(sDisp == "EF07")//<DF02><EF07><C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04></EF07></DF02>
			{
				unsigned char wordkey[4]={0x48,0x46,0x85};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK3DF02认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				CYC cy[4]={{0x07,AN_style},{0x04,CN_style},{0x04,CN_style},{0x46,AN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// 
				EndLen = strdata1.find(">",StartLen);
				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);//					
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());	
				if(iWriteXHFile(Fid,0,0x55,cy,4,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
			}
			else if(sDisp == "EF09")
			{
				unsigned char wordkey[4]={0x47,0x27,0x86};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK4DF02认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x55\x56\x96\x97",4);
				memcpy(datalength,"\x10\x46\x04\x03",4);
				memcpy(style,"\x01\x01\x0F\x0F",4);
			}
			
			else if(sDisp == "EF15")//如果是记录文件<C0X>..</C0X> TLV <C0XYY>..<COXYY>
			{
				unsigned char wordkey[4]={0x47,0x28,0x87};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK5DF02认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				TLV tlv[3]={{"10",0x03,AN_style},{"11",0x04,CN_style},{"12",0x03,CN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());
				while(true)
				{
					strdata1 = data;
					StartLen = strdata1.find("<",EndLen1);// <C01
					int posit =0;
					posit = strdata1.find("<C",EndLen1); //EF
					if(posit<0)
					{
						StartLen = strdata1.find("</EF",EndLen1);// </EF
						EndLen = strdata1.find(">",StartLen);
						break;
					}
					EndLen = strdata1.find(">",StartLen);
				
					sDisp = strdata1.substr(StartLen+2,EndLen-StartLen-1);//
					int recNo = atoi(sDisp.c_str());
					if(recNo>4)
					{
						memcpy(Tag,"\x0F\1F",2);
						memcpy(datalength,"\x04\x03",2);
						memcpy(style,"\x0F\x0F",2);

						StartLen1 = strdata1.find("<",EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(StartLen,EndLen1-StartLen+1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());
						if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							strcpy(data,"<DATA>99</DATA>");
							return 1;
						}
					}
					else if(recNo >=1 && recNo <5)
					{
						sDisp = strdata1.substr(StartLen,EndLen-StartLen+1);
						sDisp.insert(1,"/");
						StartLen1 = strdata1.find(sDisp.c_str(),EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(EndLen+1,StartLen1-EndLen-1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());

						if(iWriteBTLV(Fid,recNo,0x10,tlv,3,datatemp,0x99))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							strcpy(data,"<DATA>99</DATA>");
							return 1;
						}
					}
					else
					{
						strcpy(err,"传入参数有误");
						strcpy(data,"<DATA>99</DATA>");
						return 1;
					}
				}			
			}
			else if(sDisp == "EF16")//<DF02><EF07><C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04></EF07></DF02>
			{
				unsigned char wordkey[4]={0x47,0x36,0x89};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK6DF02认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				CYC cy[5]={{0x03,AN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style},{0x03,CN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// 
				EndLen = strdata1.find(">",StartLen);
				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);//					
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());	
				if(iWriteXHFile(Fid,0,0x12,cy,5,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
			}
			else
			{
				strcpy(err,"该EF文件不存在");
				strcpy(data,"<DATA>99</DATA>");
				return 1;
			}
			
			if(sDisp == "EF06" || sDisp== "EF09" )
			{
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// </EF
				EndLen = strdata1.find(">",StartLen);

				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());
				if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}	
			}		
		}
	}
	else if(sDisp == "DF03")
	{
		SelectFile("DF03");
		while(true)
		{
			strdata1 = data;
			memset(Tag,0,20);
			memset(datalength,0,20);
			memset(style,0,20);
			StartLen1 = strdata1.find("<",EndLen); //EF
			int posit =0;
			posit = strdata1.find("<C",EndLen); //EF
			if(posit<0)
				break;
			EndLen1 = strdata1.find(">",StartLen1);

			sDisp = strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
			if(sDisp == "EF05")
			{
				unsigned char wordkey[4]={0x48,0x47,0x86};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK1DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x61\x98\x62\x63\x64\x65\x66",7);
				memcpy(datalength,"\x03\x04\x04\x03\x03\x03\x03",7);
				memcpy(style,"\x0F\x0F\x0F\x01\x01\x01\x01",7);
			}
			else if(sDisp == "EF06")
			{
				unsigned char wordkey[4]={0x47,0x29,0x87};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK2DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				TLV tlv[5]={{"13",0x02,AN_style},{"14",0x01,AN_style},{"15",0x14,AN_style},{"16",0x04,CN_style},{"17",0x3C,AN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());
				while(true)
				{
					strdata1 = data;
					StartLen = strdata1.find("<",EndLen1);// <C01
					int posit =0;
					posit = strdata1.find("<C",EndLen1); //EF
					if(posit<0)
					{
						StartLen = strdata1.find("</EF",EndLen1);// </EF
						EndLen = strdata1.find(">",StartLen);
						break;
					}
					EndLen = strdata1.find(">",StartLen);
				
					sDisp = strdata1.substr(StartLen+2,EndLen-StartLen-1);//
					int recNo = atoi(sDisp.c_str());
					if(recNo<8)
					{
						memcpy(Tag,"\x45\x46\x47\x48\x49\x67\x6B",7);
						memcpy(datalength,"\x14\x02\x02\x01\x01\x04\x3C",7);
						memcpy(style,"\x01\x01\x01\x01\x01\x0F\x01",7);

						StartLen1 = strdata1.find("<",EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(StartLen,EndLen1-StartLen+1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());
						if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							strcpy(data,"<DATA>99</DATA>");
							return 1;
						}
					}
					else if(recNo > 7 && recNo < 11)
					{
						sDisp = strdata1.substr(StartLen,EndLen-StartLen+1);
						sDisp.insert(1,"/");
						StartLen1 = strdata1.find(sDisp.c_str(),EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(EndLen+1,StartLen1-EndLen-1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());

						if(iWriteBTLV(Fid,recNo,0x61,tlv,5,datatemp,0x4A))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							strcpy(data,"<DATA>99</DATA>");
							return 1;
						}
					}
					else
					{
						strcpy(err,"传入参数有误");
						strcpy(data,"<DATA>99</DATA>");
						return 1;
					}
				}
			}
			else if(sDisp == "EF07")//<DF02><EF07><C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04></EF07></DF02>
			{
				unsigned char wordkey[4]={0x48,0x48,0x88};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK3DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x70\x71\x6E\x6C\x6F\x73",6);
				memcpy(datalength,"\x03\x03\x04\x04\x04\x04",6);
				memcpy(style,"\x01\x0F\x0F\x0F\x0F\x0F",6);

			/*	CYC cy[4]={{0x07,AN_style},{0x04,CN_style},{0x04,CN_style},{0x46,AN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// 
				EndLen = strdata1.find(">",StartLen);
				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);//					
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());	
				if(iWriteXHFile(Fid,0,0x55,cy,4,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					return 1;
				}*/
			}
			else if(sDisp == "EF15")
			{
				unsigned char wordkey[4]={0x47,0x37,0x89};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK4DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x7A\x7B\x7C",3);
				memcpy(datalength,"\x03\x04\x04",3);
				memcpy(style,"\x0F\x0F\x0F",3);
			}
			else if(sDisp == "EF16")
			{
				unsigned char wordkey[4]={0x47,0x38,0x8A};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK5DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x51\x5F",2);
				memcpy(datalength,"\x03\x01",2);
				memcpy(style,"\x0F\x01",2);
			}
			else if(sDisp == "EF17")
			{
				unsigned char wordkey[4]={0x47,0x39,0x8B};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK6DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x3B\x3C\x3D\x3E\x3F",5);
				memcpy(datalength,"\x14\x46\x01\x04\x3C",5);
				memcpy(style,"\x01\x01\x01\x0F\x01",5);
			}
			else if(sDisp == "EF18")
			{
				unsigned char wordkey[4]={0x47,0x3A,0x8C};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK7DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x74\x75\x76\x77\x78",5);
				memcpy(datalength,"\x03\x03\x01\x04\x04",5);
				memcpy(style,"\x01\x0F\x0F\x0F\x0F",5);
			}		
			else if(sDisp == "EF19")//如果是记录文件<C0X>..</C0X> TLV <C0XYY>..<COXYY>
			{
				unsigned char wordkey[4]={0x47,0x3B,0x8D};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK8DF03认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				TLV tlv[7]={{"18",0x03,AN_style},{"19",0x03,CN_style},{"1A",0x04,CN_style},{"1B",0x04,CN_style},{"1C",0x04,CN_style},{"1D",0x03,AN_style},{"1E",0x04,CN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());
				while(true)
				{
					strdata1 = data;
					StartLen = strdata1.find("<",EndLen1);// <C01
					int posit =0;
					posit = strdata1.find("<C",EndLen1); //EF
					if(posit<0)
					{
						StartLen = strdata1.find("</EF",EndLen1);// </EF
						EndLen = strdata1.find(">",StartLen);
						break;
					}
					EndLen = strdata1.find(">",StartLen);
				
					sDisp = strdata1.substr(StartLen+2,EndLen-StartLen-1);//
					int recNo = atoi(sDisp.c_str());
				/*	if(recNo>4)
					{
						memcpy(Tag,"\x2A",1);
						memcpy(datalength,"\x01",1);
						memcpy(style,"\x0F",1);

						StartLen1 = strdata1.find("<",EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(StartLen,EndLen1-StartLen+1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());
						if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							return 1;
						}
					}*/
					if(recNo >=1 && recNo <5)
					{
						sDisp = strdata1.substr(StartLen,EndLen-StartLen+1);
						sDisp.insert(1,"/");
						StartLen1 = strdata1.find(sDisp.c_str(),EndLen);// </C
						EndLen1 = strdata1.find(">",StartLen1);

						sDisp = strdata1.substr(EndLen+1,StartLen1-EndLen-1);
						char datatemp[256]={0};
						strcpy(datatemp,sDisp.c_str());

						if(iWriteBTLV(Fid,recNo,0x27,tlv,7,datatemp,0x79))
						{
							strcpy(err,"写入");
							strcat(err,Fid);
							strcat(err,"失败");
							strcpy(data,"<DATA>99</DATA>");
							return 1;
						}
					}
					else
					{
						strcpy(err,"传入参数有误");
						strcpy(data,"<DATA>99</DATA>");
						return 1;
					}
				}			
			}
			else //<DF02><EF07><C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04></EF07></DF02>
			{
				strcpy(err,"传入参数有误");
				strcpy(data,"<DATA>99</DATA>");
				return 1;
			}
			
			if(sDisp == "EF07" || sDisp== "EF15" || sDisp== "EF16" || sDisp== "EF17" || sDisp== "EF18" || sDisp== "EF05")
			{
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// </EF
				EndLen = strdata1.find(">",StartLen);

				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());
				if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}	
			}		
		}
	}
	else if(sDisp == "DF04")
	{
		SelectFile("DF04");
		while(true)
		{
			strdata1 = data;
			memset(Tag,0,20);
			memset(datalength,0,20);
			memset(style,0,20);
			StartLen1 = strdata1.find("<",EndLen); //EF
			int posit =0;
			posit = strdata1.find("<C",EndLen); //EF
			if(posit<0)
				break;
			EndLen1 = strdata1.find(">",StartLen1);

			sDisp = strdata1.substr(StartLen1+1,EndLen1-StartLen1-1);
			if(sDisp == "EF05")
			{
				unsigned char wordkey[4]={0x48,0x49,0x85};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK1DF04认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x81\x84\x87\x8C\x80\x8B\x8A\x83\x86\x89\x7D\x7E\x7F\x8D\x8E\x8F",16);
				memcpy(datalength,"\x08\x03\x11\x01\x04\x1D\x0F\x09\x09\x09\x09\x09\x09\x09\x09\x01",16);
				memcpy(style,"\x01\x0F\x01\x0F\x0F\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01",16);
			}
			else if(sDisp == "EF06")
			{
				unsigned char wordkey[4]={0x47,0x2A,0x86};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK2DF04认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				memcpy(Tag,"\x90\x92\x93",3);
				memcpy(datalength,"\x01\x04\x02",3);
				memcpy(style,"\x01\x0F\x01",3);
			}
			else if(sDisp == "EF08")//<DF02><EF07><C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04></EF07></DF02>
			{
				strcpy(err,"传入参数有误");
				strcpy(data,"<DATA>99</DATA>");
				return 1;

			/*	CYC cy[7]={{0x02,CN_style},{0x01,AN_style},{0x06,CN_style},{0x07,CN_style},{0x04,CN_style},{0x04,CN_style},{0x04,CN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// 
				EndLen = strdata1.find(">",StartLen);
				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);//					
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());	
				if(iWriteXHFile(Fid,0,0x1C,cy,7,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					return 1;
				}*/
			}
			else if(sDisp == "EF15")//<DF02><EF07><C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04></EF07></DF02>
			{
				unsigned char wordkey[4]={0x47,0x2A,0x86};
				if(ExterAuthen(wordkey,2))
				{
					strcpy(err,"UK2DF04认证失败!");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
				CYC cy[2]={{0x02,CN_style},{0x01,AN_style}};
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// 
				EndLen = strdata1.find(">",StartLen);
				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);//					
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());	
				if(iWriteXHFile(Fid,0,0x03,cy,2,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}
			}		
			else //<DF02><EF07><C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04></EF07></DF02>
			{
				strcpy(err,"传入参数有误");
				strcpy(data,"<DATA>99</DATA>");
				return 1;
			}
			
			if(sDisp == "EF05" || sDisp== "EF06" )
			{
				char Fid[5]={0};
				strcpy(Fid,sDisp.c_str());

				StartLen = strdata1.find("</EF",EndLen1);// </EF
				EndLen = strdata1.find(">",StartLen);

				sDisp = strdata1.substr(EndLen1+1,StartLen-EndLen1-1);
				char datatemp[256]={0};
				strcpy(datatemp,sDisp.c_str());
				if(iWriteRecord(Fid,Tag,0,datalength,style,datatemp))
				{
					strcpy(err,"写入");
					strcat(err,Fid);
					strcat(err,"失败");
					strcpy(data,"<DATA>99</DATA>");
					return 1;
				}	
			}		
		}
	}
	else
	{
		strcpy(err,"传入参数有误");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	strcpy(data,"<DATA>00</DATA>");
	return 0;
}

long iReadRecord(char *EFid,int recNO,int datalength,int style,char *result)//读取记录文件 
{
	unsigned char resp[256];
	unsigned char cmd[260];
	sDisp="";
	int n=0;
//	strdata1=data;

	memset(resp,0,256);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
	cmd[5]=chartoint(EFid[0])*16+chartoint(EFid[1]);
	cmd[6]=chartoint(EFid[2])*16+chartoint(EFid[3]);	
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	if(ret<2 || resp[0]!=0x90)
	{
		return 1;
	}

	memcpy(cmd, "\x00\xB2\x00\x04\x00",5);
	cmd[2]=recNO;
	cmd[4]=datalength+2;

	memset(resp,0,256);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	if (ret<0 || (resp[ret-2]!=0x90))
	{
		return 1;
	}
	char temp[300]={0};
	if(style==AN_style)
	{
		for(  n=0;n<(ret-2);n++)
		{
			temp[n]=resp[n];		
		}
		sDisp = (char*)temp;
		int len = sDisp.length();

		memcpy(result,temp+2,len-2);			
	}
	else if(style == CN_style)
	{
		char data1[3]={0};
		for( n=0;n<(ret-2);n++)
		{
			sprintf(data1,"%02x",resp[n]);
			strcat(temp,data1);  
		}
		int len = strlen(temp);
		
		memcpy(result,temp+4,len-4);
	}
	return 0;		
}

long iReadBinary(char *EFid,int recNO,int datalength,int style,char *result)
{
	unsigned char resp[256];
	unsigned char cmd[260];
	strdata1="";
	sDisp="";
	int n=0;
//	strdata1=data;

	memset(resp,0,100);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
	cmd[5]=chartoint(EFid[0])*16+chartoint(EFid[1]);
	cmd[6]=chartoint(EFid[2])*16+chartoint(EFid[3]);	
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	if(ret<2 || resp[0]!=0x90)
	{
	//	strcpy(err,"没有找到文件");
	//	strcat(err,EFid);
		return 1;
	}

	memcpy(cmd, "\x00\xB0\x00\x04\x00",5);
	cmd[2]=recNO;
	cmd[4]=datalength;

	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	if (ret<0 || (resp[ret-2]!=0x90))
	{
	//	strcpy(err,"读取文件失败");
		return 1;
	}
	char temp[300]={0};
	if(style==AN_style)
	{
		for(  n=0;n<(ret-2);n++)
		{
			temp[n]=resp[n];		
		}
		sDisp = (char*)temp;
		int len = sDisp.length();

		memcpy(result,temp+2,len-2);			
	}
	else if(style == CN_style)
	{
		char data1[3]={0};
		for( n=0;n<(ret-2);n++)
		{
			sprintf(data1,"%02x",resp[n]);
			strcat(temp,data1);  
		}
		int len = strlen(temp);
		
		memcpy(result,temp+4,len-4);
	}
	
	return 0;		
}

long SelectFile(char *FileId)
{
	unsigned char resp[256];
	unsigned char cmd[260];
	sDisp="";
	int n=0;
//	strdata1=data;

	memset(resp,0,100);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
	cmd[5]=chartoint(FileId[0])*16+chartoint(FileId[1]);
	cmd[6]=chartoint(FileId[2])*16+chartoint(FileId[3]);	
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	if(ret<2 || (resp[0]!=0x61 && resp[0]!=0x90))
	{
	//	strcpy(err,"没有找到文件");
	//	strcat(err,EFid);
		return 1;
	}
	return 0;
}

long GetRandom()
{
	unsigned char resp[256]={0};
	unsigned char cmd[260]={0};

	long ret=0;

	memcpy(cmd, "\x00\x84\x00\x00\x08",5);
	
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);//X选择MF文件
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		return 1;
	}
	memcpy(_Random,resp,8);

	return 0;	
}
static DWORD WINAPI SendProc(PVOID p)
{
	unsigned char cpass[20]={0};
	WaitForSingleObject(g_hEvent, INFINITE);
	unsigned char len ;
	long re = ICC_GetInputPass(Rhand, 20,&len,0,0, cpass);
	SetEvent(g_hEvent);

	return 0;
}


long GetPassWord(char*data,char*err)
{
	/*参数说明： BaudRate,: 波特率 1200或9600
	Soundmode: 声音提示方式 0 请输入密码 ，1 。请在输入一次
	*Password：保存用户输入的密码。*/
	WaitForSingleObject(g_hEvent, INFINITE);
//	HANDLE hThread = CreateThread(NULL,0,SendProc,0,0,NULL);
//	ICC_DispSound(Rhand,4);
	Sleep(200);
	unsigned char cpass[20]={0};
	unsigned char len ;
	long re = ICC_GetInputPass(Rhand, 60,&len,0,0, cpass);
	
//	HANDLE hThread = CreateThread(NULL,0,SendProc,0,0,NULL);
//	WaitForSingleObject(g_hEvent, INFINITE);
	if(re==0 && len ==0)
		re = -13;

	for(int j=0;j<len;j++)
	{
		cpass[j] = cpass[j] - 0x30;
	}

	char temp[3]={0};
	char password[100]={0};

	for(int i=0;i<len;i++)
	{
		if(cpass[i]>0x10)
		{
			re = -3;
			break;
		}
		sprintf(temp,"%x",cpass[i]);
		strcat(password,temp);
	}
	
	SetEvent(g_hEvent);
	if(re!=0)
	{
		switch(re)
		{
			case -12:strcpy(err,"端口没有打开");break;
			case -1:strcpy(err,"发送数据失败");break;
			case -2:strcpy(err,"超时错误");break;
			case -13:strcpy(err,"按下确定键退出");break;
			default:strcpy(err,"出错，请重新拔插加密键盘");break;
		}
		return 1;
	}

	strcpy(data,"<DATA>");
	strcat(data,password);
	strcat(data,"</DATA>");

/*	unsigned char readchar[10]={0};
	char tempdata[100]={0};
	long readlen=0;
	int ret=0;
	for(int i=1;i<15;i++)
	{
		ret = OpenComPort(i, 1200);
		if(ret==0)
		{
			if(InitKeyBoard()==0)
				break;
		}
			
	}
	if(i==15)
		return -1;
	KeyPadPlaintxtMod(0x82);
	int re = 0;

	while (!re)
	{
		memset(readchar,0,10);
		re = ReadCharFromKeyPad(readchar, &readlen);
		if(readchar[0]==0x0d || re!=0)
			break;
		strcat(tempdata,(char*)readchar);
	}
	CloseComPort();
	strcpy(data,tempdata);
*/
	return 0;
}

long PerPINVerify(char*data,char*err)
{
	unsigned char resp[100]={0};
	unsigned char cmd[260]={0};
	unsigned char temp[100]={0};
	strdata="";
	sDisp="";
	long ret;
	memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF",20);
	//00A404000F7378312E73682EC9E7BBE1B1A3D5CF
	ret = ICC_Reader_Application(Rhand,0x01,20,cmd,resp);//X选择MF文件
	
	strdata = data;
	long EndLen = strdata.find("<",2);
	long StartLen = strdata.find(">",0); 
	sDisp = strdata.substr(StartLen+1,EndLen-StartLen-1);
	

	memcpy(cmd, "\x00\x20\x00\x00",5);
	int len = sDisp.length()/2;
	cmd[4]=len;
	strcpy((char*)temp,sDisp.c_str());
	for(int i=0;i<len;i++)
	{
		cmd[5+i]=(temp[2*i]-0x30)*16+temp[2*i+1]-0x30;
	}
	memset(resp,0,100);
	ret = ICC_Reader_Application(Rhand,0x01,len+5,cmd,resp);
	if (ret<0)
	{
		sprintf(err,"%d",ret);
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}

	if(resp[0]!=0x90 && resp[1]!=0x00)
	{
		switch(resp[1])
		{
			case 0xc5:strcpy(err,"密钥认证错误,剩余5次");break;
			case 0xc4:strcpy(err,"密钥认证错误,剩余4次");break;
			case 0xc3:strcpy(err,"密钥认证错误,剩余3次");break;
			case 0xc2:strcpy(err,"密钥认证错误,剩余2次");break;
			case 0xc1:strcpy(err,"密钥认证错误,剩余1次");break;
			case 0xc0:strcpy(err,"密钥认证错误,剩余0次");break;
			default:strcpy(err,"密码被锁！");break;
		}

		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}

	strcpy(data,"<DATA>00</DATA>");
	return 0;
}

long ExterAuthen(unsigned char *WorkKey,int level)//
{
	unsigned char cmd[100]={0};
	unsigned char resp[100]={0};

	GetRandom();

	memset(cmd,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDF\x01",7);
	int ret = ICC_Reader_Application(Rhand,0x11,7,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90 && resp[ret-2]!=0x61))
	{
		return -1;
	}
	memcpy(cmd, "\xBF\xDE\x67\x08\x20",5); //一级
	cmd[2]=WorkKey[0];
	cmd[3]=WorkKey[1];

	if(level==1)//一级
	{
		cmd[4]=0x20;
		cmd[5]=_ATR[0];
		cmd[6]=_ATR[1];
		cmd[7]=_ATR[2];
		cmd[8]=_ATR[3];
		cmd[9]=_ATR[4];
		cmd[10]=_ATR[5];
		cmd[11]=_ATR[6];
		cmd[12]=_ATR[7];

		cmd[13]=_CityCode[0];
		cmd[14]=_CityCode[1];
		cmd[15]=_CityCode[2];
		cmd[16]=_CityCode[3];
		cmd[17]=_CityCode[4];
		cmd[18]=_CityCode[5];
		cmd[19]=0x73;
		cmd[20]=0x78;

		cmd[21]=_CityCode[0];
		cmd[22]=_CityCode[1];
		cmd[23]=0x30;
		cmd[24]=0x30;
		cmd[25]=0x30;
		cmd[26]=0x30;
		cmd[27]=0x73;
		cmd[28]=0x68;
		
		cmd[29]=_Random[0];
		cmd[30]=_Random[1];
		cmd[31]=_Random[2];
		cmd[32]=_Random[3];
		cmd[33]=_Random[4];
		cmd[34]=_Random[5];
		cmd[35]=_Random[6];
		cmd[36]=_Random[7];

		ret = ICC_Reader_Application(Rhand,0x11,37,cmd,resp);
		if(ret<2 || (resp[ret-2]!=0x90))
		{
			return -1;
		}
	}
	else if(level ==2)//二级
	{
		cmd[4]=0x18;
		cmd[5]=_ATR[0];
		cmd[6]=_ATR[1];
		cmd[7]=_ATR[2];
		cmd[8]=_ATR[3];
		cmd[9]=_ATR[4];
		cmd[10]=_ATR[5];
		cmd[11]=_ATR[6];
		cmd[12]=_ATR[7];

		cmd[13]=_CityCode[0];
		cmd[14]=_CityCode[1];
		cmd[15]=_CityCode[2];
		cmd[16]=_CityCode[3];
		cmd[17]=_CityCode[4];
		cmd[18]=_CityCode[5];
		cmd[19]=0x73;
		cmd[20]=0x78;
		cmd[21]=_Random[0];
		cmd[22]=_Random[1];
		cmd[23]=_Random[2];
		cmd[24]=_Random[3];
		cmd[25]=_Random[4];
		cmd[26]=_Random[5];
		cmd[27]=_Random[6];
		cmd[28]=_Random[7];
		ret = ICC_Reader_Application(Rhand,0x11,29,cmd,resp);
		if(ret<2 || (resp[ret-2]!=0x90))
		{
			return -1;
		}
	}
	else if(level == 3)//三级
	{
		cmd[4]=0x10;
		cmd[5]=_ATR[0];
		cmd[6]=_ATR[1];
		cmd[7]=_ATR[2];
		cmd[8]=_ATR[3];
		cmd[9]=_ATR[4];
		cmd[10]=_ATR[5];
		cmd[11]=_ATR[6];
		cmd[12]=_ATR[7];

		cmd[13]=_Random[0];
		cmd[14]=_Random[1];
		cmd[15]=_Random[2];
		cmd[16]=_Random[3];
		cmd[17]=_Random[4];
		cmd[18]=_Random[5];
		cmd[19]=_Random[6];
		cmd[20]=_Random[7];
		ret = ICC_Reader_Application(Rhand,0x11,21,cmd,resp);
		if(ret<2 || (resp[ret-2]!=0x90))
		{
			return -1;
		}
	}
	else
		return -1;

	memset(cmd,0,50);
	memcpy(cmd, "\x80\xFA\x00\x00\x08\x01\x02\x03\x04\x05\x06\x07\x08",13);//对鉴别因子加密
	ret = ICC_Reader_Application(Rhand,0x11,13,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x61))
	{
		return -1;
	}
	memset(cmd,0,50);
	memcpy(cmd, "\x00\xc0\x00\x00\x08",5);
	ret = ICC_Reader_Application(Rhand,0x11,5,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		return -1;
	}

	memset(cmd,0,50);
	memcpy(cmd,"\x00\x82\x00\x00\x10",5);
	cmd[3]=WorkKey[2];
	memcpy(cmd+5,resp,8);
	memcpy(cmd+13,"\x01\x02\x03\x04\x05\x06\x07\x08",8);

	ret = ICC_Reader_Application(Rhand,0x01,21,cmd,resp);
	if(resp[0]!=0x90 || ret<2)
		return -1;

	return 0;
}

long iReadBTLV(char *EFid,int recNO,int datalength,TLV *tl,int size,char *result) //recNO 记录号  size 数据项
{
	unsigned char resp[256];
	unsigned char cmd[260];
	sDisp="";
	int n=0;
//	strdata1=data;
	memset(resp,0,256);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
	cmd[5]=chartoint(EFid[0])*16+chartoint(EFid[1]);
	cmd[6]=chartoint(EFid[2])*16+chartoint(EFid[3]);	
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	if(ret<2 || resp[0]!=0x90)
	{
		return 1;
	}

	memcpy(cmd, "\x00\xB2\x00\x04\x00",5);
	cmd[2]=recNO;
	cmd[4]=datalength+2;
	
	memset(resp,0,256);
	ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
	if (ret<0 || (resp[ret-2]!=0x90))
	{
		return 1;
	}
	char head[10]={0};
	char tail[10]={0};
	char sno[3]={0};
	sprintf(sno,"%02d",recNO);
	char temp[512]={0};
	strcpy(head,"<C");
	strcat(head,sno);
	strcpy(tail,"</C");
	strcat(tail,sno);
	unsigned char tempdata[256]={0};
	int total_len=0;
	for(int i=0;i<size;i++)
	{
		memset(tempdata,0,256);
		memcpy(head+4,tl[i].flag,2);
		memcpy(head+6,">",1);
		memcpy(tail+5,tl[i].flag,2);
		memcpy(tail+7,">",1);
		strcat(result,head);
		memcpy(tempdata,resp+total_len+2,tl[i].length+2);

		if(tl[i].datastyle==AN_style)
		{
			strcat(result,(char*)tempdata+2);			
		}
		else if(tl[i].datastyle == CN_style)
		{
			char data1[3]={0};
			char data2[300]={0};
			for( n=2;n<tl[i].length+2;n++)
			{
				sprintf(data1,"%02x",tempdata[n]);
				strcat(data2,data1);  
			}
			strcat(result,data2);
		}
		strcat(result,tail);
		total_len+=2;
		total_len+=tl[i].length;
	}
	return 0;		 
}

long iReadXHFile(char *EFid,int recNO,int datalength,CYC *cy,int size,char *result)//recNO,记录条数，size，数据项数目
{
	unsigned char resp[256];
	unsigned char cmd[260];
	sDisp="";
	int n=0;
//	strdata1=data;
	memset(resp,0,256);
	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
	cmd[5]=chartoint(EFid[0])*16+chartoint(EFid[1]);
	cmd[6]=chartoint(EFid[2])*16+chartoint(EFid[3]);	
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	if(ret<2 || resp[0]!=0x90)
	{
		return 1;
	}

	memcpy(cmd, "\x00\xB2\x00\x04\x00",5);
	cmd[2]=recNO;
	cmd[4]=datalength;
	int i = recNO;
//	for(int i=1;i<recNO+1;i++)
//	{
		cmd[2]=i;
		memset(resp,0,256);
		ret = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);
		if (ret<0 || (resp[ret-2]!=0x90))
		{
			return 1;
		}
		char head[10]={0};
		char tail[10]={0};
		char sno[3]={0};
		sprintf(sno,"%d",i);
		char temp[512]={0};
		strcpy(head,"<ROW");
		strcat(head,sno);
		strcat(head,">");
		strcpy(tail,"</ROW");
		strcat(tail,sno);
		strcat(tail,">");

		strcpy(result,head);

		unsigned char tempdata[256]={0};
		int total_len=0;
		for(int j=0;j<size;j++)
		{
			memset(tempdata,0,256);
			
			char sno[3]={0};
			sprintf(sno,"%02d",j+1);
			strcat(result,"<C");
			strcat(result,sno);
			strcat(result,">");
			memcpy(tempdata,resp+total_len,cy[j].length);

			if(cy[j].datastyle==AN_style)
			{
				strcat(result,(char*)tempdata);			
			}
			else if(cy[j].datastyle == CN_style)
			{
				char data1[3]={0};
				char data2[300]={0};
				for( n=0;n<cy[j].length;n++)
				{
					sprintf(data1,"%02x",tempdata[n]);
					strcat(data2,data1);  
				}
				strcat(result,data2);
			}
//			strcat(result,"</C01>");
			total_len+=cy[j].length;

			strcat(result,"</C");
			strcat(result,sno);
			strcat(result,">");
		}
		strcat(result,tail);
//	}	
	return 0;
}

long iWriteRecord(char *EFid,unsigned char * Tag,int recNO,unsigned char * datalength,unsigned char* style,char *data) //recNO 没有用到  Tag 记录文件每条记录的标签
{
	unsigned char resp[256];
	unsigned char cmd[260];
	unsigned char temp[256]={0};
	sDisp="";
	int n=0;
	string strdata1;
	strdata="";
	strdata1="";
	strdata1 = data;
	long StartLen = 0;
	long EndLen = 0;
	long StartLen1 = 0;
	long EndLen1 = 0;
	
	while(true)
	{
		StartLen = strdata1.find("<",EndLen1);
		if(StartLen<0)
			break;
		EndLen = strdata1.find(">",StartLen); // <C01>

		sDisp = strdata1.substr(StartLen+2,EndLen-StartLen-1);//C01->01

		int rec = atoi(sDisp.c_str());

		StartLen1 = strdata1.find("<",EndLen);// </C
		EndLen1 = strdata1.find(">",StartLen1); // </C01>

		sDisp = strdata1.substr(EndLen+1,StartLen1-EndLen-1);

		memset(resp,0,256);
		long ret;
		memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
		cmd[5]=chartoint(EFid[0])*16+chartoint(EFid[1]);
		cmd[6]=chartoint(EFid[2])*16+chartoint(EFid[3]);	
		ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
		if(ret<2 || resp[0]!=0x90)
		{
			return 1;
		}
		memset(temp,0,256);
		int len = sDisp.length();
		if(style[rec-1]==AN_style)
		{
			for(  n=0;n<(len);n++)
			{
				temp[n]=sDisp[n];		
			}		
		}
		else if(style[rec-1] == CN_style)
		{
			for( n=0;n<len/2;n++)
			{
				temp[n] = chartoint(sDisp[2*n])*16+chartoint(sDisp[2*n+1]);  
			}
		}
		else
		{
			return 1;
		}

		memcpy(cmd, "\x00\xDC\x00\x04\x00",5);
		cmd[2]=rec;
		cmd[4]=datalength[rec-1]+2;
		cmd[5]=Tag[rec-1];
		cmd[6]=datalength[rec-1];
		for(int i=0;i<datalength[rec-1];i++)
		{
			cmd[7+i]=temp[i];
		}

		memset(resp,0,256);
		ret = ICC_Reader_Application(Rhand,0x01,datalength[rec-1]+7,cmd,resp);
		if (ret<0 || (resp[ret-2]!=0x90))
		{
	//		return 1;
		}
	}
	return 0;		
}

long iWriteBTLV(char *EFid,int recNO,int datalength,TLV *tl,int size,char *data,unsigned char _flag) //size 数据项
{   //<C0257></C0257><C0258></C0258><C0259></C0259>
	int st ;
	int ret =0;
	char carddata[256]={0};
	strdata="";
	sDisp="";
	strdata1 = data;
	long StartLen = 0;
	long EndLen = 0;
	long StartLen1 = 0;
	long EndLen1 = 0;
	int n=0;
	int len =0;
	int j=0;

	for(int i=0;i<size;i++)
	{
		StartLen = strdata1.find("<",EndLen1);
		EndLen = strdata1.find(">",StartLen); // <C0257>

		sDisp = strdata1.substr(StartLen+1,EndLen-StartLen-1);//C0257

		if(sDisp.compare(3,2,tl[i].flag)!=0)  //没有时，填充00
		{
			carddata[n++]=chartoint(tl[i].flag[0])*16+chartoint(tl[i].flag[1]);
			carddata[n++]=tl[i].length;
			for(j=0;j<(tl[i].length);j++)
				carddata[n++]=0;
			continue;
		}
		else
		{
			carddata[n++]=chartoint(tl[i].flag[0])*16+chartoint(tl[i].flag[1]);
			carddata[n++]=tl[i].length;
		}

		StartLen1 = strdata1.find("<",EndLen);// </C
		EndLen1 = strdata1.find(">",StartLen1);// >
		sDisp = strdata1.substr(EndLen+1,StartLen1-EndLen-1);//取出数据

		if((tl[i].datastyle)==AN_style)
		{
			len = sDisp.length();
			for( int j=0;j<(len);j++)
			{
				carddata[n++]=sDisp[j];		
			}		
		}
		else if((tl[i].datastyle) == CN_style)
		{
			len = sDisp.length()/2;
			for( j=0;j<len;j++)
			{
				carddata[n++] = chartoint(sDisp[2*j])*16+chartoint(sDisp[2*j+1]);  
			}
		}
		for(j=0;j<(tl[i].length-len);j++)  //不够长度补00
			carddata[n++]=0;
	}

	unsigned char resp[256];
	unsigned char cmd[300]={0};
	memset(resp,0,256);
//	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
	cmd[5]=chartoint(EFid[0])*16+chartoint(EFid[1]);
	cmd[6]=chartoint(EFid[2])*16+chartoint(EFid[3]);	
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	if(ret<2 || resp[0]!=0x90)
	{
		return 1;
	}

	memset(cmd,0,300);
	memcpy(cmd,"\x00\xDC\x00\x04\x00",5);
	cmd[2]=recNO;
	cmd[4]=datalength+2;
	cmd[5]=_flag;
	cmd[6]=datalength;

	for(i=0;i<datalength;i++)
	{
		cmd[7+i]=carddata[i];
	}

	memset(resp,0,256);
	ret = ICC_Reader_Application(Rhand,0x01,datalength+5+2,cmd,resp);
	if (ret<0 || (resp[ret-2]!=0x90))
	{
		return 1;
	}

	return 0;
}

long iWriteXHFile(char *EFid,int recNO,int datalength,CYC *cy,int size,char *data) //recNO 没有使用
{	//<C01>10</C01><C02>2</C02><C03>12</C03><C04>123</C04>
	int st ;
	int ret =0;
	char carddata[256]={0};
	strdata="";
	string sDisp1="";
	strdata1 = data;
	long StartLen = 0;
	long EndLen = 0;
	long StartLen1 = 0;
	long EndLen1 = 0;
	int n=0;
	int len =0;
	int j=0;

	for(int i=0;i<size;i++)
	{
		StartLen = strdata1.find("<",EndLen1);
		EndLen = strdata1.find(">",StartLen); // 

		sDisp1 = strdata1.substr(StartLen+2,EndLen-StartLen-1);//01
		int rec = atoi(sDisp1.c_str());
		
		if(rec!=(i+1))  //没有时，填充00
		{
			for(j=0;j<(cy[i].length);j++)
				carddata[n++]=0;
			continue;
		}
		
		StartLen1 = strdata1.find("<",EndLen);// </C
		EndLen1 = strdata1.find(">",StartLen1);// >
		sDisp1 = strdata1.substr(EndLen+1,StartLen1-EndLen-1);//取出数据

		if((cy[i].datastyle)==AN_style)
		{
			len = sDisp1.length();
			for( int j=0;j<(len);j++)
			{
				carddata[n++]=sDisp1[j];		
			}		
		}
		else if((cy[i].datastyle) == CN_style)
		{
			len = sDisp1.length()/2;
			for( j=0;j<len;j++)
			{
				carddata[n++] = chartoint(sDisp1[2*j])*16+chartoint(sDisp1[2*j+1]);  
			}
		}
		for(j=0;j<(cy[i].length-len);j++)  //不够长度补00
			carddata[n++]=0;
	}

	unsigned char resp[256];
	unsigned char cmd[300]={0};
	memset(resp,0,256);
//	long ret;
	memcpy(cmd, "\x00\xA4\x00\x00\x02",5);
	cmd[5]=chartoint(EFid[0])*16+chartoint(EFid[1]);
	cmd[6]=chartoint(EFid[2])*16+chartoint(EFid[3]);	
	ret = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);//X选择MF文件
	if(ret<2 || resp[0]!=0x90)
	{
		return 1;
	}

	memset(cmd,0,300);
	memcpy(cmd,"\x00\xDC\x01\x04\x00",5);
	cmd[4]=datalength;

	for(i=0;i<datalength;i++)
	{
		cmd[5+i]=carddata[i];
	}

	memset(resp,0,256);
	ret = ICC_Reader_Application(Rhand,0x01,datalength+5,cmd,resp);
	if (ret<0 || (resp[ret-2]!=0x90))
	{
		return 1;
	}
	return 0;
}

long PerPINChange(char*data,char*err)
{
		int st ;
	int ret =0;
	char result[256]={0};
	strdata="";
	sDisp="";
	strdata1 = data;
	
	char oldPassword[10]={0};
	char newPassword[10]={0};
//	char newPassword2[10]={0};

	long StartLen = strdata1.find("<",0); // <OLD>
	long EndLen = strdata1.find(">",StartLen); 

	long StartLen1 = strdata1.find("<",EndLen); //</OLD>
	long EndLen1 = strdata1.find(">",StartLen1); 

	long StartLen2 = strdata1.find("<",EndLen1); //<NEW>
	long EndLen2 = strdata1.find(">",StartLen2);
	
	long StartLen3 = strdata1.find("<",EndLen2); //</NEW>
	long EndLen3 = strdata1.find(">",StartLen3); 

	sDisp = strdata1.substr(EndLen+1,StartLen1-EndLen-1); //获取旧密码
	strcpy(oldPassword,sDisp.c_str());
	sDisp = strdata1.substr(EndLen2+1,StartLen3-EndLen2-1); //获取新密码
	strcpy(newPassword,sDisp.c_str());

	unsigned char resp[300]={0};
	unsigned char cmd[200]={0};

	int re = ICC_Reader_pre_PowerOn(Rhand,0x01,resp);
	for(int n=re-8;n<re;n++)
	{	
		_ATR[n-9] =  resp[n] ;
	}
	re = ICC_Reader_pre_PowerOn(Rhand,0x11,resp);
	if(re<0)
	{
		strcpy(err,"请放置SAM卡于SAM1卡槽");
		strcpy(data,"<DATA>99</DATA>");
		return 104;
	}
	memset(cmd,0,50);
	memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF",20);
	//00A404000F7378312E73682EC9E7BBE1B1A3D5CF
	re = ICC_Reader_Application(Rhand,0x01,20,cmd,resp);//X选择MF文件
	if(resp[0]!=0x61)
	{
		strcpy(err,"卡类型不对");
		strcpy(data,"<DATA>99</DATA>");
		return 105;
	}
	
	memset(cmd,0,50);
	memcpy(cmd,"\x80\x5E\x01\x00\x07",5);

	for(int i=0;i<3;i++)
	{
		cmd[5+i]=chartoint(oldPassword[2*i])*16+chartoint(oldPassword[2*i+1]);
		cmd[9+i]=chartoint(newPassword[2*i])*16+chartoint(newPassword[2*i+1]);
	}
	cmd[8]=0xFF;
	memset(resp,0,30);
	re = ICC_Reader_Application(Rhand,0x01,12,cmd,resp);//X选择MF文件
	if(resp[0]!=0x90)
	{
		//strcpy(pErrMsg,"卡类型不对");
		switch(resp[1])
		{
		case 0xC6:strcpy(err,"还剩6次认证机会!");return 6;
		case 0xC5:strcpy(err,"还剩5次认证机会!");return 5;
		case 0xC4:strcpy(err,"还剩4次认证机会!");return 4;
		case 0xC3:strcpy(err,"还剩3次认证机会!");return 3;
		case 0xC2:strcpy(err,"还剩2次认证机会!");return 2;
		case 0xC1:strcpy(err,"还剩1次认证机会!");return 1;
		case 0xC0:strcpy(err,"还剩0次认证机会!");return -1;
		}
		return 105;
	}
	strcpy(data,"<DATA>00</DATA>");
	return 0;
}
long ResetPassWord(char*data,char*err)
{
	unsigned char resp[100]={0};
	unsigned char cmd[260]={0};
	unsigned char temp[100]={0};
	unsigned char newPassword[10]={0};
	strdata="";
	sDisp="";
	long re;
	memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF",20);
	//00A404000F7378312E73682EC9E7BBE1B1A3D5CF
	re = ICC_Reader_Application(Rhand,0x01,20,cmd,resp);//X选择MF文件 
	
	strdata = data;
	long EndLen = strdata.find("<",2);
	long StartLen = strdata.find(">",0); 
	sDisp = strdata.substr(StartLen+1,EndLen-StartLen-1);

	int len = sDisp.length()/2;
	strcpy((char*)temp,sDisp.c_str());
	for(int i=0;i<len;i++)
	{
		newPassword[i]=(temp[2*i]-0x30)*16+temp[2*i+1]-0x30;
	}

	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
	re = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd, "\x00\xB2\x01\x04\x12",5);
	re = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);

	if(re<0 || resp[re-2]!=0x90)
	{
		strcpy(err,"卡片为空卡");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	char sdisp[3]={0};
	char saccm[40]={0};
	for(int n=0;n<re;n++)
	{
		sprintf(sdisp,"%02x",resp[n]);
		strcat(saccm,sdisp);
	}
	//char str[33]={0}; 
	memcpy(_CityCode,saccm+4,32);
	  
	unsigned char wordkey[4]={0x48,0x10,0x06};
	if(ExterAuthen(wordkey,2))
	{
		strcpy(err,"PUK认证失败!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}

	GetRandom();
	memset(cmd,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDF\x01",7);
	int ret = ICC_Reader_Application(Rhand,0x11,7,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90 && resp[ret-2]!=0x61))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}

	memcpy(cmd, "\xBF\xDE\x48\x09\x18",5); //STK 
	cmd[5]=_ATR[0];
	cmd[6]=_ATR[1];
	cmd[7]=_ATR[2];
	cmd[8]=_ATR[3];
	cmd[9]=_ATR[4];
	cmd[10]=_ATR[5];
	cmd[11]=_ATR[6];
	cmd[12]=_ATR[7];

	cmd[13]=_CityCode[0];
	cmd[14]=_CityCode[1];
	cmd[15]=_CityCode[2];
	cmd[16]=_CityCode[3];
	cmd[17]=_CityCode[4];
	cmd[18]=_CityCode[5];
	cmd[19]=0x73;
	cmd[20]=0x78;
	cmd[21]=_Random[0];
	cmd[22]=_Random[1];
	cmd[23]=_Random[2];
	cmd[24]=_Random[3];
	cmd[25]=_Random[4];
	cmd[26]=_Random[5];
	cmd[27]=_Random[6];
	cmd[28]=_Random[7];
	ret = ICC_Reader_Application(Rhand,0x11,29,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}

	memset(cmd,0,50);
	memset(resp,0,30);
	memcpy(cmd, "\x80\xFA\x00\x00\x08",5);//对鉴别因子加密
	cmd[5]=3;
	for(i=0;i<3;i++)
	{
		cmd[6+i]=newPassword[i];
	}
	cmd[9]=0x80;
	for(i = 0;i<3;i++)
		cmd[10+i]=0x00;

	ret = ICC_Reader_Application(Rhand,0x11,13,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x61))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	memset(cmd,0,50);
	memset(resp,0,30);
	memcpy(cmd, "\x00\xC0\x00\x00\x08",5);
	ret = ICC_Reader_Application(Rhand,0x11,5,cmd,resp);//得到密文
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	unsigned char EncData[20]={0};
	memcpy(EncData,resp,8);
	
	memset(cmd,0,50);
	memset(resp,0,30);
	memcpy(cmd, "\xBF\xDE\x48\x09\x18",5); //一级
	cmd[5]=_ATR[0];
	cmd[6]=_ATR[1];
	cmd[7]=_ATR[2];
	cmd[8]=_ATR[3];
	cmd[9]=_ATR[4];
	cmd[10]=_ATR[5];
	cmd[11]=_ATR[6];
	cmd[12]=_ATR[7];

	cmd[13]=_CityCode[0];
	cmd[14]=_CityCode[1];
	cmd[15]=_CityCode[2];
	cmd[16]=_CityCode[3];
	cmd[17]=_CityCode[4];
	cmd[18]=_CityCode[5];
	cmd[19]=0x73;
	cmd[20]=0x78;
	cmd[21]=_Random[0];
	cmd[22]=_Random[1];
	cmd[23]=_Random[2];
	cmd[24]=_Random[3];
	cmd[25]=_Random[4];
	cmd[26]=_Random[5];
	cmd[27]=_Random[6];
	cmd[28]=_Random[7];
	ret = ICC_Reader_Application(Rhand,0x11,29,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}

	memset(cmd,0,50);
	memset(resp,0,30);
	memcpy(cmd, "\x80\xFA\x05\x00\x18",5);//计算MAC
	memcpy(cmd+5,"\x00\x00\x00\x00\x00\x00\x00\x00",8);
	memcpy(cmd+13,"\x84\x24\x00\x01\x0C",5);
	memcpy(cmd+18,EncData,8);
	memcpy(cmd+26,"\x80\x00\x00",3);
	ret = ICC_Reader_Application(Rhand,0x11,29,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x61))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	memset(cmd,0,50);
	memset(resp,0,30);
	memcpy(cmd, "\x00\xc0\x00\x00\x08",5);
	ret = ICC_Reader_Application(Rhand,0x11,5,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	unsigned char MacData[10]={0};
	memcpy(MacData,resp,4);//得到MAC

	memset(cmd,0,50);
	memcpy(cmd,"\x84\x24\x00\x01\x0C",5);
	memcpy(cmd+5,EncData,8);
	memcpy(cmd+13,MacData,4);

	ret = ICC_Reader_Application(Rhand,0x01,17,cmd,resp);
	if(resp[0]!=0x90 || ret<2)
	{
		strcpy(err,"重置PIN码出错");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	strcpy(data,"<DATA>00</DATA>");
	return 0;
}

long PerPINUnLock(char*data,char*err)
{

	unsigned char resp[300]={0};
	unsigned char cmd[200]={0};

	int re = ICC_Reader_pre_PowerOn(Rhand,0x01,resp);
	for(int n=re-8;n<re;n++)
	{	
		_ATR[n-9] =  resp[n] ;
	}
	re = ICC_Reader_pre_PowerOn(Rhand,0x11,resp);
	if(re<0)
	{
		strcpy(err,"请放置SAM卡于SAM1卡槽");
		strcpy(data,"<DATA>99</DATA>");
		return 104;
	}
	memset(cmd,0,50);
	memset(resp,0,20);
	memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF",20);
	//00A404000F7378312E73682EC9E7BBE1B1A3D5CF
	re = ICC_Reader_Application(Rhand,0x01,20,cmd,resp);//X选择MF文件
	if(resp[0]!=0x61)
	{
		strcpy(err,"卡类型不对");
		strcpy(data,"<DATA>99</DATA>");
		return 105;
	}
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xEF\x05",7);
	re = ICC_Reader_Application(Rhand,0x01,7,cmd,resp);
	memcpy(cmd, "\x00\xB2\x01\x04\x12",5);
	re = ICC_Reader_Application(Rhand,0x01,5,cmd,resp);

	if(re<0 || resp[re-2]!=0x90)
	{
		strcpy(err,"卡片为空卡");
		strcpy(data,"<DATA>99</DATA>");
		return 1;
	}
	char sdisp[3]={0};
	char saccm[40]={0};
	for(n=0;n<re;n++)
	{
		sprintf(sdisp,"%02x",resp[n]);
		strcat(saccm,sdisp);
	}
	//char str[33]={0}; 
	memcpy(_CityCode,saccm+4,32);

	unsigned char wordkey[4]={0x48,0x10,0x06};
	if(ExterAuthen(wordkey,2))
	{
		strcpy(err,"PUK认证失败!");
		strcpy(data,"<DATA>99</DATA>");
		return 104;
	}

	GetRandom();
	memset(cmd,0,50);
	memcpy(cmd, "\x00\xA4\x00\x00\x02\xDF\x01",7);
	int ret = ICC_Reader_Application(Rhand,0x11,7,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90 && resp[ret-2]!=0x61))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 105;
	}
	memcpy(cmd, "\xBF\xDE\x48\x09\x18",5); //STK 

	cmd[5]=_ATR[0];
	cmd[6]=_ATR[1];
	cmd[7]=_ATR[2];
	cmd[8]=_ATR[3];
	cmd[9]=_ATR[4];
	cmd[10]=_ATR[5];
	cmd[11]=_ATR[6];
	cmd[12]=_ATR[7];

	cmd[13]=_CityCode[0];
	cmd[14]=_CityCode[1];
	cmd[15]=_CityCode[2];
	cmd[16]=_CityCode[3];
	cmd[17]=_CityCode[4];
	cmd[18]=_CityCode[5];
	cmd[19]=0x73;
	cmd[20]=0x78;
	cmd[21]=_Random[0];
	cmd[22]=_Random[1];
	cmd[23]=_Random[2];
	cmd[24]=_Random[3];
	cmd[25]=_Random[4];
	cmd[26]=_Random[5];
	cmd[27]=_Random[6];
	cmd[28]=_Random[7];
	ret = ICC_Reader_Application(Rhand,0x11,29,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 105;
	}

	memset(cmd,0,50);
	memset(resp,0,30);
	memcpy(cmd, "\x80\xFA\x05\x00\x10",5);//计算MAC
	memcpy(cmd+5,"\x00\x00\x00\x00\x00\x00\x00\x00",8);
	memcpy(cmd+13,"\x84\x24\x00\x00\x04",5);
	memcpy(cmd+18,"\x80\x00\x00",3);
	ret = ICC_Reader_Application(Rhand,0x11,21,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x61))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 105;
	}
	memset(cmd,0,50);
	memset(resp,0,30);
	memcpy(cmd, "\x00\xc0\x00\x00\x08",5);
	ret = ICC_Reader_Application(Rhand,0x11,5,cmd,resp);
	if(ret<2 || (resp[ret-2]!=0x90))
	{
		strcpy(err,"PSAM卡类型不对!");
		strcpy(data,"<DATA>99</DATA>");
		return 105;
	}
	unsigned char MacData[10]={0};
	memcpy(MacData,resp,4);//得到MAC

	memset(cmd,0,50);
	memcpy(cmd,"\x84\x24\x00\x00\x04",5);
	memcpy(cmd+5,MacData,4);

	ret = ICC_Reader_Application(Rhand,0x01,9,cmd,resp);
	if(resp[0]!=0x90 || ret<2)
	{
		strcpy(err,"解锁PIN码出错");
		strcpy(data,"<DATA>99</DATA>");
		return 105;
	}
	strcpy(data,"<DATA>00</DATA>");
	return 0;
}

long WINAPI Run(char* flag,char*data,char*err)
{
	int st;
	int tete=0;
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