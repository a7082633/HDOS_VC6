#ifndef MHC_CARDINTERFACE_H
#define MHC_CARDINTERFACE_H

/*
#ifdef DLL_FILE
#define MHC_CARDINTERFACE_API  extern "C" __declspec(dllexport)
#else
#define MHC_CARDINTERFACE_API  extern "C" __declspec(dllimport)
#endif 
*/
#define MHC_CARDINTERFACE_API  extern "C" __declspec(dllexport)

/*
#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF

#define SLOT_USER			0x01
#define SLOT_PSAM			0x11
#define SLOT_CARD			0x12	*/

//#include "Application.h"
/*

typedef struct st_itemselect_
{
	WORD	wItemFlag;				  // 数据项序号
	WORD	wID;					  // 记录文件ID
	VOID	*pValue;				  // 数据地址 
	WORD	wValueLen;				  // 数据长度
	DWORD	*pdwErrCode;	
}ITEMSELECT, *P_ITEMSELECT;	
*/
/***********************************************************************/
/* 函数接口声明                                                        */
/************************************************************************/

//连接设备
MHC_CARDINTERFACE_API int __stdcall iDOpenPort(void);

//断开设备
MHC_CARDINTERFACE_API int __stdcall iDClosePort(void);

//上电复位
// slot = SLOT_USER(0x01) 用户卡上电
// slot = SLOT_PSAM(0x11) SAM卡上电
// ATR需要分配40+1以上的字符空间
MHC_CARDINTERFACE_API int __stdcall PowerOn(HANDLE hDev,int slot, char * ATR) ; //slot 1  User; slot 0x11 SAM1

MHC_CARDINTERFACE_API int __stdcall iVerifyPIN(HANDLE hDev,char * PIN) ;//校验PSAM卡PIN

MHC_CARDINTERFACE_API int __stdcall iChange_Pin(int hDev,char *oldPin, char *newPin);  

MHC_CARDINTERFACE_API int __stdcall iReader_SAM_Public(int hDev,
														 char* info);//该函数取得SAM卡片公共信息文件

MHC_CARDINTERFACE_API int __stdcall iReader_SAM_Terminal(int hDev,
														   char* info);//该函数取得SAM卡片的终端信息文件

MHC_CARDINTERFACE_API int __stdcall  iReader_SAM_PublicApp(int hDev,
															 char* info);//该函数取得SAM卡片的居民健康卡应用的公共信息文件

MHC_CARDINTERFACE_API int __stdcall  iReader_SAM_OrgCertificate(int hDev,
															 char* info);//该函数取得SAM卡片的居民健康卡发卡机构证书文件

MHC_CARDINTERFACE_API int __stdcall  iReader_SAM_Certificate(int hDev,
															 char* info);//该函数取得SAM卡片的SAM卡机构证书

//发卡机构基本数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF05Info(HANDLE hDev,
							  char * KLB,             //卡类别代码                                                                                        
							  char * GFBB,            //规范版本                                                                                          
							  char * FKJGMC,          //发卡机构名称                                                                                      
							  char * FKJGDM,          //发卡机构代码 
							  char * FKJGZS,			//发卡机构证书
							  char * FKSJ,            //发卡时间，YYYYMMDD格式                                                                            
							  char * KH,              //卡号，与居民身份证号或者证件号码一致
							  char * AQM,             //安全码                                                                                            
							  char * XPXLH,           //芯片序列号
							  char * YYCSDM				//应用城市代码
							  );

//发卡机构基本数据文件
MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF05Info(HANDLE hDev,
							  char * KLB,             //卡类别代码                                                                                        
							  char * GFBB,            //规范版本                                                                                          
							  char * FKJGMC,          //发卡机构名称                                                                                      
							  char * FKJGDM,          //发卡机构代码 
							  char * FKJGZS,			//发卡机构证书
							  char * FKSJ,            //发卡时间，YYYYMMDD格式                                                                            
							  char * KH,              //卡号，与居民身份证号或者证件号码一致
							  char * AQM,             //安全码                                                                                            
							  char * XPXLH,           //芯片序列号
							  char * YYCSDM				//应用城市代码
							  );

