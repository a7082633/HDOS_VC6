#ifndef HD_EEDS_H
#define HD_EEDS_H

#define EEDS_HD_API extern "C" __declspec(dllexport)

EEDS_HD_API int __stdcall ReadInfo(unsigned char *pKey, 
								   unsigned char *GECHH, 
								   unsigned char *XM, 
								   unsigned char *SFZH, 
								   unsigned char *CSRQ, 
								   unsigned char *XB, 
								   unsigned char *MZ,
								   char *pErr);


#endif