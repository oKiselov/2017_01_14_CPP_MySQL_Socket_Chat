#pragma once

#include <Windows.h>
#include <Winsock.h>
#include <vector>
#include "TCPException.h"

#pragma comment(lib, "Ws2_32.lib")

namespace SocketChat
{
	/* GLOBAL VARIABLES */
	// PC's name by default 
	const std::string strNameDefault = "localhost"; 

	// connections ports
	const enum Ports {Default = 30001};

	// status of current user 
	const enum StatusType {JoinChat = 1, MessageWasSended=2, LeftChat=3}; 

	// the size of message, the amount of clients 
	const enum Limitation {sizeOfMessageBuffer = 1024, connectedClients = 10};

	class TCPBase
	{
		static bool bInitialized; 

		/*
		The WSADATA structure is used to store Windows Sockets
		initialization information returned by a call
		to the AfxSocketInit global function.

		struct WSAData {
		WORD wVersion;
		WORD wHighVersion;
		char szDescription[WSADESCRIPTION_LEN+1];
		char szSystemStatus[WSASYSSTATUS_LEN+1];
		unsigned short iMaxSockets;
		unsigned short iMaxUdpDg;
		char FAR* lpVendorInfo;
		};
		*/
		static WSADATA structWSADATA; 

	protected:
		// handler for socket 
		/*
		Implements the Berkeley sockets interface.
		The socket function creates a socket that is
		bound to a specific transport service provider.
		*/
		SOCKET socket = 0; 

		// adress and port of connection 
		std::string strIPadress = std::string(); 
		int iPort = 0; 
		
		// parameterless constructor 
		TCPBase(void){}

		//
		explicit TCPBase (SOCKET alienSocket) : socket(alienSocket){}

		// constructor with parameters 
		TCPBase(const std::string &strIP, const int &iPort) :
			strIPadress(strIP), iPort(iPort){}; 

		/*		CREATION		
		The socket function creates a socket that is bound
		to a specific transport service provider.

		SOCKET WSAAPI socket(
		_In_ int af,		- AF_INET = 2 = IPv4
		_In_ int type,		- SOCK_STREAM = 1 = two-way (TCP)
		_In_ int protocol	- If a value of 0 is specified,
		the caller does not wish to specify
		a protocol and the service provider
		will choose the protocol to use.
		);
		*/
		void CreateSocket(void);


		void CloseSocket(void);

	public:

		virtual ~TCPBase(void); 

		/*		INITIALIZATION	OF STRUCT	
		The WSAStartup function initiates use of the Winsock DLL by a process.

		int WSAStartup	(
		WORD      wVersionRequested,
		LPWSADATA lpWSAData
		);

		If successful, the WSAStartup function returns zero.
		The WSAStartup function directly returns the extended error code
		in the return value for this function. A call to the WSAGetLastError
		function is not needed and should not be used.
		*/
		static void Initialize(void);

		/*
		The send function sends data on a connected socket.
		int send(
			_In_       SOCKET s,	- descriptor identifying a connected socket
			_In_ const char   *buf,	- pointer to a buffer containing the data to be transmitted
			_In_       int    len,	- length, in bytes, of the data in buffer
			_In_       int    flags	- set of flags that specify the way in which the call is made
				);
		If no error occurs, send returns the total number of bytes sent, 
		which can be less than the number requested to be sent in the len parameter. 
		Otherwise, a value of SOCKET_ERROR is returned, and a specific error code 
		can be retrieved by calling WSAGetLastError.
		*/
		virtual int Send(const std::vector<unsigned char>&)const; 

		/*
		The recv function receives data from a connected socket or a bound connectionless socket.
		int recv(
		_In_  SOCKET s,		- descriptor that identifies a connected socket
		_Out_ char   *buf,	- pointer to the buffer to receive the incoming data
		_In_  int    len,	- length, in bytes, of the buffer pointed to by the buf parameter
		_In_  int    flags	- set of flags that influences the behavior of this function.
		);
		If no error occurs, recv returns the number of bytes received
		and the buffer pointed to by the buf parameter will contain this data received.
		If the connection has been gracefully closed, the return value is zero.
		*/
		virtual int Receive(std::vector<unsigned char>&)const;

		// Function returns current IP-Adress
		std::string& GetIPAdress(void) throw();

		// Function returns current IP-Adress as CONST VALUE 
		const std::string& GetIPAdress(void) const throw();

		// Function returns current Port number 
		int & GetPort(void)throw();

		// Function returns current Port number as CONST VALUE 
		const int& GetPort(void) const throw();

		// Function returns current status of socket
		bool IsConnected(void)const throw();

		// Method clears all information about current socket 
		void ClearFields(void);

	};
}