#include "TCPClient.h"

SocketChat::TCPClient::TCPClient(SOCKET currClientSocket) :TCPBase(currClientSocket)
{
}

SocketChat::TCPClient::TCPClient(const std::string & strName, const int & iPort) : TCPBase(strName, iPort)
{
}

void SocketChat::TCPClient::Connect(void)
{
	TCPBase::CreateSocket();

	sockaddr_in structServer_addr = { 0 }; 
	structServer_addr.sin_addr.s_addr = ::inet_addr(TCPBase::strIPadress.c_str());
	if(INADDR_NONE == structServer_addr.sin_addr.s_addr)
	{
		hostent *h = ::gethostbyname(TCPBase::strIPadress.c_str()); 
		if(!h)
		{
			throw TCPException("Getting host function error", WSAGetLastError());
		}

		structServer_addr.sin_addr = *reinterpret_cast<in_addr*>(h->h_addr_list[0]);
	}
	structServer_addr.sin_family = AF_INET; 
	structServer_addr.sin_port = ::htons(TCPBase::iPort);

	if(SOCKET_ERROR == connect(
		TCPBase::socket, 
		reinterpret_cast<sockaddr*>(&structServer_addr),
		sizeof structServer_addr))
	{
		throw TCPException("Connection to server error", WSAGetLastError());
	}
}

void SocketChat::TCPClient::Disconnect(void)
{
	TCPBase::CloseSocket();
}

const SocketChat::TCPClient & SocketChat::TCPClient::operator=(TCPClient && alienClient)
{
	{
		if (this == &alienClient)
		{
			return *this;
		}
		this->Disconnect();
		TCPBase::socket = alienClient.socket;
		TCPBase::iPort = alienClient.iPort;
		TCPClient::strClientName = alienClient.strClientName;
		alienClient.socket = 0;
		return *this;
	}
}

std::string & SocketChat::TCPClient::GetName(void)
{
	return this->strClientName;
}

const std::string & SocketChat::TCPClient::GetName(void) const
{
	return this->strClientName;
}

void SocketChat::TCPClient::SetName(std::string &strName)
{
	this->strClientName=strName;
}

void SocketChat::TCPClient::Clear(void)
{
	this->Disconnect();
	ClearFields();
	this->strClientName = "";
}