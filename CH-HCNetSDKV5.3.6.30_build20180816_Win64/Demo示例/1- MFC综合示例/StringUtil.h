#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_




#include <assert.h>
#include <string>
#include <sstream>
#include <vector>

namespace Base
{
    using namespace std;

    namespace StringUtil
    {

        /** @fn 
         *  @brief  T类型转string，前提T是必须标准C++类型或者重载了转换符
         *          【注意】浮点类型只能精确到.00001
         *  @param  (IN) 
         *  @return 
         */
        template <class T>
        inline string T2String(const T& source)
        {
            std::stringstream ss;
            ss << source;
            return ss.str();
        }

        template<>
        inline string T2String(const bool &source)
        {
            if (source == true)
            {
                return "true";
            }
            else
            {
                return "false";
            }
        }

        /** @fn 
         *  @brief  string转T类型，前提T是必须标准C++类型或者重载了转换符
         *          【注意】浮点类型只能精确到.00001
         *  @param  (IN) 
         *  @return 
         */
        template <class T>
        inline T String2T(const string& str)
        {
            //assert(!str.empty());

            T value;
            std::stringstream ss(str);
            ss >> value;

            return value;
        }

        /** @fn 
         *  @brief  string转c风格string
         *  @param  (IN) 
         *  @return 
         */
        template <size_t N>
        inline char* String2CStr(char (&szArray)[N], const char* pStr)
        {
            assert(pStr != NULL); // 不能为NULL
            memset(szArray, 0, N);
            return strncpy(szArray, pStr, N - 1);
        }

        /** @fn 
         *  @brief  string转c风格string
         *  @param  (IN) 
         *  @return 
         */
        template <size_t N>
        inline char* String2CStr(char (&szArray)[N], const string& str)
        {
            return String2CStr(szArray, str.c_str());
        }

        /** @fn 
         *  @brief  字节流转string
         *  @param  (IN) const unsigned char (&szArray)[N] 输入参数无终止符
         *  @return 
         */
        template <size_t N>
        inline string Bytes2String(const unsigned char (&szArray)[N])
        {
            char szDuplicate[N + 1] = { 0 };
            memcpy(szDuplicate, szArray, N);
            return szDuplicate;
        }

        /** @fn 
         *  @brief string转字节流 
         *  @param  (IN) unsigned char (&szArray)[N] 输出参数无终止符
         *  @return 
         */
        template <size_t N>
        inline void String2Bytes(unsigned char (&szArray)[N], const char* pStr)
        {
            assert(pStr != NULL); // 不能为NULL
            memset(szArray, 0, N);
            strncpy((char*)szArray, pStr, N);
        }

        template <size_t N>
        inline bool BytesCmp(unsigned char (&szArray)[N], const char* pStr)
        {
            assert(pStr != NULL); // 不能为NULL
            return strncmp((char*)szArray, pStr, N) == 0;
        }

        /** @fn 
         *  @brief string转字节流 
         *  @param  (IN) unsigned char (&szArray)[N] 输出参数无终止符
         *  @return 
         */
        template <size_t N>
        inline void String2Bytes(unsigned char (&szArray)[N], const string& str)
        {
            String2Bytes(szArray, str.c_str());
        }

        // 切割字符串
        // 将 "1,2,3,4,5"这种类型的字符串转换为{ 1, 2, 3, 4, 5 }此类型数组
        template <typename T>
        void String2Array(vector<T>& vsValues, const string& strArray, char cSplit = ',')
        {
            vsValues.clear();

            size_t uPreIndex = 0;
            size_t uIndex = 0;
            size_t uLen = 0;

            while((uIndex = strArray.find_first_of(cSplit, uPreIndex)) != string::npos)
            {
                if ((uLen = uIndex - uPreIndex) != 0)
                {
                    vsValues.push_back(String2T<T>(strArray.substr(uPreIndex, uLen)));
                }
                uPreIndex = uIndex + 1;
            }
            if (uPreIndex < strArray.size())
            {
                vsValues.push_back(String2T<T>(strArray.substr(uPreIndex).c_str()));
            }
        }

        // 将{ 1, 2, 3, 4, 5 }此类型数组转换为 "1,2,3,4,5"这种类型的字符串
        template <typename T>
        void Array2String(string& strArray, const vector<T>& vsValues, char cSplit = ',')
        {
            strArray.clear();
            strArray.reserve(vsValues.size() * 3); // 有些数字可能是两位数的

            if (vsValues.empty())
            {
                return;
            }

            for (typename vector<T>::const_iterator it = vsValues.begin();;)
            {
                strArray += T2String(*it);
                if (++it != vsValues.end())
                {
                    strArray += cSplit;
                }
                else
                {
                    break;
                }
            }
        }
        

    }

}
#endif