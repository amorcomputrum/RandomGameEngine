#pragma once
#pragma GCC diagnostic ignored "-Wnarrowing"

#include <string>
#include <vector>

#include "RGE/Window/Render/Render.h"
#include "RGE/Window/Render/Sprite.h"

namespace RGE{
	class Animation{
	public:
		bool restarted = false;

		Animation();

		Animation(std::string file, unsigned int startX, unsigned int y    , unsigned int width, unsigned int height, unsigned int num   , unsigned int frameStep                  );

		Animation(std::string file, unsigned int startX, unsigned int stepX, unsigned int y    , unsigned int width , unsigned int height, unsigned int num, unsigned int frameStep);

		Animation(std::vector<RGE::Sprite*> sprites, int w, int h, unsigned int frameStep);

		void moveToFirstFrame();

		void resize(int width, int height);

		void stepFrame();

		void render(int x, int y);

		unsigned int getFrame();

		Animation copy();
	private:
		std::vector<RGE::Sprite*> sprites;
		int size[2];

		unsigned int frame = 0;
		unsigned int frameStep;
	};
};