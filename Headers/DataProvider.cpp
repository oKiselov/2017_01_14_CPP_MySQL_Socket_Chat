#include "DataProvider.h"
#include "TCPException.h"

SocketChat::DataProvider::DataProvider()
{
	this->handle = nullptr;
	this->connection = nullptr;
}

SocketChat::DataProvider::~DataProvider()
{
}

void SocketChat::DataProvider::Initialize(void)
{
	this->handle = mysql_init(nullptr);
	if (!this->handle)
	{
		throw TCPException(mysql_error(this->handle));
	}
}

void SocketChat::DataProvider::SetConnection(void)
{
	this->connection = mysql_real_connect(
		this->handle,
		GlobalDataVariables::strIPadress.c_str(),
		GlobalDataVariables::strUserAccount.c_str(),
		GlobalDataVariables::strPassword.c_str(),
		GlobalDataVariables::strNameDB.c_str(),
		GlobalDataVariables::iPort,
		0,
		0);

	if (!this->connection)
	{
		throw TCPException(mysql_error(this->handle));
	}

	/*
	This function is used to set 
	the default character set for the current connection.
	
	Return Values
	Zero for success. Nonzero if an error occurred.
	*/
	mysql_set_character_set(this->handle, "cp1251");
}

int SocketChat::DataProvider::Query(std::ostringstream & os) const
{
	//std::string strTempQuery = os.str();

	int iRet = mysql_query(this->handle, os.str().c_str());

	if (iRet!=0)
	{
		throw TCPException(mysql_error(this->handle));
	}
	// Zero for success. Nonzero if an error occurred.
	return 0;
}

std::vector<std::vector<std::string>> SocketChat::DataProvider::GetResult(void)const
{
	std::vector<std::vector<std::string>> vec_strResultOfQuery;
	std::vector<std::string> vec_strForRow;
	/*
	mysql::store_result() will fetch the whole resultset from the MySQL server 
	while mysqli::use_result() will fetch the rows one by one.
	*/
	if (MYSQL_RES *resultOfQueryExecution = mysql_store_result(this->handle))
	{
		while (MYSQL_ROW rowFromResTable = mysql_fetch_row(resultOfQueryExecution))
		{
			unsigned int i = 0;
			for (; i < mysql_num_fields(resultOfQueryExecution); i++)
			{
				vec_strForRow.push_back(
					rowFromResTable[i] ? rowFromResTable[i] : "NULL");
			}
			vec_strResultOfQuery.push_back(vec_strForRow);
		}
		mysql_free_result(resultOfQueryExecution);
	}
	return vec_strResultOfQuery; 
}

void SocketChat::DataProvider::CloseConnection(void)const
{
	mysql_close(this->handle);
}
