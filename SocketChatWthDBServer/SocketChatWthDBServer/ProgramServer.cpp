#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>
#include "..\..\Headers\TCPServer.h"
#include "..\..\Headers\TCPClient.h"
#include "..\..\Headers\TCPException.h"
#include "..\..\Headers\Convertor.h"
#include "..\..\Headers\GlobalVariables.h"
#include "..\..\Headers\SocketChatDataProvider.h"
#include "..\..\Headers\ViewController.h"

/*
Работа с БД:

1. При входе 	- авторизация и проверка
- логинимся новым именем и проверка
chat_users;

2. После входа 	- трекер активности
chat_activity; where chat_users login;

3. При сообщениях
chat_messages; where chat_users login;

4. При выходе 	- трекер активности
chat_activity; where chat_users login;

*/

namespace GlobalVariables
{
	std::mutex mtx; 

	std::vector<SocketChat::TCPClient> vec(SocketChat::Limitation::connectedClients);
	
	// thread created by server for each socket 
	void WorkInDifferentThread(const size_t&);
}

int main()
{
	try
	{
		SocketChat::TCPBase::Initialize(); 
		SocketChat::TCPServer server; 
		server.SetConnection();

		while(true)
		{
			try
			{
				// acceptation of incoming socket 
				SocketChat::TCPClient client(server.Accept());



				// start point of sync
				GlobalVariables::mtx.lock(); 

				auto itFind = std::find_if(
					GlobalVariables::vec.begin(), 
					GlobalVariables::vec.end(), 
					[](const SocketChat::TCPClient &currClient)
				{
					return !currClient.IsConnected(); 
				}); 

				if(itFind == GlobalVariables::vec.cend())
				{
					client.Disconnect(); 
				}

				else
				{
					*itFind = std::move(client); 

					// creation of different thread 
					std::thread directThread(
						GlobalVariables::WorkInDifferentThread,
						std::distance(GlobalVariables::vec.begin(),
						itFind));
					directThread.detach(); 
				}

				// end point of sync
				GlobalVariables::mtx.unlock(); 
			}
			catch(const SocketChat::TCPException &ex)
			{
				SocketChat::ViewController::ShowText(ex.what());
			}
		}
	}
	catch(const std::exception &ex)
	{
		SocketChat::ViewController::ShowText(ex.what());
	}
	
	return 0;
}

