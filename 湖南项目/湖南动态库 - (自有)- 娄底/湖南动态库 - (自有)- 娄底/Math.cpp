#include "stdafx.h"
#include <memory.h>
#include <string.h>
#include <time.h>

#include <stdio.h>
#include <ctype.h>
#define Bool BOOL
#define ICC_ECB 0
#define ICC_CBC 1
#define ICC_SUC		0x9000
#define EXCUTE_SUC 0x9000
#define GCECB	0
#define GCCBC	1

#define CER_HEXSTR  -21
// return content
#define RET_SUCCESS		0
#define RET_KEYVERSION	1//密钥版本错误
#define RET_MAC			2//校验MAC错误
#define RET_DATA		3//校验文件数据错误
#define RET_DATALEN		4//数据长度错误
#define RET_TAC			5//校验TAC错误
#define RET_ILLEGEL		6//非法卡片
#define RET_COMERROR	-1
#define RET_LINEERROR	-2
#define RET_OPENERROR	-3
#define RET_CARDERROR	-4
#define RET_PARAERROR	-5
#define RET_APPBLOCK	6

#define RET_ATRFAIL		-10
#define RET_TESTFAIL	-11
#define RET_FORMATFAIL	-12
#define RET_VERIFYFAIL	-13
#define RET_TIMEOUTERROR -14
#define RET_GETINFOERROR  -15

#define RET_MAKERERROR	-20
#define RET_ISSUERERROR	-21
#define RET_USERERROR	-22
#define RET_CUSTERROR	-23
#define RET_KEYERROR	-24
#define RET_VERIFYERROR	-25


#define RET_3DES_ENCIPHERRROR	-26
#define RET_3DES_DECIPHERERROR	-27
#define RET_3DES_MACERROR		-28
#define RET_DES_ENCIPHERRROR	-29
#define RET_DES_DECIPHERERROR	-30
#define RET_DES_MACERROR		-32

#define RET_APP_SELECTERROR		-33
#define RET_ERROR		-99
#define CER_RESULT 0
#define CER_ILLEGALDEVICE -16
#define CER_KEYLEN -17
#define CER_DATALEN -18
#define CER_CBC -19
#define CER_MODE -20

Bool bLicenseOK = TRUE;
void MATH_License();
Bool checkhexstr( char *str );
int getbyte( char *svHex, short num );
unsigned short DecHstr( unsigned long ivDec, short ivNum, char *srHex );
void desdeciph(unsigned char *data, unsigned char *key);
void desenciph(unsigned char *data, unsigned char *key);

unsigned short HD_3DES_MACByte( unsigned char *svHex, short svHexLen, unsigned char *svKey, short svKeyLen, unsigned char *srHex,short *srHexLen )
{
	int i, ptr;
	unsigned char seed2[8], des_data[8], key_buf[8];

	MATH_License();
	if ( !bLicenseOK )
	 	return CER_ILLEGALDEVICE ;


	if( svKeyLen != 16 )
		return CER_KEYLEN;		// len of KEY must be 16 bytes

	if( svHexLen % 8 != 0 )
		return CER_DATALEN;		// len of DATA must be the time of 8
	
	if( svHexLen<16 )	// len of DATA must be larger than 16
		return CER_CBC;

	// Init seed
	for(i=0; i<8; i++)
		seed2[i] = svHex[i];
	ptr = 8;
	svHexLen = svHexLen - 8;
	

	while( svHexLen/8 != 0 )
	{
		//get plain data
		// memcpy(des_data, idata+ptr, 8);
		for(i=ptr; i<ptr+8; i++)
			des_data[i-ptr] = svHex[i];
           			
		for(i=0;i<8;i++)
			des_data[i] = des_data[i] ^ seed2[i];
		
           		
        //call the desenciph to encipher
		// memcpy(key_buf, L_key, 8);
		for(i=0; i<8; i++)		// DES+
			key_buf[i] = svKey[i];
        desenciph(des_data, key_buf);
        
		memcpy(seed2, des_data, 8);
	
		svHexLen = svHexLen - 8;
        ptr = ptr + 8;
	}
	// Decipher
	// memcpy(key_buf, R_key, 8);
	for(i=8; i<16; i++)
		key_buf[i-8] = svKey[i];
	desdeciph(des_data, key_buf);

	// Encipher
	// memcpy(key_buf, L_key, 8);
	for(i=0; i<8; i++)
		key_buf[i] = svKey[i];
	desenciph(des_data, key_buf);

    //get result
	//memcpy(odata, des_data, 8);
	for(i=0; i<8; i++)
		srHex[i] = des_data[i];
	*srHexLen = i;
	return EXCUTE_SUC;
}
 
