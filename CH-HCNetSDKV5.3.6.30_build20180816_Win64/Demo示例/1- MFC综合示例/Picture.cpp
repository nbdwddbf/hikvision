// CPicture.cpp: implementation of the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "PreviewDialog.h"
#include "Picture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//----------------CFileProcess class------------------------------------
//constructor
CFileProcess::CFileProcess()
{
	m_File = NULL;         //File *m_File;
}

//destructor !
CFileProcess::~CFileProcess()
{
//	this->Close();
}

//opens a file either for reading or writing
BOOL CFileProcess::Open(char * FileName , FILE_OPENMODE Open_Mode)
{

	switch (Open_Mode)
	{
		case OFM_READ:
			m_File = fopen(FileName, "rb");
			break;
		case OFM_WRITE:
			m_File = fopen(FileName, "wb");
			break;
	}

	//ASSERT(m_File != NULL);
	if(!m_File) 
		return FALSE;
	return TRUE;
}


//Reads data from the file stream.
BOOL CFileProcess::Read(VOID * zBuffer, DWORD cSize)
{
	DWORD dwFreadReslut = fread(zBuffer, sizeof(BYTE), cSize, m_File);
	if(dwFreadReslut < cSize)
		return FALSE;
	return TRUE;
}

//Writes data to the file stream.
BOOL CFileProcess::Write(VOID * zBuffer,DWORD cSize)
{
	//fwrite :write size*count byte to buffer.
	if(fwrite(zBuffer, sizeof(BYTE), cSize, m_File) < cSize)
       return FALSE;
	return TRUE;
}

//Gets the File Size
LONG CFileProcess::GetSize(VOID)
{
	long t_location =  ftell(m_File);
	//moves the file pointer to  a specified location 
	fseek(this->m_File, 0, SEEK_END);

	long f_size = ftell(this->m_File);
	fseek(this->m_File ,t_location, SEEK_SET);
	return f_size;
}

//Closes the File
VOID CFileProcess::Close(VOID)
{
	if(m_File)
	{
		fclose(this->m_File);
	    this->m_File  = NULL;
	}
	return;
}

//-----------------------
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPicture::CPicture()
{
	m_pic = NULL;
	hGlobal = NULL;

}

CPicture::~CPicture()
{
	this->FreePicture();

}



void CPicture::Render(CDC* pDC, LPRECT pDrawRect, LPRECT pSrcRect/*=NULL*/,LPCRECT prcWBounds/*=NULL*/)
{
    if (pDC == NULL || m_pPict == NULL) return ;
    
	CRect recrDest(pDrawRect);
	
	
	
    long Width  = 0;
    long Height = 0;
    m_pPict->get_Width(&Width);
    m_pPict->get_Height(&Height);
	
	
	
	CRect SrcRect(0,0,Width,Height);
	
	
	
	if(pSrcRect){
		SrcRect=*pSrcRect;
	}
	CRect DrawRect(pDrawRect);
    HRESULT hrP = NULL;
	
	
	
    hrP = m_pPict->Render(pDC->m_hDC,
		DrawRect.left,                  // Left
		DrawRect.top,                   // Top
		DrawRect.Width(), // Right
		DrawRect.Height(), // Bottom
		SrcRect.left,
		SrcRect.top,
		SrcRect.Width(),
		SrcRect.Height(),
		prcWBounds);
	
	
	
    if (SUCCEEDED(hrP)) return;
	AfxThrowMemoryException();
    return;
}
/*
OUR MAIN FUNCTION
*/
HBITMAP CPicture::LoadPicture(char *FileName)
{
	FreePicture();

	CFileProcess cFile;  //the image file
	
	//if we couldn't open the image file then we should get out of here
    if(!cFile.Open(FileName, OFM_READ)) 
		return NULL;

	//we must know exactly the buffer size to allocate
	//in order to read the image in it
	//so get the image file size
    long nSize = cFile.GetSize(); 
	//allocate enough memory to hold the image
	//it must be allocated using GlobalAlloc
	//otherwise it will fail...try using new or malloc and you'll see!!!
	hGlobal = GlobalAlloc(GMEM_MOVEABLE, nSize);
	
	//get pointer to first byte
	void* pData = GlobalLock(hGlobal);
	
	//read the file in the prev allocated memory
	if(!cFile.Read(pData, nSize)) 
		return NULL;;
	//we don't need the file any more so close it
	cFile.Close();
	GlobalUnlock(hGlobal); 

	IStream* pStream = NULL;
    //ole routines....
	//creates a stream from our handle
	//don't know why and how?
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) != S_OK)
		return NULL;

	HRESULT hr;
	//aha..now let ole reads the image and load it for us
	//param3:Reference to the identifier of the interface 
               // describing the type of interface pointer to return
	//param4: Address of output variable that receives interface  pointer requested in riid
	hr = OleLoadPicture(pStream, nSize, FALSE, IID_IPicture, (LPVOID*)&this->m_pic);
	if(hr != S_OK)
		return NULL;
	
