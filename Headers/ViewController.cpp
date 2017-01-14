#include "ViewController.h"
#include <iostream>

void SocketChat::ViewController::ShowText(std::string strText)
{
	std::cout << strText << std::endl;
}

std::string SocketChat::ViewController::ReadText(void)
{
	std::string strRet = std::string();
	std::getline(std::cin, strRet);
	return strRet; 
}
