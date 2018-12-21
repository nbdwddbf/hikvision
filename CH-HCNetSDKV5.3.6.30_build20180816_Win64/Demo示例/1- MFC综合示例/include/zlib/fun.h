#ifndef _ZIPUNZIPFUN_H
#define _ZIPUNZIPFUN_H

#if (!defined(_WIN32)) && (!defined(WIN32)) && (!defined(__APPLE__))
#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#ifndef _FILE_OFFSET_BIT
#define _FILE_OFFSET_BIT 64
#endif
#endif

#ifdef __APPLE__
// In darwin and perhaps other BSD variants off_t is a 64 bit value, hence no need for specific 64 bit functions
#define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#define FTELLO_FUNC(stream) ftello(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#define FTELLO_FUNC(stream) ftello64(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#ifdef _WIN32
# include <direct.h>
# include <io.h>
#else
# include <unistd.h>
# include <utime.h>
# include <sys/types.h>
# include <sys/stat.h>
#endif

#include "zip.h"
#include "unzip.h"

#ifdef _WIN32
#define USEWIN32IOAPI
#include "iowin32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

// 公共函数
extern uLong ZEXPORT filetime OF ((const char* pFile, tm_zip* tmzip, uLong* pDosTime));

extern int ZEXPORT check_exist_file OF((const char* filename));

extern int ZEXPORT getFileCrc OF((const char* filenameinzip, void* buf, unsigned long size_buf,unsigned long* result_crc));

extern int ZEXPORT isLargeFile OF ((const char* filename));

extern int ZEXPORT makedir OF((const char* newdir));


// 解压zip文件的具体函数,返回52表示文件路径太长
extern int do_extract OF((unzFile uf, int opt_extract_without_path, int opt_overwrite, const char* password, int iDirPathLength));

#ifdef __cplusplus
}
#endif

#endif