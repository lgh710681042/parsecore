#pragma once
#include <mutex>
#include "NDHttp.h"
#include "NDHttpBo.h"

struct _stChunk
{
	UINT nIndex;
	ULONGLONG ullSize;
};

namespace NDHttp
{
	class CNDHttpDownBuilderBiz;
	class CNDHttpUploadBuilderBiz;
	//////////////////////////////////////////////////////////////////////////
	class CHttpRequestData : public CNDHttpBo, public IHttpRequestData
	{
	public:
		CHttpRequestData(CHttpRequestDataModel* pModel);
		~CHttpRequestData();

	public:
		virtual DWORD Excute();
		virtual DWORD GetHttpCode();
		virtual LPCSTR GetHttpHeader();
		virtual LPCSTR GetResult();
		virtual DWORD GetLength()	{ return m_nRecvBufferSize; }
		virtual LPCTSTR GetErrorDescritpion() { return m_strErrorDescription.c_str(); }

		void  SetErrorDescritpion(wstring strError);
		void  Release();
	protected:
		static size_t	GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		static size_t	GetHttpHeaderCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		size_t ProgrossCallBack(void *ptr, size_t size, size_t nmemb, void *userp);

	private:
		char*	m_pBuffer; // recv buffer
		int		m_nBufferSize;
		int		m_nRecvBufferSize;

		DWORD	m_dwHttpCode;
		wstring m_strErrorDescription;
		string  m_strHttpHeader;
	};

	//////////////////////////////////////////////////////////////////////////
	class CHttpRequestFile : public CNDHttpBo, public IHttpRequestFile
	{
	public:
		enum { NORAML, PAUSE, STOP };
	public:
		CHttpRequestFile(CHttpRequestFileModel* pModel);
		~CHttpRequestFile();

	public:
		virtual DWORD Excute();
		virtual void Cancel();
		virtual void Pause();
		virtual void Resume();
		virtual LPCTSTR GetErrorDescription()	{ return m_strErrorDescription.c_str(); }
		virtual ULONGLONG	GetFileSize()		{ return m_ullFileSize; };
		void  Release();

		void	SetLocalFilePath(wstring wstrLocalFilePath)		{ m_wstrLocalFilePath = wstrLocalFilePath; }
		wstring& GetLocalFilePath()			{ return m_wstrLocalFilePath; }

		void	SetStatus(DWORD	dwStatus)	{ m_dwStatus = dwStatus; }
		DWORD	GetStatus()					{ return m_dwStatus; }

		ULONGLONG	GetLastFileSizePos();
		
		void  SetConfPath();
		
		void SetNDHttpBuilderBiz(CNDHttpDownBuilderBiz*	pNDHttpBuilderBiz) { m_pNDHttpBuilderBiz = pNDHttpBuilderBiz; }
		CNDHttpDownBuilderBiz* GetNDHttpBuilderBiz() { return m_pNDHttpBuilderBiz; }

	protected:
		static size_t	GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		static size_t	GetHttpHeaderCallBack(void *ptr, size_t size, size_t nmemb, void *userp);

		size_t StartCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		size_t ProgrossCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		bool   CompleteCallBack(CURLcode code);
		void   ReleaseFile();

		void	SetErrorDescription(wstring strErrorDescription);

	private:
		DWORD		m_dwHttpCode;			//HttpCode
		ULONGLONG	m_ullDownloadTotalSize;	//������Ҫ���ص��ļ���С
		ULONGLONG	m_ullFileSize;			//ʵ���������ļ���С
		ULONGLONG	m_ullCurDownloadSize;	//��ǰ�����ش�С
		ULONGLONG	m_ullDownloadTotalSizeInConfig;//�����м�¼���ܴ�С����Ҫ���ڶԱȷ����������ص��ļ��Ƿ��е���

		ULONGLONG	m_ullLastFileSize;		//�ϵ�������ʼλ��

		HANDLE	m_hNdfFile;				//Config·��
		HANDLE	m_hNdsFile;				//�����ļ�·��

		DWORD	m_dwStartTime;			//���ؿ�ʼʱ��
		DWORD	m_dwLastOnProgressTime; //��¼�ϴλص�ʱ��

