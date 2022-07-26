#include "RGE/System/Exception.h"

#include "RGE/Window/Render/Color.h"

//Define Variables
const RGE::Color RGE::Color::Black(0  , 0  , 0  );
const RGE::Color RGE::Color::Red  (255, 0  , 0  );
const RGE::Color RGE::Color::Green(0  , 255, 0  );
const RGE::Color RGE::Color::Blue (0  , 0  , 255);
const RGE::Color RGE::Color::White(255, 255, 255);

RGE::Color::Color(int r, int g, int b){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}else{
		throw RGE::exception("RGE::Color::Color - Out of Range 0-255");
	}
}

RGE::Color::Color(int r, int g, int b, int a){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255) && (a >= 0 && a <= 255)){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}else{
		throw RGE::exception("RGE::Color::Color - Out of Range 0-255");
	}
}

float RGE::Color::getFloat(int color){
	return (float) (color/255.0);
}
