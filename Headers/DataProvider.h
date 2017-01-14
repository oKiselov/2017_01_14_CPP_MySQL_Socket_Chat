#pragma once

#include <Winsock.h>
#include <mysql.h>
#include <vector>

namespace GlobalDataVariables
{
	// PCname or IP adress
	static std::string strIPadress = "localhost";

	// account for DataBase MySQL
	static std::string strUserAccount = "root";

	// password
	static std::string strPassword = "MySQLDr0zd0vsk1y";

	// name of database
	static std::string strNameDB = "socket_chat_db";

	// names of tables in DB 
	static std::string strMessageTable = "chat_messages";

	static std::string strActivityTable = "chat_activity";

	static std::string strUsersTable = "chat_users";

	// port number 
	static int iPort = 3306;

}

namespace SocketChat
{
	class DataProvider
	{
	protected:
		MYSQL * handle;
		MYSQL * connection; 
	public:

		DataProvider();

		virtual ~DataProvider();

		void Initialize(void);

		void SetConnection(void);

		/*
		Executes the SQL statement pointed to by the null-terminated string stmt_str. 
		Normally, the string must consist of a single SQL statement 
		without a terminating semicolon (;) or \g. 
		If multiple-statement execution has been enabled, 
		the string can contain several statements separated by semicolons
		
		Return Values
		Zero for success. Nonzero if an error occurred.
		*/
		int Query(std::ostringstream &os) const;

		/*
		After invoking mysql_query() or mysql_real_query(), 
		you must call mysql_store_result() or mysql_use_result() for every statement 
		that successfully produces a result set 
		(SELECT, SHOW, DESCRIBE, EXPLAIN, CHECK TABLE, and so forth). 
		You must also call mysql_free_result() after you are done 
		with the result set.
		
		If you enable multiple-statement support, 
		you should retrieve results from calls to mysql_query() or mysql_real_query() 
		by using a loop that calls mysql_next_result() to determine whether there are more results

		Return Values
		A MYSQL_RES result structure with the results. 
		NULL (0) if an error occurred.
		*/
		std::vector<std::vector<std::string>> GetResult(void)const;

		/*
		Closes a previously opened connection. mysql_close() 
		also deallocates the connection handle pointed to by mysql 
		if the handle was allocated automatically by mysql_init() or mysql_connect().
		Return Values.      None.
		*/
		void CloseConnection(void)const;
	};
}