unsigned short HD_3DES_EncryptByte( unsigned char *svHex, short svHexLen, unsigned char *srHex, short *srHexLen )
{
	short svKeyLen=16;
	short ivMode=0;
	unsigned char svKey[16]={0xCF,0xC9,0xA3,0xBA,0xAB,0xB9,0xBB,0xBD,0x32,0x30,0x31,0x31,0x31,0x30,0x76,0x31};
	

	int i, ptr;
	unsigned char seed2[8], des_data[8], key_buf[8];
	MATH_License();
	if ( !bLicenseOK )
	 	return CER_ILLEGALDEVICE ;

	if( ivMode != ICC_ECB && ivMode != ICC_CBC) 
		return CER_MODE;    // mode only is 0 or 1

//	if( svKeyLen != 16 )
//		return CER_KEYLEN;		// len of KEY must be 16 bytes

	if( svHexLen % 8 != 0 )
		return CER_DATALEN;		// len of DATA must be the time of 8
	
	if( ivMode == ICC_CBC && svHexLen<16 )	// len of DATA must be larger than 8
		return CER_CBC;

	// Init seed
	if( ivMode == ICC_CBC )
	{
		for(i=0; i<8; i++)
			seed2[i] = svHex[i];
		ptr = 8;
		svHexLen = svHexLen - 8;
	}
	else
		ptr = 0;

	*srHexLen = svHexLen;
	while( svHexLen/8 != 0 )
	{
		//get plain data
		//memcpy(des_data, idata+ptr, 8);
		for(i=ptr; i<ptr+8; i++)
			des_data[i-ptr] = svHex[i];
           			
        if( ivMode == ICC_CBC )
		{
			for(i=0;i<8;i++)
				des_data[i] = des_data[i] ^ seed2[i];
		}
           		
        //call the desenciph to encipher
		for(i=0; i<8; i++)		// DES+
			key_buf[i] = svKey[i];
        desenciph(des_data, key_buf);

		for(i=8; i<16; i++)		// DES-
			key_buf[i-8] = svKey[i];
		desdeciph(des_data, key_buf);
		
		if (svKeyLen==16)	//112 bit
		{
			for(i=0; i<8; i++)		// DES+
				key_buf[i] = svKey[i];
		}
		else if (svKeyLen==24)	//168 bit
		{
			for(i=16; i<24; i++)		// DES+
				key_buf[i-16] = svKey[i];
		}
		else
		{
			return CER_KEYLEN;		// len of KEY must be 16 bytes or 24 byte
		}
		desenciph(des_data, key_buf);

		if( ivMode == ICC_CBC )
			memcpy(seed2, des_data, 8);

        //get result
		for(i=ptr; i<ptr+8; i++)
			if(ivMode == ICC_CBC) srHex[i-8] = des_data[i%8];			
			else srHex[i] = des_data[i%8];		
		svHexLen = svHexLen - 8;
        ptr = ptr + 8;
	}
	return EXCUTE_SUC;
}