//持卡人基本信息数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF06Info(HANDLE hDev,
							  char * XM,              //姓名
							  char * XB,              //性别代码
							  char * MZ,              //民族代码
							  char * CSRQ,            //出生日期，YYYYMMDD格式
							  char * SFZH            //居民身份证号
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF06Info(HANDLE hDev,
							  char * XM,              //姓名
							  char * XB,              //性别代码
							  char * MZ,              //民族代码
							  char * CSRQ,            //出生日期，YYYYMMDD格式
							  char * SFZH            //居民身份证号
							  );
//照片
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF07Info(HANDLE hDev,
							  BYTE * ZHAOPIAN        //照片												  												  
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF07Info(HANDLE hDev,
							  BYTE * ZHAOPIAN        //照片												  												  
							  );

//EF08
MHC_CARDINTERFACE_API int __stdcall iR_DDF1EF08Info(HANDLE hDev,
							  char * KYXQ,			//卡有效期
							  char * BRDH1,           //本人电话1
							  char * BRDH2,           //本人电话2
							  char * YLFYZFFS1,		  //医疗费用支付方式1
							  char * YLFYZFFS2,		  //医疗费用支付方式2
							  char * YLFYZFFS3		  //医疗费用支付方式3		
							  );

//EF08
MHC_CARDINTERFACE_API int __stdcall iW_DDF1EF08Info(HANDLE hDev,
							  char * KYXQ,			//卡有效期
							  char * BRDH1,           //本人电话1
							  char * BRDH2,           //本人电话2
							  char * YLFYZFFS1,		  //医疗费用支付方式1
							  char * YLFYZFFS2,		  //医疗费用支付方式2
							  char * YLFYZFFS3		  //医疗费用支付方式3		
							  );


//地址信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF05Info(HANDLE hDev,
							  char * DZLB1,             //地址类别1
							  char * DZ1,				//地址1
							  char * DZLB2,             //地址类别2
							  char * DZ2				//地址2
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF05Info(HANDLE hDev,
							  char * DZLB1,             //地址类别1
							  char * DZ1,				//地址1
							  char * DZLB2,             //地址类别2
							  char * DZ2				//地址2
							  );
//联系人信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF06Info(HANDLE hDev,
							  char * LXRXM1,          //联系人姓名1                                                                                       
							  char * LXRGX1,          //联系人关系代码1                                                                                   
							  char * LXRDH1,          //联系人电话1                                                                                       
							  char * LXRXM2,          //联系人姓名2                                                                                       
							  char * LXRGX2,          //联系人关系代码2                                                                                   
							  char * LXRDH2,          //联系人电话2                                                                                       
							  char * LXRXM3,          //联系人姓名3                                                                                       
							  char * LXRGX3,          //联系人关系代码3                                                                                   
							  char * LXRDH3			  //联系人电话3
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF06Info(HANDLE hDev,
							  char * LXRXM1,          //联系人姓名1                                                                                       
							  char * LXRGX1,          //联系人关系代码1                                                                                   
							  char * LXRDH1,          //联系人电话1                                                                                       
							  char * LXRXM2,          //联系人姓名2                                                                                       
							  char * LXRGX2,          //联系人关系代码2                                                                                   
							  char * LXRDH2,          //联系人电话2                                                                                       
							  char * LXRXM3,          //联系人姓名3                                                                                       
							  char * LXRGX3,          //联系人关系代码3                                                                                   
							  char * LXRDH3			  //联系人电话3
							  
							  );
//职业婚姻信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF07Info(HANDLE hDev,
							  char * WHCD,          //文化程度代码
							  char * HYZK,			//婚姻状况代码
							  char * ZY             //职业代码
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF07Info(HANDLE hDev,
							  char * WHCD,          //文化程度代码
							  char * HYZK,			//婚姻状况代码
							  char * ZY             //职业代码
							  );
//证件记录信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF01EF08Info(HANDLE hDev,
							  char * ZJLB,            //证件类别代码，决定身份证号和证件号码哪一项必填
							  char * ZJHM,            //证件号码
							  char * JKDAH,           //健康档案号
							  char * XNHZH            //新农合证号
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DF01EF08Info(HANDLE hDev,
							  char * ZJLB,            //证件类别代码，决定身份证号和证件号码哪一项必填
							  char * ZJHM,            //证件号码
							  char * JKDAH,           //健康档案号
							  char * XNHZH            //新农合证号
							  );
//临床基本数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF05Info(HANDLE hDev,
							  char * ABOXX,           //ABO血型代码
							  char * RHXX,            //RH血型代码
							  char * XCBZ,            //哮喘标志
							  char * XZBBZ,           //心脏病标志
							  char * XNXGBBZ,         //心脑血管病标志
							  char * DXBBZ,           //癫痫病标志
							  char * NXWLBZ,          //凝血紊乱标志
							  char * TNBBZ,           //糖尿病标志
							  char * QGYBZ,           //青光眼标志
							  char * TXBZ,            //透析标志
							  char * QGYZBZ,          //器官移植标志
							  char * QGQSBZ,          //器官缺失标志
							  char * KZXYZBZ,         //可装卸义肢标志
							  char * XZQBQBZ,         //心脏起搏器标志
							  char * QTYXJSMC         //其他医学警示名称
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DF02EF05Info(HANDLE hDev,
							  char * ABOXX,           //ABO血型代码
							  char * RHXX,            //RH血型代码
							  char * XCBZ,            //哮喘标志
							  char * XZBBZ,           //心脏病标志
							  char * XNXGBBZ,         //心脑血管病标志
							  char * DXBBZ,           //癫痫病标志
							  char * NXWLBZ,          //凝血紊乱标志
							  char * TNBBZ,           //糖尿病标志
							  char * QGYBZ,           //青光眼标志
							  char * TXBZ,            //透析标志
							  char * QGYZBZ,          //器官移植标志
							  char * QGQSBZ,          //器官缺失标志
							  char * KZXYZBZ,         //可装卸义肢标志
							  char * XZQBQBZ,         //心脏起搏器标志
							  char * QTYXJSMC        //其他医学警示名称
							  );
//特殊信息数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF06Info(HANDLE hDev,
							  char * JSBBZ           //精神病标志
							  );


