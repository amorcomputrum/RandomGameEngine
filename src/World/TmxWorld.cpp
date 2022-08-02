#include "RGE/World/TmxWorld.h"
#include "RGE/Window/Render/Render.h"
#include "RGE/Window/Camera.h"

#include <iostream>

RGE::TmxWorld::TmxWorld(const char* file,const char* folder){
	map = new tmxparser::TmxMap();
	tmxparser::parseFromFile(file, RGE::TmxWorld::map, folder);

	mapWidth = map->width;
	mapHeight = map->height;
	tileWidth = map->tileWidth;
	tileHeight = map->tileHeight;

	loadSprites();
}

RGE::TmxWorld::TmxWorld(const char* file, const char* folder,void(*loadTile)(int,int,int,int)){
	map = new tmxparser::TmxMap();
	tmxparser::parseFromFile(file, RGE::TmxWorld::map, folder);

	mapWidth = map->width;
	mapHeight = map->height;
	tileWidth = map->tileWidth;
	tileHeight = map->tileHeight;

	loadSprites();

	for(int layer = 0; layer < map->layerCollection.size(); layer++){
		for(int layerX = 0; layerX < map->layerCollection[layer].width; layerX++){
			for(int layerY = 0; layerY < map->layerCollection[layer].height; layerY++){

				int gid = map->layerCollection[layer].tiles[layerX+(layerY*mapWidth)].gid;
				int x = layerX*tileWidth;
				int y = layerY*tileHeight;

				loadTile(x, y, layer, gid);
			}
		}
	}

}

void RGE::TmxWorld::render(){
	int camX{RGE::Window::Camera::X}, camY{RGE::Window::Camera::Y};

	int startX = (camX - (camX%tileWidth))/tileWidth;
	int startY = (camY - (camY%tileHeight))/tileHeight;

	if(startX < 0) startX = 0;
	if(startY < 0) startY = 0;

	//loop through layers
	for(int layer = 0; layer < map->layerCollection.size(); layer++){
		//loop through from start x until x is the layer width or off camera
		for(int layerX = startX; layerX < map->layerCollection[layer].width && layerX*tileWidth < RGE::Window::Camera::X + RGE::Window::Camera::W; layerX++){
			//loop through from start y until y is the layer height or off camera
			for(int layerY = startY; layerY < map->layerCollection[layer].height && layerY*tileHeight < RGE::Window::Camera::Y + RGE::Window::Camera::H; layerY++){

				int gid = map->layerCollection[layer].tiles[layerX+(layerY*mapWidth)].gid;

				if(sprites[gid] != 0) {
					sprites[gid]->resize(tileWidth, tileHeight);
					RGE::Window::Render::drawSprite(sprites[gid], layerX*tileWidth, layerY*tileHeight);
				}

			}
		}
	}
}

int RGE::TmxWorld::getTile(int x, int y, int layer){
	return map->layerCollection[layer].tiles[x+(y*mapWidth)].gid;
}

int RGE::TmxWorld::getTile(int x, int y, std::string layer){
	return map->layerCollection[getLayer(layer)].tiles[x+(y*mapWidth)].gid;
}

void RGE::TmxWorld::setTile(int x, int y, int layer, int gid){
	map->layerCollection[layer].tiles[x+(y*mapWidth)].gid = gid;
}

void RGE::TmxWorld::setTile(int x, int y, std::string layer, int gid){
	map->layerCollection[getLayer(layer)].tiles[x+(y*mapWidth)].gid = gid;
}

void RGE::TmxWorld::resizeTiles(int w, int h){
	if(w <= 0) w = 1;
	if(h <= 0) h = 1;

	tileWidth = w;
	tileHeight = h;
}

void RGE::TmxWorld::loadSprites(){
	for(int file = 0; file < map->tilesetCollection.size(); file++){
		int first_gid = map->tilesetCollection[file].firstgid;
		//get defined offset
		int offsetX = map->tilesetCollection[file].offset.x;
		int offsetY = map->tilesetCollection[file].offset.y;
		//get tile width and height
		int width = map->tilesetCollection[file].tileWidth;
		int height = map->tilesetCollection[file].tileHeight;
		//get tile spacing and margins
		int spacing = map->tilesetCollection[file].tileSpacingInImage;
		int margin  = map->tilesetCollection[file].tileMarginInImage;

		for(int row = 0; row < map->tilesetCollection[file].rowCount; row++){
			for(int col = 0; col < map->tilesetCollection[file].colCount; col++){
				//calculate the x and y
				int x = (width*col) + (spacing*col) + margin + offsetX + offsetY;
				int y = (height*row) + (spacing*row) + margin + offsetX + offsetY;
				//place sprite into map with its respective gid

				int gid = first_gid + (col + (row * map->tilesetCollection[file].colCount) );
				
				if(sprites.find(gid) != sprites.end()) std::cout << "GID: " << gid << " FIRST_GID: " << first_gid << std::endl;

				sprites.insert(std::pair<int, RGE::Sprite*>(gid, new RGE::Sprite(map->tilesetCollection[file].image.source, x, y, width, height)));
			}
		}
	}
}

int RGE::TmxWorld::getLayer(std::string layer){
	for(int mapLayer = 0; mapLayer < map->layerCollection.size(); mapLayer++){
		if(map->layerCollection[mapLayer].name == layer) return mapLayer;
	}
	return {};
}