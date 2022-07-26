#include "RGE/World/AutoTiler.h"
#include "RGE/System/File.h"
#include "RGE/System/Exception.h"

#include <sstream>

#include "RGE/World/GridWorld.h"

RGE::GridWorld::GridWorld(){}

RGE::GridWorld::GridWorld(std::string name){
	this->name = name;
}

RGE::GridWorld::GridWorld(int width, int height, int blockSize, int chunkWidth, int chunkHeight, int layers, std::string name){
	int worldSizeArray[2] = {width, height};
	int chunkSizeArray[3] = {chunkWidth, chunkHeight, layers};

	this->worldSize = worldSizeArray;
	this->chunkSize = chunkSizeArray;
	this->blockSize = blockSize;
	this->name = name;

	createChunks();
}

void RGE::GridWorld::destroyBlock(int chunkX, int chunkY, int x, int y, int layer){
	checkCords(chunkX, chunkY, x, y, layer);
	this->chunks[chunkX][chunkY].data[x][y][layer] = RGE::Block();
}

void RGE::GridWorld::destroyBlock(int x, int y, int layer){
	int* loc{toWorldCords(x,y)};
	destroyBlock(loc[0], loc[1], loc[2], loc[4], layer);
}

void RGE::GridWorld::setBlock(int chunkX, int chunkY, int x, int y, int layer, RGE::Block block){
	checkCords(chunkX, chunkY, x, y, layer);
	this->chunks[chunkX][chunkY].data[x][y][layer] = block;
}

void RGE::GridWorld::setBlock(int x, int y, int layer, RGE::Block block){
	int* loc{toWorldCords(x,y)};
	setBlock(loc[0], loc[1], loc[2], loc[4], layer, block);
}

void RGE::GridWorld::loadWorld(){
	RGE::File* worldFile = new RGE::File("Worlds/" + this->name + ".world");

	//get base variables
	std::string line = worldFile->getLine(1);

	std::stringstream ss(line);

	//grab metadata
	std::string width;
	std::string height;
	std::string chunkWidth;
	std::string chunkHeight;
	std::string layer;
	std::string block_size;

	getline(ss,width,':');
	getline(ss,height,':');
	getline(ss,chunkWidth,':');
	getline(ss,chunkHeight,':');
	getline(ss,layer,':');
	getline(ss,block_size,':');

	int worldSizeArray[2] = {std::stoi(width), std::stoi(height)};
	this->worldSize = worldSizeArray;

	int chunkSizeArray[3] = {std::stoi(chunkWidth), std::stoi(chunkHeight), std::stoi(layer)};
	this->chunkSize = chunkSizeArray;

	this->blockSize = std::stoi(block_size);


	for(int chunkY = 0; chunkY < this->worldSize[1]; chunkY++){
		std::string line = worldFile->getLine(chunkY+2);
		std::stringstream ss(line);
		//iterate each chunk on line
		for(int a = 0; a < this->worldSize[0]*(this->chunkSize[0]*this->chunkSize[1]); a+=this->chunkSize[0]*this->chunkSize[1]){
			int chunkX = a/(this->chunkSize[0]*this->chunkSize[1]);
			Chunk chunk = Chunk();
			for(int y = 0; y < this->chunkSize[1]; y++){
				for(int x = 0; x < this->chunkSize[0]; x++){
					//get Block data
					std::string data;
					getline(ss,data,',');
					for(int z = 0; z < this->chunkSize[3]; z++){
						chunk.data[x][y][z] = getBlock(data,z);
					}
				}
			}
			this->chunks[chunkX][chunkY] = chunk;
		}
	}
	worldFile->close();
}

