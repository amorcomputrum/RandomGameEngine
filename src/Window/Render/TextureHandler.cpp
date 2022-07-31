#include <iostream>

#include "RGE/glLibs/glad/glad.h"

#include "RGE/System/Exception.h"

#include "RGE/Window/Render/TextureHandler.h"

txHandler::Texture::Texture(){}

txHandler::Texture::Texture(std::string filename){
	unsigned char* data = stbi_load(filename.c_str(), &w, &h, &type, 0);

	if(data == NULL) throw RGE::exception("Image[" + filename + "]: Failed to load");

	//Load Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Load Sprite according to its type(RGB,RGBA)
	if(type == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->FILE = filename;
}

void txHandler::generateTexture(std::string filename){
	//check if texture exists
	if(textures.size() != 0){
		for(int i = 0; i < textures.size(); i++){
			if(textures[i].FILE == filename) return;
		}
	}
	//if it does not then generate and store new texture
	textures.push_back(txHandler::Texture(filename));
}

txHandler::Texture txHandler::getTexture(std::string filename){
	//return texture info of file
	for(int i = 0; i < textures.size(); i++){
		if(textures[i].FILE == filename) return textures[i];
	}
}