void GlobalVariables::WorkInDifferentThread(const size_t &i)
{
	size_t index = i;

	//DataProvider initialization 
	SocketChat::SocketChatDataProvider dataBase;
	dataBase.Initialize();
	dataBase.SetConnection();

	// variables for authorization 
	int iTypeOfAnswer = 0;
	std::string strClientName, strClientPassword;
	std::pair<int, std::string> infoAuth;
	std::vector<unsigned char> vecAuthInfo;

	try
	{
		// loop is working 
		// till authorization won't be completed 
		while (iTypeOfAnswer != GlobalVariables::iAnswerAuthorizationQuery::Valid)
		{
			vecAuthInfo.resize(SocketChat::Limitation::sizeOfMessageBuffer);
			int sizeRecv = 0;

			sizeRecv = vec[index].Receive(vecAuthInfo);

			vecAuthInfo.resize(sizeRecv);

			infoAuth = SocketChat::Convertor::VectorUCToData(vecAuthInfo);

			// inspection of incoming information about login, password 
			std::string strModeOfAuthorization;
			strModeOfAuthorization.assign(infoAuth.second.end() - 4, infoAuth.second.end());

			strClientName.assign(infoAuth.second.begin(), infoAuth.second.begin() + infoAuth.first);
			strClientPassword.assign(infoAuth.second.begin() + infoAuth.first, infoAuth.second.end() - 4);

			// point of locking the process with database 
			GlobalVariables::mtx.lock();
			if (strModeOfAuthorization.c_str() == GlobalVariables::RegMode)
			{
				if (!dataBase.CheckUser(strClientName, strClientPassword))
				{
					iTypeOfAnswer = GlobalVariables::iAnswerAuthorizationQuery::Valid;
					// insert info about new user into DB 
					dataBase.InsertIntoUsers(strClientName, strClientPassword);
				}
				else
				{
					iTypeOfAnswer = GlobalVariables::iAnswerAuthorizationQuery::Invalid;
				}
			}

			else if (strModeOfAuthorization.c_str() == GlobalVariables::LogMode)
			{
				if (!dataBase.CheckUser(strClientName, strClientPassword))
				{
					iTypeOfAnswer = GlobalVariables::iAnswerAuthorizationQuery::Invalid;
				}
				else
				{
					iTypeOfAnswer = GlobalVariables::iAnswerAuthorizationQuery::Valid;
					for (int i = 0; i < GlobalVariables::vec.size(); i++)
					{
						if (GlobalVariables::vec[i].GetName() == strClientName)
						{
							iTypeOfAnswer = GlobalVariables::iAnswerAuthorizationQuery::Invalid;
							break;
						}
					}
				}
			}
			else
			{
				throw std::exception("Invalid authorization sign");
			}
			// point of unlocking the process with database 
			GlobalVariables::mtx.unlock();

			std::vector<unsigned char> vec_answer(SocketChat::Limitation::sizeOfMessageBuffer);
			vec_answer = SocketChat::Convertor::DataToVectorUC(iTypeOfAnswer, GlobalVariables::LogMode.c_str());
			GlobalVariables::vec[index].Send(vec_answer);
		}


		// point of locking the process with database 
		GlobalVariables::mtx.lock();
		// insert to DB information about start point of activity 
		dataBase.StartActivity(std::string(infoAuth.second.begin(), infoAuth.second.begin() + infoAuth.first));
		// point of unlocking the process with database 
		GlobalVariables::mtx.unlock();

		vec[index].SetName(strClientName);


		while (true)
		{
			std::vector<unsigned char> vecMessage(SocketChat::Limitation::sizeOfMessageBuffer);

			int sizeRecv = GlobalVariables::vec[index].Receive(vecMessage);
			vecMessage.resize(sizeRecv);

			std::pair<int, std::string> p = SocketChat::Convertor::VectorUCToData(vecMessage);

			std::ostringstream os;
			if (p.first == SocketChat::StatusType::JoinChat)
			{
				os << "Chat in " << (GlobalVariables::vec[index].GetName() = p.second);
			}
			else
			{
				os << "Message from " << GlobalVariables::vec[index].GetName().c_str() << ":" << p.second;
				// insert information about current message int DB 
				// point of locking the process with database 
				GlobalVariables::mtx.lock();
				dataBase.InsertIntoMessages(GlobalVariables::vec[index].GetName(), p.second);
				// point of unlocking the process with database 
				GlobalVariables::mtx.unlock();
			}

			vecMessage = SocketChat::Convertor::DataToVectorUC(SocketChat::StatusType::MessageWasSended,
				os.str());

			GlobalVariables::mtx.lock();
			for (size_t i = 0; i < GlobalVariables::vec.size(); i++)
			{
				if (i != index && GlobalVariables::vec[i].IsConnected())
				{
					try
					{
						GlobalVariables::vec[i].Send(vecMessage);
					}
					catch (const SocketChat::TCPException)
					{
						continue;
					}
				}
			}
			GlobalVariables::mtx.unlock();
		}
	}
	catch (const std::exception &ex)
	{
		SocketChat::ViewController::ShowText(ex.what());
		// point of locking the process with database 
		GlobalVariables::mtx.lock();
		dataBase.FinishActivity(GlobalVariables::vec[index].GetName());
		GlobalVariables::mtx.unlock();
		// erase vector 
		GlobalVariables::vec[index].Clear();
	}
}