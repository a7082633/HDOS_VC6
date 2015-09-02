/************************************************************************/
/* 密钥ID 定义                                                                     */
/************************************************************************/
#define RK_DDF1		0
#define RK_DF01		1
#define RK_DF02		2
#define RK_DF03		3

#define STK_DDF1	4
#define STK_DF01	5
#define STK_DF02	6
#define STK_DF03	7

#define UK_DDF1		8
#define UK_DF01		9
#define UK_DF02_1		10
#define UK_DF02_2		11
#define UK_DF02_3		12
#define UK_DF03_1		13
#define UK_DF03_2		14


/************************************************************************/
/*  函数返回值常量                                                      */
/************************************************************************/
#define IRV_OK			0			//正常
#define IRV_PARA_ERR	101			//输入参数错
#define IRV_NO_FILE	    102			//文件不存在
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

//#define 

#define IRV_DEBUGERR    1024

/************************************************************************/
/* 应用常量定义                                                         */
/************************************************************************/
#define NO_style			0x00

#define AN_style			0x01
#define CN_style			0x0F
#define B_style				0xFF

#define SLOT_USER			0x01
#define SLOT_PSAM			0x11
#define SLOT_CARD			0x12	/*测试用大卡座*/


#include "Utils.h"
#include "Reader.h"

typedef struct st_itemselect_
{
	WORD	wItemFlag;				  // 数据项序号
	WORD	wID;					  // 记录文件ID
	VOID	*pValue;				  // 数据地址 
	WORD	wValueLen;				  // 数据长度
	DWORD	*pdwErrCode;	
}ITEMSELECT, *P_ITEMSELECT;	


static Reader rd ;
static Utils u;

void datatoTLV(char tag , IN char * data , OUT char* Output);
void tlvRespToOutput(int coding , IN char * resp , OUT char* Ouput);
void Padding(IN char * data);

int SelectFile(int slot , char * DFID , char * ADFID, char * EFID);

int AuthIRK(IN int KeyID , IN char * cardNo , IN char * cityCode);
int AuthUK(IN int KeyID , IN char * cardNo , IN char * cityCode);

int GetCNandCityCode(OUT char* Cn , OUT char* CityCode);
void loadCardNo(char * atr);
void loadCityCode(char * cityCode);

int UpdateBinEncMac(IN int keyID ,IN char * apduHead , IN char *LcData );
int UpdateRecEncMac(IN int keyID ,IN char * RecID,IN char* Lc, IN int datatag,  IN char *LcData );
int PSAMEncMac(IN int keyID ,IN char * divGene, IN char* apduHead , IN char *LcData , OUT char * compApdu);
int getUpdateACCbyADF(WORD itemID, char * cardno , char * citycode);


/************************************************************************/
/* wsc应用函数                                                         */
/************************************************************************/
BOOL isWorkingDFID(char * DFID);
BOOL isWorkingEFID(char * EFID);
BOOL getDFEFfromFILEMAP( IN P_ITEMSELECT item, OUT char * DFID ,OUT char * EFID);
int getReadACCbyADF(char* adfid , char * cardno , char * citycode);
int RdFileByItemStruct(P_ITEMSELECT pitem);
int UdFileByItemStruct(P_ITEMSELECT pitem);

void BinDataPadding(int coding ,char * data, int ExpLen);
void resetWorkingADF();




/************************************************************************/
/* 数据tag定义                                                          */
/************************************************************************/
#define TAG_KLB	    1  //卡类别 
#define TAG_GFBB	2  //规范版本
#define TAG_FKJGMC	3  //发卡机构名称
#define TAG_FKJGDM	4  //发卡机构代码
#define TAG_FKJGZS	5  //发卡机构证书
#define TAG_FKSJ	6  //发卡时间
#define TAG_KH      8  //卡号
#define TAG_AQM     9  //安全码
#define TAG_XPXLH	10  //发卡序列号
#define TAG_YYCSDM	57  //应用城市代码

