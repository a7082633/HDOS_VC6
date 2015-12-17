#ifndef BHGX_HD_H
#define BHGX_HD_H

#define BHGX_HD_API extern "C" __declspec(dllexport)

#define WS_OK						  0 //	成功
#define WS_ERR_UserCancle	    	 -1 //	用户取消操作
#define WS_ERR_PHOTOFILELarge		 -2 //	照片文件过大!(最大支持 3K 大小的照片)
#define WS_ERR_Empty	        	 -3//	数据无效(为空)
#define WS_ERR_KBCONNECT	    	 -4 //	密码键盘连接异常
#define WS_ERR_FileNoErr	    	 -5 //	记录标识无效
#define WS_ERR_DataLenErr	    	 -6 //	输入数据长度无效
#define WS_ERR_PINERR	        	 -7 //	PIN 码验证失败
#define WS_ERR_ItemTAG	        	 -8 //	传入 TAG 标识无效
#define WS_ERR_ItemNo	        	 -9 //	传入记录号无效
#define WS_ERR_UnAllowWrite	    	-10 //	该数据不允许写入
#define WS_ERR_UNSUPPORTED	    	-11 //	功能不支持
#define WS_ERR_RCertInfos	    	-12 //	读取身份证异常[请放卡重试!]
#define WS_ERR_CreatePhotoFile		-13 //	生成身份证持卡人照片文件失败
#define WS_ERR_DEVICEUNINIT	    	-14 //	设备未初始化或已关闭
#define WS_ERR_DataStyleCheckErr	-15 //	传入数据格式无效
#define WS_ERR_UNKNOWN	        	-16 //	未知错误
#define WS_ERR_RLength	        	-17 //	入参中数据长度标识无效
#define WS_ERR_ROffSET	        	-18 //	入参中读取偏移量标识无效

#define	WS_ERR_RDataStyle			-19 //入参中数据类型标识无效
#define	WS_ERR_CARDMISS				-20 //无卡
#define	WS_ERR_NORESPONSE_CPU		-21 //用户卡无响应[请重试]
#define	WS_ERR_NORESPONSE_SAM		-22 //PSAM 卡无响应[请重试]
#define	WS_ERR_RESET_SAM			-23 //PSAM 卡复位异常[卡插卡或没插卡或卡型无效]
#define	WS_ERR_RESET_CPU			-24 //未寻到卡,[没放卡或卡型无效],请重试!
#define	WS_ERR_SETSLOTID			-25 //设置卡座异常
#define	WS_ERR_DataItemsErr			-26 //数据项个数与规范不符
#define	WS_ERR_InputPassOutTime		-27 //密码输入超时,请重试!
#define	WS_ERR_GetPassCancel		-28 //用户取消密码输入
#define	WS_ERR_TLVLenthErr			-29 //TLV 数据中 Length 无效
#define	WS_ERR_PORTPARAMETER		-30 //端口参数无效
#define	WS_ERR_GETDEVICEVER			-31 //设备版本信息读取异常
#define	WS_ERR_DEVICEVer			-32 //版本号无效(非法设备)
#define	WS_ERR_DEVICECONNECT		-33 //设备连接异常
#define	WS_ERR_UNSLOTID				-34 //卡座参数无效
#define	WS_ERR_APDUDataLenErr		-35 //APDU 数据长度无效
#define WS_ERR_DEVICESNR			-36 //设备序列号读取或校验异常
#define	WS_ERR_CARDTYPE				-37 //无卡
#define WS_ERR_IC					-99 //卡片级别应答错误
#define WS_ERR_OTHER			    -999 //其他异常错误

BHGX_HD_API BOOL __stdcall bProbe(void);
BHGX_HD_API int __stdcall iOpen(void);
BHGX_HD_API int __stdcall iClose(void);
BHGX_HD_API int __stdcall iReadBin(unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, int iSizeInBytes, int iOffsetInBytes);
BHGX_HD_API int __stdcall iWriteBin(unsigned char iCardType, unsigned char *pKey, const unsigned char *pBuf, int nCtrlword, int iSizeInBytes, int iOffsetInBytes);
BHGX_HD_API int __stdcall iReadRec(unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, unsigned long buflen, int  iRecNo, int  iRecCount);
BHGX_HD_API int __stdcall iWriteRec(unsigned char iCardType, unsigned char *pKey, unsigned char *pBuf, unsigned long buflen, int  iRecNo, int  iRecCount);
BHGX_HD_API int __stdcall iAppendRec(unsigned char *pKey, const unsigned char *pBuf, unsigned long buflen);
BHGX_HD_API int __stdcall iSignRec(unsigned char *pKey, int  iRecNo, int  sign);
BHGX_HD_API int __stdcall iIOCtl(int cmd, void *data, int datasize);
BHGX_HD_API int __stdcall ICCSet(unsigned int  iCardSet, unsigned char *pCardType, unsigned char *pRet);
BHGX_HD_API int __stdcall iUCardAuthSys(int  iKeyID);
BHGX_HD_API int __stdcall iSelectFile(unsigned char  iCardType, unsigned char  *pInFID);
BHGX_HD_API int __stdcall iGetRandom(unsigned char  iCardType, unsigned char  iRndLen, unsigned char  * pOutRnd);
BHGX_HD_API int __stdcall iChangePwdEx(const unsigned char * pNewKeyA, const unsigned char * ctrlword,	const unsigned char * pNewKeyB, const unsigned char * poldPin,  unsigned char nsector, unsigned char keyA1B0, unsigned char changeflag);

#endif


