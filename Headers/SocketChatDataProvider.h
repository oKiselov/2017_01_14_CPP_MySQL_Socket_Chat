#pragma once

#include "string"
#include "DataProvider.h"
#include <iostream>

namespace SocketChat
{
	// Class inherits methods from Base DataProvider and presents special methods 
	// to work with CHAT Data Base 
	class SocketChatDataProvider: public DataProvider 
	{
	public:

		SocketChatDataProvider(){};

		virtual ~SocketChatDataProvider(){};

		// method inserts info about new registered user into DB
		int InsertIntoUsers(std::string &strLogin, std::string &strPassword)const;

		// method checks information if user exists 
		bool CheckUser(std::string &strLogin, std::string &strPassword)const;

		// method inserts info about start point of activity in chat 
		int StartActivity(std::string &strLogin)const; 

		// method updates info about least point of activity in chat 
		int FinishActivity(std::string &strLogin) const;

		// method collects all messages into current table 
		int InsertIntoMessages(std::string &strLogin, std::string &strMessage) const;

		// Function returns current datetime in UTC format 
		static std::string GetDateTimeUTC(void); 
	};
}