MHC_CARDINTERFACE_API int __stdcall iW_DF02EF06Info(HANDLE hDev,
							  char * JSBBZ           //精神病标志
							  );



//过敏基本数据文件
//nRecorderNo 记录号
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF07Info(HANDLE hDev, int nRecorderNo, char* GMWZMC, char* GMFY);

//由于是循环记录，新写入的数据永远是第一条数据
MHC_CARDINTERFACE_API int __stdcall iW_DF02EF07Info(HANDLE hDev,
							  char * GMWZMC,        //过敏物质名称
							  char * GMFY			//过敏物质反应
							  );
//免疫基本数据文件
MHC_CARDINTERFACE_API int __stdcall iR_DF02EF08Info(HANDLE hDev, int nRecorderNo, char* MYJZMC, char* MYJZSJ);
MHC_CARDINTERFACE_API int __stdcall iW_DF02EF08Info(HANDLE hDev,
							  char* MYJZMC,//免疫接种名称 
							  char* MYJZSJ //免疫接种时间
							  );

//住院信息索引文件
MHC_CARDINTERFACE_API int __stdcall iR_DF03EF05Info(HANDLE hDev,
							  char * ZYJLBS1,             //住院记录有效标志
							  char * ZYJLBS2,
							  char * ZYJLBS3
							  );
//将住院有效标识更改为0x00
MHC_CARDINTERFACE_API int __stdcall iW_DF03EF05Info(HANDLE hDev,
							  int nRecorderNo
							  );

//将住院有效标识更改为0xff
MHC_CARDINTERFACE_API int __stdcall iErase_DF03EF05Info(HANDLE hDev,
								  int nRecorderNo
								  );


//门诊信息索引文件
MHC_CARDINTERFACE_API int __stdcall iR_DF03EF06Info(HANDLE hDev,
							  char * MZJLBS1, //门诊记录有效标识
							  char * MZJLBS2,
							  char * MZJLBS3,
							  char * MZJLBS4,
							  char * MZJLBS5
							  );
