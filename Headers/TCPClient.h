#pragma once
#include "TCPBase.h"

namespace SocketChat
{
	// class inherits from base class TCPBase
	class TCPClient : public TCPBase
	{
		std::string strClientName = std::string();

	public:

		explicit TCPClient(SOCKET currClientSocket);

		TCPClient(
			const std::string &strName = strNameDefault,
			const int &iPort = Ports::Default);

		TCPClient(TCPClient &alienClient)
		{
			TCPBase::socket = alienClient.socket;
			TCPBase::iPort = alienClient.iPort;
			TCPClient::strClientName = alienClient.strClientName;
		}

		virtual ~TCPClient(){} 

		/*
		The connect function establishes a connection to a specified socket.
		int connect(
		_In_ SOCKET                s,		- descriptor identifying an unconnected socket
		_In_ const struct sockaddr *name,	- pointer to the sockaddr structure to which the connection should be established.
		_In_ int                   namelen	- length, in bytes, of the sockaddr structure pointed to by the name parameter
		);

		If no error occurs, connect returns zero. Otherwise, it returns SOCKET_ERROR
		*/
		void Connect(void); 

		void Disconnect(void); 

		const TCPClient & operator = (TCPClient &&alienClient);

		std::string & GetName(void);

		const std::string & GetName(void) const;

		void SetName(std::string &strName);

		// Method clears all info about current socket 
		void Clear(void);

	};
}