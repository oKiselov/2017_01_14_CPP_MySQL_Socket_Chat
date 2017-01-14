#include "SocketChatDataProvider.h"
#include <ctime>
#include "TCPException.h"


int SocketChat::SocketChatDataProvider::InsertIntoUsers(std::string & strLogin, std::string & strPassword)const
{
	std::ostringstream osToFillUser;
	osToFillUser << "INSERT INTO " << GlobalDataVariables::strUsersTable
		<< " (login, password, date)"
		<< " VALUES('"
		<< strLogin.c_str() << "', '"
		<< strPassword.c_str()<<"', '" 
		<< GetDateTimeUTC().c_str() << "')";

	 return this->Query(osToFillUser);
}

// method checks if user exists 
bool SocketChat::SocketChatDataProvider::CheckUser(std::string & strLogin, std::string & strPassword)const
{
	bool bRet = false; 

	// creates new query for getting bool value from DB about existing login and password 
	std::ostringstream osCheckUser; 
	osCheckUser << "SELECT IF (EXISTS (SELECT * FROM "
		<< GlobalDataVariables::strUsersTable.c_str()
		<< " WHERE login='"
		<< strLogin.c_str()
		<< "' AND password='"
		<< strPassword.c_str()
		<< "' LIMIT 1), 1, 0);";

	this->Query(osCheckUser);

	std::vector<std::vector<std::string>> vec_strResultOfQuery = std::vector<std::vector<std::string>>();
	vec_strResultOfQuery = this->GetResult();

	// inspection of returned value 
	if(vec_strResultOfQuery.size()==1 && vec_strResultOfQuery[0].size()==1 && vec_strResultOfQuery[0][0]=="1")
	{
		bRet = true;
	}

	return bRet;
}

int SocketChat::SocketChatDataProvider::StartActivity(std::string & strLogin)const
{
	std::ostringstream osStartActivity; 
	osStartActivity << "INSERT INTO "
		<< GlobalDataVariables::strActivityTable.c_str()
		<< "(user_id, date_in) VALUES((SELECT id FROM "
		<<  GlobalDataVariables::strUsersTable.c_str()
		<<" WHERE login='"
		<< strLogin.c_str()
		<< "'), '"
		<< this->GetDateTimeUTC().c_str()
		<< "');";

	return this->Query(osStartActivity);
}

int SocketChat::SocketChatDataProvider::FinishActivity(std::string & strLogin) const
{

	std::ostringstream osFinishActivity; 
	osFinishActivity << "UPDATE "
		<< GlobalDataVariables::strActivityTable.c_str()
		<< " SET date_out='"
		<< this->GetDateTimeUTC().c_str()
		<< "' WHERE user_id=(SELECT id FROM "
		<< GlobalDataVariables::strUsersTable.c_str()
		<< " WHERE login='"
		<< strLogin.c_str()
		<< "') ORDER BY date_in DESC LIMIT 1;";

	return this->Query(osFinishActivity);
}

int SocketChat::SocketChatDataProvider::InsertIntoMessages(std::string & strLogin, std::string & strMessage) const
{
	std::ostringstream osInsertToMessages;
	osInsertToMessages << "INSERT INTO "
		<< GlobalDataVariables::strMessageTable.c_str()
		<< "(user_id, date, message) VALUES((SELECT id FROM "
		<< GlobalDataVariables::strUsersTable.c_str()
		<< " WHERE login='"
		<< strLogin.c_str()
		<< "'), '"
		<< this->GetDateTimeUTC().c_str()
		<< "', '"
		<< strMessage.c_str()
		<< "');";

	return this->Query(osInsertToMessages);
}

std::string SocketChat::SocketChatDataProvider::GetDateTimeUTC(void)
{
	time_t     now = time(0);
	struct tm  tstruct;

	try
	{
		if (gmtime_s(&tstruct, &now))
		{
			throw std::exception();
		}
	}
	catch (const SocketChat::TCPException &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::ostringstream osTime;
	osTime
		<< tstruct.tm_year + 1900 << "-"
		<< tstruct.tm_mon + 1 << "-"
		<< tstruct.tm_mday << " "
		<< tstruct.tm_hour << ":"
		<< tstruct.tm_min << ":"
		<< tstruct.tm_sec;

	return osTime.str();
}