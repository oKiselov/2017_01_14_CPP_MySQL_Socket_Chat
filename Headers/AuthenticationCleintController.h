#pragma once
#include <vector>
#include <string>

namespace SocketChat
{
	struct LoginPassword
	{
		std::string strName;
		std::string strPassword;
	};

	// Class for authorization process 
	class AuthentificationClientController
	{
	private:
		std::string strName;
		std::string strPassword;
		
	public:
		// Constructors 
		AuthentificationClientController(std::string strName, std::string strPassword);

		AuthentificationClientController(AuthentificationClientController &User);

		AuthentificationClientController(LoginPassword &User);

		AuthentificationClientController(void){}

		virtual ~AuthentificationClientController(void);

		std::string GetName(void)const; 

		std::string GetPassword(void)const;

		// Method returns structure with credentials 
		static LoginPassword Login(void); 
	};
}