void RGE::GridWorld::saveWorld(){
	RGE::File* file = new RGE::File("Worlds/save.tempworld");

	std::string metaData = "";
	metaData += std::to_string(this->worldSize[0]) + ":";
	metaData += std::to_string(this->worldSize[1]) + ":";
	metaData += std::to_string(this->chunkSize[0]) + ":";
	metaData += std::to_string(this->chunkSize[1]) + ":";
	metaData += std::to_string(this->chunkSize[2]) + ":";
	metaData += std::to_string(this->blockSize   ) + ":";

	file->writeLine(metaData);

	for(int chunkY = 0; chunkY < this->worldSize[1]; chunkY++){
		std::string line;
		for(int chunkX = 0; chunkX < this->worldSize[0]; chunkX++){
			for(int y = 0; y < this->chunkSize[1]; y++){
				for(int x = 0; x < this->chunkSize[0]; x++){
					for(int z = 0; z < this->chunkSize[3]; z++){
						line += std::to_string(chunks[chunkX][chunkY].data[x][y][z].id);
						if(z+1 < this->chunkSize[3]) line += ":";
						else line += ",";
					}
				}
			}
		}
		file->writeLine(line);
	}
	file->close();
	delete(file);
	std::string oldFile = "Worlds/" + this->name + ".world";
	std::remove(oldFile.c_str());
	std::rename("Worlds/save.tempworld",oldFile.c_str());
}

int* RGE::GridWorld::toWorldCords(int x, int y){
	int chunkX = ((int)(x)-((int)(x)%(this->chunkSize[0]*this->blockSize)))/(this->chunkSize[0]*this->blockSize);
	int chunkY = ((int)(y)-((int)(y)%(this->chunkSize[1]*this->blockSize)))/(this->chunkSize[1]*this->blockSize);

	x = (((int)(x)-((int)(x)%(this->blockSize)))/(this->blockSize)) - (chunkX*this->chunkSize[0]);
	y = (((int)(y)-((int)(y)%(this->blockSize)))/(this->blockSize)) - (chunkY*this->chunkSize[1]);

	int cords[4] = {chunkX, chunkY, x, y};

	return cords;
}

void RGE::GridWorld::updateBlockShape(int chunkX, int chunkY, int x, int y, int layer){
	checkCords(chunkX, chunkY, x, y, layer);

	RGE::Block currentBlock = chunks[chunkX][chunkY].data[x][y][layer];

	if(currentBlock.id == -1) return;

	int topBlock         = getTopBlock        (chunkX, chunkY, x, y, layer);
	int bottomBlock      = getBottomBlock     (chunkX, chunkY, x, y, layer);
	int leftBlock        = getLeftBlock       (chunkX, chunkY, x, y, layer);
	int rightBlock       = getRightBlock      (chunkX, chunkY, x, y, layer);
	int topLEFTBlock     = getTopLeftBlock    (chunkX, chunkY, x, y, layer);
	int topRIGHTBlock    = getTopRightBlock   (chunkX, chunkY, x, y, layer);
	int bottomLEFTBlock  = getBottomLeftBlock (chunkX, chunkY, x, y, layer);
	int bottomRIGHTBlock = getBottomRightBlock(chunkX, chunkY, x, y, layer);

	//Bit Masking
	chunks[chunkX][chunkY].data[x][y][layer].shape = RGE::AutoTiler::tile(currentBlock.id,topBlock,bottomBlock,leftBlock,rightBlock,topLEFTBlock,topRIGHTBlock,bottomLEFTBlock,bottomRIGHTBlock);
}

