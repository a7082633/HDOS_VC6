// HDCardDev.h : HDCardDev DLL 的主头文件
//

#ifndef CARDDEV_H
#define CARDDEV_H

/*状态码*/
#define IFD_OK	0					     /*执行成功*/
#define IFD_OpenError	-1		     /*打开串口失败*/
#define IFD_CloseError	-2			 /*关闭串口失败*/
#define IFD_SendError	-3			 /*发送数据失败*/
#define IFD_RevError   	-4	         /*接收数据失败*/
#define IFD_ActiveError	-5	           /*寻卡失败*/
#define IFD_AuthError    -6           /*认证失败*/
#define IFD_ReadError    -7          /*读M1失败*/
#define IFD_WriteError   -8              /*写M1失败*/
#define IFD_ReadIDCardError -9    /*写M1失败*/
#define IFD_OTHER	        -10           /*其他错误*/

/*############设备操作函数#################*/
#ifdef __cplusplus
extern "C" {
#endif

long WINAPI hd_Open(int Port);  //打开串口

long WINAPI hd_Close();  //关闭串口

long WINAPI hd_Active(TCHAR * uid);  // M1卡寻卡操作

long WINAPI hd_AuthPass(unsigned char Mode, unsigned char SecNr, unsigned char *PassWord); //M1卡认证

long WINAPI hd_Read(unsigned char Addr,unsigned char*Data);  //M1卡读块数据

long WINAPI hd_Write(unsigned char Addr, unsigned char*Data);  //M1卡写块数据

long WINAPI hd_ReadIDCard(const TCHAR* sBmpFile,
					   TCHAR* sName, 
					   TCHAR* sSex, 
					   TCHAR* sNation, 
					   TCHAR* sBirth, 
					   TCHAR* sAddress, 
					   TCHAR* sCertNo, 
					   TCHAR* sDepartment, 
					   TCHAR* sEffectTime,
					   TCHAR* sExpire);

#ifdef __cplusplus
}
#endif
#endif