#ifndef HD300_V1_H
#define HD300_V1_H
#include <windows.h>


//状态码
#define IFD_OK	0					 //执行成功
#define IFD_ICC_TypeError	-1		 //卡片类型不对
#define IFD_ICC_NoExist	-2			 //无卡
#define IFD_ICC_NoPower	-3			 //有卡未上电
#define IFD_ICC_NoResponse	-4	     //卡片无应答
#define IFD_ConnectError	-11	     //读卡器连接错
#define IFD_UnConnected	-12	         //未建立连接(没有执行打开设备函数)
#define IFD_BadCommand	-13	         //(动态库)不支持该命令
#define IFD_ParameterError	-14	     //(发给动态库的)命令参数错
#define IFD_CheckSumError	-15	     //信息校验和出错


#ifdef __cplusplus
extern "C" {
#endif

/*############设备操作函数#################*/

long WINAPI ICC_Reader_Open(char* dev_Name); 
long WINAPI ICC_Reader_Close(long ReaderHandle);
long WINAPI ICC_PosBeep(long ReaderHandle, unsigned char time);//蜂鸣
long WINAPI ICC_Reader_EnterDFU (long ReaderHandle);  //进入USB下载程序状态
long WINAPI ICC_Reader_LeaveDFU (long ReaderHandle);  //离开USB下载程序状态
long WINAPI ICC_Reader_Libinfo (char* info);//,long length,unsigned char *buffer
long WINAPI ICC_Reader_ReadEEPROM(long ReaderHandle,long offset,long length,unsigned char *buffer);//从eeprom读取数据
long WINAPI ICC_Reader_WriteEEPROM(long ReaderHandle,long offset,long length,unsigned char *buffer);//从eeprom写入数据
long WINAPI ICC_Machine_Reset(long ReaderHandle);  
void WINAPI ICC_Reader_PPS(bool IsEnable); //是否启用PPS  false:不启用  true:启用
long WINAPI ICC_Reader_GetDeviceVersion(long ReaderHandle,char *VSoftware,char *VHardware,char *VBoot,char *VDate);//如果VBoot为V0.0表示不带该该版本
/*############接触CPU操作函数#################*/

long WINAPI ICC_Reader_pre_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response);//上电 冷 返回数据长度
long WINAPI ICC_Reader_hot_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response);//上电 热 返回数据长度

long WINAPI ICC_Reader_PowerOn(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char* Response);//上电  返回数据长度 冷+热
/*
	大卡座ICC_Slot_No：0x01
	SAM1:0x11
	SAM2:0x12
	SAM3:0x13
	SAM4:0x14
	下同

*/
long WINAPI ICC_Reader_PowerOff(long ReaderHandle,unsigned char ICC_Slot_No);//下电

long WINAPI ICC_Reader_GetStatus(long ReaderHandle,unsigned char ICC_Slot_No);//获取卡座状态

long WINAPI ICC_Reader_Application(long ReaderHandle,unsigned char ICC_Slot_No,
							 long Lenth_of_Command_APDU,unsigned char* Command_APDU,
							 unsigned char* Response_APDU);  //执行apdu命令  返回数据长度

long WINAPI ICC_Reader_LongApplication(long ReaderHandle,unsigned char ICC_Slot_No,
							 long Lenth_of_Command_APDU,unsigned char* Command_APDU,
							 unsigned char* Response_APDU);  //执行apdu命令  返回数据长度

//cpuetu=01、02、03、04代表的波特率分别为9600、19200、38400、115200 
//unsigned char cpupro ---- 卡的协议类型 =0表示T=0协议 =1表示T=1协议
long WINAPI ICC_SetCpupara(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char cpupro,unsigned char cpuetu);//设置速率

long WINAPI ICC_SetCpuETU(long ReaderHandle,unsigned char ICC_Slot_No,unsigned char cpupro,unsigned char cpuetu);//设置速率

/*############ 4442基本操作函数#################*/

long WINAPI ICC_Reader_4442_PowerOn(long ReaderHandle,unsigned char *data); //4442卡上电
long WINAPI ICC_Reader_4442_PowerOff(long ReaderHandle); //4442卡下电
long WINAPI ICC_Reader_4442_Read(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡读数据
long WINAPI ICC_Reader_4442_Write(long ReaderHandle,int offset,int len,unsigned char *data); //4442卡写数据 
long WINAPI ICC_Reader_4442_Verify(long ReaderHandle,unsigned char *key); //4442卡认证密钥
long WINAPI ICC_Reader_4442_Change(long ReaderHandle,unsigned char *newkey); //4442卡修改密钥
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
long WINAPI ICC_Reader_4428_PowerOff(long ReaderHandle); //4428卡下电
long WINAPI ICC_Reader_4428_Read(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡读数据
long WINAPI ICC_Reader_4428_Write(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡写数据 
long WINAPI ICC_Reader_4428_Verify(long ReaderHandle,unsigned char *key); //4428卡认证密钥
long WINAPI ICC_Reader_4428_Change(long ReaderHandle,unsigned char *newkey); //4428卡修改密钥
long WINAPI ICC_Reader_4428_ReadProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡读保护数据
long WINAPI ICC_Reader_4428_WriteProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡写保护数据
long WINAPI ICC_Reader_4428_ReadCount(long ReaderHandle); //读取4428卡密钥剩余认证次数 返回次数0~8次
/*############非接基本操作函数#################*/

long WINAPI PICC_Reader_SetTypeA(long ReaderHandle);//设置读typeA

long WINAPI PICC_Reader_SetTypeB(long ReaderHandle);//设置读typeB

long WINAPI PICC_Reader_Select(long ReaderHandle,unsigned char cardtype);//选择卡片，41为typea,M1 42为typeb,TypeB卡片需先上电后选卡

long WINAPI PICC_Reader_Request(long ReaderHandle);//typea M1请求卡片

long WINAPI PICC_Reader_RFControl(long ReaderHandle);//关闭天线

long WINAPI PICC_Reader_anticoll(long ReaderHandle,unsigned char *uid);//防碰撞 typea M1卡片

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

long  WINAPI HD_USBkey(long ReaderHandle,unsigned char _Adr, int len);//模拟键盘

/*############ 15693 卡操作函数#################*/

long WINAPI PICC_Reader_Inventory(long ReaderHandle,unsigned char* Response_APDU);//此命令通过防冲突用于得到读卡区域内所有卡片的序列号

long WINAPI PICC_Reader_15693_Read(long ReaderHandle,unsigned char blk_add,unsigned char* Response_APDU);//用来读取1个扇区的值

long WINAPI PICC_Reader_15693_Write(long ReaderHandle,unsigned char blk_add,unsigned char* data,
									unsigned char* Response_APDU);//对一个块进行写操作（每次只能写一个块）

long WINAPI PICC_Reader_API(long ReaderHandle,unsigned char* data,unsigned char* Response_APDU);//Data[0]	0代表写API,1代表锁API

long WINAPI PICC_Reader_DSFID(long ReaderHandle,unsigned char* data,unsigned char* Response_APDU);//Data[0]	0代表写DSFID,1代表锁DSFID

long WINAPI PICC_Reader_LockDataBlock(long ReaderHandle,unsigned char blk_add,unsigned char* Response_APDU);//用于锁定块内容。注意：此过程不可逆（不能解锁）块锁定后内容不能在修改。

long WINAPI PICC_Reader_SystemInfor(long ReaderHandle,unsigned char *Response_APDU);//用于得到卡的详细信息

#ifdef __cplusplus
}
#endif
#endif