unsigned short HD_3DES_DecryptByte( unsigned char *svHex, short svHexLen, unsigned char *srHex, short *srHexLen)
{
	short svKeyLen=16;
	short ivMode=0;
//	unsigned char svKey[16]={0xCF,0xC9,0xA3,0xBA,0xAB,0xB9,0xBB,0xBD,0x32,0x30,0x31,0x31,0x31,0x30,0x76,0x31};
	unsigned char svKey[16]={0x35,0x38,0x37,0x33,0x30,0x36,0x33,0x35,0x35,0x38,0x37,0x33,0x30,0x36,0x33,0x35};
	unsigned short i, ptr;
	unsigned char seed2[8], des_data[8], key_buf[8];
	MATH_License();
	if ( !bLicenseOK )
	 	return CER_ILLEGALDEVICE ;


	if( ivMode != ICC_ECB && ivMode != ICC_CBC) 
		return CER_MODE;    // mode only is 0 or 1
	

	//if( svKeyLen != 16 )
	//	return CER_KEYLEN;		// len of KEY must be 16 bytes


	if( svHexLen % 8 != 0 )
		return CER_DATALEN;		// len of DATA must be the time of 8
	
	if( ivMode == ICC_CBC && svHexLen<16 )	// len of DATA must be larger than 8
		return CER_CBC;

	// Init seed
	if( ivMode == ICC_CBC )
	{
		for(i=0; i<8; i++)
			seed2[i] = svHex[i];
		ptr = 8;
		svHexLen = svHexLen - 8;
	}
	else
		ptr = 0;
	
	*srHexLen = svHexLen;
	while( svHexLen/8 != 0 )
	{   
		//decipher
        //memcpy(des_data, idata+ptr, 8); 
		for(i=ptr; i<ptr+8; i++)
			des_data[i-ptr] = svHex[i];
           		
        //call the desdeciph to decipher
		if (svKeyLen==16)	//112 bit
		{
		for(i=0; i<8; i++)		// DES-
			key_buf[i] = svKey[i];
		}
		else if (svKeyLen==24)	//168 bit
		{
			for(i=16; i<24; i++)		// DES-
				key_buf[i-16] = svKey[i];
		}
		else
		{
			return CER_KEYLEN;		// len of KEY must be 16 bytes or 24 byte
		}
        desdeciph(des_data, key_buf);

		for(i=8; i<16; i++)		// DES+
			key_buf[i-8] = svKey[i];
		desenciph(des_data, key_buf);

		for(i=0; i<8; i++)		// DES-
			key_buf[i] = svKey[i];
		desdeciph(des_data, key_buf);

        if( ivMode == ICC_CBC )
		{
			for(i=0;i<8;i++)
				des_data[i] = des_data[i] ^ seed2[i];

			// memcpy(seed2, idata+ptr, 8);
			for(i=ptr; i<ptr+8; i++)
				seed2[i-ptr] = svHex[i];
		}
           		
        // memcpy(odata+ptr, des_data, 8);
		for(i=ptr; i<ptr+8; i++)
			if(ivMode == ICC_CBC) srHex[i-8] = des_data[i%8];			
			else srHex[i] = des_data[i%8];		
		svHexLen = svHexLen - 8;
        ptr = ptr + 8;
    }

	return EXCUTE_SUC;
}

static unsigned short HD_HstrCstr( char *svHex,unsigned char *srChar )
{
	int bc, i;

	srChar[0] = '\0';
	if( !checkhexstr( svHex ))
		return CER_HEXSTR;		// 锟角凤拷十锟斤拷锟斤拷锟狡达拷

	bc = strlen( svHex ) / 2;
	for( i=0; i<bc; i++)
		srChar[i] = getbyte( svHex, i+1);
	srChar[i] = '\0';

	return EXCUTE_SUC;
}
unsigned short HD_DecCstr( unsigned long ivDec, unsigned char *srHex,short *srHexLen )
{
	char buf[255];
	short retval;

	retval=DecHstr( ivDec, 0, buf);
	if(retval!=0)
		return CER_RESULT;

	*srHexLen = strlen(buf)/2;

	retval=HD_HstrCstr(buf,srHex);

	return retval;

}


