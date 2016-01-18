#ifndef HD_HD_ZTHInterface_H
#define HD_HD_ZTHInterface_H

//#define OPEN_FAILURE	       1       //打开设备失败
//#define POWERON_FAILURE	       2       //卡片上电失败
//#define EXC_APDU_FAILURE	   3       //执行指令失败
//#define ERR_CARDTYPE	       4       //卡型错误
//#define GET_DEVN_FAILURE	   5       //获取设备序列号失败
//#define SAM_ON_FAILURE	       6       //SAM卡上电失败

#ifdef __cplusplus
extern "C" {
#endif

int __stdcall HD_OpenDevice(char *PIN,char *pErr);
int __stdcall HD_CloseDevice();
int __stdcall HD_ReadCardInfo(char *Key,char *CardType,char *CardNo,char *Name,char *Sex,char *Born,char *IDNo,char *MakeCDT,char *EffectD,char *Nation,char *pErr);

#ifdef __cplusplus
}
#endif
#endif