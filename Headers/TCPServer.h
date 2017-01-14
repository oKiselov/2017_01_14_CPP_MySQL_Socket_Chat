#pragma once
#include "TCPBase.h"

namespace SocketChat
{
	// class inherits from base class TCPBase
	class TCPServer: public TCPBase
	{
	public:

		TCPServer (
			const std::string &strName = std::string(), 
			const int &iPort = Ports::Default)
			:TCPBase(strName, iPort){}

		virtual ~TCPServer() {};

		// Method runs other functions from direct class to set socket connection 
		void SetConnection(void); 

		// Method closes socket connection 
		void CloseConnection(void);

		/*		ACCEPT		
		The accept function permits an incoming connection attempt on a socket

		SOCKET accept(
		_In_    SOCKET          s,
		_Out_   struct sockaddr *addr,
		_Inout_ int             *addrlen
		);
		// Method runs method accept and creates connection 
		// with direct sicket 
		*/
		SOCKET Accept(void) const; 

	protected:

		/*		BINDING		
		The bind function associates a local address with a socket.
		int bind(
		_In_ SOCKET                s,		- A descriptor identifying an unbound socket.
		_In_ const struct sockaddr *name,	- A pointer to a sockaddr structure
		of the local address to assign to the bound socket.
		_In_ int                   namelen	- The length, in bytes, of the value pointed to
		by the name parameter
		);
		If no error occurs, bind returns zero
		*/
		// Method creates and fills all gaps in specified structure 
		void Bind(void); 

		/*		LISTENING		 
		The listen function places a socket in a state in which
		it is listening for an incoming connection

		int listen(
		_In_ SOCKET s,			- descriptor identifying a bound, unconnected socket
		_In_ int    backlog		- The maximum length of the queue of pending connections
		);

		If no error occurs, listen returns zero.
		// Method runs Barckley's socket function listen in active mode 
		*/
		void Listen(void);
	};
}