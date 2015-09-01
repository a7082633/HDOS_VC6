#ifndef HD_CARDINTERFACE_H
#define MHC_CARDINTERFACE_H

#define MHC_CARDINTERFACE_API  extern "C" __declspec(dllexport)

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
#define IRV_OK			0			//正常
#define IRV_PARA_ERR	101			//输入参数错
#define IRV_NO_FILE		102			//文件不存在
#define IRV_RD_RCDERR	103			//读记录失败
#define IRV_CARD_ERR	104			//卡片响应异常
#define IRV_PSAM_ERR	105			//PSAM卡片响应异常
#define IRV_IRK_VERR	106			//内部认证失败
#define IRV_RD_BINERR	107			//读BIN失败
#define IRV_WR_RCDERR	108			//写记录失败
#define IRV_WR_BINERR	109			//写BIN失败
#define IRV_W_DF03EF05ERR	110			//写DF03EF05失败
#define IRV_ER_DF03EF05ERR	111			//擦除DF03EF05失败
#define IRV_RCINVALID	112			//记录不可用(ef 有效标记为 ff)
#define IRV_DDF1EF07_DATAERR	113			//照片文件数据异常
#define PARA_COVERT_ERR	114			//无法将参数转换成整形
#define GETCARD_INFO_ERR	115      // wsc_GetCardInfo出错
#define OPEN_FILE_ERR	116      // 打开照片文件流出错
#define CANT_FINDWEB	117      // 找不到主页
#define HTTP_EXCEPTION	118      // http异常
#define AUTHENTICATION_FAILURE	119      // 认证失败
#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF

#define SLOT_USER			0x01
#define SLOT_PSAM			0x11
#define SLOT_CARD			0x12	
MHC_CARDINTERFACE_API int __stdcall IDOpenPort(char *account,char *password);//连接设备
MHC_CARDINTERFACE_API int __stdcall IDClosePort(void);//关闭设备
//上电复位
// slot = SLOT_USER(0x01) 用户卡上电
// slot = SLOT_PSAM(0x11) SAM卡上电
// ATR需要分配40+1以上的字符空间
MHC_CARDINTERFACE_API int __stdcall IPowerOn(HANDLE hDev,int slot, 
											 char * ATR,char *account,
											 char *password,int doctype,
											 char *para,char *userid); //slot 1  User; slot 0x11 SAM1
MHC_CARDINTERFACE_API int __stdcall IVerifyPIN(HANDLE hDev,char * PIN) ;//校验PSAM卡PIN
MHC_CARDINTERFACE_API int __stdcall IChange_Pin(int hDev,char *oldPin,char *newPin); //修改PIN
MHC_CARDINTERFACE_API int __stdcall IR_ReadCard(char *para,char *dataOut);
MHC_CARDINTERFACE_API int __stdcall IR_WriteCard(char *para,char *dataIn);



#endif