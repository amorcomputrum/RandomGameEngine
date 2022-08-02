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
		TmxWorld(const char* file, const char* folder,void(*loadTile)(int,int,int));

		void render();

		int getTile(int x, int y, int layer);
		void setTile(int x, int y, int layer, int gid);
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