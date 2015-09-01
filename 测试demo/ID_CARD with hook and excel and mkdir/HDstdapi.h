#ifndef HDSTDAPI_H
#define HDSTDAPI_H
#include <windows.h>

//状态码
#define SHD_OK					  0		 //执行成功
#define SHD_Connect_Error		 -1	     //设备连接错
#define SHD_UnConnected		 	 -2	     //设备未建立连接(没有执行打开设备函数)
#define SHD_BadLoadDLL_Error	 -3	     //(动态库)加载失败
#define SHD_Parameter_Error		 -4	     //(发给动态库的)参数错
#define SHD_Request_Error		 -5		 //寻卡失败
#define SHD_Select_Error		 -6		 //选卡失败
#define SHD_ReadBase_Error	     -7		 //读卡失败
#define SHD_ReadBaseFP_Error     -8	     //读取追加信息失败
#define SHD_ReadADD_Error	     -9	     //读取追加信息失败
#define SHD_Sam_Error	        -10      //管理通信失败
#define SHD_CheckSam_Error	    -11      //检验通信失败
#define SHD_SamToFinger_Error	-12      //管理通信模块不支持获取指纹
#define SHD_OTHER_ERROR	        -999	 //其他异常错误



#ifdef __cplusplus
extern "C" {
#endif

int WINAPI HD_InitComm(int Port);
int WINAPI HD_CloseComm(int Port);
int WINAPI HD_Authenticate();

int WINAPI HD_Read_IDInfo(char* pBmpData, char *BaseMsgData);
int WINAPI HD_Read_IDFPInfo(char* pFingerData, char* pBmpData, char *BaseMsgData);

int WINAPI HD_Read_BaseMsg(const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire);
//如果pBmpFile==NULL，则不生成照片，如需生成照片，这里请传入路径。例如：C:/zhaopian/zp.bmp
int WINAPI HD_Read_BaseInfo(char* pBmpData, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData,  char *pExpire);
//如果pBmpFileData==NULL，则不生成照片，如需生成照片，这里输出照片数据信息，需分配77725空间

int WINAPI HD_Read_BaseFPMsg(char* pFingerData, const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire);
//如果pBmpFile==NULL，则不生成照片，如需生成照片，这里请传入路径。例如：C:/zhaopian/zp.bmp
int WINAPI HD_Read_BaseFPInfo(char* pFingerData, char* pBmpData, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData,  char *pExpire);
//如果pBmpFileData==NULL，则不生成照片，如需生成照片，这里输出照片数据信息，需分配77725空间

int WINAPI HD_Read_NewAppMsg(char* AppAddressMsg);
//读取 身份证追加地址信息

int WINAPI HD_Get_SAMIDToStr(char* SAMIDMsg);
//获取管理模块ID，输出为字符串

int WINAPI HD_ResetSAM(int Port);
int WINAPI HD_Set_MaxRFByte(unsigned char RFByte);
int WINAPI HD_Get_SAMStatus();
int WINAPI HD_Get_SAMID(unsigned char* SAMID);
int WINAPI HD_ID_RequestIDCard();
int WINAPI HD_ID_SelectIDCard();

#ifdef __cplusplus
}
#endif

#endif