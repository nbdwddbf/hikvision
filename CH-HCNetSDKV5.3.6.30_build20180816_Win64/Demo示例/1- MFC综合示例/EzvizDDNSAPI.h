#pragma once

#include <string>
#include <iostream>
#include "curl/curl.h"
#include "curl_httpclient.h"
#include <Windows.h>
#include <WinSock2.h>
#include <time.h>
#include <sstream>

using namespace std;

class EzvizDDNSAPI
{
private:
	string accessToken;
	string areaDomain;
public:
	EzvizDDNSAPI();
	~EzvizDDNSAPI();
	void setToken(string strToken);
	void setDomain(string strDomain);
	string getToken();
	string get_ddns_info_by_device_serial(string accessToken, string deviceSerial);
	string get_ddns_info_by_domain(string accessToken, string domain);
	string set_ddns_domain(string accessToken, string deviceSerial, string domain);
	string set_ddns_auto_mapping(string accessToken, string deviceSerial);
	string set_ddns_manual_mapping(string accessToken, string deviceSerial, int cmdPort, int httpPort);
	string get_ddns_info_of_my_devices(string accessToken);
	string share_ddns(string accessToken, string deviceSerial, string account);
	string add_device(string accessToken, string deviceSerial, string validateCode);
	string get_ddns_info_of_shared_devices(string accessToken, int pageSize, int pageStart);
};

string int_to_string(int n);
char *AnsiToUTF8(const char *szAnsiString);
char *UTF8ToAnsi(const char *szUTF8String);
string UTF8ToANSIString(const char *pUtf8String);
string UTF8ToANSIString(string rsp);
string get_area_list();
string get_access_token(string appKey, string appSecret);