//	if ((hr = OleLoadPicture(pStream, nSize, FALSE, IID_IPicture, (LPVOID *)&this->m_pic)) != S_OK)
//		return NULL;
	HBITMAP hbmp = NULL;
	//return an HBITMAP to our image like the LoadImage function does
	//we might need the handle
	this->m_pic->get_Handle((OLE_HANDLE *) &hbmp);
	return hbmp;
}


//an overloaded version of the above to draw the picture
//as well in a given DC
HBITMAP CPicture::LoadPicture(char *FileName, HDC hdc)
{
	HBITMAP hbmp = this->LoadPicture(FileName);
	this->DrawPicture(hdc, 0, 0, this->_GetWidth(), _GetHeight());
	return hbmp;
}

//an overloaded version of the above to draw the picture
//as well in a given DC , give the rect, width and height
HBITMAP CPicture::LoadPicture(char *FileName, HDC hdc, long cx, long cy)
{
	HBITMAP hbmp = this->LoadPicture(FileName);
	this->DrawPicture(hdc, 0, 0, cx,cy);
	return hbmp;
}

//returns the width of the loaded image  
DWORD CPicture::_GetWidth(VOID)
{
    
	if(! m_pic) 
		return 0;
	OLE_XSIZE_HIMETRIC pWidth;
	m_pic->get_Width(&pWidth);
	HDC tDC = ::CreateCompatibleDC(0);
	int nWidth	= MulDiv(pWidth,::GetDeviceCaps(tDC, LOGPIXELSX), HIMETRIC_INCH);
	DeleteDC(tDC);
	return (DWORD) nWidth;
}


//returns the height of the loaded image
DWORD CPicture::_GetHeight(VOID)
{
	if(! m_pic) 
		return 0;
	OLE_YSIZE_HIMETRIC pHeight;

	m_pic->get_Height(&pHeight);
	HDC tDC = ::CreateCompatibleDC(0);

	int nHeight	= MulDiv(pHeight,::GetDeviceCaps(tDC, LOGPIXELSY), HIMETRIC_INCH);
	DeleteDC(tDC);
	
	return (DWORD) nHeight;
}

//returns the current DC of the loaded image
HDC CPicture::_GetDC(VOID)
{
	if(! m_pic) 
		return NULL;
	HDC pDC ;
	m_pic->get_CurDC(&pDC);
	return  pDC;
}

//returns the Handle of the loaded image(HBITMAP)
HBITMAP CPicture::_GetHandle( VOID )
{
	if(! m_pic) 
		return NULL; 

	HBITMAP hbmp;
	m_pic->get_Handle((OLE_HANDLE *) &hbmp);
	return  hbmp;
}


//Draws the image in a specified DC..with given dimensions
//specify -1 for width and height if you like to draw
//with original dimensions
BOOL CPicture::DrawPicture(HDC hdc,long x,long y,long cx,long cy)
{
	if(!m_pic) 
		return FALSE;

	LONG pHeight,pWidth;
	if(cx == -1) 
		cx = this->_GetWidth();
	if(cy == -1) 
		cy = this->_GetHeight();
	m_pic->get_Width(&pWidth);
    m_pic->get_Height(&pHeight);
	if (m_pic->Render(hdc, x, y, cx, cy, 0, pHeight, pWidth,-pHeight, NULL) != S_OK)
		return FALSE ;
	
	return TRUE;
}

