#ifndef ICCInter_H
#define ICCInter_H
/////////////////////// M1 Error Code ////////////////////////
#define REQUEST_FAILURE	       -1       //请求卡片失败
#define ANTICOL_FAILURE	       -2       //防碰撞失败
#define SELECT_FAILURE	       -3       //选卡失败
#define AUTH_FAILURE	       -4       //验证密码失败
#define READ_FAILURE	       -5       //读M1卡数据失败
#define WRITE_FAILURE	       -6       //写M1卡失败
/////////////////////// ID Error Code ////////////////////////
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


//////////////////////  M1   ///////////////////
long __stdcall Reader_Open();
long __stdcall Reader_Close(long ReaderHandle);
int __stdcall Find_M1Card(long ReaderHandle,unsigned char *uid);
long __stdcall Authentication_Pass(long ReaderHandle,unsigned char Mode, unsigned char SecNr,unsigned char *PassWord);
long __stdcall Reader_Read(long  ReaderHandle,unsigned char Addr,unsigned  char *Data);
long __stdcall Reader_Write(long ReaderHandle,unsigned char Addr,unsigned char *Data);
//////////////////////  身份证   ///////////////////
int __stdcall Reader_ReadIdCard(const char* pBmpFile, char *pName, char *pSex, char *pNation, char *pBirth, char *pAddress, char *pCertNo, char *pDepartment , char *pEffectData, char *pExpire);
#ifdef __cplusplus
}
#endif
#endif
