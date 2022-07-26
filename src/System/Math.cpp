#include <time.h>

#include "RGE/System/Math.h"

double RGE::Distance(double x1, double y1, double x2, double y2){
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int RGE::Random(int min, int max){
	srand(time(NULL));
	return rand() % (max - min + 1) + min;
}

RGE::Vector2d RGE::toGrid(int x, int y, int gridSize){
	return RGE::Vector2d(x-(x%gridSize), y-(y%gridSize));
}