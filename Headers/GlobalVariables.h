#pragma once

// Global constants and variables 
namespace GlobalVariables
{
	// message is automatically cutted of till this size 
	const int iMaxSizeOfMessage = 1054;

	// marks for registration or login modes 
	const std::string RegMode = "Reg";

	const std::string LogMode = "Log";

	enum iVariantConnection
	{
		defaultConnection = 1,
		manualConnection = 2
	};

	enum iEntrance
	{
		Login = 1,
		Register = 2
	};

	enum iAnswerAuthorizationQuery
	{
		Valid = 1,
		Invalid = 2
	};

}