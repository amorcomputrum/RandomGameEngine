#include "RGE/Utils/Animation.h"

RGE::Animation::Animation(){}

RGE::Animation::Animation(std::string file, unsigned int startX, unsigned int y    , unsigned int width, unsigned int height, unsigned int num   , unsigned int frameStep                  ){
	this->frameStep = frameStep;
	//Loads file at starting point then steps by width
	this->size[0]   = width;
	this->size[1]   = height;

	for(int i = 0; i < num; i++){
		sprites.push_back(new RGE::Sprite(file.c_str(), startX + (width*i), y, width, height));
	}
}

RGE::Animation::Animation(std::string file, unsigned int startX, unsigned int stepX, unsigned int y    , unsigned int width , unsigned int height, unsigned int num, unsigned int frameStep){
	this->frameStep = frameStep;
	//Loads file at starting point then steps by stepX
	this->size[0]   = width;
	this->size[1]   = height;

	for(int i = 0; i < num; i++){
		sprites.push_back(new RGE::Sprite(file.c_str(), startX + stepX*i, y, width, height));
	}
}

RGE::Animation::Animation(std::vector<RGE::Sprite*> sprites, int w, int h, unsigned int frameStep){
	this->size[0]   = w;
	this->size[1]   = h;

	this->sprites   = sprites;
	this->frameStep = frameStep;
}

void RGE::Animation::moveToFirstFrame(){
	frame = 0;
}

void RGE::Animation::resize(int width, int height){
	this->size[0]   = width;
	this->size[1]   = height;
}

void RGE::Animation::stepFrame(){
	restarted = false;
	frame++;
	if(frame >= sprites.size()*frameStep){
		frame = 0;
		restarted = true;
	}
}

void RGE::Animation::render(int x, int y){
	sprites[round(frame/frameStep)]->resize(size[0], size[1]);
	RGE::Window::Render::drawSprite(sprites[round(frame/frameStep)], x, y);
}

unsigned int RGE::Animation::getFrame(){
	return frame;
}

RGE::Animation RGE::Animation::copy(){
	return Animation(sprites,size[0],size[1],frameStep);
}