		wstring	m_strNdfFile;			//Config�����ļ����
		wstring	m_strNdsFile;			//�����ļ����

		DWORD	m_dwStatus;				//����״̬ NORAML, PAUSE, STOP
		wstring	m_strErrorDescription;	//ʧ�ܴ�������

		wstring m_wstrLocalFilePath;	//���ص����ص��ļ�·��

		CNDHttpDownBuilderBiz*	m_pNDHttpBuilderBiz;

		float	m_fSpeed;			//�������һ�ε������ٶ�

		std::mutex mtx;           // mutex for critical section
	};

	//////////////////////////////////////////////////////////////////////////
#define CHUNKSIZE ( 1024 * 1024 )
	class CHttpUploadFile : public CNDHttpBo, public IHttpUploadFile
	{
	public:
		enum { NORAML, PAUSE, STOP };
	public:
		CHttpUploadFile(CHttpUploadFileModel* pModel);
		~CHttpUploadFile();

	public:
		virtual DWORD Excute();
		virtual void Cancel();
		virtual void Pause();
		virtual void Resume();
		virtual LPCSTR GetResult();

		void  Release();

		void	SetLocalFilePath(wstring wstrLocalFilePath)		{ m_wstrLocalFilePath = wstrLocalFilePath; }
		wstring& GetLocalFilePath()			{ return m_wstrLocalFilePath; }

		void	SetServerFilePath(wstring wstrServerFilePath)	
		{ 
			m_wstrServerFilePath = wstrServerFilePath;
			if (!m_wstrServerFilePath.empty())
			{
				WCHAR wc = m_wstrServerFilePath.back();
				if (wc != _T('/'))
					m_wstrServerFilePath += _T("/");
			}
		}
		wstring& GetServerFilePath()			{ return m_wstrServerFilePath; }

		void	SetFileName(wstring wstrFileName)	{ m_wstrFileName = wstrFileName; }
		wstring& GetFileName()				{ return m_wstrFileName; }

		void	SetStatus(DWORD	dwStatus)	{ m_dwStatus = dwStatus; }
		DWORD	GetStatus()					{ return m_dwStatus; }

        void    SetChunkUpload(bool bChunkUpload)   { m_bChunkUpload = bChunkUpload; }
        DWORD	GetChunkUpload()					{ return m_bChunkUpload; }

		void		SetFileSize(ULONGLONG ullFileSize);
		ULONGLONG	GetFileSize();

		void	SetErrorDescription(wstring strError);
		LPCTSTR GetErrorDescription()	{ return m_strErrorDescription.c_str(); }

		void SetNDHttpBuilderBiz(CNDHttpUploadBuilderBiz*	pNDHttpBuilderBiz) { m_pNDHttpBuilderBiz = pNDHttpBuilderBiz; }
		CNDHttpUploadBuilderBiz* GetNDHttpBuilderBiz() { return m_pNDHttpBuilderBiz; }
	protected:
		static size_t	GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		static size_t	UploadCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

		size_t ResponseCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		size_t ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

		void   ReleaseFile();
	private:
		DWORD	m_dwStatus;				//����״̬ NORAML, PAUSE, STOP

		wstring m_wstrLocalFilePath;	//�����ϴ��ļ�·��
		wstring m_wstrServerFilePath;	//remote server file save path
		wstring m_wstrFileName;

		char*	m_pBuffer; // recv buffer
		int		m_nBufferSize;
		int		m_nRecvBufferSize;

		HANDLE	m_hFile;				//�ϴ��ļ����

		wstring	m_strErrorDescription;	//ʧ�ܴ�������

		DWORD	m_dwLastTime;			//��¼�ϴλص�ʱ��
		DWORD	m_dwStartTime;			//��������ʼʱ��
		ULONGLONG	m_ullFileSize;		//�ϴ��ļ���С
		ULONGLONG	m_ullUploadFileSize;//
		ULONGLONG	m_ullProgressSize;

		CNDHttpUploadBuilderBiz*	m_pNDHttpBuilderBiz;

		std::mutex mtx;           // mutex for critical section
		UINT m_nChunkIndex;
		UINT m_nChunkCount;
		std::string m_strFileMD5;
        bool m_bChunkUpload = true;
	};
}
