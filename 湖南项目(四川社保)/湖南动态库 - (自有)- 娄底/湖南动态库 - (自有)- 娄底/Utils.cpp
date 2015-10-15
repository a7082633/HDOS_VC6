// Utils.cpp: implementation of the Utils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Utils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Utils::Utils()
{

}

Utils::~Utils()
{

}

int Utils::chartoint(char c)
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

int Utils::HexstrToBin(unsigned char *bin, unsigned char *asc,int len)
{
/*	char ucChar;
	len=len/2+len%2;
	//npDest=(char *)bin;
	while(len--){
		ucChar=(*asc<='9'&&*asc>='0')?*asc-'0':*asc-'A'+10;
		ucChar<<=4;
		asc++;
		ucChar|=((*asc<='9'&&*asc>='0')?*asc-'0':*asc-'A'+10)&0x0F;
		asc++;
		*bin++=ucChar;
	}*/
	for(int i=0;i<len/2;i++)
	{
		bin[i]=chartoint(asc[2*i])*16+chartoint(asc[2*i+1]);
	}
	return len/2;

}

int Utils::BinToHexstr(unsigned char *HexStr,unsigned char *Bin,int  BinLen)
{
	char Temp1[3];
	char *result;
	int ret;
	int lens;
	lens=BinLen;
	if (lens<=0) return 0;
	result=(char *)malloc((lens*2+2)*sizeof( char));
	if (!result) return 0;
	memset(result,0,sizeof(result));
	for (int i=0;i<lens;i++)
	{
		memset(Temp1,0,sizeof(Temp1));
		ret=sprintf(Temp1,"%X",Bin[i]);
		if (strlen(Temp1)==1) {
			Temp1[1]=Temp1[0];
			Temp1[0]='0';
		}
		strcat(result,Temp1);

	}
	strcpy((char *)HexStr,result);
	
	free(result);
	return 2*i;
}

//将UINT型转成 16 进制
void Utils::UINTToBin(unsigned int ul , char* hex)
{
	unsigned char t[3];
	
	t[0] = (unsigned char) (ul / 256);
	t[1] = (unsigned char) (ul % 256);
	t[2] = 0;

	memcpy(hex , t , 2);
}

//将int型，转成一个字节的Hexstr 如 10 -》"0A",
//数据只改变指针后面2字节内容
void Utils::intTo1ByteHex(int i , char * pHex)
{
	char t[3];
	char tmp[8];
	UINTToBin(i , t);
	BinToHexstr((unsigned char*)tmp ,(unsigned char*)t + 1, 1 );
	memcpy(pHex  , tmp , 2);
}

