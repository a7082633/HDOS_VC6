#include "stdafx.h"
//#include "Application.h"
#include "staticDefine.h"
#include "FileMap.h"
#include <time.h>
#define DEBUG_LOG( str ) log_append_to_file("test.txt", str,__FILE__,__LINE__ )
//二进制数据补足长度
void BinDataPadding(int coding ,char * data, int ExpLen)
{
	int l = strlen(data);
	int i;
	switch (coding)
	{
	case AN_style:
	case B_style:
		if (l < ExpLen * 2)
		{
			for(i = 0 ;i < (ExpLen * 2 - l ) ;i++)
				strcat(data , "0");
		}
		break;
	case CN_style:
		if (l < ExpLen * 2)
		{
			for(i = 0 ;i < (ExpLen * 2 - l ) ;i++)
				strcat(data , "F");
		}

		break;
	}
}

int UdFileByItemStruct(P_ITEMSELECT pitem)
{
	char apdu[500];
	char resp[256];
	char data[256];
	char sw[5];
	int ret ;

	//判断文件长度
	if ( (*pitem).wValueLen < _stDataFileMAP[(*pitem).wItemFlag].iDataLen )
	{
		//*(*pitem).pdwErrCode = IRV_PARA_ERR;
		return IRV_PARA_ERR;
	}

	getDFEFfromFILEMAP(pitem , apdu , resp);
	int stkid ;
	if (strcmp(apdu , "DDF1") == 0)
		stkid = STK_DDF1;
	else if (strcmp(apdu , "DF01") == 0)
		stkid = STK_DF01;
	else if (strcmp(apdu , "DF02") == 0)
		stkid = STK_DF02;
	else if (strcmp(apdu , "DF03") == 0)
		stkid = STK_DF03;
	
	//区分文件类型
	if (_stDataFileMAP[pitem->wItemFlag].cFiletype == FILE_REC)
	{
		// 记录号
		memset (apdu , 0 ,sizeof(apdu));
		u.intTo1ByteHex( _stRECmap[pitem->wItemFlag].recid, apdu);
		//计算数据长度
		int lenExp = _stDataFileMAP[pitem->wItemFlag].iDataLen + 16 + 2;
		
		lenExp = lenExp - (lenExp % 16) + 4;

		memset (resp , 0 ,sizeof(resp));
		u.intTo1ByteHex( lenExp, resp);
		ret = UpdateRecEncMac(stkid , apdu , resp , pitem->wItemFlag, (char*)pitem->pValue );

		//*(pitem->pdwErrCode) = ret;
		return ret;

	}
	else if (_stDataFileMAP[pitem->wItemFlag].cFiletype == FILE_BIN)
	{	
		//准备数据
		switch (_stDataFileMAP[pitem->wItemFlag].cCoding)
		{
		case CN_style:
		case B_style:
			strcpy( data , (char*)pitem->pValue );
			break;
		case AN_style:
			u.BinToHexstr((unsigned char*)data ,  (unsigned char*)pitem->pValue ,  strlen((char*)pitem->pValue));
			break;
		}
		BinDataPadding(_stDataFileMAP[pitem->wItemFlag].cCoding , data , _stDataFileMAP[pitem->wItemFlag].iDataLen);
		//apdu head
		memcpy (resp, "\x00\xd6\x00\x00\x80" , 5);
		//偏移地址 BINmap 有64个偏移
		u.UINTToBin(_stBINmap[pitem->wItemFlag - 64].ioffset , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		u.intTo1ByteHex(_stDataFileMAP[pitem->wItemFlag].iDataLen , apdu + 8);
		apdu[10] = 0;
		
		strcat (apdu , data);
		ret = rd.RF_Send (apdu , resp , sw);
		//*(pitem->pdwErrCode) = ret;
		return ret;		
	}
	else if (_stDataFileMAP[pitem->wItemFlag].cFiletype == FILE_REC_NORM)
	{
		//准备数据
		switch (_stDataFileMAP[pitem->wItemFlag].cCoding)
		{
		case CN_style:
		case B_style:
			strcpy( data , (char*)pitem->pValue );
			break;
		case AN_style:
			u.BinToHexstr((unsigned char*)data ,  (unsigned char*)pitem->pValue ,  strlen((char*)pitem->pValue));
			break;
		}
		BinDataPadding(_stDataFileMAP[pitem->wItemFlag].cCoding , data , _stDataFileMAP[pitem->wItemFlag].iDataLen);
		//apdu head
		memcpy (resp, "\x04\xdc\x00\x04\x80" , 5);
		resp[2] = (char)pitem->wID;
		resp[4] = (char)(_stDataFileMAP[pitem->wItemFlag].iDataLen + 16);
		resp[4] = resp[4] - (resp[4] % 16) + 4;
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		ret = UpdateBinEncMac(stkid ,apdu , data );
		//*(pitem->pdwErrCode) = ret;
		return ret;
	}
	else if (_stDataFileMAP[pitem->wItemFlag].cFiletype == FILE_CYREC)
	{
		//组织apdu 
		//to continue...		
	}
	return IRV_OK;
}


int RdFileByItemStruct(P_ITEMSELECT pitem)
{
	char apdu[100];
	char resp[512];
	char sw[5];
	int ret ;
	//判断文件长度
	if ( (*pitem).wValueLen < _stDataFileMAP[(*pitem).wItemFlag].iDataLen )
	{
		//*(*pitem).pdwErrCode = IRV_PARA_ERR;
		return IRV_PARA_ERR;
	}
	//区分文件类型
	switch (_stDataFileMAP[pitem->wItemFlag].cFiletype)
	{
	case FILE_REC:
		//组织apdu
		strcpy(apdu , "00b2000400");		
		u.intTo1ByteHex(_stRECmap[pitem->wItemFlag].recid , apdu + 4);
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			//*(pitem->pdwErrCode) = ret;
			return ret;
		}
		else
		{
			tlvRespToOutput(_stDataFileMAP[pitem->wItemFlag].cCoding, resp, (char *)pitem->pValue );
			//*(pitem->pdwErrCode) = ret;
			return ret;
		}
		break;
	case FILE_BIN:
		//组织apdu
		memcpy (resp, "\x00\xb0\x00\x00\x00" , 5);
		//偏移地址 BINmap 有64个偏移
		u.UINTToBin(_stBINmap[pitem->wItemFlag - 64].ioffset , resp + 2);
		u.BinToHexstr((unsigned char *)apdu , (unsigned char *)resp , 5);
		u.intTo1ByteHex(_stDataFileMAP[pitem->wItemFlag].iDataLen , apdu + 8);
		apdu[10] = 0;
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			//*(pitem->pdwErrCode) = IRV_RD_BINERR;
			return IRV_RD_BINERR;
		}
		//代码转换输出
		//数据输出
		switch (_stDataFileMAP[pitem->wItemFlag].cCoding)
		{
		case CN_style:
		case B_style:
			strcpy((char *)pitem->pValue ,resp);
			break;
		case AN_style:
			u.HexstrToBin ((unsigned char*)pitem->pValue , (unsigned char*)resp , strlen(resp));
			break;
		}
		//*(pitem->pdwErrCode) = ret;
		return ret;
		break;
	case FILE_CYREC:
		//组织apdu 
		//to continue...
		break;
	case FILE_REC_NORM://普通记录文件
		strcpy(apdu , "00b2000400");		
		u.intTo1ByteHex(pitem->wID, apdu + 4);
		ret = rd.RF_Send (apdu , resp , sw);
		if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		{
			//*(pitem->pdwErrCode) = ret;
			return ret;
		}
		else
		{
			switch (_stDataFileMAP[pitem->wItemFlag].cCoding)
			{
			case CN_style:
			case B_style:
				strcpy((char *)pitem->pValue ,resp);
				break;
			case AN_style:
				u.HexstrToBin ((unsigned char*)pitem->pValue , (unsigned char*)resp , strlen(resp));
				break;
			}
			//*(pitem->pdwErrCode) = ret;
			return ret;
		}
		break;
	}	
	return IRV_OK;
}


