#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

std::string getCharByte(char c){
	char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	std::string output;
	char const byte = c;
	output += "0x";
	output += hex_chars[ ( byte & 0xF0 ) >> 4 ];
	output += hex_chars[ ( byte & 0x0F ) >> 0 ];
	return(output);
}
