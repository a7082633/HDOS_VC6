// Utils.h: interface for the Utils class.
//
//////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>

#if !defined(AFX_UTILS_H__E9159915_0714_479A_8B94_E02DE9DDE9C5__INCLUDED_)
#define AFX_UTILS_H__E9159915_0714_479A_8B94_E02DE9DDE9C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Utils  
{
public:
	static int chartoint(char c);
	static int BinToHexstr(unsigned char *HexStr,unsigned char *Bin,int  BinLen);
	static int HexstrToBin(unsigned char *bin, unsigned char *asc,int len);
	static void UINTToBin(unsigned int ul , char* hex);
	static void intTo1ByteHex(int i , char * pHex);
	
	Utils();
	virtual ~Utils();

};

#endif // !defined(AFX_UTILS_H__E9159915_0714_479A_8B94_E02DE9DDE9C5__INCLUDED_)
