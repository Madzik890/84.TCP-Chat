#pragma once

#include <vector>
#include "Encryptor_cpp.h"

#ifndef Caesar_hpp
#define Caesar_hpp

namespace Encryptor
{
	class Caesar : public Encryptor
	{
	public:
		std::vector<Etime>elapsed_time;
		unsigned int key = 0;

		Caesar(int key):key(key) {};

		std::string Decrypt(std::string input);//function for decrypting
		std::string Encrypt(std::string input);//function for decrypting
		std::string ReverseDecrypt(std::string input);//reverse decrypting
		std::string ReverseEncrypt(std::string input);//reverse encrypting

		void ChangeAlphabet(char alph[]);//changing alphabet

		char * GetAlphabet();//returing a alphabet
	private:

		char encrypt_letter(char letter);//encrypting a letter
		char decrypt_letter(char letter);//decrypting a letter
	};
}

#endif