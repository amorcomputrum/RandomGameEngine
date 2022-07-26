#include "RGE/System/Clock.h"

RGE::Clock::Clock(){
	start();
}

void RGE::Clock::start(){
	time = std::chrono::high_resolution_clock::now();
}

double RGE::Clock::getTime(){
	return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - time).count();
}