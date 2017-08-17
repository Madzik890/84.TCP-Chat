#pragma once
#include <string>

namespace Encryptor
{

	class Encryptor
	{
	public:

		class Etime
		{
		public:
			enum Type
			{
				decrypt,
				encrypt
			};
			Etime(double time, Type type, int lenght) :time(time), type(type), lenght(lenght) {};
			double time;//time to do
			Type type;//type of operation
			int lenght;//lenght of decrypted/encrypted text
		};

		virtual std::string Decrypt(std::string input) = 0;//function for decrypting
		virtual std::string Encrypt(std::string input) = 0;//function for decrypting
		virtual std::string ReverseDecrypt(std::string input) = 0;//reverse decrypting
		virtual std::string ReverseEncrypt(std::string input) = 0;//reverse encrypting
	};

}

