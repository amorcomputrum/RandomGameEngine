#include <cstddef>

#include "RGE/World/Chunk.h"

RGE::Chunk::Chunk(int width, int height, int layers){
	this->width = width;
	this->height = height;
	this->layers = layers;

	makeData();
}

void RGE::Chunk::makeData(){
	//allocate array
	data = new RGE::Block**[this->width];

	for(int x = 0; x < this->width; x++){
		//allocate 2d
		data[x] = new RGE::Block*[this->height];

		for(int y = 0; y < this->height; y++){
			data[x][y] = new RGE::Block[this->layers];

			for(int z = 0; z < this->layers; z++){
				data[x][y][z] = RGE::Block();
			}
		}
	}
}