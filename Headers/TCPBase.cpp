#include "TCPBase.h"

namespace SocketChat
{
	bool TCPBase::bInitialized = false; 
	
	WSADATA TCPBase::structWSADATA = { 0 }; 

	void TCPBase::CreateSocket(void)
	{
		this->CloseSocket(); 

		this->socket = ::socket(
			AF_INET,
			SOCK_STREAM,
			0);
		if (this->socket == SOCKET_ERROR)
		{
			throw TCPException("Creation socket error", ::WSAGetLastError());
		}
	}

	void TCPBase::CloseSocket(void)
	{
		if (this->socket)
		{
			::closesocket(this->socket);
		}
		this->socket = 0;
	}

	TCPBase::~TCPBase(void)
	{
	}

	void TCPBase::Initialize(void)
	{
		if (!TCPBase::bInitialized)
		{
			if(::WSAStartup(MAKEWORD(1,1), &TCPBase::structWSADATA))
			{
				throw TCPException("WSAStartup function failed", ::WSAGetLastError());
			}
			TCPBase::bInitialized = true;
		}
	}
	int TCPBase::Send(const std::vector<unsigned char>& vec) const
	{
		int iRet = ::send(
			this->socket,
			reinterpret_cast<const char*>(&vec[0]),
			vec.size(),
			0);
		if (iRet == SOCKET_ERROR)
		{
			throw TCPException("Sending function error", WSAGetLastError());
		}
		return iRet;
	}

	int TCPBase::Receive(std::vector<unsigned char>&vec) const
	{
		int iRet = ::recv(
			this->socket,
			reinterpret_cast<char*>(&vec[0]),
			vec.size(),
			0);
		if(iRet==SOCKET_ERROR)
		{
			throw TCPException("Receiving function error", WSAGetLastError());
		}
		return iRet;
	}
	std::string & TCPBase::GetIPAdress(void) throw()
	{
		return this->strIPadress; 
	}
	const std::string & TCPBase::GetIPAdress(void) const throw()
	{
		return this->strIPadress;
	}
	int & TCPBase::GetPort(void) throw()
	{
		return this->iPort;
	}
	const int & TCPBase::GetPort(void) const throw()
	{
		return this->iPort; 
	}

	bool SocketChat::TCPBase::IsConnected(void) const throw()
	{
		return !(this->socket == SOCKET_ERROR || this->socket == INVALID_SOCKET || !this->socket);
	}

	void TCPBase::ClearFields(void)
	{
		this->iPort = 0;
		this->socket = NULL;
		this->strIPadress = "";
		this->bInitialized = NULL; 
		this->structWSADATA = {};
	}

}