void RGE::GridWorld::updateBlockShapeAround(int chunkX, int chunkY, int x, int y, int layer){
	checkCords(chunkX, chunkY, x, y, layer);

	if(getTopBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkY != 0){
			if(y > 0) updateBlockShape(chunkX, chunkY  , x, y-1            , layer);
			else      updateBlockShape(chunkX, chunkY-1, x, this->chunkSize[1]-1, layer);
		}else{
			if(y > 0) updateBlockShape(chunkX, chunkY  , x, y-1            , layer);
		}
	}
	if(getBottomBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkY+1 < this->worldSize[1]){
			if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX, chunkY  , x, y+1, layer);
			else                         updateBlockShape(chunkX, chunkY+1, x, 0  , layer);
		}else{
			if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX, chunkY  , x, y+1, layer);
		}
	}
	if(getLeftBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkX != 0){
			if(x > 0) updateBlockShape(chunkX  , chunkY, x-1           , y, layer);
			else      updateBlockShape(chunkX-1, chunkY, this->chunkSize[0]-1, y, layer);
		}else{
			if(x > 0) updateBlockShape(chunkX  , chunkY, x-1           , y, layer);
		}
	}
	if(getRightBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkX+1 < this->worldSize[0]){
			if(x+1 < this->chunkSize[0]) updateBlockShape(chunkX  , chunkY, x+1, y, layer);
			else                         updateBlockShape(chunkX+1, chunkY, 0  , y, layer);
		}else{
			if(x+1 < this->chunkSize[0]) updateBlockShape(chunkX  , chunkY, x+1, y, layer);
		}
	}
	if(getTopLeftBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkY != 0){
			if(chunkX != 0){
				if(x > 0){
					if(y > 0) updateBlockShape(chunkX  , chunkY  , x-1           , y-1            , layer);
					else      updateBlockShape(chunkX  , chunkY-1, x-1           , this->chunkSize[1]-1, layer);
				}else{
					if(y > 0) updateBlockShape(chunkX-1, chunkY  , this->chunkSize[0]-1, y-1            , layer);
					else      updateBlockShape(chunkX-1, chunkY-1, this->chunkSize[0]-1, this->chunkSize[1]-1, layer);
				}
			}else{
				if(x > 0){
					if(y > 0) updateBlockShape(chunkX  , chunkY  , x-1           , y-1            , layer);
					else      updateBlockShape(chunkX  , chunkY-1, x-1           , this->chunkSize[1]-1, layer);
				}
			}
		}else{
			if(y > 0){
				if(chunkX != 0){
					if(x > 0) updateBlockShape(chunkX  , chunkY  , x-1           , y-1            , layer);
					else      updateBlockShape(chunkX-1, chunkY  , this->chunkSize[0]-1, y-1            , layer);
				}else{
					if(x > 0) updateBlockShape(chunkX  , chunkY  , x-1           , y-1            , layer);
				}
			}
		}
	}
	if(getTopRightBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkY != 0){
			if(chunkX+1 < this->worldSize[0]){
				if(x+1 < this->chunkSize[0]){
					if(y > 0) updateBlockShape(chunkX  , chunkY  , x+1, y-1            , layer);
					else      updateBlockShape(chunkX  , chunkY-1, x+1, this->chunkSize[1]-1, layer);
				}else{
					if(y > 0) updateBlockShape(chunkX+1, chunkY  , 0  , y-1            , layer);
					else      updateBlockShape(chunkX+1, chunkY-1, 0  , this->chunkSize[1]-1, layer);
				}
			}else{
				if(x+1 < this->chunkSize[0]){
					if(y > 0) updateBlockShape(chunkX  , chunkY  , x+1, y-1            , layer);
					else      updateBlockShape(chunkX  , chunkY-1, x+1, this->chunkSize[1]-1, layer);
				}
			}
		}else{
			if(y > 0){
				if(chunkX+1 < this->worldSize[0]){
					if(x+1 < this->chunkSize[0]) updateBlockShape(chunkX  , chunkY, x+1, y-1, layer);
					else                         updateBlockShape(chunkX+1, chunkY, 0  , y-1, layer);
				}else{
					if(x+1 < this->chunkSize[0]) updateBlockShape(chunkX  , chunkY, x+1, y-1, layer);
				}
			}
		}
	}
	if(getBottomLeftBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkY+1 < this->worldSize[1]){
		if(chunkX != 0){
			if(x > 0){
				if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX, chunkY  , x-1, y+1, layer);
				else                         updateBlockShape(chunkX, chunkY+1, x-1, 0  , layer);
			}else{
				if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX-1, chunkY  , this->chunkSize[0]-1, y+1, layer);
				else                         updateBlockShape(chunkX-1, chunkY+1, this->chunkSize[0]-1, 0  , layer);
			}
		}else{
			if(x > 0){
				if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX, chunkY  , x-1, y+1, layer);
				else                         updateBlockShape(chunkX, chunkY+1, x-1, 0  , layer);
			}
		}
	}else{
		if(y+1 < this->chunkSize[1]){
			if(chunkX != 0){
				if(x > 0) updateBlockShape(chunkX  , chunkY, x-1           , y+1, layer);
				else      updateBlockShape(chunkX-1, chunkY, this->chunkSize[0]-1, y+1, layer);
			}else{
				if(x > 0) updateBlockShape(chunkX  , chunkY, x-1           , y+1, layer);
			}
		}
	}
	}
	if(getBottomRightBlock(chunkX, chunkY, x, y, layer) != NULL){
		if(chunkY+1 < this->worldSize[1]){
			if(chunkX+1 < this->worldSize[0]){
				if(x+1 < this->chunkSize[0]){
					if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX  , chunkY  , x+1, y+1, layer);
					else                         updateBlockShape(chunkX  , chunkY+1, x+1, 0  , layer);
				}else{
					if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX+1, chunkY  , 0  , y+1, layer);
					else                         updateBlockShape(chunkX+1, chunkY+1, 0  , 0  , layer);
				}
			}else{
				if(x+1 < this->chunkSize[0]){
					if(y+1 < this->chunkSize[1]) updateBlockShape(chunkX  , chunkY  , x+1, y+1, layer);
					else                         updateBlockShape(chunkX  , chunkY+1, x+1, 0  , layer);
				}
			}
		}else{
			if(y+1 < this->chunkSize[1]){
				if(chunkX+1 < this->worldSize[0]){
					if(x+1 < this->chunkSize[0])  updateBlockShape(chunkX  , chunkY  , x+1, y+1, layer);
					else                          updateBlockShape(chunkX+1, chunkY  , 0  , y+1, layer);
				}else{
					if(x+1 < this->chunkSize[0])  updateBlockShape(chunkX  , chunkY  , x+1, y+1, layer);
				}
			}
		}
	}

	updateBlockShape(chunkX, chunkY, x, y, layer);
}

