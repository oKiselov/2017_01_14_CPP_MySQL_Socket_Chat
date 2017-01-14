#pragma once
#include <vector>
#include <string>

namespace SocketChat
{
	class Convertor
	{
	public:
		static std::vector<unsigned char> DataToVectorUC(
			const int &iCode,
			const std::string &strData);


		static std::pair<int, std::string> VectorUCToData(
			std::vector<unsigned char>&vec);

		// Method for encryption / decryption of sended information 
		static std::vector<unsigned char> XOR(std::vector<unsigned char> &vecChar);
	};
}