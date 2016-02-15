#ifndef HD_EEDS_H
#define HD_EEDS_H

#define EEDS_HD_API extern "C" __declspec(dllexport)

EEDS_HD_API int __stdcall iReadCard(unsigned char *OutXml,
								   char *pErr);


#endif