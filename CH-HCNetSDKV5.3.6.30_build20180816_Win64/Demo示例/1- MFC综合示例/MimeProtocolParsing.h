
#include "stdafx.h"
#include "string.h"
using namespace std;
typedef unsigned long           DWORD;
#define TRUE  1
#define FALSE 0
#define  BOOL  int

#define UTILS_SPACE               " "         //空格其实不大会打错个数，以防万一，还是定义一个宏
#define UTILS_CRLF                "\r\n"      //回车换行，HTTP里经常各种回车换行，避免笔误打错
#define UTILS_LINE                "\n"        //换行符
#define DOUBLE_UTILS_CRLF         "\r\n\r\n"  //双回车换行，http头结束标志

char *get_boundary(char *mfd);
char* mutipart_form_data(char *mfd, char *boundary, char **type, char **content, int mfdSize, int& contentLen, int& offsetLen);