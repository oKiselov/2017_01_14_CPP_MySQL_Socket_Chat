#include "Convertor.h"
#include <iostream>
#include <bitset>

std::vector<unsigned char> SocketChat::Convertor::DataToVectorUC(const int & iCode, const std::string & strData)
{
	std::vector<unsigned char> vec(sizeof iCode + strData.length());
	memcpy_s(&vec[0], vec.size(), &iCode, sizeof iCode);
	memcpy_s(&vec[sizeof iCode], vec.size() - sizeof iCode, &strData[0], strData.length());
	return vec;
}

std::pair<int, std::string> SocketChat::Convertor::VectorUCToData(std::vector<unsigned char>& vec)
{
	std::pair<int, std::string> p;
	memcpy_s(&p.first, sizeof(p.first), &vec[0], sizeof(p.first));
	p.second.resize(vec.size() - sizeof(p.first) + 1);
	memcpy_s(&p.second[0], p.second.size(), &vec[sizeof(p.first)], vec.size() - sizeof(p.first));
	return p;
}

std::vector<unsigned char> SocketChat::Convertor::XOR(std::vector<unsigned char>& vecChar)
{
	std::vector<unsigned char> vecRet(vecChar.size()); 
	for (int i = 0; i < vecChar.size(); i++)
	{
		std::bitset<8> bContainer(vecChar[i]);
		std::bitset<8> bKey(static_cast<int>(vecChar[i%vecChar.size()]));
		bContainer ^= bKey; 
		int from_XOR = bContainer.to_ulong();
		vecRet[i] = static_cast<unsigned char>(from_XOR); 
	}
	return vecRet;
}