//===================================================================================================
Bool checkhexstr( char *str )
{
	int i, len;

	len = strlen( str );
	if( len%2 != 0 )
		return FALSE;

	for( i=0; i<len; i++)
	{
		if( (str[i]<48 || str[i]>57)			// 0...9
			&& (str[i]<65 || str[i]>70)			// A...F
			&& (str[i]<97 || str[i]>102) )		// a...f
			return FALSE;
	}

	return TRUE;
}

Bool checkdecstr( char *str )
{
	int i, len;

	len = strlen( str );
	for( i=0; i<len; i++)
	{
		if( str[i]<48 || str[i]>57 )		// 0...9
			return FALSE;
	}
	return TRUE;
}

Bool checkbinstr( char *str )
{
	int i, len;

	len = strlen( str );
	for( i=0; i<len; i++)
	{
		if( str[i]!='0' && str[i]!='1' )		// 0 or 1
			return FALSE;
	}
	return TRUE;
}

int getbyte( char *svHex, short num )
{
	char stds[] = "0123456789ABCDEF";
	char c[2];
	int a, b;

	if( (unsigned int)num > strlen(svHex)/2)
		return 0;

	c[0] = toupper(svHex[2*num-2]);
	c[1] = '\0';
	a = strcspn( stds, c );
	c[0] = toupper(svHex[2*num-1]);
	c[1] = '\0';
	b = strcspn( stds, c );
	
	return (a*16+b);
}

void byte2str( char *svHex, unsigned char ivByte )
{
	char subs[5];

	sprintf(subs, "%02X", ivByte);
	strcat( svHex, subs );
	return;
}

void upperstr( char *svStr, char *srStr )
{
	int i, j, slen;
	char cc;

	slen = strlen(svStr);
	srStr[0] = '\0';
	j = 0;
	for(i=0; i<slen; i++)
	{
		cc = toupper( svStr[i] );
		if( cc != 32 )			// 32 is space
			srStr[j++] = cc;
	}
	srStr[j] = '\0';
	return;
}

////////////////////////////////////////////////////////////////
// Function INI_PERMUTATION is used to inital permutation with 
// the data which to be encipher or decipher
// Function Pammes Description  
// ini_permutation(s)
// Parameter Description:
//   s:      return deciphed data and deciphing data
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void ini_permutation (unsigned char *s)
{
    unsigned char p[8];
    unsigned char buf;
    unsigned char rule = 1;
    int i,j;
       
       //begin to inital permutation
       
       for (i=0;i<8;i++){
	       p[i] = 0;
           for(j=7;j>=0;j--){
	           buf = s[j];
	       	   s[j] = s[j] >> 1;
               buf = buf & rule;
	       	   p[i] = p[i] | buf;
	       	   
	       	   if(j==0) 
	       	      break;
               
               p[i] = p[i] << 1;
           }
      }

       s[0] = p[6];
       s[1] = p[4];
       s[2] = p[2];
       s[3] = p[0];
       s[4] = p[7];
       s[5] = p[5];
       s[6] = p[3];
       s[7] = p[1];

       return;
}              

