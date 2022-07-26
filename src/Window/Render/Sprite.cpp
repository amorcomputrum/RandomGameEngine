#include "RGE/glLibs/glad/glad.h"
#include "RGE/Window/Render/TextureHandler.h"

#include "RGE/Window/Render/Sprite.h"

RGE::Sprite::Sprite(){}

RGE::Sprite::Sprite(std::string FILE){
	this->FILE = FILE;
	txHandler::generateTexture(FILE);
	txHandler::Texture tex = txHandler::getTexture(FILE);
	this->width = tex.w;
	this->height = tex.h;
	loadShader(0,0,tex.w,tex.h,tex.w,tex.h);
}

RGE::Sprite::Sprite(std::string FILE, int x, int y, int width, int height){
	this->FILE = FILE;
	txHandler::generateTexture(FILE);
	txHandler::Texture tex = txHandler::getTexture(FILE);
	this->width = width;
	this->height = height;
	loadShader(x,y,width,height,tex.w,tex.h);
}

void RGE::Sprite::resize(int width, int height){
	this->width = width;
	this->height = height;
}

int RGE::Sprite::getWidth() {
	return this->width;
}

int RGE::Sprite::getHeight(){
	return this->height;
}

unsigned int RGE::Sprite::getVAO(){
	return VAO;
}

void RGE::Sprite::Bind(){
	glActiveTexture(GL_TEXTURE0);
	txHandler::Texture tex = txHandler::getTexture(this->FILE);
	glBindTexture(GL_TEXTURE_2D, tex.texture);
}

void RGE::Sprite::loadShader(int x,int y,int width, int height,int imageW, int imageH){

	//Define the sides of the sprite to load
	float lx,ty,rx,by;
	lx =  (x + 0.5)/(imageW*1.0f) ;
	ty =  (y + 0.5)/(imageH*1.0f);
	rx = (x + width*1.0f)/(imageW*1.0f);
	by = (y + height*1.0f)/(imageH*1.0f);

	float vertices[] = {
		0.0f, 1.0f, lx, by,
		1.0f, 0.0f, rx, ty,
		0.0f, 0.0f, lx, ty,

		0.0f, 1.0f, lx, by,
		1.0f, 1.0f, rx, by,
		1.0f, 0.0f, rx, ty
	};

	//Prepare Buffers
	glGenVertexArrays(1, &this->VAO);

	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);
}