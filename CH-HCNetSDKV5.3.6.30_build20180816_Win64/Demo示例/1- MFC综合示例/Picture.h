// CPicture.h: interface for the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__081D008A_5029_4C56_B80C_37793E323DF6__INCLUDED_)
#define AFX_PICTURE_H__081D008A_5029_4C56_B80C_37793E323DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <afxctl.h>
//------------------------------------------

typedef enum
{
	OFM_WRITE        = 0,
	OFM_READ         = 1
}FILE_OPENMODE;

#define HIMETRIC_INCH 2540

//=-----------------------------
class CFileProcess
{
private :
	FILE  *m_File;

public:
	CFileProcess();
   ~CFileProcess();
    BOOL	Open        (char * FileName , FILE_OPENMODE Open_Mode);
	BOOL	Write       (VOID * zBuffer, DWORD cSize);
    BOOL	Read        (VOID * zBuffer, DWORD cSize);
	LONG    GetSize     (VOID);
	VOID    Close       (VOID);
};

//-------------------------------------------------------------


//-----------------------------------------
class CPicture  
{
public:
	CPicture();
	virtual ~CPicture();
	
private:
	IPicture *m_pic;
	HGLOBAL  hGlobal;
	LPPICTURE m_pPict;

public:

	HBITMAP LoadPicture(char * FileName);
	HBITMAP LoadPicture(char * FileName, HDC hdc);
	HBITMAP LoadPicture(char *FileName, HDC hdc, long cx, long cy);
	VOID    FreePicture( VOID );
    HDC     _GetDC     ( VOID );
	HBITMAP _GetHandle ( VOID );
	DWORD   _GetWidth  ( VOID );
	DWORD   _GetHeight ( VOID );
	BOOL    DrawPicture(HDC hdc,long x,long y,long cx,long cy);
	void Render(CDC* pDC, LPRECT pDrawRect/*目标矩形，单位是逻辑坐标单位*/, LPRECT 
		
		
		
		pSrcRect=NULL/*来源矩形，单位是0.01毫米,如果为空，则拉伸整个图像到目标矩形*/,LPCRECT prcWBounds=NULL/*图元文件专用，绑定矩形*/);//在给定的DC上画图，


};

class CPicture_Ex:public CPictureHolder  
{
public:
	BOOL Load(CString sFilePathName);//从文件读取图像
	BOOL Load(HINSTANCE hInstance,LPCTSTR lpszResourceName, LPCSTR ResourceType);//从资源读取图像
	BOOL LoadPictureData(BYTE* pBuffer, int nSize);//从内存读取图像
	BOOL SaveAsBitmap(CString sFilePathName);//写入到BMP文件
	void Render(CDC* pDC, LPRECT pDrawRect/*目标矩形，单位是逻辑坐标单位*/, LPRECT 
		
		
		
		pSrcRect=NULL/*来源矩形，单位是0.01毫米,如果为空，则拉伸整个图像到目标矩形*/,LPCRECT prcWBounds=NULL/*图元文件专用，绑定矩形*/);//在给定的DC上画图，
	CPicture_Ex();
	virtual ~CPicture_Ex();
	void  UnloadPicture();//释放图像，作用同CPictureHolder::~CPictureHolder()
public:
	LONG      get_Height(); // 以0.01毫米为单位的图像高度
	LONG      get_Width();  // 以0.01毫米为单位的图像宽度
};

#endif // !defined(AFX_PICTURE_H__081D008A_5029_4C56_B80C_37793E323DF6__INCLUDED_)
