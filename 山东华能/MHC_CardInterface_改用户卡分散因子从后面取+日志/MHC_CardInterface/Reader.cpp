// Reader.cpp: implementation of the Reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Reader.h"
#include <time.h>
#include <stdlib.h>
#include "Utils.h"
//#include "Application.h"
#include "HD300_V1.h"
#pragma comment(lib,"HD300_V1")
//#define DEBUG_LOG( str ) log_append_to_file("test.txt", str,__FILE__,__LINE__ );
/************************************************************************/
/* 读卡器类型宏定义                                                     */
/************************************************************************/
/*#define HHD06 
//#define DC_D8
#ifdef HHD06
	#include "RdReader.h"
#else ifdef DC_D8
	#include "dcrf32.h"
#endif
*/
//Utils u;

//HANDLE Reader::rdHandle = 0;
long Reader::m_hReader=0;
int _SLOT = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Reader::Reader()
{

}

Reader::~Reader()
{

}

int Reader::Open()
{
	/*
#ifdef DC_D8
	
	HANDLE icdev;

	icdev = dc_init(100, 115200);
	if (icdev <= 0 )
		return RD_CONNECT_ERROR;
	else
		Reader::rdHandle = icdev;

	return RD_OK;
#else ifdef HHD06

	HANDLE icdev;	

	time_t seed = time(NULL); 
	
    srand((unsigned)seed); 
	
	icdev =(HANDLE) rand();
	int ret = OpenUsb((ULONG)icdev);
	if (ret)
		return RD_CONNECT_ERROR;
	else
		Reader::rdHandle = icdev;
	return RD_OK;
#endif	*/
	
	long hReader = ICC_Reader_Open("USB1");
	if (hReader <= 0 )
		return RD_CONNECT_ERROR;
	else
		Reader::m_hReader = hReader;
	return RD_OK;
}

int Reader::Close()
{
/*#ifdef DC_D8
	dc_exit(Reader::rdHandle);
	Reader::rdHandle = 0;
	return RD_OK;
#else ifdef HHD06
	CloseUsb(); 
	return RD_OK;
#endif*/
	ICC_Reader_Close(Reader::m_hReader);
	Reader::m_hReader = 0;
	return RD_OK;
}

//蜂鸣
int Reader::Beep(unsigned short _Ms)
{/*
#ifdef DC_D8
	int ret = dc_beep(Reader::rdHandle, _Ms);
	if (ret)
		return RD_ERROR;
	return RD_OK;
#else ifdef HHD06
	int ret = Beeps(_Ms);
	if (ret)
		return RD_ERROR;
	return RD_OK;
#endif*/
	int ret = ICC_PosBeep(Reader::m_hReader,_Ms);
	if(ret)
		return RD_ERROR;
	return RD_OK;

}

//非接CPU复位
int Reader::RF_Reset( char *_ATS_Responce)
{/*
	int retval;
	unsigned char lenr;
	unsigned char resp[256];

#ifdef DC_D8
	unsigned long lngr;

	retval = dc_reset(Reader::rdHandle, 7);
	if (retval) 
		return RD_ERROR;   
	//set Type A
	dc_config_card (Reader::rdHandle , 65);

	retval = dc_card(Reader::rdHandle, 1, &lngr);
	if (retval)
		return RD_NO_ICC;
		
	retval = dc_pro_resethex(Reader::rdHandle, &lenr, (char*)_ATS_Responce);
	if (retval)
		return RD_ERROR;

	return RD_OK;

#else ifdef HHD06
	retval = RF_SC_RATS(&lenr , (unsigned char*)resp );
	if (retval) 
		return RD_NO_ICC;   

	u.BinToHexstr((unsigned char*)_ATS_Responce , resp , (int)lenr);

	return RD_OK;
#endif*/
	int re=0;
	unsigned char Response[128]={0};
	unsigned char uid[5]={0};
	re = PICC_Reader_SetTypeA(Reader::m_hReader);
	if(re!=0)
	{
		return RD_ERROR;
	}
	re=PICC_Reader_Request(Reader::m_hReader);
	if(re!=0)
	{
		return RD_NO_ICC;
	}
	re = PICC_Reader_anticoll(Reader::m_hReader,uid);
	if(re!=0)
	{
		return RD_NO_ICC;
	}
	re = PICC_Reader_Select(Reader::m_hReader,0x41);
	if(re!=0)
	{
		return RD_NO_ICC ;
	}
	re = PICC_Reader_PowerOnTypeA(Reader::m_hReader,Response);
	if(re<0)
	{
		return RD_NO_ICC;
	}
	u.BinToHexstr((unsigned char*)_ATS_Responce , Response , re);
	return RD_OK;
}

