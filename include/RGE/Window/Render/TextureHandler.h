#pragma once

//#define STB_IMAGE_IMPLEMENTATION

#include "RGE/Window/Render/stb_image.h"

#include <vector>
#include <string>

namespace txHandler{
	class Texture{
	public:
		int w,h,type;
		std::string FILE;
		unsigned int texture;
		Texture();
		Texture(std::string filename);
	};
	static std::vector<Texture> textures;
	void generateTexture(std::string filename);
	Texture getTexture(std::string filename);
}