RGE::Block RGE::GridWorld::getBlock(int chunkX, int chunkY, int x, int y, int layer){
	checkCords(chunkX, chunkY, x, y, layer);
	return chunks[chunkX][chunkY].data[x][y][layer];
}

RGE::Block RGE::GridWorld::getBlock(int x, int y, int layer){
	int* loc{toWorldCords(x,y)};
	return getBlock(loc[0], loc[1], loc[2], loc[3], layer);
}

void RGE::GridWorld::createChunks(){
	//create 2d array
	chunks = new RGE::Chunk*[this->worldSize[0]];

	for(int x = 0; x < this->worldSize[0]; x++){
		//allocate y layer
		chunks[x] = new RGE::Chunk[this->worldSize[1]];
		for(int y = 0; y < this->worldSize[1]; y++){
			//create chunks
			chunks[x][y] = RGE::Chunk(this->chunkSize[0],this->chunkSize[1],this->chunkSize[2]);
		}
	}
}

void RGE::GridWorld::checkCords(int chunkX, int chunkY, int x, int y, int layer){
	if(chunkX + 1 > this->worldSize[0] || chunkX < 0) throw RGE::exception("chunkX Out of Range");
	if(chunkY + 1 > this->worldSize[1] || chunkY < 0) throw RGE::exception("chunkY Out of Range");
	if(x + 1      > this->chunkSize[0] || x < 0)      throw RGE::exception("dataX Out of Range" );
	if(y + 1      > this->chunkSize[1] || y < 0)      throw RGE::exception("dataY Out of Range" );
	if(layer + 1  > this->worldSize[3] || layer < 0)  throw RGE::exception("Layer Out of Range" );
}

RGE::Block RGE::GridWorld::getBlock(std::string data, int layer){
	std::string ID;
	std::stringstream ss(data);
	//get ID from layer
	for(int i = 0; i < layer+1; i++){
		getline(ss,ID,':');
	}

	return RGE::Block(std::stoi(ID), 0);
}

int RGE::GridWorld::getTopBlock(int chunkX, int chunkY, int x, int y, int layer){
	int topBlock = NULL;

	//TOP BLOCK
	if(chunkY != 0){
		if(y > 0) topBlock = chunks[chunkX][chunkY].data[x][y-1][layer].id;
		else      topBlock = chunks[chunkX][chunkY-1].data[x][this->chunkSize[1]-1][layer].id;
	}else{
		if(y > 0) topBlock = chunks[chunkX][chunkY].data[x][y-1][layer].id;
	}

	return topBlock;
}

