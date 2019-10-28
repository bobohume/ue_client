#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_

#include <string>
#include <list>

#include "Socket/Socket.h"
#include "TcpSocket.h"
#include "Base/bitStream.h"
#include "message/Packet.h"

#ifndef _WIN32
#include "pthread.h"
#endif

namespace WinTcp{
	#define MAX_VERTIFY_CACHE_PACKET        10
	#define MAX_CACHE_PACKET                30
	class ClientSocket : public CTcpSocket
	{
	public:
		ClientSocket();
		virtual ~ClientSocket();

		static ClientSocket* Instance(void)
		{
			static ClientSocket local;
			return &local;
		}

		//CTcpSocket ·ÏÆú½Ó¿Ú=============================
		bool Initialize();
		bool Start();
		bool Stop();
		bool Restart() { return false; };
		int  Connect(const char* szServerAddr, int nServerPort);
		bool Send(::google::protobuf::Message* packet);
		bool Send(const char* buffer, int bufferLen);
		bool Disconnect();
		bool Loop();

	protected:
		void OnDisconnect();
		void OnConnect(int) { return; };
		virtual void ReceivePacket(const char *pBuf, int nBufferSize);

	public:
		virtual void	update(float dt);
		virtual void	Release(void);
		void OnConnected();
		virtual         void			Close(void);

	private:
		bool				Select(void);
		bool				ProcessExcept(void);
		bool				ProcessInput(void);
		bool				ProcessOutput(void);

	private:
		fd_set				m_ReadFD;
		fd_set				m_WriteFD;
		fd_set				m_ExceptFD;
		///SOCKET
		Socket				m_Socket;
		bool				m_isConnecting;
		bool                m_sendConnected;
		bool				m_isConnected;
		bool				m_isDisConnected;


#ifdef _WIN32
		static DWORD WINAPI	 _LoopThread(LPVOID data);
#else
		static void*	_LoopThread(void *data);
#endif

#ifdef _WIN32
		HANDLE				m_hLoopThread;
#else
		pthread_t			m_hLoopThread;
#endif
	};

#define  CLIENT_TCP ClientSocket::Instance()
}
#endif