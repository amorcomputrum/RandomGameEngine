#pragma once

#include<map>

#include "tmxparser/tmxparser.h"

#include "RGE/Window/Render/Sprite.h"

namespace RGE{
	class TmxWorld
	{
	public:
		TmxWorld(){};
		TmxWorld(const char* file, const char* folder);

		void render();
	protected:
		
	private:
		tmxparser::TmxMap* map;
		//map sprites by gid
		std::map<int, RGE::Sprite*> sprites;
		int mapWidth, mapHeight;
		int tileWidth, tileHeight;

		void loadSprites();
	};
}