#define TAG_KYXQ	07  //卡有效期 
#define TAG_XM		11  //姓名 
#define TAG_XB		12  //性别 
#define TAG_MZDM	13  //民族代码 
#define TAG_CSRQ	14  //出生日期 
#define TAG_JMSFZH	15  //居民身份证号码 
#define TAG_BRDH1	16  //本人电话 1 
#define TAG_BRDH2	17  //本人电话 2 
#define TAG_YLFYZF1	18  //医疗费用支付方式 
#define TAG_YLFYZF2	19  //医疗费用支付方式 
#define TAG_YLFYZF3	20  //医疗费用支付方式 
#define TAG_DZLB1	21  //地址类别 1 
#define TAG_DZ1		22  //地址 1 
#define TAG_DZLB2	23  //地址类别 2 
#define TAG_DZ2		24  //地址 2 
#define TAG_LXRXM1	25  //联系人姓名1
#define TAG_LXRGX1	26  //联系人关系1 
#define TAG_LXRDH1	27  //联系人电话1 
#define TAG_LXRXM2	28  //联系人姓名2 
#define TAG_LXRGX2	29  //联系人关系2 
#define TAG_LXRDH2	30  //联系人电话2 
#define TAG_LXRXM3	31  //联系人姓名3 
#define TAG_LXRGX3	32  //联系人关系3 
#define TAG_LXRDH3	33  //联系人电话3 
#define TAG_WHCD	34  //文化程度代码 
#define TAG_HYZK	35  //婚姻状况代码 
#define TAG_ZYDM	36  //职业代码 
#define TAG_ZJLB	37  //证件类别 
#define TAG_ZJHM	38  //证件号码 
#define TAG_JKDABH	39  //健康档案编号 
#define TAG_XNHZH	40  //新农合证（卡）号 
#define TAG_ABOXX	41  //ABO血型代码 
#define TAG_RHXX	42  //RH 血型代码 
#define TAG_XCBZ	43  //哮喘标志 
#define TAG_XZBBZ	44  //心脏病标志 
#define TAG_XNXGBBZ	45  //心脑血管病标志 
#define TAG_DXBBZ	46  //癫痫病标志 
#define TAG_NXWLBZ	47  //凝血紊乱标志 
#define TAG_TNBBZ	48  //糖尿病标志 
#define TAG_QGYBZ	49  //青光眼标志 
#define TAG_TXBZ	50  //透析标志 
#define TAG_QGYZBZ	51  //器官移植标志 
#define TAG_QGQSBZ	52  //器官缺失标志 
#define TAG_KZXYZBZ	53  //可装卸的义肢标志 
#define TAG_XZQBQBZ	54  //心脏起搏器标志 
#define TAG_QTYXJS	55  //其他医学警示名称 
#define TAG_JSBBZ	56  //精神病标志 


/*定义结构体struct 数据tcl*/
struct _DATATCL 
{
	char tag;	/*tag*/
	UINT  coding; /*编码*/
	UINT  length; /*长度*/
}static _stTCL[]={
{01,10,1},
{TAG_KLB,  AN_style,1},
{TAG_GFBB,  AN_style,4},
{TAG_FKJGMC,  AN_style,30},
{TAG_FKJGDM,  CN_style,11},
{TAG_FKJGZS,  B_style,180},
{TAG_FKSJ,  CN_style,4},/*0~6*/
{TAG_KYXQ ,  CN_style, 4},
{TAG_KH,  AN_style,18},
{TAG_AQM,  AN_style,3},
{TAG_XPXLH,  AN_style,10},/*8~10*/
{TAG_XM ,  AN_style , 30},
{TAG_XB ,  B_style , 1},
{TAG_MZDM	  ,CN_style, 1},
{TAG_CSRQ	  ,CN_style, 4},
{TAG_JMSFZH ,AN_style, 18},
{TAG_BRDH1	,AN_style, 20},
{TAG_BRDH2	,AN_style, 20},
{TAG_YLFYZF1 ,CN_style, 1},
{TAG_YLFYZF2 ,CN_style, 1},
{TAG_YLFYZF3 ,CN_style, 1},
{TAG_DZLB1	,CN_style, 1},
{TAG_DZ1	,AN_style, 100},
{TAG_DZLB2	,CN_style, 1},
{TAG_DZ2	,AN_style, 100},//地址2                        
{TAG_LXRXM1 ,AN_style, 30},
{TAG_LXRGX1 ,CN_style, 1},
{TAG_LXRDH1 ,AN_style, 20},
{TAG_LXRXM2 ,AN_style, 30},
{TAG_LXRGX2 ,CN_style, 1},
{TAG_LXRDH2 ,AN_style, 20},
{TAG_LXRXM3 ,AN_style, 30},
{TAG_LXRGX3 ,CN_style, 1},
{TAG_LXRDH3 ,AN_style, 20},
{TAG_WHCD	  ,CN_style, 1},
{TAG_HYZK	  ,CN_style, 1},
{TAG_ZYDM	  ,AN_style, 3},
{TAG_ZJLB	  ,CN_style, 1},
{TAG_ZJHM	  ,AN_style, 18},
{TAG_JKDABH ,AN_style, 17},
{TAG_XNHZH	,AN_style, 18},
{TAG_ABOXX	,B_style, 1},
{TAG_RHXX	  ,CN_style, 1},
{TAG_XCBZ	  ,B_style, 1},
{TAG_XZBBZ	,B_style, 1},
{TAG_XNXGBBZ ,B_style,1 },
{TAG_DXBBZ	,B_style, 1},
{TAG_NXWLBZ ,B_style, 1},
{TAG_TNBBZ	,B_style, 1},
{TAG_QGYBZ	,B_style, 1},
{TAG_TXBZ	  ,B_style, 1},
{TAG_QGYZBZ ,B_style, 1},
{TAG_QGQSBZ ,B_style, 1},
{TAG_KZXYZBZ ,B_style, 1},
{TAG_XZQBQBZ ,B_style, 1},
{TAG_QTYXJS ,AN_style, 40},
{TAG_JSBBZ	,B_style, 1},
{TAG_YYCSDM	,CN_style, 3}
};
