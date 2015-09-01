extern unsigned short  HD_3DES_Decrypt( char *svHex, char *svKey, short ivMode, char *srHex );
extern unsigned short  HD_3DES_Encrypt( char *svHex, char *svKey, short ivMode, char *srHex );
extern unsigned short  HD_3DES_MAC( char *svHex, char *svKey, char *srHex );
extern unsigned short  HD_DES_Decrypt( char *svHex, char *svKey, short ivMode, char *srHex );
extern unsigned short  HD_DES_Encrypt( char *svHex, char *svKey, short ivMode, char *srHex );
extern unsigned short  HD_XorHstr( char *svHex1, char *svHex2, short ivNum, char *srHex );
extern unsigned short  HD_DecHstr( unsigned long ivDec, short ivNum, char *srHex );

extern unsigned short HD_3DES_DecryptByte( unsigned char *svHex, short svHexLen, unsigned char *srHex, short *srHexLen);
extern unsigned short HD_3DES_EncryptByte( unsigned char *svHex, short svHexLen, unsigned char *srHex, short *srHexLen);
// 
// extern INT APIENTRY des(unsigned char *key,unsigned char *instr,unsigned char *outstr,unsigned char *outser,int len,int lock);
// extern void des_code(unsigned char *,unsigned char *,unsigned char *,int);
// extern BYTE hextostr(BYTE inbyte,int hl);