////////////////////////////////////////////////////////////////
// Function KEY_PC_1 is used to call the PC-1 permutation
// Function Pammes Description  
// key_pc_1(s)
// Parameter Description:
//   s:     the main key
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void key_pc_1(unsigned char *s)
{
    unsigned char table[8][8] = {{57, 49, 41, 33, 25, 17, 9,'\0'},
                                 {1,  58, 50, 42, 34, 26, 18,'\0'},
                                 {10, 2,  59, 51, 43, 35, 27,'\0'},
                                 {19, 11, 3,  60, 52, 44, 36,'\0'},
                                 {63, 55, 47, 39, 31, 23, 15,'\0'},
                                 {7,  62, 54, 46, 38, 30, 22,'\0'},
                                 {14, 6,  61, 53, 45, 37, 29,'\0'},
                                 {21, 13, 5,  28, 20, 12, 4, '\0'}};
    unsigned char p[9] = {0,0,0,0,0,0,0,0,'\0'};
    unsigned char buf;
    unsigned char rule = 128;
    int  found = 0;
    int  i=0,j=0,k,l;
        
        //begin to the PC-1
        for(;i<8;i++)
          for(;j<64;j++){
            buf = s[i] & rule;
            for(k=0;k<8;k++){
               for(l=0;l<7;l++)
                 if((j+1)==table[k][l]){
                    buf = buf>>l;
                    p[k] = p[k] | buf;
                    found= 1;
                    break;
                 }
               if(found){
                   found = 0;
                   break;
               }
            }
            s[i] = s[i] << 1;
            if((j+1)%8==0){
              j++;
              break;
            }
          }

       for(i=0;i<8;i++)
           s[i] = p[i];
       return;
}                       

