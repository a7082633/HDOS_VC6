#ifndef HD_XJIDCARDInter_H
#define HD_XJIDCARDInter_H


#ifdef __cplusplus
extern "C" {
#endif


int __stdcall Reader_ReadIDMsg(const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire,char * pErrMsg);


#ifdef __cplusplus
}
#endif
#endif
