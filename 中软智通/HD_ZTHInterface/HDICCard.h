#ifndef HDICCARD_H
#define HDICCARD_H
#include <windows.h>


#define JR_OK 0     //执行成功

#define IC_UnConnect -1001 //设备通讯超时
#define IC_CardNoExist -1002 //无卡
#define IC_CardLock -2001	//卡片已锁定，请解锁
#define IC_CardInit -2002	//卡片初始化失败
#define IC_CardGetCDOL1 -2003	//卡片获取CDOL1失败
#define IC_CardARQC  -2004	//卡片获取ARQC失败
#define IC_CardGetCDOL2 -2005	//读取卡片CDOL2失败
#define IC_CardTC -2006	  //卡片生成TC失败
#define IC_CardAAC -2007	//卡片生成AAC失败

#define IC_CardIsAuthen -2010	//卡片发卡行认证失败
#define IC_CardScript -2008	  //卡片执行脚本失败
#define IC_CardList -2009	//获取交易明细失败





#ifdef __cplusplus
extern "C" {
#endif

int __stdcall HD_ICC_GetInfo(char *TermType, 
					char *PortType, 
					char *PortNO, 
					char *TransPortNO, 
					char *ICFlag,
					char *Taglist,
					char *AIDList,
					char *DataBuf
);

int __stdcall HD_ICC_GenARQC(char *TermType, 
					char *PortType, 
					char *PortNO,  
					char *TransPortNO, 
					char *ICFlag,
					char *TxData, 
					char *AIDList, 
					char *ARQCLen,
					char *ascARQC,
					char *hexARQC
);

int __stdcall HD_ICC_ARPC_ExeICScript(
					char *TermType, 
					char *PortType, 
					char *PortNO,  
					char *TransPortNO, 
					char *ICFlag,
					char *TxData,
					char *ARPCLen,
					char *hexARPC,
					char *Status,
					char *TC, 
					char *ScriptResult
);

int __stdcall HD_ICC_GetTxDetail(
						char *TermType, 
						char *PortType, 
						char *PortNO,  
						char *TransPortNO, 
						char *ICFlag,
						char *AIDList, 
						char *TxDetail
);






#ifdef __cplusplus
}
#endif

#endif