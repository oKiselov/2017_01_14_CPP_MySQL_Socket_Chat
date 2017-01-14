#include "TCPServer.h"
#include "GlobalVariables.h"

void SocketChat::TCPServer::SetConnection(void)
{
	TCPBase::CreateSocket(); 

	this->Bind(); 

	this->Listen(); 
}

void SocketChat::TCPServer::CloseConnection(void)
{
	TCPBase::CloseSocket();
}

SOCKET SocketChat::TCPServer::Accept(void) const
{
	sockaddr_in structClient_addr = { 0 }; 
	int sizeClient_addr = sizeof structClient_addr; 

	SOCKET currSocket = accept(
		TCPBase::socket,
		reinterpret_cast<sockaddr*>(&structClient_addr),
		&sizeClient_addr); 
	if(currSocket == INVALID_SOCKET)
	{
		throw TCPException("Acception function error", WSAGetLastError());
	}
	return currSocket;
}

void SocketChat::TCPServer::Bind(void)
{
	sockaddr_in structServer_addr = { 0 }; 
	structServer_addr.sin_family = AF_INET; 
	structServer_addr.sin_port = htons(TCPBase::iPort);
	structServer_addr.sin_addr.s_addr = TCPBase::strIPadress.length() ? inet_addr(TCPBase::strIPadress.c_str()) : 0;

	if(bind(
		TCPBase::socket, 
		reinterpret_cast<sockaddr*>(&structServer_addr),
		sizeof structServer_addr)==SOCKET_ERROR)
	{
		throw TCPException("Binding function error", WSAGetLastError());
	}
}

void SocketChat::TCPServer::Listen(void)
{
	if(listen(
		TCPBase::socket, 
		GlobalVariables::iMaxSizeOfMessage)
		==SOCKET_ERROR)
	{
		throw TCPException("Listening function error", WSAGetLastError());
	}
}