int RGE::GridWorld::getBottomBlock(int chunkX, int chunkY, int x, int y, int layer){
	int bottomBlock = NULL;

	//BOTTOM BLOCK
	if(chunkY+1 < this->worldSize[1]){
		if(y+1 < this->chunkSize[1]) bottomBlock = chunks[chunkX][chunkY].data[x][y+1][layer].id;
		else                    bottomBlock = chunks[chunkX][chunkY+1].data[x][0][layer].id;
	}else{
		if(y+1 < this->chunkSize[1]) bottomBlock = chunks[chunkX][chunkY].data[x][y+1][layer].id;
	}

	return bottomBlock;
}

int RGE::GridWorld::getRightBlock(int chunkX, int chunkY, int x, int y, int layer){
	int rightBlock = NULL;

	//NEXT BLOCK
	if(chunkX+1 < this->worldSize[0]){
		if(x+1 < this->chunkSize[0]) rightBlock = chunks[chunkX][chunkY].data[x+1][y][layer].id;
		else                   rightBlock = chunks[chunkX+1][chunkY].data[0][y][layer].id;
	}else{
		if(x+1 < this->chunkSize[0]) rightBlock = chunks[chunkX][chunkY].data[x+1][y][layer].id;
	}

	return rightBlock;
}

int RGE::GridWorld::getLeftBlock(int chunkX, int chunkY, int x, int y, int layer){
	int leftBlock = NULL;

	if(chunkX != 0){
		if(x > 0) leftBlock = chunks[chunkX][chunkY].data[x-1][y][layer].id;
		else      leftBlock = chunks[chunkX-1][chunkY].data[this->chunkSize[0]-1][y][layer].id;
	}else{
		if(x > 0) leftBlock = chunks[chunkX][chunkY].data[x-1][y][layer].id;
	}

	return leftBlock;
}

int RGE::GridWorld::getTopRightBlock(int chunkX, int chunkY, int x, int y, int layer){
	int topRIGHTBlock = NULL;

	if(chunkY != 0){
		if(chunkX+1 < this->worldSize[0]){
			if(x+1 < this->chunkSize[0]){
				if(y > 0) topRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y-1][layer].id;
				else      topRIGHTBlock = chunks[chunkX][chunkY-1].data[x+1][this->chunkSize[1]-1][layer].id;
			}else{
				if(y > 0) topRIGHTBlock = chunks[chunkX+1][chunkY].data[0][y-1][layer].id;
				else      topRIGHTBlock = chunks[chunkX+1][chunkY-1].data[0][this->chunkSize[1]-1][layer].id;
			}
		}else{
			if(x+1 < this->chunkSize[0]){
				if(y > 0) topRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y-1][layer].id;
				else      topRIGHTBlock = chunks[chunkX][chunkY-1].data[x+1][this->chunkSize[1]-1][layer].id;
			}
		}
	}else{
		if(y > 0){
			if(chunkX+1 < this->worldSize[0]){
				if(x+1 < this->chunkSize[0]) topRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y-1][layer].id;
				else                   topRIGHTBlock = chunks[chunkX+1][chunkY].data[0][y-1][layer].id;
			}else{
				if(x+1 < this->chunkSize[0]) topRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y-1][layer].id;
			}
		}
	}

	return topRIGHTBlock;
}

int RGE::GridWorld::getBottomRightBlock(int chunkX, int chunkY, int x, int y, int layer){
	int bottomRIGHTBlock = NULL;

	if(chunkY+1 < this->worldSize[1]){
		if(chunkX+1 < this->worldSize[0]){
			if(x+1 < this->chunkSize[0]){
				if(y+1 < this->chunkSize[1]) bottomRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y+1][layer].id;
				else                    bottomRIGHTBlock = chunks[chunkX][chunkY+1].data[x+1][0][layer].id;
			}else{
				if(y+1 < this->chunkSize[1]) bottomRIGHTBlock = chunks[chunkX+1][chunkY].data[0][y+1][layer].id;
				else                    bottomRIGHTBlock = chunks[chunkX+1][chunkY+1].data[0][0][layer].id;
			}
		}else{
			if(x+1 < this->chunkSize[0]){
				if(y+1 < this->chunkSize[1]) bottomRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y+1][layer].id;
				else                    bottomRIGHTBlock = chunks[chunkX][chunkY+1].data[x+1][0][layer].id;
			}
		}
	}else{
		if(y+1 < this->chunkSize[1]){
			if(chunkX+1 < this->worldSize[0]){
				if(x+1 < this->chunkSize[0]) bottomRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y+1][layer].id;
				else                   bottomRIGHTBlock = chunks[chunkX+1][chunkY].data[0][y+1][layer].id;
			}else{
				if(x+1 < this->chunkSize[0]) bottomRIGHTBlock = chunks[chunkX][chunkY].data[x+1][y+1][layer].id;
			}
		}
	}

	return bottomRIGHTBlock;
}

