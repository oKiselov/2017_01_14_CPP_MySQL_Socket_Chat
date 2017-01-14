#pragma once
#include <exception>
#include <string>
#include <sstream>

namespace SocketChat
{
	// direct class for exception handling 
	class TCPException: public std::exception
	{
		int iCodeError = 0; 

		std::string strErrorMessage; 

	public:

		// parameterless constructor 
		TCPException(){};

		// Constructor with parameters
		TCPException(const std::string &strMessage, const int &iCode)
			:exception(strMessage.c_str()), iCodeError(iCode)
		{
			std::ostringstream os; 
			os << exception::what() << ", error code = " << this->iCodeError;
			this->strErrorMessage = os.str();
		}

		// Constructor with parameters for dataprovider 
		TCPException(const std::string &strMessage) :exception(strMessage.c_str())
		{
			std::ostringstream os; 
			os << exception::what();
			this->strErrorMessage = os.str();
		}

		virtual ~TCPException() {}; 

		// override of exception-classes function what()
		// describe message about error 
		const char * what(void)const override
		{
			return this->strErrorMessage.c_str();
		}
	};
}