int getUpdateACCbyADF(WORD itemID, char * cardno , char * citycode)
{
	int ukid = _stDataFileMAP[itemID].cUpdateAcc;

	int ret = AuthUK(ukid , cardno , citycode);
	return ret;
}

//根据ADF文件的名称 获取响应的读权限
int getReadACCbyADF(char* adfid , char * cardno , char * citycode)
{
	int keyid = 0;
	if (strcmp(adfid ,"DDF1") == 0)
	{
		keyid = RK_DDF1;
	}
	else if (strcmp(adfid ,"DF01") == 0)
	{
		keyid = RK_DF01;
	}
	else if(strcmp(adfid ,"DF02") == 0)
	{
		keyid = RK_DF02;
	}
	else if (strcmp(adfid ,"DF03") == 0)
	{
		keyid = RK_DF03;
	}
	else
		return IRV_PARA_ERR;

	int ret = AuthIRK(keyid , cardno , citycode);
	return ret;
}

//从文件map中提取文件的目录和文件ID
BOOL getDFEFfromFILEMAP( IN P_ITEMSELECT item, OUT char * DFID ,OUT char * EFID)
{
	if ((item->wItemFlag < 1) ||(item->wItemFlag > MAX_FILEMAP))
		return false;
	
	u.BinToHexstr((unsigned char *)DFID , (unsigned char *)_stDataFileMAP[item->wItemFlag].ADFID,2);
	u.BinToHexstr((unsigned char *)EFID , (unsigned char *)_stDataFileMAP[item->wItemFlag].FileID,2);
	//对二进制文件的文件ID 进行特殊处理
	if (_stDataFileMAP[item->wItemFlag].cFiletype == FILE_BIN) 
	{
		//记录文件ID = Fileid 低字节
		u.intTo1ByteHex( (int)item->wID  , EFID + 2);
	}
	return true;
}

