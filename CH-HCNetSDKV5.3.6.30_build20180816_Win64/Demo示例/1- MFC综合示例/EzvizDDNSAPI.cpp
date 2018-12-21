#include "stdafx.h"
#include "EzvizDDNSAPI.h"

EzvizDDNSAPI::EzvizDDNSAPI()
{
	accessToken = "";
	areaDomain = "";
}


EzvizDDNSAPI::~EzvizDDNSAPI()
{
}

void EzvizDDNSAPI::setToken(string strToken){
	accessToken = strToken;
}

void EzvizDDNSAPI::setDomain(string strDomain){
	areaDomain = strDomain;
}

string EzvizDDNSAPI::getToken(){
	return accessToken;
}

string get_access_token(string appKey, string appSecret){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts("https://open.ezvizlife.com/api/lapp/token/get", "appKey=" + appKey + "&appSecret=" + appSecret, strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::get_ddns_info_by_device_serial(string accessToken, string deviceSerial){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/get", "accessToken=" + accessToken + "&deviceSerial=" + deviceSerial, strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::get_ddns_info_by_domain(string accessToken, string domain){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/get", "accessToken=" + accessToken + "&domain=" + domain, strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::set_ddns_domain(string accessToken, string deviceSerial, string domain){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/setDomain", "accessToken=" + accessToken + "&deviceSerial=" + deviceSerial + "&domain=" + domain, strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::set_ddns_auto_mapping(string accessToken, string deviceSerial){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/mode/setAutomatic", "accessToken=" + accessToken + "&deviceSerial=" + deviceSerial, strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::set_ddns_manual_mapping(string accessToken, string deviceSerial, int cmdPort, int httpPort){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/mode/setManual", "accessToken=" + accessToken + "&deviceSerial=" + deviceSerial + "&cmdPort=" + int_to_string(cmdPort) + "&httpPort=" + int_to_string(httpPort), strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::get_ddns_info_of_my_devices(string accessToken){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/list", "accessToken=" + accessToken + "&pageSize=10&pageStart=0", strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::share_ddns(string accessToken, string deviceSerial, string account){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/share", "accessToken=" + accessToken + "&deviceSerial=" + deviceSerial + "&account=" + account, strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::add_device(string accessToken, string deviceSerial, string validateCode){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/device/add", "accessToken=" + accessToken + "&deviceSerial=" + deviceSerial + "&validateCode=" + validateCode, strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string EzvizDDNSAPI::get_ddns_info_of_shared_devices(string accessToken, int pageSize, int pageStart){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Posts(areaDomain + "/api/lapp/ddns/share/list", "accessToken=" + accessToken + "&pageSize=" + int_to_string(pageSize) + "&pageStart=" + int_to_string(pageStart), strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string get_area_list(){
	CHttpClient httpClient;
	string strRetData;
	httpClient.Gets("https://open.ezvizlife.com/api/lapp/area/list", strRetData);
	strRetData = UTF8ToANSIString(strRetData);
	return strRetData;
}

string int_to_string(int n){
	ostringstream stream;
	stream << n;  //n为int类型
	return stream.str();
}

/****************************************
Function:    AnsiToUTF8
Description: Ansi字符转换成UTF-8字符
Input:       szAnsiString Ansi字符
Return:      UTF-8字符
****************************************/
char* AnsiToUTF8(const char *szAnsiString)
{
#if defined(_WIN32) || defined(_WIN64)
	if (szAnsiString == NULL || strlen(szAnsiString) == 0)
	{
		return NULL;
	}
	//AnsiToUnicode
	//预转换，得到所需空间的大小
	int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szAnsiString, (int)strlen(szAnsiString), NULL, 0);

	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszUnicodeString = new wchar_t[(size_t)wcsLen + 1];

	//转换
	::MultiByteToWideChar(CP_ACP, NULL, szAnsiString, (int)strlen(szAnsiString), wszUnicodeString, wcsLen);

	//最后加上'\0'
	wszUnicodeString[wcsLen] = '\0';

	// unicode to UTF8
	//预转换，得到所需空间的大小，这次用的函数和上面名字相反
	int UTF8Len = ::WideCharToMultiByte(CP_UTF8, NULL, wszUnicodeString, (int)wcslen(wszUnicodeString), NULL, 0, NULL, NULL);

	//同上，分配空间要给'\0'留个空间
	//UTF8虽然是Unicode的压缩形式，但也是多字节字符串，所以可以以char的形式保存
	char* szUTF8 = new char[(size_t)UTF8Len + 1];

	//转换
	//unicode版对应的strlen是wcslen
	::WideCharToMultiByte(CP_UTF8, NULL, wszUnicodeString, (int)wcslen(wszUnicodeString), szUTF8, UTF8Len, NULL, NULL);

	//最后加上'\0'
	szUTF8[UTF8Len] = '\0';

	delete[] wszUnicodeString;
	wszUnicodeString = NULL;

	return szUTF8;

#else
	if (NULL == szAnsiString)
	{
		return NULL;
	}
	char *outbuf = 0;
	if (szAnsiString)
	{
		iconv_t cd = iconv_open("UTF-8", "EUC-CN");
		if (cd)
		{
			size_t contlen = strlen(szAnsiString);
			size_t outbuflen = contlen * 3 + 1;
			outbuf = new char[outbuflen];
			memset(outbuf, 0, outbuflen);

			char *inptr = const_cast<char*>(szAnsiString);
			char *outptr = outbuf;

			size_t inlen = contlen;
			size_t outlen = outbuflen;
			if (iconv(cd, &inptr, &inlen, &outptr, &outlen) == (size_t)(-1))
			{
				outbuf = 0;
			}

			iconv_close(cd);
		}
	}
	return outbuf;
#endif
}

/****************************************
Function:    UTF8ToAnsi
Description: UTF-8字符转换成Ansi字符
Input:       szAnsiString UTF-8字符
Return:      Ansi字符
****************************************/
char* UTF8ToAnsi(const char *szUTF8String)
{
#if defined(_WIN32) || defined(_WIN64)
	WCHAR* strSrc = NULL;
	char* szRes = NULL;

	int i = MultiByteToWideChar(CP_UTF8, 0, szUTF8String, -1, NULL, 0);

	strSrc = new WCHAR[(size_t)i + 1];
	MultiByteToWideChar(CP_UTF8, 0, szUTF8String, -1, strSrc, i);

	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);

	szRes = new char[(size_t)i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	delete[] strSrc;
	strSrc = NULL;

	return szRes;

#else
	char *outbuf = 0;
	if (szUTF8String)
	{
		iconv_t cd = iconv_open("EUC-CN", "UTF-8");
		if (cd)
		{
			size_t contlen = strlen(szUTF8String);
			size_t outbuflen = contlen * 3 + 1;
			outbuf = new char[outbuflen];
			memset(outbuf, 0, outbuflen);

			char *inptr = const_cast<char*>(szUTF8String);
			char *outptr = outbuf;

			size_t inlen = contlen;
			size_t outlen = outbuflen;
			if (iconv(cd, &inptr, &inlen, &outptr, &outlen) == (size_t)(-1))
			{
				outbuf = 0;
			}

			iconv_close(cd);
		}
	}
	return outbuf;
#endif
}

string UTF8ToANSIString(const char *pUtf8String)
{
	string strANSI;
	if (pUtf8String != NULL)
	{
		char *pAnsi = UTF8ToAnsi(pUtf8String);
		if (pAnsi != NULL)
		{
			strANSI = pAnsi;
			delete[]pAnsi;
		}
	}

	return strANSI;
}

string UTF8ToANSIString(string strRetData){
#if defined(_WIN32) || defined(_WIN64)
	strRetData = UTF8ToANSIString(strRetData.c_str());
#endif
	return strRetData;
}