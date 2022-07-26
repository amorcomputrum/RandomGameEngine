#pragma once

#include <fstream>

namespace RGE{
	class File{
	public:
		int numLines;
		
		File(std::string filename);
		~File();
		std::string getLine(unsigned int line);
		std::string getFileLocation();
		void setLine(unsigned int line,std::string data);
		void writeLine(std::string data);
		void open();
		void close();
		void rename(std::string newName);
		RGE::File operator<<(std::string param);
	private:
		std::ifstream input;
		std::ofstream output;
		std::string fileLoc;
		std::string to_bytes(std::string data);
	};
}
