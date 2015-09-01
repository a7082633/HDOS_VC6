// HD_RWHealInterface.h : main header file for the HD_RWHEALINTERFACE DLL
//
#if !defined(AFX_HD_RWHEALINTERFACE_H__ECF36EDA_9730_46D9_8146_0BEF432004DC__INCLUDED_)
#define AFX_HD_RWHEALINTERFACE_H__ECF36EDA_9730_46D9_8146_0BEF432004DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

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
#define PROCCESS_EXIST  119      //未打开卡管中心
#define HTTP_EXCEPTION1 1001	//缺少账号或为空
#define HTTP_EXCEPTION2 1002	//缺少密码或为空
#define HTTP_EXCEPTION3 1003	//身份验证失败
#define HTTP_EXCEPTION4 2001	//缺少健康卡序列号
#define HTTP_EXCEPTION5 2002	//安全验证查询参数错误或非法参数
#define HTTP_EXCEPTION6 2003	//卡已经挂失
#define HTTP_EXCEPTION7 2004	//卡已经注销
#define HTTP_EXCEPTION8 3001	//卡不存在
#define HTTP_EXCEPTION9 3002	//个人身份识别查询参数错误或非法参数
#define HTTP_EXCEPTIONA 4001	//缺少SAM卡号
#define HTTP_EXCEPTIONB 4002	//SAM卡号已冻结
#define HTTP_EXCEPTIONC 4003	//SAM卡号已注销
#define HTTP_EXCEPTIOND 4004	//SAM卡号已挂失
#define HTTP_EXCEPTIONE 4005	//SAM卡不存在
#define HTTP_EXCEPTIONF 5001	//没有可以修改的内容
#define HTTP_EXCEPTIONG 5002	//目标格式不正确
#define HTTP_EXCEPTIONH 6001	//缺少机具号
#define HTTP_EXCEPTIONI 6002	//机具已冻结
#define HTTP_EXCEPTIONJ 6003	//机具已注销
#define HTTP_EXCEPTIONK 6004	//机具已挂失
#define HTTP_EXCEPTIONL 6005	//机具不存在
#define HTTP_EXCEPTIONM 7001	//机具与SAM卡不匹配

#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF

#define SLOT_USER			0x01
#define SLOT_PSAM			0x11
#define SLOT_CARD			0x12	
MHC_CARDINTERFACE_API int __stdcall IChange_Pin(int hDev,char *oldPin,char *newPin); //修改PIN
MHC_CARDINTERFACE_API int __stdcall IR_ReadCard(char *para,char *dataOut,char *account,char *password,int doctype,char *userid,char *pin);
MHC_CARDINTERFACE_API int __stdcall IR_WriteCard(char *para,char *dataIn,char *account,char *password,int doctype,char *userid,char *pin);

#endif // !defined(AFX_HD_RWHEALINTERFACE_H__ECF36EDA_9730_46D9_8146_0BEF432004DC__INCLUDED_)
