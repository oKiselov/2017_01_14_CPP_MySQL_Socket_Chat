#pragma once
#include <string>

namespace SocketChat
{
	// Class for work with Console 
	class ViewController
	{
	public:
		static void ShowText(std::string strText);

		static std::string ReadText(void); 
	};
}
