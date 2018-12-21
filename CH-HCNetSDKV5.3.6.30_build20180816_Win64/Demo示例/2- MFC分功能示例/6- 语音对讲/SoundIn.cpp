
// SoundIn.cpp: implementation of the CSoundIn class.
// 描述：音频采集
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoundIn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundIn::CSoundIn()
{
	m_pWaveHead = NULL;
	m_QueuedBuffers = 0;
	m_hRecord = NULL;
	m_bRecording = FALSE;
	DataFromSoundIn = NULL;
}

CSoundIn::~CSoundIn()
{
	if (m_bRecording)
	{
		Stop();
	}
}


BOOL CSoundIn::Start(WAVEFORMATEX* format, DWORD nBufNum, DWORD nBufSize)
{
	if (m_bRecording || DataFromSoundIn == NULL)
	{
		TRACE("m_bRecording || DataFromSoundIn == NULL:m_bRecording:%d", m_bRecording);
		return FALSE;
	}

	MMRESULT mmReturn = 0;
	int i = 0;
	
	m_nBufSize = nBufSize;
	m_nBufNum = nBufNum;
	
	if (format != NULL)
	{
		m_Format = *format;
	}
	
	mmReturn = ::waveInOpen( &m_hRecord, WAVE_MAPPER, &m_Format, (DWORD)waveInProc, (DWORD)this, CALLBACK_FUNCTION);
	if (mmReturn)
	{
		waveInErrorMsg(mmReturn, "in Start()");
		if (mmReturn == MMSYSERR_ALLOCATED)
		{
			TRACE("!waveInOpen:mmReturn:%d",mmReturn);
		}
		return FALSE;
	}
	
	m_pWaveHead = new WAVEHDR[m_nBufNum];
	if (m_pWaveHead == NULL)
	{
		TRACE("m_pWaveHead == NULL");
		return NULL;
	}

	for (i=0; i<(INT)m_nBufNum; i++)
	{
		ZeroMemory(&m_pWaveHead[i], sizeof(WAVEHDR));
		m_pWaveHead[i].lpData = new char [m_nBufSize];
		m_pWaveHead[i].dwBufferLength = m_nBufSize;
		AddInputBufferToQueue(&m_pWaveHead[i]);
	}
	
	mmReturn = ::waveInStart(m_hRecord);
	if (mmReturn)
	{
		waveInErrorMsg(mmReturn, "in Start()");
		return FALSE;
	}

	m_bRecording = TRUE;
	return TRUE;
}


void CSoundIn::Stop()
{
	MMRESULT mmReturn = MMSYSERR_NOERROR;
	int i = 0;
	if (m_bRecording)
	{
		m_bRecording = FALSE;
		::waveInReset(m_hRecord);
		
		if (m_pWaveHead)
		{
			for (i=0; i<(INT)m_nBufNum; i++)
			{				
				mmReturn = ::waveInUnprepareHeader(m_hRecord, &m_pWaveHead[i], sizeof(WAVEHDR));
				if (mmReturn)
				{
					TRACE("waveInUnprepareHeader failed:%d", mmReturn);
				}				
				delete[] m_pWaveHead[i].lpData;
				m_QueuedBuffers--;
			}
			delete[] m_pWaveHead;
			m_pWaveHead=NULL;
		}
		mmReturn = ::waveInClose(m_hRecord);
		if (mmReturn)
		{
			TRACE("waveInClose failed:%d:%d", mmReturn, m_QueuedBuffers);
			waveInErrorMsg(mmReturn, "in Stop()");
		}
	}
}

//音频采集回调函数
void CALLBACK CSoundIn::waveInProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	ASSERT(dwInstance);
	CSoundIn*pOwner = (CSoundIn*)dwInstance;
	if (!pOwner->m_bRecording)
	{
		return;
	}

	MMRESULT mmReturn = 0;
	LPWAVEHDR pHdr = (LPWAVEHDR) dwParam1;

	switch (uMsg)
	{
	case WIM_DATA:		
		//TRACE("waveInProc[%d]\n", pHdr->dwBytesRecorded);
		(pOwner->DataFromSoundIn)(pHdr->lpData, pHdr->dwBytesRecorded, pOwner->m_dwUser);
		
		if (pOwner->m_bRecording)
		{			
			// add the input buffer to the queue again
			mmReturn = ::waveInAddBuffer(pOwner->m_hRecord, pHdr, sizeof(WAVEHDR));
			if (mmReturn) 
			{
				waveInErrorMsg(mmReturn, "in OnWIM_DATA()");
			}
		}		
		break;
	default:
		TRACE("other msg\n");
		break;
	}
}

//添加缓存
int CSoundIn::AddInputBufferToQueue(WAVEHDR *pHdr)
{
	MMRESULT mmReturn = 0;

	// prepare it
	mmReturn = ::waveInPrepareHeader(m_hRecord, pHdr, sizeof(WAVEHDR));
	if (mmReturn)
	{
		waveInErrorMsg(mmReturn, "in AddInputBufferToQueue()");
		return m_QueuedBuffers;
	}
	
	// add the input buffer to the queue
	mmReturn = ::waveInAddBuffer(m_hRecord, pHdr, sizeof(WAVEHDR));
	if (mmReturn)
	{
		waveInErrorMsg(mmReturn, "in AddInputBufferToQueue()");
		return m_QueuedBuffers;
	}
	// no error
	// increment the number of waiting buffers
	return ++m_QueuedBuffers;
}
//错误代码
void CSoundIn::waveInErrorMsg(MMRESULT result, LPCTSTR addstr)
{
	char errorbuffer[100];
	waveInGetErrorText(result, errorbuffer,100);
}

//设置回调函数
void CSoundIn::SetSoundInDataCB(void (CALLBACK *SoundInCB)(char*,DWORD,DWORD), DWORD dwUser)
{
	DataFromSoundIn=SoundInCB;
	m_dwUser=dwUser;
}