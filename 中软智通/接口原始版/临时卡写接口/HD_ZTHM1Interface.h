#ifndef HD_ZTHM1Interface_H
#define HD_ZTHM1Interface_H


#ifdef __cplusplus
extern "C" {
#endif

int __stdcall HD_WriteM1(char *Key,char *Name,char *Sex,char *IDNo,char *Born,char *CardNo,char *MakeCDT,char *pErr);
int __stdcall HD_ReadM1(char *Key,char *Addr,char *DataOut,char *pErr);

#ifdef __cplusplus
}
#endif
#endif