//写0x00
MHC_CARDINTERFACE_API int __stdcall iW_DF03EF06Info(HANDLE hDev,
							  int nRecorderNo
							  );
//写0xff
MHC_CARDINTERFACE_API int __stdcall iErase_DF03EF06Info(HANDLE hDev,
								  int nRecorderNo
								  );


//住院信息文件

//1. nStyle可以取以下4个值。

// #define NO_style			0x00
// 
// #define AN_style			0x01
// #define CN_style			0x0F
// #define B_style			0xFF

//2.如果全读全写，比如读写整个EE01的数据，那么 nStyle=NO_style, pos=0, Len=1639(不需要操作EEXX文件的最后2项)
//	文件最后2项为“签名”操作时才写入的数据。

//3.如果读写具体数据项，pos\len\style的取值请参考相关文档。

//4.pos\len取值的单位是卡内部存储空间的字节的大小

//5.如果卡内存储数据的类型是CN_style和B_style， szData的size需要大于(卡内存储空间的2倍+1)


MHC_CARDINTERFACE_API int __stdcall iR_DF03EEInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  );

MHC_CARDINTERFACE_API int __stdcall iR_DF03EE_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData											  
							  );//全读

MHC_CARDINTERFACE_API int __stdcall iW_DF03EEInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DF03EE_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData										  
							  );//全写


//门诊信息文件
MHC_CARDINTERFACE_API int __stdcall iR_DF03EDInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  );

MHC_CARDINTERFACE_API int __stdcall iR_DF03ED_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData											  
							  );//全读

MHC_CARDINTERFACE_API int __stdcall iW_DF03EDInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData,											  
							  int	 nPos,
							  int	 nLen,
							  int	 nStyle
							  );

MHC_CARDINTERFACE_API int __stdcall iW_DF03ED_ALLInfo(HANDLE hDev,
							  int	 nRecorderNo,
							  char * szData										  
							  );//全写


//按数据项序号读数据
MHC_CARDINTERFACE_API DWORD __stdcall wsc_GetCardInfo(HANDLE hCard,void *pvSelect,int nItem);
//按数据项序号写数据
MHC_CARDINTERFACE_API DWORD __stdcall wsc_PutCardInfo(HANDLE hCard,void *pvSelect,int nItem);

MHC_CARDINTERFACE_API HANDLE __stdcall OpenDevice(int port);

MHC_CARDINTERFACE_API DWORD __stdcall	CloseDevice(HANDLE hCard);

MHC_CARDINTERFACE_API DWORD  __stdcall SendAPDU (
				HANDLE hDev,
				unsigned char bySlot,
				unsigned char * pbyC_Command,
				unsigned long byLen,
				unsigned char * pbyR_Command,
				int * pnRes );

/*
函数：wsc_SM3Digest
功能：对输入数据进行SM3哈希运算
	参数说明：
	hCard		: [in] 设备句柄
	pbData		: [in] 待哈希数据
	nDataLen	: [in] 待哈希数据长度
	pbHash		: [out]哈希结果
	pbHashLen	: [out]指向哈希结果长度的指针
	返回值：如果成功，返回0，失败返回相应的错误码。
*/
MHC_CARDINTERFACE_API DWORD __stdcall SM3Digest(HANDLE hCard, BYTE *pbData, unsigned int nDataLen,  BYTE *pbHash, BYTE *pbHashLen);


/*
函数:wsc_SM2SignHash
功能：对输入数据进行SM2签名运算
	参数说明：
	hCard		: [in] 设备句柄
	pbData		: [in] 待签名数据，原始数据的哈希结果
	bLen		: [in] 待签名哈希数据长度
	pbSignedData: [out]签名结果
	pbLength	: [out]指向哈希结果长度的指针
	返回值：如果成功，返回0，失败返回相应的错误码。

说明：在执行签名前，需要wsc_VerifyPin验证PIN获取相应的权限
*/
DWORD __stdcall SM2SignHash(HANDLE hCard,
								BYTE *pbData,
								BYTE bLen,
								BYTE *pbSignedData,
								BYTE *pbLength);


#endif