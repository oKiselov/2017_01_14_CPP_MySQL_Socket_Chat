#include <thread>
#include <iostream>
#include "..\..\Headers\TCPClient.h"
#include "..\..\Headers\TCPException.h"
#include "..\..\Headers\Convertor.h"
#include "..\..\Headers\AuthenticationCleintController.h"
#include "..\..\Headers\ViewController.h"
#include "..\..\Headers\GlobalVariables.h"

namespace GlobalVariables
{
	SocketChat::TCPClient client; 

	// thread created by client for receiving messages 
	void WorkInDifferentThread(void);
}

int main(void)
{
	try
	{
		// Initialization of connection
		GlobalVariables::client.Initialize();

		SocketChat::ViewController::ShowText("Type settings connect to server: 1 - default(localhost:30001) or 2 - manual:");
		
		// incoming value of entrance mode 
		int iModeOfConnection = 0;
		do {
			try
			{
				std::string strVariant = SocketChat::ViewController::ReadText();
				iModeOfConnection = std::stoi(strVariant);
			}
			// exception doesnt break application 
			catch (const std::exception &ex)
			{
				std::cout << "Enter correct value!" << std::endl; 
			}
		} while (iModeOfConnection != GlobalVariables::iVariantConnection::defaultConnection
			&& iModeOfConnection != GlobalVariables::iVariantConnection::manualConnection);

		// First menu
		switch (iModeOfConnection)
		{
		case GlobalVariables::iVariantConnection::defaultConnection:
			break;
		case GlobalVariables::iVariantConnection::manualConnection:
		{
			std::cout << "Enter ip or name:";
			std::getline(std::cin, GlobalVariables::client.GetName());
			std::cout << "Enter port:";
			std::cin >> GlobalVariables::client.GetPort();
			break;
		}
		default:
			throw std::exception("Invalid argument");
		}

		// Setting connection 
		GlobalVariables::client.Connect();

		SocketChat::ViewController::ShowText("Press 1 if you want to log in, 2 - to register: ");

		// incoming value of entrance mode 
		int iModeOfEntrance = 0;
		do {
			try
			{
				std::string strLogReg = SocketChat::ViewController::ReadText();				
				iModeOfEntrance = std::stoi(strLogReg);
			}
			// exception doesnt break application 
			catch (const std::exception &ex)
			{
				std::cout << "Enter correct value!" << std::endl;
			}
		} while (iModeOfEntrance != GlobalVariables::iVariantConnection::defaultConnection
			&& iModeOfEntrance != GlobalVariables::iVariantConnection::manualConnection);


		// Authorization menu
		switch (iModeOfEntrance)
		{
			// Login process 
		case GlobalVariables::iEntrance::Login:
		{
			// variable for loop of login process
			while (true)
			{
				// creation of new Authorized User
				SocketChat::AuthentificationClientController User = SocketChat::AuthentificationClientController(SocketChat::AuthentificationClientController::Login());

				// Sending of name and password to server (int - size of name, string = name+password)

				std::vector<unsigned char> vecForMessage; 
				vecForMessage = SocketChat::Convertor::
					DataToVectorUC(User.GetName().size(), User.GetName() + User.GetPassword() + GlobalVariables::LogMode);
				GlobalVariables::client.Send(vecForMessage);

				// Receiving answer from server about results of authorization process 
				std::vector<unsigned char> vecMessageOfAuthorization(SocketChat::Limitation::sizeOfMessageBuffer);
				int sizeRecv = GlobalVariables::client.Receive(vecMessageOfAuthorization);
				vecMessageOfAuthorization.resize(sizeRecv);
				std::pair<int, std::string> infoAuth = SocketChat::Convertor::VectorUCToData(vecMessageOfAuthorization);

				// inspection of results 
				if (infoAuth.first == GlobalVariables::iAnswerAuthorizationQuery::Valid)
				{
					break;
				}
				SocketChat::ViewController::ShowText("Please, enter correct login and password!");
			}
			break;
		}

		//Registration process 
		case GlobalVariables::iEntrance::Register:
		{
			while (true)
			{
				// creation of User for its registration 
				SocketChat::AuthentificationClientController User = SocketChat::AuthentificationClientController(SocketChat::AuthentificationClientController::Login());

				GlobalVariables::client.Send(SocketChat::Convertor::
					DataToVectorUC(User.GetName().size(), User.GetName() + User.GetPassword() + GlobalVariables::RegMode));

				// receiving information with results of authorization
				std::vector<unsigned char> vecMessageOfAuthorization(SocketChat::Limitation::sizeOfMessageBuffer);
				int sizeRecv = GlobalVariables::client.Receive(vecMessageOfAuthorization);
				vecMessageOfAuthorization.resize(sizeRecv);
				std::pair < int, std::string> infoAuth = SocketChat::Convertor::VectorUCToData(vecMessageOfAuthorization);

				if (infoAuth.first == 1)
				{
					break;
				}
				SocketChat::ViewController::ShowText("You have just entered engaged login. Try again!");
			}
			break;
		}
		default:
			throw std::exception("Invalid argument");
		}

		SocketChat::ViewController::ShowText("[Enter command 'exit' to leave chat]");

		std::thread th(GlobalVariables::WorkInDifferentThread);

		while (true)
		{
			std::string strText = SocketChat::ViewController::ReadText();
			if (strText.size() > SocketChat::Limitation::sizeOfMessageBuffer)
			{
				strText.resize(SocketChat::Limitation::sizeOfMessageBuffer);
			}
			if (strText == "exit")
				break;
			GlobalVariables::client.Send(
				SocketChat::Convertor::DataToVectorUC(SocketChat::StatusType::MessageWasSended,
					strText));
		}
		GlobalVariables::client.Disconnect();
		th.join();
	}
	catch (const std::exception &ex)
	{
		SocketChat::ViewController::ShowText(ex.what());
	}

	return 0;
}

void GlobalVariables::WorkInDifferentThread(void)
{
	try
	{
		while (true)
		{
			std::vector<unsigned char> vec(SocketChat::Limitation::sizeOfMessageBuffer);

			int sizeRecv = GlobalVariables::client.Receive(vec);
			vec.resize(sizeRecv);

			std::pair<int, std::string> p = SocketChat::Convertor::VectorUCToData(vec);

			if (p.first == SocketChat::StatusType::MessageWasSended)
				SocketChat::ViewController::ShowText(p.second);
		}
	}
	catch (const std::exception &ex)
	{
		SocketChat::ViewController::ShowText(ex.what());
	}
}