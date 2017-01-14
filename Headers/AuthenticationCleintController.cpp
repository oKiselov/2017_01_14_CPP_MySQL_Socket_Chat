#include "AuthenticationCleintController.h"
#include "ViewController.h"

SocketChat::AuthentificationClientController::AuthentificationClientController(std::string strName, std::string strPassword)
{
	this->strName = strName; 
	this->strPassword = strPassword;
}

SocketChat::AuthentificationClientController::AuthentificationClientController(AuthentificationClientController& User):strName(User.strName), strPassword(User.strPassword)
{
}

SocketChat::AuthentificationClientController::AuthentificationClientController(LoginPassword& User):strName(User.strName), strPassword(User.strPassword)
{
}


SocketChat::AuthentificationClientController::~AuthentificationClientController(void)
{
}

std::string SocketChat::AuthentificationClientController::GetName(void)const
{
	return this->strName;
}

std::string SocketChat::AuthentificationClientController::GetPassword(void)const
{
	return this->strPassword;
}

SocketChat::LoginPassword SocketChat::AuthentificationClientController::Login(void)
{
	ViewController::ShowText("Enter user's name: ");
	std::string strLogin = ViewController::ReadText();
	ViewController::ShowText("Enter user's password: ");
	std::string strPassword = ViewController::ReadText();
	return LoginPassword{ strLogin, strPassword };
}
