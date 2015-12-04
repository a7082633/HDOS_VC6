struct TLV
{
	char flag[3];
	int length;
	int datastyle;
};

struct CYC
{
	int length;
	int datastyle;
};

long SelectFile1(char*data,char*err);
long SelectFile2(char*data,char*err);
long SelectFile3(char*data,char*err);
long SelectFile4(char*data,char*err);
long SelectFile5(char*data,char*err);
long SelectFile6(char*data,char*err);
long SelectFile7(char*data,char*err);
long SelectFile8(char*data,char*err);
long SelectFile9(char*data,char*err);
long SelectFile10(char*data,char*err);
long SelectFile11(char*data,char*err);
long SelectFile12(char*data,char*err);
long SelectFile13(char*data,char*err);
long SelectFile14(char*data,char*err);
long SelectFile15(char*data,char*err);
long SelectFile16(char*data,char*err);
long SelectFile17(char*data,char*err);
long SelectFile18(char*data,char*err);
long SelectFile19(char*data,char*err);
long GetPassWord(char*data,char*err);
long PerPINVerify(char*data,char*err);
long ResetPassWord(char*data,char*err);
long PerPINChange(char*data,char*err);
long PerPINUnLock(char*data,char*err);

long ExterAuthen(unsigned char *WorkKey,int level);//外部认证 
/*
	WorkKey：包含两字节内容，PSAM卡密钥表里面的用途和标示
	ATR：用户卡上电复位返回值
	CityCode：应用城市代码，在判断是否为社保卡时从卡片读取
	Random：随机数
	level：分散级数。1代表国家一级根密钥，用途为6X；2代表国家二级或省一级，用途为4X；3代表用途为2X的密钥
	result：返回8字节的密文
*/
long iReadRecord(char *EFid,int recNO,int datalength,int style,char *result);//读取记录文件 recNO:记录号；style=0 :an  style=1 :cn
long iReadBinary(char *EFid,int datalength,char *result);
long iReadBTLV(char *EFid,int recNO,int datalength,TLV *tl,int size,char *result);
long iReadXHFile(char *EFid,int recNO,int datalength,CYC *cy,int size,char *result);
long iWriteRecord(char *EFid,unsigned char * Tag,int recNO,unsigned char * datalength,unsigned char* style,char *data);
long iWriteBTLV(char *EFid,int recNO,int datalength,TLV *tl,int size,char *data,unsigned char _flag);
long iWriteXHFile(char *EFid,int recNO,int datalength,CYC *cy,int size,char *data);
long SelectFile(char *FileId);
long GetRandom();
long ReadIDCard(char *data,char *err);

long WINAPI Run(char* flag,char*data,char*err);