////////////////////////////////////////////////////////////////
// Function SHIFT is used to move key left
// Function Pammes Description  
// shift(s,n)
// Parameter Description:
//   s:     children key in C or D unit
//   n:     the level of the loop
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void shift(unsigned char *s, int n)
{
	unsigned char lsh[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	unsigned char tmp[4];
    unsigned char rule = 128;
    int i,j;
        
        //begin to move left according the table lsh
        for(i=0;i<lsh[n-1];i++){
            for(j=0;j<4;j++){
                tmp[j] = s[j] & rule;
                s[j]=s[j] << 1;
            }
            for(j=0;j<4;j++){
                if(j==3){
                   tmp[0]=tmp[0]>>6;
                   s[j]=s[j] | tmp[0];
                   break;
                }
                tmp[j+1] = tmp[j+1]>>6;
                s[j]= s[j] | tmp[j+1];
            }
        }
}

////////////////////////////////////////////////////////////////
// Function KEY_PC_2 is used to call the PC-2 permutation
// Function Pammes Description  
// key_pc_2(s)
// Parameter Description:
//   s:     the main key
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void key_pc_2(unsigned char *s)
{
    unsigned char table[8][7] = {{14, 17, 11, 24, 1,  5,  '\0'},
                                 {3,  28, 15, 6,  21, 10, '\0'},
                                 {23, 19, 12, 4,  26, 8,  '\0'},
                                 {16, 7,  27, 20, 13, 2,  '\0'},
                                 {41, 52, 31, 37, 47, 55, '\0'},
                                 {30, 40, 51, 45, 33, 48, '\0'},
                                 {44, 49, 39, 56, 34, 53, '\0'},
                                 {46, 42, 50, 36, 29, 32, '\0'}};
    unsigned char p[8] = {0,0,0,0,0,0,0,0};
    unsigned char buf;
    unsigned char rule = 128;
    int  found = 0;
    int  i=0,j=0,k,l;
        
        //begin the PC-2
        for(;i<8;i++)
           for(;j<57;j++){
              buf = s[i] & rule;
              for(k=0;k<8;k++){
                 for(l=0;l<6;l++)
                    if((j+1)==table[k][l]){
                      buf = buf>>l;
                      p[k] = p[k] | buf;
                      found= 1;
                      break;
                    }
                 if(found){
                    found = 0;
                    break;
                 }
             }
             s[i] = s[i] << 1;
             if((j+1)%7==0){
                j++;
                break;
             }
          }

       for(i=0;i<8;i++)
          s[i] = p[i];

       return;
}         
  
////////////////////////////////////////////////////////////////
// Function EXP_PERM is used to call the e permutation
// Function Pammes Description  
// exp_perm(s1,s2)
// Parameter Description:
//   s1:  the right 4 bytes
//   key: the key in this level;
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void exp_perm(unsigned char *s1, unsigned char *s2)
{
    unsigned char top[4];
    unsigned char end[4];
    unsigned char rule_top = 1;
    unsigned char rule_end = 128;
    unsigned char tmp_top;
    unsigned char tmp_end;
    int  i;
        
        //begin the e permutation
        for(i=0;i<4;i++){
            top[i] = s1[i] & rule_top;
            top[i] = top[i] << 7;
            end[i] = s1[i] & rule_end;
            end[i] = end[i] >> 5;
        }

        tmp_top = top[3];
        for(i=3;i>=0;i--){
           if(i==0){
              top[i] = tmp_top;
              break;
           }
           top[i] = top[i-1];
        }

        tmp_end = end[0];
        for(i=0;i<4;i++){
           if(i==3){
              end[i] = tmp_end;
              break;
           }
           end[i] = end[i+1];
        }

        for(i=0;i<4;i++){
           tmp_top = s1[i] & 248;
           tmp_top = tmp_top >> 1;
           tmp_top = top[i] | tmp_top;
           s2[i*2] = tmp_top;
        }

        for(i=0;i<4;i++){
           tmp_end = s1[i] & 31;
           tmp_end = tmp_end << 3;
           tmp_end = end[i] | tmp_end;
           s2[i*2+1] = tmp_end;
        }
}   

////////////////////////////////////////////////////////////////
// Function RK_XOR is used to xor the right unit and the key
// in current level.
// Function Pammes Description:  
// rk_xor(s1,s2)
// Parameter Description:
//   s1:  the right 4 bytes througth the e permutation
//   s2:  the key in this level;
// Return Val:
//   void
/////////////////////////////////////////////////////////////////

void rk_xor(unsigned char *s1, unsigned char *s2)
{
     int i;
    
        for(i=0;i<8;i++)
           s1[i] = s1[i] ^ s2[i];
}

////////////////////////////////////////////////////////////////
// Function S_BOX is used to call the S_BOX
// Function Pammes Description:  
// s_box(p)
// Parameter Description:
//   p:  the right 4 bytes througth the e permutation and xor
// Return Val:
//   void
/////////////////////////////////////////////////////////////////

void s_box(unsigned char *p)
{
     unsigned char s[8][4][16] = {
              {
               {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
               {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
               {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
               {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
              },
              {
               {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
               {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
               {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
               {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
              },
              {
               {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
               {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
               {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
               {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
              },
              {
               {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
               {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
               {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
               {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
              },
              {
               {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
               {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
               {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
               {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
              },
              {
               {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
               {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
               {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
               {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
              },
              {
               {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
               {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
               {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
               {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
              },
              {
               {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
               {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
               {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
               {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
              }
     };
     unsigned char line_rule = 132;
     unsigned char col_rule = 120;
     unsigned char line;
     unsigned char col;
     int  i;
          
          //to change in the S_BOX table
          for(i=0;i<8;i++){
             line = p[i] & line_rule;
             col = p[i] & col_rule;
             col = col >> 3;
             switch(line){
                case 0:
                       p[i] = s[i][0][col];
                       break;
                case 4:
                       p[i] = s[i][1][col];
                       break;
                case 128:
                       p[i] = s[i][2][col];
                       break;
                case 132:
                       p[i] = s[i][3][col];
                       break;
                default: break;
            }
         }
}

////////////////////////////////////////////////////////////////
// Function p_perm is used to the p permutation
// Function Pammes Description:  
// p_perm(s)
// Parameter Description:
//   s:  the right 4 bytes througth the e permutation and xor
//       and s_box
// Return Val:
//   void
/////////////////////////////////////////////////////////////////

void p_perm(unsigned char *s)
{
     unsigned char table[8][4] = {
                   {16, 7, 20, 21},
                   {29, 12, 28, 17},
                   {1, 15, 23, 26},
                   {5, 18, 31, 10},
                   {2, 8, 24, 14},
                   {32, 27, 3, 9},
                   {19, 13, 30, 6},
                   {22, 11, 4, 25}
     };
     unsigned char p[8] = {0,0,0,0,0,0,0,0};
     unsigned char buf;
     unsigned char rule = 128;
     int found = 0;
     int i=0,j=0,k,l;
         
         //begin to the P permutation
     	 for(k=0;k<8;k++)
        	 s[k] = s[k] << 4;

         for(;i<8;i++)
         	for(;j<32;j++){
               buf = s[i] & rule;
               for(k=0;k<8;k++){
                 for(l=0;l<4;l++)
                    if((j+1)==table[k][l]){
                      buf = buf>>l;
                      p[k] = p[k] | buf;
                      found= 1;
                      break;
                    }
                 if(found){
                   found = 0;
                   break;
                  }
              } 
              s[i] = s[i] << 1;
              if((j+1)%4==0){
                 j++;
                 break;
              }
            }

         for(i=0;i<4;i++){
            s[i] = p[2*i];
            p[2*i+1] = p[2*i+1] >> 4;
            s[i] = s[i] | p[2*i+1];
         }
}

////////////////////////////////////////////////////////////////
// Function lf_xor is used to xor the left unit and P(B) unit
// Function Pammes Description:  
// lf_xor(s1,s2)
// Parameter Description:                     
//   s1:  the left unit
//   s2:  the right 4 bytes througth the F function
// Return Val:
//   void
/////////////////////////////////////////////////////////////////

void lf_xor(unsigned char *s1, unsigned char *s2)
{
     int i;

         for(i=0;i<4;i++)
            s1[i] = s1[i] ^ s2[i];
}          

////////////////////////////////////////////////////////////////
// Function f_rk is used to call the F encipher function
// Function Pammes Description  
// f_rk(s1,s2)
// Parameter Description:
//   s1:     the right unit
//   s2:     the key in current level
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void f_rk(unsigned char *s1, unsigned char *s2)
{
    unsigned char p[8];
    int i;
         
         //Call the E permutation 
         exp_perm(s1,p);         
         
         //Xor the right unit and the key in current level
         rk_xor(p, s2);                                   
         
         //Call the S_BOX
         s_box(p);       
         
         //Call the P permutation
         p_perm(p);

         for(i=0;i<4;i++)
             s1[i] = p[i];
}
      
////////////////////////////////////////////////////////////////
// Function lst_permutation is used to call the last permutation
//    (LP-1).
// Function Pammes Description:  
// lst_permutation(s)
// Parameter Description:                     
//   s:  the data throught the decipher
// Return Val:
//   void
/////////////////////////////////////////////////////////////////

void lst_permutation (unsigned char *s)
{
     unsigned char p[8];
     unsigned char q[8];
     unsigned char buf;
     unsigned char rule = 1;
     int i,j;

         //begin the last permutation (LP-1)
         q[0] = s[3];
         q[1] = s[7];
         q[2] = s[2];
         q[3] = s[6];
         q[4] = s[1];
         q[5] = s[5];
         q[6] = s[0];
         q[7] = s[4];

         for(i=0;i<8;i++){
             p[i] = 0;
             for(j=7;j>=0;j--){
                 buf = q[j];
                 q[j] = q[j] >> 1;
                 buf = buf & rule;
                 p[i] = p[i] | buf;
                 if(j==0) break;
                 p[i] = p[i] << 1;
             }
         }

         for(i=0;i<8;i++)
             s[i] = p[i];

         return;
}

////////////////////////////////////////////////////////////////
// Function KEY_GEN is used to genation the children key
// Function Pammes Description  
// key_gen(s1,s2)
// Parameter Description:
//   s1:     the main key
//   s2:     the children keys
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void key_gen(unsigned char *s1, unsigned char s2[][8])
{
   unsigned char c[4];
   unsigned char d[4];
   unsigned char p[8];
   int i,j;
         
         //Call the PC-1
         key_pc_1(s1);
         
         //Create the C and D
         memcpy(c, s1, 4);
         memcpy(d, s1+4, 4);
         
         //begin to loop 16
         for (i=1;i<17;i++){
             //move C and D left 
             shift(c,i);
             shift(d,i);    
             
             //Call the PC-2
             for(j=0;j<4;j++){
                 p[j] = c[j];
                 p[j+4] = d[j];
             }
                          
             key_pc_2(p);
             memcpy(s2[i-1], p, 8);
         }                  
         
         return;
}       

////////////////////////////////////////////////////////////////
// Function DESDECIPH is used to decipher the data
// Function Pammes Description  
// desdeciph(data,key)
// Parameter Description:
//   data:  return deciphed data and deciphing data
//   key:    the key to decipher;
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void desdeciph(unsigned char *data, unsigned char *key)
{
    unsigned char l[4];
    unsigned char r[4];
    unsigned char proc[4];
    unsigned char key_level[16][8];
    int i;
        
        //inital permutation
        ini_permutation(data);
        
        //key generation
        key_gen(key, key_level);
        
        //create right and left units
        memcpy(l, data, 4);
        memcpy(r, data+4, 4);
        memcpy(proc, r, 4);
        
        //begin to decipher
        
        for(i=15;i>=0;i--){
            f_rk(proc, key_level[i]);    //call the function F
            lf_xor(l, proc);             //Xor the left and and P(B)
            if(i==0) break;              //end when loop 16
            
            //create the left and right units in the next loop
            memcpy(proc, l, 4);
            memcpy(l, r, 4);
            memcpy(r, proc, 4);
        }                                        
        
        //Call the lp-1
        
        memcpy(data, l, 4);
        memcpy(data+4, r, 4);
        lst_permutation(data);

}

////////////////////////////////////////////////////////////////
// Function DESENCIPH is used to encipher the data
// Function Pammes Description  
// desenciph(data,key)
// Parameter Description:
//   data:  return enciphed data and enciphing data
//   key:   the key to encipher;
// Return Val:
//     void
/////////////////////////////////////////////////////////////////

void desenciph(unsigned char *data, unsigned char *key)
{
     unsigned char l[4];
     unsigned char r[4];
     unsigned char proc[4];
     unsigned char key_level[16][8];
     int i=1;   
        
        //inital permutation
        ini_permutation(data);
        
        //key generation
        key_gen(key, key_level);
        
        //create right and left units
        memcpy(l, data, 4);
        memcpy(r, data+4, 4);
        memcpy(proc, r, 4);   
        
        //begin to encipher
        
        for(i=0;i<16;i++){
            f_rk(proc, key_level[i]);      //call the function F
            lf_xor(l, proc);               //Xor the left and and P(B)
            if(i==15) break;               //end when loop 16
            
            //create the left and right units in the next loop
            memcpy(proc, l, 4);
            memcpy(l, r, 4);
            memcpy(r, proc, 4);
        } 
        
        //Call the lp-1
        memcpy(data, l, 4);
        memcpy(data+4, r, 4);
        lst_permutation(data);

}  

unsigned short DecHstr( unsigned long ivDec, short ivNum, char *srHex )
{
	char str[20];
	int i, slen;

	srHex[0] = '\0';
	sprintf( str, "%X", ivDec);
	slen = strlen( str);
	if( ivNum == 0)
	{
		if( slen%2 == 1)
		{
			strcat( srHex, "0");
			strcat( srHex, str);
		}
		else
			strcat( srHex, str);
	}
	else if( slen < 2*ivNum)
	{
		for( i=slen; i<2*ivNum; i++)
			strcat(srHex, "0");
		strcat(srHex, str);
	}
	else 
		strcat( srHex, str+slen-2*ivNum);

	return 0;
}

void MATH_License( )
{
	bLicenseOK = TRUE;
}
