#ifndef HD_WHInterface_H
#define HD_WHInterface_H

//#define OPEN_FAILURE	       1       //打开设备失败
//#define POWERON_FAILURE	       2       //卡片上电失败
//#define EXC_APDU_FAILURE	   3       //执行指令失败
//#define ERR_CARDTYPE	       4       //卡型错误
//#define GET_DEVN_FAILURE	   5       //获取设备序列号失败
//#define SAM_ON_FAILURE	       6       //SAM卡上电失败

#ifdef __cplusplus
extern "C" {
#endif

int __stdcall IC_GetMagneData(char *dataOut,int TimeOut);
int __stdcall IC_GetData(char *dataOut,char *pErr,int TimeOut);

#ifdef __cplusplus
}
#endif
#endif
