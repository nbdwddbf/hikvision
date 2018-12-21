#ifndef __CASRV_LIB__
#define __CASRV_LIB__

#ifdef   __cplusplus
extern "C"{
#endif


	typedef struct{
		char CommonName[64];
		char Province[32];
		char City[32];
		char Company[32];
		char TelNum[12];
		char Email[32];
		int  ValidYears;
	}SWCA_CERT_REQ;

	/*RSA密钥结构定义*/
#define LiteRSAref_MAX_BITS    2048
#define LiteRSAref_MAX_LEN     ((LiteRSAref_MAX_BITS + 7) / 8)
#define LiteRSAref_MAX_PBITS   ((LiteRSAref_MAX_BITS + 1) / 2)
#define LiteRSAref_MAX_PLEN    ((LiteRSAref_MAX_PBITS + 7)/ 8)

	typedef struct RSArefPublicKeyLite_st
	{
		unsigned int  bits;
		unsigned char m[LiteRSAref_MAX_LEN];
		unsigned char e[LiteRSAref_MAX_LEN];
	}RSArefPublicKeyLite;

	/*ECC密钥结构定义*/
#define ECCref_MAX_BITS			512 
#define ECCref_MAX_LEN			((ECCref_MAX_BITS+7) / 8)
#define ECCref_MAX_CIPHER_LEN	136

	typedef struct ECCrefPublicKey_st
	{
		unsigned int  bits;
		unsigned char x[ECCref_MAX_LEN];
		unsigned char y[ECCref_MAX_LEN];
	} ECCrefPublicKey;


	/*----------------------------------------------------------
	功能：初始化，读取配置文件
	参数：
	IP_CA		输入		CA服务IP地址
	Port_CA		输入		CA服务端口

	返回值：0：成功  其他：失败（具体查询错误码）
	----------------------------------------------------------*/
	int CA_Init(const char *IP_CA, int Port_CA);

	/*----------------------------------------------------------
	功能：P10格式在线申请证书
	参数：
	iValidYear	输入		证书有效期
	uiP10Len    输入        P10长度
	ucP10		输入		P10请求
	uiCertLen   输入/输出   证书存储长度
	ucCert	    输出		证书
	返回值：0：成功  其他：失败（具体查询错误码）
	----------------------------------------------------------*/
	int CA_ApplyCert_P10(int iValidYear, int uiP10Len, unsigned char *ucP10, int *uiCertLen, unsigned char *ucCert);

	/*----------------------------------------------------------
	功能:在线申请证书
	参数：
	iReqType			输入		申请类型 1 签名 2加密
	iAlgFlag			输入        算法类型 1 RSA 2 SM2
	iModLen				输入		模长 1024 2048 256
	iPriType			输入		返回密钥对格式 1 ASN.1  2 SKF
	ucPubKey			输入	    公钥 国密结构
	uiPubKeyLen			输入	    公钥长度
	ucCertReqInfo		输入	    用户信息
	uiCertReqInfoLen	输入	    用户信息长度
	ucUserCert			输出        证书
	uiUserCertLen		输入/输出	证书存储长度
	ucUserKey           输出        用户加密密钥对（密文）
	uiUserKeyLen        输入/输出   用户加密密钥对长度
	返回值：0：成功  其他：失败（具体查询错误码）
	----------------------------------------------------------*/
	int CA_GenUserCert(int iReqType, int iAlgFlag, int iModLen, int iPriType,
		unsigned char *ucPubKey, unsigned int uiPubKeyLen,
		unsigned char *ucCertReqInfo, unsigned int uiCertReqInfoLen,
		unsigned char *ucUserCert, unsigned int *uiUserCertLen,
		unsigned char *ucUserKey, unsigned int *uiUserKeyLen);

	/*----------------------------------------------------------
	功能:获取CA根证书
	参数：
	ucRootCert			输出        证书
	uiRootCertLen		输入/输出	证书存储长度
	返回值：0：成功  其他：失败（具体查询错误码）
	----------------------------------------------------------*/
	int CA_GetRootCert(unsigned char *ucRootCert, unsigned int *uiRootCertLen);

	/*----------------------------------------------------------
	功能:获取KMS根证书
	参数：
	ucKMSCert			输出        证书
	uiKMSCertLen		输入/输出	证书存储长度
	返回值：0：成功  其他：失败（具体查询错误码）
	----------------------------------------------------------*/
	int CA_GetKMSCert(unsigned char *ucKMSCert, unsigned int *uiKMSCertLen);

//错误码定义
#define KMSSRV_ERR_SRV_RETURN_BASE				0x20000000    /*密管服务返回错误 偏移*/

#define ERR_SUCCESS						0x00    /*成功*/
#define ERR_PACKAGE						0x01    /*报文格式错误*/
#define ERR_P10							0x02    /*p10格式错误*/
#define ERR_PUBKey					    0x03    /*公钥格式错误*/
#define ERR_USERINFO					0x04    /*用户信息格式错误*/
#define ERR_GENKEY						0x05    /*生成非对称密钥对错误*/

#define ERR_GENCERT						0x06    /*签发证书错误*/
#define ERR_APPLYTYPE					0x07    /*申请类型不支持错误*/
#define ERR_ALGORITHM					0x08    /*不支持的算法类型*/
#define ERR_LICENSE                     0x09    /*服务端授权错误*/
#define ERR_RANDOM                      0x0A    /*响应报文随机信息不匹配*/
#define ERR_CERTLEN                     0x0B    /*证书长度错误*/
#define ERR_CN_NULL                     0x0C    /*CN为空*/
#define ERR_USERINFO_ITEM_TOO_LONG      0x0D    /*用户信息分项太长*/
#define ERR_CMD                         0X0E    /*服务端返回命令码不正确*/
#define ERR_NO_USER_KEY                 0x0F    /*服务端没有返回加密证书密钥对*/
#define ERR_PRIVATE_TYPE                0x10    /*请求返回私钥格式错误*/
#define ERR_VALID_YEAR                  0x11    /*请求证书有效期错误1-19*/
#define ERR_UNKNOW						0x70    /*未知错误*/


#define KMSSRV_ERR_NOINIT						0x30	/*接口未初始化*/
#define KMSSRV_ERR_TCP_CONNECT					0x31    /*连接密管失败*/
#define KMSSRV_ERR_TCP_SEND						0x32    /*发送数据错误*/
#define KMSSRV_ERR_TCP_RECEIVE					0x33    /*接受数据错误*/
#define KMSSRV_ERR_TCP_DATALEN					0x34    /*接受报文数据长度错误*/
#define KMSSRV_ERR_TCP_CERTBUFF					0x35    /*证书缓冲区长度错误*/
#define KMSSRV_ERR_TCP_KEYBUFF					0x36    /*密钥缓冲区长度错误*/
#define KMSSRV_ERR_TCP_UNKNOW					0x37    /*未知错误*/

	/*其他错误码请查阅 密码卡头文件定义*/

#ifdef   __cplusplus
}
#endif
#endif