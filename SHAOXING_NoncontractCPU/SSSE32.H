#ifndef SSSE32_H
#define SSSE32_H
#include <windows.h>


//状态码
#define IFD_OK	0			     //执行成功
#define IFD_ICC_TypeError	-1	     //卡片类型不对
#define IFD_ICC_NoExist	-2		     //无卡
#define IFD_ICC_NoPower	-3		     //有卡未上电
#define IFD_ICC_NoResponse	-4	     //卡片无应答
#define IFD_ConnectError	-11	     //读卡器连接错
#define IFD_UnConnected	-12	             //未建立连接(没有执行打开设备函数)
#define IFD_BadCommand	-13	             //(动态库)不支持该命令
#define IFD_ParameterError	-14	     //(发给动态库的)命令参数错
#define IFD_CheckSumError	-15	     //信息校验和出错

#define IFD_PIN_LEN -35   //密码长度不对
#define IFD_PIN_CANCEL -34 //按下取消键
#define IFD_KEY_LEN  -36  //下载密钥长度错误
#define IFD_KEY_NUM   -37 //密钥套数错误
#define IFD_KEY_EXIS  -38 //密钥不存在



#ifdef __cplusplus
extern "C" {
#endif


long WINAPI ICC_Reader_Open(char* dev_Name); 
long WINAPI ICC_Reader_Close(long ReaderHandle);
long WINAPI ICC_Reader_Libinfo(char* info);
long WINAPI ICC_Reader_ReadEEPROM (long ReaderHandle,int offset,int length,unsigned char *buffer);//从eeprom读取数据
long WINAPI ICC_Reader_WriteEEPROM (long ReaderHandle,int offset,int length,unsigned char *buffer);//从eeprom写入数据
long WINAPI ICC_Reader_GetDeviceVersion(long ReaderHandle,char *VSoftware,char *VHardware,char *VBoot,char *VDate); //如果VBoot为V0.0表示不带该该版本
long WINAPI ICC_Reader_GetDeviceCSN(long ReaderHandle,char* dev_Ser); //获取唯一序列号，从芯片获取
long WINAPI ICC_Reader_GetDeviceSN(long ReaderHandle,char* dev_Ser); //获取设备序列号，从设备获取
long WINAPI ICC_Reader_SetDeviceSN(long ReaderHandle,char* dev_Ser); //设置设备序列号
long WINAPI ICC_Reader_GetKeyBoardVersion(long ReaderHandle,char* ver); //获取键盘版本号
long WINAPI ICC_Reader_ChangeSlot(long ReaderHandle,unsigned char slot ); //切换卡座
long WINAPI ICC_Reader_SetDeviceReadMode(long ReaderHandle,unsigned char type ); //设置读卡器为主动/被动读卡模式 type==1 主动  type==0被动

long WINAPI ICC_Reader_DisCardType(long ReaderHandle); //1：CPU卡；2:4428卡；3:4442卡

long WINAPI ICC_Reader_GetMagCardMode(long ReaderHandle,unsigned short *Mode,unsigned short *Track); //获取磁卡读卡模式 Mode=1 通过软件控制读取 Mode=2模拟键盘
long WINAPI ICC_Reader_SetMagCardMode(long ReaderHandle,unsigned short Mode,unsigned short Track); //设置磁卡读卡模式 Mode=1 通过软件控制读取 Mode=2模拟键盘

long WINAPI ICC_Reader_pre_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response);//上电 冷 返回数据长度
long WINAPI ICC_Reader_hot_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response);//上电 热 返回数据长度
long WINAPI ICC_Reader_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response);//上电 冷+热 返回数据长度
long WINAPI ICC_Reader_PowerOnHEX(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response);//上电 冷+热 返回数据长度

/*
	大卡座ICC_Slot_No：0x01
	SAM1:0x11
	SAM2:0x12
	SAM3:0x13
	SAM4:0x14
	下同
*/
long WINAPI ICC_Reader_PowerOff(long ReaderHandle,unsigned char ICC_Slot_No);

long WINAPI ICC_Reader_GetStatus(long ReaderHandle,unsigned char ICC_Slot_No);//获取卡座状态