void resetWorkingADF()
{
	strcpy(_WorkingADF , "");
}

//判断用户输入的EFID是否是当前正在使用的EF
BOOL isWorkingEFID(char * EFID)
{
	if (strcmp(EFID , _pWorkingEF) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//判断用户输入的DFID是否是当前正在使用的DF
BOOL isWorkingDFID(char * DFID)
{
	if (strcmp(DFID , _pWorkingADF) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//将卡片中 ATR 数据加载到全局变量
void loadCardNo(char * atr)
{
	memset(_cardNo , 0, sizeof(_cardNo));
	int count=strlen(atr);
	//取分散因子后8字节
	//memcpy(_cardNo , atr + count - 16 , 16 );
	//取分散因子中8字节
	memcpy(_cardNo , atr + 10 , 16 );
}

//将卡片中 数据加载到全局变量
void loadCityCode(char * cityCode)
{
	memset(_cityCode , 0, sizeof(_cityCode));
	u.BinToHexstr((unsigned char *)_cityCode , (unsigned char *)cityCode, 2 );
	strcat(_cityCode , "303030303030");
}


//目前是假函数，待修改!!!!!!
//获取用户卡卡号信息以及CityCode，用于PSAM发散
int GetCNandCityCode(OUT char* Cn , OUT char* CityCode)
{
	//取得全局的卡号数据
	strcpy(Cn , _pcardNo);
	//取得城市代码
	strcpy(CityCode , _pcityCode);
	//strcpy(CityCode , "3431303030303030");
	return IRV_OK;
}


void datatoTLV(char tag , IN char * data , OUT char* Output)
{
	int l = _stTCL[tag].length * 2 + 4; //t + l + v
	UINT i;
	char * tmp = (char *)malloc((l + 1)*sizeof(char));
	memset(tmp  , 0 , sizeof (tmp));

	tmp[0] = tag;
	tmp[1] = (char)_stTCL[tag].length;

	switch(_stTCL[tag].coding)
	{
	case AN_style:
		strcpy(tmp + 2 , data);
		u.BinToHexstr((unsigned char *)Output , (unsigned char *)tmp , _stTCL[tag].length + 2);
		break;
	case CN_style:
		u.BinToHexstr((unsigned char *)Output , (unsigned char *)tmp ,2);

		if (strlen(data) < _stTCL[tag].length * 2)
		{
			strcat(Output , data);
			for(i = 0 ;i < (_stTCL[tag].length * 2 - strlen(data) ) ;i++)
				strcat(Output , "F");
		}	
		else
		{
			strcat(Output , data);
		}
		break;
	case B_style:
		u.BinToHexstr((unsigned char *)Output , (unsigned char *)tmp ,2);
		strcat(Output , data);
		break;
	}
	free (tmp);
}

//将卡片的TLV返回数据转换为 接口输出格式
//Coding 为输出编码方式;  
//ascII AN_style			0x01 asc编码
//CN_style					0x0F 压缩数字
//Binary B_style			0xFF 二进制
void tlvRespToOutput(int coding , IN char * resp , OUT char* Ouput)
{
	char out[20]={0};
	char *ptmp;
	int len = strlen(resp) ;
	UINT i;
	
	ptmp = (char *)malloc((len)*sizeof( char));
	memset(ptmp , 0 , sizeof(ptmp));

	switch (coding)
	{
	case AN_style:
		u.HexstrToBin((unsigned char *)ptmp ,(unsigned char *)resp + 4,  len - 4);
		ptmp[(len - 4) /2] = 0;
		break;
	case CN_style: //  CN 编码方式 左对齐，右补“F”
		strcpy(ptmp ,resp + 4);
		for ( i = 0 ; i < strlen(ptmp) ;i++)
		{
			if (ptmp[i] == 'F')
			{
				ptmp[i] = 0;break;
			}
		}
		break;
	case B_style:
		strcpy( ptmp , resp + 4);
		break;
	}
	strcpy(Ouput,ptmp);	
	free(ptmp);

	return ;
}



void XorStr(IN char *p1 , IN char* p2, OUT char * pout)
{
	int l = strlen(p1);

	char tmp[100];
	char tmp1[100];
	u.HexstrToBin((unsigned char *)tmp , (unsigned char *)p1 , l);
	u.HexstrToBin((unsigned char *)tmp1, (unsigned char *)p2 , l);
	for (int i = 0; i < l/2 ;i++)
		tmp[i] = tmp[i]^tmp1[i];
	
	u.BinToHexstr((unsigned char *)pout ,(unsigned char *) tmp , l/2);
}


//在原数据后面自动添加0x8000000...数据至16字节整数倍
//上层函数需要保证补充字节后不会溢出
void Padding(IN char * data)
{
	int l = strlen(data) / 2;
	char padding[33] = {"80000000000000000000000000000000"};

	padding[ (16 - l % 16) *2]  = 0;
	strcat (data, padding);
}

//为PSAM 加密计算准备数据输入原始数据，增加长度字节以及补充字节
void makeLVwithPadding(IN char * data , OUT char * outdata)
{
	int l = strlen(data) / 2;
	char len[3] = { 0 ,0, 0};
	//len
	u.UINTToBin(l, len);
	u.BinToHexstr((unsigned char*)outdata, (unsigned char *)len + 1 ,1);
	outdata[2] = 0;
	//v
	strcat(outdata, data);
	//padding
	Padding(outdata);
}


//通过DFID， EFID 选择文件
int SelectFile(int slot , char * DFID , char * ADFID, char * EFID)
{
	int ret ;
	char apdu[100];
	char resp[256];
	char sw[5];
	//选择DF目录
	if ((DFID != NULL) && (strlen(DFID) != 0))
	{
		strcpy((char *)apdu , "00A4000002");
		strcat((char *)apdu  , DFID );
		if (slot == SLOT_USER)
		{
			ret = rd.RF_Send(apdu , resp , sw);
			if (ret != IRV_OK)
				return ret;
			strcpy(_pWorkingADF , DFID);
		}
		else
		{
			ret = rd.PSAM_Send(apdu , resp , sw);
			if (ret != IRV_OK)
				return ret;
		}
		if ((strcmp((char *)sw , "9000") != 0 ) && (memcmp(sw , "\x36\x31",2) != 0))
		{
			return IRV_NO_FILE;
		}		
	}
	//选择DF目录
	if ((ADFID != NULL) && (strlen(ADFID) != 0))
	{
		strcpy((char *)apdu , "00A4000002");
		strcat((char *)apdu  , ADFID );
		if (slot == SLOT_USER)
		{
			ret = rd.RF_Send(apdu , resp , sw);
			if (ret != IRV_OK)
				return ret;
			strcpy(_pWorkingADF , ADFID);
		}
		else
		{
			ret = rd.PSAM_Send(apdu , resp , sw);
			if (ret != IRV_OK)
				return ret;
		}
		if (strcmp((char *)sw , "9000") != 0 )
		{
			return IRV_NO_FILE;
		}		
	}

	//选择EF目录
	if ((EFID != NULL) && (strlen(EFID) != 0))
	{
		strcpy((char *)apdu , "00A4000002");
		strcat((char *)apdu  , EFID );
		if (slot == SLOT_USER)
		{
			ret = rd.RF_Send(apdu , resp , sw);
			if (ret != IRV_OK)
				return ret;
			strcpy(_pWorkingEF , EFID);
		}
		else
		{
			ret = rd.PSAM_Send(apdu , resp , sw);
			if (ret != IRV_OK)
				return ret;
		}
		if (strcmp((char *)sw , "9000") != 0 )
		{
			return IRV_NO_FILE;
		}
	}
	return IRV_OK;
}


//PSAM卡对APDU数据进行 加密算MaC
//keyID：加密算mac 使用的Keyid
//divGene：发散因子， 依据Keyid不同 发散因子可能为 16字节或16 +8字节由上层负责。
//apduHead：apdu 命令头
//LcData:	更新数据
int PSAMEncMac(IN int keyID ,IN char * divGene, IN char* apduHead , IN char *LcData , OUT char * compApdu)
{
	int ret ;
	char apdu[513];
	char resp[513];
	char sw[5];
	
	switch (keyID)
		{
		case STK_DDF1:
			strcpy(apdu , "80DE280210");
			break;
		case STK_DF01:
			strcpy(apdu , "80DE280310");
			break;
		case STK_DF02:
			strcpy(apdu , "80DE480418");
			break;
		case STK_DF03:
			strcpy(apdu , "80DE480518");
			break;
		}
	strcat(apdu , divGene);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	//Enc Data
	strcpy(apdu , "80FA0000");
	makeLVwithPadding(LcData , apdu + 10);
	ret = strlen(apdu + 10) / 2;
	u.UINTToBin(ret , sw);
	u.BinToHexstr((unsigned char *)resp , (unsigned char *)sw + 1, 1 );
	memcpy(apdu + 8 , resp , 2);

	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (memcmp(sw , "\x36\x31" , 2) != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C00000");
	strcat(apdu , sw + 2);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	//resp = encdata
	strcpy(compApdu , apduHead);
	strcat(compApdu , resp );

	//mac
		switch (keyID)
		{
		case STK_DDF1:
			strcpy(apdu , "80DE280210");
			break;
		case STK_DF01:
			strcpy(apdu , "80DE280310");
			break;
		case STK_DF02:
			strcpy(apdu , "80DE480418");
			break;
		case STK_DF03:
			strcpy(apdu , "80DE480518");
			break;
		}
	strcat(apdu , divGene);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy(apdu , "80FA0500");
	strcpy(apdu + 10 , "00000000000000000000000000000000" ); // mac init
	strcpy( apdu + 10 + 32,compApdu ) ;
	Padding(apdu + 10);
	ret = strlen(apdu + 10) /2;
	u.UINTToBin(ret , sw);
	u.BinToHexstr((unsigned char *)resp ,(unsigned char *) sw + 1, 1 );
	memcpy(apdu + 8 , resp , 2);

	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (memcmp(sw , "\x36\x31" , 2) != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C00000");
	strcat(apdu , sw + 2);
	ret = rd.PSAM_Send (apdu , resp , sw); //发散密钥
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;
	
	strcat(compApdu , resp);

	return IRV_OK;
}


//更新二进制文件-密文+MAC读写
int UpdateBinEncMac(IN int keyID ,IN char * apduHead , IN char *LcData )
{
	char apdu[512 + 10 + 1];
	char resp[512];
	char divGene[49];
	char sw[5];

	int ret = GetCNandCityCode(divGene , divGene + 16 );
	if (ret != IRV_OK)
		return ret;
	switch(keyID) 
	{
	case STK_DDF1:
	case STK_DF01:
		divGene[16] = 0;  //一次发散
		break;
	case STK_DF02:
	case STK_DF03:
		//no code here	 //需要两次发散
		break;
	default:
		return IRV_DEBUGERR;
	}

	strcpy(apdu , "0084000008");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;
	strcat(divGene , resp ); //cardno + (citycode) + rand

	//prepare data	
	ret = PSAMEncMac(keyID , divGene ,apduHead , LcData , apdu );
	if (ret != IRV_OK) 
		return ret;
	
	ret = rd.RF_Send(apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_WR_RCDERR;

	return IRV_OK;

}


//更新线性定长记录文件-密文+MAC读写
//keyID：	使用的传输密钥STK ID 
//RecID：	更新的记录号
//Lc：		密文 + MAC的 数据长度
//datatag:	数据的tag标记
//LcData：	要写入的数据
int UpdateRecEncMac(IN int keyID ,IN char * RecID,IN char* Lc, IN int datatag,  IN char *LcData )
{
/*
	char apdu[512 + 10 + 1];
	char resp[256];
	char apduHead[11];
	char divGene[49];
	char sw[5];

	datatoTLV(datatag , LcData , resp);

	int l = _stTCL[datatag].length + 2; //t + l + v
	char a[3]={0};
	sprintf(a,"%02X",l);

	strcpy(apdu , "00DC");
	strcat(apdu , RecID );
	strcat(apdu , "04");	
	strcat(apdu , a);
	strcat(apdu ,resp);

	int ret = rd.RF_Send(apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_WR_RCDERR;
*/
	char apdu[512 + 10 + 1];
	char resp[256];
	char apduHead[11];
	char divGene[49];
	char sw[5];
	
	int ret = GetCNandCityCode(divGene , divGene + 16 );
	if (ret != IRV_OK)
		return ret;
	switch(keyID) 
	{
	case STK_DDF1:
	case STK_DF01:
		divGene[16] = 0;  //一次发散
		break;
	case STK_DF02:
	case STK_DF03:
		//no code here	 //需要两次发散
		break;
	default:
		return IRV_DEBUGERR;
	}

	strcpy(apdu , "0084000008");
	ret = rd.RF_Send (apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_RD_RCDERR;
	strcat(divGene , resp ); //cardno + (citycode) + rand

	//prepare data
	datatoTLV(datatag , LcData , resp);
	strcpy(apduHead , "04DC");
	strcat(apduHead , RecID );
	strcat(apduHead , "04");	
	strcat(apduHead , Lc);
	ret = PSAMEncMac(keyID , divGene ,apduHead , resp , apdu );
	if (ret != IRV_OK) 
		return ret;
	
	ret = rd.RF_Send(apdu , resp , sw);
	if ((ret != IRV_OK) ||(strcmp(sw , "9000") != 0))
		return IRV_WR_RCDERR;

	return IRV_OK;
}




//验证用户卡 UK
//KeyID : RK_DDF1/RK_DF01/RK_DF02
//用户卡号 ， 城市代码
int AuthUK(IN int KeyID , IN char * cardNo , IN char * cityCode)
{
//	return IRV_OK;
	int ret ;
	char apdu[100];
	char resp[256];
	char sw[5];
	char rand1[20];
	char rand2[20];

	//取用户随机数1
	strcpy((char *)apdu , "0084000008");
	ret = rd.RF_Send(apdu , resp , sw);
	if (ret != IRV_OK)
		return ret;
	if (strcmp(sw , "9000") != 0)
		return IRV_CARD_ERR;
	strcpy(rand1 , resp);

	//取用户随机数2
	strcpy((char *)apdu , "0084000008");
	ret = rd.RF_Send(apdu , resp , sw);
	if (ret != IRV_OK)
		return ret;
	if (strcmp(sw , "9000") != 0)
		return IRV_CARD_ERR;
	strcpy(rand2 , resp);

		
	switch(KeyID) {
	case UK_DDF1:
		strcpy(apdu , "80DE272A10");
		strcat(apdu , cardNo);
		strcat(apdu , rand2);
		break;
	case UK_DF01:
		strcpy(apdu , "80DE272B10");
		strcat(apdu , cardNo);
		strcat(apdu , rand2);
		break;
	case UK_DF02_1:
		strcpy(apdu , "80DE472C18");
		strcat(apdu , cardNo);
		strcat(apdu , cityCode);
		strcat(apdu , rand2);

		break;
	case UK_DF02_2:
		strcpy(apdu , "80DE472D18");
		strcat(apdu , cardNo);
		strcat(apdu , cityCode);
		strcat(apdu , rand2);
		break;
	case UK_DF02_3:
		strcpy(apdu , "80DE472E18");
		strcat(apdu , cardNo);
		strcat(apdu , cityCode);
		strcat(apdu , rand2);
		break;
	case UK_DF03_1:
		strcpy(apdu , "80DE472F18");
		strcat(apdu , cardNo);
		strcat(apdu , cityCode);
		strcat(apdu , rand2);
		break;
	case UK_DF03_2:
		strcpy(apdu , "80DE273010");
		strcat(apdu , cardNo);
		strcat(apdu , rand2);
		break;
	}	
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy(apdu , "80FA000010");
	strcat(apdu , rand1 );
	strcat(apdu , "0000000000000000");
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "6110") != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C0000010");
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy( rand2 ,resp + 16 );

	XorStr(rand2, resp , resp);
	
	switch  (KeyID)
	{	
	case  UK_DDF1:
		strcpy(apdu , "0082000511");
		break;	
	case UK_DF01:
	case UK_DF02_1:
	case UK_DF03_1:
		strcpy(apdu , "0082008511");
		break;
	case UK_DF02_2:
	case UK_DF03_2:
		strcpy(apdu , "0082008611");
		break;
	case UK_DF02_3:
		strcpy(apdu , "0082008711");
		break;
	}

	strcat(apdu , resp);
	strcat(apdu , rand1);
	strcat(apdu , "01");
	ret = rd.RF_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_IRK_VERR;
	
	return IRV_OK;
}


//验证用户卡 IRK 
//KeyID : RK_DDF1/RK_DF01/RK_DF02
//用户卡号 ， 城市代码
int AuthIRK(IN int KeyID , IN char * cardNo , IN char * cityCode)
{
//	return IRV_OK;
	int ret ;
	char apdu[100];
	char resp[256];
	char sw[5];
	char vRand[20];

	//取用户随机数
	strcpy((char *)apdu , "0084000008");
	ret = rd.RF_Send(apdu , resp , sw);
	if (ret != IRV_OK)
		return ret;
	if (strcmp(sw , "9000") != 0)
		return IRV_CARD_ERR;
	strcpy(vRand , resp);

		
	switch(KeyID) {
	case RK_DDF1:
		strcpy(apdu , "80DE473118");
		break;
	case RK_DF01:
		strcpy(apdu , "80DE473218");
		break;
	case RK_DF02:
		strcpy(apdu , "80DE473318");
		break;
	case RK_DF03:
		strcpy(apdu , "80DE473418");
		break;
	}	
	strcat(apdu , cardNo);
	strcat(apdu , cityCode);
	strcat(apdu , vRand);
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy(apdu , "80FA00001011223344556677880000000000000000");
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "6110") != 0)
		return IRV_PSAM_ERR;
	
	strcpy(apdu , "00C0000010");
	ret = rd.PSAM_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_PSAM_ERR;

	strcpy( vRand ,resp + 16 );

	XorStr(vRand , resp , resp);
	
	if (KeyID == RK_DDF1)
		strcpy(apdu , "0082000411");
	else
		strcpy(apdu , "0082008411");

	strcat(apdu , resp);
	strcat(apdu , "112233445566778801");
	ret = rd.RF_Send (apdu , resp , sw);
	if (strcmp(sw , "9000") != 0)
		return IRV_IRK_VERR;
	
	return IRV_OK;
}


void log_append_to_file(char* filename,char* str,char* sourceFile,int fileLine)
{
    time_t t;
    time(&t);
    struct tm* tp= localtime(&t);
    printf("%x\n",tp);
    char now_str[100];
    strftime(now_str, 100, "%Y-%m-%d %H:%M:%S", tp);
 
    FILE *fo;
    fo = fopen(filename, "a");
    if (fo == 0) {  
        return;
    }
 
    fprintf(fo, "%s %s(:%d):%s\r\n",now_str,sourceFile,fileLine, str);
    fclose(fo);
}