//Cleans up
VOID CPicture::FreePicture(VOID)
{
	if(m_pic)
	{
		m_pic->Release();
		m_pic = NULL;
	}

	if(hGlobal)
	{
		GlobalFree(hGlobal);
		hGlobal = NULL;
	}
}

//[add] by zhaolin 2012-9-20 11:59 视频综合平台B20
CPicture_Ex::CPicture_Ex()
{

}

CPicture_Ex::~CPicture_Ex()
{

}
//-----------------------------------------------------------------------------
// Does:   Free The Allocated Memory That Holdes The IPicture Interface Data
// ~~~~    And Clear Picture Information
//
// Note:   This Might Also Be Useful If U Only Need To Show The Picture Once
// ~~~~~   Or If U Copy The Picture To The Device Context, So It Can Still
//         Remain On Screen - But IPicture Data Is Not Needed No More
//
//-----------------------------------------------------------------------------
void CPicture_Ex::UnloadPicture()
//=============================================================================
{
 if(m_pPict != NULL){
  m_pPict->Release();
  m_pPict = NULL;
 }
}
//-----------------------------------------------------------------------------
// Does:   Open a Resource And Load It Into IPicture (Interface)
// ~~~~    (.BMP .DIB .EMF .GIF .ICO .JPG .WMF)
//
// Note:   When Adding a Bitmap Resource It Would Automatically Show On "Bitmap"
// ~~~~    This NOT Good Coz We Need To Load It From a Custom Resource "BMP"
//         To Add a Custom Rresource: Import Resource -> Open As -> Custom
//         (Both .BMP And .DIB Should Be Found Under "BMP")
//
// InPut:  ResourceName - As a UINT Defined (Example: IDR_PICTURE_RESOURCE)
// ~~~~~   ResourceType - Type Name (Example: "JPG")
//
// OutPut: TRUE If Succeeded...
// ~~~~~~
//-----------------------------------------------------------------------------
BOOL CPicture_Ex::Load(HINSTANCE hInstance,LPCTSTR lpszResourceName, LPCSTR ResourceType)
//=============================================================================
{
 HGLOBAL  hGlobal = NULL;
 HRSRC  hSource = NULL;
 LPVOID  lpVoid  = NULL;
 int   nSize   = 0;
 BOOL  bResult=FALSE;
 if(m_pPict != NULL) UnloadPicture(); // Important - Avoid Leaks...



 hSource = FindResource(hInstance, lpszResourceName, ResourceType);



 if(hSource == NULL)
  {
  HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
  MessageBoxEx(hWnd, "FindResource() Failed\t", "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
  return(FALSE);
  }



 hGlobal = LoadResource(hInstance, hSource);
 if(hGlobal == NULL)
  {
  HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
  MessageBoxEx(hWnd, "LoadResource() Failed\t", "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
  return(FALSE);
  }



 lpVoid = LockResource(hGlobal);
 if(lpVoid == NULL)
  {
  HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
  MessageBoxEx(hWnd, "LockResource() Failed\t", "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
  return(FALSE);
  }



 nSize = (UINT)SizeofResource(hInstance, hSource);
 if(LoadPictureData((BYTE*)hGlobal, nSize)) bResult = TRUE;



 UnlockResource(hGlobal); // 16Bit Windows Needs This
 FreeResource(hGlobal); // 16Bit Windows Needs This (32Bit - Automatic Release)
 return(bResult);
}



//-----------------------------------------------------------------------------
// Does:   Open a File And Load It Into IPicture (Interface)
// ~~~~    (.BMP .DIB .EMF .GIF .ICO .JPG .WMF)
//
// InPut:  sFilePathName - Path And FileName Target To Save
// ~~~~~   
//
// OutPut: TRUE If Succeeded...
// ~~~~~~
//-----------------------------------------------------------------------------
BOOL CPicture_Ex::Load(CString sFilePathName)
//=============================================================================
{
 //if(!PathFileExists(sFilePathName))return FALSE;
/*
			CFile file;
			if (!file.Open(sFilePathName, CFile::modeRead/ *|CFile::shareDenyWrite* /))
				return FALSE;*/
		
		
 BOOL bResult = FALSE;
 CFile PictureFile;
 CFileException e;
 int nSize = 0;



 if(m_pPict != NULL) UnloadPicture(); // Important - Avoid Leaks...



 if(PictureFile.Open(sFilePathName, CFile::modeRead | CFile::typeBinary, &e))
  {
  nSize = PictureFile.GetLength();
  BYTE* pBuffer = new BYTE[nSize];
 
  if(PictureFile.Read(pBuffer, nSize) > 0)
   {
   if(LoadPictureData(pBuffer, nSize)) bResult = TRUE;
   }



  PictureFile.Close();
  delete [] pBuffer;
  }
 else // Open Failed...
  {
  TCHAR szCause[255];
  e.GetErrorMessage(szCause, 255, NULL);
  HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
  MessageBoxEx(hWnd, szCause, "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
  bResult = FALSE;
  }
 return(bResult);
}



//-----------------------------------------------------------------------------
// Does:   Read The Picture Data From a Source (File / Resource)
// ~~~~    And Load It Into The Current IPicture Object In Use
//
// InPut:  Buffer Of Data Source (File / Resource) And Its Size
// ~~~~~   
//
// OutPut: Feed The IPicture Object With The Picture Data
// ~~~~~~  (Use Draw Functions To Show It On a Device Context)
//         TRUE If Succeeded...
//-----------------------------------------------------------------------------
BOOL CPicture_Ex::LoadPictureData(BYTE *pBuffer, int nSize)
//=============================================================================
{
 BOOL bResult = FALSE;
 HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nSize);



 if(hGlobal == NULL)
  {
  HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
  MessageBoxEx(hWnd, "Can not allocate enough memory\t", "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
  return(FALSE);
  }



 void* pData = GlobalLock(hGlobal);
 memcpy(pData, pBuffer, nSize);
 GlobalUnlock(hGlobal);



 IStream* pStream = NULL;



 if(CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK)
  {
  HRESULT hr;
  if((hr = OleLoadPicture(pStream, nSize, FALSE, IID_IPicture, (LPVOID *)&m_pPict)) == E_NOINTERFACE)
   {
   HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
   MessageBoxEx(hWnd, "IPicture interface is not supported\t", "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
   return(FALSE);
   }
  else // S_OK
   {
   pStream->Release();
   pStream = NULL;
   bResult = TRUE;
   
   }
  }



 FreeResource(hGlobal); // 16Bit Windows Needs This (32Bit - Automatic Release)



 return(bResult);
}



//-----------------------------------------------------------------------------
// Does:   Draw The Loaded Picture Direct To The Client DC
// ~~~~
//
// Note:   Bigger OR Smaller Dimentions Than The Original Picture Size
// ~~~~    Will Draw The Picture Streached To Its New Given NEW Dimentions...
//
// InPut:  pDC - Given DC To Draw On
// ~~~~~   pSrcRect- Dimentions Of The Picture To Draw From(As a Rectangle)
//   DrawRect - Dimentions Of The Picture To Draw To(As a Rectangle)
// OutPut: TRUE If Succeeded...
// ~~~~~~
//-----------------------------------------------------------------------------
//=============================================================================



void CPicture_Ex::Render(CDC* pDC, LPRECT pDrawRect, LPRECT pSrcRect/*=NULL*/,LPCRECT prcWBounds/*=NULL*/)
{
    if (pDC == NULL || m_pPict == NULL) return ;
    
 CRect recrDest(pDrawRect);



    long Width  = 0;
    long Height = 0;
    m_pPict->get_Width(&Width);
    m_pPict->get_Height(&Height);



 CRect SrcRect(0,0,Width,Height);



 if(pSrcRect){
  SrcRect=*pSrcRect;
 }
 CRect DrawRect(pDrawRect);
    HRESULT hrP = NULL;



    hrP = m_pPict->Render(pDC->m_hDC,
                      DrawRect.left,                  // Left
                      DrawRect.top,                   // Top
                      DrawRect.Width(), // Right
                      DrawRect.Height(), // Bottom
                      SrcRect.left,
                      SrcRect.top,
                      SrcRect.Width(),
                      SrcRect.Height(),
                      prcWBounds);



    if (SUCCEEDED(hrP)) return;
 AfxThrowMemoryException();
    return;
}//-----------------------------------------------------------------------------
// Does:   Saves The Picture That Is Stored In The IPicture Object As a Bitmap
// ~~~~    (Converts From Any Known Picture Type To a Bitmap / Icon File)
//
// InPut:  sFilePathName - Path And FileName Target To Save
// ~~~~~
//
// OutPut: TRUE If Succeeded...
// ~~~~~~
//-----------------------------------------------------------------------------
BOOL CPicture_Ex::SaveAsBitmap(CString sFilePathName)
//=============================================================================
{
 BOOL bResult = FALSE;
 ILockBytes *Buffer = 0;
 IStorage   *pStorage = 0;
 IStream    *FileStream = 0;
 BYTE    *BufferBytes;
 STATSTG  BytesStatistics;
 DWORD  OutData;
 long  OutStream;
 CFile  BitmapFile; CFileException e;
 double  SkipFloat = 0;
 DWORD  ByteSkip = 0;
 _ULARGE_INTEGER RealData;



 CreateILockBytesOnHGlobal(NULL, TRUE, &Buffer); // Create ILockBytes Buffer



 HRESULT hr = ::StgCreateDocfileOnILockBytes(Buffer,
     STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &pStorage);



 hr = pStorage->CreateStream(L"PICTURE",
   STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, 0, &FileStream);



 m_pPict->SaveAsFile(FileStream, TRUE, &OutStream); // Copy Data Stream
 FileStream->Release();
 pStorage->Release();
 Buffer->Flush(); 



 // Get Statistics For Final Size Of Byte Array
 Buffer->Stat(&BytesStatistics, STATFLAG_NONAME);



 // Cut UnNeeded Data Coming From SaveAsFile() (Leave Only "Pure" Picture Data)
 SkipFloat = (double(OutStream) / 512); // Must Be In a 512 Blocks...
 if(SkipFloat > DWORD(SkipFloat)) ByteSkip = (DWORD)SkipFloat + 1;
 else ByteSkip = (DWORD)SkipFloat;
 ByteSkip = ByteSkip * 512; // Must Be In a 512 Blocks...
 
 // Find Difference Between The Two Values
 ByteSkip = (DWORD)(BytesStatistics.cbSize.QuadPart - ByteSkip);



 // Allocate Only The "Pure" Picture Data
 RealData.LowPart = 0;
 RealData.HighPart = 0;
 RealData.QuadPart = ByteSkip;
 BufferBytes = (BYTE*)malloc(OutStream);
 if(BufferBytes == NULL)
  {
  Buffer->Release();
  HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
  MessageBoxEx(hWnd, "Can not allocate enough memory\t", "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
  }



 Buffer->ReadAt(RealData, BufferBytes, OutStream, &OutData);



 if(BitmapFile.Open(sFilePathName, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite, &e))
  {
  BitmapFile.Write(BufferBytes, OutData);
  BitmapFile.Close();
  bResult = TRUE;
  }
 else // Write File Failed...
  {
  TCHAR szCause[255];
  e.GetErrorMessage(szCause, 255, NULL);
  HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
  MessageBoxEx(hWnd, szCause, "ERROR"/*ERROR_TITLE*/, MB_OK | MB_ICONSTOP, LANG_ENGLISH);
  bResult = FALSE;
  }
 
 Buffer->Release();
 free(BufferBytes);



 return(bResult);
}



LONG      CPicture_Ex::get_Height()
{
 LONG     nHeight = 0;



 if (m_pPict != NULL)
 {
  m_pPict->get_Height(&nHeight);
 }


 return nHeight;
}
LONG      CPicture_Ex::get_Width()
{
 LONG     nWidth = 0;



 if (m_pPict != NULL)
 {
  m_pPict->get_Width(&nWidth);
 }



 return nWidth;


}