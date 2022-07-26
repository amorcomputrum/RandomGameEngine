#include "RGE/System/File.h"
#include <cstddef>
#include <sstream>
#include <iostream>

RGE::File::File(std::string filename){
	fileLoc = filename;
	input.open(filename,std::ios::binary);
	output.open(filename,std::ios::app | std::ios::binary);
}

RGE::File::~File(){
	input.close();
	output.close();
}

std::string RGE::File::getLine(unsigned int line){
	std::string text;
	for(int i = 0; i < line; i++){
		text = "";
		std::getline(this->input,text);
	}
	std::string result = "";
	std::istringstream iss(text);
	int word;
	while(iss >> std::hex >> word){
		result += char(word);
	}
	input.seekg(0);
	output.flush();
	return result;
}

std::string RGE::File::getFileLocation(){
	return fileLoc;
}

void RGE::File::setLine(unsigned int line, std::string data){
	input.seekg(0);
	std::ofstream newFile;
	newFile.open("replacementFileForTemp.rmfp",std::ios::app);
	int lineNum = 0;
	std::string lineData;
	while(std::getline(this->input,lineData)){
		lineNum++;
		if(lineNum != line){
			newFile << lineData << std::endl;
		}else{
			newFile << to_bytes(data) << std::endl;
		}
		
	}
	newFile.close();
	input.close();
	output.close();
	std::remove(fileLoc.c_str());
	std::rename("replacementFileForTemp.rmfp",fileLoc.c_str());
	input.open(fileLoc);
	output.open(fileLoc,std::ios::app);
}

void RGE::File::writeLine(std::string data){
	//output.seekp(std::ios_base::cur,std::ios_base::end);
	if(output.tellp() != 0){
		output << std::endl;
		output << to_bytes(data);
	} 
	else {

		output << to_bytes(data);
	}
	output.flush();
}

void RGE::File::open(){
	if(!input.is_open()){
		input.open(fileLoc);
	}
	if(!output.is_open()){
		output.open(fileLoc);
	}
}

void RGE::File::close(){
	input.close();
	output.close();
}

RGE::File RGE::File::operator<<(std::string param){
	output << to_bytes(param);
	output.flush();
}

std::string RGE::File::to_bytes(std::string data){
	std::stringstream val;
	for(size_t i = 0; i < data.size(); i++){
		val << std::hex << int(data[i]);
		val << " ";
	}
	return val.str();
}