long WINAPI ICC_Reader_Application(long ReaderHandle,unsigned char ICC_Slot_No,
							 long Lenth_of_Command_APDU,unsigned char* Command_APDU,
							 unsigned char* Response_APDU);  //执行apdu命令  返回数据长度

long WINAPI ICC_Reader_ApplicationHEX(long ReaderHandle,unsigned char ICC_Slot_No,
							 char* Command_APDU,
							 char* Response_APDU);  //执行apdu命令  返回数据长度

//long WINAPI ICC_Reader_Libinfo(char* info);

long WINAPI ICC_PosBeep(long ReaderHandle, unsigned char time);//蜂鸣
//如果读取9600的卡则cpuetu应为96     如果读取38400的卡则cpuetu应为20
long WINAPI ICC_SetCpupara(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char cpupro,unsigned char cpuetu);//设置速率


/*############ 4442基本操作函数#################*/

long WINAPI ICC_Reader_4442_PowerOn(long ReaderHandle,unsigned char *data); //4442卡上电
long WINAPI ICC_Reader_4442_PowerOnHEX(long ReaderHandle,unsigned char *dataHex); //4442卡上电，返回HEX串
long WINAPI ICC_Reader_4442_PowerOff(long ReaderHandle); //4442卡下电
long WINAPI ICC_Reader_4442_Read(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡读数据
long WINAPI ICC_Reader_4442_ReadHEX(long ReaderHandle,int offset,int len,unsigned char *dataHex); //4442卡读数据，返回HEX串
long WINAPI ICC_Reader_4442_Write(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡写数据 
long WINAPI ICC_Reader_4442_WriteHEX(long ReaderHandle,int offset,int len,unsigned char *dataHex); //4442卡写数据，传入数据为HEX串
long WINAPI ICC_Reader_4442_Verify(long ReaderHandle,unsigned char *key); //4442卡认证密钥
long WINAPI ICC_Reader_4442_VerifyHEX(long ReaderHandle,unsigned char *keyHex); //4442卡认证密钥，传入密钥为HEX串
long WINAPI ICC_Reader_4442_Change(long ReaderHandle,unsigned char *newkey); //4442卡修改密钥
long WINAPI ICC_Reader_4442_ChangeHEX(long ReaderHandle,unsigned char *newkeyHex); //4442卡修改密钥，传入密钥为HEX串
long WINAPI ICC_Reader_4442_ReadProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡读保护数据
long WINAPI ICC_Reader_4442_WriteProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡写保护数据
long WINAPI ICC_Reader_4442_ReadCount(long ReaderHandle); //读取4442卡密钥剩余认证次数 返回次数0~3次

/*############ 24cXX基本操作函数#################*/

long WINAPI ICC_Reader_24c_PowerOn(long ReaderHandle,unsigned char *data,unsigned char flag); //24cxx卡上电 flag=0为24C01~16  flag=1为24C32~1024
long WINAPI ICC_Reader_24c_PowerOff(long ReaderHandle,unsigned char flag); //24cxx卡下电 flag=0为24C01~16  flag=1为24C32~1024
long WINAPI ICC_Reader_24c_Read(long ReaderHandle,int offset,int len,unsigned char *data,unsigned char flag); //24cxx卡读数据 flag=0为24C01~16  flag=1为24C32~1024
long WINAPI ICC_Reader_24c_Write(long ReaderHandle,int offset,int len,unsigned char *data,unsigned char flag); //24cxx卡写数据  flag=0为24C01~16  flag=1为24C32~1024

/*############ 4428 基本操作函数#################*/

long WINAPI ICC_Reader_4428_PowerOn(long ReaderHandle,unsigned char *data); //4428卡上电
long WINAPI ICC_Reader_4428_PowerOnHEX(long ReaderHandle,unsigned char *dataHex); //4428卡上电，返回HEX串
long WINAPI ICC_Reader_4428_PowerOff(long ReaderHandle); //4428卡下电
long WINAPI ICC_Reader_4428_Read(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡读数据
long WINAPI ICC_Reader_4428_ReadHEX(long ReaderHandle,int offset,int len,unsigned char *dataHex); //4428卡读数据，返回HEX串
long WINAPI ICC_Reader_4428_Write(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡写数据 
long WINAPI ICC_Reader_4428_WriteHEX(long ReaderHandle,int offset,int len,unsigned char *dataHEX); //4428卡写数据，传入HEX串
long WINAPI ICC_Reader_4428_Verify(long ReaderHandle,unsigned char *key); //4428卡认证密钥
long WINAPI ICC_Reader_4428_VerifyHEX(long ReaderHandle,unsigned char *keyHex); //4428卡认证密钥，传入密钥为HEX串
long WINAPI ICC_Reader_4428_Change(long ReaderHandle,unsigned char *newkey); //4428卡修改密钥
long WINAPI ICC_Reader_4428_ChangeHEX(long ReaderHandle,unsigned char *newkeyHex); //4428卡修改密钥，传入密钥为HEX串
long WINAPI ICC_Reader_4428_ReadProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡读保护数据
long WINAPI ICC_Reader_4428_WriteProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡写保护数据
long WINAPI ICC_Reader_4428_ReadCount(long ReaderHandle); //读取4428卡密钥剩余认证次数 返回次数0~8次


long WINAPI Rcard(long ReaderHandle,unsigned char ctime,int track,unsigned char *rlen,char *getdata);//读磁条卡

long WINAPI ICC_DispInfo(long ReaderHandle,unsigned char row,unsigned char list,char *data); //显示信息

long WINAPI ICC_DispSound(long ReaderHandle,unsigned char type,unsigned char nMode); //声音提示信息 type(1~14) nMode==0内置键盘语音，nMode==1外置键盘语音
/*
	1、请插卡 2、请刷卡 3、读卡错误 4、请输入密码  5、密码错误  6、操作成功 7、操作超时 8、操作失败 9、请取回卡 10、请重新输入密码 11、请再次输入密码 12、请输入新密码 13、请输入旧密码 14、请确认新密码
*/

long WINAPI ICC_CtlLight(long ReaderHandle);//清屏，关屏

long WINAPI ICC_ChangeLight(long ReaderHandle,unsigned char mode);//改变屏幕亮度 mode=1 调亮  mode=0调暗

long WINAPI ICC_DownLoadKey(long ReaderHandle,unsigned char group,unsigned char *Key);//下载工作密钥到键盘里面，group：01、02、03共3组；Key16字符密钥，例如：1122334455667788

long WINAPI ICC_DownLoadMainKey(long ReaderHandle,int mainkeyno,unsigned char *Key);//下载主密钥,0~7组，用于对密文的工作密钥解密 Key==16字节 3DES 8字节 DES

long WINAPI ICC_DownLoadUserKey(long ReaderHandle,int MainKeyNo,int UserKeyNo,unsigned char *Key);//下载工作密钥到键盘里面，0~1组，用主密钥对密文的工作密钥解密 Key==16字节 3DES 8字节 DES

long WINAPI ICC_SetKeyBoardLength(long ReaderHandle,int KeyLen);//设置键盘获取密钥长度，密码长度未达到该长度时，应报错

long WINAPI ICC_ActiveKey(long ReaderHandle,int MainKeyNo,int UserKeyNo);//激活主密钥、工作密钥

long WINAPI ICC_GetInputPass(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start,unsigned char stop,unsigned char *cpass);//获取密码，带超时 start==0用内置键盘，start==1用外置键盘

long WINAPI ICC_GetInputPassENC(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start,unsigned char group,unsigned char *cpass);//获取密码,密文,带超时 start==0用内置键盘，start==1用外置键盘,group用第几组密钥

long WINAPI ICC_GetEnPass(long ReaderHandle, unsigned char ctime,int MainKeyNo, int UserkeyNo, unsigned char* CardNo,unsigned char *rlen,unsigned char *cpass);//获取密码,密文,MainKeyNo 主密钥号，UserkeyNo 工作密钥号  CardNo 卡号

long WINAPI ICC_GetInputPassEx(long ReaderHandle, unsigned char ctime, int *rlen, unsigned char * cpass, int disinfo,unsigned char type);//xians yuyin

long WINAPI ICC_GetDESMAC(long ReaderHandle,int Type,int MainKeyNo, int UserkeyNo, unsigned char *InData,unsigned char *rlen,unsigned char *OutData);// Type 0-加密 1-POS MAC 2- ANSIX9.19 MAC

long WINAPI ICC_GetInputPassID(long ReaderHandle, unsigned char ctime, unsigned char *rlen, unsigned char start,unsigned char stop,unsigned char * cardID,unsigned char * cpass);//获取密码，带超时,带ID

long WINAPI ICC_GetTimeOut(long ReaderHandle,unsigned char flag);//获取密码、读磁条超时

long WINAPI ICC_PassGet(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char start,unsigned char stop,unsigned char * cpass);//获取密码

long WINAPI ICC_PassGetENC(long ReaderHandle,unsigned char *rlen,unsigned char start,unsigned char group,unsigned char * cpass);//获取密码,密文

long WINAPI ICC_PassGetID(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char start,unsigned char stop,unsigned char * cardID,unsigned char * cpass);//获取密码，带卡号

long WINAPI ICC_PassCheck(long ReaderHandle,unsigned char *rlen,unsigned char * cpass); //查下数据是否到了

long WINAPI ICC_PassCheck1(long ReaderHandle,unsigned char *rlen,unsigned char * cpass); //查下数据是否到了

long WINAPI ICC_PassSetDES(long ReaderHandle,unsigned char DES); //设置加密模式3des or des

long WINAPI ICC_PassSetDevID(long ReaderHandle,unsigned char *devID);//设置键盘设备ID

long WINAPI ICC_PassGetDevID(long ReaderHandle,unsigned char *devID);//获取键盘设备ID

long WINAPI ICC_PassSetKeyLen(long ReaderHandle,unsigned char len);//设置密码长度

long WINAPI ICC_PassDes(long ReaderHandle,unsigned char flag,unsigned char *InData,unsigned char *OutData); //对数据加解密 flag 0 加密 1 解密

long WINAPI ICC_PassSetFD(long ReaderHandle,unsigned char fd);//密码键盘设置波特率

long WINAPI ICC_GetInputPassACOUNT(long ReaderHandle, unsigned char ctime, unsigned char *rlen,unsigned char * cardID,unsigned char * cpass);//获取密码，带超时,带16 ID

long WINAPI ICC_PassGetACOUNT(long ReaderHandle,unsigned char *rlen,unsigned char time,unsigned char * cardID,unsigned char * cpass);//获取密码，带16卡号

long WINAPI ICC_PassMAC(long ReaderHandle,unsigned char *InData,unsigned char *OutData); //对数据算MAC flag 0 未结束 1 结束

long WINAPI ICC_PassECB(long ReaderHandle,unsigned char *rlen,unsigned char *InData,unsigned char *OutData); //对数据算ECB 

long WINAPI ICC_PassChangeMkey(long ReaderHandle,unsigned char MkeyId ,unsigned char *Newmkey); //修改主密钥 

long WINAPI ICC_PassChangeWkey(long ReaderHandle,unsigned char MkeyId ,unsigned char Wkeyid,unsigned char *Newmkey); //修改工作密钥 

long WINAPI ICC_PassActiveWkey(long ReaderHandle,unsigned char MkeyId ,unsigned char Wkeyid); //激活工作密钥 


/*############非接基本操作函数#################*/

long WINAPI PICC_Reader_SetTypeA(long ReaderHandle);//设置读typeA

long WINAPI PICC_Reader_SetTypeB(long ReaderHandle);//设置读typeB

long WINAPI PICC_Reader_Select(long ReaderHandle,unsigned char cardtype);//选择卡片，41为typea,M1 42为typeb,TypeB卡片需先上电后选卡

long WINAPI PICC_Reader_Request(long ReaderHandle);//typea M1请求卡片

long WINAPI PICC_Reader_RFControl(long ReaderHandle);//关闭天线

long WINAPI PICC_Reader_anticoll(long ReaderHandle,unsigned char *uid);//防碰撞 typea M1卡片

long WINAPI PICC_Reader_FindCard(long ReaderHandle);//寻找磁场区域是否有卡

/*############ M1卡操作函数#################*/
long WINAPI PICC_Reader_Authentication(long ReaderHandle,unsigned char Mode, unsigned char SecNr);//认证密钥 M1

long WINAPI PICC_Reader_Authentication_Pass(long ReaderHandle,unsigned char Mode, unsigned char SecNr,unsigned char *PassWord);//认证密钥M1 带密钥参数

long WINAPI PICC_Reader_Readval(long ReaderHandle,unsigned char Addr,unsigned long *value);	//读值

long WINAPI PICC_Reader_Initval(long ReaderHandle,unsigned char Addr,unsigned long value);//初始化值

long WINAPI PICC_Reader_Increment(long ReaderHandle,unsigned char Addr,unsigned long value);	//增值

long WINAPI PICC_Reader_Decrement(long ReaderHandle,unsigned char Addr,unsigned long value);//减值

long WINAPI PICC_Reader_Read(long ReaderHandle,unsigned char Addr,unsigned char *Data);	//读取卡片M1

long WINAPI PICC_Reader_Write(long ReaderHandle,unsigned char Addr,unsigned char *Data);//写入数据M1

long WINAPI PICC_Reader_LoadKey(long ReaderHandle,unsigned char Mode,unsigned char SecNr,unsigned char *Key);//装载密钥

long WINAPI PICC_Reader_ReadHEX(long ReaderHandle,unsigned char Addr,unsigned char *DataHex);	//读取卡片M1

long WINAPI PICC_Reader_WriteHEX(long ReaderHandle,unsigned char Addr,unsigned char *DataHex);//写入数据M1

long WINAPI PICC_Reader_LoadKeyHEX(long ReaderHandle,unsigned char Mode,unsigned char SecNr,unsigned char *KeyHex);//装载密钥
																					 
/*
SecNr:扇区号
Mode：01 02 03 分别为第一、二、三套密钥KeyA
04 05 06 分别为第一、二、三套密钥KEYB
*/

/*############ TypeA CPU 卡操作函数 #################*/
long WINAPI PICC_Reader_PowerOnTypeA(long ReaderHandle,unsigned char* Response);//上电 返回数据长度 失败小于0

/*############ TypeB CPU 卡操作函数#################*/

long WINAPI PICC_Reader_PowerOnTypeB(long ReaderHandle,unsigned char* Response);//上电 返回数据长度 失败小于0

long WINAPI PICC_Reader_Application(long ReaderHandle,
							 long Lenth_of_Command_APDU,unsigned char* Command_APDU,
							 unsigned char* Response_APDU);  //type a/b执行apdu命令 返回数据长度 失败小于0

/*身份证读写函数*/
long WINAPI PICC_Reader_ID_Request(long ReaderHandle);//身份证寻卡

long WINAPI PICC_Reader_ID_Select(long ReaderHandle);//身份证选卡

long WINAPI PICC_Reader_ID_Read(long ReaderHandle,unsigned char* Response);//身份证读卡

long WINAPI PICC_Reader_ID_ReadUID(long ReaderHandle,unsigned char* UID);//身份证UID读取

long WINAPI PICC_Reader_ReadIDMsg(long ReaderHandle, const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire,char * pErrMsg);
//如果pBmpFile==NULL，则不生成照片，如需生成照片，这里请传入路径。例如：C:/zhaopian/zp.bmp
long WINAPI PICC_Reader_ReadIDInfo(long ReaderHandle, char* pBmpFileData, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData,  char *pExpire,char * pErrMsg);
//如果pBmpFileData==NULL，则不生成照片，如需生成照片，这里输出照片数据信息，需分配77725空间

long WINAPI  StrToHex(unsigned char *strIn,int inLen,unsigned char *strOut);//将字符命令流转为16进制流

long WINAPI  HexToStr(unsigned char *strIn,int inLen,unsigned char *strOut);//将16进制命令流转为字符流

#ifdef __cplusplus
}
#endif

#endif