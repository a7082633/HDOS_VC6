#ifndef ICCInter_H
#define ICCInter_H

#define OPEN_FAILURE	       1       //打开设备失败
#define POWERON_FAILURE	       2       //卡片上电失败
#define EXC_APDU_FAILURE	   3       //执行指令失败
#define ERR_CARDTYPE	       4       //卡型错误
#define GET_DEVN_FAILURE	   5       //获取设备序列号失败
#define SAM_ON_FAILURE	       6       //SAM卡上电失败

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
	unsigned long	readertype;			//保留
	unsigned long	cardtype;			//保留
	unsigned long	port;				//保留
	unsigned long	baud;				//保留
	HANDLE			commdevice;			//保留
	unsigned long	timeout;			//保留
	unsigned char	*PIN;				//保留
	unsigned char	*Key;				//保留
	unsigned char	*HostAddr;			//保留
	unsigned long	HostTimeOut;		//保留
	unsigned char	*CardSN;			//保留
	unsigned long	OpType;				//保留	
    unsigned long	TransType;			//保留
	unsigned char	*ATR;				//保留
	unsigned char	*CardNumber;		//保留
	unsigned char	reserved[20];		//保留
} ICC_ENV;
int __stdcall IC_GetData(ICC_ENV *iccenv,int datatype,char *data);
int __stdcall IC_OpenSession(ICC_ENV *iccenv);
int __stdcall IC_CloseSession(ICC_ENV *iccenv);
int __stdcall IC_SaveData(ICC_ENV *iccenv, int datatype, unsigned char *data);
int __stdcall IC_PINVerify(ICC_ENV *iccenv);
int __stdcall IC_Beep(unsigned char time);//蜂鸣
//long WINAPI ICC_PosBeep(long ReaderHandle, unsigned char time);//蜂鸣
#ifdef __cplusplus
}
#endif
#endif
