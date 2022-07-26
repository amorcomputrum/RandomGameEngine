#pragma once
#pragma GCC diagnostic ignored "-Wconversion-null"
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
#pragma GCC diagnostic ignored "-Wpointer-arith"

#include <string>

#include "RGE/World/Block.h"
#include "RGE/World/Chunk.h"

namespace RGE{
	class GridWorld{
	public:
		GridWorld();
		GridWorld(std::string name);
		GridWorld(int width, int height, int blockSize, int chunkWidth, int chunkHeight, int layers, std::string name);

		void destroyBlock(int chunkX, int chunkY, int x, int y, int layer);
		void destroyBlock(int x, int y, int layer);

		void setBlock(int chunkX, int chunkY, int x, int y, int layer, RGE::Block block);
		void setBlock(int x, int y, int layer, RGE::Block block);

		void loadWorld();
		void saveWorld();

		//convert to chunkX,chunkY,x,y
		int* toWorldCords(int x, int y);

		//Auto-Tile Block at specified position
		void updateBlockShape(int chunkX, int chunkY, int x, int y, int layer);

		//Update blocks around specified position
		void updateBlockShapeAround(int chunkX, int chunkY, int x, int y, int layer);

		RGE::Block getBlock(int chunkX, int chunkY, int x, int y, int layer);
		RGE::Block getBlock(int x, int y, int layer);

	private:
		double seed;
		
		int blockSize;
		int* worldSize;
		int* chunkSize;

		std::string name;

		RGE::Chunk** chunks;

		void createChunks();
		void checkCords(int chunkX, int chunkY, int x, int y, int layer);

		RGE::Block getBlock(std::string data, int layer);

		int getTopBlock        (int chunkX, int chunkY, int x, int y, int layer);
		int getBottomBlock     (int chunkX, int chunkY, int x, int y, int layer);
		int getRightBlock      (int chunkX, int chunkY, int x, int y, int layer);
		int getLeftBlock       (int chunkX, int chunkY, int x, int y, int layer);
		int getTopRightBlock   (int chunkX, int chunkY, int x, int y, int layer);
		int getBottomRightBlock(int chunkX, int chunkY, int x, int y, int layer);
		int getTopLeftBlock    (int chunkX, int chunkY, int x, int y, int layer);
		int getBottomLeftBlock (int chunkX, int chunkY, int x, int y, int layer);

	};
};