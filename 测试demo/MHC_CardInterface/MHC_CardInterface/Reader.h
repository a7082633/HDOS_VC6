// Reader.h: interface for the Reader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READER_H__23BC8A8D_6B6C_429B_A134_6DB05D369A3A__INCLUDED_)
#define AFX_READER_H__23BC8A8D_6B6C_429B_A134_6DB05D369A3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define RD_OK			0
#define RD_CONNECT_ERROR	1
#define RD_NO_ICC			2			//无卡
#define RD_IC_NO_RESP		4		//卡片无应答
#define RD_ERROR			5			//接口设备故障


class Reader  
{

public:
	static int PSAM_Send( char * _ADPU_CMD, char *_ADPU_Responce , 
						 char * _SW);

	static int PSAM_Reset(int slot , char *_ATS_Responce);

	static int RF_Send( char * _ADPU_CMD, char *_ADPU_Responce , 
						 char * _SW);

	static int RF_Reset( char *_ATS_Responce);

	static int Beep(unsigned short _Ms);
	static int Close();
	static int Open();

	Reader();
	virtual ~Reader();

//	static HANDLE rdHandle;
	static long m_hReader;
private:
	
};

#endif // !defined(AFX_READER_H__23BC8A8D_6B6C_429B_A134_6DB05D369A3A__INCLUDED_)