int RGE::GridWorld::getTopLeftBlock(int chunkX, int chunkY, int x, int y, int layer){
	int topLEFTBlock = NULL;

	if(chunkY != 0){
		if(chunkX != 0){
			if(x > 0){
				if(y > 0) topLEFTBlock = chunks[chunkX][chunkY].data[x-1][y-1][layer].id;
				else      topLEFTBlock = chunks[chunkX][chunkY-1].data[x-1][this->chunkSize[1]-1][layer].id;
			}else{
				if(y > 0) topLEFTBlock = chunks[chunkX-1][chunkY].data[this->chunkSize[0]-1][y-1][layer].id;
				else      topLEFTBlock = chunks[chunkX-1][chunkY-1].data[this->chunkSize[0]-1][this->chunkSize[1]-1][layer].id;
			}
		}else{
			if(x > 0){
				if(y > 0) topLEFTBlock = chunks[chunkX][chunkY].data[x-1][y-1][layer].id;
				else      topLEFTBlock = chunks[chunkX][chunkY-1].data[x-1][this->chunkSize[1]-1][layer].id;
			}
		}
	}else{
		if(y > 0){
			if(chunkX != 0){
				if(x > 0) topLEFTBlock = chunks[chunkX][chunkY].data[x-1][y-1][layer].id;
				else      topLEFTBlock = chunks[chunkX-1][chunkY].data[this->chunkSize[0]-1][y-1][layer].id;
			}else{
				if(x > 0) topLEFTBlock = chunks[chunkX][chunkY].data[x-1][y-1][layer].id;
			}
		}
	}

	return topLEFTBlock;
}

int RGE::GridWorld::getBottomLeftBlock(int chunkX, int chunkY, int x, int y, int layer){
	int bottomLEFTBlock = NULL;

	if(chunkY+1 < this->worldSize[1]){
		if(chunkX != 0){
			if(x > 0){
				if(y+1 < this->chunkSize[1]) bottomLEFTBlock = chunks[chunkX][chunkY].data[x-1][y+1][layer].id;
				else bottomLEFTBlock                    = chunks[chunkX][chunkY+1].data[x-1][0][layer].id;
			}else{
				if(y+1 < this->chunkSize[1]) bottomLEFTBlock = chunks[chunkX-1][chunkY].data[this->chunkSize[0]-1][y+1][layer].id;
				else bottomLEFTBlock                    = chunks[chunkX-1][chunkY+1].data[this->chunkSize[0]-1][0][layer].id;
			}
		}else{
			if(x > 0){
				if(y+1 < this->chunkSize[1]) bottomLEFTBlock = chunks[chunkX][chunkY].data[x-1][y+1][layer].id;
				else bottomLEFTBlock                    = chunks[chunkX][chunkY+1].data[x-1][0][layer].id;
			}
		}
	}else{
		if(y+1 < this->chunkSize[1]){
			if(chunkX != 0){
				if(x > 0) bottomLEFTBlock = chunks[chunkX][chunkY].data[x-1][y+1][layer].id;
				else bottomLEFTBlock      = chunks[chunkX-1][chunkY].data[this->chunkSize[0]-1][y+1][layer].id;
			}else{
				if(x > 0) bottomLEFTBlock = chunks[chunkX][chunkY].data[x-1][y+1][layer].id;
			}
		}
	}

	return bottomLEFTBlock;
}