//非接CPU发命令
int Reader::RF_Send( char * _APDU_CMD, char *_APDU_Responce ,  char * _SW)
{
	
	int retval;
	unsigned char lenr;
	unsigned char len = (unsigned char) (strlen((char *)_APDU_CMD) / 2);
	unsigned char send[260];
	unsigned char resp[260];
/*
#ifdef DC_D8
	retval = dc_pro_commandlink_hex(Reader::rdHandle, len, 
										(unsigned char*)_APDU_CMD, &lenr, 
										resp, 7, 56);
		
	if (retval)
		return RD_IC_NO_RESP;
	memcpy(_APDU_Responce , resp , lenr - 4);
	_APDU_Responce[lenr-4] = 0;
	memcpy(_SW , resp + lenr - 4 , 4);
	_SW[4] = 0;

	return RD_OK;
#else ifdef HHD06
	u.HexstrToBin(send , (unsigned char*)_APDU_CMD , strlen((char *)_APDU_CMD));
	
	retval = RF_SC_SendData(len , send , &lenr ,resp);
	if (retval)
		return RD_IC_NO_RESP;

	u.BinToHexstr((unsigned char*)_APDU_Responce , resp , lenr - 2) ;
	u.BinToHexstr((unsigned char*)_SW , resp + lenr - 2 , 2);

	return RD_OK;
#endif*/
//	log_append_to_file("Reader.log",_APDU_CMD,"发送-健康卡",3);
	u.HexstrToBin(send , (unsigned char*)_APDU_CMD , strlen((char *)_APDU_CMD));
	
	retval = PICC_Reader_Application(Reader::m_hReader,len , send  ,resp);
	if (retval<0)
		return RD_IC_NO_RESP;

	u.BinToHexstr((unsigned char*)_APDU_Responce , resp , retval - 2) ;
	unsigned temp[7000]={0};
	u.BinToHexstr((unsigned char*)temp , resp , retval) ;
//	log_append_to_file("Reader.log",(char *)temp,"接收-健康卡",3);
	u.BinToHexstr((unsigned char*)_SW , resp + retval - 2 , 2);

	return RD_OK;

}

//PSAM卡槽复位
int Reader::PSAM_Reset(int slot , char *_ATS_Responce)
{
	int retval;
	unsigned char lenr;
	unsigned char resp[256];
	int iLayout;
	/*
#ifdef DC_D8
	int st;
	//设置操作卡槽 sim1
	st = dc_setcpu(Reader::rdHandle , 0x0d);// SAMID[3]={0x0d,0x0e,0x0f};
	if (st != 0)
		return RD_ERROR;
	
	st = dc_cpureset_hex(Reader::rdHandle , &lenr , (char*)_ATS_Responce);
	if (st)
		return RD_ERROR;

	return RD_OK;
#else ifdef HHD06
	if (slot == SLOT_PSAM)
		iLayout = 1;
	else
		iLayout = 3;
	//设置卡槽1
	retval = PSAM_Select(iLayout);
	if (retval) 
		return RD_ERROR;   
	retval = PSAM_RATS(iLayout , &lenr , (unsigned char*)resp );
	if (retval) 
		return RD_NO_ICC;   

	u.BinToHexstr((unsigned char*)_ATS_Responce , resp , (int)lenr);

	return RD_OK;
#endif*/

	if (slot == SLOT_PSAM)
	{
		iLayout = 0x11;
		_SLOT = 0x11;
	}
	else
	{
		iLayout = 0x01;
		_SLOT = 0x01;
	}

	retval = ICC_Reader_PowerOn(Reader::m_hReader,iLayout , (unsigned char*)resp );
	if (retval<0) 
		return RD_NO_ICC;   

	u.BinToHexstr((unsigned char*)_ATS_Responce , resp , (int)retval);

	return RD_OK;

}


//PSAM卡槽发命令
int Reader::PSAM_Send( char * _APDU_CMD, char *_APDU_Responce ,  char * _SW)
{
	int retval;
	unsigned char len = (unsigned char) (strlen((char *)_APDU_CMD) / 2);
	unsigned char send[260];
	unsigned char resp[260];
/*
#ifdef DC_D8
	retval = dc_cpuapdu_hex(Reader::rdHandle, len, (char *)_APDU_CMD, &lenr, (char*)resp);
		
	if (retval)
		return RD_IC_NO_RESP;
	memcpy(_APDU_Responce , resp , lenr - 4);
	_APDU_Responce[lenr-4] = 0;
	memcpy(_SW , resp + lenr - 4 , 4);
	_SW[4] = 0;


	return RD_OK;
#else ifdef HHD06
	u.HexstrToBin(send , (unsigned char*)_APDU_CMD , strlen((char *)_APDU_CMD));
	
	retval = PSAM_SendData(len , send , &lenr ,resp);
	if (retval)
		return RD_IC_NO_RESP;

	u.BinToHexstr((unsigned char*)_APDU_Responce , resp , lenr - 2) ;
	u.BinToHexstr((unsigned char*)_SW , resp + lenr - 2 , 2);

	return RD_OK;
#endif
	*/
//	log_append_to_file("Reader.log",_APDU_CMD,"发送sam",1);
	u.HexstrToBin(send , (unsigned char*)_APDU_CMD , strlen((char *)_APDU_CMD));
	
	retval = ICC_Reader_Application(Reader::m_hReader,_SLOT,len , send  ,resp);
	if (retval<2)
		return RD_IC_NO_RESP;

	u.BinToHexstr((unsigned char*)_APDU_Responce , resp , retval - 2) ;
	unsigned temp[7000]={0};
	u.BinToHexstr((unsigned char*)temp , resp , retval) ;
//	log_append_to_file("Reader.log",(char *)temp,"接收sam",2);
	u.BinToHexstr((unsigned char*)_SW , resp + retval - 2 , 2);

	return RD_OK;

}
