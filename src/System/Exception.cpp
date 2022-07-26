#include "RGE/System/Exception.h"

RGE::exception::exception(std::string message){
	std::cerr << message << std::endl;
}