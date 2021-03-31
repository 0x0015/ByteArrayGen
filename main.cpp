#include <sys/stat.h>
#include <sys/mman.h>
#include "charToString.hpp"
#include "ArguementHandler/ArgHandle.hpp"
#include "SimpleCppTextFileHandler/file.hpp"

int main(int argc, char** argv){
	ArguementHandler* args = new ArguementHandler(argc, argv);
	
	if(args->hasArg("-h")){
		std::cout<<"Usage:  ByteArrayGen [input file] -o [output file] -v [variable name] -h (help)\n";
		exit(0);
	}

	std::string inputFile;
	if(args->hasArg("")){
		inputFile = args->findArgs("")[0].value;
	}else{
		std::cout<<"Please input a file"<<std::endl;
		exit(0);
	}
	
	std::string variableName = "";
	for(int i=0;i<inputFile.length();i++){
		if(!(inputFile.substr(i,1) == ".")){
			variableName = variableName + inputFile.substr(i,1);	
		}else{
			break;
		}
	}
	std::string outputFile = variableName + ".h";
	
	
	if(args->hasArg("-o")){
		outputFile = args->findArgs("-o")[0].value;
	}
	if(args->hasArg("-v")){
		variableName = args->findArgs("-o")[0].value;
	}

	std::ifstream infile(inputFile);
	std::vector<char> buffer;
	
	//get length of file
	infile.seekg(0, infile.end);
	size_t length = infile.tellg();
	infile.seekg(0, infile.beg);
	
	//read file
	if (length > 0) {
	    buffer.resize(length);    
	    infile.read(&buffer[0], length);
	}
	
	std::string output = "";
	output = output + "//This is an autogenerated byte array for compiling files into the code\n\n";
	output = output + "#pragma once\n";
	output = output + "unsigned char " + variableName + "[] = {";
	for(int i=0;i<buffer.size();i++){
		output = output + getCharByte(buffer[i]) + ",";
	}
	output = output + "}\n";
	writeFile(outputFile, output);
}
